//
// Created by DELL on 2020/7/17.
//

#ifndef SERIAL_FETCH_HPP
#define SERIAL_FETCH_HPP
#include "Decode.hpp"
#include "../register.hpp"
#include "../instruction.hpp"

class Fetch {
    friend class RISCV;
private:
    Register *regist;

public:
    ins instruction;

    Fetch(Register *r):regist(r){}

    void perform() {
        instruction.instr=regist->getinst();
        //std::cout<<instruction.instr<<std::endl;
    }

    void pass(Decode &next) {
        next.instruction=instruction;
    }
};
#endif //SERIAL_FETCH_HPP
