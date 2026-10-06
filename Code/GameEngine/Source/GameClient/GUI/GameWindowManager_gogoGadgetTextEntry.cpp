// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/GameClient/GUI /O1 /G7 /MD /EHsc /DNDEBUG
// GameWindowManager::gogoGadgetTextEntry, retail 0x002C1C74 (633 B, Ghidra
// boundary): slot 28 of the base window manager vtable 0x00BFF658, called
// directly by the W3D override in slot 28 of 0x00BC7C90 (0x0008FEAF) after it
// picks the entry draw factory. Reference semantics: Zero Hour / BFME1
// GameWindowManager::gogoGadgetTextEntry (BFME1 game/ GameWindowManager.cpp)
// on BFME's one-record factory ABI. Target facts: style test 0x40 on the
// record's instance (+0x30); window created through slot 34; owner through
// the rowed 0x003140CF; the entry data's cursor fields (+0x1C/+0x20), the
// unichar flag (+0x15) and the 0x100 clamp of the 16-bit length at +0x10; a
// 0x28-byte copy whose three display strings come from TheDisplayStringManager
// slot 14 and take the template's text through DisplayString slots 2/1; the
// rowed winSetUserData; the construct list (+0x18) built through slot 24 when
// OurLanguage is 8 or 6 (Zero Hour's LANGUAGE_ID_KOREAN / _JAPANESE), with
// the rowed WinInstanceData ctor/init/dtor, a 0x4C-byte list record and the
// rowed GadgetCreateView zeroer; winDestroy (slot 35) when that fails;
// assignDefaultGadgetLook (slot 30); winTextLabelToText (slot 75) of the
// instance label at +0x188 and the rowed GadgetTextEntrySetText. Entry and
// list fields carry Zero Hour's names where the offsets and stores agree.
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "GameWindowManagerRecordView.h"

class GameWindow { public: void winSetUserData(void *); };
class Rva003140CF { public: int rva003140CF(int); };

class WinInstanceData
{
public:
	WinInstanceData();
	virtual ~WinInstanceData();
	void init();

	unsigned char m_pad04[0xC - 4];
	unsigned int m_style;
	unsigned char m_pad10[0x188 - 0x10];
	AsciiString m_textLabelString;
	unsigned char m_pad18C[0x1A8 - 0x18C];
};

enum
{
	GWS_SCROLL_LISTBOX = 0x20,
	GWS_ENTRY_FIELD = 0x40,
	GWS_MOUSE_TRACK = 0x400
};

enum
{
	WIN_STATUS_HIDDEN = 0x10,
	WIN_STATUS_ABOVE = 0x20,
	WIN_STATUS_NO_FOCUS = 0x400,
	WIN_STATUS_ONE_LINE = 0x4000
};

enum { ENTRY_TEXT_LEN = 256 };

enum LanguageID
{
	LANGUAGE_ID_US = 0,
	LANGUAGE_ID_UK,
	LANGUAGE_ID_GERMAN,
	LANGUAGE_ID_FRENCH,
	LANGUAGE_ID_SPANISH,
	LANGUAGE_ID_ITALIAN,
	LANGUAGE_ID_JAPANESE,
	LANGUAGE_ID_JABBER,
	LANGUAGE_ID_KOREAN
};

extern LanguageID OurLanguage;

class DisplayString
{
public:
	virtual void unused0();
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText();
	virtual int getTextLength();
};

class DisplayStringManager
{
public:
#define V(n) virtual void unused##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
#undef V
	virtual DisplayString *newDisplayString();
};

extern DisplayStringManager *TheDisplayStringManager;

typedef struct _EntryData
{
	DisplayString *text;
	DisplayString *sText;
	DisplayString *constructText;
	unsigned char m_pad0C[0x10 - 0xC];
	short maxTextLen;
	unsigned char m_pad12[0x15 - 0x12];
	bool receivedUnichar;
	unsigned char m_pad16[0x18 - 0x16];
	GameWindow *constructList;
	unsigned short charPos;
	unsigned char m_pad1E[0x20 - 0x1E];
	unsigned short conCharPos;
	unsigned char m_pad22[0x28 - 0x22];
} EntryData;

