// Twelve B2-native flag-word clearers across eleven .data flag words of
// one contiguous run (0x0076E64F-0x0076E850):
//
//     mov eax,[<address>] / and al,0xFE / mov [<address>],eax / ret
//
// All twelve clear al bit 0. Same /G7 byte-register narrowing as
// GlobalFlagClearers_08.cpp (defaults emit `and eax,imm`). Each body
// carries a .rdata table slot (0x0091446C and on). Identity is not
// recovered; names derive from addresses, following
// GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFE3EC;
extern unsigned int g_Va00DFE3F4;
extern unsigned int g_Va00DFE3FC;
extern unsigned int g_Va00DFE404;
extern unsigned int g_Va00DFE40C;
extern unsigned int g_Va00DFE414;
extern unsigned int g_Va00DFE41C;
extern unsigned int g_Va00DFE424;
extern unsigned int g_Va00DFE42C;
extern unsigned int g_Va00DFE434;
extern unsigned int g_Va00DFE43C;
extern unsigned int g_Va00DFE444;

unsigned int Rva0076E64FClearFlag(void)
{
	return g_Va00DFE3EC &= 0xFFFFFFFEu;
}

unsigned int Rva0076E666ClearFlag(void)
{
	return g_Va00DFE3F4 &= 0xFFFFFFFEu;
}

unsigned int Rva0076E67DClearFlag(void)
{
	return g_Va00DFE3FC &= 0xFFFFFFFEu;
}

unsigned int Rva0076E694ClearFlag(void)
{
	return g_Va00DFE404 &= 0xFFFFFFFEu;
}

unsigned int Rva0076E6ABClearFlag(void)
{
	return g_Va00DFE40C &= 0xFFFFFFFEu;
}

unsigned int Rva0076E6C2ClearFlag(void)
{
	return g_Va00DFE414 &= 0xFFFFFFFEu;
}

unsigned int Rva0076E6D9ClearFlag(void)
{
	return g_Va00DFE41C &= 0xFFFFFFFEu;
}

unsigned int Rva0076E6F0ClearFlag(void)
{
	return g_Va00DFE424 &= 0xFFFFFFFEu;
}

unsigned int Rva0076E707ClearFlag(void)
{
	return g_Va00DFE42C &= 0xFFFFFFFEu;
}

unsigned int Rva0076E71EClearFlag(void)
{
	return g_Va00DFE434 &= 0xFFFFFFFEu;
}

unsigned int Rva0076E735ClearFlag(void)
{
	return g_Va00DFE43C &= 0xFFFFFFFEu;
}

unsigned int Rva0076E850ClearFlag(void)
{
	return g_Va00DFE444 &= 0xFFFFFFFEu;
}
