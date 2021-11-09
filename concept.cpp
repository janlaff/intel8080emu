#include <iostream>
#include <array>
#include <memory>

enum class Reg8 : uint8_t {
    B, C, D, E, H, L, M, A
};

enum class Reg16 : uint8_t {
    BC, DE, HL, SP_OR_PSW
};

enum class JumpCondition : uint8_t {
    NonZero,
    Zero,
    NoCarry,
    Carry,
    Odd,
    Even,
    Positive,
    Minus
};

class OpcodeImpl {
public:
    virtual void Execute() = 0;
};

class MovOpcode : public OpcodeImpl {
public:
    MovOpcode(Reg8 srcReg, Reg8 dstReg)
        : srcReg(srcReg), dstReg(dstReg) {}

    void Execute() override {
        // dst <-- src
    }

private:
    Reg8 srcReg;
    Reg8 dstReg;
};

class MviOpcode : public OpcodeImpl {
public:
    MviOpcode(Reg8 dstReg)
            : dstReg(dstReg) {}

    void Execute() override {
        // dst <-- src
    }

private:
    Reg8 dstReg;
};

class LxiOpcode : public OpcodeImpl {
public:
    LxiOpcode(Reg16 regPair)
            : regPair(regPair) {}

    void Execute() override {
        // dst <-- src
    }

private:
    Reg16 regPair;
};

constexpr Reg8 ParseDestinationRegister(uint8_t opcode) {
    return static_cast<Reg8>((opcode & 0b00111000) >> 3);
}

constexpr Reg8 ParseSourceRegister(uint8_t opcode) {
    return static_cast<Reg8>(opcode & 0b00000111);
}

constexpr Reg16 ParseRegisterPair(uint8_t opcode) {
    return static_cast<Reg16>((opcode & 0b00110000) >> 4);
}

constexpr JumpCondition ParseJumpCondition(uint8_t opcode) {
    return static_cast<JumpCondition>((opcode & 0b00111000) >> 3);
}

constexpr bool MatchOpcode(std::string_view pattern, uint8_t opcode) {
    for (int i = 0; i < 8; ++i) {
        uint8_t bit = opcode & (1 << (7 - i));

        if (pattern[i] == '1' && !bit) return false;
        if (pattern[i] == '0' && bit) return false;
    }

    return true;
}

template<uint8_t opcode>
constexpr std::false_type failCompilationFor{};

// Opcode generation syntactic sugar
#define OPCODE_GENERATOR template<uint8_t opcode> constexpr OpcodeImpl*
#define IF_MATCH(pattern) if constexpr (MatchOpcode(pattern, opcode)) return new
#define ELIF_MATCH(pattern) else IF_MATCH(pattern)
#define ELIF_MATCH(pattern) else IF_MATCH(pattern)
#define ELSE_FAIL(message) else static_assert(failCompilationFor<opcode>, message)

OPCODE_GENERATOR GenerateOpcodeImplementation() {
    Reg8 srcReg = ParseSourceRegister(opcode);
    Reg8 dstReg = ParseDestinationRegister(opcode);
    Reg16 regPair = ParseRegisterPair(opcode);
    JumpCondition jmpCond = ParseJumpCondition(opcode);

    IF_MATCH("01DDDSSS") MovOpcode{srcReg, dstReg};
    ELIF_MATCH("00DDD110") MviOpcode{dstReg};
    ELIF_MATCH("00RP0001") LxiOpcode{regPair};
    ELSE_FAIL("No implementation for opcode");
}

int main() {
    GenerateOpcodeImplementation<0b00111110>();

    return 0;
}
