#include "Memory.hpp"
#include "type.hpp"

#ifndef _REGISTER_
#define _REGISTER_

class Register {
  private:
    uint data[32];
    uint pc;
    Memory *mem;

  public:
    int usedpc;
    int used[32];

    Register(uint p, Memory *m) {
        for (int i = 0; i < 32; ++i) {
            //寄存器初始化为0
            data[i] = 0;
            used[i] = 0;
        }
        pc = p;
        mem = m;
    }
    uint read(int index) {
        if (index == 0)
            return 0u;
        else
            return data[index];
    }
    void write_pc(uint _pc) { pc = _pc; }

    void change(int index, uint x) {
        // 0位寄存器恒为常数0
        if (index == 0)
            return;
        else
            data[index] = x;
    }

    uint get_pc() { return pc; }
    //从内存pos位置读取n(n<=4)个字节
    uint load(uint pos, int n) {
        uint res = 0, temp[4];
        for (int i = 0; i < n; ++i)
            temp[i] = static_cast<uint>(mem->read(pos + i));
        for (int i = n - 1; ~i; --i) {
            res <<= 8;
            res += temp[i];
        }
        return res;
    }

    //将x的低n位存入内存中index位置
    void store(uint index, uint x, int n) {
        uint temp[4];
        for (int i = 0; i < 4; ++i) {
            temp[i] = (x & 255);
            x >>= 8;
        }
        for (int i = 0; i < n; ++i) {
            mem->write(index, static_cast<uchar>(temp[i]));
            ++index;
        }
    }

    uint getinst() {
        // std::cout<<std::hex<<pc<<std::endl;
        uint res = load(pc, 4);
        pc += 4;
        return res;
    }
    bool empty() {
        if (usedpc)
            return false;
        for (int i = 0; i < 32; i++)
            if (used[i])
                return false;
        return true;
    }
};

#endif
