// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Owning vector teardown for BfmeContainerRecord00048139 at 0x004B193.
// The three sibling bodies live in StringContainerRecordVector.cpp
// (record dtor 0x00470A0, _Destroy range 0x004A9F3, owning range 0x004B205).
// This TU instantiates the STLport vector itself: EH frame over the
// _Destroy call through rowed 0x004A9F3 plus the conditional buffer free
// through rowed _free at 0x0030830. Retail carries the extra
// `or [ebp-4],-1` state store that /EHsc omits; /GX emits it (63 bytes).
// Split from the sibling TU per the per-function-flags law: the sibling
// stays /EHsc green, this shard takes /GX.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

#include "ascii_string.h"


struct BfmeContainerRecord00048139 {
	AsciiString text0;
	AsciiString text1;
	unsigned char m_pad[0x5C - 8];
	BfmeContainerRecord00048139();
	BfmeContainerRecord00048139(const BfmeContainerRecord00048139 &other);
	BfmeContainerRecord00048139 &operator=(const BfmeContainerRecord00048139 &other);
	~BfmeContainerRecord00048139();
};

// BfmeContainerRecord00048139::~BfmeContainerRecord00048139: defined in StringContainerRecordVector.cpp (its row's unit).

// ??1?$vector@UBfmeContainerRecord00048139@@V?$allocator@UBfmeContainerRecord00048139@@@_STL@@@_STL@@QAE@XZ @0x004B193
template class _STL::vector<BfmeContainerRecord00048139, _STL::allocator<BfmeContainerRecord00048139> >;
