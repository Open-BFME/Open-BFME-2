// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?translateGameMessage@AptTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z,
// retail 0x00432B18, 778-byte body plus its 44-byte switch tables (822B).
// Slot 0 of the AptTranslator vtable 0x00C3CA28 (slot 1 is the rowed deleting
// dtor 0x00432A1F), i.e. GameMessageTranslator::translateGameMessage; WB twin
// 0x012C98A0 (inlines AnyMouseButtonsDown). Target facts: a pending swallow
// flag (+0x1EC, set by message 0xC3) drops the next message; the per-button
// "down in Apt" bytes at +0x04 are indexed through the rowed classifier
// 0x0043289D; mouse-position messages time out stale buttons against
// TheMouse's MouseIO states (+0x4F0C) with counters +0x1F4/+0x1F8/+0x1FC;
// down/up messages set g_bfmeAptWindowManager +0x318 and call the rowed
// 0x00432A3B / 0x006CC9A0 helpers; unclaimed messages fall back to the
// first window with status bit 0x08000000 (walked through the +0x200 getter
// pinned as winGetParent). The rowed checker 0x0043287E returns a bool in AL
// (WB movzx al) though its row is spelled int, hence the byte casts.
#include <algorithm>

#include "../../../Include/Common/MessageStream.h"

struct MouseIO
{
	char m_pad00[0x18];
	int leftState;   // +0x18
	char m_pad1C[8];
	int rightState;  // +0x24
	char m_pad28[8];
	int middleState; // +0x30
};

#define MOUSE_SLOT(n) virtual void slot##n();
class Mouse
{
public:
	MOUSE_SLOT(00) MOUSE_SLOT(01) MOUSE_SLOT(02) MOUSE_SLOT(03) MOUSE_SLOT(04)
	MOUSE_SLOT(05) MOUSE_SLOT(06) MOUSE_SLOT(07) MOUSE_SLOT(08) MOUSE_SLOT(09)
	MOUSE_SLOT(10) MOUSE_SLOT(11) MOUSE_SLOT(12) MOUSE_SLOT(13) MOUSE_SLOT(14)
	MOUSE_SLOT(15) MOUSE_SLOT(16) MOUSE_SLOT(17)
	virtual void getCursorPosition(int *x, int *y); // slot 18 (+0x48)
	virtual void setCursor(int cursor);             // slot 19 (+0x4C)
	const MouseIO *getMouseStatus() const { return &m_currMouse; }
private:
	char m_pad04[0x4F0C - 4];
	MouseIO m_currMouse; // +0x4F0C
};
#undef MOUSE_SLOT
extern Mouse *TheMouse;

class BfmeAptWindowManager
{
public:
	char m_pad000[0x318];
	int m_mouseButtonMode; // +0x318
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class GameWindow
{
public:
	unsigned int winGetStatus();
	GameWindow *winGetParent();
	unsigned char winPointInWindow(int x, int y);
};
class GameWindowManager
{
public:
	char m_pad00[0x18];
	GameWindow *m_windowList; // +0x18
};
extern GameWindowManager *TheWindowManager;

enum GameWindowMessage { GWM_NONE = 0 };
GameWindowMessage rawMouseToWindowMessage(const GameMessage *msg);
int Rva0043289DClassify(int type);
void Rva006CC9A0(int a, int b, int c);

enum GameMessageDisposition { KEEP_MESSAGE = 0, DESTROY_MESSAGE = 1 };

static inline bool AnyMouseButtonsDown()
{
	const MouseIO *io = TheMouse->getMouseStatus();
	if (io && (io->leftState || io->rightState || io->middleState))
		return true;
	return false;
}

class GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg) = 0;
	virtual ~GameMessageTranslator() {}
};

class AptTranslator : public GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	int rva0043287E();
	void rva00432A3B(const GameMessage *msg);
private:
	bool m_buttonDown[4]; // +0x04
	char m_pad08[0x1EC - 8];
	bool m_1ec;
	int m_cursor;       // +0x1F0
	int m_leftCount;    // +0x1F4
	int m_rightCount;   // +0x1F8
	int m_middleCount;  // +0x1FC
	int m_200;          // +0x200
};

