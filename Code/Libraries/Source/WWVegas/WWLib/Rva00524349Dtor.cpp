// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00524349@@QAE@XZ @0x00524349 47B
// Evidence: chain via rowed 0x00524056 plus vector<AsciiString> dtor 0x0002CC70; dtor body does UI-erase loop then vector member dtor; callers 0x005248F1 0x0052A48B 0x005C79E7 etc; precedent Rva00524265Dtor single-vector dtor shape.
#include <vector>

#include "ascii_string.h"

class Rva00524021
{
public:
	void rva00524056();
};

class Rva00524349
{
public:
	~Rva00524349();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
};

Rva00524349::~Rva00524349()
{
	((Rva00524021 *)this)->rva00524056();
}
