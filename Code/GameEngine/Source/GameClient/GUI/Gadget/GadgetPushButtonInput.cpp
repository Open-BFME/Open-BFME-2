// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /DNDEBUG /MD /EHsc
// ?GadgetPushButtonInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// @0x00327E5D 1243B (Ghidra boundary, EH frame): the push button input
// callback. Reference semantics: Open-BFME-1 GadgetPushButtonInput.cpp, the
// Zero Hour GadgetPushButton.cpp body plus the auto-repeat tick (GWM_TICK 24)
// and Shift-Tab. Target facts: instance state +8, style +0xC, owner +0x14;
// status bits 0x20000 (right click) and 0x80000 (check like) through
// winGetStatus; the click is a 0x88-byte audio event built from an empty
// sound reference, given priority 2 by the setter 0x002D94CE and the button's
// own sound reference (user data +0x1C) by 0x002D9C2F when one is set, then
// handed to TheAudio slot 25; buttonTriggersOnMouseDown is 0x00327C39; the
// repeat delay is user data +0x24 and the last repeat time a file static
// (0x00E01D4C) read against timeGetTime; manager slots 42/43 (tab) and 58.
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
	GWM_RIGHT_DOWN = 13,
	GWM_RIGHT_UP = 14,
	GWM_MOUSE_ENTERING = 17,
	GWM_MOUSE_LEAVING = 18,
	GWM_CHAR = 21,
	GWM_TICK = 24
};

enum
{
	GGM_LEFT_DRAG = 0x4000,
	GBM_MOUSE_ENTERING = 0x4006,
	GBM_MOUSE_LEAVING = 0x4007,
	GBM_SELECTED = 0x4008,
	GBM_SELECTED_RIGHT = 0x4009
};

enum { WIN_STATE_HILITED = 0x02, WIN_STATE_SELECTED = 0x04 };
enum { GWS_HORZ_SLIDER = 0x10, GWS_MOUSE_TRACK = 0x400 };
enum { WIN_STATUS_RIGHT_CLICK = 0x20000, WIN_STATUS_CHECK_LIKE = 0x80000 };
enum { KEY_TAB = 0x0F, KEY_ENTER = 0x1C, KEY_SPACE = 0x39 };
enum { KEY_STATE_UP = 0x01, KEY_STATE_DOWN = 0x02, KEY_STATE_LSHIFT = 0x10 };

#define BitTest(x, i) (((x) & (i)) != 0)
#define BitSet(x, i) ((x) |= (i))
#define BitClear(x, i) ((x) &= ~(i))

#ifndef NULL
#define NULL 0
#endif

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class GameWindow;

class WinInstanceData
{
public:
	UnsignedInt getStyle() { return m_style; }
	UnsignedInt getState() { return m_state; }
	GameWindow *getOwner() { return m_owner; }

	void *m_vtable;
	Int m_id;
	UnsignedInt m_state;
	UnsignedInt m_style;
	UnsignedInt m_status;
	GameWindow *m_owner;
};

class GameWindow
{
public:
	WinInstanceData *winGetInstanceData();
	void *winGetUserData();
	GameWindow *winGetParent();
	UnsignedInt winGetStyle();
	UnsignedInt winGetStatus();
};

struct PushButtonInputData
{
	unsigned char m_pad00[0x1C];
	OpaqueRefElement4 m_sound;
	Int m_field20;
	Int m_repeatDelay;
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
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window,
		UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
};

extern GameWindowManager *TheWindowManager;

class AudioManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24)
#undef V
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *evt) = 0;
};

extern AudioManager *TheAudio;

class Keyboard
{
public:
	unsigned char m_pad00[0xC];
	UnsignedInt m_modifiers;
};

extern Keyboard *TheKeyboard;

// Event field setters rowed by address: 0x002D94CE stores the dword at +0x30
// when it changes, 0x002D9C2F assigns the sound reference at +8.
class Rva002D94CE { public: void rva002D94CE(int value); };
class Rva002D9C2F { public: OpaqueRefElement4 &rva002D9C2F(const OpaqueRefElement4 &other); };

