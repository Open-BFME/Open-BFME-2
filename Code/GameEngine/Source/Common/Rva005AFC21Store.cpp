class GameWindow;
void GadgetListBoxSetListLength(GameWindow* w, int len);
void __cdecl rva00381618(GameWindow* a, int b);

struct Rva005AFC21Class
{
	int m_0;
	int m_4;
	int m_8;
	GameWindow* m_C;

	void rva005AFC21(GameWindow* a1);
};

// cl: -GR- -EHsc-
// ?rva005AFC21@Rva005AFC21Class@@QAEXPAVGameWindow@@@Z @0x005AFC21 43B:
// stores the window, returns early on null, else forwards (window, 1000) to
// the rowed list-length helper and (m_4, m_C) to the pinned cdecl callee.
void Rva005AFC21Class::rva005AFC21(GameWindow* a1)
{
	m_C = a1;
	if (!a1)
		return;
	GadgetListBoxSetListLength(a1, 0x3E8);
	rva00381618(m_C, m_4);
}
