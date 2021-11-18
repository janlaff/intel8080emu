#pragma once

#include <cstdint>
#include <array>

class Bus {
public:
    uint8_t ReadByte(uint16_t address) const;
    uint16_t ReadWord(uint16_t address) const;

    void WriteByte(uint16_t address, uint8_t value);
    void WriteWord(uint16_t address, uint16_t value);

protected:
    std::array<uint8_t, 0xffff> memory;
};