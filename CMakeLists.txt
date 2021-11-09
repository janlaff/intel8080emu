cmake_minimum_required(VERSION 3.20)
project(intel8080emu)

set(CMAKE_CXX_STANDARD 23)

add_executable(intel8080emu src/main.cpp src/Instruction.cpp src/Cpu.cpp)
