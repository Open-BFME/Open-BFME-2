// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/GameClient/GUI /O1 /G7 /MD /EHsc /DNDEBUG
// GameWindowManager::gogoGadgetComboBox, retail 0x002C2AF8 (999 B, Ghidra
// boundary): slot 29 of the base window manager vtable 0x00BFF658, called
// directly by the W3D override in slot 29 of 0x00BC7C90 (0x0008FEDE) after it
// picks the combo box draw factory. Reference semantics: Zero Hour
// GameWindowManager::gogoGadgetComboBox (BFME1 2791daf553 inputs; BFME1
// carries it as a MASM dump) on BFME's one-record factory ABI. Target facts:
// style test 0x8000 on the record's instance (+0x30); window created through
// slot 34; a 0x34-byte data copy set as user data; owner through the rowed
// 0x003140CF; the rowed title-length probes whose results go unused; status
// bits 0x1010 cleared in the record; the unused font height (slot 72 of
// TheWindowManager on the pinned winGetFont); one WinInstanceData reused for
// the push button (slot 19, owner +0x14, style 1), the text entry (slot 28,
// style 0x40, label " " where Zero Hour has "Entry" -- retail pushes the
// pooled one-space literal at 0x00BBD40C -- no-input status 0x200 and the
// entry's +0x16 flag when not editable) and the list box (slot 24, style 0x30, status less 0x80
// plus 0x4020, hidden through the rowed winHide), each in its own zeroed
// GadgetCreateView; mouse tracking 0x400 copied from the pinned winGetStyle;
// each child gets the instance tooltip (rowed getTooltipText and the rowed
// 0x003148A2 setter) and the tooltip delay at +0x1C8, but no tooltip
// callback copy; the template entry/list records freed and replaced by the
// children's user data; the rowed combo box and list box setters; the three
// pinned color pairs copied to list then entry; +0x1C cleared; and
// assignDefaultGadgetLook (slot 30). Data fields carry Zero Hour's names
// where the offsets and stores agree.
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "GameWindowManagerRecordView.h"

typedef int Color;

class GameWindow
{
public:
	void winSetUserData(void *data);
	void *winGetUserData();
	int winGetTextLength();
	GameFont *winGetFont();
	unsigned int winGetStyle();
	int winHide(bool hide);
	// Zero Hour's winSetTooltip, rowed under its address name.
	void rva003148A2(UnicodeString tip);
	int getTooltipDelay() { return m_tooltipDelay; }
	void setTooltipDelay(int delay) { m_tooltipDelay = delay; }
	Color winGetEnabledTextColor();
	Color winGetEnabledTextBorderColor();
	Color winGetDisabledTextColor();
	Color winGetDisabledTextBorderColor();
	Color winGetHiliteTextColor();
	Color winGetHiliteTextBorderColor();
	void winSetEnabledTextColors(Color color, Color borderColor);
	void winSetDisabledTextColors(Color color, Color borderColor);
	void winSetHiliteTextColors(Color color, Color borderColor);

	unsigned char m_pad00[0x1C8];
	int m_tooltipDelay;
};

class Rva003140CF { public: int rva003140CF(int); };

class WinInstanceData
{
public:
	WinInstanceData();
	virtual ~WinInstanceData();
	void init();
	int getTextLength();
	UnicodeString getTooltipText();

	unsigned char m_pad04[0xC - 4];
	unsigned int m_style;
	unsigned char m_pad10[0x14 - 0x10];
	GameWindow *m_owner;
	unsigned char m_pad18[0x184 - 0x18];
	GameFont *m_font;
	AsciiString m_textLabelString;
	unsigned char m_pad18C[0x1A8 - 0x18C];
};

enum
{
	GWS_PUSH_BUTTON = 0x1,
	GWS_SCROLL_LISTBOX = 0x20,
	GWS_ENTRY_FIELD = 0x40,
	GWS_MOUSE_TRACK = 0x400,
	GWS_COMBO_BOX = 0x8000
};

enum
{
	WIN_STATUS_ACTIVE = 0x1,
	WIN_STATUS_ENABLED = 0x8,
	WIN_STATUS_HIDDEN = 0x10,
	WIN_STATUS_ABOVE = 0x20,
	WIN_STATUS_IMAGE = 0x80,
	WIN_STATUS_NO_INPUT = 0x200,
	WIN_STATUS_BORDER = 0x1000,
	WIN_STATUS_ONE_LINE = 0x4000
};

typedef struct _EntryData
{
	unsigned char m_pad00[0x16];
	bool drawTextFromStart;
	unsigned char m_pad17[0x28 - 0x17];
} EntryData;

