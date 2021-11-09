#include "InstructionTable.h"

int main(int argc, char* argv[]) {
    Cpu cpu{};
    INSTRUCTIONS[0x40](cpu);

    return 0;
}