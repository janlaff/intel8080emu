#include <stdexcept>

#include "Opcodes.h"

void Execute(Cpu& cpu, InvalidOpcode opcode) {
    throw std::runtime_error("Invalid opcode");
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
    cpu.SetRegister(Reg8::A, cpu.ReadMemory(cpu.LoadDataWord()));
}
