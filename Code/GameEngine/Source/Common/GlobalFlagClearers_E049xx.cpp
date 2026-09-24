// Sixteen B2-native flag-word clearers on 11 .data flag words
// (0x00E04900-0x00E049C8):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E045xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E04900;
extern unsigned int g_Va00E04950;
extern unsigned int g_Va00E04958;
extern unsigned int g_Va00E04960;
extern unsigned int g_Va00E04968;
extern unsigned int g_Va00E0497C;
extern unsigned int g_Va00E04988;
extern unsigned int g_Va00E04994;
extern unsigned int g_Va00E0499C;
extern unsigned int g_Va00E049A8;
extern unsigned int g_Va00E049C8;

unsigned int Rva0079529FClearFlag(void)
{
	return g_Va00E04900 &= 0xFFFFFFFEu;
}

unsigned int Rva007967C3ClearFlag(void)
{
	return g_Va00E04950 &= 0xFFFFFFFEu;
}

unsigned int Rva007967E2ClearFlag(void)
{
	return g_Va00E04958 &= 0xFFFFFFFEu;
}

unsigned int Rva00796809ClearFlag(void)
{
	return g_Va00E04960 &= 0xFFFFFFFEu;
}

unsigned int Rva007969A2ClearFlag(void)
{
	return g_Va00E04968 &= 0xFFFFFFFEu;
}

unsigned int Rva00796C2FClearFlag(void)
{
	return g_Va00E0497C &= 0xFFFFFFFEu;
}

unsigned int Rva00796C3CClearFlag(void)
{
	return g_Va00E0497C &= 0xFFFFFFFDu;
}

unsigned int Rva00796C49ClearFlag(void)
{
	return g_Va00E0497C &= 0xFFFFFFFBu;
}

unsigned int Rva00796C60ClearFlag(void)
{
	return g_Va00E04988 &= 0xFFFFFFFEu;
}

unsigned int Rva00796C6DClearFlag(void)
{
	return g_Va00E04988 &= 0xFFFFFFFDu;
}

unsigned int Rva00796C8CClearFlag(void)
{
	return g_Va00E04994 &= 0xFFFFFFFEu;
}

unsigned int Rva00796CA9ClearFlag(void)
{
	return g_Va00E04994 &= 0xFFFFFFFDu;
}

unsigned int Rva00796D1EClearFlag(void)
{
	return g_Va00E0499C &= 0xFFFFFFFEu;
}

unsigned int Rva00796D9AClearFlag(void)
{
	return g_Va00E049A8 &= 0xFFFFFFFEu;
}

unsigned int Rva00796DA7ClearFlag(void)
{
	return g_Va00E049A8 &= 0xFFFFFFFDu;
}

unsigned int Rva007970A3ClearFlag(void)
{
	return g_Va00E049C8 &= 0xFFFFFFFEu;
}

