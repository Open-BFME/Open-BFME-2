// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?GadgetListBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// List box hit testing, the Zero Hour GadgetListBox.cpp statics BFME2 keeps:
// getListboxEntryBasedOnCoord @0x00323E95 218B (cdecl; the only body the
// GadgetListBoxGetEntryBasedOnXY wrapper @0x00323F6F tail-jumps to) maps a
// screen point to the row under it and the column whose running width
// passes it. Target facts: the title adjustment through
// WinInstanceData::getTextLength and manager slot 72 (winFontHeight) of the
// font at instance +0x184; columns short +2, column widths +0x14, 16-byte
// rows at +0x18 (listHeight +0), endPos short +0x2C, displayHeight short
// +0x3C, displayPos short +0x44.
//
// GadgetListBoxMultiInput @0x00324E92 775B: the multi-select input callback.
// Reference semantics: Zero Hour GadgetListBox.cpp and the Open-BFME-1
// donor (case order, mouse-position case 24 before LEFT_DRAG). Target facts:
// LEFT_UP skips everything while the byte at +0x0F is set and resets the Int
// at +0x48 to -1; a row whose byte at +0x0C is set selects -1; case 24 hit
// tests into the Int at +0x30 when the byte at +0x12 is set and forwards the
// message to the owner; wheel scrolling goes through the display adjustment
// 0x00324AE5; GameWindowManager slots 49 (winSetFocus), 58 (winSendSystemMsg)
// and 72 (winFontHeight); instance style +0x0C, state +0x08.
//
// Also here: the bottom-entry worker 0x00323F9C, the scroll-to-row helper
// 0x00324B8F and GadgetListBoxSetTopVisibleEntry 0x0032544C. /G7 is what
// spells the helper's doubling `add eax, eax`; the other bodies are
// unchanged by it.
//
// NOTE (2026-10-10): the shared rows live in GadgetListBoxMultiInput.cpp
// (GetEntryBasedOnXY 0x00323F6F, MultiInput 0x00324E92, SetTopVisibleEntry
// 0x0032544C, Rva00323F9C 0x00323F9C); their duplicate definitions here were
// deleted after an LNK2005 proof. This TU keeps GadgetListBoxSystem plus its
// TU-local statics (getListboxEntryBasedOnCoord, removeSelection,
// Rva00324B8FScrollTo, moveRowsDown, addEntry).
// All nine existing bodies stay exact under /arch:SSE /EHsc. NEAR: the
// GadgetListBoxSystem body matches all but two instructions in
// GLM_UPDATE_DISPLAY at 0x00326B0C (retail sign-extends displayPos into EDX
// and the cached displayHeight into ECX; cl swaps the two registers).
#include <string.h>
#include "unicode_string.h"

typedef int Int;
typedef short Short;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

enum
{
	GWM_CREATE = 1,
	GWM_DESTROY = 2,
	GWM_LEFT_DOWN = 5,
	GWM_LEFT_UP = 6,
	GWM_LEFT_DRAG = 8,
	GWM_RIGHT_UP = 14,
	GWM_MOUSE_ENTERING = 17,
	GWM_MOUSE_LEAVING = 18,
	GWM_WHEEL_UP = 19,
	GWM_WHEEL_DOWN = 20,
	GWM_CHAR = 21,
	GWM_INPUT_FOCUS = 23,
	GWM_MOUSE_POS = 24,
	GWM_SHOW_SCROLL = 28
};

enum
{
	GGM_LEFT_DRAG = 0x4000,
	GGM_SET_LABEL = 0x4001,
	GGM_FOCUS_CHANGE = 0x4003,
	GGM_RESIZED = 0x4004,
	GBM_MOUSE_ENTERING = 0x4006,
	GBM_MOUSE_LEAVING = 0x4007,
	GBM_SELECTED = 0x4008,
	GSM_SLIDER_TRACK = 0x400C,
	GLM_ADD_ENTRY = 0x4011,
	GLM_DEL_ENTRY = 0x4012,
	GLM_DEL_ALL = 0x4013,
	GLM_SELECTED = 0x4014,
	GLM_RIGHT_CLICKED = 0x4016,
	GLM_SET_SELECTION = 0x4017,
	GLM_GET_SELECTION = 0x4018,
	GLM_TOGGLE_MULTI_SELECTION = 0x4019,
	GLM_GET_TEXT = 0x401A,
	GLM_SET_UP_BUTTON = 0x401B,
	GLM_SET_DOWN_BUTTON = 0x401C,
	GLM_SET_SLIDER = 0x401D,
	GLM_SCROLL_BUFFER = 0x401E,
	GLM_UPDATE_DISPLAY = 0x401F,
	GLM_GET_ITEM_DATA = 0x4020,
	GLM_SET_ITEM_DATA = 0x4021
};

