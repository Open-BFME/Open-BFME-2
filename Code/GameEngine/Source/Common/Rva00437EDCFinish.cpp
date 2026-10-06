// cl: /MD
// ?Rva00437EDCGet@@YA_NXZ @0x00437EDC 18B null-checks g_Va00E032FC then tail-calls Rva0054C88A::rva0054C88A.
// Evidence: packet disassembly; global g_Va00E032FC ?g_Va00E032FC@@3HA; callee row ?rva0054C88A@Rva0054C88A@@QAE_NXZ; callers test al as bool with no pushes.
extern int g_Va00E032FC;

class Rva0054C88A
{
public:
	bool rva0054C88A();
};

bool Rva00437EDCGet()
{
	Rva0054C88A *p = (Rva0054C88A *)g_Va00E032FC;
	if (p == 0)
		return false;
	return p->rva0054C88A();
}