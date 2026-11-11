// cl: /DNDEBUG /MD
// platformsdk
// ?GadgetCheckLikeButtonSetVisualCheck@@YAXPAVGameWindow@@_N@Z @0x00327C61 58B
// Check-like button set-checked: sets or clears bit 2 of WinInstanceData::m_state.
// Evidence: sibling ?GadgetCheckLikeButtonIsChecked@@YA_NPAVGameWindow@@@Z at 0x00327C9B
// reads the same bit; instance via rowed disp8 lea 0x00314046; status bit 0x80000 via
// GameWindow::winGetStatus pin 0x0030F45F (ICF twin of CategoryModuleClass getName).

#include <windows.h>

typedef bool Bool;
typedef unsigned int UnsignedInt;

#include "../../../../Include/GameClient/Bfme2GameWindow.h"


#include "../../../../Include/Common/Rva00314046LeaField.h"

void GadgetCheckLikeButtonSetVisualCheck(GameWindow *button, Bool checked)
{
	if (button == NULL)
		return;
	WinInstanceData *instData = (WinInstanceData *)((Rva00314046LeaField *)button)->get();
	if (instData == NULL)
		return;
	if ((button->winGetStatus() & 0x80000) == 0)
		return;
	if (checked == 1)
		instData->m_state |= 4;
	else
		instData->m_state &= ~4;
}
