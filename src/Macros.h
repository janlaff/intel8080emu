#pragma once

// Syntactic sugar for the table definition in OpcodeTable.h/ResolveOpcode()
#define RESOLVE_BEG if constexpr (false) return InvalidOpcode{};
#define RESOLVE(bitmask) else if constexpr (BitMaskMatch(bitmask, opcode)) return
#define RESOLVE_END else return InvalidOpcode{opcode};

// Syntactic sugar for the opcode implementations
#define DEFINE_OPCODE(name, params) struct name ## Opcode { params; }; void Execute(Cpu& cpu, name ## Opcode opcode);