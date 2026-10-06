// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ??4Rva00564E0D@@QAEAAV0@AAV0@@Z, retail 0x000898B0, 92 bytes.
// Copy-assignment for Rva00564E0D (AsciiString at +0xC via Pad0C head).
// Evidence: self-assignment guard (cmp this/param, je), rowed AsciiString
// getter 0x00564E0D into temp + set 0x000366F0 + releaseBuffer 0x00036410
// with EH states, 3x movsd head copy, int at +0x10, return *this.
// Layout from Rva00564E0DGetter.cpp (Pad0C + m_str); int at +0x10 proven by
// retail mov [ebx+0x10]. Callers in FUN_0048A2EF.
#include "ascii_string.h"

struct Rva00564E0DHead
{
	int m_00;
	int m_04;
	int m_08;
};

class Rva00564E0D
{
public:
	AsciiString rva00564E0D();
	Rva00564E0D &operator=(Rva00564E0D &other);

private:
	Rva00564E0DHead m_head;
	AsciiString m_str;
	int m_10;
};

Rva00564E0D &Rva00564E0D::operator=(Rva00564E0D &other)
{
	if (this != &other)
	{
		m_str = other.rva00564E0D();
		m_head = other.m_head;
		m_10 = other.m_10;
	}
	return *this;
}
