// Seven B2-native flag-word clearers across three .data flag words of one
// contiguous run (0x0077AC0A-0x0077AD65):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot (0x00923918
// and on). Identity is not recovered; names derive from addresses,
// following GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E01D24;
extern unsigned int g_Va00E01D34;
extern unsigned int g_Va00E01D3C;

unsigned int Rva0077AC0AClearFlag(void)
{
	return g_Va00E01D24 &= 0xFFFFFFFEu;
}

unsigned int Rva0077AC17ClearFlag(void)
{
	return g_Va00E01D24 &= 0xFFFFFFFDu;
}

unsigned int Rva0077AC24ClearFlag(void)
{
	return g_Va00E01D24 &= 0xFFFFFFFBu;
}

unsigned int Rva0077AC3BClearFlag(void)
{
	return g_Va00E01D34 &= 0xFFFFFFFEu;
}

unsigned int Rva0077AC48ClearFlag(void)
{
	return g_Va00E01D34 &= 0xFFFFFFFDu;
}

unsigned int Rva0077AC55ClearFlag(void)
{
	return g_Va00E01D34 &= 0xFFFFFFFBu;
}

unsigned int Rva0077AD65ClearFlag(void)
{
	return g_Va00E01D3C &= 0xFFFFFFFEu;
}
