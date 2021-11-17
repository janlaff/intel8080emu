#pragma once

#include <cstdint>
#include <string_view>

#include "Cpu.h"

struct OpcodeParams {
    Reg8 SSS() const;
    Reg8 DDD() const;
    Reg16 RP() const;
    uint8_t NNN() const;
    JumpCondition CCC() const;

    uint8_t opcode;
};

struct OpcodeDecl {
    std::string_view name;
    std::string_view bitPattern;
    void(*impl)(Cpu&, OpcodeParams);
};

struct Opcode {
    void Execute(Cpu& cpu) const;

    OpcodeDecl decl;
    OpcodeParams params;
};