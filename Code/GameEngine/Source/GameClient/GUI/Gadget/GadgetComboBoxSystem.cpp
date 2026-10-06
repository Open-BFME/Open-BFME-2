// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /DNDEBUG /MD /EHsc
// ?GadgetComboBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// @0x00322E6D 1803B (Ghidra boundary, EH frame): the combo box system
// callback. Reference semantics: ZH/BFME1 donor GadgetComboBox.cpp
// GadgetComboBoxSystem. Target facts: instance data through the rowed
// winGetInstanceData and the combo record through winGetUserData, with the
// BFME2 combo layout of the sibling GadgetComboBoxRva00322A49.cpp (dontHide
// +0x1C, entryCount +0x20, dropDownButton +0x24, editBox +0x28, listBox
// +0x2C); the child getters 0x002C0315 (list box, rowed as bfmeGo925A) and
// 0x002C032C (edit box, rowed as GadgetComboBoxGetListBox); BFME2's gadget
// message numbering read from the dispatch (GBM_SELECTED 0x4008, GLM_SELECTED
// 0x4014, GCM_ADD_ENTRY 0x4022 and a new row-text message 0x4023 before
// GCM_DEL_ENTRY 0x4024 ... GEM_UPDATE_TEXT 0x4032, jump table 0x00323578).
// BFME2 changes against the donor: GGM_FOCUS_CHANGE from the edit box sets
// its drawTextFromStart (+0x16); GGM_RESIZED scales the drop-down button to
// the height from its enabled image's size (image +0x24/+0x28); add-entry
// re-enables the drop-down button by entry count when the list is enabled
// and uses (fontHeight + 2) * rows + 4; delete-all and window message 28
// disable it; GBM_SELECTED calls the rowed drop-down toggle 0x00322A49;
// edit-done sends GCM_SELECTED with -1 and tabs on; GWM_DESTROY checks
// TheWindowManager before clearing the lone window. Retail lays the shared
// MSG_HANDLED exit between delete-all and the row-text case, which the
// row-text case's own return reproduces.
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef int Color;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

enum
{
	GWM_CREATE = 1,
	GWM_DESTROY = 2,
	GWM_INPUT_FOCUS = 23,
	GWM_MSG_28 = 28
};

enum
{
	GGM_LEFT_DRAG = 0x4000,
	GGM_SET_LABEL = 0x4001,
	GGM_FOCUS_CHANGE = 0x4003,
	GGM_RESIZED = 0x4004,
	GGM_CLOSE = 0x4005,
	GBM_SELECTED = 0x4008,
	GLM_SELECTED = 0x4014,
	GCM_ADD_ENTRY = 0x4022,
	GCM_SET_ENTRY_TEXT = 0x4023,
	GCM_DEL_ENTRY = 0x4024,
	GCM_DEL_ALL = 0x4025,
	GCM_SELECTED = 0x4026,
	GCM_GET_TEXT = 0x4027,
	GCM_SET_TEXT = 0x4028,
	GCM_EDIT_DONE = 0x4029,
	GCM_GET_ITEM_DATA = 0x402A,
	GCM_SET_ITEM_DATA = 0x402B,
	GCM_GET_SELECTION = 0x402C,
	GCM_SET_SELECTION = 0x402D,
	GCM_UPDATE_TEXT = 0x402E,
	GEM_EDIT_DONE = 0x4031,
	GEM_UPDATE_TEXT = 0x4032
};

enum { WIN_STATE_HILITED = 0x02 };
enum { WIN_STATUS_ENABLED = 0x08 };

#define BitTest(x, i) (((x) & (i)) != 0)
#define BitSet(x, i) ((x) |= (i))
#define BitClear(x, i) ((x) &= ~(i))

#ifndef NULL
#define NULL 0
#endif

struct ICoord2D
{
	Int x;
	Int y;
};

class GameFont;
class GameWindow;
class BfmeKeyLC;

class Image
{
public:
	Int getImageWidth() const { return m_imageSize.x; }
	Int getImageHeight() const { return m_imageSize.y; }

	unsigned char m_pad00[0x24];
	ICoord2D m_imageSize;
};

struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

class WinInstanceData
{
public:
	GameFont *getFont() { return m_font; }
	void setText(UnicodeString text);

