//
// Created by DELL on 2020/7/17.
//

#ifndef SERIAL_EXCUTE_HPP
#define SERIAL_EXCUTE_HPP
# include "Memoryaccess.hpp"
# include "../register.hpp"
#include"../instruction.hpp"

class Excute{
    friend class RISCV;
private:
    Register *regist;
public:
    ins instruction;
    Excute(Register *r):regist(r){}

    void perform() {
        switch(instruction.type) {
             //U-Type
            case LUI:
                instruction.res=instruction.imm;break;
            case AUIPC:
                instruction.res=instruction.src1-4+instruction.imm; break;
            //J-Type    
            case JAL:
                instruction.resultpc=instruction.res+instruction.imm;break;
            case JALR:
                instruction.resultpc=instruction.src1+instruction.imm;
                instruction.resultpc=last_zero(instruction.resultpc);
                break;
            //B-Type    
            case BEQ:
                instruction.res=static_cast<uint>(instruction.src1==instruction.src2); break;
            case BNE:
                instruction.res=static_cast<uint>(instruction.src1!=instruction.src2); break;
            case BLTU:
                instruction.res=static_cast<uint>(instruction.src1<instruction.src2); break;
            case BGEU:
                instruction.res=static_cast<uint>(instruction.src1>=instruction.src2); break;
            case BLT:
                instruction.res=static_cast<uint>((int)instruction.src1<(int)instruction.src2); break;
            case BGE:
                instruction.res=static_cast<uint>((int)instruction.src1>=(int)instruction.src2); break;
            //S-Type
            case SB:case SW:case SH:
                instruction.src1=instruction.src1+sext(instruction.imm,11); break;
            //I-type    
            case LB:case LW:case LH:case LHU:case LBU:
                instruction.src1=instruction.src1+sext(instruction.imm,11); break;
            case ADDI:
                instruction.res=instruction.src1+instruction.imm; break;
            case SLTI:
                instruction.res=static_cast<uint>((int)instruction.src1<(int)instruction.imm); break;
            case SLTIU:
                instruction.res=static_cast<uint>(instruction.src1<instruction.imm); break;
            case ANDI:
                instruction.res=(instruction.src1&instruction.imm); break;
            case ORI:instruction.res=(instruction.src1|instruction.imm); break;
            case XORI:
                instruction.res=(instruction.src1^instruction.imm); break;
            case SLLI:
                instruction.res=(instruction.src1<<instruction.imm); break;
            case SRLI:
                instruction.res=(instruction.src1>>instruction.imm); break;
            case SRAI:
                instruction.res=((instruction.src1>>instruction.imm)|(instruction.src1>>31<<31)); break;
            //R-Type
            case ADD:
                instruction.res=instruction.src1+instruction.src2; break;
            case SUB:
                instruction.res=instruction.src1-instruction.src2; break;
            case SLL:
                instruction.res=(instruction.src1<<instruction.src2); break;
            case SRL:
                instruction.res=(instruction.src1>>instruction.src2); break;
            case SRA:
                instruction.res=((instruction.src1>>instruction.src2)|(instruction.src1>>31<<31)); break;
            case SLT:
                instruction.res=static_cast<uint>((int)instruction.src1 < (int)instruction.src2); break;
            case SLTU:
                instruction.res=static_cast <uint>(instruction.src1<instruction.src2); break;
            case XOR:
                instruction.res=(instruction.src1^instruction.src2); break;
            case OR:
                instruction.res=(instruction.src1|instruction.src2); break;
            case AND:
                instruction.res=(instruction.src1&instruction.src2); break;
            default: break;
        }
    }

    void pass(MA &next) {
        next.instruction= instruction;
    }
};
#endif //SERIAL_EXCUTE_HPP
