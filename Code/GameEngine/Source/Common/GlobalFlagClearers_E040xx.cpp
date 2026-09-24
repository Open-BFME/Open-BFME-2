// Ten B2-native flag-word clearers on ten .data flag words
// (0x00E04000-0x00E04068):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_E033xx.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E033xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E04000;
extern unsigned int g_Va00E04008;
extern unsigned int g_Va00E04010;
extern unsigned int g_Va00E04018;
extern unsigned int g_Va00E04038;
extern unsigned int g_Va00E04044;
extern unsigned int g_Va00E04050;
extern unsigned int g_Va00E04058;
extern unsigned int g_Va00E04060;
extern unsigned int g_Va00E04068;

unsigned int Rva0078F617ClearFlag(void)
{
	return g_Va00E04000 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F66AClearFlag(void)
{
	return g_Va00E04008 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F693ClearFlag(void)
{
	return g_Va00E04010 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F6AAClearFlag(void)
{
	return g_Va00E04018 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F6CCClearFlag(void)
{
	return g_Va00E04038 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F6F5ClearFlag(void)
{
	return g_Va00E04044 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F71EClearFlag(void)
{
	return g_Va00E04050 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F74AClearFlag(void)
{
	return g_Va00E04058 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F78BClearFlag(void)
{
	return g_Va00E04060 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F7A2ClearFlag(void)
{
	return g_Va00E04068 &= 0xFFFFFFFEu;
}
