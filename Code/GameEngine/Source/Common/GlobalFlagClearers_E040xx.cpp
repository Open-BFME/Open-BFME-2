// Ten B2-native flag-word clearers on ten .data flag words
// (0x00E04000-0x00E04068):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_E033xx.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E033xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E04000;
extern unsigned int g_Va00E04008;
extern unsigned int g_Va00E04010;
extern unsigned int g_Va00E04018;
extern unsigned int g_Va00E04038;
extern unsigned int g_Va00E04044;
extern unsigned int g_Va00E04050;
extern unsigned int g_Va00E04058;
extern unsigned int g_Va00E04060;
extern unsigned int g_Va00E04068;
extern unsigned int g_Va00E04074;
extern unsigned int g_Va00E0407C;
extern unsigned int g_Va00E04084;
extern unsigned int g_Va00E04090;
extern unsigned int g_Va00E040B8;
extern unsigned int g_Va00E0411C;
extern unsigned int g_Va00E04128;
extern unsigned int g_Va00E04130;
extern unsigned int g_Va00E04138;
extern unsigned int g_Va00E04140;

unsigned int Rva0078F617ClearFlag(void)
{
	return g_Va00E04000 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F66AClearFlag(void)
{
	return g_Va00E04008 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F693ClearFlag(void)
{
	return g_Va00E04010 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F6AAClearFlag(void)
{
	return g_Va00E04018 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F6CCClearFlag(void)
{
	return g_Va00E04038 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F6F5ClearFlag(void)
{
	return g_Va00E04044 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F71EClearFlag(void)
{
	return g_Va00E04050 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F74AClearFlag(void)
{
	return g_Va00E04058 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F78BClearFlag(void)
{
	return g_Va00E04060 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F7A2ClearFlag(void)
{
	return g_Va00E04068 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F7CEClearFlag(void)
{
	return g_Va00E04074 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F817ClearFlag(void)
{
	return g_Va00E0407C &= 0xFFFFFFFEu;
}

unsigned int Rva0078F86AClearFlag(void)
{
	return g_Va00E04084 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F893ClearFlag(void)
{
	return g_Va00E04090 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FA4AClearFlag(void)
{
	return g_Va00E040B8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FB00ClearFlag(void)
{
	return g_Va00E0411C &= 0xFFFFFFFBu;
}

unsigned int Rva0078FB22ClearFlag(void)
{
	return g_Va00E04128 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FB39ClearFlag(void)
{
	return g_Va00E04130 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FB50ClearFlag(void)
{
	return g_Va00E04138 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FB67ClearFlag(void)
{
	return g_Va00E04140 &= 0xFFFFFFFEu;
}
