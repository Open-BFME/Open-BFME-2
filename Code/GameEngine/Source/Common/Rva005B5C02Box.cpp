// cl: -Oy- -GR- -EHsc-
// ?Run@Rva005B5C02Box@@QAEXXZ @0x005B5C02 110B: list-entry apply. Resolves
// the selected index through the rowed GadgetListBoxGetSelected, fetches
// the entry through the rowed 3-arg getter (literal 0 CSEd into ebx for
// both the compare and the push), applies the +0x27C-adjusted use plus the
// list add through pinned 1-arg callees unless a set +0x48 entry meets a
// cleared global, and stamps +0x14. Rowed callees referenced by their
// matched names; rest from retail REL32/DIR32.
class GameWindow;
void __cdecl GadgetListBoxGetSelected(GameWindow *w, int *sel);
int __cdecl Rva003253BEGet(GameWindow *w, int a, int b);

extern unsigned char g_rva005B5C02Flag;
extern class CreateAHeroManager *TheCreateAHeroManager;

struct Rva005B5C02Entry
{
	char pad[0x48];
	unsigned char m_48;

	void Use(void *s);
};

struct Rva005B5C02List
{
	void Add(Rva005B5C02Entry *e);
};

struct Rva005B5C02Mgr
{
	Rva005B5C02List *List();
};

struct Rva005B5C02Box
{
	char pad[4];
	void *m_4;
	GameWindow *m_8;
	char pad2[0x14 - 0xc];
	unsigned char m_14;

	void Run();
};

void Rva005B5C02Box::Run()
{
	int r;
	GadgetListBoxGetSelected(m_8, &r);
	if (r < 0)
		return;
	Rva005B5C02Entry *e = (Rva005B5C02Entry *)Rva003253BEGet(m_8, r, 0);
	if (e == 0)
		return;
	if (e->m_48 != 0 && g_rva005B5C02Flag == 0)
		return;
	Rva005B5C02List *l = (*(Rva005B5C02Mgr **)&TheCreateAHeroManager)->List();
	e->Use((char *)m_4 + 0x27c);
	l->Add(e);
	m_14 = 1;
}
