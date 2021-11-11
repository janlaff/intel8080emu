#pragma once

#include "OpcodeParsing.h"

class Cpu {
public:
    uint8_t GetRegister(Reg8 reg);
    uint16_t GetRegister(Reg16 reg);

    void SetRegister(Reg8 reg, uint8_t value);
    void SetRegister(Reg16 reg, uint16_t value);

    uint8_t LoadDataByte();
    uint16_t LoadDataWord();

    void WriteMemory(uint16_t address, uint8_t value);
    uint8_t ReadMemory(uint16_t address);

    void Execute(uint8_t opcode);

private:
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
    uint8_t memory[0xFFFF];
};