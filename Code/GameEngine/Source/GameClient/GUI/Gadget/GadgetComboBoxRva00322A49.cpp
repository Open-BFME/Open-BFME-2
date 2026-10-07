// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc
// ?Rva00322A49Show@@YAXPAVGameWindow@@@Z @0x00322A49 476B (Ghidra boundary,
// EH frame). The combo box drop-down toggle that GadgetComboBoxInput
// (0x00322C25) calls on GWM_LEFT_UP; ZH/BFME1 donor GadgetComboBox.cpp keeps
// this logic inline in the GWM_LEFT_UP case. Target facts: bails when the
// combo's +0x24 child (rowed 0x002C02FE under the name GadgetComboBoxGetEditBox,
// which really returns the drop-down button) is absent or hidden; clears
// dontHide (+0x1C); takes the list box through the rowed 0x002C0315 (+0x2C,
// rowed as bfmeGo925A); when it is hidden makes the combo the lone window
// (manager slot 52), needs more than one entry (+0x20, the field the rowed
// GadgetComboBoxGetLength returns), shows it, sets list bytes +0x12/+0x13,
// copies +0x34 to +0x30, hides or shows the list's up/down/slider children
// (+0x1C/+0x20/+0x24) against maxDisplay (+4) and sizes everything from
// (winFontHeight(font +0x184) + 1) * rows + 3; otherwise the rowed HideListBox
// (0x003229C5) and winSetLoneWindow(NULL). BFME2 moves the click sound after
// the toggle: TheAudio misc audio +0xC0 into the rowed event ctor 0x002D97D6,
// addAudioEvent (slot 25) and the rowed dtor 0x002D9A43, as in the sibling
// 0x00323E1C. Field names beyond those offsets are Zero Hour's.
//
// ?GadgetComboBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// @0x00322C25 252B: ZH/BFME1 donor GadgetComboBoxInput, the cdecl input
// callback in slot 1 of the gadget vtable 0x00BC8FF4. Target facts: instance
// data through the rowed winGetInstanceData, the edit box through 0x002C032C
// (+0x28, rowed as GadgetComboBoxGetListBox); GWM_LEFT_DOWN (5) is ignored
// while the combo is the lone window (manager slot 53); GWM_LEFT_UP (6) runs
// the drop-down toggle above then the rowed Apt input forwarder 0x006CC9A0
// (0, 1, 1); GWM_LEFT_DRAG (8) forwards 0x4000 to the owner through
// winSendSystemMsg (slot 58) under style 0x400; right-up and the wheels are
// eaten; GWM_CHAR (21) turns a pressed KEY_TAB (0xF) into winPrevTab /
// winNextTab (slots 43/42) by TheKeyboard's shift bit (+0xC & 0x10) and sends
// every other key to the edit box through winSendInputMsg (slot 59).
#include "Common/BfmeAudioEventPrefix136.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

enum
{
	GWM_LEFT_DOWN = 5,
	GWM_LEFT_UP = 6,
	GWM_LEFT_DRAG = 8,
	GWM_RIGHT_UP = 14,
	GWM_WHEEL_UP = 19,
	GWM_WHEEL_DOWN = 20,
	GWM_CHAR = 21
};

enum { GGM_LEFT_DRAG = 0x4000 };
enum { GWS_MOUSE_TRACK = 0x400 };
enum { KEY_TAB = 0x0F };
enum { KEY_STATE_DOWN = 0x02, KEY_STATE_LSHIFT = 0x10 };

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

class WinInstanceData
{
public:
	unsigned int getStyle() { return m_style; }
	GameFont *getFont() { return m_font; }

	unsigned char m_pad00[0xC];
	unsigned int m_style;
	unsigned char m_pad10[0x184 - 0x10];
	GameFont *m_font;
};

class GameWindow
{
public:
	GameWindow *winGetOwner();
	Bool winIsHidden();
	Int winHide(Bool hide);
	Int winGetSize(Int *width, Int *height);
	Int winSetSize(Int width, Int height);
	Int winSetPosition(Int x, Int y);
	WinInstanceData *winGetInstanceData();
	void *winGetUserData();
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

struct ListboxData
{
	unsigned char m_pad00[0x12];
	Bool m_flag12;
	Bool m_flag13;
	unsigned char m_pad14[0x1C - 0x14];
	GameWindow *upButton;
	GameWindow *downButton;
	GameWindow *slider;
	unsigned char m_pad28[0x30 - 0x28];
	Int m_field30;
	Int selectPos;
};

// 0x002C02FE returns +0x24 (dropDownButton); 0x002C0315 returns +0x2C (listBox);
// 0x002C032C returns +0x28 (editBox).
GameWindow *GadgetComboBoxGetEditBox(GameWindow *comboBox);
GameWindow *GadgetComboBoxGetListBox(GameWindow *comboBox);
void *bfmeGo925A(BfmeKeyLC *k);
void Rva003229C5Hide(GameWindow *window);

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
	V(48) V(49) V(50) V(51)
	virtual void winSetLoneWindow(GameWindow *window) = 0;
	virtual GameWindow *winGetLoneWindow() = 0;
	V(54) V(55)
	V(56) V(57)
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window,
		UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
	virtual WindowMsgHandledType winSendInputMsg(GameWindow *window,
		UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
	V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
	virtual Int winFontHeight(GameFont *font) = 0;
#undef V
};

extern GameWindowManager *TheWindowManager;

struct MiscAudioView
{
	char _pad[0xC0];
	OpaqueRefElement4 guiClickSound;
};

class AudioManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24)
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *evt) = 0;
	V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
	V(72) V(73) V(74) V(75) V(76) V(77)
