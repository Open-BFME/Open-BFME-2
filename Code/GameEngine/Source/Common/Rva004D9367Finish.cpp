// ?Rva004D9367Less@@YAEPBURva004D9367Key@@0@Z
// partial score=0.94 date=2026-10-04
// cl: /DNDEBUG /MD /EHsc
// ?Rva004D9367Less@@YAEPBURva004D9367Key@@0@Z, retail 0x004D9367, 78 bytes.
// Strict-less on 0x14-byte key: m0 then flag m4 selects m8/mC vs m10 path.
// Evidence: callers 0x004D93B5 (inequality via both orders) and 0x004DBC04; neighbours 0x004D9362/0x004D93F7.
struct Rva004D9367Key
{
	int m0;
	unsigned char m4;
	char m_pad[3];
	int m8;
	int mC;
	int m10;
};
unsigned char __cdecl Rva004D9367Less(Rva004D9367Key const *a, Rva004D9367Key const *b)
{
	if (a->m0 < b->m0)
		return 1;
	if (a->m0 > b->m0)
		return 0;
	if (a->m4 != 0) {
		if (b->m4 == 0)
			return 0;
		if (a->m8 < b->m8)
			return 1;
		if (a->m8 <= b->m8)
			return (unsigned char)(a->mC > b->mC);
		return 0;
	}
	if (b->m4 != 0)
		return 1;
	return (unsigned char)(a->m10 < b->m10);
}

#pragma auto_inline(off)
int __cdecl Rva004D93B5NotEqual(Rva004D9367Key const *a, Rva004D9367Key const *b)
{
	if (Rva004D9367Less(a, b) || Rva004D9367Less(b, a))
		return 1;
	return 0;
}
#pragma auto_inline(on)

#pragma auto_inline(off)
int __cdecl Rva004D93E2Equal(Rva004D9367Key const *a, Rva004D9367Key const *b)
{
	return !(unsigned char)Rva004D93B5NotEqual(a, b);
}
#pragma auto_inline(on)
