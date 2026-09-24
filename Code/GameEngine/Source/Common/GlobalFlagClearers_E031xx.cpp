// Four B2-native flag-word clearers on three .data flag words
// (0x00E03110-0x00E03150):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFEExx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03110;
extern unsigned int g_Va00E03118;
extern unsigned int g_Va00E03150;

unsigned int Rva00786A39ClearFlag(void)
{
	return g_Va00E03110 &= 0xFFFFFFFEu;
}

unsigned int Rva00786A46ClearFlag(void)
{
	return g_Va00E03110 &= 0xFFFFFFFDu;
}

unsigned int Rva00786A89ClearFlag(void)
{
	return g_Va00E03118 &= 0xFFFFFFFEu;
}

unsigned int Rva00786F00ClearFlag(void)
{
	return g_Va00E03150 &= 0xFFFFFFFEu;
}
