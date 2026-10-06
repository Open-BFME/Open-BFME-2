// cl: /ICode/GameEngine/Source/GameClient/GUI /O1 /G7 /MD /EHsc /DNDEBUG
// GameWindowManager::gogoGadgetListBox, retail 0x002C1395 (240 B, Ghidra
// boundary): slot 24 of the base window manager vtable 0x00BFF658, called
// directly by the W3D override in slot 24 of 0x00BC7C90 (0x0008FDC6, call at
// 0x0008FE0B) after it picks the list draw factory. Reference semantics: Zero
// Hour GameWindowManager::gogoGadgetListBox (BFME1 2791daf553 inputs) on
// BFME's one-record factory ABI. Target facts: style test 0x20 on the
// record's instance (+0x30), the 0x4C-byte list data copied before the
// window is created through slot 34, user data, owner (0x003140CF), the
// rowed WinInstanceData::getTextLength title test, the list length handed to
// the rowed GadgetListBoxSetListLength, a 16-bit display height less the
// title font height (slot 72, font at instance+0x184), the cleared scroll
// state, the scroll bar helper when data+0xA is set, the rowed
// GadgetListBoxUpdateColumnWidths in place of Zero Hour's inline column
// widths, then assignDefaultGadgetLook (slot 30). List data fields are
// labelled with Zero Hour's names where the offsets agree (listLength,
// scrollBar) and by their observed use otherwise.
#include <string.h>
#include "GameWindowManagerRecordView.h"

class GameWindow { public: void winSetUserData(void *); };
class Rva003140CF { public: int rva003140CF(int); };

class WinInstanceData
{
public:
	int getTextLength();
	GameFont *getFont() { return m_font; }

	unsigned char m_pad00[0xC];
	unsigned int m_style;
	unsigned char m_pad10[0x184 - 0x10];
	GameFont *m_font;
};

enum { GWS_SCROLL_LISTBOX = 0x20 };

typedef struct _ListboxData
{
	short listLength;
	short columns;
	int *columnWidthPercentage;
	bool autoScroll;
	bool autoPurge;
	bool scrollBar;
	bool multiSelect;
	unsigned char m_pad0C[0x28 - 0xC];
	int totalHeight;
	short endPos;
	short insertPos;
	unsigned char m_pad30[4];
	int selectPos;
	unsigned char m_pad38[4];
	short displayHeight;
	unsigned int doubleClickTime;
	short displayPos;
	unsigned char m_pad46[0x4C - 0x46];
} ListboxData;

void GadgetListBoxSetListLength(GameWindow *listbox, int newLength);
void GadgetListboxCreateScrollbar(GameWindow *listbox);
void GadgetListBoxUpdateColumnWidths(GameWindow *listbox);

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	virtual GameWindow *gogoGadgetListBox(GadgetCreateView *view,
		ListboxData *listboxDataTemplate, GameFont *defaultFont, bool defaultVisual);
	V(25) V(26) V(27) V(28) V(29)
	virtual void assignDefaultGadgetLook(GameWindow *window, GameFont *font, bool visual) = 0;
	V(31) V(32) V(33)
	virtual GameWindow *createFromView(GadgetCreateView *view) = 0;
	V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
	virtual int winFontHeight(GameFont *font) = 0;
#undef V
};

GameWindow *GameWindowManager::gogoGadgetListBox(GadgetCreateView *view,
	ListboxData *listboxDataTemplate, GameFont *defaultFont, bool defaultVisual)
{
	GameWindow *listbox;
	ListboxData *listboxData;
	bool title = false;

	if (!(view->instance->m_style & GWS_SCROLL_LISTBOX))
		return 0;

	listboxData = new ListboxData;
	memcpy(listboxData, listboxDataTemplate, sizeof(ListboxData));

	listbox = createFromView(view);
	if (listbox == 0)
		return 0;

	listbox->winSetUserData(listboxData);
	((Rva003140CF *)listbox)->rva003140CF((int)view->parent);

	if (view->instance->getTextLength())
		title = true;

	int length = listboxData->listLength;
	listboxData->listLength = 0;
	GadgetListBoxSetListLength(listbox, length);

	listboxData->displayHeight = view->height;
	if (title)
		listboxData->displayHeight -= winFontHeight(view->instance->getFont());

	listboxData->displayPos = 0;
	listboxData->selectPos = -1;
	listboxData->doubleClickTime = 0;
	listboxData->insertPos = 0;
	listboxData->endPos = 0;
	listboxData->totalHeight = 0;

	if (listboxData->scrollBar)
		GadgetListboxCreateScrollbar(listbox);

	GadgetListBoxUpdateColumnWidths(listbox);

	assignDefaultGadgetLook(listbox, defaultFont, defaultVisual);

	return listbox;
}
