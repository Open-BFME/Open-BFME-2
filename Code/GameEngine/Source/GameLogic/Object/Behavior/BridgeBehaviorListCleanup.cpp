// cl: /Ireference/shims/sweep /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/asciistring_outofline /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ivendor/stlport /ICode/GameEngine/Source/Common /O1
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// STLport cleanup for the shared BridgeDieFX/OCL list representation.
// Registered callbacks and node-copy code establish pointer/delay/string
// fields at +0/+4/+8. Only the string field is destroyed by thunk 0x577998.
#include <list>
#include "Common/AsciiString.h"

struct BridgeBehaviorTimeInfo8 {
	unsigned int delay_00;
	AsciiString boneName_04;
};

struct BridgeBehaviorListValue12 {
	void *object_00;
	BridgeBehaviorTimeInfo8 time_04;
	~BridgeBehaviorListValue12();
};
typedef char CheckBridgeListValueSize[(sizeof(BridgeBehaviorListValue12) == 12) ? 1 : -1];

typedef std::list<BridgeBehaviorListValue12> BridgeBehaviorList12;

// ?ForceBridgeBehaviorListClear@@YAXAAV?$list@UBridgeBehaviorListValue12@@V?$allocator@UBridgeBehaviorListValue12@@@_STL@@@_STL@@@Z absent-from-retail
__declspec(noinline) void ForceBridgeBehaviorListClear(BridgeBehaviorList12 &list)
{
	list.clear();
}

// ?ForceBridgeBehaviorListDestroy@@YAXPAV?$list@UBridgeBehaviorListValue12@@V?$allocator@UBridgeBehaviorListValue12@@@_STL@@@_STL@@@Z absent-from-retail
__declspec(noinline) void ForceBridgeBehaviorListDestroy(BridgeBehaviorList12 *list)
{
	list->~list();
}
