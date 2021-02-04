#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cstring>
#include"type.hpp"
#include"Memory.hpp"
#include"register.hpp"
#include"Forward.hpp"
#include"Pipeline/Decode.hpp"
#include"Pipeline/Excute.hpp"
#include"Pipeline/Fetch.hpp"
#include"Pipeline/Memoryaccess.hpp"
#include"Pipeline/Writeback.hpp"

# ifndef _RISCV_HPP_
# define _RISCV_HPP_

class RISCV {
private:
            Memory *mem;
            Register reg;
            Fetch IF;
            Decode ID;
            Excute EX;
            MA ma;
            WB wb;
            Forwarding forward;
            predict p;

public:
        RISCV (Memory *m) : reg(0,m),IF(&reg),ID(&reg,&p),EX(&reg,&p),ma(&reg),wb(&reg){
                mem=m;
            }
        void run(){
            mem->parse();
            while(true){
                wb.perform();
                ma.perform();
                //转发
                forward.MA_Forward_EX(ma,EX);
                EX.perform();
                if(!EX.judge())ID.back(); //跳转错误，重新取指令
                ID.perform();
                forward.MA_Forward_ID(ma,ID);
                IF.perform();
                if (IF.instruction.instr==0x0ff00513||mem->full()) break;
                //下一批阶段到达时钟周期
                ma.pass(wb);  //1
                EX.pass(ma);  //2
                ID.pass(EX);  //3
                IF.pass(ID);  //4
            }
        }
        void parrael(){
            run();
            uint result=((reg.read(10))&255);
            std::cout/*<<"result="*/<<result<<std::endl;
            //reg.debug();
            //p.print();
        }
};

# endif

