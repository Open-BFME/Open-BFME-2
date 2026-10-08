// ?GadgetListBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// partial score=0.9 date=2026-10-08
// ?GadgetListBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// partial score=0.9 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /DNDEBUG /MD /EHsc
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
#include "unicode_string.h"

typedef int Int;
typedef short Short;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

enum
{
	GWM_LEFT_DOWN = 5,
	GWM_LEFT_UP = 6,
	GWM_LEFT_DRAG = 8,
	GWM_RIGHT_DOWN = 13,
	GWM_RIGHT_UP = 14,
	GWM_MOUSE_ENTERING = 17,
	GWM_MOUSE_LEAVING = 18,
	GWM_WHEEL_UP = 19,
	GWM_WHEEL_DOWN = 20,
	GWM_CHAR = 21,
	GWM_MOUSE_POS = 24
};

enum
{
	GGM_LEFT_DRAG = 0x4000,
	GBM_MOUSE_ENTERING = 0x4006,
	GBM_MOUSE_LEAVING = 0x4007,
	GLM_SELECTED = 0x4014,
	GLM_DOUBLE_CLICKED = 0x4015,
	GLM_RIGHT_CLICKED = 0x4016
};

enum { WIN_STATE_HILITED = 0x02 };
enum { GWS_MOUSE_TRACK = 0x400 };
enum
{
	KEY_TAB = 0x0F,
	KEY_ENTER = 0x1C,
	KEY_SPACE = 0x39,
	KEY_HOME = 0xC7,
	KEY_UP = 0xC8,
	KEY_PGUP = 0xC9,
	KEY_END = 0xCF,
	KEY_DOWN = 0xD0,
	KEY_PGDN = 0xD1
};
enum
{
	KEY_STATE_UP = 0x01,
	KEY_STATE_DOWN = 0x02,
	KEY_STATE_CONTROL = 0x0C,
	KEY_STATE_LSHIFT = 0x10
};
enum { LISTBOX_TEXT = 1 };

#define BitTest(x, i) (((x) & (i)) != 0)
#define BitSet(x, i) ((x) |= (i))
#define BitClear(x, i) ((x) &= ~(i))

#ifndef NULL
#define NULL 0
#endif
#define TRUE true
#define FALSE false

extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int count);

// Zero Hour inlines UnicodeString::getCharAt; WWLib keeps the out-of-line
// copy at 0x00035760, but this unit expands it in place.
template <> inline unsigned short StringBase<unsigned short>::getCharAt(int index) const
{
	return m_data ? m_data->data[index] : 0;
}

class GameFont
{
public:
	unsigned char m_pad00[0x10];
	Int height;
};

class WinInstanceData
{
public:
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

class GameWindow
{
public:
	WinInstanceData *winGetInstanceData();
	void *winGetUserData();
	Int winGetScreenPosition(Int *x, Int *y);
	GameWindow *winGetOwner();
	Int winNextTab();
	GameFont *winGetFont();
};

// 0x003140AB, rowed by address: true when the argument is this window or
// one of its descendants.
class Rva003140AB { public: bool rva003140AB(Rva003140AB *window); };

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText();
};

struct ListEntryCell
{
	Int cellType;
	unsigned char m_pad04[0x0C - 0x04];
	void *data;
	unsigned char m_pad10[0x1C - 0x10];
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
	unsigned char m_pad04[0x0C - 0x04];
	Bool forceSelect;
	unsigned char m_pad0D[0x0F - 0x0D];
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
	unsigned char m_pad2E[0x30 - 0x2E];
	Int mouseOverRow;
	Int selectPos;
	Int *selections;
	Short displayHeight;
	UnsignedInt doubleClickTime;
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
	V(40) V(41)
	virtual void winNextTab(GameWindow *window) = 0;
	virtual void winPrevTab(GameWindow *window) = 0;
	V(44) V(45) V(46) V(47)
	V(48)
	virtual Int winSetFocus(GameWindow *window) = 0;
	V(50) V(51) V(52)
	virtual GameWindow *winGetLoneWindow() = 0;
	V(54) V(55)
	V(56) V(57)
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window,
		UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
	V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
#undef V
	virtual Int winFontHeight(GameFont *font) = 0;
};

extern GameWindowManager *TheWindowManager;

class Keyboard
{
public:
	enum { MAX_KEY_STATES = 3 };
	UnsignedInt getModifierFlags() { return m_modifiers; }
	WideChar getPrintableKey(UnsignedByte key, Int state);

