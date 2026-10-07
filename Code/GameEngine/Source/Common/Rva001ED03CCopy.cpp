// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva001ED03C@@QAE@ABV0@@Z, retail 0x001ED03C, 109 bytes.
// Evidence: unlock lane copy ctor; callees rowed StringBase 0x000365F0 vector 0x000BC07E Rva001ECF66 0x001ECF66; caller 0x001ED20D.
#include <vector>

#include "ascii_string.h"

class Rva001ECF66
{
public:
	Rva001ECF66(const Rva001ECF66 &o);
};

class Rva001ED03C
{
public:
	Rva001ED03C(const Rva001ED03C &o);
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_0c;
	Rva001ECF66 m_18;
};

Rva001ED03C::Rva001ED03C(const Rva001ED03C &o)
	: m_00(o.m_00),
	  m_04(o.m_04),
	  m_08(o.m_08),
	  m_0c(o.m_0c),
	  m_18(o.m_18)
{
}
