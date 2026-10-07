// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva004BA1C8@@QAE@XZ, retail 0x004BA1C8 8B: add ecx,4 then jmp to vector<AsciiString> dtor at 0x0002CC70.
// Evidence: callees all rowed; callers at 0x004BA2D0 and 0x004BA34A plus jmp at 0x004BA31F; shares 0x2C layout
// with copy ctor at 0x004BA1D0 and assign at 0x004BA291 which both use vector<AsciiString> at +4.
#include <vector>

#include "ascii_string.h"


class Rva004BA1C8Triple {
public:
	unsigned int a;
	unsigned int b;
	unsigned int c;
};

class Rva004BA1C8 {
public:
	~Rva004BA1C8();
	Rva004BA1C8 &operator=(const Rva004BA1C8 &other);
private:
	int m_00;
	_STL::vector<AsciiString> m_04;
	unsigned int m_10;
	Rva004BA1C8Triple m_14;
	Rva004BA1C8Triple m_20;
};

Rva004BA1C8::~Rva004BA1C8()
{
}

Rva004BA1C8 &Rva004BA1C8::operator=(const Rva004BA1C8 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_20 = other.m_20;
	return *this;
}

void Rva004BA341DestroyRange(Rva004BA1C8 *first, Rva004BA1C8 *last)
{
	for (; first != last; ++first)
		first->~Rva004BA1C8();
}

extern "C" void __cdecl free(void *block);

class Rva004BA3CC {
	Rva004BA1C8 *m_first;
	Rva004BA1C8 *m_last;
public:
	void clear();
};

void Rva004BA3CC::clear()
{
	Rva004BA341DestroyRange(m_first, m_last);
	if (m_first)
		free(m_first);
}

Rva004BA1C8 *Rva004BA2E9Copy(Rva004BA1C8 *first, Rva004BA1C8 *last, Rva004BA1C8 *out)
{
	int n = last - first;
	if (n <= 0)
		return out;
	for (int i = n; i != 0; --i) {
		*out = *first;
		++first;
		++out;
	}
	return out;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??$__copy@PAVRva004BA1C8@@PAV1@H@_STL@@YAPAVRva004BA1C8@@PAV1@00ABUrandom_access_iterator_tag@0@PAH@Z=?Rva004BA2E9Copy@@YAPAVRva004BA1C8@@PAV1@00@Z")
