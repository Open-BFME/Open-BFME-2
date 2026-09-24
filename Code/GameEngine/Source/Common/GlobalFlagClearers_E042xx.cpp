// Sixteen B2-native flag-word clearers on sixteen .data flag words
// (0x00E04234-0x00E042C8):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E034xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E04234;
extern unsigned int g_Va00E0423C;
extern unsigned int g_Va00E04248;
extern unsigned int g_Va00E04254;
extern unsigned int g_Va00E04260;
extern unsigned int g_Va00E0426C;
extern unsigned int g_Va00E04278;
extern unsigned int g_Va00E04280;
extern unsigned int g_Va00E04288;
extern unsigned int g_Va00E04290;
extern unsigned int g_Va00E0429C;
extern unsigned int g_Va00E042A4;
extern unsigned int g_Va00E042AC;
extern unsigned int g_Va00E042B4;
extern unsigned int g_Va00E042C0;
extern unsigned int g_Va00E042C8;

unsigned int Rva00790024ClearFlag(void)
{
	return g_Va00E04234 &= 0xFFFFFFFEu;
}

unsigned int Rva0079003BClearFlag(void)
{
	return g_Va00E0423C &= 0xFFFFFFFEu;
}

unsigned int Rva00790064ClearFlag(void)
{
	return g_Va00E04248 &= 0xFFFFFFFEu;
}

unsigned int Rva0079008DClearFlag(void)
{
	return g_Va00E04254 &= 0xFFFFFFFEu;
}

unsigned int Rva007900A4ClearFlag(void)
{
	return g_Va00E04260 &= 0xFFFFFFFEu;
}

unsigned int Rva007900BBClearFlag(void)
{
	return g_Va00E0426C &= 0xFFFFFFFEu;
}

unsigned int Rva0079010DClearFlag(void)
{
	return g_Va00E04278 &= 0xFFFFFFFEu;
}

unsigned int Rva00790124ClearFlag(void)
{
	return g_Va00E04280 &= 0xFFFFFFFEu;
}

unsigned int Rva0079014DClearFlag(void)
{
	return g_Va00E04288 &= 0xFFFFFFFEu;
}

unsigned int Rva00790176ClearFlag(void)
{
	return g_Va00E04290 &= 0xFFFFFFFEu;
}

unsigned int Rva0079019DClearFlag(void)
{
	return g_Va00E0429C &= 0xFFFFFFFEu;
}

unsigned int Rva007901BCClearFlag(void)
{
	return g_Va00E042A4 &= 0xFFFFFFFEu;
}

unsigned int Rva007901D3ClearFlag(void)
{
	return g_Va00E042AC &= 0xFFFFFFFEu;
}

unsigned int Rva007901EAClearFlag(void)
{
	return g_Va00E042B4 &= 0xFFFFFFFEu;
}

unsigned int Rva00790201ClearFlag(void)
{
	return g_Va00E042C0 &= 0xFFFFFFFEu;
}

unsigned int Rva0079023FClearFlag(void)
{
	return g_Va00E042C8 &= 0xFFFFFFFEu;
}
