#pragma once

#include <cstdint>
#include <string_view>

#include "Cpu.h"

struct OpcodeParams {
    [[nodiscard]] Reg8 SSS() const;
    [[nodiscard]] Reg8 DDD() const;
    [[nodiscard]] Reg16 RP() const;
    [[nodiscard]] uint8_t NNN() const;
    [[nodiscard]] JumpCondition CCC() const;

    uint8_t opcode;
};

struct OpcodeDefinition {
    std::string_view label;
    std::string_view bitPattern;
    void(*execute)(Cpu&, OpcodeParams);
};

struct Opcode {
    void Execute(Cpu& cpu) const;
    std::string disassemble(Cpu& cpu) const;

    OpcodeDefinition definition{};
    OpcodeParams params{};
};