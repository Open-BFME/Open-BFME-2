// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0021F804@@QAE@ABVAsciiString@@0000@Z @0x0021F804 114B. Five-string
// ctor: m_00/m_04/m_08/m_0C from params 2-5 and m_10 from param 1 plus
// default vector<BfmeE16> at +0x14 via rowed _Vector_base 0x00211E58.
// Evidence: caller 0x0022032A plus rowed StringBase copy 0x000365F0 x5 and
// EH states 0-3 with ret 0x14 and lea eax [ebp+0xF] allocator byte.

#include "ascii_string.h"
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva0021F804
{
public:
	Rva0021F804(const AsciiString &a4, const AsciiString &a0, const AsciiString &a1, const AsciiString &a2, const AsciiString &a3);
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	AsciiString m_10;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_14;
};

Rva0021F804::Rva0021F804(const AsciiString &a4, const AsciiString &a0, const AsciiString &a1, const AsciiString &a2, const AsciiString &a3)
	: m_00(a0)
	, m_04(a1)
	, m_08(a2)
	, m_0C(a3)
	, m_10(a4)
	, m_14()
{
}
