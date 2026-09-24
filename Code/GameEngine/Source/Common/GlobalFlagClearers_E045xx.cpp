// Fourteen B2-native flag-word clearers on 10 .data flag words
// (0x00E04554-0x00E045FC):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E044xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E04554;
extern unsigned int g_Va00E0456C;
extern unsigned int g_Va00E04578;
extern unsigned int g_Va00E04584;
extern unsigned int g_Va00E0458C;
extern unsigned int g_Va00E04594;
extern unsigned int g_Va00E0459C;
extern unsigned int g_Va00E045A8;
extern unsigned int g_Va00E045E8;
extern unsigned int g_Va00E045FC;

unsigned int Rva007941ACClearFlag(void)
{
	return g_Va00E04554 &= 0xFFFFFFFEu;
}

unsigned int Rva007942D4ClearFlag(void)
{
	return g_Va00E0456C &= 0xFFFFFFFEu;
}

unsigned int Rva007942E1ClearFlag(void)
{
	return g_Va00E0456C &= 0xFFFFFFFDu;
}

unsigned int Rva0079431CClearFlag(void)
{
	return g_Va00E04578 &= 0xFFFFFFFEu;
}

unsigned int Rva007943B0ClearFlag(void)
{
	return g_Va00E04584 &= 0xFFFFFFFEu;
}

unsigned int Rva007943C7ClearFlag(void)
{
	return g_Va00E0458C &= 0xFFFFFFFEu;
}

unsigned int Rva007943DEClearFlag(void)
{
	return g_Va00E04594 &= 0xFFFFFFFEu;
}

unsigned int Rva007943FDClearFlag(void)
{
	return g_Va00E0459C &= 0xFFFFFFFEu;
}

unsigned int Rva0079441CClearFlag(void)
{
	return g_Va00E045A8 &= 0xFFFFFFFEu;
}

unsigned int Rva007946BDClearFlag(void)
{
	return g_Va00E045E8 &= 0xFFFFFFFEu;
}

unsigned int Rva007946CAClearFlag(void)
{
	return g_Va00E045E8 &= 0xFFFFFFFDu;
}

unsigned int Rva00794749ClearFlag(void)
{
	return g_Va00E045FC &= 0xFFFFFFFEu;
}

unsigned int Rva00794756ClearFlag(void)
{
	return g_Va00E045FC &= 0xFFFFFFFDu;
}

unsigned int Rva00794763ClearFlag(void)
{
	return g_Va00E045FC &= 0xFFFFFFFBu;
}

