// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// BFME 2 port of Open-BFME-1's dedicated GameWindowManagerMessageBox body.
// Donor source: reference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/GameWindowManagerMessageBox.cpp.
// Donor revision d6db6bfa4fd3bd86c1d7ca4a5ab882d7c453a92c; its original flags were
// /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib.
// Donor identity/layout remain donor facts; BFME 2 identity and offsets below
// are supported separately by target literals, body behavior and retail calls.
// The BFME 2 body at 0x002C263A is identified by its menu literals and message-box
// behavior; retail calls prove manager slots +0x7c/+0xc4/+0xf0/+0x100 and clears
// the +0x1f4 field on both created windows. Its UnicodeString copy is inline here
// to reproduce the direct StringBase<wchar_t> copy at retail 0x00037050.

#include <stddef.h>
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
enum NameKeyType { NAMEKEY_INVALID = 0 };
#define FALSE false
#define NEW new
#define DEBUG_ASSERTCRASH(condition, message) ((void)0)

enum {
	MSG_BOX_YES = 0x01,
	MSG_BOX_NO = 0x02,
	MSG_BOX_CANCEL = 0x04,
	MSG_BOX_OK = 0x08
};

struct ICoord2D { Int x, y; };
typedef void (*GameWinMsgBoxFunc)(void);
struct WindowMessageBoxData
{
	GameWinMsgBoxFunc yesCallback;
	GameWinMsgBoxFunc noCallback;
	GameWinMsgBoxFunc okCallback;
	GameWinMsgBoxFunc cancelCallback;
};
class WindowLayoutInfo;

class GameWindow
{
public:
	Int winSetPosition(Int x, Int y);
	Int winGetPosition(Int *x, Int *y);
	Int winGetSize(Int *w, Int *h);
	Int winSetSize(Int w, Int h);
	Int winHide(Bool hide);
	Int winBringToTop(void);
	void winSetUserData(void *data);
	GameWindow *winGetChild(void);
	GameWindow *winGetNext(void);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	NameKeyType nameToKey(const AsciiString &name) { return nameToKey(name.str()); }
};

class __declspec(novtable) GameWindowManager
{
public:
	virtual GameWindow *gogoMessageBox(Int x, Int y, Int width, Int height,
		UnsignedShort buttonFlags, UnicodeString titleString,
		UnicodeString bodyString, GameWinMsgBoxFunc yesCallback,
		GameWinMsgBoxFunc noCallback, GameWinMsgBoxFunc okCallback,
		GameWinMsgBoxFunc cancelCallback, Bool useLogo);
};
extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;
void GadgetStaticTextSetText(GameWindow *win, UnicodeString text);

class GogoMessageBoxManagerBfme2View
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual GameWindow *winCreateFromScript( AsciiString filename, void *info, void *extra = NULL ) = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual Int winSetFocus( GameWindow *window ) = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual GameWindow *winGetWindowFromId( GameWindow *window, Int id ) = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual Int winSetModal( GameWindow *window ) = 0;
};

/* The same BFME-only GameWindow field is documented at +0x1f4 in the gamewindow shim. */
struct GogoMessageBoxGameWindowBfme2TailView
{
	char m_pad[0x1f4];
	void *m_bfmeCallbackExtra2;
};

GameWindow *GameWindowManager::gogoMessageBox(Int x, Int y, Int width, Int height, UnsignedShort buttonFlags,
                        UnicodeString titleString, UnicodeString bodyString,
                        GameWinMsgBoxFunc yesCallback,
                        GameWinMsgBoxFunc noCallback,
                        GameWinMsgBoxFunc okCallback,
                        GameWinMsgBoxFunc cancelCallback, Bool useLogo )

