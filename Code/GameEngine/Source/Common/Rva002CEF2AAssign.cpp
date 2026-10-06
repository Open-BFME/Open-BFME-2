// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??4Rva002CEF2A@@QAEAAU0@ABU0@@Z, RVA 0x002CEF2A, 33B.
// Copy-assignment copying an AsciiString member at +0 via pinned
// ??4AsciiString@@QAEAAV0@ABV0@@Z then dwords at +4 and +8, returning this
// with ret 4. Callers at 0x002D1121 and 0x002D112D inside 0x002D1101 prove
// the thiscall shape; owning class is otherwise unproven, so the honest
// address name stands.
#include "ascii_string.h"

struct Rva002CEF2A
{
	AsciiString m_name; // +0
	int m_4; // +4
	int m_8; // +8
	Rva002CEF2A &operator=(const Rva002CEF2A &other);
};

Rva002CEF2A &Rva002CEF2A::operator=(const Rva002CEF2A &other)
{
	m_name = other.m_name;
	m_4 = other.m_4;
	m_8 = other.m_8;
	return *this;
}
