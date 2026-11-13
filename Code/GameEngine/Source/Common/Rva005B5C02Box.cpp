// cl: -Oy- -GR- -EHsc-
// ?Run@Rva005B5C02Box@@QAEXXZ @0x005B5C02 110B: list-entry apply. Resolves
// the selected index through the rowed GadgetListBoxGetSelected, fetches
// the entry through the rowed 3-arg getter (literal 0 CSEd into ebx for
// both the compare and the push), copies the +0x27C record into the entry
// (CreateAHeroData::operator=) and adds it to the manager's hero list
// unless a set +0x48 entry meets a cleared global, and stamps +0x14. Rowed
// callees referenced by their matched names; rest from retail REL32/DIR32.
class GameWindow;
void __cdecl GadgetListBoxGetSelected(GameWindow *w, int *sel);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);

extern unsigned char g_rva005B5C02Flag;

// The entry is a CreateAHeroData record: the "use" call at 0x005B5C5A is its
// rowed copy assignment 0x00409359 from the record at +0x27C.
#include "../../Include/GameLogic/CreateAHeroData.h"

struct Rva005B5C02Entry
{
	char pad[0x48];
	unsigned char m_48;
};

// The rowed bool-returning add 0x0040A384 (result unused here).
#include "../../Include/Common/Rva005B5C02List.h"

// The manager's rowed hero-list fetch 0x0021F797.
class Rva0040A3F9;
#include "../../Include/GameLogic/CreateAHeroManager.h"
extern CreateAHeroManager *TheCreateAHeroManager;

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
	Rva005B5C02Entry *e = (Rva005B5C02Entry *)GadgetListBoxGetItemData(m_8, r, 0);
	if (e == 0)
		return;
	if (e->m_48 != 0 && g_rva005B5C02Flag == 0)
		return;
	Rva005B5C02List *l = (Rva005B5C02List *)TheCreateAHeroManager->rva0021F797();
	*(CreateAHeroData *)e = *(const CreateAHeroData *)((char *)m_4 + 0x27c);
	l->Add(e);
	m_14 = 1;
}