	void *m_vtable;
	Int m_id;
	UnsignedInt m_state;
	UnsignedInt m_style;
	UnsignedInt m_status;
	GameWindow *m_owner;
	WinDrawData m_enabledDrawData[1];
	unsigned char m_pad24[0x184 - 0x24];
	GameFont *m_font;
};

class GameWindow
{
public:
	UnsignedInt winGetStatus();
	Int winGetWindowId();
	GameWindow *winGetOwner();
	Bool winIsHidden();
	Int winHide(Bool hide);
	Int winEnable(Bool enable);
	Int winGetSize(Int *width, Int *height);
	Int winSetSize(Int width, Int height);
	Int winSetPosition(Int x, Int y);
	WinInstanceData *winGetInstanceData();
	void *winGetUserData();
	const Image *winGetEnabledImage(Int index) { return m_instData.m_enabledDrawData[index].image; }

	unsigned char m_pad00[0x30];
	WinInstanceData m_instData;
};

struct ComboBoxData
{
	Bool isEditable;
	Int maxDisplay;
	unsigned char m_pad08[0x1C - 0x8];
	Bool dontHide;
	Int entryCount;
	GameWindow *dropDownButton;
	GameWindow *editBox;
	GameWindow *listBox;
	unsigned char m_pad30[0x34 - 0x30];
};

struct EntryData
{
	unsigned char m_pad00[0x16];
	Bool drawTextFromStart;
};

struct ListboxData
{
	short listLength;
	unsigned char m_pad02[0x1C - 0x2];
	GameWindow *upButton;
	GameWindow *downButton;
	GameWindow *slider;
};

// 0x002C0315 returns +0x2C (listBox); 0x002C032C returns +0x28 (editBox).
void *bfmeGo925A(BfmeKeyLC *k);
GameWindow *GadgetComboBoxGetListBox(GameWindow *comboBox);
void Rva003229C5Hide(GameWindow *window);
void Rva00322A49Show(GameWindow *comboBox);

UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void GadgetTextEntrySetTextColor(GameWindow *textEntry, Color color);
void GadgetListBoxGetSelected(GameWindow *listbox, Int *selectList);
void GadgetListBoxSetSelected(GameWindow *listbox, Int selectIndex);
void GadgetListBoxReset(GameWindow *listbox);
void GadgetListBoxSetListLength(GameWindow *listbox, Int newLength);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, Int row, Int column);
void *GadgetListBoxGetItemData(GameWindow *listbox, Int row, Int column);
Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, Color color,
	Int row, Int column, Bool overwrite);
UnicodeString GadgetListBoxGetTextAndColor(GameWindow *listbox, Color *color, Int row, Int column);

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
	V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51)
	virtual void winSetLoneWindow(GameWindow *window) = 0;
	V(53) V(54) V(55)
	V(56) V(57)
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window,
		UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
	V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
	virtual Int winFontHeight(GameFont *font) = 0;
#undef V
};

extern GameWindowManager *TheWindowManager;

