#pragma once

#include <unordered_map>
#include <memory>

#include "Cpu.h"

class Shell {
public:
    void Run();

private:
    std::string ReadCmd();
    void InterpretCmd(std::string cmd);
    void PrintOpcode(std::string opcode);
    void PrintWelcome();
    void PrintFlags();
    void Prompt();
    void ResetCpu();

    std::unique_ptr<Cpu> cpu;
    bool shouldRun;

    std::unordered_map<uint16_t, const Opcode&> breakPoints;
};