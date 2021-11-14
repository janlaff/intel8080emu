#pragma once

#include <cstdint>
#include <cstddef>
#include <tuple>

#include "Cpu.h"
#include "Macros.h"

template<typename T>
struct Opcode {
    constexpr explicit Opcode(uint8_t opcode)
        : opcode{opcode}
        {}

    Reg8 GetSSS() {
        return ParseSourceReg(opcode);
    }

    Reg8 GetDDD() {
        return ParseDestinationReg(opcode);
    }

    Reg16 GetRP() {
        return ParseDestinationReg16(opcode);
    }

    uint8_t GetNNN() {
        return ParseVectorNum(opcode);
    }

    JumpCondition GetCCC() {
        return ParseJumpCondition(opcode);
    }

    uint8_t opcode;
};

template<typename T>
void Execute(Cpu& cpu, T opcode);

void Execute(Cpu& cpu, Opcode<struct INVALID> opcode);
void Execute(Cpu& cpu, Opcode<struct MOV> opcode);
void Execute(Cpu& cpu, Opcode<struct MVI> opcode);
void Execute(Cpu& cpu, Opcode<struct LXI> opcode);
void Execute(Cpu& cpu, Opcode<struct LDA> opcode);
void Execute(Cpu& cpu, Opcode<struct STA> opcode);
void Execute(Cpu& cpu, Opcode<struct LHLD> opcode);
void Execute(Cpu& cpu, Opcode<struct SHLD> opcode);
void Execute(Cpu& cpu, Opcode<struct LDAX> opcode);
void Execute(Cpu& cpu, Opcode<struct STAX> opcode);
void Execute(Cpu& cpu, Opcode<struct XCHG> opcode);
void Execute(Cpu& cpu, Opcode<struct ADD> opcode);
void Execute(Cpu& cpu, Opcode<struct ADI> opcode);
void Execute(Cpu& cpu, Opcode<struct ADC> opcode);
void Execute(Cpu& cpu, Opcode<struct ACI> opcode);
void Execute(Cpu& cpu, Opcode<struct SUB> opcode);
void Execute(Cpu& cpu, Opcode<struct SUI> opcode);
void Execute(Cpu& cpu, Opcode<struct SBB> opcode);
void Execute(Cpu& cpu, Opcode<struct SBI> opcode);
void Execute(Cpu& cpu, Opcode<struct INR> opcode);
void Execute(Cpu& cpu, Opcode<struct DCR> opcode);
void Execute(Cpu& cpu, Opcode<struct INX> opcode);
void Execute(Cpu& cpu, Opcode<struct DCX> opcode);
void Execute(Cpu& cpu, Opcode<struct DAD> opcode);
void Execute(Cpu& cpu, Opcode<struct DAA> opcode);
void Execute(Cpu& cpu, Opcode<struct ANA> opcode);
void Execute(Cpu& cpu, Opcode<struct ANI> opcode);
void Execute(Cpu& cpu, Opcode<struct ORA> opcode);
void Execute(Cpu& cpu, Opcode<struct ORI> opcode);
void Execute(Cpu& cpu, Opcode<struct XRA> opcode);
void Execute(Cpu& cpu, Opcode<struct XRI> opcode);
void Execute(Cpu& cpu, Opcode<struct CMP> opcode);
void Execute(Cpu& cpu, Opcode<struct CPI> opcode);
void Execute(Cpu& cpu, Opcode<struct RLC> opcode);
void Execute(Cpu& cpu, Opcode<struct RRC> opcode);
void Execute(Cpu& cpu, Opcode<struct RAL> opcode);
void Execute(Cpu& cpu, Opcode<struct RAR> opcode);
void Execute(Cpu& cpu, Opcode<struct CMA> opcode);
void Execute(Cpu& cpu, Opcode<struct CMC> opcode);
void Execute(Cpu& cpu, Opcode<struct STC> opcode);
void Execute(Cpu& cpu, Opcode<struct JMP> opcode);
void Execute(Cpu& cpu, Opcode<struct JMP_IF> opcode);
void Execute(Cpu& cpu, Opcode<struct CALL> opcode);
void Execute(Cpu& cpu, Opcode<struct CALL_IF> opcode);
void Execute(Cpu& cpu, Opcode<struct RET> opcode);
void Execute(Cpu& cpu, Opcode<struct RET_IF> opcode);
void Execute(Cpu& cpu, Opcode<struct RST> opcode);
void Execute(Cpu& cpu, Opcode<struct PUSH> opcode);
void Execute(Cpu& cpu, Opcode<struct POP> opcode);
void Execute(Cpu& cpu, Opcode<struct XTHL> opcode);
void Execute(Cpu& cpu, Opcode<struct SPHL> opcode);
void Execute(Cpu& cpu, Opcode<struct IN> opcode);
void Execute(Cpu& cpu, Opcode<struct OUT> opcode);
void Execute(Cpu& cpu, Opcode<struct EI> opcode);
void Execute(Cpu& cpu, Opcode<struct DI> opcode);
void Execute(Cpu& cpu, Opcode<struct HLT> opcode);
void Execute(Cpu& cpu, Opcode<struct NOP> opcode);
