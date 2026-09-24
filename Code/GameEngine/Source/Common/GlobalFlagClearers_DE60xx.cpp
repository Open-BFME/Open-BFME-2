// Thirteen B2-native flag-word clearers across six .data flag words of one
// contiguous run (0x007605CD-0x007608FD):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// All thirteen clear low al bits (0-2). Same /G7 byte-register narrowing
// as GlobalFlagClearers_08.cpp (defaults emit `and eax,imm`). Each body
// carries a .rdata table slot (0x00903598 and on). Identity is not
// recovered; names derive from addresses, following
// GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DE6078;
extern unsigned int g_Va00DE6090;
extern unsigned int g_Va00DE60D0;
extern unsigned int g_Va00DE60E0;
extern unsigned int g_Va00DE60F0;
extern unsigned int g_Va00DE6100;

unsigned int Rva007605CDClearFlag(void)
{
	return g_Va00DE6078 &= 0xFFFFFFFEu;
}

unsigned int Rva007606C6ClearFlag(void)
{
	return g_Va00DE6090 &= 0xFFFFFFFEu;
}

unsigned int Rva007606DBClearFlag(void)
{
	return g_Va00DE6090 &= 0xFFFFFFFDu;
}

unsigned int Rva007606F0ClearFlag(void)
{
	return g_Va00DE6090 &= 0xFFFFFFFBu;
}

unsigned int Rva00760705ClearFlag(void)
{
	return g_Va00DE6090 &= 0xFFFFFFF7u;
}

unsigned int Rva00760802ClearFlag(void)
{
	return g_Va00DE60D0 &= 0xFFFFFFFEu;
}

unsigned int Rva00760817ClearFlag(void)
{
	return g_Va00DE60D0 &= 0xFFFFFFFDu;
}

unsigned int Rva0076082CClearFlag(void)
{
	return g_Va00DE60D0 &= 0xFFFFFFFBu;
}

unsigned int Rva00760895ClearFlag(void)
{
	return g_Va00DE60E0 &= 0xFFFFFFFEu;
}

unsigned int Rva007608AAClearFlag(void)
{
	return g_Va00DE60E0 &= 0xFFFFFFFDu;
}

unsigned int Rva007608BFClearFlag(void)
{
	return g_Va00DE60E0 &= 0xFFFFFFFBu;
}

unsigned int Rva007608DEClearFlag(void)
{
	return g_Va00DE60F0 &= 0xFFFFFFFEu;
}

unsigned int Rva007608FDClearFlag(void)
{
	return g_Va00DE6100 &= 0xFFFFFFFEu;
}
