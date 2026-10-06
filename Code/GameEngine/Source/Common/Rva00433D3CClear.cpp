// cl: /MD
// ?Rva00433D3CClear@@YAXXZ, retail 0x00433D3C, 17 bytes.
// If g_Va00E032E0 is non-null, clears byte at +0x29D.
// Evidence: global g_Va00E032E0 ?g_Va00E032E0@@3HA shared with 0x00433D27,
// caller at 0x0051E3D1.
extern int g_Va00E032E0;
void Rva00433D3CClear()
{
	char *p = (char *)g_Va00E032E0;
	if (!p)
		return;
	p[0x29D] = 0;
}
