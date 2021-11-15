#pragma once

#include <array>

#include "Opcodes.h"
#include "BitMask.h"
#include "Macros.h"

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
constexpr decltype(auto) ResolveOpcode() {
    RESOLVE_BEG
    RESOLVE("01DDDSSS", MOV)
    RESOLVE("00DDD110", MVI)
    RESOLVE("00RP0001", LXI)
    RESOLVE("00111010", LDA)
    RESOLVE("00110010", STA)
    RESOLVE("00101010", LHLD)
    RESOLVE("00100010", SHLD)
    RESOLVE("00RP1010", LDAX)
    RESOLVE("00XXX000", NOP)
    RESOLVE_END
}

template<uint8_t opcode>
constexpr OpcodeTable::OpcodeImpl CreateOpcodeEntry() {
    return [](Cpu& cpu) {
        Execute(cpu, ResolveOpcode<opcode>());
    };
}

template<uint8_t ... opcodes>
constexpr OpcodeTable CreateOpcodeTableImpl(std::integer_sequence<uint8_t, opcodes...>) {
    return OpcodeTable{CreateOpcodeEntry<opcodes>()...};
}

constexpr OpcodeTable CreateOpcodeTable() {
    return CreateOpcodeTableImpl(std::make_integer_sequence<uint8_t, 0xff>{});
}
