// Twelve B2-native flag-word clearers on ten scattered .data flag words
// (0x00774B31-0x00777532):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot (0x0091BF1C
// and on). Identity is not recovered; names derive from addresses,
// following GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFEEA8;
extern unsigned int g_Va00DFEEB0;
extern unsigned int g_Va00DFEEC4;
extern unsigned int g_Va00DFEEDC;
extern unsigned int g_Va00DFEEE4;
extern unsigned int g_Va00DFEF04;
extern unsigned int g_Va00DFF038;
extern unsigned int g_Va00DFF04C;
extern unsigned int g_Va00DFF058;
extern unsigned int g_Va00DFF064;

unsigned int Rva00774B31ClearFlag(void)
{
	return g_Va00DFEEA8 &= 0xFFFFFFFEu;
}

unsigned int Rva00774B58ClearFlag(void)
{
	return g_Va00DFEEB0 &= 0xFFFFFFFEu;
}

unsigned int Rva00774D4CClearFlag(void)
{
	return g_Va00DFEEC4 &= 0xFFFFFFFDu;
}

unsigned int Rva00774E90ClearFlag(void)
{
	return g_Va00DFEEDC &= 0xFFFFFFFDu;
}

unsigned int Rva00774F3FClearFlag(void)
{
	return g_Va00DFEEE4 &= 0xFFFFFFFEu;
}

unsigned int Rva00775A83ClearFlag(void)
{
	return g_Va00DFEF04 &= 0xFFFFFFFEu;
}

unsigned int Rva007773D8ClearFlag(void)
{
	return g_Va00DFF038 &= 0xFFFFFFFEu;
}

unsigned int Rva007774EAClearFlag(void)
{
	return g_Va00DFF04C &= 0xFFFFFFFDu;
}

unsigned int Rva00777501ClearFlag(void)
{
	return g_Va00DFF058 &= 0xFFFFFFFEu;
}

unsigned int Rva0077750EClearFlag(void)
{
	return g_Va00DFF058 &= 0xFFFFFFFDu;
}

unsigned int Rva00777525ClearFlag(void)
{
	return g_Va00DFF064 &= 0xFFFFFFFEu;
}

unsigned int Rva00777532ClearFlag(void)
{
	return g_Va00DFF064 &= 0xFFFFFFFDu;
}
