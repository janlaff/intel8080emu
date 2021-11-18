#include "Opcode.h"
#include "Format.h"

using namespace std;

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
    string label{definition.label};

    uint8_t nextByte = cpu.FetchDataByte();
    uint16_t nextWord = uint16_t(cpu.FetchDataByte())<<8 | uint16_t(nextByte);

    Replace(label, "<OPCODE>", Format("$%02x", params.opcode));
    Replace(label, "<DST>", FormatEnum(params.DDD()));
    Replace(label, "<SRC>", FormatEnum(params.SSS()));
    Replace(label, "<BYTE>", Format("$%02x", nextByte));
    Replace(label, "<WORD>", Format("$%04x", nextWord));
    Replace(label, "<ADDR>", Format("@%04x", nextWord));
    Replace(label, "<RP>", FormatEnum(params.RP()));
    Replace(label, "<FLAG>", FormatEnum(params.CCC()));

    return label;
}
