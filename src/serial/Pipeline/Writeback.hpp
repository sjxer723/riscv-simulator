//
// Created by DELL on 2020/7/17.
//

#include"../instruction.hpp"
#include"../type.hpp"
#include"../register.hpp"
#include"../Memory.hpp"
#include<iostream>
#ifndef SERIAL_WRITEBACK_HPP
#define SERIAL_WRITEBACK_HPP

class WB {
    friend class RISCV;
private:
    Register *regist;

public:
    ins instruction;
    WB(Register *r):regist(r){}

    void perform() {
        switch(instruction.type) {
            case JAL:{
                //将pc+4写入目标寄存器中
                regist->change(instruction.rd,instruction.res);
                regist->write_pc(instruction.resultpc-4);
                break;
            }
            case JALR:
                regist->change(instruction.rd,instruction.res);
                regist->write_pc(instruction.resultpc);
                break;
            case LUI:case AUIPC:
            case LB:case LW:case LH:case LBU:case LHU:
            case ADDI:case SLTI:case SLTIU:case ANDI:case ORI:
            case XORI:case SLLI:case SRLI:case SRAI:
            case ADD:case SUB:case SLL:case SLT:case SLTU:
            case XOR:case SRL:case SRA:case OR:case AND:
                regist->change(instruction.rd, instruction.res);
                break;
            case BEQ:case BNE:case BLT:case BGE:case BLTU:case BGEU:
                if(instruction.res) regist->write_pc(instruction.resultpc+instruction.imm-4);
                else regist->write_pc(instruction.resultpc);
                break;
            default: break;
        }
    }
};
#endif //SERIAL_WRITEBACK_HPP
