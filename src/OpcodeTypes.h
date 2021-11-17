#pragma once

#include <cstdint>
#include <string_view>

#include "Cpu.h"

struct OpcodeParams {
    Reg8 SSS();
    Reg8 DDD();
    Reg16 RP();
    uint8_t NNN();
    JumpCondition CCC();

    uint8_t opcode;
};

struct OpcodeDecl {
    std::string_view name;
    std::string_view bitPattern;
    void(*impl)(Cpu&, OpcodeParams);
};

struct Opcode {
    OpcodeDecl decl;
    OpcodeParams params;
};