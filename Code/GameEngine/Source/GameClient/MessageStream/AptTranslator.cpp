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

// The canonical Mouse keeps the current MouseIO record at +0x4F0C in opaque
// storage (field4F0C is its leading pos); the button states are read through
// the record view above. Slot 18 (+0x48) is the cursor-position getter the
// header still spells vslot18 with unsigned outputs.
#include "../../../Include/GameClient/Mouse.h"

#include "../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../../Include/GameClient/Bfme2GameWindow.h"
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
	const MouseIO *io = (const MouseIO *)&TheMouse->field4F0C;
	if (io && (io->leftState || io->rightState || io->middleState))
		return true;
	return false;
}

#include "../../../Include/Common/GameMessageTranslator.h"

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
			TheMouse->setCursor((Mouse::MouseCursor)m_cursor);
			disp = DESTROY_MESSAGE;
		}
		if (m_200 > 0)
			--m_200;
		const int maxCount = 5;
		if (m_buttonDown[0] && ((const MouseIO *)&TheMouse->field4F0C)->leftState == 0)
		{
			if (++m_leftCount > maxCount)
			{
				g_bfmeAptWindowManager->field318 = 0;
				Rva006CC9A0(0, 1, 1);
				m_buttonDown[0] = false;
				m_leftCount = 0;
			}
		}
		else
			m_leftCount = 0;
		if (m_buttonDown[2] && ((const MouseIO *)&TheMouse->field4F0C)->rightState == 0)
		{
			if (++m_rightCount > maxCount)
			{
				g_bfmeAptWindowManager->field318 = 2;
				Rva006CC9A0(0, 1, 1);
				m_buttonDown[2] = false;
				m_rightCount = 0;
			}
		}
		else
			m_rightCount = 0;
		if (m_buttonDown[1] && ((const MouseIO *)&TheMouse->field4F0C)->middleState == 0)
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
			g_bfmeAptWindowManager->field318 = 0;
		else
			g_bfmeAptWindowManager->field318 = 2;
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
				g_bfmeAptWindowManager->field318 = 0;
			else
				g_bfmeAptWindowManager->field318 = 2;
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
			TheMouse->vslot18((unsigned int *)&x, (unsigned int *)&y);
			if (window->winPointInWindow(x, y))
				disp = DESTROY_MESSAGE;
			break;
		}
	}
	return disp;
}
