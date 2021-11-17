#include "OpcodeTypes.h"

Reg8 OpcodeParams::SSS() const {
    return static_cast<Reg8>(opcode & 0b00000111);
}

Reg8 OpcodeParams::DDD() const {
    return static_cast<Reg8>((opcode & 0b00111000) >> 3);
}

Reg16 OpcodeParams::RP() const {
    return static_cast<Reg16>((opcode & 0b00110000) >> 4);
}

uint8_t OpcodeParams::NNN() const {
    return (opcode & 0b00111000) >> 3;
}

JumpCondition OpcodeParams::CCC() const {
    return static_cast<JumpCondition>((opcode & 0b00111000) >> 3);
}

void Opcode::Execute(Cpu &cpu) const {
    decl.impl(cpu, params);
}