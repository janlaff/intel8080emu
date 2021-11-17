#pragma once

#include <array>

#include "BitMask.h"
#include "OpcodeDecls.h"

struct OpcodeTable {
    using OpcodeImpl = void(*)(Cpu&);

    constexpr OpcodeTable(std::initializer_list<OpcodeImpl> entries) {
        std::copy(entries.begin(), entries.end(), &data[0]);
    }

    constexpr OpcodeImpl operator[](size_t index) const {
        return data[index];
    }

    std::array<OpcodeImpl, 0xff> data;
};

template<uint8_t opcode>
constexpr Opcode ResolveOpcode() {
    for (auto& opcodeDecl : OPCODE_DECLS) {
        if (BitMaskMatch(opcodeDecl.bitPattern, opcode)) {
            return { opcodeDecl, {opcode} };
        }
    }

    // Should never happen since last entry of
    // OPCODE_DECLS will match with every opcode
    return { {}, {0x00} };
}

template<uint8_t opcode>
constexpr OpcodeTable::OpcodeImpl CreateOpcodeEntry() {
    return [](Cpu& cpu) {
        constexpr auto opcodeImpl = ResolveOpcode<opcode>();
        opcodeImpl.Execute(cpu);
    };
}

template<uint8_t ... opcodes>
constexpr OpcodeTable CreateOpcodeTableImpl(std::integer_sequence<uint8_t, opcodes...>) {
    return OpcodeTable{CreateOpcodeEntry<opcodes>()...};
}

constexpr OpcodeTable CreateOpcodeTable() {
    return CreateOpcodeTableImpl(std::make_integer_sequence<uint8_t, 0xff>{});
}
