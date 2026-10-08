// cl: /O1 /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ??$__copy_backward@PAUBfmePod248@@PAU1@H@_STL@@YAPAUBfmePod248@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z @0x000C7977 54B.
// ??$__copy_backward_ptrs@PAUBfmePod248@@PAU1@@_STL@@YAPAUBfmePod248@@PAU1@00ABU__false_type@0@@Z @0x000C8369 29B.
// STLport copy_backward pair for the 248-byte Pod248 element via its native
// operator= at 0x000C6C54 (240B, ret 4, thiscall, returns this).
// Retail chain: wrapper 0xC8369 (29B, push 0 + lea tmp + 3 pushes + call
// 0xC7977) -> worker 0xC7977 (54B, (last-first)/0xF8 idiv loop calling
// 0xC6C54) -> native Pod248 operator= 0xC6C54 (240B, rep movsd 0x13 + member
// assigns + 6x vector60 assign via 0xBC3C4, ret 4). Stride 0xF8 proven by the
// idiv; bottom ABI proven by ret-4 + this-return + member-call pattern
// matching the rowed Pod248 dtor 0xC6D44 layout family; BfmePod248 is the
// size-derived opaque identifier from that row (primary 61182), not an
// original name. Footprint 248B view here preserves size/non-trivial ABI only;
// full member layout lives in StlportPod248ElementDtor.cpp. The insertion at
// 0xC8E19 calls these same providers, plus Construct 0xC78F3, copy 0xC6B17,
// destructor 0xC6D44 and overflow 0xC8D04. Its temporary needs the observed
// leading AsciiString for compiler-generated unwind cleanup; the remainder
// stays opaque. Original application identity remains unknown.
// Keep the original algorithm header: the allocator shim's replacement
// inlines the four-argument wrapper and changes the insertion's call ABI.
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include <algorithm>
#include "ascii_string.h"

struct BfmePod248
{
	AsciiString m_head;
	int m_opaque[61];
	BfmePod248(const BfmePod248 &that);
	BfmePod248 &operator=(const BfmePod248 &that);
	~BfmePod248();
};

namespace _STL {
template <> void _Construct<BfmePod248, BfmePod248>(BfmePod248 *, const BfmePod248 &);
}

#include <vector>

template BfmePod248 *_STL::__copy_backward(BfmePod248 *, BfmePod248 *, BfmePod248 *, const _STL::random_access_iterator_tag &, int *);
template BfmePod248 *_STL::__copy_backward_ptrs(BfmePod248 *, BfmePod248 *, BfmePod248 *, const _STL::__false_type &);

// Native boundary 0x000C8E19..0x000C8EEF (214B), immediately following
// the rowed push_back at 0xC8DDF. All calls resolve to the existing family.
template BfmePod248 *_STL::vector<BfmePod248>::insert(BfmePod248 *, const BfmePod248 &);
