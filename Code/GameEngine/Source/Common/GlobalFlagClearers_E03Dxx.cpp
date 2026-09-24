// Twenty-four B2-native flag-word clearers on 24 .data flag words
// (0x00E03D00-0x00E03DF4):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E03Cxx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03D00;
extern unsigned int g_Va00E03D0C;
extern unsigned int g_Va00E03D14;
extern unsigned int g_Va00E03D20;
extern unsigned int g_Va00E03D2C;
extern unsigned int g_Va00E03D34;
extern unsigned int g_Va00E03D40;
extern unsigned int g_Va00E03D48;
extern unsigned int g_Va00E03D50;
extern unsigned int g_Va00E03D58;
extern unsigned int g_Va00E03D60;
extern unsigned int g_Va00E03D6C;
extern unsigned int g_Va00E03D78;
extern unsigned int g_Va00E03D88;
extern unsigned int g_Va00E03D90;
extern unsigned int g_Va00E03D9C;
extern unsigned int g_Va00E03DA4;
extern unsigned int g_Va00E03DB0;
extern unsigned int g_Va00E03DB8;
extern unsigned int g_Va00E03DC4;
extern unsigned int g_Va00E03DD0;
extern unsigned int g_Va00E03DDC;
extern unsigned int g_Va00E03DE8;
extern unsigned int g_Va00E03DF4;

unsigned int Rva0078E337ClearFlag(void)
{
	return g_Va00E03D00 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E38CClearFlag(void)
{
	return g_Va00E03D0C &= 0xFFFFFFFEu;
}

unsigned int Rva0078E426ClearFlag(void)
{
	return g_Va00E03D14 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E4DBClearFlag(void)
{
	return g_Va00E03D20 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E540ClearFlag(void)
{
	return g_Va00E03D2C &= 0xFFFFFFFEu;
}

unsigned int Rva0078E557ClearFlag(void)
{
	return g_Va00E03D34 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E58EClearFlag(void)
{
	return g_Va00E03D40 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E5A5ClearFlag(void)
{
	return g_Va00E03D48 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E5BCClearFlag(void)
{
	return g_Va00E03D50 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E5D3ClearFlag(void)
{
	return g_Va00E03D58 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E61FClearFlag(void)
{
	return g_Va00E03D60 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E677ClearFlag(void)
{
	return g_Va00E03D6C &= 0xFFFFFFFEu;
}

unsigned int Rva0078E722ClearFlag(void)
{
	return g_Va00E03D78 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E790ClearFlag(void)
{
	return g_Va00E03D88 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E887ClearFlag(void)
{
	return g_Va00E03D90 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E925ClearFlag(void)
{
	return g_Va00E03D9C &= 0xFFFFFFFEu;
}

unsigned int Rva0078E9AFClearFlag(void)
{
	return g_Va00E03DA4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EA48ClearFlag(void)
{
	return g_Va00E03DB0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EA71ClearFlag(void)
{
	return g_Va00E03DB8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EA88ClearFlag(void)
{
	return g_Va00E03DC4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EB0DClearFlag(void)
{
	return g_Va00E03DD0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EB36ClearFlag(void)
{
	return g_Va00E03DDC &= 0xFFFFFFFEu;
}

unsigned int Rva0078EB4DClearFlag(void)
{
	return g_Va00E03DE8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EB64ClearFlag(void)
{
	return g_Va00E03DF4 &= 0xFFFFFFFEu;
}

