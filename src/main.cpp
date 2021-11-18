#include <iostream>

#include "Cpu.h"
#include "Opcode.h"
#include "Format.h"

int main(int argc, char* argv[]) {
    Cpu cpu{};
    cpu.LoadRom("roms/cpudiag.bin");

    for (int i = 0; i < 10; ++i) {
        auto opcode = cpu.FetchNext();

        auto address = cpu.GetRegister(Reg16::PC) - 1;
        std::cout << Format("$%04X: %s", address, cpu.Disassemble(opcode)) << std::endl;

        cpu.Execute(opcode);
    }

    return 0;
}