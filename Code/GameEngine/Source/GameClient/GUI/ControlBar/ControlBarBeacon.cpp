// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// ControlBarBeacon.cpp -- the beacon panel and the beacon window's input callback.
//
// ?BeaconWindowInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// retail 0x0050DBAA, 60 bytes; the function lexicon (g_009BCAC8) binds it
// to the name "BeaconWindowInput". Zero Hour's body calls
// TheInGameUI->deselectAllDrawables(TRUE); BFME 2's deselectAllDrawables
// (InGameUI slot 68, rowed 0x0029BDBC) takes no argument, and the group
// message Zero Hour posts under postMsg is posted here, first: message
// 0x3EC (Zero Hour's MSG_DESTROY_SELECTED_GROUP) through TheMessageStream's
// appendMessage (slot 18) with TRUE, which deletes the entire group.

//
// ?populateBeacon@ControlBar@@QAEXPAVObject@@@Z retail 0x0050DBE6 (380
// bytes, ret 4): Zero Hour's ControlBar::populateBeacon. The three window
// names are retail's literals; setPortraitByObject is BFME 2's empty body
// (the shared ret-4 twin 0x0047A69C). TheWindowManager is called through
// +0xF0 and +0xC4 at the Zero Hour winGetWindowFromId and winSetFocus
// positions, and getCaptionText is the rowed address-named getter
// 0x0027653A on the beacon's drawable.

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;
class GameWindow;

enum { GWM_CHAR = 0x15 };
enum { KEY_ESC = 0x01 };

#include "../../../../Include/Common/MessageStream.h"
#include "../../../../../GameEngine/Include/GameClient/Drawable.h"

extern MessageStream *TheMessageStream;

#include "../../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

WindowMsgHandledType BeaconWindowInput( GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2 )
{
	if (msg == GWM_CHAR && mData1 == KEY_ESC)
	{
		GameMessage *groupMsg = TheMessageStream->appendMessage( GameMessage::MSG_DESTROY_SELECTED_GROUP );
		groupMsg->appendBooleanArgument( true );
		TheInGameUI->deselectAllDrawables(); // there should only be one beacon and nothing else selected
		return MSG_HANDLED;
	}

	return MSG_IGNORED;
}

enum NameKeyType { NAMEKEY_INVALID = 0 };
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

#include "unicode_string.h"

#include "../../../../Include/GameClient/Bfme2GameWindow.h"
void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );

#include "../../../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;

class Rva0027653A
{
public:
	UnicodeString rva0027653A();	// the drawable's caption text
};
class Drawable;
#include "../../../GameLogic/Object/object.h"

#include "../../../../Include/GameClient/ControlBar.h"

void ControlBar::populateBeacon( Object *beacon )
{

	// set the portrait for the thing being constructed
	setPortraitByObject( beacon );

	static NameKeyType textID = NAMEKEY("ControlBar.wnd:EditBeaconText");
	static NameKeyType staticTextID = NAMEKEY("ControlBar.wnd:StaticTextBeaconLabel");
	static NameKeyType clearButtonID = NAMEKEY("ControlBar.wnd:ButtonClearBeaconText");

	GameWindow *textEntryWin = TheWindowManager->winGetWindowFromId(0, textID);
	GameWindow *staticTextWin = TheWindowManager->winGetWindowFromId(0, staticTextID);
	GameWindow *buttonWin = TheWindowManager->winGetWindowFromId(0, clearButtonID);

	if (beacon->isLocallyControlled())
	{
		if (textEntryWin)
		{
			textEntryWin->winHide(false);
			GadgetTextEntrySetText( textEntryWin, ((Rva0027653A *)beacon->getDrawable())->rva0027653A() );
			TheWindowManager->winSetFocus( textEntryWin );
		}

		if (staticTextWin)
			staticTextWin->winHide(false);

		if (buttonWin)
			buttonWin->winHide(false);
	}
	else
	{
		if (textEntryWin)
			textEntryWin->winHide(true);

		if (staticTextWin)
			staticTextWin->winHide(true);

		if (buttonWin)
			buttonWin->winHide(true);
	}
}  // end populateBeacon
