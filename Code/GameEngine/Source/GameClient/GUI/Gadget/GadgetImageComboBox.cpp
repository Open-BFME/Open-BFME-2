// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc
// ?GadgetImageComboBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// @0x0032386A 497B (Ghidra boundary, EH frame): the image combo box input
// callback, slot 0x54 of the input table 0x9BCAD8. Reference semantics:
// Open-BFME-1 GadgetImageComboBox.cpp GadgetImageComboBoxInput, itself the
// combo box input with the drop-down list kept in the user data. Target
// facts: the user data holds the drop-down button at +4 and the list box at
// +8; GWM_SCRIPT_CREATE (22) finds the child through manager slot 60 and
// files a push button (style 1) at +4 or a list box (style 0x20) at +8,
// setting the list's bytes +0x12, +0x13 and +0x0E; GWM_LEFT_UP (6) plays the
// misc-audio click (+0xC0, as GadgetComboBoxRva00322A49.cpp does), toggles the
// list through the one-pointer helper 0x00323736 on a copy of the window and
// calls the Apt input forwarder 0x006CC9A0 (0, 1, 1); GWM_LEFT_DOWN (5) is
// ignored while the combo is the lone window (slot 53); GWM_LEFT_DRAG (8)
// forwards 0x4000 to the owner under style 0x400; right-up and the wheels are
// eaten; GWM_CHAR (21) handles only KEY_TAB, choosing winPrevTab/winNextTab
// by TheKeyboard's shift bit. The switch tree pivots on 19, so the two wheel
// cases reach "handled" through different labels; which case returns
// directly is not recoverable (any split of 19 from 20 compiles the same).
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
	GWM_CHAR = 21,
	GWM_SCRIPT_CREATE = 22
};

enum { GGM_LEFT_DRAG = 0x4000 };
enum { GWS_PUSH_BUTTON = 0x01, GWS_SCROLL_LISTBOX = 0x20, GWS_MOUSE_TRACK = 0x400 };
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
	UnsignedInt winGetStyle();
};

struct ImageComboBoxData
{
	Int maxListHeight;
	GameWindow *dropDownButton;
	GameWindow *listBox;
};

struct ListboxData
{
	unsigned char m_pad00[0x0E];
	Bool m_flag0E;
	unsigned char m_pad0F[0x12 - 0x0F];
	Bool m_flag12;
	Bool m_flag13;
	unsigned char m_pad14[0x1C - 0x14];
	GameWindow *upButton;
	GameWindow *downButton;
	GameWindow *slider;
	Int totalHeight;
	unsigned char m_pad2C[0x30 - 0x2C];
	Int m_field30;
	Int selectPos;
};

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
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id) = 0;
	V(61) V(62) V(63)
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

class Keyboard
{
public:
	Int getModifierFlags() { return m_modifiers; }

	unsigned char m_pad00[0xC];
	// Retail mouse callers read the modifier word at +0x0c.
	unsigned short m_modifiers;
};

extern Keyboard *TheKeyboard;

// The one-pointer combo wrapper of MpGameSetupSlots.cpp; its 0x00323736 is
// the drop-down toggle (BFME1 Rva004B5C90::invoke), pinned there by address.
class MpGameSetupComboRef
{
public:
	void rva00323736(bool flag);

	GameWindow *m_window;
};

void Rva003248F5Show(GameWindow *listBox, bool hide);

