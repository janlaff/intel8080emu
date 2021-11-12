#include "OpcodeTable.h"

int main(int argc, char* argv[]) {
    Cpu cpu{};
    cpu.LoadRom("roms/cpudiag.bin");
    cpu.RunSingle();

    return 0;
}