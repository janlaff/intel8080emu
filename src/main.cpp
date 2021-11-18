#include <iostream>

#include "Cpu.h"
#include "Opcode.h"
#include "Format.h"

int main(int argc, char* argv[]) {
    Cpu cpu{};
    cpu.LoadRom("roms/cpudiag.bin");

    while (true) {
        auto address = cpu.GetRegister(Reg16::PC);
        auto opcode = cpu.FetchNext();
        
        std::cout << Format("$%04X: %s", address, cpu.Disassemble(opcode)) << std::endl;

        cpu.Execute(opcode);
    }

    return 0;
}