#include "OpcodeTypes.h"

Reg8 OpcodeParams::SSS() {
    return static_cast<Reg8>(opcode & 0b00000111);
}

Reg8 OpcodeParams::DDD() {
    return static_cast<Reg8>((opcode & 0b00111000) >> 3);
}

Reg16 OpcodeParams::RP() {
    return static_cast<Reg16>((opcode & 0b00110000) >> 4);
}

uint8_t OpcodeParams::NNN() {
    return (opcode & 0b00111000) >> 3;
}

JumpCondition OpcodeParams::CCC() {
    return static_cast<JumpCondition>((opcode & 0b00111000) >> 3);
}