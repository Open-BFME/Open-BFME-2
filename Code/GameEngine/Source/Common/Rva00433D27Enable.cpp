// cl: /MD
// ?Rva00433D27Enable@@YAXXZ @0x00433D27 21B: if g_Va00E032E0==0 return else tail-jmp Rva00222479ByteOneSetter::enable via TheRva00222A8BTarget; callers 0x002B8875 0x00433DAC
extern int g_Va00E032E0;
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00222479ByteOneSetter
{
public:
	void enable();
};
void Rva00433D27Enable()
{
	if (g_Va00E032E0 == 0)
		return;
	((Rva00222479ByteOneSetter *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->enable();
}
