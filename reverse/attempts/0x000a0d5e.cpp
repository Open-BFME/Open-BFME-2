// ?Rva000A0D5EDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.95 date=2026-10-04
// cl: /Ireference/shims/bfme2gwm /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ?Rva000A0D5EDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z @0x000A0D5E 493B: progress bar draw.
// Vtable 0x00BC8D04 slot 3 via Rva000A12E6Window::draw; system GadgetProgressBarSystem.
// Evidence: rowed winGetUserData winGetScreenPosition winGetSize winGetStatus; status bit 8 and state bit 2;
// disabled/hilite/enabled colors at +0xB8/+0xBC/+0xE8/+0xEC +0x124/+0x128/+0x154/+0x158 +0x4C/+0x50/+0x7C/+0x80;
// manager winOpenRect 0x110 winFillRect 0x10C winDrawLine 0x114 with 1.0f and -1/0xFFC8C8C8; donor BFME1 W3DProgressBar.cpp W3DGadgetProgressBarDraw.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

class Image;
class GameWindow;
class WinInstanceData;

struct ICoord2D
{
	Int x;
	Int y;
};

struct BfmeWinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	UnsignedInt winGetStatus(void);
	void *winGetUserData(void);

	Color winGetEnabledColor(Int index)
	{
		return m_enabledDrawData[index].color;
	}
	Color winGetEnabledBorderColor(Int index)
	{
		return m_enabledDrawData[index].borderColor;
	}
	Color winGetDisabledColor(Int index)
	{
		return m_disabledDrawData[index].color;
	}
	Color winGetDisabledBorderColor(Int index)
	{
		return m_disabledDrawData[index].borderColor;
	}
	Color winGetHiliteColor(Int index)
	{
		return m_hiliteDrawData[index].color;
	}
	Color winGetHiliteBorderColor(Int index)
	{
		return m_hiliteDrawData[index].borderColor;
	}

private:
	unsigned char m_unreconstructed_00[0x48];
	BfmeWinDrawData m_enabledDrawData[9];
	BfmeWinDrawData m_disabledDrawData[9];
	BfmeWinDrawData m_hiliteDrawData[9];
};

class WinInstanceData
{
public:
	UnsignedInt getState(void) const { return m_state; }

private:
	unsigned char m_unreconstructed_00[0x08];
	UnsignedInt m_state;
};

class GameWindowManager
{
public:
	virtual void unused00(void);
	virtual void unused01(void);
	virtual void unused02(void);
	virtual void unused03(void);
	virtual void unused04(void);
	virtual void unused05(void);
	virtual void unused06(void);
	virtual void unused07(void);
	virtual void unused08(void);
	virtual void unused09(void);
	virtual void unused10(void);
	virtual void unused11(void);
	virtual void unused12(void);
	virtual void unused13(void);
	virtual void unused14(void);
	virtual void unused15(void);
	virtual void unused16(void);
	virtual void unused17(void);
	virtual void unused18(void);
	virtual void unused19(void);
	virtual void unused20(void);
	virtual void unused21(void);
	virtual void unused22(void);
	virtual void unused23(void);
	virtual void unused24(void);
	virtual void unused25(void);
	virtual void unused26(void);
	virtual void unused27(void);
	virtual void unused28(void);
	virtual void unused29(void);
	virtual void unused30(void);
	virtual void unused31(void);
	virtual void unused32(void);
	virtual void unused33(void);
	virtual void unused34(void);
	virtual void unused35(void);
	virtual void unused36(void);
	virtual void unused37(void);
	virtual void unused38(void);
	virtual void unused39(void);
	virtual void unused40(void);
	virtual void unused41(void);
	virtual void unused42(void);
	virtual void unused43(void);
	virtual void unused44(void);
	virtual void unused45(void);
	virtual void unused46(void);
	virtual void unused47(void);
	virtual void unused48(void);
	virtual void unused49(void);
	virtual void unused50(void);
	virtual void unused51(void);
	virtual void unused52(void);
	virtual void unused53(void);
	virtual void unused54(void);
	virtual void unused55(void);
	virtual void unused56(void);
	virtual void unused57(void);
	virtual void unused58(void);
	virtual void unused59(void);
	virtual void unused60(void);
	virtual void unused61(void);
	virtual void unused62(void);
	virtual void unused63(void);
	virtual void unused64(void);
	virtual void unused65(void);
	virtual void unused66(void);
	virtual void winFillRect(Color color, Real width, Int startX, Int startY, Int endX, Int endY);
	virtual void winOpenRect(Color color, Real width, Int startX, Int startY, Int endX, Int endY);
	virtual void winDrawLine(Color color, Real width, Int startX, Int startY, Int endX, Int endY);
};

extern GameWindowManager *TheWindowManager;

enum
{
	WIN_STATUS_ENABLED = 0x00000008,
	WIN_STATE_HILITED = 0x00000002,
	WIN_COLOR_UNDEFINED = 0x00ffffff
};

