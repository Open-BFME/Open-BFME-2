// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ??4Rva000B419E@@QAEAAU0@ABU0@@Z @0x000B419E 81B: copy-assignment for 32B struct with AsciiString at +0 plus 28B tail.
// Evidence: thiscall ret 4 returning this; rowed AsciiString::operator= 0x000366F0 on +0 then 6 dword plus 4 byte copies; same flags as StlportFixedObject60Copy sibling; caller 0x000BDC2C on list node data; unblocks 0x000BDBFA.
#include "ascii_string.h"

struct Rva000B419E
{
	AsciiString m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	unsigned char m_1c;
	unsigned char m_1d;
	unsigned char m_1e;
	unsigned char m_1f;
	Rva000B419E &operator=(const Rva000B419E &rhs);
};

Rva000B419E &Rva000B419E::operator=(const Rva000B419E &rhs)
{
	m_00 = rhs.m_00;
	m_04 = rhs.m_04;
	m_08 = rhs.m_08;
	m_0c = rhs.m_0c;
	m_10 = rhs.m_10;
	m_14 = rhs.m_14;
	m_18 = rhs.m_18;
	m_1c = rhs.m_1c;
	m_1d = rhs.m_1d;
	m_1e = rhs.m_1e;
	m_1f = rhs.m_1f;
	return *this;
}