	unsigned char m_pad00[0x0C];
	UnsignedInt m_modifiers;
};

extern Keyboard *TheKeyboard;

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

Int GadgetListBoxGetEntryBasedOnXY(GameWindow *listbox, Int x, Int y, Int &row, Int &column)
{
	return getListboxEntryBasedOnCoord(listbox, x, y, row, column);
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

struct RightClickStruct
{
	Int mouseX;
	Int mouseY;
	Int pos;
};

// doAudioFeedback 0x00323E1C, rowed as a method on the window pointer.
class Rva00323E1C { public: void rva00323E1C(); };
void Rva00324AE5Update(GameWindow *window, Int adjustment, Bool updateSlider);

WindowMsgHandledType GadgetListBoxMultiInput(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	ListboxData *list = (ListboxData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();

	switch (msg)
	{
		case GWM_CHAR:
		{
			switch (mData1)
			{
				case KEY_TAB:
					if (BitTest(mData2, KEY_STATE_DOWN))
						window->winNextTab();
					break;

				default:
					return MSG_IGNORED;
			}
			break;
		}

		case GWM_LEFT_UP:
		{
			if (list->m_noSelect)
				break;
			TheWindowManager->winSetFocus(window);
			Int selectPos = -2;
			Int mousey = mData1 >> 16;
			Int x, y, i;
			Bool removed = FALSE;

			window->winGetScreenPosition(&x, &y);

			// Adjust for title if present
			if (instData->getTextLength())
				y += TheWindowManager->winFontHeight(instData->getFont()) + 1;

			for (i = 0; ; i++)
			{
				if (i > 0)
					if (list->listData[i - 1].listHeight >
							(list->displayPos + list->displayHeight))
					{
						selectPos = -1;
						break;
					}

				if (i == list->endPos)
				{
					selectPos = -1;
					break;
				}

				if (list->listData[i].listHeight > (mousey - y + list->displayPos))
					break;
			}

			if (selectPos == -2)
			{
				if (list->listData[i].m_disabled)
					selectPos = -1;
				else
					selectPos = i;
			}

			i = 0;
			while (list->selections[i] >= 0)
			{
				if (list->selections[i] == selectPos)
				{
					removeSelection(list, i);
					removed = TRUE;
					break;
				}

				i++;
			}

			if (removed == FALSE)
			{
				list->selections[i] = selectPos;
				list->selections[i + 1] = -1;
			}

			list->m_field48 = -1;
			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GLM_SELECTED, (WindowMsgData)window, selectPos);
			break;
		}

		case GWM_RIGHT_UP:
		{
			TheWindowManager->winSetFocus(window);
			Int pos;
			Int mousex = mData1 & 0xFFFF;
			Int mousey = mData1 >> 16;
			Int x, y, i;
			RightClickStruct rc;

			window->winGetScreenPosition(&x, &y);

			// Adjust for title if present
			if (instData->getTextLength())
				y += TheWindowManager->winFontHeight(instData->getFont()) + 1;

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

				if (list->listData[i].listHeight > (mousey - y + list->displayPos))
					break;
			}

			if (pos == -2)
				pos = i;

			rc.pos = pos;
			rc.mouseX = mousex;
			rc.mouseY = mousey;
			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GLM_RIGHT_CLICKED, (WindowMsgData)window, (WindowMsgData)&rc);
			break;
		}

		case GWM_WHEEL_DOWN:
			// Simulate the down button if it exists
			if (list->downButton)
			{
				if (list->displayPos + list->displayHeight <= list->totalHeight)
					Rva00324AE5Update(window, 1, TRUE);
			}
			break;

		case GWM_WHEEL_UP:
			// Simulate the up button if it exists
			if (list->upButton)
			{
				if (list->displayPos > 0)
					Rva00324AE5Update(window, -1, TRUE);
			}
			break;

		case GWM_MOUSE_ENTERING:
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
			{
				BitSet(instData->m_state, WIN_STATE_HILITED);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GBM_MOUSE_ENTERING, (WindowMsgData)window, 0);
			}
			break;

		case GWM_MOUSE_LEAVING:
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
			{
				BitClear(instData->m_state, WIN_STATE_HILITED);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GBM_MOUSE_LEAVING, (WindowMsgData)window, 0);
			}
			break;

		case GWM_MOUSE_POS:
			if (list->m_trackMouseOver)
			{
				Int column;
				getListboxEntryBasedOnCoord(window, mData1 & 0xFFFF, mData1 >> 16,
					list->mouseOverRow, column);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(), msg,
					(WindowMsgData)window, mData1);
			}
			break;

		case GWM_LEFT_DRAG:
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GGM_LEFT_DRAG, (WindowMsgData)window, 0);
			break;

		case GWM_LEFT_DOWN:
			((Rva00323E1C *)window)->rva00323E1C();
			// we want to eat the down... so we may receive the up.
			return MSG_HANDLED;

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}

