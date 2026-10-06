// cl: /Ireference/shims/bfmelist /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
// ??0Rva0055B0CC@@QAE@ABV0@@Z @0x0055B182 166B: user-written copy constructor
// of the opaque owner whose ctor/dtor are the rowed 0x0055B048/0x0055B0CC
// (layout from Rva0055B048Ctor.cpp; vtable 0x00C6B900). It copies the scalars
// and the AsciiString at +0x0C, default-constructs both int lists (EH states
// 0/1), resets m_20 to true, copies the trailing fields, then assigns both
// lists through the rowed list<int>::operator= 0x002C54EE. Caller: the rowed
// Rva00573B23 copy 0x00573AC8. Identity is address-derived.
#include <list>
#include "ascii_string.h"

class Rva0055B0CC
{
public:
	Rva0055B0CC(const Rva0055B0CC &other);
	virtual ~Rva0055B0CC();

private:
	float m_04;
	int m_08;
	AsciiString m_0C;
	unsigned int m_10;
	_STL::list<int, _STL::allocator<int> > m_14;
	float m_18;
	_STL::list<int, _STL::allocator<int> > m_1C;
	bool m_20;
	bool m_21;
	int m_24;
	bool m_28;
};

Rva0055B0CC::Rva0055B0CC(const Rva0055B0CC &other) :
	m_04(other.m_04),
	m_08(other.m_08),
	m_0C(other.m_0C),
	m_10(other.m_10),
	m_18(other.m_18),
	m_20(true),
	m_21(other.m_21),
	m_24(other.m_24),
	m_28(other.m_28)
{
	m_14 = other.m_14;
	m_1C = other.m_1C;
}
