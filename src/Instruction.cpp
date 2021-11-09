#include <stdexcept>

#include "Instruction.h"

void UnimplementedInstruction::ExecuteOn(Cpu &cpu) {
    throw std::runtime_error{"Unimplemented instruction"};
}

void MovInstruction::ExecuteOn(Cpu &cpu) {
    cpu.SetRegister(dst, cpu.GetRegister(src));
}