// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva004E2CF7Equal@@YAHPBURva004E2CF7Data@@0@Z @0x004E2CF7 (348B): multi-string plus float plus range equal.
// Compares dword +0x4C then StringBase members via rowed compare 0x000069D6 then
// floats +0x20 +0x24 +0x44 via ucomiss then strings then byte +0x54 then string +0x50
// then dword +0x48 then range +0x38 via just-landed Rva002ADD75Equal 0x002ADD75
// then byte +0x55 returning int 1/0. Same tail shape as sibling Rva002AAC9EEqual.
// No callers. Prev Rva004E2CD5Contains next Rva004E2E58 dtor.
#include "ascii_string.h"

struct AsciiRange002ADD75
{
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
};

int __cdecl Rva002ADD75Equal(const AsciiRange002ADD75 *a, const AsciiRange002ADD75 *b);

struct Rva004E2CF7Data
{
	char _00[4];
	StringBase<char> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0C;
	StringBase<char> m_10;
	StringBase<char> m_14;
	StringBase<char> m_18;
	StringBase<char> m_1C;
	float m_20;
	float m_24;
	StringBase<char> m_28;
	StringBase<char> m_2C;
	StringBase<char> m_30;
	StringBase<char> m_34;
	AsciiRange002ADD75 m_38;
	char _40[4];
	float m_44;
	int m_48;
	int m_4C;
	StringBase<char> m_50;
	unsigned char m_54;
	unsigned char m_55;
};

int __cdecl Rva004E2CF7Equal(const Rva004E2CF7Data *a, const Rva004E2CF7Data *b)
{
	if (a->m_4C == b->m_4C
		&& a->m_04.compare(b->m_04) == 0
		&& a->m_08.compare(b->m_08) == 0
		&& a->m_18.compare(b->m_18) == 0
		&& a->m_0C.compare(b->m_0C) == 0
		&& a->m_10.compare(b->m_10) == 0
		&& a->m_14.compare(b->m_14) == 0
		&& a->m_1C.compare(b->m_1C) == 0
		&& a->m_20 == b->m_20
		&& a->m_24 == b->m_24
		&& a->m_28.compare(b->m_28) == 0
		&& a->m_2C.compare(b->m_2C) == 0
		&& a->m_30.compare(b->m_30) == 0
		&& a->m_34.compare(b->m_34) == 0
		&& a->m_54 == b->m_54
		&& a->m_50.compare(b->m_50) == 0
		&& a->m_44 == b->m_44
		&& a->m_48 == b->m_48
		&& (unsigned char)Rva002ADD75Equal(&a->m_38, &b->m_38)
		&& a->m_55 == b->m_55)
		return 1;
	return 0;
}
