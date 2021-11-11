#include "OpcodeTable.h"

int main(int argc, char* argv[]) {
    Cpu cpu{};

    cpu.SetRegister(Reg8::B, 42);
    cpu.Execute(0x78);

    return cpu.GetRegister(Reg8::A);
}