Bool Rva00327C39Get(GameWindow *window);

static UnsignedInt lastRepeatTime;

WindowMsgHandledType GadgetPushButtonInput(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	WinInstanceData *instData = window->winGetInstanceData();

	switch (msg)
	{
		case GWM_TICK:
		{
			if (BitTest(instData->m_state, WIN_STATE_SELECTED) && Rva00327C39Get(window))
			{
				PushButtonInputData *pData = (PushButtonInputData *)window->winGetUserData();
				if (pData->m_repeatDelay)
				{
					UnsignedInt now = timeGetTime();
					if (now > lastRepeatTime && now - lastRepeatTime > (UnsignedInt)pData->m_repeatDelay)
					{
						TheWindowManager->winSendSystemMsg(instData->getOwner(), GBM_SELECTED,
							(WindowMsgData)window, 0);
						lastRepeatTime = now;
					}
				}
			}
			return MSG_IGNORED;
		}

		case GWM_MOUSE_ENTERING:
		{
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
			{
				BitSet(instData->m_state, WIN_STATE_HILITED);
				TheWindowManager->winSendSystemMsg(instData->getOwner(), GBM_MOUSE_ENTERING,
					(WindowMsgData)window, mData1);
			}
			if (window->winGetParent() && BitTest(window->winGetParent()->winGetStyle(), GWS_HORZ_SLIDER))
			{
				WinInstanceData *instDataParent = window->winGetParent()->winGetInstanceData();
				BitSet(instDataParent->m_state, WIN_STATE_HILITED);
			}
			break;
		}

		case GWM_MOUSE_LEAVING:
		{
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
			{
				BitClear(instData->m_state, WIN_STATE_HILITED);
				TheWindowManager->winSendSystemMsg(instData->getOwner(), GBM_MOUSE_LEAVING,
					(WindowMsgData)window, mData1);
			}
			if (BitTest(window->winGetStatus(), WIN_STATUS_CHECK_LIKE) == false)
				if (BitTest(instData->getState(), WIN_STATE_SELECTED))
					BitClear(instData->m_state, WIN_STATE_SELECTED);
			if (window->winGetParent() && BitTest(window->winGetParent()->winGetStyle(), GWS_HORZ_SLIDER))
			{
				WinInstanceData *instDataParent = window->winGetParent()->winGetInstanceData();
				BitClear(instDataParent->m_state, WIN_STATE_HILITED);
			}
			break;
		}

		case GWM_LEFT_DRAG:
			TheWindowManager->winSendSystemMsg(instData->getOwner(), GGM_LEFT_DRAG,
				(WindowMsgData)window, mData1);
			break;

		case GWM_LEFT_DOWN:
		{
			PushButtonInputData *pData = (PushButtonInputData *)window->winGetUserData();
			BfmeAudioEventPrefix136 buttonClick((const OpaqueRefElement4 &)BfmePoolRef08(), 0);
			((Rva002D94CE *)&buttonClick)->rva002D94CE(2);
			if (pData && pData->m_sound.referent)
				((Rva002D9C2F *)&buttonClick)->rva002D9C2F(pData->m_sound);

			if (TheAudio)
				TheAudio->addAudioEvent(&buttonClick);

			if (BitTest(window->winGetStatus(), WIN_STATUS_CHECK_LIKE))
			{
				if (BitTest(instData->m_state, WIN_STATE_SELECTED))
					BitClear(instData->m_state, WIN_STATE_SELECTED);
				else
					BitSet(instData->m_state, WIN_STATE_SELECTED);
			}
			else
				BitSet(instData->m_state, WIN_STATE_SELECTED);

			if (Rva00327C39Get(window))
			{
				TheWindowManager->winSendSystemMsg(instData->getOwner(), GBM_SELECTED,
					(WindowMsgData)window, mData1);
				lastRepeatTime = timeGetTime() + pData->m_repeatDelay * 2;
			}
			break;
		}

		case GWM_LEFT_UP:
			if (BitTest(instData->getState(), WIN_STATE_SELECTED) &&
				BitTest(window->winGetStatus(), WIN_STATUS_CHECK_LIKE) == false)
			{
				if (!Rva00327C39Get(window))
					TheWindowManager->winSendSystemMsg(instData->getOwner(), GBM_SELECTED,
						(WindowMsgData)window, mData1);
				BitClear(instData->m_state, WIN_STATE_SELECTED);
			}
			else
				return MSG_IGNORED;
			break;

		case GWM_RIGHT_DOWN:
		{
			PushButtonInputData *pData = (PushButtonInputData *)window->winGetUserData();
			BfmeAudioEventPrefix136 buttonClick((const OpaqueRefElement4 &)BfmePoolRef08(), 0);
			((Rva002D94CE *)&buttonClick)->rva002D94CE(2);
			if (pData && pData->m_sound.referent)
				((Rva002D9C2F *)&buttonClick)->rva002D9C2F(pData->m_sound);

			if (BitTest(window->winGetStatus(), WIN_STATUS_RIGHT_CLICK))
			{
				if (TheAudio)
					TheAudio->addAudioEvent(&buttonClick);

				if (BitTest(window->winGetStatus(), WIN_STATUS_CHECK_LIKE))
				{
					if (BitTest(instData->m_state, WIN_STATE_SELECTED))
						BitClear(instData->m_state, WIN_STATE_SELECTED);
					else
						BitSet(instData->m_state, WIN_STATE_SELECTED);
				}
				else
					BitSet(instData->m_state, WIN_STATE_SELECTED);

				if (Rva00327C39Get(window))
				{
					TheWindowManager->winSendSystemMsg(instData->getOwner(), GBM_SELECTED_RIGHT,
						(WindowMsgData)window, mData1);
					lastRepeatTime = timeGetTime() + pData->m_repeatDelay * 2;
				}
			}
			else
				return MSG_IGNORED;
			break;
		}

		case GWM_RIGHT_UP:
			if (BitTest(window->winGetStatus(), WIN_STATUS_RIGHT_CLICK))
			{
				if (BitTest(instData->getState(), WIN_STATE_SELECTED) &&
					BitTest(window->winGetStatus(), WIN_STATUS_CHECK_LIKE) == false)
				{
					if (!Rva00327C39Get(window))
						TheWindowManager->winSendSystemMsg(instData->getOwner(), GBM_SELECTED_RIGHT,
							(WindowMsgData)window, mData1);
					BitClear(instData->m_state, WIN_STATE_SELECTED);
				}
				else
					return MSG_IGNORED;
			}
			else
				return MSG_IGNORED;
			break;

		case GWM_CHAR:
			switch (mData1)
			{
				case KEY_ENTER:
				case KEY_SPACE:
					if (BitTest(mData2, KEY_STATE_UP))
					{
						if (BitTest(instData->getState(), WIN_STATE_SELECTED) &&
							BitTest(window->winGetStatus(), WIN_STATUS_CHECK_LIKE) == false)
						{
							TheWindowManager->winSendSystemMsg(instData->getOwner(), GBM_SELECTED,
								(WindowMsgData)window, 0);
							BitClear(instData->m_state, WIN_STATE_SELECTED);
						}
					}
					else
					{
						if (BitTest(window->winGetStatus(), WIN_STATUS_CHECK_LIKE))
						{
							if (BitTest(instData->m_state, WIN_STATE_SELECTED))
								BitClear(instData->m_state, WIN_STATE_SELECTED);
							else
								BitSet(instData->m_state, WIN_STATE_SELECTED);
							TheWindowManager->winSendSystemMsg(instData->getOwner(), GBM_SELECTED,
								(WindowMsgData)window, mData1);
						}
						else
							BitSet(instData->m_state, WIN_STATE_SELECTED);
					}
					break;

				case KEY_TAB:
					if (BitTest(mData2, KEY_STATE_DOWN))
					{
						if (BitTest(TheKeyboard->m_modifiers, KEY_STATE_LSHIFT))
							TheWindowManager->winPrevTab(window);
						else
							TheWindowManager->winNextTab(window);
					}
					break;

				default:
					return MSG_IGNORED;
			}
			break;

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
