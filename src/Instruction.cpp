#include <stdexcept>

#include "Instruction.h"

void Execute(Cpu& cpu, InvalidOpcode opcode) {
    throw std::runtime_error("Invalid opcode");
}

void Execute(Cpu& cpu, MovOpcode opcode) {
    cpu.SetRegister(opcode.dstReg, cpu.GetRegister(opcode.srcReg));
}

void Execute(Cpu& cpu, MviOpcode opcode) {
    // TODO
}