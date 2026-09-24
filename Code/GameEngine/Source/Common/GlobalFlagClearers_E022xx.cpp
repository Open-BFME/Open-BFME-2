// Ten B2-native flag-word clearers on five .data flag words
// (0x00E02280-0x00E022C8):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFEExx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E02280;
extern unsigned int g_Va00E022A0;
extern unsigned int g_Va00E022B0;
extern unsigned int g_Va00E022B8;
extern unsigned int g_Va00E022C8;

unsigned int Rva0077EBF1ClearFlag(void)
{
	return g_Va00E02280 &= 0xFFFFFFFEu;
}

unsigned int Rva0077EC06ClearFlag(void)
{
	return g_Va00E02280 &= 0xFFFFFFFDu;
}

unsigned int Rva0077EC13ClearFlag(void)
{
	return g_Va00E02280 &= 0xFFFFFFFBu;
}

unsigned int Rva0077EC36ClearFlag(void)
{
	return g_Va00E02280 &= 0xFFFFFFDFu;
}

unsigned int Rva0077F12AClearFlag(void)
{
	return g_Va00E022A0 &= 0xFFFFFFFEu;
}

unsigned int Rva0077F141ClearFlag(void)
{
	return g_Va00E022B0 &= 0xFFFFFFFEu;
}

unsigned int Rva0077F14EClearFlag(void)
{
	return g_Va00E022B0 &= 0xFFFFFFFDu;
}

unsigned int Rva0077F180ClearFlag(void)
{
	return g_Va00E022B8 &= 0xFFFFFFFEu;
}

unsigned int Rva0077F22AClearFlag(void)
{
	return g_Va00E022C8 &= 0xFFFFFFFEu;
}

unsigned int Rva0077F237ClearFlag(void)
{
	return g_Va00E022C8 &= 0xFFFFFFFDu;
}
