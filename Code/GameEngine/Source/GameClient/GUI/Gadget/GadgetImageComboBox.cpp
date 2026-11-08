// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// platformsdk
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
#include <string.h>
#include <windows.h>
#include "Common/BfmeAudioEventPrefix136.h"
#include "unicode_string.h"

typedef int Int;
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
	GWM_WHEEL_UP = 19,
	GWM_WHEEL_DOWN = 20,
	GWM_CHAR = 21,
	GWM_SCRIPT_CREATE = 22,
	GWM_INPUT_FOCUS = 23
};

enum
{
	GGM_LEFT_DRAG = 0x4000,
	GGM_SET_LABEL = 0x4001,
	GGM_FOCUS_CHANGE = 0x4003,
	GGM_RESIZED = 0x4004,
	GGM_CLOSE = 0x4005,
	GBM_SELECTED = 0x4008,
	GCM_SELECTED = 0x4014,
	GCM_ADD_ENTRY = 0x4022,
	GCM_DEL_ALL = 0x4024,
	GCM_RESET = 0x4025,
	GCM_UPDATE_TEXT = 0x4026,
	GCM_GET_ITEM_DATA = 0x402A,
	GCM_SET_ITEM_DATA = 0x402B,
	GCM_GET_SELECTION = 0x402C,
	GCM_SET_SELECTION = 0x402D
};
enum { WIN_STATE_HILITED = 0x02 };
enum { GWS_PUSH_BUTTON = 0x01, GWS_SCROLL_LISTBOX = 0x20, GWS_MOUSE_TRACK = 0x400 };
enum { KEY_TAB = 0x0F };
enum { KEY_STATE_DOWN = 0x02, KEY_STATE_LSHIFT = 0x10 };

#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

class GameFont;
class GameWindow;
class BfmeKeyLC;

#include "../../../../Include/GameClient/ImageClass.h"

#include "../../../../Include/GameClient/Bfme2GameWindow.h"


struct ImageComboBoxData
{
	Int maxListHeight;
	GameWindow *dropDownButton;
	GameWindow *listBox;
	Int m_field0C;
};

struct ListboxData
{
	short listLength;
	unsigned char m_pad02[0x0E - 0x02];
	Bool m_flag0E;
	unsigned char m_pad0F[0x12 - 0x0F];
	Bool m_flag12;
	Bool m_flag13;
	unsigned char m_pad14[0x1C - 0x14];
	GameWindow *upButton;
	GameWindow *downButton;
	GameWindow *slider;
	Int totalHeight;
	short insertPos;
	unsigned char m_pad2E[0x30 - 0x2E];
	Int m_field30;
	Int selectPos;
};




#include "../../../../Include/Common/GameAudio.h"
#include "../../../../Include/Common/MiscAudioClass.h"
#include "../../../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;

extern AudioManager *TheAudio;

class Keyboard
{
public:
	__declspec(dllimport) __forceinline Int getModifierFlags() { return m_modifiers; }

	unsigned char m_pad00[0xC];
	Int m_modifiers;
};

extern Keyboard *TheKeyboard;

// The one-pointer combo wrapper of MpGameSetupSlots.cpp; its 0x00323736 is
// the drop-down toggle (BFME1 Rva004B5C90::invoke), pinned there by address.
class MpGameSetupComboRef
{
public:
	MpGameSetupComboRef();
	MpGameSetupComboRef(const MpGameSetupComboRef &other);
	~MpGameSetupComboRef();
	void rva00323736(bool flag);

	GameWindow *m_window;
};

// The lobby panel constructor 0x00441ECE builds its +0x2F4 color combo array
// through this null-pointer default constructor; retail folds the complete
// body with the other one-word null initializers at 0x00326BE6.
MpGameSetupComboRef::MpGameSetupComboRef()
	: m_window(0)
{
}

// The lobby copies this one-pointer view and destroys the copy. Retail folds
// these complete bodies at 0x0027EA56 and 0x000B3FD0 respectively.
MpGameSetupComboRef::MpGameSetupComboRef(const MpGameSetupComboRef &other)
	: m_window(other.m_window)
{
}

MpGameSetupComboRef::~MpGameSetupComboRef()
{
}

void Rva003248F5Show(GameWindow *listBox, bool hide);

inline __declspec(noinline) void MpGameSetupComboRef::rva00323736(bool hide)
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
		if (TheWindowManager->slot53() == current)
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

