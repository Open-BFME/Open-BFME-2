// cl: /DNDEBUG /MD
// platformsdk
// ?Rva003229C5Hide@@YAXPAVGameWindow@@@Z @0x003229C5 132B.
// ZH/BFME1 donor GadgetComboBox.cpp HideListBox: null listBox guard then
// winIsHidden then winHide TRUE then entry size and combo size then
// winSetSize(newSize.x winSize.y). BFME2 adds loneWindow focus release.
// Retail calls 0x002C0315 listBox +0x2c rowed as bfmeGo925A then winIsHidden
// 0x313CD9 winHide 0x313C64 then 0x002C032C entry +0x28 rowed as GetListBox
// then winGetSize 0x313BC6 twice winSetSize 0x313B87 then manager 0xD4 get
// 0xD0 set; 5 callers include 0x00322BB8 0x00322FF5.
typedef int Int;
typedef bool Bool;

#include <windows.h>
#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

class GameWindow;
class BfmeKeyLC;

void *bfmeGo925A(BfmeKeyLC *k);
GameWindow *GadgetComboBoxGetListBox(GameWindow *comboBox);

#include "../../../../Include/GameClient/Bfme2GameWindow.h"

#include "../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

void Rva003229C5Hide(GameWindow *window)
{
	ICoord2D winSize;
	ICoord2D newSize;
	GameWindow *listBox = (GameWindow *)bfmeGo925A((BfmeKeyLC *)window);
	if (!listBox)
		return;
	if (!listBox->winIsHidden())
	{
		listBox->winHide(true);
		GameWindow *editBox = GadgetComboBoxGetListBox(window);
		editBox->winGetSize(&winSize.x, &winSize.y);
		window->winGetSize(&newSize.x, &newSize.y);
		window->winSetSize(newSize.x, winSize.y);
		if (TheWindowManager->slot53() == window)
			TheWindowManager->winSetLoneWindow(NULL);
	}
}
