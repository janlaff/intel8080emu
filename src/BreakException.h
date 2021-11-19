#pragma once

#include <stdexcept>

#include "Opcode.h"

class BreakException : public std::exception {
public:
    BreakException(uint16_t address, const Opcode& opcode)
        : address(address)
        , opcode(opcode) {}

    uint16_t address;
    const Opcode& opcode;
};