#include <stdexcept>
#include <tuple>

#include "Opcodes.h"
#include "Format.h"

void Execute(Cpu& cpu, Opcode<INVALID> opcode) {
    int pc = cpu.GetRegister(Reg16::PC) - 1;
    throw std::runtime_error(
        Format("Invalid opcode 0x%02x at address 0x%04x", opcode.GetRaw(), pc)
    );
}

void Execute(Cpu& cpu, Opcode<MOV> opcode) {
    cpu.SetRegister(
        opcode.GetDDD(),
        cpu.GetRegister(opcode.GetSSS())
    );
}

void Execute(Cpu& cpu, Opcode<MVI> opcode) {
    cpu.SetRegister(
        opcode.GetDDD(),
        cpu.LoadDataByte()
    );
}

void Execute(Cpu& cpu, Opcode<LXI> opcode) {
    cpu.SetRegister(
        opcode.GetRP(),
        cpu.LoadDataWord()
    );
}

void Execute(Cpu& cpu, Opcode<LDA> opcode) {
    cpu.SetRegister(
        opcode.GetDDD(),
        cpu.ReadByte(cpu.LoadDataWord())
    );
}

void Execute(Cpu& cpu, Opcode<STA> opcode) {
    cpu.WriteByte(
        cpu.LoadDataWord(),
        cpu.GetRegister(Reg8::A)
    );
}

void Execute(Cpu& cpu, Opcode<LHLD> opcode) {
    cpu.SetRegister(
        Reg16::HL,
        cpu.ReadWord(cpu.LoadDataWord())
    );
}

void Execute(Cpu& cpu, Opcode<SHLD> opcode) {
    cpu.WriteWord(
        cpu.ReadWord(cpu.LoadDataWord()),
        cpu.GetRegister(Reg16::HL)
    );
}

void Execute(Cpu& cpu, Opcode<LDAX> opcode) {
    cpu.SetRegister(
        Reg8::A,
        cpu.ReadWord(cpu.GetRegister(opcode.GetSSS()))
    );
}

void Execute(Cpu& cpu, Opcode<NOP> opcode) {
    // No operation
}