#include "Format.h"

using namespace std;

bool Replace(string& str, const string& from, const string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

string FormatEnum(Reg8 value) {
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

string FormatEnum(Reg16 value) {
    switch (value) {
        case Reg16::PSW: return "PSW";
        case Reg16::BC: return "BC";
        case Reg16::DE: return "DE";
        case Reg16::HL: return "HL";
        case Reg16::SP: return "SP";
        case Reg16::PC: return "PC";
    }
}

string FormatEnum(JumpCondition value) {
    switch (value) {
        case JumpCondition::Carry: return "CARRY";
        case JumpCondition::NoCarry: return "NOT CARRY";
        case JumpCondition::Even: return "EVEN";
        case JumpCondition::Odd: return "ODD";
        case JumpCondition::Negative: return "NEGATIVE";
        case JumpCondition::Positive: return "POSITIVE";
        case JumpCondition::Zero: return "ZERO";
        case JumpCondition::NonZero: return "NOT ZERO";
    }
}