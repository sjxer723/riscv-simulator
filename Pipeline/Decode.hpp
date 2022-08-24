#include "../instruction.hpp"
#include "../prediction.hpp"
#include "../register.hpp"
#include "Execute.hpp"

#ifndef _DECODE_
#define _DECODE_

class Decode {
    friend class RISCV;

  private:
    Register *regist;
    predict *pre;

  public:
    ins instruction;
    int fun_call_num;
    bool notrun;
    Decode(Register *r, predict *p) : regist(r), pre(p), notrun(false), fun_call_num(0) {}

    bool set() {
        switch (instruction.type) {
        //更改pc的指令
        case AUIPC:
            if (regist->usedpc)
                return false;
            instruction.src1 = regist->get_pc();
            break;
            //跳转指令
        case JAL:
            if (regist->usedpc)
                return false;
            instruction.res = regist->get_pc();
            fun_call_num++;
            break;
        case JALR:
            if (regist->usedpc)
                return false;
            instruction.src1 = regist->read(instruction.rs1);
            instruction.res = regist->get_pc();
            fun_call_num++;
            break;
        case BEQ:
        case BNE:
        case BLT:
        case BLTU:
        case BGE:
        case BGEU:
            if (regist->usedpc)
                return false;
            instruction.src1 = regist->read(instruction.rs1);
            instruction.src2 = regist->read(instruction.rs2);
            instruction.resultpc = regist->get_pc();
            instruction.pre = pre->prediction();
            break;
        //无需更改pc的指令
        // R-I指令
        case ADDI:
        case SLTI:
        case SLTIU:
        case ANDI:
        case ORI:
        case XORI:
        case SLLI:
        case SRLI:
        case SRAI:
        case LB:
        case LH:
        case LW:
        case LBU:
        case LHU:
            instruction.src1 = regist->read(instruction.rs1);
            break;
        // R-R指令
        case SW:
        case SH:
        case SB:
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
            instruction.src1 = regist->read(instruction.rs1);
            instruction.src2 = regist->read(instruction.rs2);
            break;
        default:
            break;
        }
        return true;
    }
    //加入分支预测
    void branchpredict() {
        if (instruction.type == BEQ || instruction.type == BNE || instruction.type == BGE || instruction.type == BLT ||
            instruction.type == BGEU || instruction.type == BLTU) {
            instruction.pre = pre->prediction();
            //若预测成功，在ID阶段就修改PC
            if (instruction.pre)
                regist->write_pc(instruction.resultpc - 4 + instruction.imm);
        }
    }
    void back() { instruction.instr = regist->getinst(); }
    //保护J型指令，暂停后续流水，防止pc在后续过程中被修改
    void lockit() {
        switch (instruction.type) {
        case JALR:
        case JAL:
            regist->usedpc++;
            break;
        default:
            break;
        }
    }
    void perform() {
        notrun = false;
        if (instruction.type == LOCK)
            return;
        instruction.Type();
        instruction.setarg();
        if (!set())
            notrun = true; //现在不可调用pc
        else {
            branchpredict();
            lockit();
        }
    }
    void pass(Execute &next) {
        next.instruction = instruction;
        if (notrun)
            next.instruction.type = LOCK;
    }
};
#endif
