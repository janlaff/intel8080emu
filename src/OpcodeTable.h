#pragma once

#include <array>

#include "BitMask.h"
#include "Opcodes.h"

template<uint8_t opcode>
constexpr Opcode ResolveOpcode() {
    for (auto& definition : opcodeDefinitions) {
        if (BitMaskMatch(definition.bitPattern, opcode)) {
            return {definition, {opcode}};
        }
    }

    // Should never happen since last entry of
    // opcodeDefinitions will match with every opcode
    throw std::logic_error("Failed to resolve opcode");
}

template<uint8_t ... opcodes>
constexpr OpcodeTable CreateOpcodeTableImpl(std::integer_sequence<uint8_t, opcodes...>) {
    return OpcodeTable{ResolveOpcode<opcodes>()...};
}

constexpr OpcodeTable CreateOpcodeTable() {
    return CreateOpcodeTableImpl(std::make_integer_sequence<uint8_t, 0xff>{});
}
