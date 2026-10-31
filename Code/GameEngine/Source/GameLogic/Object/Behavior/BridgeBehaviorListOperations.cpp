// cl: /G7 /arch:SSE /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/sweep /Ireference/shims/bfmealloc /Ivendor/stlport /Ireference/shims/asciistring_outofline /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /O1
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Genuine STLport insertion for the shared BridgeDieFX/OCL list shape.
// Target nodes contain two links and the verified 12-byte value. The allocator
// takes the byte count and a null hint; the original folded type owner is unknown.
#include <list>
#include "Common/AsciiString.h"

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

// Retail keeps this list's node construction out of line: insert 0x00457552 calls 0x0045741F.
namespace _STL {
template <>
inline __declspec(noinline) list<BridgeBehaviorListValue12, allocator<BridgeBehaviorListValue12> >::_Node *
list<BridgeBehaviorListValue12, allocator<BridgeBehaviorListValue12> >::_M_create_node(const BridgeBehaviorListValue12 &__x)
{
	_Node *__p = this->_M_node.allocate(1);
	_Construct(&__p->_M_data, __x);
	return __p;
}
}

typedef std::list<BridgeBehaviorListValue12> BridgeBehaviorList12;

// ?ForceBridgeBehaviorPushBack@@YAXAAV?$list@UBridgeBehaviorListValue12@@V?$allocator@UBridgeBehaviorListValue12@@@_STL@@@_STL@@ABUBridgeBehaviorListValue12@@@Z absent-from-retail
__declspec(noinline) void ForceBridgeBehaviorPushBack(
	BridgeBehaviorList12 &list, const BridgeBehaviorListValue12 &value)
{
	list.push_back(value);
}

// ?ForceBridgeBehaviorInsert@@YA?AU?$_List_iterator@UBridgeBehaviorListValue12@@U?$_Nonconst_traits@UBridgeBehaviorListValue12@@@_STL@@@_STL@@AAV?$list@UBridgeBehaviorListValue12@@V?$allocator@UBridgeBehaviorListValue12@@@_STL@@@2@U12@ABUBridgeBehaviorListValue12@@@Z absent-from-retail
__declspec(noinline) BridgeBehaviorList12::iterator ForceBridgeBehaviorInsert(
	BridgeBehaviorList12 &list, BridgeBehaviorList12::iterator position,
	const BridgeBehaviorListValue12 &value)
{
	return list.insert(position, value);
}
