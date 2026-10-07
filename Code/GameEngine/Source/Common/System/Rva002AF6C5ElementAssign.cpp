// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??4Rva002AF6C5Element@@QAEAAU0@ABU0@@Z, retail 0x002AF505, 57 bytes.
// Copy-assignment over the 0x24-byte element: AsciiString at +0 via rowed
// AsciiString op= 0x366F0, int at +4, 4-byte-POD vector at +8 via folded
// 0x26F4F4 (vector<int> spelling), AsciiString vector at +0x14 via rowed
// 0xBDB46, int at +0x20. Evidence: matched copy-loop caller at 0x002AF6E1
// (Rva002AF6C5CopyLoop.cpp) names this pin; neighbours FamilyDeletingDtors.
#include <vector>

#include "ascii_string.h"

struct Rva002AF6C5Element
{
	AsciiString m_00;
	int m_04;
	_STL::vector<unsigned int> m_08;
	_STL::vector<AsciiString> m_14;
	int m_20;

	Rva002AF6C5Element &operator=(const Rva002AF6C5Element &other);
};

Rva002AF6C5Element &Rva002AF6C5Element::operator=(const Rva002AF6C5Element &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_14 = other.m_14;
	m_20 = other.m_20;
	return *this;
}
