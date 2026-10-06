// cl: /MD
// ?Rva0057A272Get@@YAPAGXZ @0x0057A272 62B
// Time separator one-time init via GetLocaleInfoW with ':' fallback.
// Evidence: GetLocaleInfoW(0x800 0x1E) into 5-WCHAR buffer at 0x00E06354 flag at 0x00E0635E caller 0x0057A62B.
extern "C" __declspec(dllimport) int __stdcall GetLocaleInfoW(unsigned long, unsigned long, unsigned short *, int);
// g_00E06354: matched references place it at VA 0xe06354 (zero-filled).
unsigned short g_00E06354[5] = { 0 };
extern unsigned char g_00E0635E;
// g_00E0635E: matched references place it at VA 0xe0635e (zero-filled .bss).
unsigned char g_00E0635E;
unsigned short *Rva0057A272Get(void)
{
	unsigned short *p = g_00E06354;
	if (!g_00E0635E)
	{
		if (!GetLocaleInfoW(0x800, 0x1E, p, 5))
		{
			p[1] = 0;
			p[0] = 0x3A;
		}
		g_00E0635E = 1;
	}
	return p;
}
