// Fourteen B2-native flag-word clearers across fourteen .data flag words
// of one contiguous run (0x00781323-0x00781D66):
//
//     mov eax,[<address>] / and al,0xFE / mov [<address>],eax / ret
//
// All fourteen clear al bit 0. Same /G7 byte-register narrowing as
// GlobalFlagClearers_08.cpp (defaults emit `and eax,imm`). Each body
// carries a .rdata table slot (0x0092C168 and on). An image-wide raw
// branch scan flagged some of these addresses, but targeted decode proves
// every flag is a `jmp 0x629182` displacement byte, not a branch into the
// body. Identity is not recovered; names derive from addresses, following
// GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E0282C;
extern unsigned int g_Va00E02844;
extern unsigned int g_Va00E028CC;
extern unsigned int g_Va00E028D4;
extern unsigned int g_Va00E028E4;
extern unsigned int g_Va00E028EC;
extern unsigned int g_Va00E02910;
extern unsigned int g_Va00E02918;
extern unsigned int g_Va00E02920;
extern unsigned int g_Va00E02928;
extern unsigned int g_Va00E02930;
extern unsigned int g_Va00E02938;
extern unsigned int g_Va00E02940;
extern unsigned int g_Va00E0294C;
extern unsigned int g_Va00E02958;

unsigned int Rva00781323ClearFlag(void)
{
	return g_Va00E02844 &= 0xFFFFFFFEu;
}

unsigned int Rva007816EBClearFlag(void)
{
	return g_Va00E028CC &= 0xFFFFFFFEu;
}

unsigned int Rva00781B3FClearFlag(void)
{
	return g_Va00E028D4 &= 0xFFFFFFFEu;
}

unsigned int Rva00781B83ClearFlag(void)
{
	return g_Va00E028E4 &= 0xFFFFFFFEu;
}

unsigned int Rva00781BACClearFlag(void)
{
	return g_Va00E028EC &= 0xFFFFFFFEu;
}

unsigned int Rva00781C62ClearFlag(void)
{
	return g_Va00E02910 &= 0xFFFFFFFEu;
}

unsigned int Rva00781C79ClearFlag(void)
{
	return g_Va00E02918 &= 0xFFFFFFFEu;
}

unsigned int Rva00781C90ClearFlag(void)
{
	return g_Va00E02920 &= 0xFFFFFFFEu;
}

unsigned int Rva00781CA7ClearFlag(void)
{
	return g_Va00E02928 &= 0xFFFFFFFEu;
}

unsigned int Rva00781CBEClearFlag(void)
{
	return g_Va00E02930 &= 0xFFFFFFFEu;
}

unsigned int Rva00781CD5ClearFlag(void)
{
	return g_Va00E02938 &= 0xFFFFFFFEu;
}

unsigned int Rva00781CECClearFlag(void)
{
	return g_Va00E02940 &= 0xFFFFFFFEu;
}

unsigned int Rva00781D4FClearFlag(void)
{
	return g_Va00E0294C &= 0xFFFFFFFEu;
}

unsigned int Rva00781D66ClearFlag(void)
{
	return g_Va00E02958 &= 0xFFFFFFFEu;
}

unsigned int Rva007810A7ClearFlag(void)
{
	return g_Va00E0282C &= 0xFFFFFFFEu;
}

unsigned int Rva007810B4ClearFlag(void)
{
	return g_Va00E0282C &= 0xFFFFFFFDu;
}
