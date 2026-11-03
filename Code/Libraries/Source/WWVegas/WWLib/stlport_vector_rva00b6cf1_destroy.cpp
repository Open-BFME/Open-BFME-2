// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAURva00B6CF1@@@_STL@@YAXPAURva00B6CF1@@0@Z, retail 0x000BDCD6, 25 bytes.
// Range destroy for the 8-byte Rva00B6CF1 element (two StringBase releases
// at +0/+4, dtor at 0xB6CF1): strides 8 calling that dtor. Same 25B loop
// shape as rowed Rva0048130E _Destroy at 0x00481595 (53B twin dtor at
// 0x48130E, QAE non-virtual, no vptr store). The existing UAE pin at
// 0xB6CF1 carries the wrong virtualness (body stores no vptr); the QAE
// twin pin added beside this TU corrects it per the ICF-twin plus call
// site (BDCD6 calls B6CF1 as 481595 calls 48130E). Emitted via explicit
// _Destroy instantiation over an opaque 8-byte view declaring the twin
// dtor; callers at 0xC03F2/0xC05D6/0xC0647/0xC0804/0xC0986 unblock C03D8.
#include <vector>
#include <algorithm>

#include "ascii_string.h"

#include "../../../../GameEngine/Include/Common/BfmeStringRecord000B94D2.h"

struct Rva00B6CF1
{
	~Rva00B6CF1();
	Rva00B6CF1 &operator=(const Rva00B6CF1 &other);

	AsciiString m_s0;
	AsciiString m_s1;
};

namespace _STL
{
template <>
inline void _Destroy<Rva00B6CF1 *>(Rva00B6CF1 *first, Rva00B6CF1 *last)
{
	for (; first != last; ++first)
		reinterpret_cast<BfmeStringRecord000B94D2 *>(first)->~BfmeStringRecord000B94D2();
}
}

template _STL::vector<Rva00B6CF1>::~vector();

// The same record under its other placeholder name: the copy constructor
// 0x000BCDBF is rowed as vector<BfmeStringRecord000B94D2>, and BfmePod252's
// copy constructor (0x000C254B, unwind state 4) destroys that +0x64 member
// through 0x000C03D8. Both names fold onto the 63B dtor and the 25B range
// destroy above (fold-proof pins in reverse/symbols.csv).
template _STL::vector<BfmeStringRecord000B94D2>::~vector();

Rva00B6CF1 &Rva00B6CF1::operator=(const Rva00B6CF1 &other)
{
	m_s0 = other.m_s0;
	m_s1 = other.m_s1;
	return *this;
}

// ??$__copy@PAURva00B6CF1@@PAU1@H@_STL@@YAPAURva00B6CF1@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z @0x000B6894 47B
// Forward __copy stride 8 via rowed ??4Rva00B6CF1 at 0xB433E; wrapper at 0xB67BC pushes tag plus distance.
template Rva00B6CF1 *_STL::__copy<Rva00B6CF1 *, Rva00B6CF1 *, int>(Rva00B6CF1 *, Rva00B6CF1 *, Rva00B6CF1 *, const _STL::random_access_iterator_tag &, int *);

template void _STL::_Destroy<Rva00B6CF1 *>(Rva00B6CF1 *, Rva00B6CF1 *);
