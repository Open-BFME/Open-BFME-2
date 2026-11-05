// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?setWindowText@@YAXPAVGameWindow@@VAsciiString@@@Z, retail 0x003161F2,
// 355 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// setWindowText): reject an empty label, fetch the translated UnicodeString
// from TheGameText, then dispatch on the window style to the matching gadget
// setter, falling back to GameWindow::winSetText.
// BFME2 facts (all retail-measured):
// - The body is a file-static compiled with MSVC's private parser ABI: the
//   caller createWindow at 0x00316CCE hands the GameWindow in ESI and the
//   by-value AsciiString label on the stack. A visible caller is required to
//   make MSVC pick that convention, so this TU carries the external
//   setWindowTextCaller scaffold; without it the function is dead-stripped.
// - AsciiString isEmpty is inlined as m_text == 0 || *(u16*)(m_text+4) == 0
//   (the bfme2_ascii view of StringBase's Header), verified against the
//   0x00316210 cmp WORD PTR [eax+4],bx.
// - UnicodeString is a one-pointer StringBase<wchar_t> wrapper whose copy
//   constructor body is visible; retail records esp before loading it into ecx
//   at each by-value temporary, which only happens when the ctor makes a call.
// - Callees (retail call targets): TheGameText fetch slot 0x3C, StringBase
//   <wchar_t>::set 0x37150, releaseBuffer wide 0x36E70, narrow 0x36410,
//   StringBase<wchar_t> copy ctor 0x37050, translate 0x6CB6A0,
//   winGetStyle 0x5C4AF1, winSetText 0x31484A, GadgetButtonSetText 0x3283F7,
//   GadgetRadioSetText 0x3278F1, GadgetCheckBoxSetText 0x327BD4,
//   GadgetStaticTextSetText 0x321552, GadgetTextEntrySetText 0x2C17EB.
// - Identity: the only caller at 0x00316CCE is createWindow's textLabel tail,
//   and the source-order/size agree; the name is carried from the reference.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned short wchar_t;

class AsciiString;
class UnicodeString;

#include <string.h>

#include "ascii_string.h"


#include "unicode_string.h"

#include "GameWindowManagerRecordView.h"

// Retail fetch call uses vtable offset 0x3c (VersionUnicode.cpp recipe).
#include "../../../Include/GameClient/GameText.h"


struct GameWindowEditData;
class GameWindow
{
public:
	UnsignedInt winGetStyle(void);
	Int winSetText(UnicodeString newText);
	Int winSetInstanceData(WinInstanceData *data);
	Int winSetWindowId(Int value);
	GameWindowEditData *winGetEditData(void);
};

class WinInstanceData
{
public:
	unsigned char m_pad00[0x0C];
	UnsignedInt m_style;	// +0x0C (retail or-byte at +0x0D for |=0x200/0x4000)
	unsigned char m_pad10[0x188 - 0x10];
	AsciiString m_textLabelString;	// +0x188 (retail add eax,0x188)
};

struct GameWindowEditData
{
	AsciiString systemCallbackString;
	AsciiString inputCallbackString;
	AsciiString tooltipCallbackString;
	AsciiString drawCallbackString;
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n(void) = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33)
#undef V
	virtual GameWindow *slot88(GadgetCreateView *record) = 0;	// +0x88 USER/TABPANE factory
#define W(n) virtual void pad##n(void) = 0;
	W(35) W(36) W(37) W(38) W(39) W(40) W(41) W(42)
	W(43) W(44) W(45) W(46) W(47) W(48) W(49) W(50)
	W(51) W(52) W(53) W(54) W(55) W(56) W(57) W(58)
#undef W
	virtual Int slotEC(GameWindow *window, UnsignedInt m1, UnsignedInt m2, UnsignedInt m3) = 0;	// +0xEC
};

extern GameWindowManager *TheWindowManager;

extern GameWindow *peekWindow(void);
extern AsciiString g_systemCallbackName;
extern AsciiString g_inputCallbackName;
extern AsciiString g_tooltipCallbackName;
extern AsciiString g_drawCallbackName;

GameWindow *createGadget(char *type, void *data, GadgetCreateView *view, GameWindow *source);


void GadgetButtonSetText(GameWindow *window, UnicodeString text);
void GadgetRadioSetText(GameWindow *window, UnicodeString text);
void GadgetCheckBoxSetText(GameWindow *window, UnicodeString text);
void GadgetStaticTextSetText(GameWindow *window, UnicodeString text);
void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);

