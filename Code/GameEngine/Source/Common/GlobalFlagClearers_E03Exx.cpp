// Twenty-three B2-native flag-word clearers on 23 .data flag words
// (0x00E03E00-0x00E03EF4):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E03Dxx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03E00;
extern unsigned int g_Va00E03E08;
extern unsigned int g_Va00E03E10;
extern unsigned int g_Va00E03E1C;
extern unsigned int g_Va00E03E28;
extern unsigned int g_Va00E03E30;
extern unsigned int g_Va00E03E38;
extern unsigned int g_Va00E03E44;
extern unsigned int g_Va00E03E50;
extern unsigned int g_Va00E03E5C;
extern unsigned int g_Va00E03E68;
extern unsigned int g_Va00E03E74;
extern unsigned int g_Va00E03E80;
extern unsigned int g_Va00E03E8C;
extern unsigned int g_Va00E03E98;
extern unsigned int g_Va00E03EA4;
extern unsigned int g_Va00E03EB0;
extern unsigned int g_Va00E03EBC;
extern unsigned int g_Va00E03EC8;
extern unsigned int g_Va00E03ED4;
extern unsigned int g_Va00E03EE0;
extern unsigned int g_Va00E03EE8;
extern unsigned int g_Va00E03EF4;

unsigned int Rva0078EB7BClearFlag(void)
{
	return g_Va00E03E00 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EB92ClearFlag(void)
{
	return g_Va00E03E08 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EBD7ClearFlag(void)
{
	return g_Va00E03E10 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EBEEClearFlag(void)
{
	return g_Va00E03E1C &= 0xFFFFFFFEu;
}

unsigned int Rva0078EC05ClearFlag(void)
{
	return g_Va00E03E28 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EC2EClearFlag(void)
{
	return g_Va00E03E30 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EC45ClearFlag(void)
{
	return g_Va00E03E38 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EC5CClearFlag(void)
{
	return g_Va00E03E44 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EC73ClearFlag(void)
{
	return g_Va00E03E50 &= 0xFFFFFFFEu;
}

unsigned int Rva0078ECE6ClearFlag(void)
{
	return g_Va00E03E5C &= 0xFFFFFFFEu;
}

unsigned int Rva0078ECFDClearFlag(void)
{
	return g_Va00E03E68 &= 0xFFFFFFFEu;
}

unsigned int Rva0078ED14ClearFlag(void)
{
	return g_Va00E03E74 &= 0xFFFFFFFEu;
}

unsigned int Rva0078ED2BClearFlag(void)
{
	return g_Va00E03E80 &= 0xFFFFFFFEu;
}

unsigned int Rva0078ED42ClearFlag(void)
{
	return g_Va00E03E8C &= 0xFFFFFFFEu;
}

unsigned int Rva0078ED59ClearFlag(void)
{
	return g_Va00E03E98 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EDF6ClearFlag(void)
{
	return g_Va00E03EA4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EE5BClearFlag(void)
{
	return g_Va00E03EB0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EE72ClearFlag(void)
{
	return g_Va00E03EBC &= 0xFFFFFFFEu;
}

unsigned int Rva0078EE89ClearFlag(void)
{
	return g_Va00E03EC8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EEA0ClearFlag(void)
{
	return g_Va00E03ED4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EEB7ClearFlag(void)
{
	return g_Va00E03EE0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EEE8ClearFlag(void)
{
	return g_Va00E03EE8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EF1CClearFlag(void)
{
	return g_Va00E03EF4 &= 0xFFFFFFFEu;
}