typedef struct _ListboxData ListboxData;

typedef struct _ComboBoxData
{
	bool isEditable;
	int maxDisplay;
	int maxChars;
	bool asciiOnly;
	bool lettersAndNumbersOnly;
	ListboxData *listboxData;
	EntryData *entryData;
	int entryCount;
	bool dontHide;
	unsigned char m_pad1D[0x24 - 0x1D];
	GameWindow *dropDownButton;
	GameWindow *editBox;
	GameWindow *listBox;
	unsigned char m_pad30[0x34 - 0x30];
} ComboBoxData;

void GadgetListBoxSetAudioFeedback(GameWindow *listbox, bool enable);
void GadgetComboBoxSetIsEditable(GameWindow *comboBox, bool isEditable);
void GadgetComboBoxSetMaxChars(GameWindow *comboBox, int maxChars);
void GadgetComboBoxSetMaxDisplay(GameWindow *comboBox, int maxDisplay);

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18)
	virtual GameWindow *gogoGadgetPushButton(GadgetCreateView *view,
		GameFont *defaultFont, bool defaultVisual) = 0;
	V(20) V(21) V(22) V(23)
	virtual GameWindow *gogoGadgetListBox(GadgetCreateView *view,
		ListboxData *listboxDataTemplate, GameFont *defaultFont, bool defaultVisual) = 0;
	V(25) V(26) V(27)
	virtual GameWindow *gogoGadgetTextEntry(GadgetCreateView *view,
		EntryData *entryData, GameFont *defaultFont, bool defaultVisual) = 0;
	virtual GameWindow *gogoGadgetComboBox(GadgetCreateView *view,
		ComboBoxData *comboBoxDataTemplate, GameFont *defaultFont, bool defaultVisual);
	virtual void assignDefaultGadgetLook(GameWindow *window, GameFont *font, bool visual) = 0;
	V(31) V(32) V(33)
	virtual GameWindow *createFromView(GadgetCreateView *view) = 0;
	V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
	virtual int winFontHeight(GameFont *font) = 0;
#undef V
};

extern GameWindowManager *TheWindowManager;

