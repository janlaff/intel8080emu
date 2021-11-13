#pragma once

#include <cstdint>
#include <cstddef>

#include "Cpu.h"
#include "Macros.h"

DEFINE_OPCODE(Invalid, uint8_t byte)
DEFINE_OPCODE(Mov, Reg8 dstReg; Reg8 srcReg)
DEFINE_OPCODE(Mvi, Reg8 dstReg)
DEFINE_OPCODE(Lxi, Reg16 dstReg)
DEFINE_OPCODE(Lda,)
DEFINE_OPCODE(Sta,)
DEFINE_OPCODE(Lhld,)
DEFINE_OPCODE(Shld,)
DEFINE_OPCODE(Ldax, Reg16 srcReg)

/*struct MovOpcode { Reg8 dstReg; Reg8 srcReg; };
struct MviOpcode { Reg8 dstReg; };
struct LxiOpcode { Reg16 dstReg; };
struct LdaOpcode {};
struct StaOpcode {};
struct LhldOpcode {};
struct ShldOpcode {};
struct LdaxOpcode { Reg16 dstReg; };
struct StaxOpcode { Reg16 dstReg; };
struct XchgOpcode {};
struct AddOpcode { Reg8 srcReg; };
struct AdiOpcode {};
struct AdcOpcode { Reg8 srcReg; };
struct AciOpcode {};
struct SubOpcode { Reg8 srcReg; };
struct SuiOpcode {};
struct SbbOpcode { Reg8 srcReg; };
struct SbiOpcode {};
struct InrOpcode { Reg8 dstReg; };
struct DcrOpcode { Reg8 dstReg; };
struct InxOpcode { Reg16 dstReg; };
struct DcxOpcode { Reg16 dstReg; };
struct DadOpcode { Reg16 dstReg; };
struct DaaOpcode {};
struct AnaOpcode { Reg8 srcReg; };
struct AniOpcode {};
struct OraOpcode { Reg8 srcReg; };
struct OriOpcode {};
struct XraOpcode { Reg8 srcReg; };
struct XriOpcode {};
struct CmpOpcode { Reg8 srcReg; };
struct CpiOpcode {};
struct RlcOpcode {};
struct RrcOpcode {};
struct RalOpcode {};
struct RarOpcode {};
struct CmaOpcode {};
struct CmcOpcode {};
struct StcOpcode {};
struct JmpOpcode {};
struct JmpIfOpcode { JumpCondition condition; };
struct CallOpcode {};
struct CallIfOpcode { JumpCondition condition; };
struct RetOpcode {};
struct RetIfOpcode { JumpCondition condition; };
struct RstOpcode { uint8_t vectorNum; };
struct PchlOpcode {};
struct PushOpcode { Reg16 dstReg; };
struct PopOpcode { Reg16 dstReg; };
struct XthlOpcode {};
struct SphlOpcode {};
struct InOpcode {};
struct OutOpcode {};
struct EiOpcode {};
struct DiOpcode {};
struct HltOpcode {};
struct NopOpcode {};*/