enum { WIN_STATE_HILITED = 0x02 };
enum { GWS_MOUSE_TRACK = 0x400, GWS_COMBO_BOX = 0x8000 };
enum { WIN_STATUS_ONE_LINE = 0x4000 };
enum { LISTBOX_TEXT = 1, LISTBOX_IMAGE = 2 };
enum { TEXT_WIDTH_OFFSET = 7 };
enum { GP_DONT_UPDATE = 1 };
enum { KEY_TAB = 0x0F };
enum { KEY_STATE_DOWN = 0x02 };

#define BitTest(x, i) (((x) & (i)) != 0)
#define BitSet(x, i) ((x) |= (i))
#define BitClear(x, i) ((x) &= ~(i))

#ifndef NULL
#define NULL 0
#endif
#define TRUE true
#define FALSE false

void *operator new[](unsigned int size);
void operator delete[](void *block);
void operator delete(void *block);

class GameFont
{
public:
	unsigned char m_pad00[0x10];
	Int height;
};

class Image;

struct ICoord2D
{
	Int x;
	Int y;
};

class WinInstanceData
{
public:
	void setText(UnicodeString text);
	Int getTextLength();
	GameFont *getFont() { return m_font; }
	UnsignedInt getStyle() { return m_style; }

	void *m_vtable;
	Int m_id;
	UnsignedInt m_state;
	UnsignedInt m_style;
	unsigned char m_pad10[0x184 - 0x10];
	GameFont *m_font;
};

class FXParticleSystem
{
public:
	template <int N> class CategoryModuleClass
	{
	public:
		const char *getName() const;
	};
};

class Rva00313D6CDwordField
{
public:
	Int get() const;
};

class Rva003140C8DwordField
{
public:
	Int get() const;
};

class GameWindow
{
public:
	WinInstanceData *winGetInstanceData();
	void *winGetUserData();
	Int winGetScreenPosition(Int *x, Int *y);
	GameWindow *winGetOwner();
	GameWindow *winGetParent();
	UnsignedInt winGetStyle();
	Int winGetWindowId();
	Int winNextTab();
	Int winGetSize(Int *width, Int *height);
	Int winSetSize(Int width, Int height);
	Int winSetPosition(Int x, Int y);
	GameWindow *winGetChild() { return (GameWindow *)((Rva003140C8DwordField *)this)->get(); }
	UnsignedInt winGetStatus();	// declaration only: the rowed home copy
					// (GameWindowStatusUserData.cpp) is strong; the inline
					// body emits a select-any COMDAT that LNK2005s against
					// it (mini-link proven). The call site binds the same
					// folded address 0x30F45F.
	GameFont *winGetFont() { return (GameFont *)((Rva00313D6CDwordField *)this)->get(); }
	// NOTE: declaration-only winGetChild breaks this TU's 3111B row (register
	// allocation ripple); left inline. Its D is out of this row's scope.
};

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void setFont(GameFont *font);
	virtual void slot07();
	virtual void setWordWrap(Int width);
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void getSize(Int *width, Int *height);
};

class DisplayStringManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual DisplayString *newDisplayString();
	virtual void freeDisplayString(DisplayString *string);
};
extern DisplayStringManager *TheDisplayStringManager;

struct ListEntryCell
{
	Int cellType;
	Int unknown04;
	Int color;
	void *data;
	void *userData;
	Int width;
	Int height;
};

struct ListEntryRow
{
	Int listHeight;
	Int height;
	ListEntryCell *cell;
	Bool m_disabled;
};

typedef struct _ListboxData
{
	Short listLength;
	Short columns;
	Int *columnWidthPercentage;
	Bool autoScroll;
	Bool autoPurge;
	unsigned char m_pad0A[0x0B - 0x0A];
	Bool multiSelect;
	unsigned char m_pad0C[0x0F - 0x0C];
	Bool m_noSelect;
	Bool m_freeScroll;
	Bool m_fixedTotalHeight;
	Bool m_trackMouseOver;
	unsigned char m_pad13[0x14 - 0x13];
	Int *columnWidth;
	ListEntryRow *listData;
	GameWindow *upButton;
	GameWindow *downButton;
	GameWindow *slider;
	Int totalHeight;
	Short endPos;
	Short insertPos;
	Int mouseOverRow;
	Int selectPos;
	Int *selections;
	Short displayHeight;
	unsigned char m_pad3E[0x44 - 0x3E];
	Short displayPos;
	unsigned char m_pad46[0x48 - 0x46];
	Int m_field48;
} ListboxData;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48)
	virtual Int winSetFocus(GameWindow *window) = 0;
	V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window,
		UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
	V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
