// cl: /GX-
// ?Rva00075E3CGet@@YAHXZ @ 0x00075E3C (6B): same shape over 0x001FDE58.

extern int g_Va001FDE58;
// g_Va001FDE58: matched references place it at VA 0xde1f58 (zero-filled .bss).
int g_Va001FDE58;

int Rva00075E3CGet(void)
{
	return g_Va001FDE58;
}
