#include "Shell.h"
#include "Opcode.h"
#include "Format.h"

#include <iostream>

void Shell::Run() {
    ResetCpu();
    PrintWelcome();

    shouldRun = true;
    while (shouldRun) {
        Prompt();
        auto cmd = ReadCmd();
        InterpretCmd(std::move(cmd));
    }
}

std::string Shell::ReadCmd() {
    std::string cmd{};
    std::cin >> cmd;

    return cmd;
}

void Shell::InterpretCmd(std::string cmd) {
    if (cmd == "exit") {
        shouldRun = false;
    } else if (cmd == "step") {
        auto opcode = cpu->FetchNext();
        PrintOpcode(cpu->Disassemble(opcode));
        cpu->Execute(opcode);
    } else if (cmd == "pc") {
        std::cout << Format("%04x", cpu->GetRegister(Reg16::PC)) << std::endl;
    } else if (cmd == "run") {
        while (true) {
            InterpretCmd("step");

            if (cpu->GetRegister(Reg16::PC) == 0) {
                break;
            }
        }
    } else if (cmd == "load") {
        cpu->LoadRom("roms/cpudiag.bin");
    } else if (cmd == "flags") {
        PrintFlags();
    } else if (cmd == "reset") {
        ResetCpu();
    }
}

void Shell::PrintOpcode(std::string opcode) {
    uint16_t pc = cpu->GetRegister(Reg16::PC) - 1;
    std::cout << Format("%04x: %s", pc, opcode) << std::endl;
}

void Shell::PrintWelcome() {
    std::cout << "Welcome to the intel8080emu project by Jan Lafferton" << std::endl;
}

void Shell::PrintFlags() {
    auto flags = Format(
        "| S: %d | Z: %d | AC: %d | P: %d | C: %d |",
        cpu->GetFlag(Flag::Sign),
        cpu->GetFlag(Flag::Zero),
        cpu->GetFlag(Flag::AuxCarry),
        cpu->GetFlag(Flag::Parity),
        cpu->GetFlag(Flag::Carry)
    );

    std::cout << flags << std::endl;
}

void Shell::Prompt() {
    std::cout << "> " << std::flush;
}

void Shell::ResetCpu() {
    cpu.reset(new Cpu{});
}