//
// Created by DELL on 2020/7/16.
//

#ifndef RISC_V_PREDICTION_HPP
#define RISC_V_PREDICTION_HPP

#include <cstring>
#include <iostream>
#include <vector>
#include "instruction.hpp"

int StateForward(int s, int jump_or_not)
{
    switch (s)
    {
    case 0: return jump_or_not?1:0;
    case 1: return jump_or_not?2:0;
    case 2: return jump_or_not?3:1;
    case 3: return jump_or_not?3:2;
    }
    return s;
}

class predict {  
  private:
    int TwoBitState;

  public:
    int success, total;
    predict() { TwoBitState = 0; success =0; total = 0;}
    int prediction() {
        return (TwoBitState>=2)?1:0;
    }
    void record(int type, int result, int success_or_not) {
        TwoBitState = StateForward(TwoBitState, result);
        if (success_or_not) ++success;
        ++total;
    }
    void debug() {
        std::cout << "success" << success << " "
                  << "total" << total << std::endl;
        std::cout << "rate=" << (double)success / total << std::endl;
    }
};
#endif