void MpGameSetupComboRef::rva00323736(bool hide)
{
	GameWindow *listBox = ((ImageComboBoxData *)m_window->winGetUserData())->listBox;
	if (!listBox)
		return;

	ICoord2D windowSize;
	if (hide)
	{
		ICoord2D listSize;
		if (listBox->winIsHidden())
			return;
		m_window->winGetSize(&windowSize.x, &windowSize.y);
		listBox->winGetSize(&listSize.x, &listSize.y);
		listBox->winHide(true);
		GameWindow *current = m_window;
		if (TheWindowManager->winGetLoneWindow() == current)
			TheWindowManager->winSetLoneWindow(NULL);
		m_window->winSetSize(windowSize.x, windowSize.y - listSize.y);
	}
	else
	{
		ICoord2D listSize;
		if (!listBox->winIsHidden())
			return;
		TheWindowManager->winSetLoneWindow(m_window);
		listBox->winHide(false);
		m_window->winGetSize(&windowSize.x, &windowSize.y);
		ListboxData *listData = (ListboxData *)((ImageComboBoxData *)m_window->winGetUserData())->listBox->winGetUserData();
		ImageComboBoxData *comboData = (ImageComboBoxData *)m_window->winGetUserData();
		listData->m_field30 = listData->selectPos;
		listSize = windowSize;
		Int total = listData->totalHeight + 8;
		Int maximum = comboData->maxListHeight;
		Int height;
		if (maximum >= total)
		{
			height = total;
			Rva003248F5Show(listBox, true);
		}
		else
		{
			height = maximum;
			Rva003248F5Show(listBox, false);
		}
		m_window->winSetSize(windowSize.x, windowSize.y + height);
		listBox->winSetPosition(0, windowSize.y);
		listBox->winSetSize(listSize.x, height);
	}
}

void Rva006CC9A0(Int a, Int b, Int c);

WindowMsgHandledType GadgetImageComboBoxInput(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	GameWindow *combo = window;
	WinInstanceData *instData = window->winGetInstanceData();

	switch (msg)
	{
		case GWM_CHAR:
			if (mData1 != KEY_TAB)
				return MSG_IGNORED;
			if (mData2 & KEY_STATE_DOWN)
			{
				if (TheKeyboard->getModifierFlags() & KEY_STATE_LSHIFT)
					TheWindowManager->winPrevTab(window);
				else
					TheWindowManager->winNextTab(window);
			}
			break;

		case GWM_LEFT_UP:
		{
			if (TheAudio)
			{
				BfmeAudioEventPrefix136 buttonClick(TheAudio->getMiscAudio()->guiClickSound, 2);
				TheAudio->addAudioEvent(&buttonClick);
			}
			GameWindow *listBox = ((ImageComboBoxData *)window->winGetUserData())->listBox;
			((MpGameSetupComboRef *)&combo)->rva00323736(!listBox->winIsHidden());
			Rva006CC9A0(0, 1, 1);
			break;
		}

		case GWM_LEFT_DRAG:
			if (instData->getStyle() & GWS_MOUSE_TRACK)
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GGM_LEFT_DRAG, (WindowMsgData)window, 0);
			break;

		case GWM_SCRIPT_CREATE:
		{
			GameWindow *child = TheWindowManager->winGetWindowFromId(window, (Int)mData1);
			if (child)
			{
				ImageComboBoxData *comboData = (ImageComboBoxData *)window->winGetUserData();
				if (child->winGetStyle() & GWS_PUSH_BUTTON)
					comboData->dropDownButton = child;
				else if (child->winGetStyle() & GWS_SCROLL_LISTBOX)
				{
					comboData->listBox = child;
					((ListboxData *)((ImageComboBoxData *)window->winGetUserData())->listBox->winGetUserData())->m_flag12 = true;
					((ListboxData *)((ImageComboBoxData *)window->winGetUserData())->listBox->winGetUserData())->m_flag13 = true;
					((ListboxData *)((ImageComboBoxData *)window->winGetUserData())->listBox->winGetUserData())->m_flag0E = true;
				}
			}
			break;
		}

		case GWM_LEFT_DOWN:
			if (TheWindowManager->winGetLoneWindow() == window)
				return MSG_IGNORED;
			break;

		case GWM_RIGHT_UP:
		case GWM_WHEEL_UP:
			break;

		case GWM_WHEEL_DOWN:
			return MSG_HANDLED;

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
