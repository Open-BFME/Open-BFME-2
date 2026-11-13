// cl: /DNDEBUG /MD
// ?rva00323619@Rva00323619@@QAEXH@Z @0x00323619 41B
// Setter through GameWindow userData: *this+0 is GameWindow* via rowed winGetUserData 0x005C4ACD then store (TheWritableGlobalData+0x34 * arg)/0x300 into userData+0. Early-out when *this is null. ret 4.
// Evidence: callees rowed 0x005C4ACD plus TheWritableGlobalData ?TheWritableGlobalData@@3PAVGlobalData@@A; callers 0x0044045A 0x005BA907.
#include "../../../../Include/GameClient/Bfme2GameWindow.h"

#include "../../../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;

#include "../../../../Include/Common/Rva00323619.h"

void GadgetListBoxReset(GameWindow *listbox);

void Rva00323619::rva00323619(int v)
{
	GameWindow *gameWindow = m_window;
	if (gameWindow == 0)
		return;
	int *p = (int *)gameWindow->winGetUserData();
	*p = (TheWritableGlobalData->m_yResolution * v) / 0x300;
}

// ?rva00323642@Rva00323619@@QAEXXZ @0x00323642 21B
// Adjacent method of same class: *this+0 GameWindow* null-guarded then GadgetListBoxReset(*(GameWindow**)(userData+8)).
// Evidence: callees rowed 0x005C4ACD winGetUserData plus 0x003247E5 GadgetListBoxReset; prev row same class.
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline void Rva00323619::rva00323642()
{
	GameWindow *w = m_window;
	if (w == 0)
		return;
	void *userData = w->winGetUserData();
	GadgetListBoxReset(*(GameWindow **)((char *)userData + 8));
}

// ?bfmeAnchorRva00323619 absent-from-retail
void bfmeAnchorRva00323619(Rva00323619 *p)
{
	p->rva00323642();
}

