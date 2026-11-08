// cl: /DNDEBUG /MD /EHs-c-
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/MessageStream/WindowXlat.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// rawMouseToWindowMessage 0x0040FE7A (152B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME5: WindowXlat.cpp's rawMouseToWindowMessage, retail 0x005B9B94,
// zh_sweep packet 005b9b94.
//
// The reference body ports unchanged. What had to be established is that both
// enums it switches between survived into BFME with Zero Hour's numbering, and
// the retail jump table says they did. It covers 3..19 with three holes -- 7, 9
// and 17 -- and those are exactly MSG_RAW_MOUSE_LEFT_CLICK, the unused slot
// between the left and middle groups, and MSG_RAW_MOUSE_RIGHT_CLICK, none of
// which this switch handles. The message numbering is confirmed independently
// by message_stream_commandName.cpp, which names 3 through 19 the same way.
//
// The values the arms return pin the other enum: 24 for a mouse position, 5/6/8
// for the left group, 9/10/12 for the middle, 13/14/16 for the right, and
// 19/20 for the wheel. That is Zero Hour's GameWindowMessage exactly, counting
// GWM_NONE = 0 through GWM_MOUSE_POS = 24.
//
// Its own TU because BFME has no WindowXlat.cpp yet.

typedef int Int;

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

union GameMessageArgumentType
{
	Int integer;
	void *pointer;
	ICoord2D pixel;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
#include "../../../Include/Common/MessageStream.h"

enum GameWindowMessage
{
	GWM_NONE = 0,

	GWM_CREATE,									GWM_DESTROY,
	GWM_ACTIVATE,								GWM_ENABLE,
	GWM_LEFT_DOWN,								GWM_LEFT_UP,
	GWM_LEFT_DOUBLE_CLICK,						GWM_LEFT_DRAG,
	GWM_MIDDLE_DOWN,							GWM_MIDDLE_UP,
	GWM_MIDDLE_DOUBLE_CLICK,					GWM_MIDDLE_DRAG,
	GWM_RIGHT_DOWN,								GWM_RIGHT_UP,
	GWM_RIGHT_DOUBLE_CLICK,						GWM_RIGHT_DRAG,
	GWM_MOUSE_ENTERING,							GWM_MOUSE_LEAVING,
	GWM_WHEEL_UP,								GWM_WHEEL_DOWN,
	GWM_CHAR,									GWM_SCRIPT_CREATE,
	GWM_INPUT_FOCUS,							GWM_MOUSE_POS,
	GWM_IME_CHAR,								GWM_IME_STRING
};

// ?rawMouseToWindowMessage@@YA?AW4GameWindowMessage@@PBVGameMessage@@@Z
GameWindowMessage rawMouseToWindowMessage( const GameMessage *msg )
{
	GameWindowMessage gwm = GWM_NONE;

	switch( msg->getType() )
	{
		// ------------------------------------------------------------------------
		case GameMessage::MSG_RAW_MOUSE_POSITION:
			gwm = GWM_MOUSE_POS;
			break;

		// ------------------------------------------------------------------------
		// Strange, but true. The window stuff really doesn't care about double clicks, so just
		// treat it as a down click.. Kinda like a second click.
		case GameMessage::MSG_RAW_MOUSE_LEFT_DOUBLE_CLICK:
		case GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_DOWN:
			gwm = GWM_LEFT_DOWN;
			break;

		case GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_UP:
			gwm = GWM_LEFT_UP;
			break;

		case GameMessage::MSG_RAW_MOUSE_LEFT_DRAG:
			gwm = GWM_LEFT_DRAG;
			break;

		// ------------------------------------------------------------------------
		case GameMessage::MSG_RAW_MOUSE_MIDDLE_DOUBLE_CLICK:
		case GameMessage::MSG_RAW_MOUSE_MIDDLE_BUTTON_DOWN:
			gwm = GWM_MIDDLE_DOWN;
			break;

		case GameMessage::MSG_RAW_MOUSE_MIDDLE_BUTTON_UP:
			gwm = GWM_MIDDLE_UP;
			break;

		case GameMessage::MSG_RAW_MOUSE_MIDDLE_DRAG:
			gwm = GWM_MIDDLE_DRAG;
			break;

		// ------------------------------------------------------------------------
		case GameMessage::MSG_RAW_MOUSE_RIGHT_DOUBLE_CLICK:
		case GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN:
			gwm = GWM_RIGHT_DOWN;
			break;

		case GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_UP:
			gwm = GWM_RIGHT_UP;
			break;

		case GameMessage::MSG_RAW_MOUSE_RIGHT_DRAG:
			gwm = GWM_RIGHT_DRAG;
			break;

		// ------------------------------------------------------------------------
		case GameMessage::MSG_RAW_MOUSE_WHEEL:
			if( msg->getArgument( 1 )->integer > 0 )
				gwm = GWM_WHEEL_UP;
			else
				gwm = GWM_WHEEL_DOWN;
			break;

	}  // end switch

	return gwm;

}  // end rawMouseToWindowMessage

// Expose the translator address through the existing accessor.
typedef GameWindowMessage (*RawMouseToWindowMessageType)( const GameMessage * );


// Zero Hour's WindowTranslator::translateGameMessage (WindowXlat.cpp), the
// body right after rawMouseToWindowMessage. Native [40FF12,4101F7),741B plus
// its case tables (vtable 0x00BED684 slot 0, priority 10 in GameClient::init).
// BFME2 deltas: the translator's +0x04 mode is copied into the window
// manager's +0x3C first; in mode 1 a paused-game guard replaces Zero Hour's
// mouse lock, otherwise the mouse position is forwarded to the Apt window
// manager and two global gates can keep the message; the shell/input checks
// run only in mode 1 (and for clicks not in mode 0 while the guard object at
// VA 0x00DFEF18 runs unpaused).
typedef unsigned char UnsignedByte;
enum WinInputReturnCode { WIN_INPUT_NOT_USED = 0, WIN_INPUT_USED };
enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };
enum { KEY_ESC = 0x01, KEY_STATE_UP = 0x0001 };

