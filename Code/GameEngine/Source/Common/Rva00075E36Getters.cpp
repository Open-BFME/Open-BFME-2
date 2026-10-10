// cl: /GX-
// ?Rva00075E36Get@@YAHXZ @ 0x00075E36 (6B): global dword getter reading
// 0x001FDE68 (mov eax,[mem]; ret). Ported from Open-BFME-1
// Code/GameEngine/Source/Common/GlobalDwordGetters.cpp (same shape).
// First of an adjacent pair (0x75E36/3C); dedicated TU so no caller
// inlines the load (Rva007EB810Get precedent).

extern int g_Va001FDE68;
// g_Va001FDE68: matched references place it at VA 0xde1f68 (zero-filled .bss).
int g_Va001FDE68;


// ?Rva00075E3CGet@@YAHXZ @ 0x00075E3C (6B): same shape over 0x001FDE58.

extern int g_Va001FDE58;
// g_Va001FDE58: matched references place it at VA 0xde1f58 (zero-filled .bss).
int g_Va001FDE58;

int Rva00075E3CGet(void)
{
	return g_Va001FDE58;
}