{
	// first check to make sure we have some buttons to display
	if(buttonFlags == 0 )
	{
		return NULL;
	}
	GameWindow *trueParent = NULL;
	//Changed by Chris
	if(useLogo)
		trueParent = ((GogoMessageBoxManagerBfme2View *)this)->winCreateFromScript( AsciiString("Menus/QuitMessageBox.wnd"), NULL );
	else
		trueParent = ((GogoMessageBoxManagerBfme2View *)this)->winCreateFromScript( AsciiString("Menus/MessageBox.wnd"), NULL );
	((GogoMessageBoxGameWindowBfme2TailView *)trueParent)->m_bfmeCallbackExtra2 = NULL;
	//Added By Chris
	AsciiString menuName;
	if(useLogo)
		menuName.set("QuitMessageBox.wnd:");
	else
		menuName.set("MessageBox.wnd:");

	AsciiString tempName;
	GameWindow *parent = NULL;

	tempName = menuName;
	tempName.concat("MessageBoxParent");
	parent = ((GogoMessageBoxManagerBfme2View *)TheWindowManager)->winGetWindowFromId(trueParent, TheNameKeyGenerator->nameToKey( tempName ));
	if (parent != NULL) ((GogoMessageBoxGameWindowBfme2TailView *)parent)->m_bfmeCallbackExtra2 = NULL;
	((GogoMessageBoxManagerBfme2View *)TheWindowManager)->winSetModal( trueParent );
	((GogoMessageBoxManagerBfme2View *)TheWindowManager)->winSetFocus( NULL ); // make sure we lose focus from other windows even if we refuse focus ourselves
	((GogoMessageBoxManagerBfme2View *)TheWindowManager)->winSetFocus( parent	 );

	// If the user wants the size to be different then the default
	float ratioX, ratioY = 1;

	if( width > 0 && height > 0 )
	{
		ICoord2D temp;
		//First grab the percent increase/decrease compaired to the default size
		parent->winGetSize( &temp.x, &temp.y);
		ratioX = (float)width / (float)temp.x;
		ratioY = (float)height / (float)temp.y;
		//Set the window's new size
		parent->winSetSize( width, height);

		//Resize/reposition all the children windows based off the ratio
		GameWindow *child;
		for( child = parent->winGetChild(); child; child = child->winGetNext() )
		{
			child->winGetSize(&temp.x, &temp.y);
			temp.x =Int(temp.x * ratioX);
			temp.y =Int(temp.y * ratioY);
			child->winSetSize(temp.x, temp.y);

			child->winGetPosition(&temp.x, &temp.y);
			temp.x =Int(temp.x * ratioX);
			temp.y =Int(temp.y * ratioY);
			child->winSetPosition(temp.x, temp.y);
		}
	}

	// If the user wants to position the message box somewhere other then default
	if( x >= 0 && y >= 0)
		parent->winSetPosition(x, y);

	// Reposition the buttons
	Int buttonX[3], buttonY[3];

	//In the layout, buttonOk will be in the first button position
	NameKeyType buttonOkID = NAMEKEY_INVALID;

	tempName = menuName;
	tempName.concat("ButtonOk");
	buttonOkID = TheNameKeyGenerator->nameToKey( tempName );
	GameWindow *buttonOk = ((GogoMessageBoxManagerBfme2View *)TheWindowManager)->winGetWindowFromId(parent, buttonOkID);
	buttonOk->winGetPosition(&buttonX[0], &buttonY[0]);

	tempName = menuName;
	tempName.concat("ButtonYes");
	NameKeyType buttonYesID = TheNameKeyGenerator->nameToKey( tempName );
	GameWindow *buttonYes = ((GogoMessageBoxManagerBfme2View *)TheWindowManager)->winGetWindowFromId(parent, buttonYesID);
	//buttonNo in the second position
	tempName = menuName;
	tempName.concat("ButtonNo");
	NameKeyType buttonNoID = TheNameKeyGenerator->nameToKey(tempName);
	GameWindow *buttonNo = ((GogoMessageBoxManagerBfme2View *)TheWindowManager)->winGetWindowFromId(parent, buttonNoID);
	buttonNo->winGetPosition(&buttonX[1], &buttonY[1]);

	//and buttonCancel in the third
	tempName = menuName;
	tempName.concat("ButtonCancel");
	NameKeyType buttonCancelID = TheNameKeyGenerator->nameToKey( tempName );
	GameWindow *buttonCancel = ((GogoMessageBoxManagerBfme2View *)TheWindowManager)->winGetWindowFromId(parent, buttonCancelID);
	buttonCancel->winGetPosition(&buttonX[2], &buttonY[2]);

	//we shouldn't have button OK and Yes on the same dialog
	if((buttonFlags & (MSG_BOX_OK | MSG_BOX_YES)) == (MSG_BOX_OK | MSG_BOX_YES) )
	{
		DEBUG_ASSERTCRASH(false, ("Passed in MSG_BOX_OK and MSG_BOX_YES.  Big No No."));
	}

	//Position the OK button if we have one
	if( (buttonFlags & MSG_BOX_OK) == MSG_BOX_OK)
	{
		buttonOk->winSetPosition(buttonX[0], buttonY[0]);
		buttonOk->winHide(FALSE);
	}
	else if( (buttonFlags & MSG_BOX_YES) == MSG_BOX_YES)
	{
		//Position the Yes if we have one
		buttonYes->winSetPosition(buttonX[0], buttonY[0]);
		buttonYes->winHide(FALSE);
	}

	if((buttonFlags & (MSG_BOX_NO | MSG_BOX_CANCEL)) == (MSG_BOX_NO | MSG_BOX_CANCEL) )
	{
		//If we have both the No and Cancel button, then the no should go in the middle position
		buttonNo->winSetPosition(buttonX[1], buttonY[1]);
		buttonCancel->winSetPosition(buttonX[2], buttonY[2]);
		buttonNo->winHide(FALSE);
		buttonCancel->winHide(FALSE);
	}
	else if( (buttonFlags & MSG_BOX_NO) == MSG_BOX_NO)
	{
		//if we just have the no button, then position it in the right most spot
		buttonNo->winSetPosition(buttonX[2], buttonY[2]);
		buttonNo->winHide(FALSE);
	}
	else if( (buttonFlags & MSG_BOX_CANCEL) == MSG_BOX_CANCEL)
	{
		//else if we just have the Cancel button, well, it should always go in the right spot
		buttonCancel->winSetPosition(buttonX[2], buttonY[2]);
		buttonCancel->winHide(FALSE);
	}

	// Fill the text into the text boxes
	tempName = menuName;
	tempName.concat("StaticTextTitle");
	NameKeyType staticTextTitleID = TheNameKeyGenerator->nameToKey( tempName );
	GameWindow *staticTextTitle = ((GogoMessageBoxManagerBfme2View *)TheWindowManager)->winGetWindowFromId(parent, staticTextTitleID);
	GadgetStaticTextSetText(staticTextTitle,titleString);
	tempName = menuName;
	tempName.concat("StaticTextMessage");
	NameKeyType staticTextMessageID = TheNameKeyGenerator->nameToKey( tempName );
	GameWindow *staticTextMessage = ((GogoMessageBoxManagerBfme2View *)TheWindowManager)->winGetWindowFromId(parent, staticTextMessageID);
	GadgetStaticTextSetText(staticTextMessage,bodyString);

	// create a structure that will pass the functions to
	WindowMessageBoxData *MsgBoxCallbacks = NEW WindowMessageBoxData;
	MsgBoxCallbacks->cancelCallback = cancelCallback;
	MsgBoxCallbacks->noCallback = noCallback;
	MsgBoxCallbacks->okCallback = okCallback;
	MsgBoxCallbacks->yesCallback = yesCallback;
	//pass the structure to the dialog
	trueParent->winSetUserData( MsgBoxCallbacks );

	//make sure the dialog is showing and bring it to the top
	parent->winHide(FALSE);
	parent->winBringToTop();

	//Changed By Chris
	return trueParent;
}// gogoMessageBox
