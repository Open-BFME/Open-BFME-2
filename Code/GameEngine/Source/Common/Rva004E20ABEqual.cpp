// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?rva004E20AB@@YA_NPBURva004E20ABRec@@0@Z @0x004E20AB 76B.
// Three-string-plus-flag equality: rowed StringBase compare 0x00069D6 on
// the +0x04/+0x08/+0x0C members (each must compare equal) and the +0x10 flag
// byte, as one AND chain sharing the xor epilogue with return-1 out of the
// zeroed eax as inc eax. Bind the four-byte string storage directly to
// the retail StringBase<char> owner; no AsciiString wrapper is needed.
#include "ascii_string.h"

struct Rva004E20ABRec
{
	char m_pad[4];
	StringBase<char> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0C;
	unsigned char m_10;
};

bool rva004E20AB(const Rva004E20ABRec *lhs, const Rva004E20ABRec *rhs)
{
	return lhs->m_04.compare(rhs->m_04) == 0
		&& lhs->m_08.compare(rhs->m_08) == 0
		&& lhs->m_0C.compare(rhs->m_0C) == 0
		&& lhs->m_10 == rhs->m_10;
}
