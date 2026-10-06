// cl: /MD
// ?Rva00415EF8Close@@YAXXZ @0x00415EF8 46B chain via 0x00516EE9.
// If g_Va00A04904 and g_Va00A03094 are set call Rva00517048 close then clear
// three globals. Evidence: caller 0x00415F0B sets ecx from g_Va00A04904;
// rowed callee 0x00516EE9; globals 0x00A03090 0x00A0308C 0x00A03094.
struct Rva00517048
{
	void rva00516EE9();
};
extern struct Rva00517048 *g_Va00A04904;
extern unsigned char g_Va00A03094;
extern int g_Va00A03090;
extern unsigned char g_Va00A0308C;

void Rva00415EF8Close()
{
	if (g_Va00A04904 != 0 && g_Va00A03094 != 0)
		g_Va00A04904->rva00516EE9();
	g_Va00A03090 = 0;
	g_Va00A0308C = 0;
	g_Va00A03094 = 0;
}
