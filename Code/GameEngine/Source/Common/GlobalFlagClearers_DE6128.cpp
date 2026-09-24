// Six B2-native flag-word clearers on the .data flag word g_Va00DE6128:
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Bits 1-6 through al. Same /G7 byte-register narrowing as
// GlobalFlagClearers_08.cpp (defaults emit `and eax,imm`). Each body
// carries a .rdata table slot (0x009039EC and on, stride 0x10). Identity
// is not recovered; names derive from addresses, following
// GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DE6128;

unsigned int Rva00760981ClearFlag(void)
{
	return g_Va00DE6128 &= 0xFFFFFFFDu;
}

unsigned int Rva00760996ClearFlag(void)
{
	return g_Va00DE6128 &= 0xFFFFFFFBu;
}

unsigned int Rva007609ABClearFlag(void)
{
	return g_Va00DE6128 &= 0xFFFFFFF7u;
}

unsigned int Rva007609C0ClearFlag(void)
{
	return g_Va00DE6128 &= 0xFFFFFFEFu;
}

unsigned int Rva007609D5ClearFlag(void)
{
	return g_Va00DE6128 &= 0xFFFFFFDFu;
}

unsigned int Rva007609EAClearFlag(void)
{
	return g_Va00DE6128 &= 0xFFFFFFBFu;
}
