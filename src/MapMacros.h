#pragma once

// Syntactic sugar for the table definition in OpcodeTable.h/ResolveOpcode()
#define MAP_BEGIN if constexpr (false) return InvalidOpcode{};
#define MAP_ENTRY(bitmask) else if constexpr (BitMaskMatch(bitmask, opcode)) return
#define MAP_END else return InvalidOpcode{};