WindowMsgHandledType GadgetComboBoxSystem(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	WinInstanceData *instData = window->winGetInstanceData();
	ComboBoxData *comboData = (ComboBoxData *)window->winGetUserData();
	switch (msg)
	{
		case GWM_MSG_28:
		{
			if (comboData->entryCount <= 1)
				comboData->dropDownButton->winEnable(false);
			break;
		}

		case GGM_SET_LABEL:
		{
			instData->setText(*(UnicodeString *)mData1);
			break;
		}

		case GCM_GET_TEXT:
		{
			if (comboData->editBox)
				*(UnicodeString *)mData2 = GadgetTextEntryGetText(comboData->editBox);
			break;
		}

		case GCM_SET_TEXT:
		{
			if (comboData->editBox)
				GadgetTextEntrySetText(comboData->editBox, *(const UnicodeString *)mData1);
			break;
		}

		case GEM_UPDATE_TEXT:
		{
			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GCM_UPDATE_TEXT, (WindowMsgData)window, 0);
			if (comboData->listBox)
			{
				GadgetListBoxSetSelected(comboData->listBox, -1);
				Rva003229C5Hide(window);
			}
			break;
		}

		// if we get sent an edit done message from the text box, lets notify the parent
		case GEM_EDIT_DONE:
		{
			if ((GameWindow *)mData1 == comboData->editBox)
			{
				Rva003229C5Hide(window);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GCM_SELECTED, (WindowMsgData)window, (WindowMsgData)-1);
				TheWindowManager->winNextTab(window);
			}
			break;
		}

		case GCM_SET_SELECTION:
		{
			GameWindow *listBox = (GameWindow *)bfmeGo925A((BfmeKeyLC *)window);
			if (listBox)
			{
				if (!listBox->winIsHidden() && mData2 == true)
					comboData->dontHide = true;

				GadgetListBoxSetSelected(listBox, (Int)mData1);
			}
			break;
		}

		case GCM_GET_SELECTION:
		{
			if (comboData->listBox)
				GadgetListBoxGetSelected(comboData->listBox, (Int *)mData2);
			else
				*(Int *)mData2 = -1;
			break;
		}

		case GCM_SET_ITEM_DATA:
		{
			if (comboData->listBox)
				GadgetListBoxSetItemData(comboData->listBox, (void *)mData2, (Int)mData1, 0);
			break;
		}

		case GCM_GET_ITEM_DATA:
		{
			if (comboData->listBox)
				*(void **)mData2 = GadgetListBoxGetItemData(comboData->listBox, (Int)mData1, 0);
			break;
		}

		// Pass onto the parent window the selection the listbox just made
		case GLM_SELECTED:
		{
			if ((GameWindow *)mData1 == comboData->listBox)
			{
				if (comboData->dontHide == true)
					comboData->dontHide = false;
				else
					Rva003229C5Hide(window);

				// Nothing was actually selected
				if (mData2 == -1)
					break;

				// Grab the text that was selected
				UnicodeString tempUString;
				Color color;
				tempUString = GadgetListBoxGetTextAndColor(comboData->listBox, &color, mData2, 0);

				GadgetTextEntrySetTextColor(comboData->editBox, color);

				GadgetTextEntrySetText(comboData->editBox, tempUString);

				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GCM_SELECTED, (WindowMsgData)window, 0);
			}
			break;
		}

		case GGM_LEFT_DRAG:
			break;

		case GCM_DEL_ALL:
		{
			if (comboData->listBox)
				GadgetListBoxReset(comboData->listBox);
			if (comboData->editBox)
				GadgetTextEntrySetText(comboData->editBox, UnicodeString::TheEmptyString);
			comboData->entryCount = 0;
			comboData->dropDownButton->winEnable(false);
			break;
		}

		case GCM_DEL_ENTRY:
			break;

		case GGM_CLOSE:
		{
			Rva003229C5Hide(window);
			break;
		}

		case GCM_ADD_ENTRY:
		{
			GameWindow *listBox = (GameWindow *)bfmeGo925A((BfmeKeyLC *)window);
			ListboxData *listData = (ListboxData *)listBox->winGetUserData();

			Int addedIndex = -1;
			if (listBox)
			{
				// Increase our internal entry count
				comboData->entryCount++;
				// If we've exceeded the set listlength, resize it to twice the size
				if (comboData->entryCount >= listData->listLength)
					GadgetListBoxSetListLength(listBox, listData->listLength * 2);
				// Add the entry to the Listbox
				addedIndex = GadgetListBoxAddEntryText(listBox, *(UnicodeString *)mData1, mData2, -1, 0, true);

				// Now resize the list box
				ICoord2D winSize;
				ICoord2D newSize;
				ICoord2D editBoxSize;
				Int listX;
				Int multiplier;
				WinInstanceData *listInstData = listBox->winGetInstanceData();
				GameWindow *editBox = GadgetComboBoxGetListBox(window);
				window->winGetSize(&winSize.x, &winSize.y);
				editBox->winGetSize(&editBoxSize.x, &editBoxSize.y);
				// If the listbox has less entries then the MaxDisplay, size it smaller
				if (comboData->entryCount <= comboData->maxDisplay)
				{
					multiplier = comboData->entryCount;
					listX = winSize.x + 16;
					if (listData->upButton)
						listData->upButton->winHide(true);
					if (listData->downButton)
						listData->downButton->winHide(true);
					if (listData->slider)
						listData->slider->winHide(true);
				}
				else
				{
					// Else size it to the MaxDisplay Size
					multiplier = comboData->maxDisplay;
					listX = winSize.x;
					if (listData->upButton)
						listData->upButton->winHide(false);
					if (listData->downButton)
						listData->downButton->winHide(false);
					if (listData->slider)
						listData->slider->winHide(false);
				}
				newSize.y = (TheWindowManager->winFontHeight(listInstData->getFont()) + 2) * multiplier + 4;
				listBox->winSetPosition(0, editBoxSize.y);
				listBox->winSetSize(listX, newSize.y);

				if (BitTest(listBox->winGetStatus(), WIN_STATUS_ENABLED))
					comboData->dropDownButton->winEnable(comboData->entryCount > 1);
			}

			return (WindowMsgHandledType)addedIndex;
		}

		// Replace the text of one row, keeping its color, and the edit box
		// text when that row is the selection.
		case GCM_SET_ENTRY_TEXT:
		{
			GameWindow *listBox = (GameWindow *)bfmeGo925A((BfmeKeyLC *)window);
			ListboxData *listData;
			if (listBox && (listData = (ListboxData *)listBox->winGetUserData()) != NULL)
			{
				Color color;
				UnicodeString text = GadgetListBoxGetTextAndColor(listBox, &color, mData2, 0);
				if (((UnicodeString *)mData1)->compare(text))
					GadgetListBoxAddEntryText(listBox, *(UnicodeString *)mData1, color, mData2, 0, true);

				Int selected = 0;
				GadgetListBoxGetSelected(listBox, &selected);
				if (selected == (Int)mData2 || selected < 0)
					GadgetTextEntrySetText(GadgetComboBoxGetListBox(window), *(UnicodeString *)mData1);
			}
			return MSG_HANDLED;
		}

		case GWM_CREATE:
			break;

		case GGM_RESIZED:
		{
			Int width = (Int)mData1;
			Int height = (Int)mData2;
			ICoord2D dropDownSize;

			// get needed window sizes
			comboData->dropDownButton->winGetSize(&dropDownSize.x, &dropDownSize.y);

			GameWindow *listBox = (GameWindow *)bfmeGo925A((BfmeKeyLC *)window);
			if (listBox->winIsHidden())
			{
				if (listBox)
					listBox->winSetSize(width, height);

				if (comboData->dropDownButton)
				{
					const Image *image = comboData->dropDownButton->winGetEnabledImage(0);
					if (image)
					{
						Real scale = (Real)height;
						dropDownSize.x = image->getImageWidth();
						Real imageHeight = (Real)image->getImageHeight();
						scale /= imageHeight;
						dropDownSize.x = (Int)(dropDownSize.x * scale);
						dropDownSize.y = (Int)(imageHeight * scale);
					}
					comboData->dropDownButton->winSetPosition(width - dropDownSize.x, 0);
					comboData->dropDownButton->winSetSize(dropDownSize.x, dropDownSize.y);
				}

				if (comboData->editBox)
				{
					comboData->editBox->winSetPosition(0, 0);
					comboData->editBox->winSetSize(width - dropDownSize.x, height);
				}
			}
			break;
		}

		case GWM_DESTROY:
		{
			// if we are transitioning screens, close all combo boxes
			if (TheWindowManager)
				TheWindowManager->winSetLoneWindow(NULL);
			if (comboData)
			{
				delete comboData;
				comboData = NULL;
			}
			break;
		}

		case GWM_INPUT_FOCUS:
		{
			// If we're losing focus
			if (mData1 == false)
				BitClear(instData->m_state, WIN_STATE_HILITED);
			else
				BitSet(instData->m_state, WIN_STATE_HILITED);

			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GGM_FOCUS_CHANGE, mData1, window->winGetWindowId());

			Bool wantsFocus = false;
			GameWindow *editBox = GadgetComboBoxGetListBox(window);
			// we need to tell the text entry box to take the focus.
			TheWindowManager->winSendSystemMsg(editBox, GWM_INPUT_FOCUS, mData1, (WindowMsgData)&wantsFocus);

			*(Bool *)mData2 = true;
			break;
		}

		case GGM_FOCUS_CHANGE:
		{
			GameWindow *editBox = GadgetComboBoxGetListBox(window);
			if ((Int)mData2 == editBox->winGetWindowId())
			{
				EntryData *entryData = (EntryData *)editBox->winGetUserData();
				if (mData1)
					entryData->drawTextFromStart = false;
				else
					entryData->drawTextFromStart = true;
			}
			break;
		}

		case GBM_SELECTED:
		{
			// See if the drop down button was selected
			if ((GameWindow *)mData1 == comboData->dropDownButton)
				Rva00322A49Show(window);
			break;
		}

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
