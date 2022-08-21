//
// Created by DELL on 2020/7/16.
//
#ifndef RISC_V_FORWARD_HPP
#define RISC_V_FORWARD_HPP
#include "Pipeline/Decode.hpp"
#include "Pipeline/Execute.hpp"
#include "Pipeline/Fetch.hpp"
#include "Pipeline/Memoryaccess.hpp"
#include "Pipeline/Writeback.hpp"
#include "instruction.hpp"
#include "type.hpp"

class Forwarding {
    friend class RISCV;

  public:
    // EXE阶段需要使用还未存入寄存器中的数据
    void MA_Forward_EX(MA &ma, Execute &EX) {
        switch (ma.instruction.type) {
        case LUI:
        case AUIPC:
        case LB:
        case LH:
        case LW:
        case LBU:
        case LHU:
        case SB:
        case SH:
        case SW:
        case ADDI:
        case SLTI:
        case SLTIU:
        case XORI:
        case ANDI:
        case ORI:
        case SLLI:
        case SRLI:
        case SRAI:
        case ADD:
        case SUB:
        case SLL:
        case SLTU:
        case XOR:
        case SRL:
        case SRA:
        case OR:
        case AND:
            if (ma.instruction.rd == EX.instruction.rs1 && ma.instruction.rd != 0) {
                // EXE阶段需要使用还未存入寄存器中的数据
                EX.instruction.src1 = ma.instruction.res;
            }
            if (ma.instruction.rd == EX.instruction.rs2 && ma.instruction.rd != 0) {
                EX.instruction.src2 = ma.instruction.res;
            }
            break;
        default:
            break;
        }
    }
    // ID阶段要读未存入寄存器的值
    void MA_Forward_ID(MA &ma, Decode &ID) {
        switch (ma.instruction.type) {
        case LUI:
        case AUIPC:
        case LB:
        case LW:
        case LH:
        case LBU:
        case LHU:
        case SB:
        case SH:
        case SW:
        case ADDI:
        case SLTI:
        case SLTIU:
        case XORI:
        case ANDI:
        case ORI:
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
            if (ma.instruction.rd == ID.instruction.rs1 && ma.instruction.rd != 0) {
                // ID阶段要读未存入寄存器的值
                ID.instruction.src1 = ma.instruction.res;
            }
            if (ma.instruction.rd == ID.instruction.rs2 && ma.instruction.rd != 0) {
                // ID阶段要读未存入寄存器的值
                ID.instruction.src2 = ma.instruction.res;
            }
            break;
        default:
            break;
        }
    }
};

#endif // RISC_V_FORWARD_HPP
