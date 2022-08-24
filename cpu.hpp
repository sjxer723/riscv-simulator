#include "Forward.hpp"
#include "Memory.hpp"
#include "Pipeline/Decode.hpp"
#include "Pipeline/Execute.hpp"
#include "Pipeline/Fetch.hpp"
#include "Pipeline/Memoryaccess.hpp"
#include "Pipeline/Writeback.hpp"
#include "register.hpp"
#include "type.hpp"
#include <cstring>
#include <stdio.h>

#ifndef _CPU_HPP_
#define _CPU_HPP_

class CPU {
  private:
    Memory *mem;        // The register pointing to the main memory
    Register regs;      // Comman registers
    Fetch IF;           // Fetch stage
    Decode ID;          // Decode stage
    Execute EX;         // Excute stage
    MA ma;              // Memory access stage
    WB wb;              // Writeback stage
    Forwarding forward; // Data forward
    predict p;          // The branch predictor
    int cycles;         // Clock Cycles

  public:
    CPU(Memory *m) : regs(0, m), IF(&regs), ID(&regs, &p), EX(&regs, &p), ma(&regs), wb(&regs) {
        mem = m;
        cycles = 0;
    }
    void run() {
        mem->parse();
        while (true) {
            cycles++;
            wb.perform();
            ma.perform();
            //转发
            forward.MA_Forward_EX(ma, EX);
            EX.perform();
            if (!EX.judge())
                ID.back(); //跳转错误，重新取指令
            ID.perform();
            forward.MA_Forward_ID(ma, ID);
            IF.perform();
            if (IF.instruction.instr == 0x0ff00513) // Encounter li a0, 255 (means return)
                return;
            if (mem->full()) {
                fprintf(stderr, "The main memory is full\n");
                return;
            }
            ma.pass(wb);
            EX.pass(ma);
            ID.pass(EX);
            IF.pass(ID);
        }
    }
    void show_statistic_data() {
        uint result = ((regs.read(10)) & 255); // Read the result from a0
        fprintf(stdout, "Execution result:                             %d\n", result);
        fprintf(stdout, "Total executing time:                         %d(cycles)\n", cycles);
        fprintf(stdout, "Funtion call times:                           %d\n", ID.fun_call_num);
        fprintf(stdout, "Success branch prediction:                    %d\n", EX.p->success);
        fprintf(stdout, "Total branch cnnditions:                      %d\n", EX.p->total);
        fprintf(stdout, "Successful conditional prediction  rate:      %.2f\n",
                (EX.p->total != 0) ? (double)EX.p->success / EX.p->total : 0);
    }
    void parrael() {
        run();
        show_statistic_data();
    }
};

#endif
