// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// GameWindow::winGetStatus (retail 0x0030F45F, 4 bytes) and
// GameWindow::winSetUserData (retail 0x002B2210, 10 bytes): Zero Hour
// GameWindow.cpp accessors of m_status (+0x08, the offset GameWindowHide.cpp's
// rowed winSetStatus/winHide use) and m_userData (+0x2C, the offset the rowed
// winGetUserData reads). The GUI units that call them pin both names at these
// addresses. Retail folded each with an identical one-instruction accessor:
// winGetStatus lands as the ICF alias of the rowed
// CategoryModuleClass<1>::getName; winSetUserData replaces a gen-alias
// placeholder (Matrix3D::Set_Z_Translation's identical bytes).

typedef unsigned int UnsignedInt;
typedef int Int;
typedef int Color;
class GameFont;
class WinInstanceData;

class GameWindow
{
public:
	UnsignedInt winGetStatus(void);
	void winSetUserData(void *data);
	UnsignedInt winGetStyle(void);
	GameWindow *winGetParent(void);
	GameWindow *winGetChild(void);
	Int winGetWindowId(void);
	Color winGetEnabledTextColor(void);
	Color winGetEnabledTextBorderColor(void);
	Color winGetDisabledTextColor(void);
	Color winGetDisabledTextBorderColor(void);
	Color winGetHiliteTextColor(void);
	Color winGetHiliteTextBorderColor(void);
	GameFont *winGetFont(void);
	WinInstanceData *winGetInstanceData(void);
	GameWindow *winGetNext(void);
	GameWindow *winGetPrev(void);
	Int winNextTab(void);
	Int winPrevTab(void);
	GameWindow *winGetOwner(void);

private:
	char m_pad00[0x08];
	UnsignedInt m_status;	// +0x08
	char m_pad0C[0x20];
	void *m_userData;		// +0x2C
	// m_instData (WinInstanceData) begins at +0x30; the id, style and owner
	// below are its fields.
	char m_instData30[0x04];
	Int m_id;				// +0x34
	char m_pad38[0x04];
	UnsignedInt m_style;	// +0x3C
	char m_pad40[0x04];
	GameWindow *m_owner;	// +0x44
	char m_pad48[0x144];
	Color m_textColor[6];	// +0x18C enabled, enabled border, disabled,
							//        disabled border, hilite, hilite border
	char m_pad1A4[0x10];
	GameFont *m_font;		// +0x1B4
	char m_pad1B8[0x40];
	GameWindow *m_next;		// +0x1F8
	GameWindow *m_prev;		// +0x1FC
	GameWindow *m_parent;	// +0x200
	GameWindow *m_child;	// +0x204
};

UnsignedInt GameWindow::winGetStatus(void)
{
	return m_status;
}

void GameWindow::winSetUserData(void *data)
{
	m_userData = data;
}

// winGetStyle (0x005C4AF1, +0x3C), winGetParent (0x003140A4, +0x200) and
// winGetChild (0x003140C8, +0x204): pinned at those addresses by the GUI
// callers; m_parent and m_child are adjacent as in Zero Hour's GameWindow.h.
// Each is folded with an identical one-load getter already rowed there.
UnsignedInt GameWindow::winGetStyle(void)
{
	return m_style;
}

GameWindow *GameWindow::winGetParent(void)
{
	return m_parent;
}

GameWindow *GameWindow::winGetChild(void)
{
	return m_child;
}

// The window id (+0x34), the six text colours (+0x18C..+0x1A0) and the font
// (+0x1B4): each pinned by its GUI callers at a one-load getter that retail
// folded with an identical one already rowed.
Int GameWindow::winGetWindowId(void) { return m_id; }
Color GameWindow::winGetEnabledTextColor(void) { return m_textColor[0]; }
Color GameWindow::winGetEnabledTextBorderColor(void) { return m_textColor[1]; }
Color GameWindow::winGetDisabledTextColor(void) { return m_textColor[2]; }
Color GameWindow::winGetDisabledTextBorderColor(void) { return m_textColor[3]; }
Color GameWindow::winGetHiliteTextColor(void) { return m_textColor[4]; }
Color GameWindow::winGetHiliteTextBorderColor(void) { return m_textColor[5]; }
GameFont *GameWindow::winGetFont(void) { return m_font; }

// winGetInstanceData (0x00314046, lea +0x30), winGetNext (0x003140F1,
// +0x1F8, just before m_prev/m_parent/m_child as in Zero Hour) and
// winGetOwner (0x005C4AF9, +0x44): pinned by their callers at one-instruction
// getters retail folded with identical rowed ones.
WinInstanceData *GameWindow::winGetInstanceData(void) { return reinterpret_cast<WinInstanceData *>(m_instData30); }
GameWindow *GameWindow::winGetNext(void) { return m_next; }
GameWindow *GameWindow::winGetOwner(void) { return m_owner; }

// winGetPrev (0x00314105, +0x1FC, between m_next and m_parent): pinned by
// GadgetTabControlFixupSubPaneList; folded with the identical rowed getter.
GameWindow *GameWindow::winGetPrev(void) { return m_prev; }

// winNextTab and winPrevTab: GadgetStaticTextInput (0x003213F0) calls both
// where its donor does, and both sites land on 0x000D43D0, the shared
// xor eax,eax / ret body. Zero Hour's tab walk is gone from BFME2; both
// return 0.
Int GameWindow::winNextTab(void) { return 0; }
Int GameWindow::winPrevTab(void) { return 0; }
