#include <stdexcept>

#include "Opcodes.h"
#include "Format.h"

void Execute(Cpu& cpu, InvalidOpcode opcode) {
    int pc = cpu.GetRegister(Reg16::PC) - 1;
    throw std::runtime_error(
        Format("Invalid opcode %02x at address %04x", opcode.byte, pc)
    );
}

void Execute(Cpu& cpu, MovOpcode opcode) {
    cpu.SetRegister(opcode.dstReg, cpu.GetRegister(opcode.srcReg));
}

void Execute(Cpu& cpu, MviOpcode opcode) {
    cpu.SetRegister(opcode.dstReg, cpu.LoadDataByte());
}

void Execute(Cpu& cpu, LxiOpcode opcode) {
    cpu.SetRegister(opcode.dstReg, cpu.LoadDataWord());
}

void Execute(Cpu& cpu, LdaOpcode opcode) {
    cpu.SetRegister(Reg8::A, cpu.ReadByte(cpu.LoadDataWord()));
}

void Execute(Cpu& cpu, StaOpcode opcode) {
    cpu.WriteByte(cpu.LoadDataWord(), cpu.GetRegister(Reg8::A));
}

void Execute(Cpu& cpu, LhldOpcode opcode) {
    cpu.SetRegister(Reg16::HL, cpu.ReadWord(cpu.LoadDataWord()));
}

void Execute(Cpu& cpu, ShldOpcode opcode) {
    cpu.WriteWord(cpu.ReadWord(cpu.LoadDataWord()), cpu.GetRegister(Reg16::HL));
}

void Execute(Cpu& cpu, LdaxOpcode opcode) {
    cpu.SetRegister(Reg8::A, cpu.ReadWord(cpu.GetRegister(opcode.srcReg)));
}