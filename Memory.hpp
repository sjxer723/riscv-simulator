#ifndef _MEMORY_
#define _MEMORY_

#include "type.hpp"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#define MAXN 0x3ffffff

class Memory {
  private:
	uchar mem[MAXN];
    bool is_full;

  public:
    Memory() {
        memset(mem, 0, sizeof mem);
        is_full = false;
    }
    uchar &operator[](uint index) { return mem[index]; }
    void write(uint add, uchar x) {
        mem[add] = x;
        if (add == 0x30004)
            is_full = true;
    }
    uchar read(uint adr) { return mem[adr]; }
    void parse() {
        char temp[16];
        memset(temp, 0, sizeof(temp));
        int adr = 0;
        while (std::cin >> temp) {
            if (temp[0] == '#')
                break;
            if (temp[0] == '@') {
                adr = fetch(temp + 1);
                // std::cout<<"success @"<<std::endl;
            } else {
                mem[adr] = static_cast<uchar>(fetch(temp));
                adr++;
                // std::cout<<"success mem"<<std::endl;
            }
            memset(temp, 0, sizeof(temp));
        }
    }
    bool full() const {
        if (is_full)
            return true;
        else
            return false;
    }
    void debug() {
        for (int i = 0; i < MAXN; i++) {
            if (mem[i])
                printf("%d %d", i, (uint)mem[i]);
        }
    }
};

#endif