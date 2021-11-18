#pragma once

#include <string>
#include <array>
#include <vector>

#include "EnumTypes.h"

struct Opcode;

class Cpu {
public:
    [[nodiscard]] uint8_t GetRegister(Reg8 which) const;
    [[nodiscard]] uint16_t GetRegister(Reg16 which) const;
    [[nodiscard]] uint8_t ReadByte(uint16_t address) const;
    [[nodiscard]] uint16_t ReadWord(uint16_t address) const;
    [[nodiscard]] bool GetFlag(Flag which) const;

    void SetRegister(Reg8 which, uint8_t value);
    void SetRegister(Reg16 which, uint16_t value);
    void WriteByte(uint16_t address, uint8_t value);
    void WriteWord(uint16_t address, uint16_t value);
    void SetFlag(Flag which, bool enabled);

    uint8_t FetchDataByte();
    uint16_t FetchDataWord();

    const Opcode& FetchNext();
    void Execute(const Opcode& opcode);
    std::string Disassemble(const Opcode& opcode);

    void LoadRom(const std::string& filename);
    void LoadRom(const std::vector<uint8_t> rom);

    uint8_t AddByte(uint8_t left, uint8_t right);
    uint8_t SubByte(uint8_t left, uint8_t right);
    uint8_t AndByte(uint8_t left, uint8_t right);
    uint8_t OrByte(uint8_t left, uint8_t right);
    uint8_t XorByte(uint8_t left, uint8_t right);
    void CmpByte(uint8_t left, uint8_t right);

    bool JumpConditionMet(JumpCondition condition);

private:
    void CheckSZPC(uint16_t value);

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
    std::array<uint8_t, 0xffff> memory;
};