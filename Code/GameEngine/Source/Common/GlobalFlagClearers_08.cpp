// Sixteen B2-native flag-word clearers sharing one shape:
//
//     mov eax,[<address>] / and al|ah,<mask8> / mov [<address>],eax / ret
//
// All sixteen clear one bit of the same .data flag word g_Va00DFEFA0: bits
// 0-7 through al, bits 8-15 through ah. The matching BFME1 donor family
// (GlobalFlagClearers_04.cpp) only ever emits the eax form (`and eax,imm`),
// fourteen bytes for an imm8-encodable mask; these sixteen need the
// byte-register narrowing (`and al,imm8` / `and ah,imm8`), thirteen and
// fourteen bytes. That narrowing is a /G7 (Pentium 4 target) peephole:
// the identical source under the default /O2 emits `and eax,imm8`, under
// /G6 it stays `and eax,imm8`, and only /G7 narrows to al/ah (probe-proven
// for all three encodings). Hence this TU carries `// cl: /G7` while the
// sibling clearers build at defaults. Each body was placed by whole-.text
// shape walk over one contiguous run (0x776C65-0x776D3C) with VA-consistency
// (both address slots agree), ret termination, a free interval, and -- for
// every body -- a .rdata function-table slot pointing at it (0x91E688 and
// on, stride 8). Identity is not recovered; every name is derived from an
// address, following GlobalFlagClearers_06.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFEFA0;
extern unsigned int g_Va00E02F24;
extern unsigned int g_Va00E040B0;

unsigned int Rva00776C65ClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFFFFEu;
}

unsigned int Rva00776C72ClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFFFFDu;
}

unsigned int Rva00776C7FClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFFFFBu;
}

unsigned int Rva00776C8CClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFFFF7u;
}

unsigned int Rva00776C99ClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFFFEFu;
}

unsigned int Rva00776CA6ClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFFFDFu;
}

unsigned int Rva00776CB3ClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFFFBFu;
}

unsigned int Rva00776CC0ClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFFF7Fu;
}

unsigned int Rva00776CCDClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFFEFFu;
}

unsigned int Rva00776CDBClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFFDFFu;
}

unsigned int Rva00776CE9ClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFFBFFu;
}

unsigned int Rva00776CF7ClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFF7FFu;
}

unsigned int Rva00776D05ClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFEFFFu;
}

unsigned int Rva00776D13ClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFDFFFu;
}

unsigned int Rva00776D21ClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFFBFFFu;
}

unsigned int Rva00776D2FClearFlag(void)
{
	return g_Va00DFEFA0 &= 0xFFFF7FFFu;
}

unsigned int Rva00784B8EClearFlag(void)
{
	return g_Va00E02F24 &= 0xFFFFFFFEu;
}

unsigned int Rva00784B9BClearFlag(void)
{
	return g_Va00E02F24 &= 0xFFFFFFFDu;
}

unsigned int Rva00784BA8ClearFlag(void)
{
	return g_Va00E02F24 &= 0xFFFFFFFBu;
}

unsigned int Rva00784BB5ClearFlag(void)
{
	return g_Va00E02F24 &= 0xFFFFFFF7u;
}

unsigned int Rva00784BC2ClearFlag(void)
{
	return g_Va00E02F24 &= 0xFFFFFFEFu;
}

unsigned int Rva00784BCFClearFlag(void)
{
	return g_Va00E02F24 &= 0xFFFFFFDFu;
}

unsigned int Rva00784BDCClearFlag(void)
{
	return g_Va00E02F24 &= 0xFFFFFFBFu;
}

unsigned int Rva00784BF1ClearFlag(void)
{
	return g_Va00E02F24 &= 0xFFFFFF7Fu;
}

unsigned int Rva0078F8BCClearFlag(void)
{
	return g_Va00E040B0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F8C9ClearFlag(void)
{
	return g_Va00E040B0 &= 0xFFFFFFFDu;
}

unsigned int Rva0078F8D6ClearFlag(void)
{
	return g_Va00E040B0 &= 0xFFFFFFFBu;
}

unsigned int Rva0078F8E3ClearFlag(void)
{
	return g_Va00E040B0 &= 0xFFFFFFF7u;
}

unsigned int Rva0078F8F0ClearFlag(void)
{
	return g_Va00E040B0 &= 0xFFFFFFEFu;
}

unsigned int Rva0078F8FDClearFlag(void)
{
	return g_Va00E040B0 &= 0xFFFFFFDFu;
}

unsigned int Rva0078F90AClearFlag(void)
{
	return g_Va00E040B0 &= 0xFFFFFFBFu;
}