#undef V
	virtual Int winFontHeight(GameFont *font) = 0;
};

extern GameWindowManager *TheWindowManager;

static Int getListboxEntryBasedOnCoord(GameWindow *window, Int x, Int y, Int &row, Int &column)
{
	Int pos;
	Int winx, winy, i;
	WinInstanceData *instData = window->winGetInstanceData();
	ListboxData *list = (ListboxData *)window->winGetUserData();

	window->winGetScreenPosition(&winx, &winy);

	// Adjust for title if present
	if (instData->getTextLength())
		winy += TheWindowManager->winFontHeight(instData->getFont()) + 1;

	pos = -2;

	for (i = 0; ; i++)
	{
		if (i > 0)
			if (list->listData[i - 1].listHeight >
					(list->displayPos + list->displayHeight))
			{
				pos = -1;
				break;
			}

		if (i == list->endPos)
		{
			pos = -1;
			break;
		}

		if (list->listData[i].listHeight > (y - winy + list->displayPos))
			break;
	}

	column = -1;
	if (pos == -2)
	{
		pos = i;
		Int total = 0;
		for (i = 0; i < list->columns; i++)
		{
			total += list->columnWidth[i];
			if (x - winx < total)
			{
				column = i;
				break;
			}
		}
	}
	row = pos;
	return pos;
}


// removeSelection @0x00323FD9 40B: drops one entry from the -1 terminated
// selection list (Int* at +0x38, listLength short at +0). Its only callers
// share this unit, so the compiler gives it the private ESI/ECX convention.
// Retail calls it from four sites (0x003250D3 here, three in
// GadgetListBoxSystem), so it is never inlined; with only this caller
// recovered so far, it is kept out of line as the BFME 1 donor does.
__declspec(noinline) static void removeSelection(ListboxData *list, Int i)
{
	memcpy(&list->selections[i], &list->selections[(i + 1)],
		((list->listLength - i) * sizeof(Int)));
	list->selections[(list->listLength - 1)] = -1;
}

void Rva003249D2(GameWindow *window, Bool updateSlider);

// 0x00324B8F 210B: scrolls so row `index` is at the top (mode 1) or centred
// (otherwise), then refreshes the slider 0x003249D2. Its callers share this
// unit, so the compiler passes the index in EAX. The Open-BFME-1 donor
// carries the same helper (Rva004B7DC0); BFME2 adds the byte at +0x11 that
// stops it growing totalHeight (+0x28).
__declspec(noinline) static void Rva00324B8FScrollTo(GameWindow *window, Int index, Int mode)
{
	if (index < 0)
		return;
	ListboxData *list = (ListboxData *)window->winGetUserData();
	if (index >= list->endPos)
		return;
	ListEntryRow *rows = list->listData;
	ListEntryRow *row = &rows[index];
	Int y;
	switch (mode)
	{
		case 1:
			y = row->listHeight - row->height;
			break;
		default:
			y = (2 * row->listHeight - list->displayHeight - row->height) / 2;
			break;
	}
	list->displayPos = 0;
	Int entry = 0;
	while (list->listData[entry].listHeight - list->listData[entry].height < y)
		++entry;
	while (entry > 0 && list->totalHeight <
			rows[entry - 1].listHeight - rows[entry - 1].height + list->displayHeight)
		--entry;
	list->displayPos = rows[entry].listHeight - rows[entry].height;
	if (!list->m_fixedTotalHeight &&
			rows[list->endPos - 1].listHeight < list->displayPos + list->displayHeight)
		list->totalHeight = list->displayPos + list->displayHeight;
	Rva003249D2(window, TRUE);
}

void Rva00324AE5Update(GameWindow *window, Int adjustment, Bool updateSlider);
void computeTotalHeight(GameWindow *window);
void Rva00324B39Add(GameWindow *window, Short adjustment, Bool updateSlider);
void Rva003248F5Show(GameWindow *window, Bool show);
Int addImageEntry(const Image *image, Int color, Int row, Int column, GameWindow *window, Int width, Int height);

