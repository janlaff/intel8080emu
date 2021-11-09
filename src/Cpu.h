#pragma once

#include "MemoryBus.h"

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

class Instruction;

class Cpu {
public:
    uint8_t GetRegister(Reg8 reg);
    uint16_t GetRegister(Reg16 reg);

    void SetRegister(Reg8 reg, uint8_t value);
    void SetRegister(Reg16 reg, uint16_t value);

    uint8_t LoadDataByte();

//private:
    uint8_t a;
    uint8_t flags;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    MemoryBus memBus;
};