#undef V
	virtual const MiscAudioView *getMiscAudio() = 0;
};

extern AudioManager *TheAudio;

void Rva00322A49Show(GameWindow *comboBox)
{
	if (!comboBox)
		return;

	GameWindow *dropDown = GadgetComboBoxGetEditBox(comboBox);
	if (!dropDown || dropDown->winIsHidden())
		return;

	ComboBoxData *comboData = (ComboBoxData *)comboBox->winGetUserData();
	comboData->dontHide = false;

	GameWindow *listBox = (GameWindow *)bfmeGo925A((BfmeKeyLC *)comboBox);
	if (!listBox)
		return;

	// If the Listbox isn't showing, Show it.
	if (listBox->winIsHidden())
	{
		TheWindowManager->winSetLoneWindow(comboBox);
		if (comboData->entryCount <= 1)
			return;

		ICoord2D winSize;
		ICoord2D newSize;
		Int listX;
		Int multiplier;

		listBox->winHide(false);
		comboBox->winGetSize(&winSize.x, &winSize.y);
		WinInstanceData *listInstData = listBox->winGetInstanceData();
		ListboxData *listData = (ListboxData *)listBox->winGetUserData();
		listData->m_flag12 = true;
		listData->m_flag13 = true;
		listData->m_field30 = listData->selectPos;

		// If we have less entries then our max display is set to, only show
		// those entries and not additional blank lines.  Also, just so it looks
		// pretty, hide the list box's sliders if we don't need to scroll.
		if (comboData->entryCount <= comboData->maxDisplay)
		{
			multiplier = comboData->entryCount;
			listX = winSize.x;

			if (listData->upButton)
				listData->upButton->winHide(true);
			if (listData->downButton)
				listData->downButton->winHide(true);
			if (listData->slider)
				listData->slider->winHide(true);
		}
		else
		{
			multiplier = comboData->maxDisplay;
			listX = winSize.x;
			if (listData->upButton)
				listData->upButton->winHide(false);
			if (listData->downButton)
				listData->downButton->winHide(false);
			if (listData->slider)
				listData->slider->winHide(false);
		}

		newSize.y = (TheWindowManager->winFontHeight(listInstData->getFont()) + 1) * multiplier + 3;
		comboBox->winSetSize(winSize.x, winSize.y + newSize.y);
		listBox->winSetPosition(0, winSize.y);
		listBox->winSetSize(listX, newSize.y);
	}
	// if the Listbox was showing, hide it.
	else
	{
		Rva003229C5Hide(comboBox);
		TheWindowManager->winSetLoneWindow(NULL);
	}

	if (TheAudio)
	{
		BfmeAudioEventPrefix136 buttonClick(TheAudio->getMiscAudio()->guiClickSound, 2);
		TheAudio->addAudioEvent(&buttonClick);
	}
}

class Keyboard
{
public:
	Int getModifierFlags() { return m_modifiers; }

	unsigned char m_pad00[0xC];
	// Retail mouse callers read the modifier word at +0x0c.
	unsigned short m_modifiers;
};

extern Keyboard *TheKeyboard;

void Rva006CC9A0(Int a, Int b, Int c);

WindowMsgHandledType GadgetComboBoxInput(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	WinInstanceData *instData = window->winGetInstanceData();
	GameWindow *editBox = GadgetComboBoxGetListBox(window);
	switch (msg)
	{
		case GWM_CHAR:
		{
			switch (mData1)
			{
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
					return TheWindowManager->winSendInputMsg(editBox, GWM_CHAR, mData1, mData2);
			}
			break;
		}

		case GWM_WHEEL_DOWN:
			break;

		case GWM_WHEEL_UP:
			break;

		case GWM_LEFT_DOWN:
			if (TheWindowManager->winGetLoneWindow() == window)
				return MSG_IGNORED;
			break;

		case GWM_LEFT_UP:
			Rva00322A49Show(window);
			Rva006CC9A0(0, 1, 1);
			break;

		case GWM_RIGHT_UP:
			break;

		case GWM_LEFT_DRAG:
			if (instData->getStyle() & GWS_MOUSE_TRACK)
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GGM_LEFT_DRAG, (WindowMsgData)window, 0);
			break;

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
