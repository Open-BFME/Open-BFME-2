// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva001ED0DE@@QAE@XZ @0x001ED0DE 92B.
// Non-virtual dtor: vector<Rva001EC349> at +0x18, vector<AsciiString> at +0x0C, three strings at +0x08..+0x00.
// Evidence: callees rowed 0x001ECFDF 0x0002CC70 0x00036410(x3); callers 0x001ED26C 0x001ED353 0x001ED5FF.
#include <vector>

#include "ascii_string.h"


class Rva001EC349
{
public:
	~Rva001EC349();
};

class Rva001ED0DE
{
public:
	~Rva001ED0DE();
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_0C;
	_STL::vector<Rva001EC349, _STL::allocator<Rva001EC349> > m_18;
};

Rva001ED0DE::~Rva001ED0DE()
{
}
