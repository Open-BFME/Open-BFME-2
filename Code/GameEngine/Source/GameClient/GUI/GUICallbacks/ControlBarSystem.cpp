// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ControlBarSystem 0x00402455 (1291B): Zero Hour ControlBarCallback.cpp's
// control bar system callback, read against BFME1's ControlBarSystem
// (Open-BFME-1 game/GameEngine/Source/GameClient/GUI/GUICallbacks/Rva004C0560.cpp).
//
// Target evidence: the FunctionLexicon entry at 0x009BCA7C pairs the literal
// "ControlBarSystem" (0x00C02708) with 0x00402455. The body is ZH's: the
// game-ending early-out, the PopupCommunicator key on create, the
// button-transition call on mouse entering/leaving, the beacon, general,
// large, options and idle-worker buttons with their seven function-local
// keys, and the beacon text on edit done. BFME2, like BFME1, also takes slider
// track (0x400B) into the button case, swallowing it for the named buttons and
// otherwise passing it to processContextSensitiveButtonClick; the
// communicator button does nothing; HideQuitMenu and ToggleQuitMenu are the
// unnamed 0x0051B11C and 0x0051B8EA; remove beacon and set beacon text are
// messages 0x445 and 0x446; GEM_EDIT_DONE is 0x4031.
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned short WideChar;
typedef unsigned int WindowMsgData;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

enum { GWM_CREATE = 1 };

enum GadgetGameMessage
{
	GBM_MOUSE_ENTERING = 0x4006,
	GBM_MOUSE_LEAVING = 0x4007,
	GBM_SELECTED = 0x4008,
	GBM_SELECTED_RIGHT = 0x4009,
	GSM_SLIDER_TRACK = 0x400B,
	GEM_EDIT_DONE = 0x4031
};

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum CBCommandStatus { CBC_COMMAND_NOT_USED = 0, CBC_COMMAND_USED };

class GameWindow
{
public:
	Int winGetWindowId();
};

class CommandButton;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

class ControlBar
{
public:
	CBCommandStatus processContextSensitiveButtonClick(GameWindow *button, GadgetGameMessage gadgetMessage);
	CBCommandStatus processContextSensitiveButtonTransition(GameWindow *button, GadgetGameMessage gadgetMessage);
	const CommandButton *findCommandButton(const AsciiString &commandName);
	void togglePurchaseScience();
	void rva0031BAB1();
};
extern ControlBar *TheControlBar;

class GameLogic
{
public:
	Bool isInMultiplayerGame();
};
extern GameLogic *TheGameLogic;

class Player
{
public:
	Bool isPlayerActive() const;
};

class PlayerList
{
public:
	// Matched callers read the local player at +0x10 directly; do not emit
	// a shared getter from this partial target layout.
	char m_pad00[0x10];
	Player *m_local;                // +0x10
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
	char m_pad00[0x1A104];
	Int m_endGameTimer;             // +0x1A104
	Bool isGameEnding() { return m_endGameTimer >= 0; }
};
extern ScriptEngine *TheScriptEngine;

class LanguageFilter
{
public:
	void filterLine(UnicodeString &line);
};
extern LanguageFilter *TheLanguageFilter;

class GameMessage
{
public:
	enum Type { MSG_REMOVE_BEACON = 0x445, MSG_SET_BEACON_TEXT = 0x446 };
	void appendWideCharArgument(const WideChar &arg);
};

class MessageStream
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(GameMessage::Type type);           // +0x48
};
extern MessageStream *MessageStreamSubsystem;

class GameWindowManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);   // +0xF0
};
extern GameWindowManager *TheWindowManager;

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46();
	virtual void setGUICommand(const CommandButton *command);              // +0xBC
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69();
	virtual Int getSelectCount();                                         // +0x118
	virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74();
	virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78();
	virtual void v79(); virtual void v80(); virtual void v81(); virtual void v82();
	virtual void v83(); virtual void v84(); virtual void v85(); virtual void v86();
	virtual void v87(); virtual void v88(); virtual void v89(); virtual void v90();
	virtual void v91(); virtual void v92(); virtual void v93(); virtual void v94();
	virtual void v95(); virtual void v96(); virtual void v97(); virtual void v98();
	virtual void v99(); virtual void v100(); virtual void v101(); virtual void v102();
	virtual void v103(); virtual void v104(); virtual void v105(); virtual void v106();
	virtual void selectNextIdleWorker();                                  // +0x1AC
};
extern InGameUI *TheInGameUI;

UnicodeString GadgetTextEntryGetText(GameWindow *textentry);
void GadgetTextEntrySetText(GameWindow *textentry, UnicodeString text);
void Rva0051B11CEnable();
void Rva0051B8EA();

