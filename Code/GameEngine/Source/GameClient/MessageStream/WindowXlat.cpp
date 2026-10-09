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

struct ICoord2D
{
	Int x, y;
};

union GameMessageArgumentType
{
	Int integer;
	void *pointer;
	ICoord2D pixel;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	enum Type
	{
		MSG_RAW_MOUSE_POSITION					= 3,
		MSG_RAW_MOUSE_LEFT_BUTTON_DOWN			= 4,
		MSG_RAW_MOUSE_LEFT_DOUBLE_CLICK			= 5,
		MSG_RAW_MOUSE_LEFT_BUTTON_UP			= 6,
		MSG_RAW_MOUSE_LEFT_DRAG					= 8,
		MSG_RAW_MOUSE_MIDDLE_BUTTON_DOWN		= 10,
		MSG_RAW_MOUSE_MIDDLE_DOUBLE_CLICK		= 11,
		MSG_RAW_MOUSE_MIDDLE_BUTTON_UP			= 12,
		MSG_RAW_MOUSE_MIDDLE_DRAG				= 13,
		MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN			= 14,
		MSG_RAW_MOUSE_RIGHT_DOUBLE_CLICK		= 15,
		MSG_RAW_MOUSE_RIGHT_BUTTON_UP			= 16,
		MSG_RAW_MOUSE_RIGHT_DRAG				= 18,
		MSG_RAW_MOUSE_WHEEL						= 19,
		MSG_RAW_KEY_DOWN						= 21,
		MSG_RAW_KEY_UP							= 22
	};

	Type getType( void ) const { return m_type; }
	const GameMessageArgumentType *getArgument( Int argIndex ) const;

private:
	unsigned char m_unreconstructed_00[0x10];
	Type m_type;											///< +0x10
};

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
extern Rva002D3627Host *g_00DFEF18;

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

class InGameUI
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
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual bool isPlacementAnchored();
	bool getInputEnabled() { return m_15 && m_16; }
	unsigned char m_04[0x11];
	bool m_15;
	bool m_16;
};
extern InGameUI *TheInGameUI;

class View
{
public:
	virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003(); virtual void v004();
	virtual void v005(); virtual void v006(); virtual void v007(); virtual void v008(); virtual void v009();
	virtual void v010(); virtual void v011(); virtual void v012(); virtual void v013(); virtual void v014();
	virtual void v015(); virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023(); virtual void v024();
	virtual void v025(); virtual void v026(); virtual void v027(); virtual void v028(); virtual void v029();
	virtual void v030(); virtual void v031(); virtual void v032(); virtual void v033(); virtual void v034();
	virtual void v035(); virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
	virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043(); virtual void v044();
	virtual void v045(); virtual void v046(); virtual void v047(); virtual void v048(); virtual void v049();
	virtual void v050(); virtual void v051(); virtual void v052(); virtual void v053(); virtual void v054();
	virtual void v055(); virtual void v056(); virtual void v057(); virtual void v058(); virtual void v059();
	virtual void v060(); virtual void v061(); virtual void v062(); virtual void v063(); virtual void v064();
	virtual void v065(); virtual void v066(); virtual void v067(); virtual void v068(); virtual void v069();
	virtual void v070(); virtual void v071(); virtual void v072(); virtual void v073(); virtual void v074();
	virtual void v075(); virtual void v076(); virtual void v077(); virtual void v078(); virtual void v079();
	virtual void v080(); virtual void v081(); virtual void v082(); virtual void v083(); virtual void v084();
	virtual void v085(); virtual void v086(); virtual void v087(); virtual void v088(); virtual void v089();
	virtual void v090(); virtual void v091(); virtual void v092(); virtual void v093(); virtual void v094();
	virtual void v095(); virtual void v096(); virtual void v097(); virtual void v098(); virtual void v099();
	virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103(); virtual void v104();
	virtual void v105();
	virtual bool isMouseLocked();
};
extern View *TheTacticalView;

class Display
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
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual void v65(); virtual void v66(); virtual void v67();
	virtual void stopMovie();
	virtual bool isMoviePlaying();
};
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
};
class WindowTranslator : public GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
private:
	Int m_mode;	// +0x04
};

GameMessageDisposition WindowTranslator::translateGameMessage(const GameMessage *msg)
{
	GameMessageDisposition disp = KEEP_MESSAGE;
	WinInputReturnCode returnCode = WIN_INPUT_NOT_USED;
	TheWindowManager->m_3c = m_mode;
	bool forceKeepMessage = false;
	GameWindowMessage gwm = rawMouseToWindowMessage(msg);

	if (m_mode == 1)
	{
		if (!(g_00DFEF18 && g_00DFEF18->m_18 && !TheGameLogic->isGamePaused() && !(TheShell && TheShell->isShellActive())))
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
	if (TheTacticalView && TheTacticalView->isMouseLocked())
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
			if (g_00DFEF18 && g_00DFEF18->m_18 && !TheGameLogic->isGamePaused())
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
