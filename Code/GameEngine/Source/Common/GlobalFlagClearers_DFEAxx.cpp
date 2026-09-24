// Twelve B2-native flag-word clearers on twelve .data flag words
// (0x00DFEAE0-0x00DFED40):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFE9xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFEAE0;
extern unsigned int g_Va00DFEAE8;
extern unsigned int g_Va00DFEB54;
extern unsigned int g_Va00DFEC4C;
extern unsigned int g_Va00DFEC60;
extern unsigned int g_Va00DFEC80;
extern unsigned int g_Va00DFECE0;
extern unsigned int g_Va00DFECE8;
extern unsigned int g_Va00DFECF0;
extern unsigned int g_Va00DFECF8;
extern unsigned int g_Va00DFED00;
extern unsigned int g_Va00DFED40;

unsigned int Rva00772D90ClearFlag(void)
{
	return g_Va00DFEAE0 &= 0xFFFFFFFEu;
}

unsigned int Rva00772DB9ClearFlag(void)
{
	return g_Va00DFEAE8 &= 0xFFFFFFFEu;
}

unsigned int Rva00773046ClearFlag(void)
{
	return g_Va00DFEB54 &= 0xFFFFFFFEu;
}

unsigned int Rva007735C6ClearFlag(void)
{
	return g_Va00DFEC4C &= 0xFFFFFFFEu;
}

unsigned int Rva0077388BClearFlag(void)
{
	return g_Va00DFEC60 &= 0xFFFFFFFEu;
}

unsigned int Rva00773EB8ClearFlag(void)
{
	return g_Va00DFEC80 &= 0xFFFFFFFEu;
}

unsigned int Rva007742BCClearFlag(void)
{
	return g_Va00DFECE0 &= 0xFFFFFFFEu;
}

unsigned int Rva007742D3ClearFlag(void)
{
	return g_Va00DFECE8 &= 0xFFFFFFFEu;
}

unsigned int Rva007742EAClearFlag(void)
{
	return g_Va00DFECF0 &= 0xFFFFFFFEu;
}

unsigned int Rva00774313ClearFlag(void)
{
	return g_Va00DFECF8 &= 0xFFFFFFFEu;
}

unsigned int Rva0077433CClearFlag(void)
{
	return g_Va00DFED00 &= 0xFFFFFFFEu;
}

unsigned int Rva0077444AClearFlag(void)
{
	return g_Va00DFED40 &= 0xFFFFFFFEu;
}
