cmake_minimum_required(VERSION 3.10)
project(Serial)

set(CMAKE_CXX_STANDARD 14)

add_executable(code main.cpp instruction.hpp type.hpp Memory.hpp register.hpp RISCV.hpp Pipeline/Fetch.hpp Pipeline/Decode.hpp Pipeline/Excute.hpp Pipeline/Memoryaccess.hpp Pipeline/Writeback.hpp)
