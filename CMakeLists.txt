cmake_minimum_required(VERSION 3.18.4)
project(intel8080emu)

set(CMAKE_CXX_STANDARD 20)

add_executable(intel8080emu src/main.cpp src/Cpu.cpp src/OpcodeTypes.cpp)
