#pragma once

#include <string_view>
#include <cstdint>

constexpr bool BitMaskMatch(std::string_view bitMask, uint8_t opcode) {
    for (int i = 0; i < 8; ++i) {
        bool currentBitIsSet = opcode & (1 << (7 - i));

        if (bitMask[i] == '1' && !currentBitIsSet)
            return false;

        if (bitMask[i] == '0' && currentBitIsSet)
            return false;

        // Other values for bitMask[i] are being used as placeholders
    }

    return true;
}