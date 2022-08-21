#include "Memory.hpp"
#include "RISCV.hpp"
#include "register.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

Memory mem;
RISCV simulator(&mem);

int main() {
    simulator.parrael();
    // std::cout<<"Success!"<<std::endl;
    return 0;
}
