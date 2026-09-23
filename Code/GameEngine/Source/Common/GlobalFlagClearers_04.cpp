// Seven flag-word clearers sharing one shape:
//
//     mov eax,[<address>] / and eax,<mask> / mov [<address>],eax / ret
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/GlobalFlagClearers_04.cpp); trimmed to the
// seven T1 bodies the sweep places. A dword is read from a fixed .data
// address, one bit is cleared, and the result is written back and left in
// eax (`return g &= MASK`). Identity is not recovered; every name is derived
// from an address.

extern unsigned int g_Va012F1BC0;

unsigned int Rva00C26802ClearFlag(void)
{
	return g_Va012F1BC0 &= 0xFFFDFFFFu;
}

unsigned int Rva00C26812ClearFlag(void)
{
	return g_Va012F1BC0 &= 0xFFFBFFFFu;
}

unsigned int Rva00C26822ClearFlag(void)
{
	return g_Va012F1BC0 &= 0xFFF7FFFFu;
}

unsigned int Rva00C26832ClearFlag(void)
{
	return g_Va012F1BC0 &= 0xFFEFFFFFu;
}

unsigned int Rva00C26842ClearFlag(void)
{
	return g_Va012F1BC0 &= 0xFFDFFFFFu;
}

unsigned int Rva00C26852ClearFlag(void)
{
	return g_Va012F1BC0 &= 0xFFBFFFFFu;
}

unsigned int Rva00C26862ClearFlag(void)
{
	return g_Va012F1BC0 &= 0xDFFFFFFFu;
}

unsigned int Rva00C26872ClearFlag(void)
{
	return g_Va012F1BC0 &= 0xBFFFFFFFu;
}
