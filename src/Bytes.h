#pragma once

#include <cstdint>
#include <tuple>

uint16_t JoinBytes(uint8_t high, uint8_t low);
std::pair<uint8_t, uint8_t> SplitBytes(uint16_t value);