void GadgetListBoxSetListLength(GameWindow *listbox, Int newLen);
Int GadgetListBoxAddEntryImage(GameWindow *listbox, const Image *image,
	Int row, Int column, Int hieght, Int width, Bool overwrite, Int color);

// One-pointer views of the combo window for its list operations. 0x003235B8
// (BFME1 Rva004B5AA0::m) adds an image entry, growing the list when full; the
// others are rowed by address elsewhere.
class Rva003235B8
{
public:
	Int rva003235B8(const Image *image, Int height, Int width, Int color);

	GameWindow *m_window;
};

inline __declspec(noinline) Int Rva003235B8::rva003235B8(const Image *image, Int height, Int width, Int color)
{
	if (!m_window)
		return -1;
	GameWindow *listBox = ((ImageComboBoxData *)m_window->winGetUserData())->listBox;
	ListboxData *listData = (ListboxData *)((ImageComboBoxData *)m_window->winGetUserData())->listBox->winGetUserData();
	if (listData->insertPos >= listData->listLength)
		GadgetListBoxSetListLength(listBox, 2 * listData->listLength);
	return GadgetListBoxAddEntryImage(listBox, image, -1, 0, width, height, true, color);
}

// The combo wrappers' remaining methods (rows 0x00323642, 0x00323657,
// 0x00323674, 0x003236A0 and 0x003236C4, each rowed in its own unit) are
// repeated here with their row bodies, inline and never inlined, like the
// two defined above. Retail's compiler knew none of them keeps the address of
// `combo`, so the GGM_SET_LABEL argument temporary's esp save shares combo's
// dead home [ebp+8]; with opaque callees it moved to [ebp+0xC].
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
void GadgetListBoxGetSelected(GameWindow *win, int *sel);
void GadgetListBoxReset(GameWindow *listbox);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, int row, int column);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);
struct Rva00323657ListData
{
	char m_pad[0x34];
	void *m_34;
};
class Rva00323619
{
public:
	__declspec(noinline) void rva00323642()
	{
		GameWindow *w = m_window;
		if (w == 0)
			return;
		void *userData = w->winGetUserData();
		GadgetListBoxReset(*(GameWindow **)((char *)userData + 8));
	}
private:
	GameWindow *m_window;
};
class BfmeThing925D
{
public:
	__declspec(noinline) void bfmeGo925D(void *v)
	{
		GameWindow *w = m_window;
		if (w)
		{
			GameWindow *listBox = ((ImageComboBoxData *)w->winGetUserData())->listBox;
			((Rva00323657ListData *)listBox->winGetUserData())->m_34 = v;
		}
	}
private:
	GameWindow *m_window;
};
class Rva00323674
{
public:
	__declspec(noinline) int rva00323674() const
	{
		GameWindow *win = m_window;
		if (win == 0)
			return -1;
		int sel = -1;
		GameWindow *listWin = ((ImageComboBoxData *)win->winGetUserData())->listBox;
		_ReadWriteBarrier();
		GadgetListBoxGetSelected(listWin, &sel);
		return sel;
	}
private:
	GameWindow *m_window;
};
class Rva003236A0
{
public:
	__declspec(noinline) void rva003236A0(int a, int b)
	{
		if (m_window == 0)
			return;
		GameWindow *listBox = ((ImageComboBoxData *)m_window->winGetUserData())->listBox;
		_ReadWriteBarrier();
		GadgetListBoxSetItemData(listBox, (void *)b, a, 0);
	}
private:
	GameWindow *m_window;
};
class Rva003236C4
{
public:
	__declspec(noinline) int rva003236C4(int a)
	{
		if (m_window == 0)
			return 0;
		GameWindow *listBox = ((ImageComboBoxData *)m_window->winGetUserData())->listBox;
		return (int)GadgetListBoxGetItemData(listBox, a, 0);
	}
private:
	GameWindow *m_window;
};
// 0x003140CF, the owner setter (null means the window itself).
class Rva003140CF { public: int rva003140CF(int v); };

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
				if (TheKeyboard->m_modifiers & KEY_STATE_LSHIFT)
					TheWindowManager->winPrevTab(window);
				else
					TheWindowManager->winNextTab(window);
			}
			break;

		case GWM_LEFT_UP:
		{
			if (TheAudio)
			{
				BfmeAudioEventPrefix136 buttonClick(TheAudio->getMiscAudio()->m_C0, 2);
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
			if (TheWindowManager->slot53() == window)
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

// ?GadgetImageComboBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// @0x00323A5B 811B: the image combo box system callback (Open-BFME-1
// GadgetImageComboBox.cpp GadgetImageComboBoxSystem, the combo box system
// message handler with the drop-down list in the user data). `combo` is the
// one-pointer wrapper whose methods the cases call; see the note above the
// wrapper classes for why their bodies are visible here.
WindowMsgHandledType GadgetImageComboBoxSystem(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	const UnsignedInt message = msg;
	GameWindow *combo = window;
	WinInstanceData *instData = window->winGetInstanceData();
	ImageComboBoxData *comboData = (ImageComboBoxData *)window->winGetUserData();

	switch (message)
	{
		case GWM_CREATE:
		{
			ImageComboBoxData *created = new ImageComboBoxData;
			memset(created, 0, sizeof(*created));
			window->winSetUserData(created);
			((Rva003140CF *)window)->rva003140CF((int)window->winGetParent());
			break;
		}

		case GWM_DESTROY:
			TheWindowManager->winSetLoneWindow(NULL);
			if (comboData)
			{
				delete comboData;
				window->winSetUserData(NULL);
			}
			break;

		case GWM_INPUT_FOCUS:
			if (mData1 == 0)
				instData->m_state &= ~WIN_STATE_HILITED;
			else
				instData->m_state |= WIN_STATE_HILITED;
			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GGM_FOCUS_CHANGE, mData1, window->winGetWindowId());
			*(Bool *)mData2 = true;
			break;

		case GGM_LEFT_DRAG:
			break;

		case GGM_SET_LABEL:
		{
			instData->setText(*(UnicodeString *)mData1);
			break;
		}

		case GGM_RESIZED:
		{
			GameWindow *listBox = ((ImageComboBoxData *)window->winGetUserData())->listBox;
			if (listBox && listBox->winIsHidden())
			{
				listBox->winSetSize(mData1, mData2);
				GameWindow *button = comboData->dropDownButton;
				ICoord2D size;
				const Image *image = button->m_instData.m_enabledDrawData[0].image;
				if (image)
				{
					size.x = image->getImageWidth();
					size.y = image->getImageHeight();
					float scale = (float)(Int)mData2 / size.y;
					size.x = (Int)(size.x * scale);
					size.y = (Int)(size.y * scale);
				}
				button->winSetPosition(mData1 - size.x, 0);
				comboData->dropDownButton->winSetSize(size.x, size.y);
			}
			break;
		}

		case GGM_CLOSE:
			if (!((ImageComboBoxData *)window->winGetUserData())->listBox->winIsHidden())
				((MpGameSetupComboRef *)&combo)->rva00323736(true);
			break;

		case GBM_SELECTED:
			if ((GameWindow *)mData1 == comboData->dropDownButton)
			{
				if (TheAudio)
				{
					BfmeAudioEventPrefix136 buttonClick(TheAudio->getMiscAudio()->m_C0, 2);
					TheAudio->addAudioEvent(&buttonClick);
				}
				((MpGameSetupComboRef *)&combo)->rva00323736(!((ImageComboBoxData *)window->winGetUserData())->listBox->winIsHidden());
			}
			break;

		case GCM_SET_SELECTION:
			((BfmeThing925D *)&combo)->bfmeGo925D((void *)mData2);
			break;

		case GCM_GET_SELECTION:
			*(Int *)mData2 = ((Rva00323674 *)&combo)->rva00323674();
			break;

		case GCM_SET_ITEM_DATA:
			((Rva003236A0 *)&combo)->rva003236A0((int)mData1, (int)mData2);
			break;

		case GCM_GET_ITEM_DATA:
			*(Int *)mData2 = ((Rva003236C4 *)&combo)->rva003236C4((int)mData1);
			// fall through

		case GCM_SELECTED:
			((MpGameSetupComboRef *)&combo)->rva00323736(true);
			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GCM_UPDATE_TEXT, (WindowMsgData)window, 0);
			break;

		case GCM_RESET:
			((Rva00323619 *)&combo)->rva00323642();
			break;

		case GCM_DEL_ALL:
			break;

		case GCM_ADD_ENTRY:
			return (WindowMsgHandledType)((Rva003235B8 *)&combo)->rva003235B8(
				(const Image *)mData1, (Int)mData2, -1, -1);

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