inline Int BitTest(UnsignedInt bits, UnsignedInt mask)
{
	return (bits & mask) != 0;
}

#define WIN_DRAW_LINE_WIDTH 1.0f

inline Color GadgetProgressBarGetEnabledColor(GameWindow *g) { return g->winGetEnabledColor(0); }
inline Color GadgetProgressBarGetEnabledBorderColor(GameWindow *g) { return g->winGetEnabledBorderColor(0); }
inline Color GadgetProgressBarGetEnabledBarColor(GameWindow *g) { return g->winGetEnabledColor(4); }
inline Color GadgetProgressBarGetEnabledBarBorderColor(GameWindow *g) { return g->winGetEnabledBorderColor(4); }
inline Color GadgetProgressBarGetDisabledColor(GameWindow *g) { return g->winGetDisabledColor(0); }
inline Color GadgetProgressBarGetDisabledBorderColor(GameWindow *g) { return g->winGetDisabledBorderColor(0); }
inline Color GadgetProgressBarGetDisabledBarColor(GameWindow *g) { return g->winGetDisabledColor(4); }
inline Color GadgetProgressBarGetDisabledBarBorderColor(GameWindow *g) { return g->winGetDisabledBorderColor(4); }
inline Color GadgetProgressBarGetHiliteColor(GameWindow *g) { return g->winGetHiliteColor(0); }
inline Color GadgetProgressBarGetHiliteBorderColor(GameWindow *g) { return g->winGetHiliteBorderColor(0); }
inline Color GadgetProgressBarGetHiliteBarColor(GameWindow *g) { return g->winGetHiliteColor(4); }
inline Color GadgetProgressBarGetHiliteBarBorderColor(GameWindow *g) { return g->winGetHiliteBorderColor(4); }

// ?Rva000A0D5EDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z present-unmatched
void Rva000A0D5EDraw(GameWindow *window, WinInstanceData *instData)
{
	ICoord2D origin, size, start, end;
	Color backColor, backBorder, barColor, barBorder;
	Int progress = (Int)window->winGetUserData();

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	if (BitTest(window->winGetStatus(), WIN_STATUS_ENABLED) == 0)
	{
		backColor = GadgetProgressBarGetDisabledColor(window);
		backBorder = GadgetProgressBarGetDisabledBorderColor(window);
		barColor = GadgetProgressBarGetDisabledBarColor(window);
		barBorder = GadgetProgressBarGetDisabledBarBorderColor(window);
	}
	else if (BitTest(instData->getState(), WIN_STATE_HILITED))
	{
		backColor = GadgetProgressBarGetHiliteColor(window);
		backBorder = GadgetProgressBarGetHiliteBorderColor(window);
		barColor = GadgetProgressBarGetHiliteBarColor(window);
		barBorder = GadgetProgressBarGetHiliteBarBorderColor(window);
	}
	else
	{
		backColor = GadgetProgressBarGetEnabledColor(window);
		backBorder = GadgetProgressBarGetEnabledBorderColor(window);
		barColor = GadgetProgressBarGetEnabledBarColor(window);
		barBorder = GadgetProgressBarGetEnabledBarBorderColor(window);
	}

	if (backBorder != WIN_COLOR_UNDEFINED)
	{
		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect(backBorder, WIN_DRAW_LINE_WIDTH, start.x, start.y, end.x, end.y);
	}

	if (backColor != WIN_COLOR_UNDEFINED)
	{
		start.x = origin.x + 1;
		start.y = origin.y + 1;
		end.x = start.x + size.x - 2;
		end.y = start.y + size.y - 2;
		TheWindowManager->winFillRect(backColor, WIN_DRAW_LINE_WIDTH, start.x, start.y, end.x, end.y);
	}

	if (progress)
	{
		if (barBorder != WIN_COLOR_UNDEFINED)
		{
			start.x = origin.x;
			start.y = origin.y;
			end.x = start.x + (size.x * progress) / 100;
			end.y = start.y + size.y;
			if (end.x - start.x > 1)
			{
				TheWindowManager->winOpenRect(barBorder, WIN_DRAW_LINE_WIDTH, start.x, start.y, end.x, end.y);
			}
		}

		if (barColor != WIN_COLOR_UNDEFINED)
		{
			start.x = origin.x + 1;
			start.y = origin.y + 1;
			end.x = start.x + (size.x * progress) / 100 - 2;
			end.y = start.y + size.y - 2;
			if (end.x - start.x > 1)
			{
				TheWindowManager->winFillRect(barColor, WIN_DRAW_LINE_WIDTH, start.x, start.y, end.x, end.y);
				TheWindowManager->winDrawLine((Color)0xffffffff, WIN_DRAW_LINE_WIDTH, start.x, start.y, end.x, start.y);
				TheWindowManager->winDrawLine((Color)0xffc8c8c8, WIN_DRAW_LINE_WIDTH, start.x, start.y, start.x, end.y);
			}
		}
	}
}
