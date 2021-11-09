#include "Cpu.h"
#include "Opcodes.h"

uint8_t Cpu::GetRegister(Reg8 reg) {
    if (reg == Reg8::B) {
        return b;
    }
}

uint16_t Cpu::GetRegister(Reg16 reg) {

}

void Cpu::SetRegister(Reg8 reg, uint8_t value) {
    if (reg == Reg8::A) {
        a = value;
    }
}

void Cpu::SetRegister(Reg16 reg, uint16_t value) {

}

uint8_t Cpu::LoadDataByte() {
    return memBus.Read(sp++);
}