// Fourteen B2-native flag-word clearers across twelve .data flag words of
// one contiguous run (0x007618F7-0x007629C6):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Thirteen clear al bit 0, one clears al bit 1. Same /G7 byte-register
// narrowing as GlobalFlagClearers_08.cpp (defaults emit `and eax,imm`).
// Each body carries a .rdata table slot (0x00904E88 and on). Identity is
// not recovered; names derive from addresses, following
// GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DEAF24;
extern unsigned int g_Va00DEAF2C;
extern unsigned int g_Va00DEAF48;
extern unsigned int g_Va00DEBB50;
extern unsigned int g_Va00DEBB5C;
extern unsigned int g_Va00DEBB70;
extern unsigned int g_Va00DEBB7C;
extern unsigned int g_Va00DEBB88;
extern unsigned int g_Va00DEBB94;
extern unsigned int g_Va00DEBBA0;
extern unsigned int g_Va00DEBBB8;
extern unsigned int g_Va00DEBBF4;
extern unsigned int g_Va00DEBC24;

unsigned int Rva007618F7ClearFlag(void)
{
	return g_Va00DEAF24 &= 0xFFFFFFFEu;
}

unsigned int Rva00761A48ClearFlag(void)
{
	return g_Va00DEAF2C &= 0xFFFFFFFEu;
}

unsigned int Rva00761BBAClearFlag(void)
{
	return g_Va00DEAF48 &= 0xFFFFFFFEu;
}

unsigned int Rva00761BC7ClearFlag(void)
{
	return g_Va00DEAF48 &= 0xFFFFFFFDu;
}

unsigned int Rva00761C5EClearFlag(void)
{
	return g_Va00DEBB50 &= 0xFFFFFFFEu;
}

unsigned int Rva00762273ClearFlag(void)
{
	return g_Va00DEBB5C &= 0xFFFFFFFEu;
}

unsigned int Rva00762319ClearFlag(void)
{
	return g_Va00DEBB70 &= 0xFFFFFFFEu;
}

unsigned int Rva00762330ClearFlag(void)
{
	return g_Va00DEBB7C &= 0xFFFFFFFEu;
}

unsigned int Rva00762382ClearFlag(void)
{
	return g_Va00DEBB88 &= 0xFFFFFFFEu;
}

unsigned int Rva00762557ClearFlag(void)
{
	return g_Va00DEBB94 &= 0xFFFFFFFEu;
}

unsigned int Rva00762614ClearFlag(void)
{
	return g_Va00DEBBA0 &= 0xFFFFFFFEu;
}

unsigned int Rva007626E1ClearFlag(void)
{
	return g_Va00DEBBB8 &= 0xFFFFFFFEu;
}

unsigned int Rva007628D8ClearFlag(void)
{
	return g_Va00DEBBF4 &= 0xFFFFFFFEu;
}

unsigned int Rva007629C6ClearFlag(void)
{
	return g_Va00DEBC24 &= 0xFFFFFFFEu;
}
