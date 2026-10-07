// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?GadgetTextEntryInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// @0x00320DA9 1607B (Ghidra boundary): the text entry input callback, slot
// 0x84 of the input table 0x9BCAD8. Reference semantics: the ZH/Open-BFME-1
// GadgetTextEntry.cpp GadgetTextEntryInput (IME guard, GWM_IME_CHAR,
// GWM_CHAR key filtering and tabbing, mouse tracking messages). BFME2 edits
// at a cursor: characters go through GadgetTextEntryInsertCharacter
// 0x00320C6F, deletions through the composition update 0x00320B3C (its
// result decides GEM_UPDATE_TEXT), and the cursor moves through
// GadgetTextEntrySetCursorPosition 0x00320737. Target facts beyond the donor:
// the IME guard skips GWM_LEFT_UP; a left click places the cursor at the
// character under the mouse (screen x less the window x plus the width of
// the first drawn character at +0x24, measured on the secret string when the
// +0x12 flag is set), resets a pending IME composition (the short at +0x20)
// through IMEManager disable/enable, and calls GameWindowManager slot 61 with
// the window; GWM_LEFT_UP calls slot 62 when slot 63 returns the window, and
// GWM_MOUSE_POS (24) drags the cursor only then. Ctrl+Left/Right jump words;
// Home, End, Left, Right move the cursor and, without shift, collapse the
// selection anchor (+0x1E); Backspace and Delete widen an empty selection by
// one character first; Tab with shift tabs backwards. Mouse entering and
// leaving pass 0x2C and 2 to the click-through handler's setter 0x00432AEB
// and set and clear the +0x14 byte the system callback tests on destroy.
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

enum
{
	GWM_LEFT_DOWN = 5,
	GWM_LEFT_UP = 6,
	GWM_LEFT_DRAG = 8,
	GWM_MOUSE_ENTERING = 17,
	GWM_MOUSE_LEAVING = 18,
	GWM_CHAR = 21,
	GWM_MOUSE_POS = 24,
	GWM_IME_CHAR = 25
};

enum
{
	GGM_LEFT_DRAG = 0x4000,
	GBM_MOUSE_ENTERING = 0x4006,
	GBM_MOUSE_LEAVING = 0x4007,
	GEM_EDIT_DONE = 0x4031,
	GEM_UPDATE_TEXT = 0x4032
};

enum
{
	KEY_ESC = 0x01,
	KEY_BACKSPACE = 0x0E,
	KEY_TAB = 0x0F,
	KEY_ENTER = 0x1C,
	KEY_CAPS = 0x3A,
	KEY_F1 = 0x3B,
	KEY_F2 = 0x3C,
	KEY_F3 = 0x3D,
	KEY_F4 = 0x3E,
	KEY_F5 = 0x3F,
	KEY_F6 = 0x40,
	KEY_F7 = 0x41,
	KEY_F8 = 0x42,
	KEY_F9 = 0x43,
	KEY_F10 = 0x44,
	KEY_F11 = 0x57,
	KEY_F12 = 0x58,
	KEY_KPENTER = 0x9C,
	KEY_HOME = 0xC7,
	KEY_PGUP = 0xC9,
	KEY_LEFT = 0xCB,
	KEY_RIGHT = 0xCD,
	KEY_END = 0xCF,
	KEY_PGDN = 0xD1,
	KEY_DEL = 0xD3
};

enum
{
	KEY_STATE_DOWN = 0x0002,
	KEY_STATE_CONTROL = 0x000C,
	KEY_STATE_SHIFT = 0x0430,
	KEY_STATE_ALT = 0x00C0
};

enum
{
	WIN_STATE_HILITED = 0x02
};

enum
{
	GWS_MOUSE_TRACK = 0x00000400,
	GWS_COMBO_BOX = 0x00008000
};

#define BitTest(x, i) (((x) & (i)) != 0)
#define BitSet(x, i) ((x) |= (i))
#define BitClear(x, i) ((x) &= ~(i))

