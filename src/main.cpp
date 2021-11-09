#include "InstructionTable.h"

int main(int argc, char* argv[]) {
    Cpu cpu{};
    cpu.b = 42;
    INSTRUCTIONS[0x78](cpu);

    return cpu.a;
}