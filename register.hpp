//
// Created by DELL on 2020/7/17.
//
#include "Memory.hpp"
#include "type.hpp"
#include <cstring>
#ifndef SERIAL_REGISTER_HPP
#define SERIAL_REGISTER_HPP
class Register {
private:
    uint data[32];
    uint pc;
    Memory *mem;

public:
    Register(uint p, Memory *m) {
        for (int i=0; i<32; ++i)
            //寄存器初始化为0
            data[i] = 0;
        pc =p;
        mem =m;
    }
    inline uint read(int index){
        if(index==0)return 0u;
        else return data[index];
    }
    inline void change(int index,uint x){
        //0位寄存器恒为常数0
        if(index==0) return;
        else data[index]=x;
    }
    inline void write_pc(uint _pc){
        pc=_pc;
    }
    inline uint get_pc() {
        return pc;
    }
    //从内存pos位置读取n(n<=4)个字节
    uint load(uint pos, int n) {
        uint res = 0,temp[4];
        for (int i=0;i<n;++i)
            temp[i] = static_cast<uint>(mem ->read(pos+i));
        for (int i=n-1; ~i; --i) {
            res<<=8;
            res+=temp[i];
        }
        return res;
    }
    //将x的低n位存入内存中index位置
    void store(uint index, uint x, int n) {
        uint temp[4];
        for (int i=0; i<4; ++i) {
            temp[i] = (x & 255);
            x >>= 8;
        }
        for (int i=0; i<n; ++i) {
            mem ->write(index, static_cast <uchar> (temp[i]));
            ++index;
        }
    }
    uint getinst() {
        //std::cout<<std::hex<<pc<<" ";
        uint res = load(pc, 4);
        pc += 4;
        return res;
    }
    inline void clear(){
        memset(data,32,sizeof(data));
        pc=0;
    }
};

#endif //SERIAL_REGISTER_HPP
