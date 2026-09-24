// Twenty-five B2-native flag-word clearers on 25 .data flag words
// (0x00E03F00-0x00E03FF4):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E03Exx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03F00;
extern unsigned int g_Va00E03F0C;
extern unsigned int g_Va00E03F18;
extern unsigned int g_Va00E03F24;
extern unsigned int g_Va00E03F30;
extern unsigned int g_Va00E03F3C;
extern unsigned int g_Va00E03F48;
extern unsigned int g_Va00E03F54;
extern unsigned int g_Va00E03F60;
extern unsigned int g_Va00E03F6C;
extern unsigned int g_Va00E03F74;
extern unsigned int g_Va00E03F7C;
extern unsigned int g_Va00E03F84;
extern unsigned int g_Va00E03F8C;
extern unsigned int g_Va00E03F94;
extern unsigned int g_Va00E03F9C;
extern unsigned int g_Va00E03FA4;
extern unsigned int g_Va00E03FAC;
extern unsigned int g_Va00E03FB4;
extern unsigned int g_Va00E03FBC;
extern unsigned int g_Va00E03FC8;
extern unsigned int g_Va00E03FD0;
extern unsigned int g_Va00E03FDC;
extern unsigned int g_Va00E03FE8;
extern unsigned int g_Va00E03FF4;

unsigned int Rva0078EFE7ClearFlag(void)
{
	return g_Va00E03F00 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F098ClearFlag(void)
{
	return g_Va00E03F0C &= 0xFFFFFFFEu;
}

unsigned int Rva0078F0AFClearFlag(void)
{
	return g_Va00E03F18 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F11CClearFlag(void)
{
	return g_Va00E03F24 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F165ClearFlag(void)
{
	return g_Va00E03F30 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F17CClearFlag(void)
{
	return g_Va00E03F3C &= 0xFFFFFFFEu;
}

unsigned int Rva0078F193ClearFlag(void)
{
	return g_Va00E03F48 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F1AAClearFlag(void)
{
	return g_Va00E03F54 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F1C1ClearFlag(void)
{
	return g_Va00E03F60 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F1D8ClearFlag(void)
{
	return g_Va00E03F6C &= 0xFFFFFFFEu;
}

unsigned int Rva0078F1EFClearFlag(void)
{
	return g_Va00E03F74 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F206ClearFlag(void)
{
	return g_Va00E03F7C &= 0xFFFFFFFEu;
}

unsigned int Rva0078F21DClearFlag(void)
{
	return g_Va00E03F84 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F263ClearFlag(void)
{
	return g_Va00E03F8C &= 0xFFFFFFFEu;
}

unsigned int Rva0078F27AClearFlag(void)
{
	return g_Va00E03F94 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F291ClearFlag(void)
{
	return g_Va00E03F9C &= 0xFFFFFFFEu;
}

unsigned int Rva0078F2A8ClearFlag(void)
{
	return g_Va00E03FA4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F2EBClearFlag(void)
{
	return g_Va00E03FAC &= 0xFFFFFFFEu;
}

unsigned int Rva0078F302ClearFlag(void)
{
	return g_Va00E03FB4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F319ClearFlag(void)
{
	return g_Va00E03FBC &= 0xFFFFFFFEu;
}

unsigned int Rva0078F362ClearFlag(void)
{
	return g_Va00E03FC8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F3B5ClearFlag(void)
{
	return g_Va00E03FD0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F533ClearFlag(void)
{
	return g_Va00E03FDC &= 0xFFFFFFFEu;
}

unsigned int Rva0078F5A8ClearFlag(void)
{
	return g_Va00E03FE8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078F5D1ClearFlag(void)
{
	return g_Va00E03FF4 &= 0xFFFFFFFEu;
}

