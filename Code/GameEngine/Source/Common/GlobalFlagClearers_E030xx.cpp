// Four B2-native flag-word clearers on three .data flag words
// (0x00E03038-0x00E030E0):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFEExx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03038;
extern unsigned int g_Va00E03088;
extern unsigned int g_Va00E030E0;

unsigned int Rva00785E4EClearFlag(void)
{
	return g_Va00E03038 &= 0xFFFFFFFEu;
}

unsigned int Rva00785E63ClearFlag(void)
{
	return g_Va00E03038 &= 0xFFFFFFFDu;
}

unsigned int Rva0078613AClearFlag(void)
{
	return g_Va00E03088 &= 0xFFFFFFFEu;
}

unsigned int Rva007869E4ClearFlag(void)
{
	return g_Va00E030E0 &= 0xFFFFFFFEu;
}
