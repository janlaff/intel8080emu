#pragma once

// Syntactic sugar for the table definition in OpcodeTable.h/ResolveOpcode()
#define RESOLVE_BEG if constexpr (false) return Opcode<INVALID>{opcode};
#define RESOLVE(bitmask, name) else if constexpr (BitMaskMatch(bitmask, opcode)) return Opcode<name>{opcode};
#define RESOLVE_END else return Opcode<INVALID>{opcode};

// Syntactic sugar for the opcode implementations
#define DEFINE_OPCODE(name, params) struct name ## Opcode { params; }; void Execute(Cpu& cpu, name ## Opcode opcode);