#ifndef NULL
#define NULL 0
#endif

class WinInstanceData
{
public:
	UnsignedInt getStyle() const { return m_style; }
	void *m_vtable;
	Int m_id;
	UnsignedInt m_state;
	UnsignedInt m_style;
};

class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	GameWindow *winGetParent();
	UnsignedInt winGetStyle();
	GameWindow *winGetOwner();
	WinInstanceData *winGetInstanceData();
	void *winGetUserData();
};

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText();
	virtual Int getTextLength();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual Int getWidth(Int charPos);
};

class IMEManager
{
public:
#define V(n) virtual void slot##n() = 0;
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07)
	V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15)
	virtual void enable() = 0;
	virtual void disable() = 0;
	V(18)
	virtual Bool isAttachedTo(GameWindow *window) = 0;
	V(20)
	virtual Bool isComposing() = 0;
#undef V
};

class GameWindowManager
{
public:
#define V(n) virtual void slot##n() = 0;
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07)
	V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41)
	virtual void winNextTab(GameWindow *window) = 0;
	virtual void winPrevTab(GameWindow *window) = 0;
	V(44) V(45) V(46) V(47) V(48)
	virtual Int winSetFocus(GameWindow *window) = 0;
	V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window,
		UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
	V(59) V(60)
	virtual void slot61SetCapture(GameWindow *window) = 0;
	virtual void slot62ReleaseCapture(GameWindow *window) = 0;
	virtual GameWindow *slot63GetCapture() = 0;
#undef V
};

// Native calls at the documented setter sites target the already rowed
// Rva00432AEB provider (same thiscall int(int) ABI); use its linker identity.
class Rva00432AEB
{
public:
	Int rva00432AEB(Int value);
};

struct EntryData
{
	DisplayString *text;
	DisplayString *sText;
	DisplayString *constructText;
	UnsignedInt validation;
	short maxTextLen;
	Bool secretText;
	Bool drawTextFromStart;
	Bool systemFlag;
	unsigned char m_pad15[0x1C - 0x15];
	UnsignedShort charPos;
	UnsignedShort conCharPos;
	UnsignedShort unknown20;
	unsigned char m_pad22[0x24 - 0x22];
	UnsignedInt drawStart;
};

extern GameWindowManager *TheWindowManager;
extern IMEManager *TheIMEManager;
extern int g_Va00E032C8;

void GadgetTextEntrySetCursorPosition(GameWindow *window, UnsignedInt position);
bool GadgetTextEntryUpdateComposition(GameWindow *window);
bool GadgetTextEntryInsertCharacter(GameWindow *window, UnsignedInt character);