class GameWindow;
class GameWindowManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
	virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45();
	virtual WinInputReturnCode winProcessMouseEvent(GameWindowMessage msg, ICoord2D *mousePos, void *data);
	virtual WinInputReturnCode winProcessKey(UnsignedByte key, UnsignedByte state);
	unsigned char m_04[0x38];
	Int m_3c;
};
extern GameWindowManager *TheWindowManager;

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
// Rowed at 0x00222597 under its address class: the Apt window manager's
// mouse-position update.
class Rva00222597
{
public:
	void rva00222597(Int *mousePos);
};

class Rva002D3627Host
{
public:
	unsigned char m_00[0x18];
	bool m_18;
};
class LivingWorld; extern LivingWorld *TheLivingWorld;

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Shell
{
public:
	bool isShellActive() const { return m_isShellActive; }
private:
	unsigned char m_00[0x5C];
	bool m_isShellActive;
};
extern Shell *TheShell;

#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

#include "../../../Include/GameClient/View.h"
extern View *TheTacticalView;

#include "../../../Include/GameClient/Display.h"
extern Display *TheDisplay;

class GlobalData
{
public:
	unsigned char m_00[0xAF4];
	bool m_allowExitOutOfMovies;	// +0xAF4
};
// Native VA 0x00DFE758 is the existing writable-global-data pointer storage.
extern GlobalData *TheWritableGlobalData;

extern unsigned int g_rva00E02FC0Bits;
bool Rva00437EDCGet();

class GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg) = 0;
	virtual ~GameMessageTranslator() {}
};
class WindowTranslator : public GameMessageTranslator
{
public:
	WindowTranslator();
	virtual ~WindowTranslator();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
private:
	Int m_mode;	// +0x04
};

// ??0WindowTranslator@@QAE@XZ, retail 0x002390E8 (16B). Target evidence: it
// installs vftable 0x00BED684, whose slot 0 is the rowed
// WindowTranslator::translateGameMessage (0x0040FF12) and slot 1 the folded
// translator deleting destructor 0x004296EE (ZH GameMessageTranslator's
// pure handler plus inline virtual destructor), then sets the +4 word that
// translateGameMessage copies into TheWindowManager to 1. ZH's empty
// WindowTranslator constructor predates that BFME2 member.
WindowTranslator::WindowTranslator()
	: m_mode(1)
{
}

