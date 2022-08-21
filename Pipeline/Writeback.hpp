#ifndef _WRITEBACK_
#define _WRITEBACK_

#include "../Memory.hpp"
#include "../instruction.hpp"
#include "../register.hpp"
#include "../type.hpp"
#include <iostream>

class WB {
    friend class RISCV;

  private:
    Register *regist;

  public:
    ins instruction;
    WB(Register *r) : regist(r) {}

    void dellock() {
        switch (instruction.type) {
        case JALR:
        case JAL:
            regist->usedpc--;
            break;
        default:
            break;
        }
    }
    void perform() {
        switch (instruction.type) {
        case JAL: {
            //将pc+4写入目标寄存器中
            regist->change(instruction.rd, instruction.res);
            regist->write_pc(instruction.resultpc - 4);
            break;
        }
        case JALR: {
            regist->change(instruction.rd, instruction.res);
            regist->write_pc(instruction.resultpc);
            break;
        }
        case LUI:
        case AUIPC:
        case LB:
        case LW:
        case LH:
        case LBU:
        case LHU:
        case ADDI:
        case SLTI:
        case SLTIU:
        case ANDI:
        case ORI:
        case XORI:
        case SLLI:
        case SRLI:
        case SRAI:
        case ADD:
        case SUB:
        case SLL:
        case SLT:
        case SLTU:
        case XOR:
        case SRL:
        case SRA:
        case OR:
        case AND:
            regist->change(instruction.rd, instruction.res);
            break;
        default:
            break;
        }
        dellock();
    }
};
#endif
