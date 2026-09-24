// Twenty-six B2-native flag-word clearers on 26 .data flag words
// (0x00E03804-0x00E038FC):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E037xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03804;
extern unsigned int g_Va00E0380C;
extern unsigned int g_Va00E03814;
extern unsigned int g_Va00E0381C;
extern unsigned int g_Va00E03828;
extern unsigned int g_Va00E03834;
extern unsigned int g_Va00E0383C;
extern unsigned int g_Va00E03844;
extern unsigned int g_Va00E03850;
extern unsigned int g_Va00E03858;
extern unsigned int g_Va00E03864;
extern unsigned int g_Va00E03870;
extern unsigned int g_Va00E03878;
extern unsigned int g_Va00E03880;
extern unsigned int g_Va00E03890;
extern unsigned int g_Va00E03898;
extern unsigned int g_Va00E038A4;
extern unsigned int g_Va00E038B0;
extern unsigned int g_Va00E038B8;
extern unsigned int g_Va00E038C4;
extern unsigned int g_Va00E038CC;
extern unsigned int g_Va00E038D8;
extern unsigned int g_Va00E038E0;
extern unsigned int g_Va00E038E8;
extern unsigned int g_Va00E038F0;
extern unsigned int g_Va00E038FC;

unsigned int Rva0078BE48ClearFlag(void)
{
	return g_Va00E03804 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BEFEClearFlag(void)
{
	return g_Va00E0380C &= 0xFFFFFFFEu;
}

unsigned int Rva0078BF27ClearFlag(void)
{
	return g_Va00E03814 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BF3EClearFlag(void)
{
	return g_Va00E0381C &= 0xFFFFFFFEu;
}

unsigned int Rva0078BF67ClearFlag(void)
{
	return g_Va00E03828 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BF90ClearFlag(void)
{
	return g_Va00E03834 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BFA7ClearFlag(void)
{
	return g_Va00E0383C &= 0xFFFFFFFEu;
}

unsigned int Rva0078BFD0ClearFlag(void)
{
	return g_Va00E03844 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C03EClearFlag(void)
{
	return g_Va00E03850 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C055ClearFlag(void)
{
	return g_Va00E03858 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C081ClearFlag(void)
{
	return g_Va00E03864 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C098ClearFlag(void)
{
	return g_Va00E03870 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C0AFClearFlag(void)
{
	return g_Va00E03878 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C0C6ClearFlag(void)
{
	return g_Va00E03880 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C0EFClearFlag(void)
{
	return g_Va00E03890 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C106ClearFlag(void)
{
	return g_Va00E03898 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C11DClearFlag(void)
{
	return g_Va00E038A4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C146ClearFlag(void)
{
	return g_Va00E038B0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C16FClearFlag(void)
{
	return g_Va00E038B8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C186ClearFlag(void)
{
	return g_Va00E038C4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C22AClearFlag(void)
{
	return g_Va00E038CC &= 0xFFFFFFFEu;
}

unsigned int Rva0078C2B8ClearFlag(void)
{
	return g_Va00E038D8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C2F3ClearFlag(void)
{
	return g_Va00E038E0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C30AClearFlag(void)
{
	return g_Va00E038E8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C428ClearFlag(void)
{
	return g_Va00E038F0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C4A1ClearFlag(void)
{
	return g_Va00E038FC &= 0xFFFFFFFEu;
}

