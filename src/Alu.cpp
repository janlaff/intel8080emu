#include <bitset>

#include "Alu.h"

uint8_t Alu::Add(uint8_t left, uint8_t right) {
    auto result = uint16_t(left) + uint16_t(right);

    CheckSZPC(result);
    SetFlag(Flag::AuxCarry, ((left & 0xf) + (right & 0xf)) > 0xf);

    return result;
}

uint8_t Alu::Sub(uint8_t left, uint8_t right) {
    return Add(left, (~right) + 1);
}

uint8_t Alu::And(uint8_t left, uint8_t right) {
    auto result = left & right;
    CheckSZPC(result);
    return result;
}

uint8_t Alu::Or(uint8_t left, uint8_t right) {
    auto result = left | right;
    CheckSZPC(result);
    return result;
}

uint8_t Alu::Xor(uint8_t left, uint8_t right) {
    auto result = left ^ right;
    CheckSZPC(result);
    return result;
}

void Alu::Cmp(uint8_t left, uint8_t right) {
    auto result = left - right;
    CheckSZPC(result);

    if (right & 0x8000)
        SetFlag(Flag::Carry, !GetFlag(Flag::Carry));
}

bool Alu::GetFlag(Flag which) const {
    auto flagBit = static_cast<uint8_t>(which);
    return (flags >> flagBit) & 1;
}

void Alu::SetFlag(Flag which, bool enabled) {
    auto flagBit = static_cast<uint8_t>(which);

    if (enabled) {
        flags |= 1 << flagBit;
    } else {
        flags &= ~(1 << flagBit);
    }
}

void Alu::CheckSZPC(uint16_t value) {
    SetFlag(Flag::Sign, value & 0x8000);
    SetFlag(Flag::Zero, value == 0);
    SetFlag(Flag::Parity, (std::bitset<8>(value).count() % 2) == 0);
    SetFlag(Flag::Carry, value > 0xff);
}