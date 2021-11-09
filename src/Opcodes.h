#pragma once

#include <cstdint>
#include <cstddef>

#include "Cpu.h"

struct InvalidOpcode {};

struct MovOpcode {
    Reg8 srcReg;
    Reg8 dstReg;
};

struct MviOpcode {
    Reg8 dstReg;
};

void Execute(Cpu& cpu, InvalidOpcode opcode);
void Execute(Cpu& cpu, MovOpcode opcode);
void Execute(Cpu& cpu, MviOpcode opcode);