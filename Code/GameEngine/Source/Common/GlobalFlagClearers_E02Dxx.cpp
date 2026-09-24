// Thirteen B2-native flag-word clearers on thirteen .data flag words
// (0x00E02D74-0x00E02DFC):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFEExx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E02D74;
extern unsigned int g_Va00E02DA4;
extern unsigned int g_Va00E02DAC;
extern unsigned int g_Va00E02DB4;
extern unsigned int g_Va00E02DBC;
extern unsigned int g_Va00E02DC4;
extern unsigned int g_Va00E02DCC;
extern unsigned int g_Va00E02DD4;
extern unsigned int g_Va00E02DDC;
extern unsigned int g_Va00E02DE4;
extern unsigned int g_Va00E02DEC;
extern unsigned int g_Va00E02DF4;
extern unsigned int g_Va00E02DFC;

unsigned int Rva0078279DClearFlag(void)
{
	return g_Va00E02D74 &= 0xFFFFFFFEu;
}

unsigned int Rva007828B2ClearFlag(void)
{
	return g_Va00E02DA4 &= 0xFFFFFFFEu;
}

unsigned int Rva007828C9ClearFlag(void)
{
	return g_Va00E02DAC &= 0xFFFFFFFEu;
}

unsigned int Rva007828E0ClearFlag(void)
{
	return g_Va00E02DB4 &= 0xFFFFFFFEu;
}

unsigned int Rva00782B88ClearFlag(void)
{
	return g_Va00E02DBC &= 0xFFFFFFFEu;
}

unsigned int Rva00782D59ClearFlag(void)
{
	return g_Va00E02DC4 &= 0xFFFFFFFEu;
}

unsigned int Rva00782D70ClearFlag(void)
{
	return g_Va00E02DCC &= 0xFFFFFFFEu;
}

unsigned int Rva00782D87ClearFlag(void)
{
	return g_Va00E02DD4 &= 0xFFFFFFFEu;
}

unsigned int Rva00782D9EClearFlag(void)
{
	return g_Va00E02DDC &= 0xFFFFFFFEu;
}

unsigned int Rva00782DEFClearFlag(void)
{
	return g_Va00E02DE4 &= 0xFFFFFFFEu;
}

unsigned int Rva00782FDFClearFlag(void)
{
	return g_Va00E02DEC &= 0xFFFFFFFEu;
}

unsigned int Rva00783011ClearFlag(void)
{
	return g_Va00E02DF4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078303BClearFlag(void)
{
	return g_Va00E02DFC &= 0xFFFFFFFEu;
}
