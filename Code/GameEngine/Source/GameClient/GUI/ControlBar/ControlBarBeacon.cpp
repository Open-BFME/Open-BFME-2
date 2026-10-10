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

class GameMessage
{
public:
	enum Type { MSG_DESTROY_SELECTED_GROUP = 0x3EC };
	void appendBooleanArgument( bool arg );
};

class MessageStream
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
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
	virtual void slot16();
	virtual void slot17();
	virtual GameMessage *appendMessage( GameMessage::Type type );	// slot 18
};
extern MessageStream *TheMessageStream;

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
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
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void deselectAllDrawables( void );	// slot 68
};
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
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

#include "unicode_string.h"

class GameWindow
{
public:
	int winHide( bool hide );
};
void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48();
	virtual int winSetFocus( GameWindow *window );	// slot 49
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59();
	virtual GameWindow *winGetWindowFromId( GameWindow *window, int id );	// slot 60
};
extern GameWindowManager *TheWindowManager;

class Rva0027653A
{
public:
	UnicodeString rva0027653A();	// the drawable's caption text
};
class Drawable;
class Object
{
public:
	bool isLocallyControlled() const;
	Drawable *getDrawable() const;
};

class ControlBar
{
public:
	void populateBeacon( Object *beacon );
	void setPortraitByObject( Object *obj );
};

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
