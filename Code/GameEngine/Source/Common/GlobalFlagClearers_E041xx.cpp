// Five B2-native flag-word clearers on five .data flag words
// (0x00E0414C-0x00E0416C):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_E040xx.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E040xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E0414C;
extern unsigned int g_Va00E04154;
extern unsigned int g_Va00E0415C;
extern unsigned int g_Va00E04164;
extern unsigned int g_Va00E0416C;

unsigned int Rva0078FBE5ClearFlag(void)
{
	return g_Va00E0414C &= 0xFFFFFFFEu;
}

unsigned int Rva0078FBFCClearFlag(void)
{
	return g_Va00E04154 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FC42ClearFlag(void)
{
	return g_Va00E0415C &= 0xFFFFFFFEu;
}

unsigned int Rva0078FC59ClearFlag(void)
{
	return g_Va00E04164 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FC70ClearFlag(void)
{
	return g_Va00E0416C &= 0xFFFFFFFEu;
}
