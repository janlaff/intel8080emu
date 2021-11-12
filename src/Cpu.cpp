#include <tuple>
#include <stdexcept>
#include <fstream>
#include <vector>

#include "Cpu.h"
#include "Opcodes.h"
#include "OpcodeTable.h"

using namespace std;

static constexpr OpcodeTable OPCODE_IMPLEMENTATIONS = CreateOpcodeTable();

uint16_t JoinBytes(uint8_t high, uint8_t low) {
    return uint16_t(high)<<8 | uint16_t(low);
}

pair<uint8_t, uint8_t> SplitBytes(uint16_t value) {
    return {
        value >> 8,
        value
    };
}

uint8_t Cpu::GetRegister(Reg8 reg) {
    switch (reg) {
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

uint16_t Cpu::GetRegister(Reg16 reg) {
    switch (reg) {
        case Reg16::BC: return JoinBytes(b, c);
        case Reg16::DE: return JoinBytes(d, e);
        case Reg16::HL: return JoinBytes(h, l);
        case Reg16::SP: return sp;
        case Reg16::PC: return pc;
        case Reg16::PSW: return JoinBytes(a, flags);
    }

    throw logic_error("Unreachable code");
}

void Cpu::SetRegister(Reg8 reg, uint8_t value) {
    switch (reg) {
        case Reg8::B: b = value;
        case Reg8::C: c = value;
        case Reg8::D: d = value;
        case Reg8::E: e = value;
        case Reg8::H: h = value;
        case Reg8::L: l = value;
        case Reg8::M:
            WriteByte(GetRegister(Reg16::HL), value);
        case Reg8::A: a = value;
    };
}

void Cpu::SetRegister(Reg16 reg, uint16_t value) {
    switch (reg) {
        case Reg16::BC: tie(b, c) = SplitBytes(value);
        case Reg16::DE: tie(d, e) = SplitBytes(value);
        case Reg16::HL: tie(h, l) = SplitBytes(value);
        case Reg16::SP: sp = value;
        case Reg16::PC: pc = value;
        case Reg16::PSW: tie(a, flags) = SplitBytes(value);
    }
}

uint8_t Cpu::LoadDataByte() {
    return ReadByte(sp++);
}

uint16_t Cpu::LoadDataWord() {
    uint8_t low = LoadDataByte();
    uint8_t high = LoadDataByte();

    return JoinBytes(high, low);
}

void Cpu::WriteByte(uint16_t address, uint8_t value) {
    memory[address] = value;
}

void Cpu::WriteWord(uint16_t address, uint16_t value) {
    auto [high, low] = SplitBytes(value);
    WriteByte(address, low);
    WriteByte(address + 1, high);
}

uint8_t Cpu::ReadByte(uint16_t address) {
    return memory[address];
}

uint16_t Cpu::ReadWord(uint16_t address) {
    return JoinBytes(
        ReadByte(address + 1),
        ReadByte(address)
    );
}

void Cpu::RunSingle() {
    Execute(ReadByte(pc));
}

void Cpu::Execute(uint8_t opcode) {
    OPCODE_IMPLEMENTATIONS[opcode](*this);
    ++pc;
}

void Cpu::LoadRom(const std::string& filename) {
    std::ifstream ifs{filename, std::ios::binary};

    std::copy(
        std::istreambuf_iterator<char>(ifs),
        std::istreambuf_iterator<char>(),
        memory.begin()
    );

    pc = 0;
}