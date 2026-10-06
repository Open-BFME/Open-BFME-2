// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// Range-27 string reset plus notify.
// ?Rva00529E19@Holder00529E19@@QAEXXZ @0x00529E19 34B
// Thiscall stashes m_30, clears it, releases the m_34 string through
// the inlined StringBase clear (rowed releaseBuffer 0x00036410), zeroes
// the m_2C byte, and runs the pinned 0x00529DA9 member on the stashed
// value. Views TU-local.
#include "ascii_string.h"

struct Holder00529E19
{
	char m_pad[0x2C];
	unsigned char m_2C;
	char m_pad2D[3];
	int m_30;
	StringBase<char> m_34;
	void Rva00529DA9(int value);
	void Rva00529E19();
};

void Holder00529E19::Rva00529E19()
{
	int tmp = m_30;
	m_30 = 0;
	m_34.clear();
	m_2C = 0;
	Rva00529DA9(tmp);
}
