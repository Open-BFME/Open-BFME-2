// cl: -GR- -EHsc-
// ?Run@Rva005C38EFBox@@QAEXXZ @0x005C38EF 59B: guarded triple dispatch.
// Resolves a handle through the first global's pinned 1-arg callee; a
// non-null handle must survive the second global (null-checked) and its
// pinned check, otherwise return; then the third global runs its pinned
// 2-arg callee on (+0xC, 0). Globals as named externs; targets from REL32.
// Row spellings of the three callees.
#include "GameLogicObjectLookupView.h"
class GameWindow;
class Rva002A7DDEArg;
#include "../../Include/Common/Rva002A7DDE.h"
#include "../../Include/GameClient/ControlBar.h"

extern GameLogic *TheGameLogic;
extern class PlayerList *ThePlayerList;
extern ControlBar *TheControlBar;

struct Rva005C38EFBox
{
	char pad[0xc];
	int m_C;
	int m_10;

	void Run();
};

void Rva005C38EFBox::Run()
{
	Object *object = TheGameLogic->findObjectByID((ObjectID)m_10);
	if (object != 0) {
		if ((*(Rva002A7DDE **)&ThePlayerList) == 0)
			return;
		if (!(*(Rva002A7DDE **)&ThePlayerList)->rva002A7DDE((Rva002A7DDEArg *)object))
			return;
	}
	TheControlBar->rva004C1B60((GameWindow *)m_C, 0);
}
