#pragma once

#include <cstdint>
#include <string_view>

#include "Cpu.h"

class Instruction {
public:
    constexpr Instruction(std::string_view label, size_t numDataBytes, size_t numClockCycles)
        : label{label}
        , numDataBytes{numDataBytes}
        , numClockCycles{numClockCycles}
        {}

    virtual void ExecuteOn(Cpu& cpu) = 0;

private:
    std::string_view label;
    size_t numDataBytes;
    size_t numClockCycles;
};

class UnimplementedInstruction : public Instruction {
public:
    constexpr UnimplementedInstruction()
        : Instruction{"<unimplemented>", 0, 0}
        {}

    void ExecuteOn(Cpu& cpu) override;
};

class MovInstruction : public Instruction {
public:
    constexpr MovInstruction(Reg8 src, Reg8 dst)
        : Instruction{"MOV D,S", 0, 5}
        , src{src}
        , dst{dst}
        {}

    void ExecuteOn(Cpu& cpu) override;

    Reg8 src;
    Reg8 dst;
};