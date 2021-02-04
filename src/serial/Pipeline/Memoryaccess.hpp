//
// Created by DELL on 2020/7/17.
//
#include "Writeback.hpp"
#include "../register.hpp"

#ifndef SERIAL_MEMORYACCESS_HPP
#define SERIAL_MEMORYACCESS_HPP


class MA {
    friend class RISCV;
private:
    Register *regist;
public:
    ins instruction;
    MA(Register *r):regist(r){}

    void perform() {
        switch(instruction.type) {
            case LW: instruction.res= regist-> load(instruction.src1, 4); break;
            case LH: instruction.res= sext(regist-> load(instruction.src1, 2), 15); break;
            case LHU: instruction.res= regist -> load(instruction.src1, 2); break;
            case LB: instruction.res= sext(regist-> load(instruction.src1, 1), 7); break;
            case LBU: instruction.res= regist-> load(instruction.src1, 1); break;
            case SW: regist-> store(instruction.src1,instruction.src2, 4); break;
            case SH: regist-> store(instruction.src1,instruction.src2, 2); break;
            case SB: regist-> store(instruction.src1,instruction.src2, 1); break;
            default: break;
        }
    }
    void pass(WB &nxt) {
        nxt.instruction= instruction;
    }
};
#endif //SERIAL_MEMORYACCESS_HPP
