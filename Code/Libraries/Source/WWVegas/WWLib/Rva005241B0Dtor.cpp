// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva005241B0@@QAE@XZ @0x005241B0 47B
// Evidence: chain via rowed 0x00523F57 plus vector<AsciiString> dtor 0x0002CC70; dtor body does UI-erase loop then vector member dtor; callers 0x004E6B14 0x0050ED89 0x00524921 etc; precedent Rva005242D7Chain single-vector dtor shape.
#include <vector>

#include "ascii_string.h"

class Rva00524021
{
public:
	void rva00523F57();
};

class Rva005241B0
{
public:
	~Rva005241B0();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
};

Rva005241B0::~Rva005241B0()
{
	((Rva00524021 *)this)->rva00523F57();
}