// Zero Hour's getListboxTopEntry (0x00323F78, list in ECX), rowed as
// fastcall in GadgetListBox.cpp; adjustDisplayByDelta 0x00324B39 and the
// slider refresh 0x003249D2 are rowed in their own units.
Int __fastcall Rva0032378(_ListboxData *list);
void Rva00324B39Add(GameWindow *window, Short delta, Bool updateSlider);
void Rva003249D2(GameWindow *window, Bool updateSlider);

// GetDoubleClickTime() captured by the dynamic initializer 0x007AE9E6.
extern unsigned int g_00E01D48;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// getListboxBottomEntry @0x00323F9C 61B: the last row the display area
// reaches. Private convention, list in ECX.
__declspec(noinline) static Int getListboxBottomEntry(ListboxData *list)
{
	for (Int entry = list->endPos - 1; ; entry--)
	{
		if (entry < 0)
			return 0;
		if (list->listData[entry].listHeight == list->displayPos + list->displayHeight)
			return entry;
		if (list->listData[entry].listHeight < list->displayPos + list->displayHeight)
		{
			if (entry != list->endPos - 1)
				return entry + 1;
			return entry;
		}
	}
}

// 0x00324B8F: scrolls so row `index` is at the top (mode 1) or centred
// (otherwise), then refreshes the slider. Private convention, index in EAX.
// The Open-BFME-1 donor carries the same helper (Rva004B7DC0); BFME2 adds
// the byte at +0x11 that stops it growing totalHeight.
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

