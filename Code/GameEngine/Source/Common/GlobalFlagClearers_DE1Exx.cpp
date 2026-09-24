// Six B2-native flag-word clearers across six .data flag words of one
// contiguous run (0x0075D47B-0x0075F15C):
//
//     mov eax,[<address>] / and al,0xFE / mov [<address>],eax / ret
//
// All six clear al bit 0. Same /G7 byte-register narrowing as
// GlobalFlagClearers_08.cpp (defaults emit `and eax,imm`). Each body
// carries a .rdata table slot (0x008FF520 and on). Identity is not
// recovered; names derive from addresses, following
// GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DE1E48;
extern unsigned int g_Va00DE1E68;
extern unsigned int g_Va00DE1E70;
extern unsigned int g_Va00DE1F14;
extern unsigned int g_Va00DE1FC4;
extern unsigned int g_Va00DE1FF0;

unsigned int Rva0075D47BClearFlag(void)
{
	return g_Va00DE1E48 &= 0xFFFFFFFEu;
}

unsigned int Rva0075E42FClearFlag(void)
{
	return g_Va00DE1E68 &= 0xFFFFFFFEu;
}

unsigned int Rva0075E4D4ClearFlag(void)
{
	return g_Va00DE1E70 &= 0xFFFFFFFEu;
}

unsigned int Rva0075EEFDClearFlag(void)
{
	return g_Va00DE1F14 &= 0xFFFFFFFEu;
}

unsigned int Rva0075F04CClearFlag(void)
{
	return g_Va00DE1FC4 &= 0xFFFFFFFEu;
}

unsigned int Rva0075F15CClearFlag(void)
{
	return g_Va00DE1FF0 &= 0xFFFFFFFEu;
}
