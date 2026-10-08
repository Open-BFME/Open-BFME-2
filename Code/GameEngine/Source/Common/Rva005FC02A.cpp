// cl: /MD
// ?rva005FC02A@Rva005FC02A@@QAEXXZ @0x005FC02A 58B
// Apt FadeOut call with level at +4 and prefix from +8 (+8 name) then state 2 at +0x1c, tail-jmp to rowed 0x005FBEBA audio remove.
// Evidence: calls rowed 0x00524EF4 AptCall; tail jmp to rowed 0x005FBEBA; caller thunk 0x005FC1A6 loads ecx+4; same +4 level and +8 outer layout as Rva005FBFE5 neighbour; FadeOut literal; empty-string and TheTarget globals.
class Rva00222A8BTarget
{
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

class Rva005FBEBA
{
public:
	void rva005FBEBA();
};

struct Rva005FC02AInner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva005FC02A
{
public:
	void rva005FC02A();
private:
	char m_pad00[4];
	int m_04;
	Rva005FC02AInner *m_08;
	char m_pad0C[0x10];
	int m_1C;
	char m_pad20[4];
	int m_handle24;
};

void Rva005FC02A::rva005FC02A()
{
	const char *prefix = m_08 ? m_08->m_name : "";
	Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_04, prefix, "FadeOut");
	m_1C = 2;
	((Rva005FBEBA *)this)->rva005FBEBA();
}
