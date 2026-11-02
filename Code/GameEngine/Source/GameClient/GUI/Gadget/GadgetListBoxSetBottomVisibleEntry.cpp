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

struct ListboxData
{
	short listLength;
	short columns;
	unsigned char m_unmodelled04[9];
	Bool scrollIfAtEnd;
	unsigned char m_unmodelled0E[0x0A];
	ListEntryRow *listData;
	unsigned char m_unmodelled1C[0x10];
	short endPos;
	unsigned char m_unmodelled2E[0x0E];
	Short displayHeight;
	unsigned char m_unmodelled3E[0x06];
	Short displayPos;
};

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
