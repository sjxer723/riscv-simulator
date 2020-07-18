//
// Created by DELL on 2020/7/17.
//
#include"Excute.hpp"
#include"../register.hpp"
#include"../instruction.hpp"

#ifndef SERIAL_DECODE_HPP
#define SERIAL_DECODE_HPP

class Decode {
    friend class RISCV;
private:
    Register *regist;
public:
    ins instruction;

    Decode(Register *r):regist(r){}

    void perform() {
        instruction.Type();
        instruction.setarg();
        switch(instruction.type) {
            case AUIPC:
                instruction.src1=regist->get_pc();
                break;
            case JAL:
                instruction.res=regist->get_pc();
                break;
            case JALR:
                instruction.src1=regist->read(instruction.rs1);
                instruction.res=regist->get_pc();
                break;
            case BEQ:case BNE:case BLT:case BLTU:case BGE:case BGEU:
                instruction.src1=regist->read(instruction.rs1);
                instruction.src2=regist->read(instruction.rs2);
                instruction.resultpc=regist->get_pc();
                break;
            case LB:case LH:case LW:case LBU:case LHU:
                instruction.src1=regist->read(instruction.rs1);
                break;
            case SW:case SH:case SB:
                instruction.src1=regist->read(instruction.rs1);
                instruction.src2=regist->read(instruction.rs2);
                break;
            case ADDI:case SLTI:case SLTIU:case ANDI:case ORI:case XORI:
                instruction.src1=regist->read(instruction.rs1);
                break;
            case SLLI:case SRLI:case SRAI:
                instruction.src1=regist->read(instruction.rs1);
                break;
            case ADD:case SUB:case SLL:case SLT:case SLTU:
            case XOR:case SRL:case SRA:case OR:case AND:
                instruction.src1=regist->read(instruction.rs1);
                instruction.src2=regist->read(instruction.rs2);
                break;
            default: break;
        }
    }
    void pass(Excute &next) {
        next.instruction= instruction;
    }
};
#endif //SERIAL_DECODE_HPP
