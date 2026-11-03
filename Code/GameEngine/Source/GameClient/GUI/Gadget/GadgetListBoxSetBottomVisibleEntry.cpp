// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// GadgetListBoxSetBottomVisibleEntry, retail 0x003253FD, 79 bytes: after the null and
// user-data guards it bounds-checks the requested row against the display height,
// sets the display position from that row height and refreshes the display through
// Rva003249D2 (the ZH source calls this adjustDisplay; that identity is not proven
// here, so the existing address-derived ledger name is used). The struct layouts below
// are the minimum the body needs.

typedef bool Bool;
typedef int Int;
typedef short Short;

#include "unicode_string.h"


#include "../../../../Include/GameClient/Bfme2GameWindow.h"

struct ListEntryRow
{
	Int listHeight;
	short rowTop;
	short m_unused06;
	void *cell;
	Int m_unmodelled0C;
};

#include "../../../../Include/GameClient/ListboxData.h"

#include "../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

void GadgetListBoxSetBottomVisibleEntry(GameWindow *window, int newPos);
void Rva003249D2(GameWindow *window, Bool updateSlider);

void GadgetListBoxSetBottomVisibleEntry(GameWindow *window, Int newPos)
{
	if (!window)
		return;

	if (!window->winGetUserData())
		return;

	ListboxData *listData = (ListboxData *)window->winGetUserData();

	if (newPos < 0)
		return;

	if (listData->listData[newPos].listHeight <= listData->displayHeight)
		return;

	if (listData->listData[newPos].listHeight <= listData->displayHeight)
		return;

	listData->displayPos = listData->listData[newPos].listHeight - listData->displayHeight + 1;

	Rva003249D2(window, true);
}
