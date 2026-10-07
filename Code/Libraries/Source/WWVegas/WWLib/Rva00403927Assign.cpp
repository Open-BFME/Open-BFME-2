// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Copy assignment (35B) of the stride-0x14 element served by the __copy loop at
// 0x004039E0 (count via idiv 0x14, per-element call) and its 29B forwarding wrapper
// at 0x00403BD2: two scalar words, then a vector<AsciiString> at +8 assigned through
// the rowed operator= 0x000BDB46. Copy ctor ??0Rva00403927@@QAE@ABV0@@Z 35B @0x004039BD
// same layout via rowed vector copy ctor 0x000BC07E unblocks 0x00403B5A.
// Application identity unknown, so an Rva owner name is used. Frameless /O1 matches
// retail (opens with mov eax,[esp+4]).
#include "ascii_string.h"
#include <vector>

class Rva00403927 {
public:
	Rva00403927(const Rva00403927 &other);
	Rva00403927 &operator=(const Rva00403927 &other);
private:
	int m_00;
	int m_04;
	_STL::vector<AsciiString> m_names;
};

Rva00403927::Rva00403927(const Rva00403927 &other)
	: m_00(other.m_00), m_04(other.m_04), m_names(other.m_names)
{
}

// ??4Rva00403927@@QAEAAV0@ABV0@@Z @0x00403927
Rva00403927 &Rva00403927::operator=(const Rva00403927 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_names = other.m_names;
	return *this;
}
