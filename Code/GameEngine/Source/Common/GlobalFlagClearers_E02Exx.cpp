// Eleven B2-native flag-word clearers on eleven .data flag words
// (0x00E02E10-0x00E02EE4):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFEExx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E02E10;
extern unsigned int g_Va00E02E18;
extern unsigned int g_Va00E02E20;
extern unsigned int g_Va00E02E28;
extern unsigned int g_Va00E02E30;
extern unsigned int g_Va00E02E3C;
extern unsigned int g_Va00E02E44;
extern unsigned int g_Va00E02ECC;
extern unsigned int g_Va00E02ED4;
extern unsigned int g_Va00E02EDC;
extern unsigned int g_Va00E02EE4;

unsigned int Rva007832F6ClearFlag(void)
{
	return g_Va00E02E10 &= 0xFFFFFFFEu;
}

unsigned int Rva0078330DClearFlag(void)
{
	return g_Va00E02E18 &= 0xFFFFFFFEu;
}

unsigned int Rva00783324ClearFlag(void)
{
	return g_Va00E02E20 &= 0xFFFFFFFEu;
}

unsigned int Rva0078334DClearFlag(void)
{
	return g_Va00E02E28 &= 0xFFFFFFFEu;
}

unsigned int Rva007833BBClearFlag(void)
{
	return g_Va00E02E30 &= 0xFFFFFFFEu;
}

unsigned int Rva007835CEClearFlag(void)
{
	return g_Va00E02E3C &= 0xFFFFFFFEu;
}

unsigned int Rva00783619ClearFlag(void)
{
	return g_Va00E02E44 &= 0xFFFFFFFEu;
}

unsigned int Rva0078476EClearFlag(void)
{
	return g_Va00E02ECC &= 0xFFFFFFFEu;
}

unsigned int Rva0078478DClearFlag(void)
{
	return g_Va00E02ED4 &= 0xFFFFFFFEu;
}

unsigned int Rva007847ACClearFlag(void)
{
	return g_Va00E02EDC &= 0xFFFFFFFEu;
}

unsigned int Rva007847CBClearFlag(void)
{
	return g_Va00E02EE4 &= 0xFFFFFFFEu;
}
