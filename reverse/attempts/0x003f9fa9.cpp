// ??0Rva003F9FA9@@QAE@ABVAsciiString@@@Z
// partial score=0.95 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva003F9FA9@@QAE@ABVAsciiString@@@Z @0x003F9FA9 61B.
// Ctor with AsciiString at +0x00, vector<BfmeE16> at +0x04 via rowed
// Vector_base 0x00211E58, six ints zeroed at +0x10..0x24 and -1 at
// +0x28/+0x2C (or under /O1). Evidence: adjacent to Rva003F9FE6 copy ctor
// 0x003F9FE6 (same SpecialPower TU pattern, same flags); caller 0x00214060
// news 0x30 bytes then calls this with AsciiString; callees rowed AsciiString
// copy 0x001D8F56 and Vector_base 0x00211E58; BfmeE16 is 16B per
// stlport_vector_e16_o1.cpp.
#include "ascii_string.h"
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva003F9FA9
{
public:
	Rva003F9FA9(const AsciiString &s);
private:
	AsciiString m_00;
	_STL::vector<BfmeE16> m_04;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
};

// ??0Rva003F9FA9@@QAE@ABVAsciiString@@@Z present-unmatched
Rva003F9FA9::Rva003F9FA9(const AsciiString &s)
	: m_00(s)
	, m_04(_STL::allocator<BfmeE16>())
	, m_10(0)
	, m_14(0)
	, m_18(0)
	, m_1C(0)
	, m_20(0)
	, m_24(0)
{
	m_28 = -1;
	m_2C = -1;
}
