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

#include "../../../../Include/GameClient/Bfme2GameWindow.h"

class CommandButton;

#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

#include "../../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "../../../../Include/Common/Player.h"

#include "../../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class LanguageFilter
{
public:
	void filterLine(UnicodeString &line);
};
extern LanguageFilter *TheLanguageFilter;

#include "../../../../Include/Common/MessageStream.h"

extern class MessageStream *TheMessageStream;

#include "../../../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;

#include "../../../../Include/GameClient/InGameUI.h"
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
				TheMessageStream->appendMessage( GameMessage::MSG_REMOVE_BEACON );
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
				TheControlBar->rva0031AD94();
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
					GameMessage *msg = TheMessageStream->appendMessage( GameMessage::MSG_SET_BEACON_TEXT );
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
