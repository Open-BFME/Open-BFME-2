// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?rva004E20AB@@YA_NPBURva004E20ABRec@@0@Z @0x004E20AB 76B.
// Three-AsciiString-plus-flag equality: rowed StringBase compare 0x00069D6 on
// the +0x04/+0x08/+0x0C members (each must compare equal) and the +0x10 flag
// byte, as one AND chain sharing the xor epilogue with return-1 out of the
// zeroed eax as inc eax.
#include "ascii_string.h"

struct Rva004E20ABRec
{
	char m_pad[4];
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	unsigned char m_10;
};

bool rva004E20AB(const Rva004E20ABRec *a, const Rva004E20ABRec *b)
{
	return a->m_04.compare(b->m_04) == 0
		&& a->m_08.compare(b->m_08) == 0
		&& a->m_0C.compare(b->m_0C) == 0
		&& a->m_10 == b->m_10;
}
