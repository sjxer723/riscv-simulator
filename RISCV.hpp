//
// Created by DELL on 2020/7/17.
//

#ifndef SERIAL_RISCV_HPP
#define SERIAL_RISCV_HPP
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cstring>
#include"type.hpp"
#include"Memory.hpp"
#include"Register.hpp"
#include"Pipeline/Decode.hpp"
#include"Pipeline/Excute.hpp"
#include"Pipeline/Fetch.hpp"
#include"Pipeline/Memoryaccess.hpp"
#include"Pipeline/Writeback.hpp"

class RISCV {
private:
    Memory *mem;
    Register reg;
    Fetch IF;
    Decode ID;
    Excute EX;
    MA ma;
    WB wb;

    void run(){
        mem->parse();
        while(!mem->full()) {
            IF.perform();
            IF.pass(ID);
            ID.perform();
            ID.pass(EX);
            EX.perform();
            EX.pass(ma);
            ma.perform();
            ma.pass(wb);
            wb.perform();
        }
    }
public:
    RISCV (Memory *m) : reg(0,m),IF(&reg),ID(&reg),EX(&reg),ma(&reg),wb(&reg){
        mem=m;
    }
    void serial(){
        run();
        std::cout/*<<"result="*/<<((reg.read(11))&255u)<<std::endl;
        //for(int j=0;j<32;j++)std::cout<<(reg.read(j))<<' ';
    }
};
#endif //SERIAL_RISCV_HPP
