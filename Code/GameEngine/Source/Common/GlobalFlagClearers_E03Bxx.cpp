// Twenty-six B2-native flag-word clearers on 25 .data flag words
// (0x00E03B00-0x00E03BF4):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E03Axx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03B00;
extern unsigned int g_Va00E03B0C;
extern unsigned int g_Va00E03B14;
extern unsigned int g_Va00E03B1C;
extern unsigned int g_Va00E03B24;
extern unsigned int g_Va00E03B2C;
extern unsigned int g_Va00E03B34;
extern unsigned int g_Va00E03B40;
extern unsigned int g_Va00E03B4C;
extern unsigned int g_Va00E03B58;
extern unsigned int g_Va00E03B60;
extern unsigned int g_Va00E03B6C;
extern unsigned int g_Va00E03B78;
extern unsigned int g_Va00E03B84;
extern unsigned int g_Va00E03B8C;
extern unsigned int g_Va00E03B98;
extern unsigned int g_Va00E03BA0;
extern unsigned int g_Va00E03BA8;
extern unsigned int g_Va00E03BB4;
extern unsigned int g_Va00E03BC4;
extern unsigned int g_Va00E03BCC;
extern unsigned int g_Va00E03BD8;
extern unsigned int g_Va00E03BE4;
extern unsigned int g_Va00E03BEC;
extern unsigned int g_Va00E03BF4;

unsigned int Rva0078D53AClearFlag(void)
{
	return g_Va00E03B00 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D595ClearFlag(void)
{
	return g_Va00E03B0C &= 0xFFFFFFFEu;
}

unsigned int Rva0078D5E0ClearFlag(void)
{
	return g_Va00E03B14 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D61BClearFlag(void)
{
	return g_Va00E03B1C &= 0xFFFFFFFEu;
}

unsigned int Rva0078D64EClearFlag(void)
{
	return g_Va00E03B24 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D6A6ClearFlag(void)
{
	return g_Va00E03B2C &= 0xFFFFFFFEu;
}

unsigned int Rva0078D6BDClearFlag(void)
{
	return g_Va00E03B34 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D7AFClearFlag(void)
{
	return g_Va00E03B40 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D829ClearFlag(void)
{
	return g_Va00E03B4C &= 0xFFFFFFFEu;
}

unsigned int Rva0078D8F9ClearFlag(void)
{
	return g_Va00E03B58 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D934ClearFlag(void)
{
	return g_Va00E03B60 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D9C9ClearFlag(void)
{
	return g_Va00E03B6C &= 0xFFFFFFFEu;
}

unsigned int Rva0078DA27ClearFlag(void)
{
	return g_Va00E03B6C &= 0xFFFFFFFDu;
}

unsigned int Rva0078DAA8ClearFlag(void)
{
	return g_Va00E03B78 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DABFClearFlag(void)
{
	return g_Va00E03B84 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DB02ClearFlag(void)
{
	return g_Va00E03B8C &= 0xFFFFFFFEu;
}

unsigned int Rva0078DB19ClearFlag(void)
{
	return g_Va00E03B98 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DB42ClearFlag(void)
{
	return g_Va00E03BA0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DB59ClearFlag(void)
{
	return g_Va00E03BA8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DB82ClearFlag(void)
{
	return g_Va00E03BB4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DBB6ClearFlag(void)
{
	return g_Va00E03BC4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DC0AClearFlag(void)
{
	return g_Va00E03BCC &= 0xFFFFFFFEu;
}

unsigned int Rva0078DC4CClearFlag(void)
{
	return g_Va00E03BD8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DCBDClearFlag(void)
{
	return g_Va00E03BE4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DCD4ClearFlag(void)
{
	return g_Va00E03BEC &= 0xFFFFFFFEu;
}

unsigned int Rva0078DD17ClearFlag(void)
{
	return g_Va00E03BF4 &= 0xFFFFFFFEu;
}

