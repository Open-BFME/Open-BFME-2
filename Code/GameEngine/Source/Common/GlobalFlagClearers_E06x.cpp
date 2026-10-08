// B2-native flag-word clearers on .data flag words
// (0x00E06220-0x00E06938):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E05x.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E06220;
// g_Va00E06220: matched references place it at VA 0xe06220 (zero-filled .bss).
unsigned int g_Va00E06220;
extern unsigned int g_Va00E062E4;
// g_Va00E062E4: matched references place it at VA 0xe062e4 (zero-filled .bss).
unsigned int g_Va00E062E4;
extern unsigned int g_Va00E06390;
// g_Va00E06390: matched references place it at VA 0xe06390 (zero-filled .bss).
unsigned int g_Va00E06390;
extern unsigned int g_Va00E063C8;
// g_Va00E063C8: matched references place it at VA 0xe063c8 (zero-filled .bss).
unsigned int g_Va00E063C8;
extern unsigned int g_Va00E06558;
// g_Va00E06558: matched references place it at VA 0xe06558 (zero-filled .bss).
unsigned int g_Va00E06558;
extern unsigned int g_Va00E065B0;
// g_Va00E065B0: matched references place it at VA 0xe065b0 (zero-filled .bss).
unsigned int g_Va00E065B0;
extern unsigned int g_Va00E065DC;
// g_Va00E065DC: matched references place it at VA 0xe065dc (zero-filled .bss).
unsigned int g_Va00E065DC;
extern unsigned int g_Va00E065E8;
// g_Va00E065E8: matched references place it at VA 0xe065e8 (zero-filled .bss).
unsigned int g_Va00E065E8;
extern unsigned int g_Va00E06774;
// g_Va00E06774: matched references place it at VA 0xe06774 (zero-filled .bss).
unsigned int g_Va00E06774;
extern unsigned int g_Va00E068CC;
// g_Va00E068CC: matched references place it at VA 0xe068cc (zero-filled .bss).
unsigned int g_Va00E068CC;
extern unsigned int g_Va00E068D8;
// g_Va00E068D8: matched references place it at VA 0xe068d8 (zero-filled .bss).
unsigned int g_Va00E068D8;
extern unsigned int g_Va00E068E0;
// g_Va00E068E0: matched references place it at VA 0xe068e0 (zero-filled .bss).
unsigned int g_Va00E068E0;
extern unsigned int g_Va00E06930;
// g_Va00E06930: matched references place it at VA 0xe06930 (zero-filled .bss).
unsigned int g_Va00E06930;
extern unsigned int g_Va00E06938;
// g_Va00E06938: matched references place it at VA 0xe06938 (zero-filled .bss).
unsigned int g_Va00E06938;

unsigned int Rva00799992ClearFlag(void)
{
	return g_Va00E06220 &= 0xFFFFFFFEu;
}

unsigned int Rva0079A20FClearFlag(void)
{
	return g_Va00E062E4 &= 0xFFFFFFFEu;
}

unsigned int Rva0079C374ClearFlag(void)
{
	return g_Va00E06390 &= 0xFFFFFFFEu;
}

unsigned int Rva0079C389ClearFlag(void)
{
	return g_Va00E06390 &= 0xFFFFFFFDu;
}

unsigned int Rva0079C3A6ClearFlag(void)
{
	return g_Va00E06390 &= 0xFFFFFFFBu;
}

unsigned int Rva0079D39DClearFlag(void)
{
	return g_Va00E063C8 &= 0xFFFFFFFEu;
}

unsigned int Rva0079D3AAClearFlag(void)
{
	return g_Va00E063C8 &= 0xFFFFFFFDu;
}

unsigned int Rva0079FB9CClearFlag(void)
{
	return g_Va00E06558 &= 0xFFFFFFFEu;
}

unsigned int Rva007A08F0ClearFlag(void)
{
	return g_Va00E065B0 &= 0xFFFFFFFEu;
}

unsigned int Rva007A0C2AClearFlag(void)
{
	return g_Va00E065DC &= 0xFFFFFFFEu;
}

unsigned int Rva007A1034ClearFlag(void)
{
	return g_Va00E065E8 &= 0xFFFFFFFEu;
}

unsigned int Rva007A40C3ClearFlag(void)
{
	return g_Va00E06774 &= 0xFFFFFFFEu;
}

unsigned int Rva007A4B3FClearFlag(void)
{
	return g_Va00E068CC &= 0xFFFFFFFEu;
}

unsigned int Rva007A4F49ClearFlag(void)
{
	return g_Va00E068D8 &= 0xFFFFFFFEu;
}

unsigned int Rva007A4F78ClearFlag(void)
{
	return g_Va00E068E0 &= 0xFFFFFFFEu;
}

unsigned int Rva007A5585ClearFlag(void)
{
	return g_Va00E06930 &= 0xFFFFFFFEu;
}

unsigned int Rva007A59F9ClearFlag(void)
{
	return g_Va00E06938 &= 0xFFFFFFFEu;
}

