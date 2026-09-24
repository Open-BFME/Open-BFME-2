// Twenty-one B2-native flag-word clearers on fourteen .data flag words
// (0x00E03304-0x00E033F0):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E031xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03304;
extern unsigned int g_Va00E03334;
extern unsigned int g_Va00E03350;
extern unsigned int g_Va00E0337C;

unsigned int Rva00788149ClearFlag(void)
{
	return g_Va00E03304 &= 0xFFFFFFFEu;
}

unsigned int Rva007886AFClearFlag(void)
{
	return g_Va00E03334 &= 0xFFFFFFFEu;
}

unsigned int Rva007886C4ClearFlag(void)
{
	return g_Va00E03334 &= 0xFFFFFFFDu;
}

unsigned int Rva007886D1ClearFlag(void)
{
	return g_Va00E03334 &= 0xFFFFFFFBu;
}

unsigned int Rva007886EEClearFlag(void)
{
	return g_Va00E03334 &= 0xFFFFFFF7u;
}

unsigned int Rva00788A22ClearFlag(void)
{
	return g_Va00E03350 &= 0xFFFFFFFEu;
}

unsigned int Rva00788A37ClearFlag(void)
{
	return g_Va00E03350 &= 0xFFFFFFFDu;
}

unsigned int Rva00789673ClearFlag(void)
{
	return g_Va00E0337C &= 0xFFFFFFFEu;
}

unsigned int Rva00789688ClearFlag(void)
{
	return g_Va00E0337C &= 0xFFFFFFFDu;
}
