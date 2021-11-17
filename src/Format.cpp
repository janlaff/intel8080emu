#include "Format.h"

bool Replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

std::string FormatEnum(Reg8 value) {
    switch (value) {
        case Reg8::A: return "A";
        case Reg8::B: return "B";
        case Reg8::C: return "C";
        case Reg8::D: return "D";
        case Reg8::E: return "E";
        case Reg8::H: return "H";
        case Reg8::L: return "L";
        case Reg8::M: return "M";
    }
}

std::string FormatEnum(Reg16 value) {
    switch (value) {
        case Reg16::PSW: return "PSW";
        case Reg16::BC: return "BC";
        case Reg16::DE: return "DE";
        case Reg16::HL: return "HL";
        case Reg16::SP: return "SP";
        case Reg16::PC: return "PC";
    }
}

std::string FormatEnum(JumpCondition value) {
    // TODO
}