GameMessageDisposition AptTranslator::translateGameMessage(const GameMessage *msg)
{
	GameMessageDisposition disp = KEEP_MESSAGE;
	if (m_1ec)
	{
		m_1ec = false;
		return disp;
	}
	int type = msg->getType();
	bool *button = &m_buttonDown[Rva0043289DClassify(type)];
	bool anyButton = _STL::find(m_buttonDown, m_buttonDown + 4, true) != m_buttonDown + 4;
	bool mouseHeld = !anyButton && AnyMouseButtonsDown();
	switch (type)
	{
	case 0xC3:
		m_1ec = true;
		disp = DESTROY_MESSAGE;
		break;
	case 3:
	{
		if (anyButton || ((unsigned char)rva0043287E() && !mouseHeld))
		{
			TheMouse->setCursor(m_cursor);
			disp = DESTROY_MESSAGE;
		}
		if (m_200 > 0)
			--m_200;
		const int maxCount = 5;
		if (m_buttonDown[0] && TheMouse->getMouseStatus()->leftState == 0)
		{
			if (++m_leftCount > maxCount)
			{
				g_bfmeAptWindowManager->m_mouseButtonMode = 0;
				Rva006CC9A0(0, 1, 1);
				m_buttonDown[0] = false;
				m_leftCount = 0;
			}
		}
		else
			m_leftCount = 0;
		if (m_buttonDown[2] && TheMouse->getMouseStatus()->rightState == 0)
		{
			if (++m_rightCount > maxCount)
			{
				g_bfmeAptWindowManager->m_mouseButtonMode = 2;
				Rva006CC9A0(0, 1, 1);
				m_buttonDown[2] = false;
				m_rightCount = 0;
			}
		}
		else
			m_rightCount = 0;
		if (m_buttonDown[1] && TheMouse->getMouseStatus()->middleState == 0)
		{
			if (++m_middleCount > maxCount)
			{
				m_buttonDown[2] = false;
				m_middleCount = 0;
			}
		}
		else
			m_middleCount = 0;
		break;
	}
	case 4:
	case 5:
	case 14:
	case 15:
		if (type == 4 || type == 5)
			g_bfmeAptWindowManager->m_mouseButtonMode = 0;
		else
			g_bfmeAptWindowManager->m_mouseButtonMode = 2;
		if ((unsigned char)rva0043287E())
		{
			rva00432A3B(msg);
			Rva006CC9A0(0, 0, 1);
			if (++m_200 < 2)
				m_200 = 2;
			*button = true;
			disp = DESTROY_MESSAGE;
		}
		break;
	case 10:
	case 11:
		if ((unsigned char)rva0043287E())
		{
			*button = true;
			disp = DESTROY_MESSAGE;
		}
		break;
	case 6:
	case 16:
		if (*button)
		{
			rva00432A3B(msg);
			if (type == 6)
				g_bfmeAptWindowManager->m_mouseButtonMode = 0;
			else
				g_bfmeAptWindowManager->m_mouseButtonMode = 2;
			Rva006CC9A0(0, 1, 1);
			if (++m_200 < 2)
				m_200 = 2;
			*button = false;
			disp = DESTROY_MESSAGE;
		}
		break;
	case 12:
		if (*button)
		{
			*button = false;
			disp = DESTROY_MESSAGE;
		}
		break;
	case 8:
	case 13:
	case 18:
		if (*button)
			disp = DESTROY_MESSAGE;
		break;
	}
	if (disp != KEEP_MESSAGE)
		return disp;
	if (mouseHeld)
		return disp;
	if (rawMouseToWindowMessage(msg) == GWM_NONE)
		return disp;
	for (GameWindow *window = TheWindowManager->m_windowList; window; window = window->winGetParent())
	{
		if (window->winGetStatus() & 0x8000000)
		{
			int x, y;
			TheMouse->getCursorPosition(&x, &y);
			if (window->winPointInWindow(x, y))
				disp = DESTROY_MESSAGE;
			break;
		}
	}
	return disp;
}
