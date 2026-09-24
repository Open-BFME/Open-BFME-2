// Seven B2-native flag-word clearers on four .data flag words
// (0x00E02F34-0x00E02FA0):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFEExx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E02F34;
extern unsigned int g_Va00E02F88;
extern unsigned int g_Va00E02F94;
extern unsigned int g_Va00E02FA0;

unsigned int Rva00784D3FClearFlag(void)
{
	return g_Va00E02F34 &= 0xFFFFFFFEu;
}

unsigned int Rva007855BDClearFlag(void)
{
	return g_Va00E02F88 &= 0xFFFFFFFEu;
}

unsigned int Rva007855CAClearFlag(void)
{
	return g_Va00E02F88 &= 0xFFFFFFFDu;
}

unsigned int Rva007855E9ClearFlag(void)
{
	return g_Va00E02F94 &= 0xFFFFFFFEu;
}

unsigned int Rva007855F6ClearFlag(void)
{
	return g_Va00E02F94 &= 0xFFFFFFFDu;
}

unsigned int Rva00785684ClearFlag(void)
{
	return g_Va00E02FA0 &= 0xFFFFFFFEu;
}

unsigned int Rva00785691ClearFlag(void)
{
	return g_Va00E02FA0 &= 0xFFFFFFFDu;
}