// GadgetListBoxInput @0x00325635 2442B: the single-select input callback.
WindowMsgHandledType GadgetListBoxInput(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	ListboxData *list = (ListboxData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();

	switch (msg)
	{
		case GWM_CHAR:
		{
			switch (mData1)
			{
				case KEY_ENTER:
				case KEY_SPACE:
					if (BitTest(mData2, KEY_STATE_UP))
						if (mData2 & KEY_STATE_CONTROL)
							return MSG_IGNORED;
						else
						{
							((Rva00323E1C *)window)->rva00323E1C();
							TheWindowManager->winSendSystemMsg(window->winGetOwner(),
								GLM_DOUBLE_CLICKED, (WindowMsgData)window, list->selectPos);
							return MSG_HANDLED;
						}
					break;

				case KEY_DOWN:
					if (BitTest(mData2, KEY_STATE_DOWN))
					{
						if (list->m_freeScroll)
						{
							Int delta = 20;
							if (window->winGetFont())
								delta = window->winGetFont()->height;
							Rva00324B39Add(window, delta, TRUE);
							break;
						}

						if (list->selectPos == -1)
						{
							list->selectPos = 0;
							Rva00324AE5Update(window, 0, TRUE);
						}
						else if (list->selectPos < list->endPos - 1)
						{
							list->selectPos++;

							while (1)
							{
								Int cellBottom = list->listData[list->selectPos].listHeight;
								Int cellTop = cellBottom - list->listData[list->selectPos].height;
								Int displayTop = list->displayPos;
								Int displayBottom = list->displayPos + list->displayHeight - 1;

								if (cellTop < displayTop)
								{
									Rva00324AE5Update(window, -1, TRUE);
								}
								else if (cellBottom < displayBottom)
								{
									Rva00324AE5Update(window, 0, TRUE);
									break;
								}
								else
								{
									Rva00324AE5Update(window, 1, TRUE);
								}
							}
						}

						list->m_field48 = -1;
						TheWindowManager->winSendSystemMsg(window->winGetOwner(),
							GLM_SELECTED, (WindowMsgData)window, list->selectPos);
						return MSG_HANDLED;
					}
					break;

				case KEY_PGDN:
					if (mData2 & KEY_STATE_DOWN)
					{
						if (list->m_freeScroll)
						{
							list->displayPos += list->displayHeight;
							Rva00324B39Add(window, 0, TRUE);
							break;
						}
						if (list->selectPos == -1)
						{
							list->selectPos = 0;
							Rva00324AE5Update(window, 0, TRUE);
						}
						else
						{
							list->selectPos += getListboxBottomEntry(list) - Rva0032378(list);
							if (list->selectPos >= list->endPos)
								list->selectPos = list->endPos - 1;
							while (1)
							{
								Int cellBottom = list->listData[list->selectPos].listHeight;
								Int cellTop = cellBottom - list->listData[list->selectPos].height;
								Int displayTop = list->displayPos;
								Int displayBottom = list->displayPos + list->displayHeight - 1;

								if (cellTop < displayTop)
								{
									Rva00324AE5Update(window, -1, TRUE);
								}
								else if (cellBottom < displayBottom)
								{
									Rva00324AE5Update(window, 0, TRUE);
									break;
								}
								else
								{
									Rva00324AE5Update(window, 1, TRUE);
								}
							}
						}
						list->m_field48 = -1;
						TheWindowManager->winSendSystemMsg(window->winGetOwner(),
							GLM_SELECTED, (WindowMsgData)window, list->selectPos);
						return MSG_HANDLED;
					}
					break;

				case KEY_END:
					if (mData2 & KEY_STATE_DOWN)
					{
						if (list->m_freeScroll)
						{
							list->displayPos = list->totalHeight - list->displayHeight;
							Rva00324B39Add(window, 0, TRUE);
							break;
						}
						list->selectPos = list->endPos - 1;
						while (1)
						{
							Int cellBottom = list->listData[list->selectPos].listHeight;
							Int cellTop = cellBottom - list->listData[list->selectPos].height;
							Int displayTop = list->displayPos;
							Int displayBottom = list->displayPos + list->displayHeight - 1;

							if (cellTop < displayTop)
							{
								Rva00324AE5Update(window, -1, TRUE);
							}
							else if (cellBottom < displayBottom)
							{
								Rva00324AE5Update(window, 0, TRUE);
								break;
							}
							else
							{
								Rva00324AE5Update(window, 1, TRUE);
							}
						}
						list->m_field48 = -1;
						TheWindowManager->winSendSystemMsg(window->winGetOwner(),
							GLM_SELECTED, (WindowMsgData)window, list->selectPos);
						return MSG_HANDLED;
					}
					break;

				case KEY_UP:
					if (BitTest(mData2, KEY_STATE_DOWN))
					{
						if (list->m_freeScroll)
						{
							Int delta = -20;
							if (window->winGetFont())
								delta = -window->winGetFont()->height;
							Rva00324B39Add(window, delta, TRUE);
							break;
						}
						if (list->selectPos == -1)
						{
							list->selectPos = 0;
							Rva00324AE5Update(window, 0, TRUE);
						}
						else if (list->selectPos > 0)
						{
							list->selectPos--;

							while (1)
							{
								if (list->listData[list->selectPos].listHeight -
										list->listData[list->selectPos].height < list->displayPos)
								{
									list->displayPos = list->listData[list->selectPos].listHeight + 1;
									Rva00324AE5Update(window, -1, TRUE);
								}
								else if (list->listData[list->selectPos].listHeight >
										list->displayPos + list->displayHeight)
								{
									list->displayPos =
										list->listData[list->selectPos].listHeight - list->displayHeight;
									Rva00324AE5Update(window, 1, TRUE);
								}
								else
								{
									Rva00324AE5Update(window, 0, TRUE);
									break;
								}
							}
						}

						list->m_field48 = -1;
						TheWindowManager->winSendSystemMsg(window->winGetOwner(),
							GLM_SELECTED, (WindowMsgData)window, list->selectPos);
						return MSG_HANDLED;
					}
					break;

				case KEY_HOME:
					if (mData2 & KEY_STATE_DOWN)
					{
						if (list->m_freeScroll)
						{
							list->displayPos = 0;
							Rva00324B39Add(window, 0, TRUE);
							break;
						}
						list->selectPos = 0;
						while (1)
						{
							if (list->listData[list->selectPos].listHeight -
									list->listData[list->selectPos].height < list->displayPos)
							{
								list->displayPos = list->listData[list->selectPos].listHeight + 1;
								Rva00324AE5Update(window, -1, TRUE);
							}
							else if (list->listData[list->selectPos].listHeight >
									list->displayPos + list->displayHeight)
							{
								list->displayPos =
									list->listData[list->selectPos].listHeight - list->displayHeight;
								Rva00324AE5Update(window, 1, TRUE);
							}
							else
							{
								Rva00324AE5Update(window, 0, TRUE);
								break;
							}
						}
						list->m_field48 = -1;
						TheWindowManager->winSendSystemMsg(window->winGetOwner(),
							GLM_SELECTED, (WindowMsgData)window, list->selectPos);
						return MSG_HANDLED;
					}
					break;

				case KEY_PGUP:
					if (mData2 & KEY_STATE_DOWN)
					{
						if (list->m_freeScroll)
						{
							list->displayPos -= list->displayHeight;
							Rva00324B39Add(window, 0, TRUE);
							break;
						}
						if (list->selectPos == -1)
						{
							list->selectPos = 0;
							Rva00324AE5Update(window, 0, TRUE);
						}
						else
						{
							list->selectPos += Rva0032378(list) - getListboxBottomEntry(list);
							if (list->selectPos < 0)
								list->selectPos = 0;
							while (1)
							{
								Int cellBottom = list->listData[list->selectPos].listHeight;
								Int cellTop = cellBottom - list->listData[list->selectPos].height;
								Int displayTop = list->displayPos;
								Int displayBottom = list->displayPos + list->displayHeight - 1;

								if (cellTop < displayTop)
								{
									Rva00324AE5Update(window, -1, TRUE);
								}
								else if (cellBottom < displayBottom)
								{
									Rva00324AE5Update(window, 0, TRUE);
									break;
								}
								else
								{
									Rva00324AE5Update(window, 1, TRUE);
								}
							}
						}
						list->m_field48 = -1;
						TheWindowManager->winSendSystemMsg(window->winGetOwner(),
							GLM_SELECTED, (WindowMsgData)window, list->selectPos);
						return MSG_HANDLED;
					}
					break;

				case KEY_TAB:
					if (mData2 & KEY_STATE_DOWN)
					{
						if (TheKeyboard->getModifierFlags() & KEY_STATE_LSHIFT)
							TheWindowManager->winPrevTab(window);
						else
							TheWindowManager->winNextTab(window);
					}
					break;

				default:
				{
					Bool foundIt = FALSE;
					if (BitTest(mData2, KEY_STATE_DOWN))
					{
						if (list->m_freeScroll)
							return MSG_IGNORED;
						Int position = list->selectPos;
						for (Int i = 0; i < list->endPos; ++i)
						{
							++position;
							if (position >= list->endPos)
								position = 0;

							ListEntryCell *cell = NULL;
							// go through the columns until we find a column with text
							for (Int j = 0; j < list->columns; ++j)
							{
								cell = &list->listData[position].cell[j];
								if (cell && cell->cellType == LISTBOX_TEXT && cell->data)
								{
									break;
								}
							}
							if (!cell || cell->cellType != LISTBOX_TEXT)
								continue;
							DisplayString *dString = (DisplayString *)cell->data;
							if (!dString)
								continue;
							for (j = 0; j < Keyboard::MAX_KEY_STATES; ++j)
							{
								if (dString->getText().getCharAt(0) ==
										TheKeyboard->getPrintableKey(mData1, j))
								{
									list->selectPos = position;
									Rva00324B8FScrollTo(window, position, 0);
									list->m_field48 = -1;
									TheWindowManager->winSendSystemMsg(window->winGetOwner(),
										GLM_SELECTED, (WindowMsgData)window, list->selectPos);
									foundIt = TRUE;
									break;
								}
							}
							if (foundIt)
							{
								((Rva00323E1C *)window)->rva00323E1C();
								break;
							}
						}
					}

					if (!foundIt)
						return MSG_IGNORED;
				}
			}

			break;
		}

		case GWM_WHEEL_DOWN:
		{
			if (list->m_freeScroll)
			{
				Int delta = 20;
				if (window->winGetFont())
					delta = window->winGetFont()->height;
				Rva00324B39Add(window, delta, TRUE);
				break;
			}
			if (list->endPos <= 0)
				break;

			if (list->listData[list->endPos - 1].listHeight >
					list->displayHeight + list->displayPos)
				Rva00324AE5Update(window, 1, TRUE);

			break;
		}

		case GWM_WHEEL_UP:
		{
			if (list->m_freeScroll)
			{
				Int delta = -20;
				if (window->winGetFont())
					delta = -window->winGetFont()->height;
				Rva00324B39Add(window, delta, TRUE);
				break;
			}
			if (list->endPos <= 0)
				break;

			Rva00324AE5Update(window, -1, TRUE);
			break;
		}

		case GWM_LEFT_UP:
		{
			if (list->m_noSelect)
				break;
			TheWindowManager->winSetFocus(window);
			Int mousex = mData1 & 0xFFFF;
			Int mousey = mData1 >> 16;
			Int x, y, i;
			Int oldPos = list->selectPos;
			Bool keepOldPos = FALSE;

			window->winGetScreenPosition(&x, &y);

			// Adjust for title if present
			if (instData->getTextLength())
				y += TheWindowManager->winFontHeight(instData->getFont()) + 1;

			list->selectPos = -2;

			for (i = 0; ; i++)
			{
				if (i > 0)
					if (list->listData[i - 1].listHeight >
							(list->displayPos + list->displayHeight))
					{
						list->selectPos = -1;
						break;
					}

				if (i == list->endPos)
				{
					list->selectPos = -1;
					break;
				}

				if (list->listData[i].listHeight > (mousey - y + list->displayPos))
				{
					if (list->listData[i].m_disabled)
						list->selectPos = -1;
					break;
				}
			}

			if ((i == oldPos) && (list->forceSelect == FALSE))
			{
				list->selectPos = -1;
			}

			if ((list->selectPos == -2) && (i < list->endPos))
			{
				list->selectPos = i;
			}

			if ((list->selectPos < 0) && (list->forceSelect))
			{
				keepOldPos = TRUE;
				list->selectPos = oldPos;
			}

			Int relativeX = mousex - x;
			list->m_field48 = -1;
			if (relativeX > 1)
			{
				for (Int column = 0; column < list->columns; ++column)
				{
					if (list->columnWidth[column] > relativeX)
					{
						list->m_field48 = column;
						break;
					}
					relativeX -= list->columnWidth[column];
				}
			}

			if (list->doubleClickTime + g_00E01D48 > timeGetTime() &&
					(i == oldPos || (oldPos == -1 && (i >= 0 && i < list->endPos))))
			{
				Int temp;
				list->doubleClickTime = 0;
				if (oldPos == -1)
					temp = i;
				else
					temp = oldPos;
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GLM_DOUBLE_CLICKED, (WindowMsgData)window, temp);
			}
			list->doubleClickTime = timeGetTime();
			if (!keepOldPos)
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GLM_SELECTED, (WindowMsgData)window, list->selectPos);

			break;
		}

		case GWM_RIGHT_DOWN:
			((Rva00323E1C *)window)->rva00323E1C();
			break;

		case GWM_RIGHT_UP:
		{
			TheWindowManager->winSetFocus(window);
			Int pos;
			Int mousex = mData1 & 0xFFFF;
			Int mousey = mData1 >> 16;
			Int x, y, i;
			RightClickStruct rc;

			window->winGetScreenPosition(&x, &y);

			// Adjust for title if present
			if (instData->getTextLength())
				y += TheWindowManager->winFontHeight(instData->getFont()) + 1;

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

				if (list->listData[i].listHeight > (mousey - y + list->displayPos))
					break;
			}

			if (pos == -2)
				pos = i;

			rc.pos = pos;
			rc.mouseX = mousex;
			rc.mouseY = mousey;
			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GLM_RIGHT_CLICKED, (WindowMsgData)window, (WindowMsgData)&rc);
			break;
		}

		case GWM_MOUSE_ENTERING:
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
			{
				BitSet(instData->m_state, WIN_STATE_HILITED);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GBM_MOUSE_ENTERING, (WindowMsgData)window, 0);
			}
			break;

		case GWM_MOUSE_LEAVING:
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
			{
				BitClear(instData->m_state, WIN_STATE_HILITED);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GBM_MOUSE_LEAVING, (WindowMsgData)window, 0);
			}
			break;

		case GWM_MOUSE_POS:
		{
			GameWindow *lone = TheWindowManager->winGetLoneWindow();
			if (lone && lone != window &&
					!((Rva003140AB *)lone)->rva003140AB((Rva003140AB *)window))
				return MSG_IGNORED;
			if (list->m_trackMouseOver)
			{
				Int column;
				getListboxEntryBasedOnCoord(window, mData1 & 0xFFFF, mData1 >> 16,
					list->mouseOverRow, column);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(), msg,
					(WindowMsgData)window, mData1);
			}
			break;
		}

		case GWM_LEFT_DRAG:
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GGM_LEFT_DRAG, (WindowMsgData)window, 0);
			break;

		case GWM_LEFT_DOWN:
			((Rva00323E1C *)window)->rva00323E1C();
			return MSG_HANDLED;

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