static Int moveRowsDown(ListboxData *list, Int startingRow)
{
	Int copyLen = (list->endPos - startingRow) * sizeof(ListEntryRow);
	char *buf = new char[copyLen];
	memcpy(buf, &list->listData[startingRow], copyLen);
	memcpy(&list->listData[startingRow + 1], buf, copyLen);
	delete [] buf;
	list->endPos++;
	list->insertPos = list->endPos;
	list->listData[startingRow].cell = 0;
	list->listData[startingRow].height = 0;
	list->listData[startingRow].listHeight = 0;
	if (list->multiSelect)
	{
		Int i = 0;
		while (list->selections[i] >= 0)
		{
			if (startingRow <= list->selections[i])
				list->selections[i]++;
			i++;
		}
	}
	else
	{
		if (list->selectPos >= startingRow)
			list->selectPos++;
	}
	return 1;
}

static Int addEntry(UnicodeString *string, Int color, Int row, Int column, GameWindow *window, Bool overwrite)
{
	ListboxData *list = (ListboxData *)window->winGetUserData();
	Int width;
	DisplayString *displayString;

	if (column >= list->columns || row >= list->listLength)
		return -1;

	if (row == -1)
	{
		row = list->insertPos;
		list->insertPos++;
		list->endPos++;
	}
	if (column == -1)
		column = 0;

	width = list->columnWidth[column] - TEXT_WIDTH_OFFSET;

	Int rowsAdded = 0;
	ListEntryRow *listRow = &list->listData[row];
	if (!listRow->cell)
	{
		listRow->cell = new ListEntryCell[list->columns];
		memset(listRow->cell, 0, list->columns * sizeof(ListEntryCell));
		rowsAdded = 1;
	}
	else if (!overwrite)
	{
		moveRowsDown(list, row);
		listRow->cell = new ListEntryCell[list->columns];
		memset(listRow->cell, 0, list->columns * sizeof(ListEntryCell));
		rowsAdded = 1;
	}

	listRow->cell[column].cellType = LISTBOX_TEXT;
	listRow->cell[column].unknown04 = 0;
	listRow->cell[column].color = color;

	if (!listRow->cell[column].data)
		listRow->cell[column].data = TheDisplayStringManager->newDisplayString();
	displayString = (DisplayString *)listRow->cell[column].data;
	if ((window->winGetStatus() & WIN_STATUS_ONE_LINE) == 0)
		displayString->setWordWrap(width);
	displayString->setText(*string);
	displayString->setFont(window->winGetFont());

	if (overwrite)
	{
		Int oldRowHeight = listRow->height;
		Int oldTotalHeight = listRow->listHeight;
		Int rowHeight;
		Int totalHeight;

		if (!oldTotalHeight && row)
			oldTotalHeight = list->listData[row - 1].listHeight;

		displayString->getSize(0, &rowHeight);
		if (rowHeight > oldRowHeight)
		{
			totalHeight = oldTotalHeight + (rowHeight - oldRowHeight);
			listRow->height = rowHeight;
			listRow->listHeight = totalHeight + rowsAdded;
			list->totalHeight += (rowHeight - oldRowHeight) + rowsAdded;
			Rva00324AE5Update(window, 0, true);
		}
	}
	else
	{
		computeTotalHeight(window);
	}

	return row;
}

struct RightClickStruct
{
	Int mouseX;
	Int mouseY;
	Int pos;
};

// doAudioFeedback 0x00323E1C, rowed as a method on the window pointer.
class Rva00323E1C { public: void rva00323E1C(); };

struct AddMessageStruct
{
	Int row;
	Int column;
	void *data;
	Int type;
	Bool overwrite;
	Int width;
	Int height;
};

struct TextAndColor
{
	UnicodeString string;
	Int color;
};

struct SliderData
{
	Int minVal;
	Int maxVal;
};

