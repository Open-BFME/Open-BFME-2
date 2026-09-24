// Twenty-one B2-native flag-word clearers on fourteen .data flag words
// (0x00E03304-0x00E033F0):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E031xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03304;

unsigned int Rva00788149ClearFlag(void)
{
	return g_Va00E03304 &= 0xFFFFFFFEu;
}
