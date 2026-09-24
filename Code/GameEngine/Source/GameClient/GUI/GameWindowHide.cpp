// cl: /O1 /DNDEBUG /MD /G7

// GameWindow::winHide, retail 0x00313C64 (117B).
// Ported from Open-BFME-1 GameWindowFields.cpp donor (GameWindow::winHide,
// BFME1 0x00478390) with BFME2 repairs: m_status at +0x08, TheWindowManager
// at 0xDFEF1C, windowHiding at manager slot 40 (0xA0), winSendSystemMsg at
// slot 58 (0xE8), plus a BFME2-only second winSendSystemMsg(this, 0x1C,
// 0x10, hiddenBit). /G7 is load-bearing: it emits retail or-al/early-push
// where /O1-/O2/G6 keep dword-RMW/late-push (VID/BVID precedent).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

enum
{
	WIN_ERR_OK = 0
};

class GameWindow;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	virtual void windowHiding(GameWindow *window) = 0;
	V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	virtual GameWindow *winGetFocus() = 0;
	virtual Int winSetFocus(GameWindow *window) = 0;
	V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
};

extern GameWindowManager *TheWindowManager;

class GameWindow
{
public:
	Int winHide(bool hide);
	UnsignedInt winSetStatus(UnsignedInt status);
	Int winEnable(bool enable);

private:
	unsigned char m_pad0[0x08];
	UnsignedInt m_status;
	unsigned char m_padC[0x1EC];
	GameWindow *m_next;
	unsigned char m_pad1FC[8];
	GameWindow *m_child;
};

// ?winHide@GameWindow@@QAEH_N@Z, retail 0x00313C64 (117B).
Int GameWindow::winHide(bool hide)
{
	UnsignedInt oldStatus = m_status;

	if (hide)
	{
		m_status |= 0x10;
		TheWindowManager->windowHiding(this);
	}
	else
	{
		m_status &= ~0x10;
	}

	if (m_status != oldStatus)
		TheWindowManager->winSendSystemMsg(this, 0x1B, !hide, 0);

	m_status &= ~0x10000000;

	TheWindowManager->winSendSystemMsg(this, 0x1C, 0x10, (m_status >> 4) & 1);

	return WIN_ERR_OK;
}

// ?winSetStatus@GameWindow@@QAEII@Z, retail 0x00313CE3 (15B).
UnsignedInt GameWindow::winSetStatus(UnsignedInt status)
{
	UnsignedInt oldStatus = m_status;
	m_status |= status;
	return oldStatus;
}

// ?winEnable@GameWindow@@QAEH_N@Z, retail 0x00313BEC (120B).
// Ported from Open-BFME-1 GameWindowFields.cpp donor (GameWindow::winEnable,
// BFME1 0x00478390) with BFME2 repairs: the trailing winSendSystemMsg is
// unconditional with (0x1C / 8 / enabled-bit) in place of the donor
// conditional (0x1C / enable / 0) and m_child sits at +0x204 with m_next at
// +0x1F8 per retail bytes. Focus slots are winGetFocus at 0xC0 and
// winSetFocus at 0xC4. WIN_STATUS_ENABLED is 0x08.
Int GameWindow::winEnable(bool enable)
{
	GameWindow *child;

	if (enable)
	{
		m_status |= 0x08;
	}
	else
	{
		m_status &= ~0x08;

		if (TheWindowManager->winGetFocus() == this)
			TheWindowManager->winSetFocus(0);
	}

	for (child = m_child; child; child = child->m_next)
		child->winEnable(enable);

	TheWindowManager->winSendSystemMsg(this, 0x1C, 8, (m_status >> 3) & 1);

	return WIN_ERR_OK;
}