typedef struct _ListboxData
{
	short listLength;
	short columns;
	int *columnWidthPercentage;
	bool autoScroll;
	bool autoPurge;
	bool scrollBar;
	bool multiSelect;
	bool forceSelect;
	bool scrollIfAtEnd;
	unsigned char m_pad0E[0x14 - 0xE];
	int *columnWidth;
	unsigned char m_pad18[0x4C - 0x18];
} ListboxData;

void GadgetTextEntrySetText(GameWindow *g, UnicodeString text);

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	virtual GameWindow *gogoGadgetListBox(GadgetCreateView *view,
		ListboxData *listboxDataTemplate, GameFont *defaultFont, bool defaultVisual) = 0;
	V(25) V(26) V(27)
	virtual GameWindow *gogoGadgetTextEntry(GadgetCreateView *view,
		EntryData *entryData, GameFont *defaultFont, bool defaultVisual);
	V(29)
	virtual void assignDefaultGadgetLook(GameWindow *window, GameFont *font, bool visual) = 0;
	V(31) V(32) V(33)
	virtual GameWindow *createFromView(GadgetCreateView *view) = 0;
	virtual int winDestroy(GameWindow *window) = 0;
	V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
	V(72) V(73) V(74)
	virtual UnicodeString winTextLabelToText(AsciiString label) = 0;
#undef V
};

GameWindow *GameWindowManager::gogoGadgetTextEntry(GadgetCreateView *view,
	EntryData *entryData, GameFont *defaultFont, bool defaultVisual)
{
	GameWindow *entry;
	EntryData *data;

	if (!(view->instance->m_style & GWS_ENTRY_FIELD))
		return 0;

	// create the window
	entry = createFromView(view);
	if (entry == 0)
		return 0;

	// set owner of this control
	((Rva003140CF *)entry)->rva003140CF((int)view->parent);

	// initialize character positions, lengths etc
	if (entryData->text)
		entryData->charPos = entryData->text->getTextLength();
	else
		entryData->charPos = 0;
	entryData->conCharPos = 0;
	entryData->receivedUnichar = false;
	if (entryData->maxTextLen >= ENTRY_TEXT_LEN)
		entryData->maxTextLen = ENTRY_TEXT_LEN;

	// allocate entry data and copy over data control
	data = new EntryData;
	memcpy(data, entryData, sizeof(EntryData));

	// allocate new text display strings
	data->text = TheDisplayStringManager->newDisplayString();
	data->sText = TheDisplayStringManager->newDisplayString();
	data->constructText = TheDisplayStringManager->newDisplayString();

	// do any real display string copies
	if (entryData->text)
		data->text->setText(entryData->text->getText());
	if (entryData->sText)
		data->sText->setText(entryData->sText->getText());

	// set data into window
	entry->winSetUserData(data);

	// asian languages get to have list box kanji character completion
	data->constructList = 0;
	if (OurLanguage == LANGUAGE_ID_KOREAN || OurLanguage == LANGUAGE_ID_JAPANESE)
	{
		// we need to create the construct listbox
		WinInstanceData boxInstData;
		ListboxData lData;

		boxInstData.init();

		memset(&lData, 0, sizeof(ListboxData));
		lData.listLength = 128;
		lData.autoScroll = false;
		lData.scrollIfAtEnd = false;
		lData.autoPurge = true;
		lData.scrollBar = true;
		lData.multiSelect = false;
		lData.columns = 1;
		lData.columnWidth = 0;

		boxInstData.m_style = GWS_SCROLL_LISTBOX | GWS_MOUSE_TRACK;

		GadgetCreateView boxView;
		boxView.status = WIN_STATUS_ABOVE | WIN_STATUS_HIDDEN |
			WIN_STATUS_NO_FOCUS | WIN_STATUS_ONE_LINE;
		boxView.y = view->height;
		boxView.width = 110;
		boxView.height = 119;
		boxView.instance = &boxInstData;

		data->constructList = gogoGadgetListBox(&boxView, &lData, 0, true);
		if (data->constructList == 0)
		{
			winDestroy(entry);
			return 0;
		}
	}

	// assign the default images/colors
	assignDefaultGadgetLook(entry, defaultFont, defaultVisual);

	// assign text from label
	UnicodeString text = winTextLabelToText(view->instance->m_textLabelString);
	if (text.getLength())
		GadgetTextEntrySetText(entry, text);

	return entry;
}
