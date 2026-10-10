// Twenty-eight B2-native flag-word clearers on 26 .data flag words
// (0x00DE6128-0x00DFF158):
//
//     mov eax,[<address>] / and a<l,h>,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E06x.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DE6128;
extern unsigned int g_Va00DEAF1C;
// g_Va00DEAF1C: matched references place it at VA 0xdeaf1c (zero-filled .bss).
unsigned int g_Va00DEAF1C;
extern unsigned int g_Va00DF2970;
// g_Va00DF2970: matched references place it at VA 0xdf2970 (zero-filled .bss).
unsigned int g_Va00DF2970;
extern unsigned int g_Va00DF3638;
// g_Va00DF3638: matched references place it at VA 0xdf3638 (zero-filled .bss).
unsigned int g_Va00DF3638;
extern unsigned int g_Va00DF3678;
extern unsigned int g_Va00DF5600;
// g_Va00DF5600: matched references place it at VA 0xdf5600 (zero-filled .bss).
unsigned int g_Va00DF5600;
extern unsigned int g_Va00DF6FC8;
extern unsigned int g_Va00DF7038;
// g_Va00DF7038: matched references place it at VA 0xdf7038 (zero-filled .bss).
unsigned int g_Va00DF7038;
extern unsigned int g_Va00DFD8E4;
// g_Va00DFD8E4: matched references place it at VA 0xdfd8e4 (zero-filled .bss).
unsigned int g_Va00DFD8E4;
extern unsigned int g_Va00DFD934;
// g_Va00DFD934: matched references place it at VA 0xdfd934 (zero-filled .bss).
unsigned int g_Va00DFD934;
extern unsigned int g_Va00DFDCE0;
// g_Va00DFDCE0: matched references place it at VA 0xdfdce0 (zero-filled .bss).
unsigned int g_Va00DFDCE0;
extern unsigned int g_Va00DFDCF4;
extern unsigned int g_Va00DFE014;
extern unsigned int g_Va00DFE484;
// g_Va00DFE484: matched references place it at VA 0xdfe484 (zero-filled .bss).
unsigned int g_Va00DFE484;
extern unsigned int g_Va00DFE4A8;
// g_Va00DFE4A8: matched references place it at VA 0xdfe4a8 (zero-filled .bss).
unsigned int g_Va00DFE4A8;
extern unsigned int g_Va00DFE4B8;
// g_Va00DFE4B8: matched references place it at VA 0xdfe4b8 (zero-filled .bss).
unsigned int g_Va00DFE4B8;
extern unsigned int g_Va00DFE744;
// g_Va00DFE744: matched references place it at VA 0xdfe744 (zero-filled .bss).
unsigned int g_Va00DFE744;
extern unsigned int g_Va00DFE778;
// g_Va00DFE778: matched references place it at VA 0xdfe778 (zero-filled .bss).
unsigned int g_Va00DFE778;
extern unsigned int g_Va00DFEDE4;
extern unsigned int g_Va00DFEEC4;
extern unsigned int g_Va00DFEEDC;
extern unsigned int g_Va00DFEFEC;
// g_Va00DFEFEC: matched references place it at VA 0xdfefec (zero-filled .bss).
unsigned int g_Va00DFEFEC;
extern unsigned int g_Va00DFF040;
// g_Va00DFF040: matched references place it at VA 0xdff040 (zero-filled .bss).
unsigned int g_Va00DFF040;
extern unsigned int g_Va00DFF04C;
extern unsigned int g_Va00DFF158;
// g_Va00DFF158: matched references place it at VA 0xdff158 (zero-filled .bss).
unsigned int g_Va00DFF158;

unsigned int Rva0076096CClearFlag(void)
{
	return g_Va00DE6128 &= 0xFFFFFFFEu;
}

unsigned int Rva00761884ClearFlag(void)
{
	return g_Va00DEAF1C &= 0xFFFFFFFEu;
}

unsigned int Rva00765860ClearFlag(void)
{
	return g_Va00DF2970 &= 0xFFFFFFFEu;
}

unsigned int Rva00766080ClearFlag(void)
{
	return g_Va00DF3638 &= 0xFFFFFFFEu;
}

unsigned int Rva007665A0ClearFlag(void)
{
	return g_Va00DF3678 &= 0xFFFFFFFEu;
}

unsigned int Rva00766999ClearFlag(void)
{
	return g_Va00DF5600 &= 0xFFFFFFFEu;
}

unsigned int Rva00767CC6ClearFlag(void)
{
	return g_Va00DF6FC8 &= 0xFFFFFFFEu;
}

unsigned int Rva00767DE0ClearFlag(void)
{
	return g_Va00DF7038 &= 0xFFFFFFFEu;
}

unsigned int Rva00769290ClearFlag(void)
{
	return g_Va00DFD8E4 &= 0xFFFFFFFEu;
}

unsigned int Rva007693B0ClearFlag(void)
{
	return g_Va00DFD934 &= 0xFFFFFFF7u;
}

unsigned int Rva0076B135ClearFlag(void)
{
	return g_Va00DFDCE0 &= 0xFFFFFFFEu;
}

unsigned int Rva0076B20FClearFlag(void)
{
	return g_Va00DFDCF4 &= 0xFFFFFFFDu;
}

unsigned int Rva0076B9EAClearFlag(void)
{
	return g_Va00DFE014 &= 0xFFFFFFFEu;
}

unsigned int Rva0076ED89ClearFlag(void)
{
	return g_Va00DFE484 &= 0xFFFFFFFEu;
}

unsigned int Rva0076ED96ClearFlag(void)
{
	return g_Va00DFE484 &= 0xFFFFFFFDu;
}

unsigned int Rva0076EF62ClearFlag(void)
{
	return g_Va00DFE4A8 &= 0xFFFFFFFEu;
}

unsigned int Rva0076EFA3ClearFlag(void)
{
	return g_Va00DFE4B8 &= 0xFFFFFFFEu;
}

unsigned int Rva0077099AClearFlag(void)
{
	return g_Va00DFE778 &= 0xFFFFFFFEu;
}

unsigned int Rva00774949ClearFlag(void)
{
	return g_Va00DFEDE4 &= 0xFFFFBFFFu;
}

unsigned int Rva00774CF7ClearFlag(void)
{
	return g_Va00DFEEC4 &= 0xFFFFFFFEu;
}

unsigned int Rva00774E83ClearFlag(void)
{
	return g_Va00DFEEDC &= 0xFFFFFFFEu;
}

unsigned int Rva00776FB6ClearFlag(void)
{
	return g_Va00DFEFEC &= 0xFFFFFFFEu;
}

unsigned int Rva007774BEClearFlag(void)
{
	return g_Va00DFF040 &= 0xFFFFFFFEu;
}

unsigned int Rva007774DDClearFlag(void)
{
	return g_Va00DFF04C &= 0xFFFFFFFEu;
}

unsigned int Rva00779416ClearFlag(void)
{
	return g_Va00DFF158 &= 0xFFFFFFFEu;
}

unsigned int Rva0076B1DFClearFlag(void)
{
	return g_Va00DFDCF4 &= 0xFFFFFFFEu;
}

unsigned int Rva007700C2ClearFlag(void)
{
	return g_Va00DFE744 &= 0xFFFFFFFEu;
}

