cmake_minimum_required(VERSION 3.18.4)
project(intel8080emu)

set(CMAKE_CXX_STANDARD 20)

set(
    SOURCE_FILES
    src/main.cpp
    src/Cpu.cpp
    src/Opcode.cpp
    src/Format.cpp
    src/Shell.cpp
    src/Alu.cpp
    src/Bus.cpp
    src/Bytes.cpp
)

add_executable(intel8080emu ${SOURCE_FILES})
