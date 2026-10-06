// cl: /Ireference/shims/bfme2_ascii /MD
// ??4Rva002E0D93@@QAEAAV0@ABV0@@Z @0x002E0D93 233B.
// Honest copy-assign of 0xD8 record: 5 dwords plus 0x80 block via rep movsd then dword/byte members then sub-record assign then two StringBase set calls; returns *this.
// Evidence: sole caller 0x002E17A0 array copy (count = bytes/0xD8); callees rowed Rva001EAFC1::op= 0x001EAFC1 and StringBase<char>::set 0x000366F0; layout from retail offsets with Rva001EAFC1 0x18 per Rva001EAFC1Assign.cpp.
#include "ascii_string.h"

class Rva001EAFC1
{
public:
	Rva001EAFC1 &operator=(const Rva001EAFC1 &other);
private:
	int m_00;
	int m_04;
	int m_08;
	StringBase<unsigned short> m_0C;
	AsciiString m_10;
	unsigned char m_14;
};

struct Rva002E0D93Mid
{
	int m[32];
};

class Rva002E0D93
{
public:
	Rva002E0D93 &operator=(const Rva002E0D93 &other);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	Rva002E0D93Mid m_14;
	int m_94;
	int m_98;
	int m_9c;
	unsigned char m_a0;
	unsigned char m_a1;
	int m_a4;
	int m_a8;
	int m_ac;
	Rva001EAFC1 m_b0;
	int m_c8;
	int m_cc;
	StringBase<char> m_d0;
	StringBase<char> m_d4;
};
Rva002E0D93 &Rva002E0D93::operator=(const Rva002E0D93 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0c = other.m_0c;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_94 = other.m_94;
	m_98 = other.m_98;
	m_9c = other.m_9c;
	m_a0 = other.m_a0;
	m_a1 = other.m_a1;
	m_a4 = other.m_a4;
	m_a8 = other.m_a8;
	m_ac = other.m_ac;
	m_b0 = other.m_b0;
	m_c8 = other.m_c8;
	m_cc = other.m_cc;
	m_d0.set(other.m_d0);
	m_d4.set(other.m_d4);
	return *this;
}
