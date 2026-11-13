// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ??1Mouse@@UAE@XZ, retail 0x001EE3DE, 165 bytes.
// Virtual dtor: vtable 0x007E0358, manual release of ptr at +0x4FA8 via
// DisplayManager global 0x009FEAD8 slot 0x3C (FreeEntry, Rva0025FC61 precedent),
// Wide strings at +0x1300/+0x12FC/+0x12F8 and narrow at +0x126C via
// releaseBuffer, CursorInfo[0x54] array at +0xC via ??_M, base
// SubsystemInterface dtor. Evidence: ??_G caller; no donor.
#include <string.h>
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

class DisplayManager
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void FreeEntry(void *p);
};

extern class DisplayStringManager *TheDisplayStringManager;

#include "../../../Include/Common/CursorInfo.h"

#include "../../../Include/Common/RGBAColorInt.h"

// ZH MouseIO, 0x3C bytes in BFME2; its empty constructor is the ICF-folded
// `mov eax,ecx; ret` at 0x0047A6A9 that ??_H receives.
struct MouseIO {
	MouseIO() {}
	unsigned int m_data[0x3C / 4];
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct GlobalDataWinCursorsView {
	unsigned char m_pad[0x9C6];
	bool m_winCursors;
};

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

// Retail identity is Mouse (vtable 0x00BE0358 is written by both the ctor
// 0x001EEC97 and the dtor 0x001EE3DE, which share one ICF-folded FuncInfo
// handler; Win32Mouse's ctor and dtor 0x000419E3 call them). Mouse.cpp keeps
// the ZH-layout methods but no longer defines the ctor/dtor or needs ??_7Mouse.
class Mouse : public SubsystemInterface
{
public:
	Mouse();
	virtual ~Mouse();

private:
	CursorInfo m_arr0C[0x38];
	AsciiString m_tooltipFontName;			// 0x126C
	int m_tooltipFontSize;					// 0x1270
	bool m_tooltipFontIsBold;				// 0x1274
	bool m_tooltipAnimateBackground;		// 0x1275
	int m_tooltipFillTime;					// 0x1278
	int m_tooltipDelayTime;					// 0x127C
	float m_tooltipWidth;					// 0x1280
	float m_lastTooltipWidth;				// 0x1284
	bool m_buttonActivity;					// 0x1288
	RGBAColorInt m_tooltipColorText;		// 0x128C
	RGBAColorInt m_tooltipColorHighlight;	// 0x129C
	RGBAColorInt m_tooltipColorShadow;		// 0x12AC
	RGBAColorInt m_tooltipColorBackground;	// 0x12BC
	RGBAColorInt m_tooltipColorBorder;		// 0x12CC
	int m_currentRedrawMode;				// 0x12DC
	bool m_useTooltipAltTextColor;			// 0x12E0
	bool m_useTooltipAltBackColor;			// 0x12E1
	bool m_adjustTooltipAltColor;			// 0x12E2
	bool m_orthoCamera;						// 0x12E3
	float m_orthoZoom;						// 0x12E4
	unsigned int m_dragTolerance;			// 0x12E8
	unsigned int m_dragTolerance3D;			// 0x12EC
	unsigned int m_dragToleranceMS;			// 0x12F0
	unsigned char m_numButtons;				// 0x12F4
	unsigned char m_numAxes;				// 0x12F5
	bool m_forceFeedback;					// 0x12F6
	UnicodeString m_str12F8;
	UnicodeString m_tooltipString;			// 0x12FC
	UnicodeString m_str1300;
	void *m_tooltipDisplayString;			// 0x1304
	bool m_displayTooltip;					// 0x1308
	bool m_isTooltipEmpty;					// 0x1309
	MouseIO m_mouseEvents[256];				// 0x130C
	MouseIO m_currMouse;					// 0x4F0C
	MouseIO m_prevMouse;					// 0x4F48
	int m_minX;								// 0x4F84
	int m_maxX;
	int m_minY;
	int m_maxY;
	unsigned int m_inputFrame;				// 0x4F94
	unsigned int m_deadInputFrame;			// 0x4F98
	bool m_inputMovesAbsolute;				// 0x4F9C
	bool m_visible;							// 0x4F9D
	bool m_flag4F9E;
	bool m_flag4F9F;
	bool m_flag4FA0;
	bool m_flag4FA1;
	int m_currentCursor;					// 0x4FA4
	void *m_cursorTextDisplayString;		// 0x4FA8
	RGBAColorInt m_cursorTextColor;			// 0x4FAC
	RGBAColorInt m_cursorTextDropColor;		// 0x4FBC
	int m_tooltipDelay;						// 0x4FCC
	int m_highlightPos;						// 0x4FD0
	unsigned int m_highlightUpdateStart;	// 0x4FD4
	unsigned int m_stillTime;				// 0x4FD8
	RGBAColorInt m_tooltipTextColor;		// 0x4FDC
	RGBAColorInt m_tooltipBackColor;		// 0x4FEC
	int m_eventsThisFrame;					// 0x4FFC
	int m_leftClickAge;						// 0x5000
	int m_rightClickAge;					// 0x5004
	bool m_flag5008;
	bool m_flag5009;
	int m_value500C;						// 0x500C
};

// ??0Mouse@@QAE@XZ, retail 0x001EEC97, 799 bytes: Mouse::Mouse. ZH's
// statement order with BFME2's added members (0x4F9E..0x4FA1, 0x5000..0x500C)
// and the explicit tooltip-string clears.
Mouse::Mouse()
{
	m_numButtons = 0;
	m_numAxes = 0;
	m_forceFeedback = false;

	m_dragTolerance = 0;
	m_dragTolerance3D = 0;
	m_dragToleranceMS = 0;

	m_flag4F9F = false;
	m_flag4FA0 = false;
	m_flag4FA1 = false;

	m_displayTooltip = false;
	m_tooltipString.clear();
	m_str1300.clear();
	m_tooltipDisplayString = 0;
	m_tooltipDelay = -1;
	m_buttonActivity = false;

	memset(m_mouseEvents, 0, sizeof(m_mouseEvents));
	memset(&m_currMouse, 0, sizeof(m_currMouse));
	memset(&m_prevMouse, 0, sizeof(m_prevMouse));

	m_minX = 0;
	m_maxX = 0;
	m_minY = 0;
	m_maxY = 0;
	m_eventsThisFrame = 0;

	m_inputFrame = 0;
	m_deadInputFrame = 0;

	m_inputMovesAbsolute = false;

	m_currentCursor = 2;
	if (TheWritableGlobalData && ((GlobalDataWinCursorsView *)TheWritableGlobalData)->m_winCursors)
		m_currentRedrawMode = 0;
	else
		m_currentRedrawMode = 1;
	m_visible = false;
	m_flag4F9E = true;
	m_tooltipFontName = "Times New Roman";
	m_tooltipFontSize = 12;
	m_tooltipFontIsBold = false;
	m_tooltipAnimateBackground = true;
	m_tooltipFillTime = 50;
	m_tooltipDelayTime = 50;

#define setColor(x, r, g, b, a) { x.red = r; x.green = g; x.blue = b; x.alpha = a; }
	setColor(m_tooltipColorText, 220, 220, 220, 255);
	setColor(m_tooltipColorHighlight, 255, 255, 0, 255);
	setColor(m_tooltipColorShadow, 0, 0, 0, 255);
	setColor(m_tooltipColorBackground, 20, 20, 0, 127);
	setColor(m_tooltipColorBorder, 0, 0, 0, 255);
#undef setColor

	m_tooltipWidth = 15.0f;
	m_lastTooltipWidth = 0.0f;

	m_useTooltipAltTextColor = false;
	m_useTooltipAltBackColor = false;
	m_adjustTooltipAltColor = false;

	m_orthoCamera = false;
	m_orthoZoom = 1.0f;

	m_isTooltipEmpty = true;

	m_cursorTextDisplayString = 0;
	m_cursorTextColor.red = 255;
	m_cursorTextColor.green = 255;
	m_cursorTextColor.blue = 255;
	m_cursorTextColor.alpha = 255;
	m_cursorTextDropColor.red = 255;
	m_cursorTextDropColor.green = 255;
	m_cursorTextDropColor.blue = 255;
	m_cursorTextDropColor.alpha = 255;

	m_highlightPos = 0;
	m_highlightUpdateStart = 0;
	m_stillTime = 0;
	m_tooltipTextColor.red = 255;
	m_tooltipTextColor.green = 255;
	m_tooltipTextColor.blue = 255;
	m_tooltipTextColor.alpha = 255;
	m_tooltipBackColor.red = 0;
	m_tooltipBackColor.green = 0;
	m_tooltipBackColor.blue = 0;
	m_tooltipBackColor.alpha = 255;

	m_leftClickAge = -1;
	m_rightClickAge = -1;
	m_flag5008 = true;
	m_flag5009 = false;
	m_value500C = -1;
}

Mouse::~Mouse()
{
	if (m_cursorTextDisplayString != 0)
		(*(DisplayManager **)&TheDisplayStringManager)->FreeEntry(m_cursorTextDisplayString);
	m_cursorTextDisplayString = 0;
}
