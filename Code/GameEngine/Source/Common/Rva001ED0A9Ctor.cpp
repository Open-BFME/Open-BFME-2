// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva001ED0A9@@QAE@ABVAsciiString@@@Z @0x001ED0A9 53B.
// Ctor: AsciiString at +0 via pinned 0x000365F0, ints at +4/+8 zeroed, two vector<BfmeE16> bases via rowed 0x00211E58.
// Evidence: callees pinned 0x000365F0 plus rowed 0x00211E58(x2); caller 0x001ED5E0 in 0x001ED580.
#include <vector>

#include "ascii_string.h"


struct BfmeE16 { int a[4]; };

class Rva001ED0A9
{
public:
	Rva001ED0A9(const AsciiString &s);
private:
	AsciiString m_00;
	int m_04;
	int m_08;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_0C;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_18;
};

Rva001ED0A9::Rva001ED0A9(const AsciiString &s)
	: m_00(s),
	  m_04(0),
	  m_08(0)
{
}
