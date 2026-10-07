// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /O1 /arch:SSE /G7
// ?rva003B2498@Rva003B2498@@QAEAAV1@ABV1@@Z at 0x003B2498 (47B). Address-derived copy method; target copies scalar fields at +0,+1,+4,+8 then StringBase<char> at +0x0C.
#include "ascii_string.h"

class Rva003B2498
{
public:
	Rva003B2498 &rva003B2498(const Rva003B2498 &other);

private:
	unsigned char m_00;
	unsigned char m_01;
	unsigned char pad02[2];
	int m_04;
	unsigned char m_08;
	unsigned char pad09[3];
	AsciiString m_string;
};

Rva003B2498 &Rva003B2498::rva003B2498(const Rva003B2498 &other)
{
	m_00 = other.m_00;
	m_01 = other.m_01;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_string = other.m_string;
	return *this;
}
