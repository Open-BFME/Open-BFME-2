// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
//
// ?translateGameMessage@BfmeOwnVVD@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z
// retail 0x0042E9EC..0x0042F213 (2087 bytes).
// Slot 0 of vtable 0x0083C938 (BfmeOwnVVD) -- the BFME 2 look-at translator
// whose ctor 0x0042E926 / dtor 0x0042E85C / stopScrolling-style reset
// 0x0042E804 / setScrolling-style start 0x0042E75F live in
// BfmeOwnVVDCtor.cpp and whose frame-tick scroll update 0x0042F213 lives in
// BfmeOwnVVDScrollUpdate.cpp. WorldBuilder twin 0x012C30D0 is
// LookAtTranslator::translateGameMessage (LookAtXlat.cpp); Zero Hour's
// LookAtXlat.cpp gives the case shapes: raw key up/down feed the four scroll
// direction flags at 0x00E03218 plus the held rotate/zoom keys +0x154..+0x157;
// the right button arms a pending scroll (+0x1C) that the mouse-position case
// starts once Mouse 0x001EDD80 reports the drag; the middle button rotates and
// a short click resets the camera (View slot 0xC8); the wheel zooms; save and
// view bookmarks use the eight 0x20-byte view locations at +0x48 and the
// GUI:BookmarkXSet text (0x0083C944). Message numbers are BFME 2's from the
// retail compare tree.
#include "unicode_string.h"
#include "Coord2D.h"
#include "../../Common/GameLogicObjectLookupView.h"

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

struct ICoord2D
{
	int x;
	int y;
};

union GameMessageArgumentType
{
	int integer;
	ICoord2D pixel;
};

class GameMessage
{
public:
	int getType() const { return m_type; }
	const GameMessageArgumentType *getArgument(int argIndex) const;

private:
	char m_pad00[0x10];
	int m_type; // +0x10
};

class ViewLocation
{
	char m_data[0x20];
};

#define V(n) virtual void v##n();

class InGameUI
{
public:
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(0A) V(0B) V(0C) V(0D) V(0E) V(0F)
	virtual void message(UnicodeString message, ...); // +0x40
	V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(1A) V(1B) V(1C) V(1D) V(1E) V(1F)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(2A) V(2B)
	virtual bool isSelecting(); // +0xB0

	bool getInputEnabled() const { return m_15 && m_16; }

	char m_pad04[0x15 - 4];
	bool m_15; // +0x15
	bool m_16; // +0x16
};

class View
{
public:
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(0A) V(0B) V(0C) V(0D) V(0E) V(0F)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(1A) V(1B) V(1C)
	virtual void slot74(int value); // +0x74
	V(1E) V(1F)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(2A) V(2B) V(2C) V(2D) V(2E) V(2F)
	V(30) V(31)
	virtual void resetCamera(int a, int b, float c, float d); // +0xC8
	V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(3A) V(3B) V(3C) V(3D) V(3E)
	virtual void setAngle(float angle); // +0xFC
	virtual float getAngle(); // +0x100
	virtual void setPitch(float pitch); // +0x104
	virtual float getPitch(); // +0x108
	V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(4A) V(4B) V(4C)
	virtual void zoomIn(); // +0x134
	virtual void zoomOut(); // +0x138
	V(4F)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(5A) V(5B)
	virtual void getLocation(ViewLocation *location); // +0x170
	virtual void setLocation(const ViewLocation *location); // +0x174
	V(5E) V(5F)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68)
	virtual void setMouseLock(bool lock); // +0x1A4
	V(6A) V(6B) V(6C) V(6D) V(6E) V(6F)
	V(70) V(71) V(72)
	virtual bool slot1CC(); // +0x1CC
	V(74) V(75) V(76) V(77) V(78) V(79) V(7A) V(7B)
	virtual void slot1F0(float value); // +0x1F0
	V(7D)
	virtual float slot1F8(); // +0x1F8
};

class Display
{
public:
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(0A) V(0B) V(0C) V(0D) V(0E) V(0F)
	virtual unsigned int getWidth(); // +0x40
	virtual unsigned int getHeight(); // +0x44
};

