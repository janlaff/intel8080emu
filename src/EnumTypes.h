#pragma once

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

enum class Flag : uint8_t {
    Sign = 7,
    Zero = 6,
    AuxCarry = 4,
    Parity = 2,
    Carry = 0
};