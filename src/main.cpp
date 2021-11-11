#include "OpcodeTable.h"

int main(int argc, char* argv[]) {
    OpcodeTable opTable = CreateOpcodeTable();
    Cpu cpu{};
    cpu.b = 42;
    opTable[0x78](cpu);

    return cpu.a;
}