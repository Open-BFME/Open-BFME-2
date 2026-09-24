// Sixteen B2-native flag-word clearers on sixteen .data flag words
// (0x00E03600-0x00E036F8):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E035xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03600;
extern unsigned int g_Va00E03620;
extern unsigned int g_Va00E03644;
extern unsigned int g_Va00E0364C;
extern unsigned int g_Va00E03658;
extern unsigned int g_Va00E03660;
extern unsigned int g_Va00E0366C;
extern unsigned int g_Va00E03674;
extern unsigned int g_Va00E0367C;
extern unsigned int g_Va00E03684;
extern unsigned int g_Va00E0368C;
extern unsigned int g_Va00E03698;
extern unsigned int g_Va00E036A4;
extern unsigned int g_Va00E036B0;
extern unsigned int g_Va00E036EC;
extern unsigned int g_Va00E036F8;

unsigned int Rva0078A9F1ClearFlag(void)
{
	return g_Va00E03600 &= 0xFFFFFFFEu;
}

unsigned int Rva0078AA08ClearFlag(void)
{
	return g_Va00E03620 &= 0xFFFFFFFEu;
}

unsigned int Rva0078AB49ClearFlag(void)
{
	return g_Va00E03644 &= 0xFFFFFFFEu;
}

unsigned int Rva0078ACF7ClearFlag(void)
{
	return g_Va00E0364C &= 0xFFFFFFFEu;
}

unsigned int Rva0078AD20ClearFlag(void)
{
	return g_Va00E03658 &= 0xFFFFFFFEu;
}

unsigned int Rva0078ADBBClearFlag(void)
{
	return g_Va00E03660 &= 0xFFFFFFFEu;
}

unsigned int Rva0078AEC8ClearFlag(void)
{
	return g_Va00E0366C &= 0xFFFFFFFEu;
}

unsigned int Rva0078AF1CClearFlag(void)
{
	return g_Va00E03674 &= 0xFFFFFFFEu;
}

unsigned int Rva0078B0B6ClearFlag(void)
{
	return g_Va00E0367C &= 0xFFFFFFFEu;
}

unsigned int Rva0078B1B9ClearFlag(void)
{
	return g_Va00E03684 &= 0xFFFFFFFEu;
}

unsigned int Rva0078B216ClearFlag(void)
{
	return g_Va00E0368C &= 0xFFFFFFFEu;
}

unsigned int Rva0078B3EFClearFlag(void)
{
	return g_Va00E03698 &= 0xFFFFFFFEu;
}

unsigned int Rva0078B418ClearFlag(void)
{
	return g_Va00E036A4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078B499ClearFlag(void)
{
	return g_Va00E036B0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078B54FClearFlag(void)
{
	return g_Va00E036EC &= 0xFFFFFFFEu;
}

unsigned int Rva0078B5B0ClearFlag(void)
{
	return g_Va00E036F8 &= 0xFFFFFFFEu;
}

