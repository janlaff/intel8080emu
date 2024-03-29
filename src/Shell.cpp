#include <iostream>

#include "Shell.h"
#include "Opcode.h"
#include "Format.h"
#include "BreakException.h"

using namespace std;

void Shell::Run() {
    ResetCpu();
    PrintWelcome();

    shouldRun = true;
    while (shouldRun) {
        Prompt();
        auto cmd = ReadCmd();
        InterpretCmd(move(cmd));
    }
}

string Shell::ReadCmd() {
    string cmd{};
    cin >> cmd;

    return cmd;
}

void Shell::InterpretCmd(string cmd) {
    if (cmd == "exit") {
        shouldRun = false;
    } else if (cmd == "step") {
        auto opcode = cpu->FetchNext();
        PrintOpcode(cpu->Disassemble(opcode));
        cpu->Execute(opcode);
    } else if (cmd == "pc") {
        cout << Format("%04x", cpu->GetRegister(Reg16::PC)) << endl;
    } else if (cmd == "run") {
        try {
            while (true) {
                auto opcode = cpu->FetchNext();
                cpu->Execute(opcode);
            }
        } catch (BreakException& b) {
            cout << Format("Reached breakpoint @%04x", b.address) << endl;
            // Invalid displayed pc (pc -1)
            PrintOpcode(cpu->Disassemble(b.opcode));
        }
    } else if (cmd == "load") {
        cpu->LoadRom("roms/cpudiag.bin");
    } else if (cmd == "flags") {
        PrintFlags();
    } else if (cmd == "reset") {
        ResetCpu();
    } else if (cmd == "break") {
        cpu->SetBreakPoint(0x0689);
    }
}

void Shell::PrintOpcode(string opcode) {
    uint16_t pc = cpu->GetRegister(Reg16::PC) - 1;
    cout << Format("%04x: %s", pc, opcode) << endl;
}

void Shell::PrintWelcome() {
    cout << "Welcome to the intel8080emu project by Jan Lafferton" << endl;
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

    cout << flags << endl;
}

void Shell::Prompt() {
    cout << "> " << flush;
}

void Shell::ResetCpu() {
    cpu.reset(new Cpu{});
}