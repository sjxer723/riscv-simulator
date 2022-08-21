#include "../instruction.hpp"
#include "../prediction.hpp"
#include "../register.hpp"
#include "Memoryaccess.hpp"

#ifndef _EXCUTE_
#define _EXCUTE_

class Excute {
    friend class RISCV;

  private:
    Register *regist;
    predict *p;

  public:
    ins instruction;

    Excute(Register *r, predict *pre) : regist(r), p(pre) {}

    void perform() {
        switch (instruction.type) {
            // U-Type
        case LUI:
            instruction.res = instruction.imm;
            break;
        case AUIPC:
            instruction.res = instruction.src1 - 4 + instruction.imm;
            break;
            // J-Type
        case JAL:
            instruction.resultpc = instruction.res + instruction.imm;
            break;
        case JALR: {
            instruction.resultpc = instruction.src1 + instruction.imm;
            instruction.resultpc = last_zero(instruction.resultpc);
            break;
        }
            // B-Type
        case BEQ:
            instruction.res =
                static_cast<uint>(instruction.src1 == instruction.src2);
            break;
        case BNE:
            instruction.res =
                static_cast<uint>(instruction.src1 != instruction.src2);
            break;
        case BLTU:
            instruction.res =
                static_cast<uint>(instruction.src1 < instruction.src2);
            break;
        case BGEU:
            instruction.res =
                static_cast<uint>(instruction.src1 >= instruction.src2);
            break;
        case BLT:
            instruction.res = static_cast<uint>((int)instruction.src1 <
                                                (int)instruction.src2);
            break;
        case BGE:
            instruction.res = static_cast<uint>((int)instruction.src1 >=
                                                (int)instruction.src2);
            break;
            // I-Type
        case LB:
        case LW:
        case LH:
        case LHU:
        case LBU:
            instruction.src1 = instruction.src1 + sext(instruction.imm, 11);
            break;
        case ADDI:
            instruction.res = instruction.src1 + instruction.imm;
            break;
        case SLTI:
            instruction.res =
                static_cast<uint>((int)instruction.src1 < (int)instruction.imm);
            break;
        case SLTIU:
            instruction.res =
                static_cast<uint>(instruction.src1 < instruction.imm);
            break;
        case ANDI:
            instruction.res = (instruction.src1 & instruction.imm);
            break;
        case ORI:
            instruction.res = (instruction.src1 | instruction.imm);
            break;
        case XORI:
            instruction.res = (instruction.src1 ^ instruction.imm);
            break;
        case SLLI:
            instruction.res = (instruction.src1 << instruction.imm);
            break;
        case SRLI:
            instruction.res = (instruction.src1 >> instruction.imm);
            break;
        case SRAI:
            instruction.res = ((instruction.src1 >> instruction.imm) |
                               (instruction.src1 >> 31 << 31));
            break;
            // S-Type
        case SB:
        case SW:
        case SH:
            instruction.src1 = instruction.src1 + sext(instruction.imm, 11);
            break;
            // R-Type
        case ADD:
            instruction.res = instruction.src1 + instruction.src2;
            break;
        case SUB:
            instruction.res = instruction.src1 - instruction.src2;
            break;
        case SLL:
            instruction.res = (instruction.src1 << instruction.src2);
            break;
        case SRL:
            instruction.res = (instruction.src1 >> instruction.src2);
            break;
        case SRA:
            instruction.res = ((instruction.src1 >> instruction.src2) |
                               (instruction.src1 >> 31 << 31));
            break;
        case SLT:
            instruction.res = static_cast<uint>((int)instruction.src1 <
                                                (int)instruction.src2);
            break;
        case SLTU:
            instruction.res =
                static_cast<uint>(instruction.src1 < instruction.src2);
            break;
        case XOR:
            instruction.res = (instruction.src1 ^ instruction.src2);
            break;
        case OR:
            instruction.res = (instruction.src1 | instruction.src2);
            break;
        case AND:
            instruction.res = (instruction.src1 & instruction.src2);
            break;
        default:
            break;
        }
    }
    bool judge() {
        if (instruction.type == BEQ || instruction.type == BNE ||
            instruction.type == BLT || instruction.type == BGE ||
            instruction.type == BLTU || instruction.type == BGEU) {
            if (instruction.pre != instruction.res) { //预测错误
                //记录本次预测结果
                p->record(instruction.type, instruction.res, false);
                if (instruction.pre == false) {
                    //应该要跳转，结果没有发生跳转
                    regist->write_pc(instruction.resultpc - 4 +
                                     instruction.imm);
                } else {
                    //不应该跳转，结果跳转
                    regist->write_pc(instruction.resultpc);
                }
                return false;
            } else { //预测成功，记录预测结果
                p->record(instruction.type, instruction.res, true);
                return true;
            }
        }
        return true;
    }
    void pass(MA &next) { next.instruction = instruction; }
};

#endif