enum
{
	GWS_PUSH_BUTTON = 0x00000001,
	GWS_RADIO_BUTTON = 0x00000002,
	GWS_CHECK_BOX = 0x00000004,
	GWS_ENTRY_FIELD = 0x00000040,
	GWS_STATIC_TEXT = 0x00000080
};

#define BitTest(value, bit) ((value) & (bit))

// ?setWindowText@@YAXPAVGameWindow@@VAsciiString@@@Z
static void setWindowText(GameWindow *window, AsciiString textLabel)
{
	// sanity
	if (textLabel.isEmpty())
		return;

	UnicodeString theText, entryText;
	// Translate the text
	theText = TheGameText->fetch((char *)textLabel.str());
	// set the text in the window based on what it is
	if (BitTest(window->winGetStyle(), GWS_PUSH_BUTTON))
		GadgetButtonSetText(window, theText);
	else if (BitTest(window->winGetStyle(), GWS_RADIO_BUTTON))
		GadgetRadioSetText(window, theText);
	else if (BitTest(window->winGetStyle(), GWS_CHECK_BOX))
		GadgetCheckBoxSetText(window, theText);
	else if (BitTest(window->winGetStyle(), GWS_STATIC_TEXT))
		GadgetStaticTextSetText(window, theText);
	else if (BitTest(window->winGetStyle(), GWS_ENTRY_FIELD))
	{
		entryText.translate(textLabel);
		GadgetTextEntrySetText(window, entryText);
	}
	else
		window->winSetText(theText);
}

// ?createWindow@@YAPAVGameWindow@@PADHPAXPAVGadgetCreateView@@@Z, retail
// 0x00316BD2, 294 bytes. BFME1 donor
// (game/GameEngine/Source/GameClient/GUI/GameWindowManagerScriptParseWindow.cpp,
// createWindow): USER/TABPANE windows come from the manager factory with a
// style bit set, other types go through createGadget, then the edit-data
// callback strings, the text label and the parent send apply. BFME2 passes
// (type, id, data, record) with the record in EDI under MSVC's private static
// convention, so the scaffold caller below keeps it emitted. All callees
// rowed or pinned: peekWindow 0x00314EEE, strcmp import, manager slots
// 0x88/0xEC, winSetInstanceData 0x0031495C, winSetWindowId 0x0031404A,
// winGetEditData 0x0031450A, StringBase::set 0x000366F0, StringBase ctor
// 0x000365F0, setWindowText 0x003161F2, createGadget pin 0x00316518.
static GameWindow *createWindow(char *type, Int id, void *data, GadgetCreateView *record)
{
	GameWindow *window, *parent;

	parent = peekWindow();

	if (!strcmp(type, "USER"))
	{
		window = TheWindowManager->slot88(record);
		if (window)
		{
			record->instance->m_style |= 0x00000200;
			window->winSetWindowId(id);
		}
	}
	else if (!strcmp(type, "TABPANE"))
	{
		window = TheWindowManager->slot88(record);
		if (window)
		{
			record->instance->m_style |= 0x00004000;
			window->winSetInstanceData(record->instance);
			window->winSetWindowId(id);
		}
	}
	else
	{
		window = createGadget(type, data, record, 0);
		if (window)
			window->winSetWindowId(id);
	}

	if (window)
	{
		GameWindowEditData *editData = window->winGetEditData();
		if (editData)
		{
			editData->systemCallbackString.setCopyInline(g_systemCallbackName);
			editData->inputCallbackString.setCopyInline(g_inputCallbackName);
			editData->tooltipCallbackString.setCopyInline(g_tooltipCallbackName);
			editData->drawCallbackString.setCopyInline(g_drawCallbackName);
		}
	}

	if (window)
		setWindowText(window, record->instance->m_textLabelString);

	if (window && parent)
		TheWindowManager->slotEC(parent, 0x16, id, 0);

	return window;
}

// Codegen scaffold: keeps the static createWindow emitted until its real
// caller parseWindow (0x00316E8F) lands in this TU.
// ?createWindowCaller absent-from-retail
GameWindow *createWindowCaller(char *type, Int id, void *data, GadgetCreateView *record)
{
	return createWindow(type, id, data, record);
}
