#pragma once

#include <stdexcept>

#include "OpcodeTypes.h"
#include "Format.h"
#include "BitMask.h"

constexpr OpcodeDefinition opcodeDefinitions[] {
    {"MOV D,S", "01DDDSSS", [](Cpu& cpu, OpcodeParams params) {
        cpu.SetRegister(
            params.DDD(),
            cpu.GetRegister(params.SSS())
        );
    }},
    {"MVI D,#", "00DDD110", [](Cpu& cpu, OpcodeParams params) {
        cpu.SetRegister(
            params.DDD(),
            cpu.LoadDataByte()
        );
    }},
    {"LXI RP,#", "00RP0001", [](Cpu& cpu, OpcodeParams params) {
        cpu.SetRegister(
            params.RP(),
            cpu.LoadDataWord()
        );
    }},
    {"LDA a", "00111010", [](Cpu& cpu, OpcodeParams params) {
        cpu.SetRegister(
            params.DDD(),
            cpu.ReadByte(cpu.LoadDataWord())
        );
    }},
    {"STA a", "00110010", [](Cpu& cpu, OpcodeParams params) {
        cpu.WriteByte(
            cpu.LoadDataWord(),
            cpu.GetRegister(Reg8::A)
        );
    }},
    {"LHLD a", "00101010", [](Cpu& cpu, OpcodeParams params) {
        cpu.SetRegister(
            Reg16::HL,
            cpu.ReadWord(cpu.LoadDataWord())
        );
    }},
    {"SHLD a", "00100010", [](Cpu& cpu, OpcodeParams params) {
        cpu.WriteWord(
            cpu.ReadWord(cpu.LoadDataWord()),
            cpu.GetRegister(Reg16::HL)
        );
    }},
    {"LDAX RP", "00RP1010", [](Cpu& cpu, OpcodeParams params) {
        cpu.SetRegister(
            Reg8::A,
            cpu.ReadWord(cpu.GetRegister(params.SSS()))
        );
    }},
    {"STAX RP", "00RP0010", [](Cpu& cpu, OpcodeParams params) {
        cpu.WriteWord(
            cpu.GetRegister(params.RP()),
            cpu.GetRegister(Reg8::A)
        );
    }},
    {"XCHG", "11101011", [](Cpu& cpu, OpcodeParams params) {
        auto hl = cpu.GetRegister(Reg16::HL);
        cpu.SetRegister(Reg16::HL, cpu.GetRegister(Reg16::DE));
        cpu.SetRegister(Reg16::DE, hl);
    }},
    {"ADD S", "10000SSS", [](Cpu& cpu, OpcodeParams params) {
        uint8_t a = cpu.GetRegister(Reg8::A);
        uint8_t x = cpu.GetRegister(params.SSS());
        uint16_t result = a + x;

        cpu.SetRegister(Reg8::A, result);
        cpu.UpdateFlags(result);
    }},
    {"NOP", "00XXX000", [](Cpu& cpu, OpcodeParams params) {
        // No operation
    }},
    {"<INVALID>", "XXXXXXXX", [](Cpu& cpu, OpcodeParams params) {
        int pc = cpu.GetRegister(Reg16::PC) - 1;
        throw std::runtime_error(
                Format("Invalid opcode 0x%02x at address 0x%04x", params.opcode, pc)
        );
    }}
};

template<uint8_t opcode>
constexpr Opcode ResolveOpcode() {
    for (auto& definition : opcodeDefinitions) {
        if (BitMaskMatch(definition.bitPattern, opcode)) {
            return {definition, {opcode}};
        }
    }

    // Should never happen since last entry of
    // opcodeDefinitions will match with every opcode
    throw std::logic_error("Failed to resolve opcode");
}

template<uint8_t ... opcodes>
constexpr OpcodeTable CreateOpcodeTableImpl(std::integer_sequence<uint8_t, opcodes...>) {
    return OpcodeTable{ResolveOpcode<opcodes>()...};
}

constexpr OpcodeTable CreateOpcodeTable() {
    return CreateOpcodeTableImpl(std::make_integer_sequence<uint8_t, 0xff>{});
}