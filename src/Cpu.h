#pragma once

#include <string>
#include <array>
#include <vector>

#include "EnumTypes.h"
#include "Alu.h"
#include "Bus.h"

struct Opcode;

class Cpu : public Bus, public Alu {
public:
    uint8_t GetRegister(Reg8 which) const;
    uint16_t GetRegister(Reg16 which) const;

    void SetRegister(Reg8 which, uint8_t value);
    void SetRegister(Reg16 which, uint16_t value);

    void Push(uint16_t value);
    uint16_t Pop();

    uint8_t FetchDataByte();
    uint16_t FetchDataWord();

    const Opcode& FetchNext();
    void Execute(const Opcode& opcode);
    std::string Disassemble(const Opcode& opcode);

    void LoadRom(const std::string& filename);
    void LoadRom(const std::vector<uint8_t> rom);

    bool JumpConditionMet(JumpCondition condition);

private:
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
};