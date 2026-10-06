// cl: /ICode/GameEngine/Source/GameClient/GUI /O1 /G7 /MD /EHsc /DNDEBUG
// GadgetListboxCreateScrollbar, retail 0x0032449E (677 B, Ghidra boundary).
// Its one caller, gogoGadgetListBox (0x002C1395), calls it only when the list
// data's scrollBar flag (+0xA) is set. Body: Zero Hour GadgetListBox.cpp's
// routine as BFME1 carries it (game/.../Gadget/GadgetListboxCreateScrollbar.cpp
// at 177ae72d) on BFME2's one-record factory ABI: the record is built by the
// out-of-line GadgetCreateView zeroer (0x0022239C), the thumb buttons scale
// 21x22 by the resolution at TheWritableGlobalData+0x30/+0x34 (BFME1: +0x2C/
// +0x30), init() is called directly, and the slider factory is slot 25 with
// the four-argument record ABI of the rowed gogoGadgetSlider. Target facts:
// list data upButton/downButton/slider at +0x1C/+0x20/+0x24, push button slot
// 19 (+0x4C), winFontHeight slot 72 (+0x120), the rowed 150-tick helper
// Rva004BCB20 (0x00328543) on both buttons.
#include <string.h>
#include "GameWindowManagerRecordView.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class GameWindow
{
public:
	void *winGetUserData(void);
	UnsignedInt winGetStatus(void);
	Int winGetSize(Int *width, Int *height);
	Int winGetTextLength(void);
	GameFont *winGetFont(void);
	UnsignedInt winGetStyle(void);
};

class WinInstanceData
{
public:
	WinInstanceData();
	virtual ~WinInstanceData();
	void init();

	UnsignedInt m_id;			// +0x04
	UnsignedInt m_state;		// +0x08
	UnsignedInt m_style;		// +0x0C
	UnsignedInt m_status;		// +0x10
	GameWindow *m_owner;		// +0x14
	unsigned char m_pad18[0x1A8 - 0x18];
};

struct ListboxData
{
	unsigned char m_pad00[0xA];
	Bool scrollBar;				// +0x0A
	unsigned char m_pad0B[0x1C - 0xB];
	GameWindow *upButton;		// +0x1C
	GameWindow *downButton;		// +0x20
	GameWindow *slider;			// +0x24
};

struct SliderData
{
	Int minVal;
	Int maxVal;
	float numTicks;
	Int position;
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18)
	virtual GameWindow *gogoGadgetPushButton(GadgetCreateView *view, GameFont *font, Bool visual) = 0;
	V(20) V(21) V(22) V(23) V(24)
	virtual GameWindow *gogoGadgetSlider(GadgetCreateView *view, SliderData *data, GameFont *font, Bool visual) = 0;
	V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
	virtual Int winFontHeight(GameFont *font) = 0;
#undef V
};
extern GameWindowManager *TheWindowManager;

class GlobalData
{
public:
	unsigned char m_pad00[0x30];
	Int m_xResolution;			// +0x30
	Int m_yResolution;			// +0x34
};
extern GlobalData *TheWritableGlobalData;

void Rva004BCB20(GameWindow *window, Int value);

enum
{
	WIN_STATUS_ACTIVE = 0x1,
	WIN_STATUS_ENABLED = 0x8,
	WIN_STATUS_HIDDEN = 0x10,
	WIN_STATUS_IMAGE = 0x80,
	WIN_STATUS_BORDER = 0x200,
	WIN_STATUS_NO_INPUT = 0x1000,
	GWS_PUSH_BUTTON = 0x1,
	GWS_VERT_SLIDER = 0x8,
	GWS_MOUSE_TRACK = 0x400
};

void GadgetListboxCreateScrollbar(GameWindow *listbox)
{
	ListboxData *listData = (ListboxData *)listbox->winGetUserData();
	WinInstanceData winInstData;
	SliderData sData = { 0 };
	Int fontHeight;
	Int top;
	Int bottom;
	UnsignedInt status = listbox->winGetStatus();
	Bool title = false;
	Int width, height;

	listbox->winGetSize(&width, &height);

	// do we have a title
	if (listbox->winGetTextLength())
		title = true;

	// remove unwanted status bits
	status &= ~(WIN_STATUS_BORDER | WIN_STATUS_HIDDEN | WIN_STATUS_NO_INPUT);

	fontHeight = TheWindowManager->winFontHeight(listbox->winGetFont());
	top = title ? (fontHeight + 1) : 0;
	bottom = title ? (height - (fontHeight + 1)) : height;

	// initialize instData
	winInstData.init();

	// size of button
	GadgetCreateView button;
	button.width = 21;
	button.height = 22;
	button.width = TheWritableGlobalData->m_xResolution * button.width / 1024;
	button.height = TheWritableGlobalData->m_yResolution * button.height / 768;

	// set the owner and style
	status |= WIN_STATUS_IMAGE;
	winInstData.m_owner = listbox;
	winInstData.m_style = GWS_PUSH_BUTTON;

	// if listbox tracks, so will this
	if (listbox->winGetStyle() & GWS_MOUSE_TRACK)
		winInstData.m_style |= GWS_MOUSE_TRACK;

	// create the up button
	UnsignedInt buttonStatus = status | WIN_STATUS_ACTIVE | WIN_STATUS_ENABLED;
	status = buttonStatus;
	button.parent = listbox;
	button.status = buttonStatus;
	button.x = width - button.width - 2;
	button.y = top + 2;
	button.instance = &winInstData;
	listData->upButton = TheWindowManager->gogoGadgetPushButton(&button, 0, true);

	// create the down button
	winInstData.init();
	winInstData.m_style = GWS_PUSH_BUTTON;
	winInstData.m_owner = listbox;
	if (listbox->winGetStyle() & GWS_MOUSE_TRACK)
		winInstData.m_style |= GWS_MOUSE_TRACK;

	button.y = top + bottom - button.height - 2;
	listData->downButton = TheWindowManager->gogoGadgetPushButton(&button, 0, true);

	// create the slider
	GadgetCreateView slide;
	slide.width = button.width;
	slide.height = bottom - (2 * button.height) - 6;
	winInstData.init();
	winInstData.m_style = GWS_VERT_SLIDER;
	winInstData.m_owner = listbox;
	if (listbox->winGetStyle() & GWS_MOUSE_TRACK)
		winInstData.m_style |= GWS_MOUSE_TRACK;

	memset(&sData, 0, sizeof(SliderData));

	slide.parent = listbox;
	slide.status = status;
	slide.x = width - slide.width - 2;
	slide.y = top + button.height + 3;
	slide.instance = &winInstData;
	listData->slider = TheWindowManager->gogoGadgetSlider(&slide, &sData, 0, true);

	Rva004BCB20(listData->upButton, 150);
	Rva004BCB20(listData->downButton, 150);

	listData->scrollBar = true;
}
