// Eleven B2-native flag-word clearers on 10 .data flag words
// (0x00E04410-0x00E044EC):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E043xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E04410;
extern unsigned int g_Va00E04418;
extern unsigned int g_Va00E04438;
extern unsigned int g_Va00E04440;
extern unsigned int g_Va00E0444C;
extern unsigned int g_Va00E044C0;
extern unsigned int g_Va00E044C8;
extern unsigned int g_Va00E044D0;
extern unsigned int g_Va00E044E4;
extern unsigned int g_Va00E044EC;

unsigned int Rva00791749ClearFlag(void)
{
	return g_Va00E04410 &= 0xFFFFFFFEu;
}

unsigned int Rva007917A4ClearFlag(void)
{
	return g_Va00E04418 &= 0xFFFFFFFEu;
}

unsigned int Rva00791B4FClearFlag(void)
{
	return g_Va00E04438 &= 0xFFFFFFFEu;
}

unsigned int Rva00791B6EClearFlag(void)
{
	return g_Va00E04440 &= 0xFFFFFFFEu;
}

unsigned int Rva00791BC0ClearFlag(void)
{
	return g_Va00E0444C &= 0xFFFFFFFEu;
}

unsigned int Rva00791BCDClearFlag(void)
{
	return g_Va00E0444C &= 0xFFFFFFFDu;
}

unsigned int Rva00792CD9ClearFlag(void)
{
	return g_Va00E044C0 &= 0xFFFFFFFEu;
}

unsigned int Rva00792D4DClearFlag(void)
{
	return g_Va00E044C8 &= 0xFFFFFFFEu;
}

unsigned int Rva00792E37ClearFlag(void)
{
	return g_Va00E044D0 &= 0xFFFFFFFEu;
}

unsigned int Rva00793000ClearFlag(void)
{
	return g_Va00E044E4 &= 0xFFFFFFFEu;
}

unsigned int Rva00793017ClearFlag(void)
{
	return g_Va00E044EC &= 0xFFFFFFFEu;
}

