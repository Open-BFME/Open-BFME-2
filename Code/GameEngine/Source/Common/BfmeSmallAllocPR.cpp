// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Og- /DZH_EMIT_POOL_GLUE /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

#define BFME_STLP_NODE_ALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define private public
#include "PreRTS.h"
#undef private

namespace _STL
{

#include "../../Include/Common/NodeAllocMutex.h"

}

#undef _STLP_STATIC_MUTEX
#define _STLP_STATIC_MUTEX NodeAllocMutex
#undef _STLP_MUTEX_INITIALIZER
#define _STLP_MUTEX_INITIALIZER
#define _STLP_EXPOSE_GLOBALS_IMPLEMENTATION 1
#include <stl/_alloc.c>
#undef _STLP_EXPOSE_GLOBALS_IMPLEMENTATION

// A local stand-in for the STLport lock guard.  The real template destructor
// compiles to a 25-byte /O2 body and lets the parent's frame shrink to 0x10,
// while this out-of-line 27-byte destructor is byte-identical to retail's
// _Node_Alloc_Lock<false,0>::~_Node_Alloc_Lock at 0x00024830 and keeps the
// parent's 0x14 frame.  Its cleanup funclet is rowed at 0x0075C850; the real
// <true,0> twin's pin at 0x00024850 records the STLport identity.
class BfmeNodeAllocLock : public _STL::_Node_Alloc_Lock<false, 0>
{
public:
	~BfmeNodeAllocLock()
	{
		int unused;
		(void)unused;
    }
};

// The matched STLport refill body is also known under this BFME alias at the
// retail address.  Calling the alias keeps the private-member decoration from
// being changed by the TU-local access exposure above.
extern void *bfmeSmallRefillPR(unsigned int bytes);

void *bfmeSmallAllocPR(unsigned int bytes)
{
	void *result;
	_STL::_Node_alloc_obj * volatile *my_free_list =
		_STL::__node_alloc<false, 0>::_S_free_list + ((bytes - 1) >> 3);
	BfmeNodeAllocLock lock_instance;
	if ((result = *my_free_list) != 0) {
		*my_free_list = ((_STL::_Node_alloc_obj *)result)->_M_free_list_link;
	} else {
		result = bfmeSmallRefillPR(bytes);
	}
	return result;
}
