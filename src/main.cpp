#include "Cpu.h"

int main(int argc, char* argv[]) {
    Cpu cpu{};
    cpu.LoadRom("roms/cpudiag.bin");

    while (true)
        cpu.ExecuteNextOpcode();

    return 0;
}