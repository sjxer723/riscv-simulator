//
// Created by DELL on 2020/7/17.
//

#ifndef SERIAL_MEMORY_HPP
#define SERIAL_MEMORY_HPP
#include<iostream>
#include<cstring>
#include<iomanip>
#include<string>
#include"type.hpp"

#define MAXN 0x000fffff

class Memory {
private:
    uchar mem[MAXN];
    bool is_full;

public:

    Memory() {
        memset(mem, 0, sizeof mem);
        is_full=false;
    }
    uchar &operator[](uint index){
        return mem[index];
    }
    inline void write(uint add, uchar x){
        mem[add]=x;
        if(add==0x30004) is_full=true;
    }
    inline uchar read(uint adr){
        return mem[adr];
    }
    void parse() {
        char temp[16];
        memset(temp, 0, sizeof(temp));
        int adr = 0;
        while (std::cin >> temp) {
            if (temp[0] == '@') {
                adr = fetch(temp + 1);
                //std::cout<<"success @"<<std::endl;
            } else {
                mem[adr] = static_cast<uchar>(fetch(temp));
                adr++;
                //std::cout<<"success mem"<<std::endl;
            }
            memset(temp, 0, sizeof(temp));
        }
    }
    bool full(){
        if(is_full) return true;
        else return false;
    }
    inline void clean(){
        memset(mem,MAXN,sizeof(mem));
    }
    void debug(){
        for(int i=0;i<MAXN;i++){
            if(mem[i])printf("%d %d",i,(uint)mem[i]);
        }
    }
};
#endif //SERIAL_MEMORY_HPP
