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
    simulator.parrael();
    //std::cout<<"Success!"<<std::endl;
    return 0;;
}
