// cl: /Ireference/shims/sweep /G7 /arch:SSE /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ivendor/stlport /Ireference/shims/asciistring_outofline /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /O1
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Registered bridge callbacks pass pointer/delay/string values to the shared
// list insertion chain. The target copies its +4 delay/string pair through
// the existing body at 0xCF475; its original class name remains unknown.
#include "Common/AsciiString.h"

// Neutral view: target callbacks/copy chain establish these fields and offsets;
// BFME1 BridgeBehavior names are semantic provenance, not target class proof.
struct BridgeBehaviorTimeInfo8
{
    unsigned int delay_00;
    AsciiString boneName_04;
    BridgeBehaviorTimeInfo8(const BridgeBehaviorTimeInfo8 &other);
};

struct BridgeBehaviorListValue12
{
    void *object_00;
    BridgeBehaviorTimeInfo8 timeInfo_04;
    BridgeBehaviorListValue12(const BridgeBehaviorListValue12 &other);
};

typedef char VerifyBridgeBehaviorValueSize[(sizeof(BridgeBehaviorListValue12) == 12) ? 1 : -1];

#include <memory>

__declspec(noinline) BridgeBehaviorListValue12::BridgeBehaviorListValue12(
    const BridgeBehaviorListValue12 &other)
    : object_00(other.object_00), timeInfo_04(other.timeInfo_04)
{
}

// ?Force_ConstructBridgeBehaviorListValue12@@YAXPAUBridgeBehaviorListValue12@@ABU1@@Z absent-from-retail
void Force_ConstructBridgeBehaviorListValue12(
    BridgeBehaviorListValue12 *destination,
    const BridgeBehaviorListValue12 &source)
{
    std::_Construct(destination, source);
}
