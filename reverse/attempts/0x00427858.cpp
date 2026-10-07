// ?IMECandidateMainDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.99 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?IMECandidateMainDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z @0x00427858 222B.
// Donor provenance: FunctionLexicon and GUICallbacks/IMECandidate.cpp name this callback and define its drawing behavior.
// Target evidence: registered neighbor string IMECandidateMainDraw; retail branches on enabled/hilited state and uses the measured color pairs at GameWindow +0x4C/+0x50, +0xB8/+0xBC, and +0x124/+0x128.

typedef unsigned int Color;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct ICoord2D
{
	Int x;
	Int y;
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66)
#undef V
	virtual void winFillRect(Color color, Real opacity, Int left, Int top, Int right, Int bottom) = 0;
	virtual void winOpenRect(Color color, Real width, Int left, Int top, Int right, Int bottom) = 0;
};

extern GameWindowManager *TheWindowManager;

class GameWindow
{
public:
	virtual void vtableAnchor();
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	UnsignedInt winGetStatus();
	Int winGetEnabledColor(Int) const { return m_enabledColor; }
	Int winGetEnabledBorderColor(Int) const { return m_enabledBorderColor; }
	Int winGetDisabledColor(Int) const { return m_disabledColor; }
	Int winGetDisabledBorderColor(Int) const { return m_disabledBorderColor; }
	Int winGetHiliteColor(Int) const { return m_hiliteColor; }
	Int winGetHiliteBorderColor(Int) const { return m_hiliteBorderColor; }

private:
	void *m_positionSink;
	UnsignedInt m_status;
	Int m_sizeX;
	Int m_sizeY;
	char m_pad14[0x4c - 0x14];
	Int m_enabledColor;
	Int m_enabledBorderColor;
	char m_pad54[0xb8 - 0x54];
	Int m_disabledColor;
	Int m_disabledBorderColor;
	char m_padC0[0x124 - 0xc0];
	Int m_hiliteColor;
	Int m_hiliteBorderColor;
};

class WinInstanceData
{
public:
	UnsignedInt getState() const { return m_state; }

private:
	char m_pad00[8];
	UnsignedInt m_state;
};

enum
{
	WIN_STATUS_ENABLED = 8,
	WIN_STATE_HILITED = 2,
	WIN_COLOR_UNDEFINED = 0xffffff
};

#define BitTest(value, mask) (((value) & (mask)) != 0)

void IMECandidateMainDraw(GameWindow *window, WinInstanceData *instData)
{
	ICoord2D origin, size, start, end;
	Color backColor;
	Color backBorder;
	Real borderWidth = 1.0f;

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	if (BitTest(window->winGetStatus(), WIN_STATUS_ENABLED) == 0)
	{
		backColor = window->winGetDisabledColor(0);
		backBorder = window->winGetDisabledBorderColor(0);
	}
	else if (BitTest(instData->getState(), WIN_STATE_HILITED))
	{
		backColor = window->winGetHiliteColor(0);
		backBorder = window->winGetHiliteBorderColor(0);
	}
	else
	{
		backColor = window->winGetEnabledColor(0);
		backBorder = window->winGetEnabledBorderColor(0);
	}

	if (backBorder != WIN_COLOR_UNDEFINED)
	{
		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect(backBorder, borderWidth, start.x, start.y, end.x, end.y);
	}

	if (backColor != WIN_COLOR_UNDEFINED)
	{
		start.x = origin.x + 1;
		start.y = origin.y + 1;
		end.x = start.x + size.x - 2;
		end.y = start.y + size.y - 2;
		TheWindowManager->winFillRect(backColor, 0.0f, start.x, start.y, end.x, end.y);
	}
}
