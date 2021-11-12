#include <stdexcept>
#include <sstream>

#include "Opcodes.h"

void Execute(Cpu& cpu, InvalidOpcode opcode) {
    std::ostringstream ss;
    ss << "Invalid opcode: ";
    ss << std::hex << int(opcode.byte);
    throw std::runtime_error(ss.str());
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