// GadgetListBoxSystem @0x00325FBF 3071B (jump table for 0x4018..0x4021
// follows at 0x00326BBE): the list box system-message callback. Reference
// semantics: Zero Hour GadgetListBox.cpp GadgetListBoxSystem; the BFME2
// shape follows the WorldBuilder twin 0x0114CEE0 case by case: GBM_SELECTED
// scrolls by the font height through 0x00324B39 while the byte at +0x10 is
// set; DEL_ENTRY clears the freed row pointer; ADD_ENTRY refreshes the
// slider 0x003249D2 after a single-select add; SET_SELECTION resets the Int
// at +0x48 and scrolls through 0x00324B8F instead of the display update;
// SCROLL_BUFFER also clears each cell's type words and frees rows with
// delete[]; RESIZED rewraps every text cell to its column width unless the
// window is one-line and re-scrolls to the selection; message 0x1C shows or
// hides the scroll controls through 0x003248F5 while the byte at +0x11 is
// set; SLIDER_TRACK goes through 0x00324B39. The statics addEntry,
// removeSelection and Rva00324B8FScrollTo take their private register
// arguments from this unit.
WindowMsgHandledType GadgetListBoxSystem(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	ListboxData *list = (ListboxData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();
	ICoord2D *pos;

	switch (msg)
	{
		// ------------------------------------------------------------------------
		case GGM_SET_LABEL:
		{
			instData->setText(*(UnicodeString *)mData1);
			break;
		}

		// ------------------------------------------------------------------------
		case GLM_GET_TEXT:
		{
			pos = (ICoord2D *)mData1;
			TextAndColor *tAndC = (TextAndColor *)mData2;

			if (pos->x >= list->columns || pos->y >= list->listLength ||
					list->listData[pos->y].cell[pos->x].cellType != LISTBOX_TEXT)
			{
				tAndC->string = UnicodeString::TheEmptyString;
				tAndC->color = 0;
			}
			else
			{
				tAndC->string = ((DisplayString *)list->listData[pos->y].cell[pos->x].data)->getText();
				tAndC->color = list->listData[pos->y].cell[pos->x].color;
			}
			break;
		}

		// ------------------------------------------------------------------------
		case GBM_SELECTED:
		{
			if (list->m_freeScroll)
			{
				Int scroll = 20;
				if (window->winGetFont())
					scroll = window->winGetFont()->height;

				if ((GameWindow *)mData1 == list->upButton)
					Rva00324B39Add(window, -scroll, TRUE);
				else if ((GameWindow *)mData1 == list->downButton)
					Rva00324B39Add(window, scroll, TRUE);
			}
			else
			{
				if ((GameWindow *)mData1 == list->upButton)
				{
					if (list->displayPos > 0)
						Rva00324AE5Update(window, -1, TRUE);
				}
				else if ((GameWindow *)mData1 == list->downButton)
				{
					if (list->displayPos + list->displayHeight < list->totalHeight)
						Rva00324AE5Update(window, 1, TRUE);
				}
			}
			break;
		}

		// ------------------------------------------------------------------------
		case GLM_DEL_ALL:
		{
			for (Int i = 0; i < list->listLength; i++)
			{
				ListEntryCell *cells = list->listData[i].cell;
				for (Int j = list->columns - 1; j >= 0; j--)
				{
					if (!cells)
						break;
					if (cells[j].cellType == LISTBOX_TEXT)
					{
						if (cells[j].data)
							TheDisplayStringManager->freeDisplayString((DisplayString *)cells[j].data);
					}
					cells[j].userData = NULL;
					cells[j].data = NULL;
				}
				delete [] (list->listData[i].cell);
				list->listData[i].cell = NULL;
			}
			memset(list->listData, 0, list->listLength * sizeof(ListEntryRow));

			if (mData1 != GP_DONT_UPDATE)
				list->displayPos = 0;

			if (list->multiSelect)
				memset(list->selections, -1, list->listLength * sizeof(Int));
			else
				list->selectPos = -1;

			list->insertPos = 0;
			list->endPos = 0;
			list->totalHeight = 0;

			Rva00324AE5Update(window, 0, TRUE);
			break;
		}

		// ------------------------------------------------------------------------
		case GLM_DEL_ENTRY:
		{
			Int i;

			if (list->endPos <= (Int)mData1)
				break;

			ListEntryCell *cells = list->listData[mData1].cell;
			if (cells)
				for (i = 0; i <= list->columns; i++)
				{
					if (cells[i].cellType == LISTBOX_TEXT && cells[i].data)
						TheDisplayStringManager->freeDisplayString((DisplayString *)cells[i].data);
					cells[i].data = NULL;
					cells[i].userData = NULL;
				}

			delete [] (list->listData[mData1].cell);
			list->listData[mData1].cell = NULL;

			memcpy(&list->listData[mData1], &list->listData[(mData1 + 1)],
				(list->endPos - mData1 - 1) * sizeof(ListEntryRow));

			list->endPos--;
			list->insertPos = list->endPos;

			if (list->multiSelect)
			{
				i = 0;
				while (list->selections[i] >= 0)
				{
					if ((Int)mData1 < list->selections[i])
						list->selections[i]--;
					else if ((Int)mData1 == list->selections[i])
					{
						removeSelection(list, i);
						i--;
					}
					i++;
				}
			}
			else
			{
				if ((Int)mData1 < list->selectPos)
					list->selectPos--;
				else if ((Int)mData1 == list->selectPos)
					list->selectPos = -1;
			}

			computeTotalHeight(window);
			break;
		}

		// ------------------------------------------------------------------------
		case GLM_ADD_ENTRY:
		{
			Bool success = TRUE;
			Int addedIndex = -1;
			AddMessageStruct *addInfo = (AddMessageStruct *)mData1;
			if (addInfo->row >= list->insertPos)
				addInfo->row = -1;

			Int row = addInfo->row;
			if (addInfo->row == -1 && list->insertPos == list->listLength)
			{
				row = list->insertPos;
				if (list->insertPos == list->listLength)
				{
					if (list->autoPurge)
						TheWindowManager->winSendSystemMsg(window, GLM_SCROLL_BUFFER, 1, 0);
					else
						success = FALSE;
				}
			}
			else if (addInfo->row != -1 && !addInfo->overwrite && list->insertPos == list->listLength)
			{
				if (list->autoPurge)
					TheWindowManager->winSendSystemMsg(window, GLM_SCROLL_BUFFER, 1, 0);
				else
					success = FALSE;
			}

			if (success)
			{
				if (addInfo->type == LISTBOX_TEXT)
				{
					addedIndex = addEntry((UnicodeString *)addInfo->data, mData2, addInfo->row, addInfo->column, window, addInfo->overwrite);
				}
				else if (addInfo->type == LISTBOX_IMAGE)
				{
					addedIndex = addImageEntry((const Image *)addInfo->data, mData2, addInfo->row, addInfo->column, window, addInfo->width, addInfo->height);
				}
				else
					success = FALSE;
			}

			if (success)
			{
				if (list->autoScroll)
				{
					while (TRUE)
					{
						if (row == -1)
						{
							if (list->listData[(list->insertPos - 1)].listHeight >=
									(list->displayPos + list->displayHeight))
								Rva00324AE5Update(window, 1, TRUE);
							else
								break;
						}
						else
						{
							if (list->listData[(row)].listHeight >=
									(list->displayPos + list->displayHeight))
								Rva00324AE5Update(window, 1, TRUE);
							else
								break;
						}
					}
				}

				if (list->multiSelect)
				{
					Int i = 0;
					while (list->selections[i] >= 0)
					{
						if ((row = list->selections[i]) != 0)
							list->selections[i] = -1;
						i++;
					}
				}
				else
				{
					if (row == list->selectPos)
						list->selectPos = -1;
					Rva003249D2(window, TRUE);
				}
			}
			return (WindowMsgHandledType)addedIndex;
		}

		// ------------------------------------------------------------------------
		case GLM_TOGGLE_MULTI_SELECTION:
		{
			if ((Int)mData1 < 0)
			{
				if (list->multiSelect)
					memset(list->selections, -1, list->listLength * sizeof(Int));
				break;
			}

			if (!list->listData[mData1].cell)
				break;

			if (list->multiSelect)
			{
				Int i = 0;
				Bool removed = FALSE;

				while (list->selections[i] >= 0)
				{
					if (list->selections[i] == (Int)mData1)
					{
						removeSelection(list, i);
						removed = TRUE;
						break;
					}
					i++;
				}

				if (removed == FALSE)
				{
					list->selections[i] = (Int)mData1;
					list->selections[i + 1] = -1;
				}
			}
			break;
		}

		// ------------------------------------------------------------------------
		case GLM_SET_SELECTION:
		{
			list->m_field48 = -1;
			const Int *selectList = (const Int *)mData1;
			Int selectCount = (Int)mData2;

			if (selectList[0] < 0 || list->listLength <= selectList[0])
			{
				if (list->multiSelect)
					memset(list->selections, -1, list->listLength * sizeof(Int));
				else
					list->selectPos = -1;

				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GLM_SELECTED, (WindowMsgData)window, list->selectPos);
				break;
			}

			if (list->multiSelect)
			{
				Int i;
				for (i = 0; i < selectCount && i < list->endPos; ++i)
				{
					if (list->listLength <= selectList[i])
						break;
					if (!list->listData[selectList[i]].cell)
						break;
					list->selections[i] = selectList[i];
				}
				list->selections[i] = -1;
			}
			else
			{
				if (!list->listData[selectList[0]].cell)
					break;

				list->selectPos = selectList[0];

				GameWindow *parent = window->winGetParent();
				if (parent && BitTest(parent->winGetStyle(), GWS_COMBO_BOX))
				{
					TheWindowManager->winSendSystemMsg(window->winGetOwner(),
						GLM_SELECTED, (WindowMsgData)window, list->selectPos);
					break;
				}

				Rva00324B8FScrollTo(window, list->selectPos, 0);
			}
			break;
		}

		// ------------------------------------------------------------------------
		case GLM_SCROLL_BUFFER:
		{
			if (list->endPos < (Int)mData1)
				break;

			ListEntryCell *cells = NULL;
			Int i;
			for (i = 0; i < (Int)mData1; i++)
			{
				cells = list->listData[i].cell;
				if (cells)
					for (Int j = 0; j < list->columns; j++)
					{
						if (cells[j].cellType == LISTBOX_TEXT && cells[j].data)
							TheDisplayStringManager->freeDisplayString((DisplayString *)cells[j].data);
						cells[j].data = NULL;
						cells[j].userData = NULL;
						cells[j].color = 0;
						cells[j].cellType = 0;
						cells[j].unknown04 = 0;
					}

				delete [] (list->listData[i].cell);
				list->listData[i].cell = NULL;
			}

			memcpy(list->listData, &list->listData[mData1],
				(list->endPos - mData1) * sizeof(ListEntryRow));

			list->endPos -= mData1;
			list->insertPos = list->endPos;

			for (i = 0; i < (Int)mData1; i++)
				list->listData[list->endPos + i].cell = NULL;

			if (list->multiSelect)
			{
				Int i = 0;
				while (list->selections[i] >= 0)
				{
					if ((Int)mData1 >= list->selections[i])
						list->selections[i] -= (Int)mData1;
					else
					{
						removeSelection(list, i);
						i--;
					}
					i++;
				}
			}
			else
			{
				if (list->selectPos > 0)
					list->selectPos -= mData1;
			}

			if (list->displayPos > 0)
				Rva00324AE5Update(window, (-1 * mData1), TRUE);

			computeTotalHeight(window);
			break;
		}

		// ------------------------------------------------------------------------
		case GLM_GET_SELECTION:
		{
			if (list->multiSelect)
				*(Int *)mData2 = (Int)list->selections;
			else
				*(Int *)mData2 = list->selectPos;
			break;
		}

		// ------------------------------------------------------------------------
		case GLM_SET_UP_BUTTON:
			list->upButton = (GameWindow *)mData1;
			break;

		case GLM_SET_DOWN_BUTTON:
			list->downButton = (GameWindow *)mData1;
			break;

		case GLM_SET_SLIDER:
			list->slider = (GameWindow *)mData1;
			break;

		// ------------------------------------------------------------------------
		case GWM_SHOW_SCROLL:
			if (list->m_fixedTotalHeight)
				Rva003248F5Show(window, list->totalHeight <= list->displayHeight);
			break;

		// ------------------------------------------------------------------------
		case GWM_CREATE:
			break;

		// ------------------------------------------------------------------------
		case GGM_RESIZED:
		{
			Int width = (Int)mData1;
			Int height = (Int)mData2;
			ICoord2D downSize = {0, 0};
			ICoord2D upSize = {0, 0};
			ICoord2D sliderSize = {0, 0};
			GameWindow *child = NULL;
			ICoord2D sliderChildSize = {0, 0};

			if (list->downButton)
				list->downButton->winGetSize(&downSize.x, &downSize.y);
			if (list->upButton)
				list->upButton->winGetSize(&upSize.x, &upSize.y);
			if (list->slider)
			{
				list->slider->winGetSize(&sliderSize.x, &sliderSize.y);
				child = list->slider->winGetChild();
				if (child)
					child->winGetSize(&sliderChildSize.x, &sliderChildSize.y);
			}

			if (list->upButton)
				list->upButton->winSetPosition(width - upSize.x - 2, 2);

			if (list->downButton)
				list->downButton->winSetPosition(width - downSize.x - 2,
					height - downSize.y - 2);

			if (list->slider)
			{
				list->slider->winSetSize(sliderSize.x, height - (2 * upSize.y) - 6);
				list->slider->winSetPosition(width - sliderSize.x - 2, upSize.y + 3);
			}

			list->displayHeight = height;
			if (instData->getTextLength())
				list->displayHeight -= TheWindowManager->winFontHeight(instData->getFont());

			if (list->columns == 1)
			{
				list->columnWidth[0] = width;
				if (list->slider)
				{
					ICoord2D sliderSize;
					list->slider->winGetSize(&sliderSize.x, &sliderSize.y);
					list->columnWidth[0] -= sliderSize.x;
				}
			}
			else if (list->columnWidthPercentage && list->columnWidth)
			{
				Int totalWidth = width;
				if (list->slider)
				{
					ICoord2D sliderSize;
					list->slider->winGetSize(&sliderSize.x, &sliderSize.y);
					totalWidth -= sliderSize.x;
				}
				for (Int i = 0; i < list->columns; i++)
					list->columnWidth[i] = list->columnWidthPercentage[i] * totalWidth / 100;
			}

			if (!BitTest(window->winGetStatus(), WIN_STATUS_ONE_LINE))
			{
				for (Int i = 0; i < list->endPos; i++)
				{
					ListEntryRow *row = &list->listData[i];
					for (Int j = 0; j < list->columns; j++)
					{
						if (row->cell[j].cellType == LISTBOX_TEXT)
						{
							DisplayString *displayString = (DisplayString *)row->cell[j].data;
							if (displayString)
								displayString->setWordWrap(list->columnWidth[j] - TEXT_WIDTH_OFFSET);
						}
					}
				}
			}

			computeTotalHeight(window);

			if (list->multiSelect)
				Rva00324AE5Update(window, 0, TRUE);
			else if (list->selectPos >= 0)
				Rva00324B8FScrollTo(window, list->selectPos, 0);
			else
				Rva003249D2(window, TRUE);
			break;
		}

		// ------------------------------------------------------------------------
		case GLM_UPDATE_DISPLAY:
		{
			if (mData1 > 0)
				list->displayPos = list->listData[(mData1 - 1)].listHeight + 1;
			else
				list->displayPos = 0;

			if (list->displayPos + (list ? list->displayHeight : list->displayHeight) >= list->totalHeight)
				list->displayPos = list->totalHeight - list->displayHeight;

			Rva00324AE5Update(window, 0, TRUE);
			break;
		}

		// ------------------------------------------------------------------------
		case GWM_DESTROY:
		{
			Int i;
			for (i = 0; i < list->listLength; i++)
			{
				ListEntryCell *cells = list->listData[i].cell;
				for (Int j = list->columns - 1; j >= 0; j--)
				{
					if (!cells)
						break;
					if (cells[j].cellType == LISTBOX_TEXT)
					{
						if (cells[j].data)
							TheDisplayStringManager->freeDisplayString((DisplayString *)cells[j].data);
					}
					cells[j].userData = NULL;
					cells[j].data = NULL;
				}
				delete [] (list->listData[i].cell);
				(list?list:list)->listData[i].cell = NULL;
			}

			delete [] (list->listData);
			if (list->columnWidth)
				delete [] (list->columnWidth);
			if (list->columnWidthPercentage)
				delete [] (list->columnWidthPercentage);
			if (list->multiSelect)
				delete [] (list->selections);

			delete (list);
			break;
		}

		// ------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:
		{
			if (mData1 == FALSE)
				BitClear(instData->m_state, WIN_STATE_HILITED);
			else
				BitSet(instData->m_state, WIN_STATE_HILITED);

			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GGM_FOCUS_CHANGE, mData1, window->winGetWindowId());

			*(Bool *)mData2 = TRUE;
			break;
		}

		// ------------------------------------------------------------------------
		case GSM_SLIDER_TRACK:
		{
			SliderData *sData = (SliderData *)list->slider->winGetUserData();
			list->displayPos = sData->maxVal - mData2;
			Rva00324B39Add(window, 0, FALSE);
			break;
		}

		// ------------------------------------------------------------------------
		case GLM_SET_ITEM_DATA:
		{
			void *data = (void *)mData2;
			pos = (ICoord2D *)mData1;
			if (pos->y >= 0 && pos->y < list->endPos && list->listData[pos->y].cell &&
					pos->x >= 0 && pos->x < list->columns)
				list->listData[pos->y].cell[pos->x].userData = data;
			break;
		}

		// ------------------------------------------------------------------------
		case GLM_GET_ITEM_DATA:
		{
			pos = (ICoord2D *)mData1;
			void **data = (void **)mData2;
			*data = NULL;
			if (pos->y >= 0 && pos->y < list->endPos && list->listData[pos->y].cell &&
					pos->x >= 0 && pos->x < list->columns)
				*data = list->listData[pos->y].cell[pos->x].userData;
			break;
		}

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
