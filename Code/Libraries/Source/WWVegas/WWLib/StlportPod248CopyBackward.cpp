// cl: /DNDEBUG /MD
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
// full member layout lives in StlportPod248ElementDtor.cpp. No C8E19 insert
// attempted (bank 0.65 wall stands: 5-arg direct vs 4-arg wrapper + missing
// construct/copy/dtor/overflow providers). Pins are candidates only; the two
// byte gates are the proof.
#include <algorithm>

struct BfmePod248
{
	char m_pad[248];
	BfmePod248(const BfmePod248 &that);
	BfmePod248 &operator=(const BfmePod248 &that);
	~BfmePod248();
};

template BfmePod248 *_STL::__copy_backward(BfmePod248 *, BfmePod248 *, BfmePod248 *, const _STL::random_access_iterator_tag &, int *);
template BfmePod248 *_STL::__copy_backward_ptrs(BfmePod248 *, BfmePod248 *, BfmePod248 *, const _STL::__false_type &);