class GameClient
{
public:
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(0A) V(0B) V(0C) V(0D) V(0E) V(0F)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(1A) V(1B) V(1C) V(1D) V(1E)
	virtual unsigned int getFrame(); // +0x7C
};

class GameTextInterface
{
public:
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(0A) V(0B) V(0C) V(0D) V(0E)
	virtual UnicodeString fetch(const char *label, bool *exists = 0); // +0x3C
	V(10)
	virtual const UnicodeString &fetchRef(const char *label, bool *exists = 0); // +0x44
};

#undef V

struct MouseIO
{
	ICoord2D pos;      // +0x00
	char m_pad08[0x18 - 8];
	int leftState;     // +0x18
};

struct Rva001EDD80Pair;

class Mouse
{
public:
	void rva001EDFF7(float *region) const;
	bool rva001EDD80(const Rva001EDD80Pair *anchor, const Rva001EDD80Pair *pos);
	const MouseIO *getMouseStatus() { return &m_currMouse; }

	char m_pad00[0x4F0C];
	MouseIO m_currMouse; // +0x4F0C
};

struct Rva001EDD80Pair
{
	int x;
	int y;
};

class GlobalData
{
public:
	char m_pad00[0x2C];
	bool m_windowed; // +0x2C
};

class Shell
{
public:
	bool isShellActive() const { return m_isShellActive; }

	char m_pad00[0x5C];
	bool m_isShellActive; // +0x5C
};

class BfmeOwnVVD
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	void rva0042E804();
	void rva0042E75F(unsigned int scrollType);

private:
	ICoord2D m_anchor;          // +0x04
	ICoord2D m_0C;              // +0x0C
	ICoord2D m_currentPos;      // +0x14
	bool m_rmbPending;          // +0x1C
	ICoord2D m_rotateAnchor;    // +0x20
	ICoord2D m_originalAnchor;  // +0x28
	ICoord2D m_rotatePos;       // +0x30
	bool m_isScrolling;         // +0x38
	bool m_isRotating;          // +0x39
	bool m_keepAnchorOffset;    // +0x3A
	bool m_isPitching;          // +0x3B
	bool m_3C;                  // +0x3C
	unsigned int m_timestamp;   // +0x40
	unsigned int m_44;          // +0x44
	ViewLocation m_viewLocation[8]; // +0x48
	int m_scrollType;           // +0x148
	unsigned int m_scrollStart; // +0x14C
	unsigned int m_lastMouseMoveFrame; // +0x150
	bool m_154;                 // +0x154
	bool m_155;                 // +0x155
	bool m_156;                 // +0x156
	bool m_157;                 // +0x157
};

extern InGameUI *TheInGameUI;
extern View *TheTacticalView;
extern Display *TheDisplay;
extern GameClient *TheGameClient;
extern GameLogic *TheGameLogic;
extern GameTextInterface *TheGameText;
extern Mouse *TheMouse;
extern GlobalData *TheWritableGlobalData;
extern Shell *TheShell;
extern bool g_00E03218[4];

