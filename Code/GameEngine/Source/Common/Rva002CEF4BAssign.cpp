// cl: /O1 /MD /EHsc
// ??4Rva002CEF4B@@QAEAAU0@ABU0@@Z, RVA 0x002CEF4B, 33B.
// Copy-assignment copying an AsciiString member at +0 via pinned
// ??4AsciiString@@QAEAAV0@ABV0@@Z then setting a wide-string member at +4
// via pinned ?set@?$StringBase@G@@QAEXABV1@@Z, returning this with ret 4.
// Six callers inside 0x002D1101 prove the thiscall assign shape; owning
// class is otherwise unproven, so the honest address name stands.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"


struct Rva002CEF4B
{
	AsciiString m_name; // +0
	StringBase<unsigned short> m_wide; // +4
	Rva002CEF4B &operator=(const Rva002CEF4B &other);
};

Rva002CEF4B &Rva002CEF4B::operator=(const Rva002CEF4B &other)
{
	m_name = other.m_name;
	m_wide.set(other.m_wide);
	return *this;
}
