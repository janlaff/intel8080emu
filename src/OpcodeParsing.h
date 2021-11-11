#pragma once

#include <cstdint>

enum class Reg8 : uint8_t {
    B, C, D, E, H, L, M, A
};

enum class Reg16 : uint8_t {
    BC, DE, HL, SP, PC, PSW
};

enum class JumpCondition : uint8_t {
    NonZero,
    Zero,
    NoCarry,
    Carry,
    Odd,
    Even,
    Positive,
    Minus
};

constexpr Reg8 ParseDestinationReg(uint8_t opcode) {
    return static_cast<Reg8>((opcode & 0b00111000) >> 3);
}

constexpr Reg8 ParseSourceReg(uint8_t opcode) {
    return static_cast<Reg8>(opcode & 0b00000111);
}

constexpr Reg16 ParseDestinationReg16(uint8_t opcode) {
    return static_cast<Reg16>((opcode & 0b00110000) >> 4);
}

constexpr JumpCondition ParseJumpCondition(uint8_t opcode) {
    return static_cast<JumpCondition>((opcode & 0b00111000) >> 3);
}
