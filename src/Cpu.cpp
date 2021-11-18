#include <tuple>
#include <stdexcept>
#include <fstream>
#include <bitset>

#include "Cpu.h"
#include "OpcodeTable.h"
#include "Bytes.h"

using namespace std;

uint8_t Cpu::GetRegister(Reg8 which) const {
    switch (which) {
        case Reg8::B: return b;
        case Reg8::C: return c;
        case Reg8::D: return d;
        case Reg8::E: return e;
        case Reg8::H: return h;
        case Reg8::L: return l;
        case Reg8::M: return ReadByte(GetRegister(Reg16::HL));
        case Reg8::A: return a;
    };

    throw logic_error("Unreachable code");
}

uint16_t Cpu::GetRegister(Reg16 which) const {
    switch (which) {
        case Reg16::BC: return JoinBytes(b, c);
        case Reg16::DE: return JoinBytes(d, e);
        case Reg16::HL: return JoinBytes(h, l);
        case Reg16::SP: return sp;
        case Reg16::PC: return pc;
        case Reg16::PSW: return JoinBytes(a, flags);
    }

    throw logic_error("Unreachable code");
}

void Cpu::SetRegister(Reg8 which, uint8_t value) {
    switch (which) {
        case Reg8::B: b = value; break;
        case Reg8::C: c = value; break;
        case Reg8::D: d = value; break;
        case Reg8::E: e = value; break;
        case Reg8::H: h = value; break;
        case Reg8::L: l = value; break;
        case Reg8::M: WriteByte(GetRegister(Reg16::HL), value); break;
        case Reg8::A: a = value; break;
    };
}

void Cpu::SetRegister(Reg16 which, uint16_t value) {
    switch (which) {
        case Reg16::BC: tie(b, c) = SplitBytes(value); break;
        case Reg16::DE: tie(d, e) = SplitBytes(value); break;
        case Reg16::HL: tie(h, l) = SplitBytes(value); break;
        case Reg16::SP: sp = value; break;
        case Reg16::PC: pc = value; break;
        case Reg16::PSW: tie(a, flags) = SplitBytes(value); break;
    }
}

uint8_t Cpu::FetchDataByte() {
    return ReadByte(pc++);
}

uint16_t Cpu::FetchDataWord() {
    uint8_t low = FetchDataByte();
    uint8_t high = FetchDataByte();

    return JoinBytes(high, low);
}

const Opcode& Cpu::FetchNext() {
    return opcodes[ReadByte(pc++)];
}

void Cpu::Execute(const Opcode& opcode) {
    opcode.Execute(*this);
}

std::string Cpu::Disassemble(const Opcode &opcode) {
    auto savedPc = pc;
    auto result = opcode.Disassemble(*this);
    pc = savedPc;
    return result;
}

void Cpu::LoadRom(const string& filename) {
    ifstream ifs{filename, ios::binary};

    copy(
        istreambuf_iterator<char>(ifs),
        istreambuf_iterator<char>(),
        memory.begin()
    );

    pc = 0;
}

void Cpu::LoadRom(const std::vector<uint8_t> rom) {
    copy(rom.begin(), rom.end(), memory.begin());
    pc = 0;
}

bool Cpu::JumpConditionMet(JumpCondition condition) {
    switch (condition) {
        case JumpCondition::Carry: return GetFlag(Flag::Carry);
        case JumpCondition::NoCarry: return !GetFlag(Flag::Carry);
        case JumpCondition::Even: return GetFlag(Flag::Parity);
        case JumpCondition::Odd: return !GetFlag(Flag::Parity);
        case JumpCondition::Negative: return GetFlag(Flag::Sign);
        case JumpCondition::Positive: return !GetFlag(Flag::Sign);
        case JumpCondition::Zero: return GetFlag(Flag::Zero);
        case JumpCondition::NonZero: return !GetFlag(Flag::Zero);
    }
}