WindowMsgHandledType GadgetTextEntryInput(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	EntryData *e = (EntryData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();

	if (msg != GWM_LEFT_UP && TheIMEManager && TheIMEManager->isAttachedTo(window) &&
		TheIMEManager->isComposing())
	{
		// ignore input while IME has focus
		return MSG_HANDLED;
	}

	switch (msg)
	{
		case GWM_MOUSE_ENTERING:
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
			{
				BitSet(instData->m_state, WIN_STATE_HILITED);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GBM_MOUSE_ENTERING, (WindowMsgData)window, 0);
			}
			((Rva00432AEB *)g_Va00E032C8)->rva00432AEB(0x2C);
			if (e)
				e->systemFlag = true;
			break;

		case GWM_LEFT_DRAG:
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GGM_LEFT_DRAG, (WindowMsgData)window, 0);
			break;

		case GWM_LEFT_UP:
			if (TheWindowManager->slot63GetCapture() == window)
				TheWindowManager->slot62ReleaseCapture(window);
			break;

		case GWM_LEFT_DOWN:
		{
			TheWindowManager->winSetFocus(window);
			if (e->unknown20 && TheIMEManager)
			{
				TheIMEManager->disable();
				TheIMEManager->enable();
			}

			Int x, y, width, height;
			window->winGetScreenPosition(&x, &y);
			window->winGetSize(&width, &height);
			Int clickX = (mData1 & 0xFFFF) - x;
			DisplayString *ds = e->text;
			if (e->secretText)
				ds = e->sText;
			clickX += e->text->getWidth(e->drawStart);
			Int pos = ds->getTextLength();
			while (pos > 0 && clickX < ds->getWidth(pos))
				pos--;
			e->conCharPos = pos;
			GadgetTextEntrySetCursorPosition(window, pos);
			TheWindowManager->slot61SetCapture(window);
			break;
		}

		case GWM_MOUSE_LEAVING:
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
			{
				BitClear(instData->m_state, WIN_STATE_HILITED);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GBM_MOUSE_LEAVING, (WindowMsgData)window, 0);
			}
			((Rva00432AEB *)g_Va00E032C8)->rva00432AEB(2);
			if (e)
				e->systemFlag = false;
			break;

		case GWM_IME_CHAR:
		{
			WideChar ch = (WideChar)mData1;
			if (ch == '\r')
			{
				// Done with this edit
				e->drawTextFromStart = false;
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GEM_EDIT_DONE, (WindowMsgData)window, 0);
			}
			else if (ch)
			{
				if (GadgetTextEntryInsertCharacter(window, mData1))
					TheWindowManager->winSendSystemMsg(window->winGetOwner(),
						GEM_UPDATE_TEXT, (WindowMsgData)window, 0);
			}
			break;
		}

		case GWM_MOUSE_POS:
		{
			if (TheWindowManager->slot63GetCapture() != window)
				return MSG_IGNORED;

			Int x, y, width, height;
			window->winGetScreenPosition(&x, &y);
			window->winGetSize(&width, &height);
			Int clickX = (mData1 & 0xFFFF) - x;
			DisplayString *ds = e->text;
			if (e->secretText)
				ds = e->sText;
			clickX += e->text->getWidth(e->drawStart);
			Int pos = ds->getTextLength();
			while (pos > 0 && clickX < ds->getWidth(pos))
				pos--;
			GadgetTextEntrySetCursorPosition(window, pos);
			break;
		}

		case GWM_CHAR:
			if (BitTest(mData2, KEY_STATE_DOWN) &&
				BitTest(mData2, KEY_STATE_ALT | KEY_STATE_CONTROL))
			{
				WindowMsgHandledType handled = MSG_IGNORED;
				if (BitTest(mData2, KEY_STATE_CONTROL))
				{
					handled = MSG_HANDLED;
					switch (mData1)
					{
						case KEY_RIGHT:
							if (e->unknown20 == 0)
							{
								// jump to the start of the next word
								if (e->charPos < e->text->getTextLength())
								{
									Int len = e->text->getTextLength();
									const WideChar *str = e->text->getText().str();
									Int pos = e->charPos;
									while (pos < len && str[pos] == ' ')
										pos++;
									while (pos < len && str[pos] != ' ')
										pos++;
									while (pos < len && str[pos] == ' ')
										pos++;
									GadgetTextEntrySetCursorPosition(window, pos);
								}
								if (!BitTest(mData2, KEY_STATE_SHIFT))
									e->conCharPos = e->charPos;
							}
							break;

						case KEY_LEFT:
							if (e->unknown20 == 0)
							{
								// jump to the start of this or the previous word
								if (e->charPos > 0)
								{
									const WideChar *str = e->text->getText().str();
									Int pos = e->charPos;
									while (pos > 0 && str[pos - 1] == ' ')
										pos--;
									while (pos > 0 && str[pos - 1] != ' ')
										pos--;
									GadgetTextEntrySetCursorPosition(window, pos);
								}
								if (!BitTest(mData2, KEY_STATE_SHIFT))
									e->conCharPos = e->charPos;
							}
							break;

						default:
							handled = MSG_IGNORED;
							break;
					}
				}
				return handled;
			}

			switch (mData1)
			{
				// Don't process these keys
				case KEY_ESC:
				case KEY_PGUP:
				case KEY_PGDN:
				case KEY_F1:
				case KEY_F2:
				case KEY_F3:
				case KEY_F4:
				case KEY_F5:
				case KEY_F6:
				case KEY_F7:
				case KEY_F8:
				case KEY_F9:
				case KEY_F10:
				case KEY_F11:
				case KEY_F12:
				case KEY_CAPS:
					return MSG_IGNORED;

				case KEY_ENTER:
				case KEY_KPENTER:
					if (BitTest(mData2, KEY_STATE_CONTROL))
						return MSG_IGNORED;
					break;

				case KEY_TAB:
					if (BitTest(mData2, KEY_STATE_DOWN))
					{
						GameWindow *parent = window->winGetParent();
						if (BitTest(mData2, KEY_STATE_SHIFT))
						{
							if (parent && !BitTest(parent->winGetStyle(), GWS_COMBO_BOX))
								parent = NULL;
							if (parent)
								TheWindowManager->winPrevTab(parent);
							else
								TheWindowManager->winPrevTab(window);
						}
						else
						{
							if (parent && !BitTest(parent->winGetStyle(), GWS_COMBO_BOX))
								parent = NULL;
							if (parent)
								TheWindowManager->winNextTab(parent);
							else
								TheWindowManager->winNextTab(window);
						}
					}
					break;

				case KEY_DEL:
					if (BitTest(mData2, KEY_STATE_DOWN) && e->unknown20 == 0)
					{
						// an empty selection deletes the character after the cursor
						if (e->conCharPos == e->charPos)
							e->conCharPos = e->charPos + 1;
						if (GadgetTextEntryUpdateComposition(window))
							TheWindowManager->winSendSystemMsg(window->winGetOwner(),
								GEM_UPDATE_TEXT, (WindowMsgData)window, 0);
					}
					break;

				case KEY_BACKSPACE:
					if (BitTest(mData2, KEY_STATE_DOWN) && e->unknown20 == 0)
					{
						// an empty selection deletes the character before the cursor
						if (e->conCharPos > 0 && e->conCharPos == e->charPos)
							e->conCharPos = e->charPos - 1;
						if (GadgetTextEntryUpdateComposition(window))
							TheWindowManager->winSendSystemMsg(window->winGetOwner(),
								GEM_UPDATE_TEXT, (WindowMsgData)window, 0);
					}
					break;

				case KEY_HOME:
					if (e->unknown20 == 0)
					{
						if (BitTest(mData2, KEY_STATE_DOWN))
							GadgetTextEntrySetCursorPosition(window, 0);
						if (!BitTest(mData2, KEY_STATE_SHIFT))
							e->conCharPos = e->charPos;
					}
					break;

				case KEY_END:
					if (e->unknown20 == 0)
					{
						if (BitTest(mData2, KEY_STATE_DOWN))
							GadgetTextEntrySetCursorPosition(window, e->text->getTextLength());
						if (!BitTest(mData2, KEY_STATE_SHIFT))
							e->conCharPos = e->charPos;
					}
					break;

				case KEY_RIGHT:
					if (BitTest(mData2, KEY_STATE_DOWN) && e->unknown20 == 0)
					{
						if (e->charPos < e->text->getTextLength())
							GadgetTextEntrySetCursorPosition(window, e->charPos + 1);
						if (!BitTest(mData2, KEY_STATE_SHIFT))
							e->conCharPos = e->charPos;
					}
					break;

				case KEY_LEFT:
					if (BitTest(mData2, KEY_STATE_DOWN) && e->unknown20 == 0)
					{
						if (e->charPos > 0)
							GadgetTextEntrySetCursorPosition(window, e->charPos - 1);
						if (!BitTest(mData2, KEY_STATE_SHIFT))
							e->conCharPos = e->charPos;
					}
					break;
			}
			break;

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
