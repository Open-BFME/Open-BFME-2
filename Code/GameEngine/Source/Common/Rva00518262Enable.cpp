// cl: /GX-
// ?Rva00518262Enable@@YAXXZ @0x00518262 21B
// Guarded enabler: if int at 0x00A04908 is 0 return else tail-jmp to rowed
// enable 0x00222479 on global 0x009FE4CC. Evidence: 4 callers with no pushes
// ret void; rowed enable 0x00222479; precedent Rva00444040Enable 21B same shape.
class Rva00222479ByteOneSetter
{
public:
	void enable();
};
extern int g_Va00A04908;
// g_Va00A04908: VA 0xe04908 (zero-filled .bss).
int g_Va00A04908;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
void Rva00518262Enable(void)
{
	if (g_Va00A04908 == 0)
		return;
	(*(Rva00222479ByteOneSetter **)&g_bfmeAptWindowManager)->enable();
}
