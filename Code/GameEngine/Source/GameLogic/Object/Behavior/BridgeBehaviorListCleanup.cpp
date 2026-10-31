// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/sweep /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/asciistring_outofline /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ivendor/stlport /ICode/GameEngine/Source/Common /O1
// stlport
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// STLport cleanup for the shared BridgeDieFX/OCL list representation.
// Registered callbacks and node-copy code establish pointer/delay/string
// fields at +0/+4/+8. Only the string field is destroyed by thunk 0x577998.
#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <list>
#include "ascii_string.h"

struct TreeKey00242F5E
{
    unsigned int delay_00;
    AsciiString boneName_04;
    TreeKey00242F5E(const TreeKey00242F5E &other);
};
struct BridgeBehaviorListValue12
{
    void *object_00;
    TreeKey00242F5E timeInfo_04;
    BridgeBehaviorListValue12(const BridgeBehaviorListValue12 &other);
    ~BridgeBehaviorListValue12();
};
typedef char VerifyBridgeBehaviorValueSize[(sizeof(BridgeBehaviorListValue12) == 12) ? 1 : -1];

__declspec(noinline) BridgeBehaviorListValue12::~BridgeBehaviorListValue12()
{
}

// Preserve retail's inline node/buffer free; the public allocator is supplied by its verified owner.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<_List_node< ::BridgeBehaviorListValue12 > >::deallocate(_List_node< ::BridgeBehaviorListValue12 > *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

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
