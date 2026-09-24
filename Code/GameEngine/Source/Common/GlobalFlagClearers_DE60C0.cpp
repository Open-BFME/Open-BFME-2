// Ten B2-native flag-word clearers on the .data flag word g_Va00DE60C0:
//
//     mov eax,[<address>] / and al|ah,<mask8> / mov [<address>],eax / ret
//
// Bits 0-7 through al (eight bodies), bits 8-9 through ah (two bodies).
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot (0x0090373C
// and on, stride 0x10). Identity is not recovered; names derive from
// addresses, following GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DE60C0;

unsigned int Rva00760724ClearFlag(void)
{
	return g_Va00DE60C0 &= 0xFFFFFFFEu;
}

unsigned int Rva00760739ClearFlag(void)
{
	return g_Va00DE60C0 &= 0xFFFFFFFDu;
}

unsigned int Rva0076074EClearFlag(void)
{
	return g_Va00DE60C0 &= 0xFFFFFFFBu;
}

unsigned int Rva00760763ClearFlag(void)
{
	return g_Va00DE60C0 &= 0xFFFFFFF7u;
}

unsigned int Rva00760778ClearFlag(void)
{
	return g_Va00DE60C0 &= 0xFFFFFFEFu;
}

unsigned int Rva0076078DClearFlag(void)
{
	return g_Va00DE60C0 &= 0xFFFFFFDFu;
}

unsigned int Rva007607A2ClearFlag(void)
{
	return g_Va00DE60C0 &= 0xFFFFFFBFu;
}

unsigned int Rva007607B7ClearFlag(void)
{
	return g_Va00DE60C0 &= 0xFFFFFF7Fu;
}

unsigned int Rva007607CCClearFlag(void)
{
	return g_Va00DE60C0 &= 0xFFFFFEFFu;
}

unsigned int Rva007607E2ClearFlag(void)
{
	return g_Va00DE60C0 &= 0xFFFFFDFFu;
}
