// stlport
// cl: -Oy- -GR- -EHsc-
// ?Run@Rva005B5C70Box@@QAEXH@Z @0x005B5C70 132B: flagged entry apply.
// Resolves the selected index through the rowed GetSelected, fetches the
// entry through the rowed 3-arg getter, runs the rowed AptMyHero consumer
// 0x005B21DA on the +0x27C sub-object with the (a != 0) flag, stamps the byte +0x14, and
// unless a set +0x48 entry meets a cleared global, fires the rowed UI
// callback with the out-bool d. Rowed callees by matched names; the middle
// params are unused padding. Targets from retail REL32/DIR32.
class GameWindow;
void __cdecl GadgetListBoxGetSelected(GameWindow *w, int *sel);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
extern unsigned char g_rva005B5C02Flag;
void __cdecl Rva004E6816Fire(Rva00222A8BTarget *t, void *p, const char *s, bool *b);

struct Rva005B5C70Entry
{
	char pad[0x48];
	unsigned char m_48;

	void M3(struct Rva005B5C70Obj *o, int z, int f);
};

// The +0x27C sub-object is the AptMyHero panel; its rowed 0x005B21DA takes
// the entry as a CreateAHeroData record.
class CreateAHeroData;
#include "../../Include/GameClient/AptMyHero.h"

struct Rva005B5C70Mid
{
	char pad[0x274];
	void *m_274;
};

struct Rva005B5C70Box
{
	char pad[4];
	Rva005B5C70Mid *m_4;
	GameWindow *m_8;
	char pad2[0x14 - 0xc];
	unsigned char m_14;

	void Run(int a);
};

void Rva005B5C70Box::Run(int a)
{
	int selected;
	GadgetListBoxGetSelected(m_8, &selected);
	Rva005B5C70Entry *e = (Rva005B5C70Entry *)GadgetListBoxGetItemData(m_8, selected, 0);
	if (e == 0)
		return;
	AptMyHero *aptMyHero = (AptMyHero *)m_4;
	int flag = (((unsigned char *)&a)[0] != 0);
	aptMyHero = (AptMyHero *)((char *)aptMyHero + 0x27c);
	aptMyHero->rva005B21DA((CreateAHeroData *)e, false, flag);
	m_14 = 1;
	if (e->m_48 == 0)
		((unsigned char *)&a)[3] = 1;
	else {
		((unsigned char *)&a)[3] = 0;
		if (g_rva005B5C02Flag != 0)
			((unsigned char *)&a)[3] = 1;
	}
	Rva004E6816Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_4->m_274, "EnableCustomizeButtons", (bool *)&((unsigned char *)&a)[3]);
}
