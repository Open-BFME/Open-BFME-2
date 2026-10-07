// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004BA1D0@@QAE@ABV0@@Z, retail 0x004BA1D0 73B: copy ctor for the 0x2C record with vector<AsciiString> at +4.
// Evidence: callees all rowed (vector copy ctor at 0x000BC07E); callers at 0x004BA235 and 0x004BAAC3; shares layout
// with dtor at 0x004BA1C8 and assign at 0x004BA291 (vector at +4 plus seven trailing dwords).
#include <vector>

#include "ascii_string.h"


class Rva004BA1D0 {
public:
	Rva004BA1D0(const Rva004BA1D0 &other);
private:
	int m_00;
	_STL::vector<AsciiString> m_04;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1C;
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
};

Rva004BA1D0::Rva004BA1D0(const Rva004BA1D0 &other)
	: m_00(other.m_00),
	  m_04(other.m_04),
	  m_10(other.m_10),
	  m_14(other.m_14),
	  m_18(other.m_18),
	  m_1C(other.m_1C),
	  m_20(other.m_20),
	  m_24(other.m_24),
	  m_28(other.m_28)
{
}
