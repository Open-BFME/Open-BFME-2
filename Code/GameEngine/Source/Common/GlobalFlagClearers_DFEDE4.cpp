// Ten B2-native flag-word clearers across three .data flag words of one
// contiguous run (0x0077489D-0x00774AA2):
//
//     mov eax,[<address>] / and al|ah,<mask8> / mov [<address>],eax / ret
//
// Four clear al bits 0/2/4/6 on g_Va00DFEDE4, four clear ah bits 8/10/12/15
// on the same word, plus two al bit-0 singles. Same /G7 byte-register
// narrowing as GlobalFlagClearers_08.cpp (defaults emit `and eax,imm`).
// Each body carries a .rdata table slot (0x0091BC2C and on). Identity is
// not recovered; names derive from addresses, following
// GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFEDE4;
extern unsigned int g_Va00DFEDEC;
extern unsigned int g_Va00DFEE10;

unsigned int Rva0077489DClearFlag(void)
{
	return g_Va00DFEDE4 &= 0xFFFFFFFEu;
}

unsigned int Rva007748B4ClearFlag(void)
{
	return g_Va00DFEDE4 &= 0xFFFFFFFBu;
}

unsigned int Rva007748CBClearFlag(void)
{
	return g_Va00DFEDE4 &= 0xFFFFFFEFu;
}

unsigned int Rva007748E2ClearFlag(void)
{
	return g_Va00DFEDE4 &= 0xFFFFFFBFu;
}

unsigned int Rva007748F9ClearFlag(void)
{
	return g_Va00DFEDE4 &= 0xFFFFFEFFu;
}

unsigned int Rva00774911ClearFlag(void)
{
	return g_Va00DFEDE4 &= 0xFFFFFBFFu;
}

unsigned int Rva00774929ClearFlag(void)
{
	return g_Va00DFEDE4 &= 0xFFFFEFFFu;
}

unsigned int Rva00774957ClearFlag(void)
{
	return g_Va00DFEDE4 &= 0xFFFF7FFFu;
}

unsigned int Rva00774A8BClearFlag(void)
{
	return g_Va00DFEDEC &= 0xFFFFFFFEu;
}

unsigned int Rva00774AA2ClearFlag(void)
{
	return g_Va00DFEE10 &= 0xFFFFFFFEu;
}
