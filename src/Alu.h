#pragma once

#include <cstdint>

#include "EnumTypes.h"

class Alu {
public:
    uint8_t Add(uint8_t left, uint8_t right);
    uint8_t Sub(uint8_t left, uint8_t right);
    uint8_t And(uint8_t left, uint8_t right);
    uint8_t Or(uint8_t left, uint8_t right);
    uint8_t Xor(uint8_t left, uint8_t right);
    void Cmp(uint8_t left, uint8_t right);

    bool GetFlag(Flag which) const;
    void SetFlag(Flag which, bool enabled);
    void CheckSZPC(uint16_t value);

    uint8_t flags;
};