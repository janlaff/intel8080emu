#pragma once

#include <cstdint>

class MemoryBus {
public:
    void Write(uint16_t address, uint8_t value);
    uint8_t Read(uint16_t address);
};