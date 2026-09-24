// Eight B2-native flag-word clearers on eight .data flag words
// (0x00E035A4-0x00E035F4):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E034xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E035A4;
extern unsigned int g_Va00E035B8;
extern unsigned int g_Va00E035C0;
extern unsigned int g_Va00E035D0;
extern unsigned int g_Va00E035D8;
extern unsigned int g_Va00E035E0;
extern unsigned int g_Va00E035EC;
extern unsigned int g_Va00E035F4;

unsigned int Rva0078A6E1ClearFlag(void)
{
	return g_Va00E035A4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A70AClearFlag(void)
{
	return g_Va00E035B8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A759ClearFlag(void)
{
	return g_Va00E035C0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A7AAClearFlag(void)
{
	return g_Va00E035D0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A7C1ClearFlag(void)
{
	return g_Va00E035D8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A7EAClearFlag(void)
{
	return g_Va00E035E0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A97DClearFlag(void)
{
	return g_Va00E035EC &= 0xFFFFFFFEu;
}

unsigned int Rva0078A994ClearFlag(void)
{
	return g_Va00E035F4 &= 0xFFFFFFFEu;
}

