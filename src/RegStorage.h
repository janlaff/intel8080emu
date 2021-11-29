#pragma once

#include <cstdint>
#include <cstddef>

enum Reg8 {
    A = 0,
    Flags = 1,
    B = 2,
    C = 3,
    D = 4,
    E = 5,
    H = 6,
    L = 7
};

enum Reg16 {
    PSW = 0,
    BC = 2,
    DE = 4,
    HL = 6,
    SP = 8,
    PC = 10
};

/*
 * | PSW | BC  | DE  | HL  | SP  | PC  |
 * | A,F | B,C | D,E | H,L | --- | --- |
 */

class RegStorage {
public:
    void SetReg(Reg8 reg, uint8_t value);
    void SetReg(Reg16 reg, uint16_t value);
    uint8_t GetReg(Reg8 reg);
    uint16_t GetReg(Reg16 reg);

private:
    uint8_t data[12];
};