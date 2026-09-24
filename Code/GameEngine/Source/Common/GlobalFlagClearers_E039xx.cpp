// Twenty-seven B2-native flag-word clearers on 27 .data flag words
// (0x00E03904-0x00E039FC):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E038xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03904;
extern unsigned int g_Va00E0390C;
extern unsigned int g_Va00E03914;
extern unsigned int g_Va00E0391C;
extern unsigned int g_Va00E03924;
extern unsigned int g_Va00E03930;
extern unsigned int g_Va00E03938;
extern unsigned int g_Va00E03940;
extern unsigned int g_Va00E03948;
extern unsigned int g_Va00E03954;
extern unsigned int g_Va00E03960;
extern unsigned int g_Va00E0396C;
extern unsigned int g_Va00E03978;
extern unsigned int g_Va00E03984;
extern unsigned int g_Va00E0398C;
extern unsigned int g_Va00E0399C;
extern unsigned int g_Va00E039A4;
extern unsigned int g_Va00E039B0;
extern unsigned int g_Va00E039B8;
extern unsigned int g_Va00E039C0;
extern unsigned int g_Va00E039C8;
extern unsigned int g_Va00E039D0;
extern unsigned int g_Va00E039D8;
extern unsigned int g_Va00E039E0;
extern unsigned int g_Va00E039E8;
extern unsigned int g_Va00E039F4;
extern unsigned int g_Va00E039FC;

unsigned int Rva0078C4F2ClearFlag(void)
{
	return g_Va00E03904 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C509ClearFlag(void)
{
	return g_Va00E0390C &= 0xFFFFFFFEu;
}

unsigned int Rva0078C53AClearFlag(void)
{
	return g_Va00E03914 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C59DClearFlag(void)
{
	return g_Va00E0391C &= 0xFFFFFFFEu;
}

unsigned int Rva0078C60BClearFlag(void)
{
	return g_Va00E03924 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C634ClearFlag(void)
{
	return g_Va00E03930 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C68AClearFlag(void)
{
	return g_Va00E03938 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C6A9ClearFlag(void)
{
	return g_Va00E03940 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C714ClearFlag(void)
{
	return g_Va00E03948 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C765ClearFlag(void)
{
	return g_Va00E03954 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C7E5ClearFlag(void)
{
	return g_Va00E03960 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C82BClearFlag(void)
{
	return g_Va00E0396C &= 0xFFFFFFFEu;
}

unsigned int Rva0078C897ClearFlag(void)
{
	return g_Va00E03978 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C8AEClearFlag(void)
{
	return g_Va00E03984 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C8E2ClearFlag(void)
{
	return g_Va00E0398C &= 0xFFFFFFFEu;
}

unsigned int Rva0078C977ClearFlag(void)
{
	return g_Va00E0399C &= 0xFFFFFFFEu;
}

unsigned int Rva0078C9A0ClearFlag(void)
{
	return g_Va00E039A4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C9FBClearFlag(void)
{
	return g_Va00E039B0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CA8BClearFlag(void)
{
	return g_Va00E039B8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CAF6ClearFlag(void)
{
	return g_Va00E039C0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CB3CClearFlag(void)
{
	return g_Va00E039C8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CBB6ClearFlag(void)
{
	return g_Va00E039D0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CC01ClearFlag(void)
{
	return g_Va00E039D8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CC5CClearFlag(void)
{
	return g_Va00E039E0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CC85ClearFlag(void)
{
	return g_Va00E039E8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CCC8ClearFlag(void)
{
	return g_Va00E039F4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CDA4ClearFlag(void)
{
	return g_Va00E039FC &= 0xFFFFFFFEu;
}

