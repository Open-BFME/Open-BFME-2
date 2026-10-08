// cl: /MD
// ?Rva0051280EEnable@@YAXXZ @0x0051280E 21B: if g_obj12F495C==0 return else tail-jmp Rva00222479ByteOneSetter::enable via TheRva00222A8BTarget; twin of Rva00433D27Enable Rva00516E92Enable
extern void *g_obj12F495C;
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00222479ByteOneSetter
{
public:
	void enable();
};
void Rva0051280EEnable()
{
	if (g_obj12F495C == 0)
		return;
	((Rva00222479ByteOneSetter *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->enable();
}
