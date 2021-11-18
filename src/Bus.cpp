#include "Bus.h"
#include "Bytes.h"

uint8_t Bus::ReadByte(uint16_t address) const {
    return memory[address];
}

uint16_t Bus::ReadWord(uint16_t address) const {
    return JoinBytes(
        ReadByte(address + 1),
        ReadByte(address)
    );
}

void Bus::WriteByte(uint16_t address, uint8_t value) {
    memory[address] = value;
}

void Bus::WriteWord(uint16_t address, uint16_t value) {
    auto [high, low] = SplitBytes(value);
    WriteByte(address, low);
    WriteByte(address + 1, high);
}