GameMessageDisposition BfmeOwnVVD::translateGameMessage(const GameMessage *msg)
{
	GameMessageDisposition disp = KEEP_MESSAGE;

	int t = msg->getType();
	switch (t)
	{
	case 0x15:
	case 0x16:
	{
		unsigned char key = msg->getArgument(0)->integer;
		unsigned char state = msg->getArgument(1)->integer;
		bool isPressed = !(state & 1);

		if (TheShell && TheShell->isShellActive())
			break;

		switch (key)
		{
		case 0xC8:
			g_00E03218[0] = isPressed;
			break;
		case 0xD0:
			g_00E03218[1] = isPressed;
			break;
		case 0xCB:
			g_00E03218[2] = isPressed;
			break;
		case 0xCD:
			g_00E03218[3] = isPressed;
			break;
		case 0x4B:
			m_154 = isPressed;
			break;
		case 0x4D:
			m_155 = isPressed;
			break;
		case 0x48:
			m_156 = isPressed;
			break;
		case 0x50:
			m_157 = isPressed;
			break;
		}

		if (TheInGameUI->isSelecting() || (m_isScrolling && m_scrollType != 2))
			break;

		int numDirs = 0;
		for (int i = 0; i < 4; ++i)
		{
			if (g_00E03218[i])
				numDirs++;
		}

		if (numDirs && !m_isScrolling)
			rva0042E75F(2);
		else if (!numDirs && m_isScrolling)
			rva0042E804();
		break;
	}

	case 0x0E:
	{
		m_lastMouseMoveFrame = TheGameLogic->getFrame();
		m_currentPos = msg->getArgument(0)->pixel;
		m_anchor.x = m_currentPos.x;
		m_anchor.y = m_currentPos.y;
		if (!TheInGameUI->isSelecting() && !m_isScrolling)
			m_rmbPending = true;
		break;
	}

	case 0x10:
	{
		m_lastMouseMoveFrame = TheGameLogic->getFrame();
		m_rmbPending = false;
		if (m_scrollType == 1)
			rva0042E804();
		break;
	}

	case 0x0A:
	{
		m_lastMouseMoveFrame = TheGameLogic->getFrame();
		m_isRotating = true;
		m_rotateAnchor = msg->getArgument(0)->pixel;
		m_originalAnchor = msg->getArgument(0)->pixel;
		m_rotatePos = msg->getArgument(0)->pixel;
		m_timestamp = TheGameClient->getFrame();
		if (!m_isScrolling)
			TheTacticalView->setMouseLock(true);
		break;
	}

	case 0x0C:
	{
		if (m_isRotating && !m_isScrolling)
			TheTacticalView->setMouseLock(false);
		m_lastMouseMoveFrame = TheGameLogic->getFrame();

		const unsigned int CLICK_DURATION = 5;
		const unsigned int PIXEL_OFFSET = 5;

		m_isRotating = false;
		int dx = m_rotatePos.x - m_originalAnchor.x;
		if (dx < 0)
			dx = -dx;
		int dy = m_rotatePos.y - m_originalAnchor.y;
		bool didMove = dx > PIXEL_OFFSET || dy > PIXEL_OFFSET;
		if (!didMove && TheGameClient->getFrame() - m_timestamp < CLICK_DURATION)
			TheTacticalView->resetCamera(0, 0, 0.0f, 0.0f);
		break;
	}

	case 0x03:
	{
		if (m_rmbPending && !m_isScrolling)
		{
			ICoord2D pos = msg->getArgument(0)->pixel;
			if (TheMouse->rva001EDD80((const Rva001EDD80Pair *)&m_anchor, (const Rva001EDD80Pair *)&pos))
				rva0042E75F(1);
		}

		if (!TheTacticalView->slot1CC())
		{
			if (m_currentPos.x != msg->getArgument(0)->pixel.x || m_currentPos.y != msg->getArgument(0)->pixel.y)
				m_lastMouseMoveFrame = TheGameLogic->getFrame();

			if (m_isRotating)
			{
				m_keepAnchorOffset = true;
				m_rotatePos = msg->getArgument(0)->pixel;
			}
			else if (m_keepAnchorOffset && m_scrollType == 1)
			{
				int dx = m_anchor.x - m_currentPos.x;
				int dy = m_anchor.y - m_currentPos.y;
				m_currentPos = msg->getArgument(0)->pixel;
				m_anchor.x = m_currentPos.x + dx;
				m_anchor.y = m_currentPos.y + dy;
				m_keepAnchorOffset = false;
			}
			else
			{
				m_currentPos = msg->getArgument(0)->pixel;
			}

			unsigned int height = TheDisplay->getHeight();
			unsigned int width = TheDisplay->getWidth();

			if (!TheInGameUI->getInputEnabled())
			{
				if (m_isScrolling)
					rva0042E804();
				break;
			}

			bool isSelecting = TheInGameUI->isSelecting();
			if (isSelecting)
			{
				const MouseIO *io = TheMouse->getMouseStatus();
				if (io && io->leftState != 1)
					isSelecting = false;
			}

			if (!TheWritableGlobalData->m_windowed && !isSelecting)
			{
				if (m_isScrolling)
				{
					if (m_scrollType == 3 && (m_currentPos.x >= 3 && m_currentPos.y >= 3 && m_currentPos.y < height - 3 && m_currentPos.x < width - 3))
						rva0042E804();
				}
				else
				{
					if (m_currentPos.x < 3 || m_currentPos.y < 3 || m_currentPos.y >= height - 3 || m_currentPos.x >= width - 3)
						rva0042E75F(3);
				}
			}

			if (m_isRotating)
			{
				float angle = 0.005f * (m_rotatePos.x - m_rotateAnchor.x);
				TheTacticalView->setAngle(TheTacticalView->getAngle() + angle);
				m_rotateAnchor = msg->getArgument(0)->pixel;
			}
		}
		else
		{
			float region[4];
			TheMouse->rva001EDFF7(region);
			Coord2D mouse;
			mouse.x = TheMouse->m_currMouse.pos.x;
			mouse.y = TheMouse->m_currMouse.pos.y;
			region[0] += 15.0f;
			region[2] -= 15.0f;
			region[1] += 15.0f;
			region[3] -= 15.0f;

			if (mouse.x <= region[0])
			{
				TheTacticalView->setAngle(TheTacticalView->getAngle() + 0.046f);
				float h = region[3] - region[1];
				float halfH = h * 0.5f;
				TheTacticalView->slot1F0(TheTacticalView->slot1F8() + ((mouse.y - halfH) / h * 2.0f) * 0.03f);
			}
			else if (mouse.x >= region[2])
			{
				TheTacticalView->setAngle(TheTacticalView->getAngle() - 0.046f);
				float h = region[3] - region[1];
				float halfH = h * 0.5f;
				TheTacticalView->slot1F0(TheTacticalView->slot1F8() + ((mouse.y - halfH) / h * 2.0f) * 0.03f);
			}
			else if (mouse.y <= region[1])
			{
				TheTacticalView->slot1F0(TheTacticalView->slot1F8() - 0.02f);
			}
			else if (mouse.y >= region[3])
			{
				TheTacticalView->slot1F0(TheTacticalView->slot1F8() + 0.02f);
			}

			if (m_isRotating)
			{
				float angle = 0.001f * (m_rotatePos.x - m_rotateAnchor.x);
				TheTacticalView->setAngle(TheTacticalView->getAngle() + angle);
				m_rotateAnchor = msg->getArgument(0)->pixel;
			}

			if (m_isPitching)
			{
				float angle = 0.01f * (m_currentPos.y - m_anchor.y);
				TheTacticalView->setPitch(TheTacticalView->getPitch() + angle);
				m_anchor = msg->getArgument(0)->pixel;
			}
		}
		break;
	}

	case 0x13:
	{
		m_lastMouseMoveFrame = TheGameLogic->getFrame();

		int spin = msg->getArgument(1)->integer;
		if (spin > 0)
		{
			for (; spin > 0; spin--)
				TheTacticalView->zoomIn();
		}
		else
		{
			for (; spin < 0; spin++)
				TheTacticalView->zoomOut();
		}
		break;
	}

	case 0x70:
	{
		rva0042E804();
		break;
	}

	case 0x24:
	case 0x25:
	case 0x26:
	case 0x27:
	case 0x28:
	case 0x29:
	case 0x2A:
	case 0x2B:
	{
		int slot = t - 0x24 + 1;
		if (slot > 0 && slot <= 8)
		{
			TheTacticalView->getLocation(&m_viewLocation[slot - 1]);
			UnicodeString text;
			text.format(&TheGameText->fetchRef("GUI:BookmarkXSet"), slot);
			TheInGameUI->message(text);
		}
		disp = DESTROY_MESSAGE;
		break;
	}

	case 0x2C:
	case 0x2D:
	case 0x2E:
	case 0x2F:
	case 0x30:
	case 0x31:
	case 0x32:
	case 0x33:
	{
		if (!TheInGameUI->getInputEnabled())
			break;
		int slot = t - 0x2C + 1;
		if (slot > 0 && slot <= 8)
			TheTacticalView->setLocation(&m_viewLocation[slot - 1]);
		disp = DESTROY_MESSAGE;
		break;
	}

	case 0x452:
	{
		int value = msg->getArgument(0)->integer;
		TheTacticalView->slot74(value);
		break;
	}
	}

	return disp;
}