GameWindow *GameWindowManager::gogoGadgetComboBox(GadgetCreateView *view,
	ComboBoxData *comboBoxDataTemplate, GameFont *defaultFont, bool defaultVisual)
{
	GameWindow *comboBox;
	ComboBoxData *comboBoxData;
	bool title = false;

	// we MUST have a combo box style window to do this
	if (!(view->instance->m_style & GWS_COMBO_BOX))
		return 0;

	// create the combo box
	comboBox = createFromView(view);
	if (comboBox == 0)
		return 0;

	// allocate the combo box data, copy template data over and set it into box
	comboBoxData = new ComboBoxData;
	memcpy(comboBoxData, comboBoxDataTemplate, sizeof(ComboBoxData));
	comboBox->winSetUserData(comboBoxData);

	// set the owner to the parent, or if no parent it will be itself
	((Rva003140CF *)comboBox)->rva003140CF((int)view->parent);

	// adjust for list title if present
	if (view->instance->getTextLength())
		title = true;

	// create the windows that make up the combo box
	WinInstanceData winInstData;
	int buttonWidth, buttonHeight;
	int fontHeight;
	int top;
	int bottom;

	// do we have a title
	if (comboBox->winGetTextLength())
		title = true;

	// remove unwanted status bits
	view->status &= ~(WIN_STATUS_BORDER | WIN_STATUS_HIDDEN);

	fontHeight = TheWindowManager->winFontHeight(comboBox->winGetFont());
	top = title ? (fontHeight + 1) : 0;
	bottom = title ? (view->height - (fontHeight + 1)) : view->height;

	// initialize instData
	winInstData.init();

	// size of button
	buttonWidth = 21;
	buttonHeight = 22;

	// create drop down button
	winInstData.m_owner = comboBox;
	winInstData.m_style = GWS_PUSH_BUTTON;

	// if the combo box tracks, so will this sub control
	if (comboBox->winGetStyle() & GWS_MOUSE_TRACK)
		winInstData.m_style |= GWS_MOUSE_TRACK;

	GadgetCreateView buttonView;
	buttonView.parent = comboBox;
	buttonView.status = view->status | WIN_STATUS_ACTIVE | WIN_STATUS_ENABLED;
	buttonView.x = view->width - buttonWidth;
	buttonView.width = buttonWidth;
	buttonView.height = view->height;
	buttonView.instance = &winInstData;
	comboBoxData->dropDownButton = TheWindowManager->gogoGadgetPushButton(&buttonView, 0, true);
	comboBoxData->dropDownButton->rva003148A2(view->instance->getTooltipText());
	comboBoxData->dropDownButton->setTooltipDelay(comboBox->getTooltipDelay());

	// create text entry
	unsigned int statusTextEntry;
	winInstData.init();
	winInstData.m_owner = comboBox;
	winInstData.m_style |= GWS_ENTRY_FIELD;
	winInstData.m_textLabelString = " ";
	if (comboBox->winGetStyle() & GWS_MOUSE_TRACK)
		winInstData.m_style |= GWS_MOUSE_TRACK;

	if (comboBoxData->isEditable)
	{
		statusTextEntry = view->status;
	}
	else
	{
		statusTextEntry = view->status | WIN_STATUS_NO_INPUT;
		comboBoxData->entryData->drawTextFromStart = true;
	}

	GadgetCreateView entryView;
	entryView.parent = comboBox;
	entryView.status = statusTextEntry;
	entryView.width = view->width - buttonWidth;
	entryView.height = view->height;
	entryView.instance = &winInstData;
	comboBoxData->editBox = TheWindowManager->gogoGadgetTextEntry(&entryView,
		comboBoxData->entryData, winInstData.m_font, false);
	comboBoxData->editBox->rva003148A2(view->instance->getTooltipText());
	comboBoxData->editBox->setTooltipDelay(comboBox->getTooltipDelay());

	delete comboBoxData->entryData;
	comboBoxData->entryData = (EntryData *)comboBoxData->editBox->winGetUserData();

	// create list box
	winInstData.init();
	winInstData.m_owner = comboBox;
	if (comboBox->winGetStyle() & GWS_MOUSE_TRACK)
		winInstData.m_style |= GWS_MOUSE_TRACK;
	view->status &= ~WIN_STATUS_IMAGE;
	unsigned int statusListBox = view->status;
	winInstData.m_style |= WIN_STATUS_HIDDEN;
	winInstData.m_style |= GWS_SCROLL_LISTBOX;

	GadgetCreateView listView;
	listView.parent = comboBox;
	listView.status = statusListBox | WIN_STATUS_ABOVE | WIN_STATUS_ONE_LINE;
	listView.y = view->height;
	listView.width = view->width;
	listView.height = view->height;
	listView.instance = &winInstData;
	comboBoxData->listBox = TheWindowManager->gogoGadgetListBox(&listView,
		comboBoxData->listboxData, winInstData.m_font, false);
	comboBoxData->listBox->winHide(true);

	delete comboBoxData->listboxData;
	comboBoxData->listboxData = (ListboxData *)comboBoxData->listBox->winGetUserData();
	comboBoxData->listBox->rva003148A2(view->instance->getTooltipText());
	comboBoxData->listBox->setTooltipDelay(comboBox->getTooltipDelay());

	GadgetListBoxSetAudioFeedback(comboBoxData->listBox, true);

	// initialize the combo box's variables and the controls with them
	GadgetComboBoxSetIsEditable(comboBox, comboBoxData->isEditable);
	GadgetComboBoxSetMaxChars(comboBox, comboBoxData->maxChars);
	GadgetComboBoxSetMaxDisplay(comboBox, comboBoxData->maxDisplay);

	// initialize the control's text colors
	Color color, border;
	color = comboBox->winGetEnabledTextColor();
	border = comboBox->winGetEnabledTextBorderColor();
	if (comboBoxData->listBox)
		comboBoxData->listBox->winSetEnabledTextColors(color, border);
	if (comboBoxData->editBox)
		comboBoxData->editBox->winSetEnabledTextColors(color, border);

	color = comboBox->winGetDisabledTextColor();
	border = comboBox->winGetDisabledTextBorderColor();
	if (comboBoxData->listBox)
		comboBoxData->listBox->winSetDisabledTextColors(color, border);
	if (comboBoxData->editBox)
		comboBoxData->editBox->winSetDisabledTextColors(color, border);

	color = comboBox->winGetHiliteTextColor();
	border = comboBox->winGetHiliteTextBorderColor();
	if (comboBoxData->listBox)
		comboBoxData->listBox->winSetHiliteTextColors(color, border);
	if (comboBoxData->editBox)
		comboBoxData->editBox->winSetHiliteTextColors(color, border);

	comboBoxData->dontHide = false;

	// assign the default images/colors
	assignDefaultGadgetLook(comboBox, defaultFont, defaultVisual);

	return comboBox;
}
