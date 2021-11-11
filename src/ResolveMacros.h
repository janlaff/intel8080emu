#pragma once

// Syntactic sugar for the table definition in OpcodeTable.h/ResolveOpcode()
#define RESOLVE_BEGIN if constexpr (false) return InvalidOpcode{};
#define RESOLVE_ENTRY(bitmask) else if constexpr (BitMaskMatch(bitmask, opcode)) return
#define RESOLVE_END else return InvalidOpcode{};