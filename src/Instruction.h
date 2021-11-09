#pragma once

#include <cstdint>
#include <cstddef>

#include "Cpu.h"

struct Opcode {
    size_t numDataBytes;
    size_t numClockCycles;
};

struct InvalidOpcode : Opcode {};

struct MovOpcode : Opcode {
    Reg8 srcReg;
    Reg8 dstReg;
};

void Execute(Cpu& cpu, InvalidOpcode opcode);
void Execute(Cpu& cpu, MovOpcode opcode);