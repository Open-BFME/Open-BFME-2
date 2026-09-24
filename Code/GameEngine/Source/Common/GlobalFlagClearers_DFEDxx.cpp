// Thirteen B2-native flag-word clearers across thirteen .data flag words
// of one contiguous run (0x00774353-0x00774780):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Twelve clear al bit 0, one clears al bit 1. Same /G7 byte-register
// narrowing as GlobalFlagClearers_08.cpp (defaults emit `and eax,imm`).
// Each body carries a .rdata table slot (0x0091B52C and on). Identity is
// not recovered; names derive from addresses, following
// GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFED08;
extern unsigned int g_Va00DFED10;
extern unsigned int g_Va00DFED18;
extern unsigned int g_Va00DFED20;
extern unsigned int g_Va00DFED28;
extern unsigned int g_Va00DFED30;
extern unsigned int g_Va00DFED38;
extern unsigned int g_Va00DFED48;
extern unsigned int g_Va00DFED54;
extern unsigned int g_Va00DFED5C;
extern unsigned int g_Va00DFED6C;
extern unsigned int g_Va00DFED74;
extern unsigned int g_Va00DFED7C;

unsigned int Rva00774353ClearFlag(void)
{
	return g_Va00DFED08 &= 0xFFFFFFFEu;
}

unsigned int Rva0077436AClearFlag(void)
{
	return g_Va00DFED10 &= 0xFFFFFFFEu;
}

unsigned int Rva00774381ClearFlag(void)
{
	return g_Va00DFED18 &= 0xFFFFFFFEu;
}

unsigned int Rva00774398ClearFlag(void)
{
	return g_Va00DFED20 &= 0xFFFFFFFEu;
}

unsigned int Rva007743AFClearFlag(void)
{
	return g_Va00DFED28 &= 0xFFFFFFFEu;
}

unsigned int Rva007743C6ClearFlag(void)
{
	return g_Va00DFED30 &= 0xFFFFFFFEu;
}

unsigned int Rva007743DDClearFlag(void)
{
	return g_Va00DFED38 &= 0xFFFFFFFEu;
}

unsigned int Rva00774461ClearFlag(void)
{
	return g_Va00DFED48 &= 0xFFFFFFFEu;
}

unsigned int Rva00774522ClearFlag(void)
{
	return g_Va00DFED54 &= 0xFFFFFFFEu;
}

unsigned int Rva00774539ClearFlag(void)
{
	return g_Va00DFED5C &= 0xFFFFFFFEu;
}

unsigned int Rva007746B0ClearFlag(void)
{
	return g_Va00DFED6C &= 0xFFFFFFFDu;
}

unsigned int Rva007746C7ClearFlag(void)
{
	return g_Va00DFED74 &= 0xFFFFFFFEu;
}

unsigned int Rva00774780ClearFlag(void)
{
	return g_Va00DFED7C &= 0xFFFFFFFEu;
}
