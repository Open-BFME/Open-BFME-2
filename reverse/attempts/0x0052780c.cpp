// ?Rva0052780C@@YAXPAUPair0052780C@@DH@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /MD
// Range-27 byte/int pair packer.
// ?Rva0052780C@@YAXPAUPair0052780C@@DH@Z @0x0052780C 27B
// Cdecl free function packing (b, c) into *out: the byte rides a
// char/int union slot (byte store, dword read) into m_0, the int goes
// straight to m_4.
union ByteDword0052780C
{
	char m_b;
	__int64 m_x;
};

struct Pair0052780C
{
	int m_0;
	int m_4;
};

void Rva0052780C(Pair0052780C *out, char b, int c)
{
	ByteDword0052780C slot;
	slot.m_b = b;
	int cval = c;
	out->m_0 = (int)slot.m_x;
	out->m_4 = cval;
}
