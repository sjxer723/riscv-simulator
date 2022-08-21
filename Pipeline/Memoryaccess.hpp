#include "../register.hpp"
#include "Writeback.hpp"

#ifndef _MEMORYACCESS_
#define _MEMORYACCESS_

class MA {
    friend class RISCV;

  private:
    Register *regist;

  public:
    ins instruction;

    MA(Register *r) : regist(r) {}

    void perform() {
        if (instruction.type == LOCK)
            return;
        switch (instruction.type) {
        case LW:
            instruction.res = regist->load(instruction.src1, 4);
            break;
        case LH:
            instruction.res = sext(regist->load(instruction.src1, 2), 15);
            break;
        case LHU:
            instruction.res = regist->load(instruction.src1, 2);
            break;
        case LB:
            instruction.res = sext(regist->load(instruction.src1, 1), 7);
            break;
        case LBU:
            instruction.res = regist->load(instruction.src1, 1);
            break;
        case SW:
            regist->store(instruction.src1, instruction.src2, 4);
            break;
        case SH:
            regist->store(instruction.src1, instruction.src2, 2);
            break;
        case SB:
            regist->store(instruction.src1, instruction.src2, 1);
            break;
        default:
            break;
        }
    }

    void pass(WB &nxt) { nxt.instruction = instruction; }
};

#endif
