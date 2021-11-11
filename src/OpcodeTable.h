#pragma once

#include <array>
#include <string_view>
#include <functional>

#include "Opcodes.h"

constexpr bool BitMaskMatch(std::string_view bitMask, uint8_t opcode) {
    for (int i = 0; i < 8; ++i) {
        bool currentBitIsSet = opcode & (1 << (7 - i));

        if (bitMask[i] == '1' && !currentBitIsSet)
            return false;

        if (bitMask[i] == '0' && currentBitIsSet)
            return false;

        // Other values for bitMask[i] are being used as placeholders
    }

    return true;
}

template<uint8_t opcode>
constexpr decltype(auto) ResolveOpcode() {
    Reg8 src = ParseSourceReg(opcode);
    Reg8 dst = ParseDestinationReg(opcode);
    Reg16 dst16 = ParseRegPair(opcode);

    if constexpr (BitMaskMatch("01DDDSSS", opcode))
        return MovOpcode{src, dst};
    else if constexpr (BitMaskMatch("00DDD110", opcode))
        return MviOpcode{dst};
    else if constexpr (BitMaskMatch("00RP0001", opcode))
        return LxiOpcode{dst16};
    else if constexpr (BitMaskMatch("00111010", opcode))
        return LdaOpcode{};
    else
        return InvalidOpcode{};
}

template<uint8_t opcode>
constexpr auto CreateOpcodeTableEntry() {
    return [](Cpu& cpu) {
        Execute(cpu, ResolveOpcode<opcode>());
    };
}

struct OpcodeTable {
    using ExecuteFn = void(*)(Cpu&);

    constexpr OpcodeTable(std::initializer_list<ExecuteFn> instructions) {
        std::copy(instructions.begin(), instructions.end(), &data[0]);
    }

    constexpr ExecuteFn operator[](size_t index) const {
        return data[index];
    }

    std::array<ExecuteFn, 0xff> data;
};

template<uint8_t ... opcodes>
constexpr OpcodeTable CreateOpcodeTableImpl(std::integer_sequence<uint8_t, opcodes...>) {
    return OpcodeTable{CreateOpcodeTableEntry<opcodes>()...};
}

constexpr OpcodeTable CreateOpcodeTable() {
    return CreateOpcodeTableImpl(std::make_integer_sequence<uint8_t, 0xff>{});
}