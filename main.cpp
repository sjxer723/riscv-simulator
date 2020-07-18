# include <iostream>
# include <stdio.h>
# include <string.h>
# include "register.hpp"
# include "Memory.hpp"
# include "RISCV.hpp"

using namespace std;

Memory mem;
RISCV simulator(&mem);

int main() {
    simulator.serial();
    //std::cout<<"Success!"<<std::endl;
    return 0;;
}
