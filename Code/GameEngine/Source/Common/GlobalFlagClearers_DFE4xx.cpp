// Eight B2-native flag-word clearers across five .data flag words of one
// contiguous run (0x0076E867-0x0076EB92):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot (0x009147A0
// and on). Identity is not recovered; names derive from addresses,
// following GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFE44C;
extern unsigned int g_Va00DFE458;
extern unsigned int g_Va00DFE464;
extern unsigned int g_Va00DFE470;
extern unsigned int g_Va00DFE478;

unsigned int Rva0076E867ClearFlag(void)
{
	return g_Va00DFE44C &= 0xFFFFFFFEu;
}

unsigned int Rva0076E8CAClearFlag(void)
{
	return g_Va00DFE458 &= 0xFFFFFFFEu;
}

unsigned int Rva0076E8D7ClearFlag(void)
{
	return g_Va00DFE458 &= 0xFFFFFFFDu;
}

unsigned int Rva0076E9A4ClearFlag(void)
{
	return g_Va00DFE464 &= 0xFFFFFFFEu;
}

unsigned int Rva0076E9B1ClearFlag(void)
{
	return g_Va00DFE464 &= 0xFFFFFFFDu;
}

unsigned int Rva0076E9E0ClearFlag(void)
{
	return g_Va00DFE470 &= 0xFFFFFFFEu;
}

unsigned int Rva0076E9EDClearFlag(void)
{
	return g_Va00DFE470 &= 0xFFFFFFFDu;
}

unsigned int Rva0076EB92ClearFlag(void)
{
	return g_Va00DFE478 &= 0xFFFFFFFEu;
}
