#include <tuple>

#include "RegStorage.h"
#include "Bytes.h"

using namespace std;

void RegStorage::SetReg(Reg8 reg, uint8_t value) {
    data[reg] = value;
}

void RegStorage::SetReg(Reg16 reg, uint16_t value) {
    tie(data[reg], data[reg+1]) = SplitBytes(value);
}

uint8_t RegStorage::GetReg(Reg8 reg) {
    return data[reg];
}

uint16_t RegStorage::GetReg(Reg16 reg) {
    return JoinBytes(data[reg], data[reg+1]);
}