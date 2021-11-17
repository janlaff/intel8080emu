#pragma once

#include "OpcodeTypes.h"

constexpr OpcodeDecl OPCODE_DECLS[] {
    {"MOV D,S", "01DDDSSS", [](Cpu& cpu, Opcode opcode) {
        cpu.SetRegister(
            opcode.GetDDD(),
            cpu.GetRegister(opcode.GetSSS())
        );
    }},
    {"MVI D,#", "00DDD110", [](Cpu& cpu, Opcode opcode) {
        cpu.SetRegister(
            opcode.GetDDD(),
            cpu.LoadDataByte()
        );
    }},
    {"LXI RP,#", "00RP0001", [](Cpu& cpu, Opcode opcode) {
        cpu.SetRegister(
            opcode.GetRP(),
            cpu.LoadDataWord()
        );
    }},
    {"LDA a", "00111010", [](Cpu& cpu, Opcode opcode) {
        cpu.SetRegister(
            opcode.GetDDD(),
            cpu.ReadByte(cpu.LoadDataWord())
        );
    }},
    {"STA a", "00110010", [](Cpu& cpu, Opcode opcode) {
        cpu.WriteByte(
            cpu.LoadDataWord(),
            cpu.GetRegister(Reg8::A)
        );
    }},
    {"LHLD a", "00101010", [](Cpu& cpu, Opcode opcode) {
        cpu.SetRegister(
            Reg16::HL,
            cpu.ReadWord(cpu.LoadDataWord())
        );
    }},
    {"SHLD a", "00100010", [](Cpu& cpu, Opcode opcode) {
        cpu.WriteWord(
            cpu.ReadWord(cpu.LoadDataWord()),
            cpu.GetRegister(Reg16::HL)
        );
    }},
    {"LDAX RP", "00RP1010", [](Cpu& cpu, Opcode opcode) {
        cpu.SetRegister(
            Reg8::A,
            cpu.ReadWord(cpu.GetRegister(opcode.GetSSS()))
        );
    }},
    {"STAX RP", "00RP0010", [](Cpu& cpu, Opcode opcode) {
        cpu.WriteWord(
            cpu.GetRegister(opcode.GetRP()),
            cpu.GetRegister(Reg8::A)
        );
    }},
    {"XCHG", "11101011", [](Cpu& cpu, Opcode opcode) {
        auto hl = cpu.GetRegister(Reg16::HL);
        cpu.SetRegister(Reg16::HL, cpu.GetRegister(Reg16::DE));
        cpu.SetRegister(Reg16::DE, hl);
    }},
    {"ADD S", "10000SSS", [](Cpu& cpu, Opcode opcode) {
        uint8_t a = cpu.GetRegister(Reg8::A);
        uint8_t x = cpu.GetRegister(opcode.GetSSS());
        uint16_t result = a + x;

        cpu.SetRegister(Reg8::A, result);
        cpu.UpdateFlags(result);
    }},
    {"NOP", "00XXX000", [](Cpu& cpu, Opcode opcode) {
        // No operation
    }},
    {"<INVALID>", "XXXXXXXX", [](Cpu& cpu, Opcode opcode) {
        int pc = cpu.GetRegister(Reg16::PC) - 1;
        throw std::runtime_error(
                Format("Invalid opcode 0x%02x at address 0x%04x", opcode.GetRaw(), pc)
        );
    }}
};