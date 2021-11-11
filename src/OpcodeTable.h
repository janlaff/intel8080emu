#pragma once

#include <array>

#include "Opcodes.h"
#include "BitMask.h"
#include "ResolveMacros.h"

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
    Reg8 src = ParseSourceReg(opcode);
    Reg8 dst = ParseDestinationReg(opcode);
    Reg16 dst16 = ParseRegPair(opcode);

    RESOLVE_BEGIN
    RESOLVE_ENTRY("01DDDSSS") MovOpcode{dst, src};
    RESOLVE_ENTRY("00DDD110") MviOpcode{dst};
    RESOLVE_ENTRY("00RP0001") LxiOpcode{dst16};
    RESOLVE_ENTRY("00111010") LdaOpcode{};
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