WindowMsgHandledType ControlBarSystem( GameWindow *window, UnsignedInt msg,
																			 WindowMsgData mData1, WindowMsgData mData2 )
{
	static NameKeyType buttonCommunicator = NAMEKEY_INVALID;
	if(TheScriptEngine && TheScriptEngine->isGameEnding())
		return MSG_IGNORED;
	switch( msg )
	{
		case GWM_CREATE:
		{
			buttonCommunicator = TheNameKeyGenerator->nameToKey( AsciiString("ControlBar.wnd:PopupCommunicator") );
			break;
		}

		case GBM_MOUSE_ENTERING:
		case GBM_MOUSE_LEAVING:
		{
			GameWindow *control = (GameWindow *)mData1;

			TheControlBar->processContextSensitiveButtonTransition( control, (GadgetGameMessage)msg );
			break;
		}

		case GBM_SELECTED:
		case GBM_SELECTED_RIGHT:
		case GSM_SLIDER_TRACK:
		{
			GameWindow *control = (GameWindow *)mData1;
			static NameKeyType beaconPlacementButtonID = NAMEKEY("ControlBar.wnd:ButtonPlaceBeacon");
			static NameKeyType beaconDeleteButtonID = NAMEKEY("ControlBar.wnd:ButtonDeleteBeacon");
			static NameKeyType beaconClearTextButtonID = NAMEKEY("ControlBar.wnd:ButtonClearBeaconText");
			static NameKeyType beaconGeneralButtonID = NAMEKEY("ControlBar.wnd:ButtonGeneral");
			static NameKeyType buttonLargeID = NAMEKEY("ControlBar.wnd:ButtonLarge");
			static NameKeyType buttonOptions = NAMEKEY("ControlBar.wnd:ButtonOptions");
			static NameKeyType buttonIdleWorker = NAMEKEY("ControlBar.wnd:ButtonIdleWorker");

			Int controlID = control->winGetWindowId();
			if( msg == GSM_SLIDER_TRACK )
			{
				if( controlID == buttonCommunicator || controlID == beaconPlacementButtonID ||
						controlID == beaconDeleteButtonID || controlID == beaconGeneralButtonID ||
						controlID == beaconClearTextButtonID || controlID == buttonLargeID ||
						controlID == buttonOptions || controlID == buttonIdleWorker )
					break;
				if( TheControlBar->processContextSensitiveButtonClick( control, (GadgetGameMessage)msg ) == CBC_COMMAND_NOT_USED )
					return MSG_IGNORED;
				break;
			}

			if( controlID == buttonCommunicator )
			{
			}
			else if( controlID == beaconPlacementButtonID && TheGameLogic->isInMultiplayerGame() &&
				ThePlayerList->m_local->isPlayerActive())
			{
				const CommandButton *commandButton = TheControlBar->findCommandButton( "Command_PlaceBeacon" );
				TheInGameUI->setGUICommand( commandButton );
			}
			else if( controlID == beaconDeleteButtonID && TheGameLogic->isInMultiplayerGame() )
			{
				MessageStreamSubsystem->appendMessage( GameMessage::MSG_REMOVE_BEACON );
			}
			else if( controlID == beaconClearTextButtonID && TheGameLogic->isInMultiplayerGame() )
			{
				static NameKeyType textID = NAMEKEY("ControlBar.wnd:EditBeaconText");
				GameWindow *win = TheWindowManager->winGetWindowFromId(0, textID);
				if (win)
				{
					GadgetTextEntrySetText( win, UnicodeString::TheEmptyString );
				}
			}
			else if( controlID == beaconGeneralButtonID)
			{
				Rva0051B11CEnable();
				TheControlBar->togglePurchaseScience();
			}
			else if( controlID == buttonLargeID)
			{
				TheControlBar->rva0031BAB1();
			}
			else if( controlID == buttonOptions)
			{
				Rva0051B8EA();
			}
			else if( controlID == buttonIdleWorker)
			{
				Rva0051B11CEnable();
				TheInGameUI->selectNextIdleWorker();
			}
			else
			{
				TheControlBar->processContextSensitiveButtonClick( control, (GadgetGameMessage)msg );
			}
			break;
		}

		case GEM_EDIT_DONE:
		{
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();
			static NameKeyType textID = NAMEKEY("ControlBar.wnd:EditBeaconText");
			if (controlID == textID)
			{
				if (TheInGameUI->getSelectCount() == 1)
				{
					GameMessage *msg = MessageStreamSubsystem->appendMessage( GameMessage::MSG_SET_BEACON_TEXT );
					UnicodeString newText = GadgetTextEntryGetText( control );
					TheLanguageFilter->filterLine(newText);
					const WideChar * c = newText.str();
					while ( c && *c )
					{
						msg->appendWideCharArgument( *c++ );
					}
					msg->appendWideCharArgument( L'\0' );
				}
			}
			break;
		}

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
