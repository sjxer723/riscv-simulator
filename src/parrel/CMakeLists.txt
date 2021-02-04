cmake_minimum_required(VERSION 3.10)
project(parrel)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -O3 -std=c++11 -g")

add_executable(code main.cpp Forward.hpp prediction.hpp instruction.hpp type.hpp Memory.hpp register.hpp RISCV.hpp Pipeline/Fetch.hpp Pipeline/Decode.hpp Pipeline/Excute.hpp Pipeline/Memoryaccess.hpp Pipeline/Writeback.hpp)
