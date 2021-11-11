#include "MemoryBus.h"

uint8_t MemoryBus::Read(uint16_t address) {
    return memory[address];
}

void MemoryBus::Write(uint16_t address, uint8_t value) {
    memory[address] = value;
}