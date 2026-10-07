// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00524265@@QAE@XZ @0x00524265 47B
// Evidence: chain via rowed 0x00523FEC plus vector<AsciiString> dtor 0x0002CC70; dtor body does UI-erase loop then vector member dtor; callers 0x004E6B08 0x00524909 0x005D40EE etc; precedent Rva005241B0Dtor single-vector dtor shape.
#include <vector>

#include "ascii_string.h"

class Rva00524021
{
public:
	void rva00523FEC();
};

class Rva00524265
{
public:
	~Rva00524265();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
};

Rva00524265::~Rva00524265()
{
	((Rva00524021 *)this)->rva00523FEC();
}
