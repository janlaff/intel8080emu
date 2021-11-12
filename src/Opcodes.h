#pragma once

#include <cstdint>
#include <cstddef>

#include "Cpu.h"

struct InvalidOpcode { uint8_t byte; };
struct MovOpcode { Reg8 dstReg; Reg8 srcReg; };
struct MviOpcode { Reg8 dstReg; };
struct LxiOpcode { Reg16 dstReg; };
struct LdaOpcode {};
struct StaOpcode {};
struct LhldOpcode {};

void Execute(Cpu& cpu, InvalidOpcode opcode);
void Execute(Cpu& cpu, MovOpcode opcode);
void Execute(Cpu& cpu, MviOpcode opcode);
void Execute(Cpu& cpu, LxiOpcode opcode);
void Execute(Cpu& cpu, LdaOpcode opcode);
void Execute(Cpu& cpu, StaOpcode opcode);
void Execute(Cpu& cpu, LhldOpcode opcode);