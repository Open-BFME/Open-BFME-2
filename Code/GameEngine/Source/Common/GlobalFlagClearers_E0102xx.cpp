// Eighteen B2-native flag-word clearers on 17 .data flag words
// (0x00E01DE0-0x00E048F8):
//
//     mov eax,[<address>] / and a<l,h>,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFxx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E01DE0;
extern unsigned int g_Va00E01E30;
extern unsigned int g_Va00E01E8C;
extern unsigned int g_Va00E01EB0;
extern unsigned int g_Va00E01EB8;
extern unsigned int g_Va00E01EE8;
extern unsigned int g_Va00E01EF0;
extern unsigned int g_Va00E01EF8;
extern unsigned int g_Va00E021E0;
extern unsigned int g_Va00E02808;
extern unsigned int g_Va00E02810;
extern unsigned int g_Va00E02818;
extern unsigned int g_Va00E02820;
extern unsigned int g_Va00E02F24;
extern unsigned int g_Va00E032C0;
extern unsigned int g_Va00E04608;
extern unsigned int g_Va00E048F8;

unsigned int Rva0077CB98ClearFlag(void)
{
	return g_Va00E01DE0 &= 0xFFFFFFFEu;
}

unsigned int Rva0077D98AClearFlag(void)
{
	return g_Va00E01E30 &= 0xFFFFFFFEu;
}

unsigned int Rva0077E24EClearFlag(void)
{
	return g_Va00E01E8C &= 0xFFFFFFFEu;
}

unsigned int Rva0077E48CClearFlag(void)
{
	return g_Va00E01EB0 &= 0xFFFFFFFEu;
}

unsigned int Rva0077E57FClearFlag(void)
{
	return g_Va00E01EB8 &= 0xFFFFFFFEu;
}

unsigned int Rva0077E778ClearFlag(void)
{
	return g_Va00E01EE8 &= 0xFFFFFFFEu;
}

unsigned int Rva0077E7D5ClearFlag(void)
{
	return g_Va00E01EF0 &= 0xFFFFFFFEu;
}

unsigned int Rva0077E87EClearFlag(void)
{
	return g_Va00E01EF8 &= 0xFFFFFFFEu;
}

unsigned int Rva0077EBADClearFlag(void)
{
	return g_Va00E021E0 &= 0xFFFFFFFEu;
}

unsigned int Rva00780EDCClearFlag(void)
{
	return g_Va00E02808 &= 0xFFFFFFFEu;
}

unsigned int Rva00780EE9ClearFlag(void)
{
	return g_Va00E02808 &= 0xFFFFFFFDu;
}

unsigned int Rva00780F00ClearFlag(void)
{
	return g_Va00E02810 &= 0xFFFFFFFEu;
}

unsigned int Rva00780F8DClearFlag(void)
{
	return g_Va00E02818 &= 0xFFFFFFFEu;
}

unsigned int Rva00780FA4ClearFlag(void)
{
	return g_Va00E02820 &= 0xFFFFFFFEu;
}

unsigned int Rva00784B78ClearFlag(void)
{
	return g_Va00E02F24 &= 0xFFFFFEFFu;
}

unsigned int Rva00787AA4ClearFlag(void)
{
	return g_Va00E032C0 &= 0xFFFFFFFEu;
}

unsigned int Rva0079477AClearFlag(void)
{
	return g_Va00E04608 &= 0xFFFFFFFEu;
}

unsigned int Rva00795288ClearFlag(void)
{
	return g_Va00E048F8 &= 0xFFFFFFFEu;
}

