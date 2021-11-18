#include "Opcode.h"
#include "Format.h"

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
    definition.execute(cpu, params);
}

std::string Opcode::Disassemble(Cpu &cpu) const {
    std::string label{definition.label};

    uint8_t nextByte = cpu.FetchDataByte();
    uint16_t nextWord = uint16_t(cpu.FetchDataByte())<<8 | uint16_t(nextByte);

    Replace(label, "<OPCODE>", Format("0x%02X", params.opcode));
    Replace(label, "<A>", Format("$%04X", nextWord));
    Replace(label, "<DST>", FormatEnum(params.DDD()));
    Replace(label, "<SRC>", FormatEnum(params.SSS()));
    Replace(label, "<BYTE>", Format("<0x%02X>", nextByte));
    Replace(label, "<WORD>", Format("<0x%04X>", nextWord));
    Replace(label, "<ADDR>", Format("$%04X", nextWord));
    Replace(label, "<RP>", FormatEnum(params.RP()));
    Replace(label, "<FLAG>", FormatEnum(params.CCC()));

    return label;
}
