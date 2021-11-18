#include <iostream>

#include "Cpu.h"
#include "Opcode.h"
#include "Format.h"

void printFlags(const Cpu& cpu) {
    auto flags = Format(
        "\t< S:%02d | Z:%02d | A:%02d | P:%02d | C:%02d >",
        cpu.GetFlag(Flag::Sign),
        cpu.GetFlag(Flag::Zero),
        cpu.GetFlag(Flag::AuxCarry),
        cpu.GetFlag(Flag::Parity),
        cpu.GetFlag(Flag::Carry)
    );

    std::cout << flags << std::endl;
}

void printRegs(const Cpu& cpu) {
    auto regs = Format(
        "\t< A:%02x | B:%02x | C:%02x | D:%02x | E:%02x | H:%02x | L:%02x >",
        cpu.GetRegister(Reg8::A),
        cpu.GetRegister(Reg8::B),
        cpu.GetRegister(Reg8::C),
        cpu.GetRegister(Reg8::D),
        cpu.GetRegister(Reg8::E),
        cpu.GetRegister(Reg8::H),
        cpu.GetRegister(Reg8::L)
    );

    std::cout << regs << std::endl;
}

int main(int argc, char* argv[]) {
    Cpu cpu{};
    cpu.LoadRom("roms/cpudiag.bin");

    while (true) {
        printRegs(cpu);
        printFlags(cpu);

        auto address = cpu.GetRegister(Reg16::PC);
        auto opcode = cpu.FetchNext();

        std::cout << Format("%04x: %s", address, cpu.Disassemble(opcode)) << std::endl;

        cpu.Execute(opcode);
    }

    return 0;
}