// cl: /Ob0
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva001BDA20Set.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?set@Rva001BDA20@@QAEXABVRva0036CA00Str@@@Z 0x000B28A5 (26B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

// The element is a narrow string handle: retail assigns it through the rowed
// StringBase<char>::set 0x000366F0 (the refcounted Rva0036CA00Str handle's own
// assignment is OpaqueRefElement4::operator= 0x00239099, see Rva00403055CopyCtor.cpp).
template <class T> class StringBase
{
public:
	void set(const StringBase<T> &src);
};
#define BFME_STR_SET(dst, src) ((StringBase<char> &)(dst)).set((const StringBase<char> &)(src))

#include "../../Include/Common/Rva0036CA00Str.h"

class Rva001BDA20
{
	char m_00[0x10];
	Rva0036CA00Str m_10;
	int m_14;

public:
	void set(const Rva0036CA00Str &s);
};

void Rva001BDA20::set(const Rva0036CA00Str &s)
{
	BFME_STR_SET(m_10, s);
	m_14 = 4;
}
