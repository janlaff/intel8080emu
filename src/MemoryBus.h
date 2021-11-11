#pragma once

#include <cstdint>
#include <array>

class MemoryBus {
public:
    void Write(uint16_t address, uint8_t value);
    uint8_t Read(uint16_t address);

private:
    std::array<uint8_t, 0xffff> memory;
};