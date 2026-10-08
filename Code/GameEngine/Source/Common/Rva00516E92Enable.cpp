// cl: /MD
// ?Rva00516E92Enable@@YAXXZ @0x00516E92 21B unlock via twin 0x00433D27.
// If g_Va00A04904 is null return else tail-jmp Rva00222479ByteOneSetter enable
// via TheRva00222A8BTarget. Evidence: same 21B shape as Rva00433D27Enable;
// globals 0x00A04904 and 0x009FE4CC with rowed callee 0x00222479.
struct Rva00517048;
extern struct Rva00517048 *g_Va00A04904;
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00222479ByteOneSetter
{
public:
	void enable();
};

void Rva00516E92Enable()
{
	if (g_Va00A04904 == 0)
		return;
	((Rva00222479ByteOneSetter *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->enable();
}
