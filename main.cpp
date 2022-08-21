#include "Memory.hpp"
#include "cpu.hpp"
#include "register.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

Memory mem;
CPU simulator(&mem);

int main() {
    simulator.parrael();
    // std::cout<<"Success!"<<std::endl;
    return 0;
}
