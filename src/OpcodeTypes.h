#pragma once

#include <cstdint>
#include <cstddef>
#include <tuple>
#include <functional>
#include <iostream>

#include "Cpu.h"
#include "Format.h"

class Opcode {
public:
    constexpr explicit Opcode(uint8_t opcode)
            : opcode{opcode}
    {}

    Reg8 GetSSS() {
        return ParseSourceReg(opcode);
    }

    Reg8 GetDDD() {
        return ParseDestinationReg(opcode);
    }

    Reg16 GetRP() {
        return ParseDestinationReg16(opcode);
    }

    uint8_t GetNNN() {
        return ParseVectorNum(opcode);
    }

    JumpCondition GetCCC() {
        return ParseJumpCondition(opcode);
    }

    uint8_t GetRaw() {
        return opcode;
    }

private:
    uint8_t opcode;
};

struct OpcodeDecl {
    std::string_view name;
    std::string_view bitPattern;
    void(*executor)(Cpu&, Opcode);
};

struct OpcodeImpl {
    OpcodeDecl decl;
    uint8_t raw;

    void Execute(Cpu& cpu) {
        decl.executor(cpu, Opcode {raw});
    }
};