GameMessageDisposition WindowTranslator::translateGameMessage(const GameMessage *msg)
{
	GameMessageDisposition disp = KEEP_MESSAGE;
	WinInputReturnCode returnCode = WIN_INPUT_NOT_USED;
	TheWindowManager->m_3c = m_mode;
	bool forceKeepMessage = false;
	GameWindowMessage gwm = rawMouseToWindowMessage(msg);

	if (m_mode == 1)
	{
		if (!(((Rva002D3627Host *)TheLivingWorld) && ((Rva002D3627Host *)TheLivingWorld)->m_18 && !TheGameLogic->isGamePaused() && !(TheShell && TheShell->isShellActive())))
			goto checkView;
		return KEEP_MESSAGE;
	}
	if (gwm != GWM_NONE)
	{
		ICoord2D mousePos = msg->getArgument(0)->pixel;
		((Rva00222597 *)g_bfmeAptWindowManager)->rva00222597(&mousePos.x);
	}
	if (g_rva00E02FC0Bits || Rva00437EDCGet())
		return KEEP_MESSAGE;
checkView:
	if (TheTacticalView && TheTacticalView->getMouseLock())
		return KEEP_MESSAGE;

	switch (msg->getType())
	{
		case GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_UP:
		{
			if (TheInGameUI && TheInGameUI->isPlacementAnchored())
				forceKeepMessage = true;
		}
		case GameMessage::MSG_RAW_MOUSE_POSITION:
		case GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_DOWN:
		case GameMessage::MSG_RAW_MOUSE_LEFT_DOUBLE_CLICK:
		case GameMessage::MSG_RAW_MOUSE_MIDDLE_BUTTON_DOWN:
		case GameMessage::MSG_RAW_MOUSE_MIDDLE_DOUBLE_CLICK:
		case GameMessage::MSG_RAW_MOUSE_MIDDLE_BUTTON_UP:
		case GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN:
		case GameMessage::MSG_RAW_MOUSE_RIGHT_DOUBLE_CLICK:
		case GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_UP:
		{
			ICoord2D mousePos = msg->getArgument(0)->pixel;
			if (TheWindowManager)
				returnCode = TheWindowManager->winProcessMouseEvent(gwm, &mousePos, 0);
			if (m_mode == 0)
				break;
			if (((Rva002D3627Host *)TheLivingWorld) && ((Rva002D3627Host *)TheLivingWorld)->m_18 && !TheGameLogic->isGamePaused())
				break;
			if (TheShell && TheShell->isShellActive())
				returnCode = WIN_INPUT_USED;
			if (TheInGameUI && TheInGameUI->getInputEnabled() == false)
				returnCode = WIN_INPUT_USED;
			break;
		}

		case GameMessage::MSG_RAW_MOUSE_LEFT_DRAG:
		case GameMessage::MSG_RAW_MOUSE_MIDDLE_DRAG:
		case GameMessage::MSG_RAW_MOUSE_RIGHT_DRAG:
		{
			ICoord2D mousePos = msg->getArgument(0)->pixel;
			ICoord2D delta = msg->getArgument(1)->pixel;
			GameWindowMessage gwm = rawMouseToWindowMessage(msg);
			if (TheWindowManager)
				returnCode = TheWindowManager->winProcessMouseEvent(gwm, &mousePos, &delta);
			if (m_mode == 1)
			{
				if (TheShell && TheShell->isShellActive())
					returnCode = WIN_INPUT_USED;
				if (TheInGameUI && TheInGameUI->getInputEnabled() == false)
					returnCode = WIN_INPUT_USED;
			}
			break;
		}

		case GameMessage::MSG_RAW_MOUSE_WHEEL:
		{
			ICoord2D mousePos = msg->getArgument(0)->pixel;
			Int wheelPos = msg->getArgument(1)->integer;
			GameWindowMessage gwm = rawMouseToWindowMessage(msg);
			if (TheWindowManager)
				returnCode = TheWindowManager->winProcessMouseEvent(gwm, &mousePos, &wheelPos);
			if (m_mode == 1)
			{
				if (TheShell && TheShell->isShellActive())
					returnCode = WIN_INPUT_USED;
				if (TheInGameUI && TheInGameUI->getInputEnabled() == false)
					returnCode = WIN_INPUT_USED;
			}
			break;
		}

		case GameMessage::MSG_RAW_KEY_DOWN:
		case GameMessage::MSG_RAW_KEY_UP:
		{
			UnsignedByte key = msg->getArgument(0)->integer;
			UnsignedByte state = msg->getArgument(1)->integer;
			if (TheWindowManager)
				returnCode = TheWindowManager->winProcessKey(key, state);
			if (m_mode == 1)
			{
				if (returnCode != WIN_INPUT_USED && key == KEY_ESC && (state & KEY_STATE_UP) &&
					TheDisplay->isMoviePlaying() && TheWritableGlobalData->m_allowExitOutOfMovies == true)
				{
					TheDisplay->stopMovie();
					returnCode = WIN_INPUT_USED;
				}
				if (returnCode != WIN_INPUT_USED && key == KEY_ESC && (state & KEY_STATE_UP) &&
					TheInGameUI && TheInGameUI->getInputEnabled() == false)
				{
					returnCode = WIN_INPUT_USED;
				}
			}
			break;
		}

		default:
			break;
	}

	if (returnCode == WIN_INPUT_USED && !forceKeepMessage)
		disp = DESTROY_MESSAGE;
	return disp;
}
