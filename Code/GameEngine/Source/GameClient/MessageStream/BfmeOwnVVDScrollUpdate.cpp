// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?rva0042F213@BfmeOwnVVD@@QAEXXZ, retail 0x0042F213 1958B.
// The per-frame camera scroll update of the BFME 2 look-at translator (the
// singleton at 0x00E03214 whose constructor and stopScrolling-style reset
// rva0042E804 live in BfmeOwnVVDCtor.cpp); GameClient::update calls it at
// 0x0023BEFC with no arguments. WorldBuilder twin 0x012C4A70 (by call graph)
// and the Zero Hour / BFME 1 LookAtTranslator MSG_FRAME_TICK case give the
// shape: stop when the UI stopped scrolling; per scroll type (1 mouse anchor
// 2 arrow keys 3 screen edge timed by +0x14C) build the offset from the
// GlobalData scroll factors; hand it to the 0x00DFEF18 host or to the UI and
// the tactical view (whose returned clamp bits pin the anchor by camera
// angle); apply the held rotate/zoom flags (+0x154..+0x157); post the replay
// camera message 0x447; then drop key flags whose keys are released.
// Identities beyond the rowed callees stay address-derived.
#include "Coord2D.h"
#include "Coord3D.h"
#include <math.h>
#include "../../Common/GameLogicObjectLookupView.h"

// The scroll amount travels by value through a copy constructor (retail
// copy-constructs it in the outgoing argument slots and records their address).
class ScrollOffset : public Coord2D
{
public:
	ScrollOffset() {}
	ScrollOffset(const ScrollOffset &that)
	{
		x = that.x;
		y = that.y;
	}
	~ScrollOffset() {}
};

inline float sqr(float x)
{
	return x * x;
}

struct ICoord2D
{
	int x;
	int y;
};

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
	void appendRealArgument(float arg);
	void appendLocationArgument(const Coord3D &arg);
	void appendPixelArgument(const ICoord2D &arg);
};

class ViewLocation
{
public:
	ViewLocation()
	{
		m_valid = false;
		m_pos.x = 0.0f;
		m_pos.y = 0.0f;
		m_pos.z = 0.0f;
		m_angle = m_pitch = m_zoom = m_1C = 0.0;
	}

	bool m_valid;
	Coord3D m_pos;      // +0x04
	float m_angle;      // +0x10
	float m_pitch;      // +0x14
	float m_zoom;       // +0x18
	float m_1C;         // +0x1C
};
class InGameUI
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
	virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
	virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C();
	virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74();
	virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C();
	virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9C(); virtual void vA0(); virtual void vA4();
	virtual bool isScrolling(); // +0xA8
	virtual void vAC(); virtual void vB0();
	virtual void setScrollAmount(ScrollOffset amount); // +0xB4
	virtual void vB8(); virtual void vBC(); virtual void vC0(); virtual void vC4(); virtual void vC8();
	virtual bool slotCC(); // +0xCC
	virtual void vD0(); virtual void vD4(); virtual void vD8(); virtual void vDC(); virtual void vE0(); virtual void vE4();
	virtual void vE8(); virtual void vEC(); virtual void vF0(); virtual void vF4(); virtual void vF8(); virtual void vFC();
	virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10C(); virtual void v110(); virtual void v114();
	virtual void v118(); virtual void v11C(); virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12C();
	virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13C(); virtual void v140(); virtual void v144();
	virtual void v148(); virtual void v14C(); virtual void v150(); virtual void v154(); virtual void v158(); virtual void v15C();
	virtual void v160(); virtual void v164(); virtual void v168(); virtual void v16C(); virtual void v170(); virtual void v174();
	virtual void v178();
	virtual bool slot17C(); // +0x17C

	char m_pad04[0x15 - 4];
	bool m_15;          // +0x15
	bool m_16;          // +0x16
	char m_pad17[0x8C4 - 0x17];
	bool m_8C4;         // +0x8C4
};

class View
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
	virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
	virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54(); virtual void v58();
	virtual unsigned int scrollBy(ScrollOffset *delta); // +0x5C
	virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74();
	virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C();
	virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9C(); virtual void vA0(); virtual void vA4();
	virtual void vA8(); virtual void vAC(); virtual void vB0(); virtual void vB4(); virtual void vB8(); virtual void vBC();
	virtual void vC0(); virtual void vC4(); virtual void vC8(); virtual void vCC(); virtual void vD0(); virtual void vD4();
	virtual void vD8(); virtual void vDC(); virtual void vE0(); virtual void vE4(); virtual void vE8(); virtual void vEC();
	virtual void vF0(); virtual void vF4(); virtual void vF8();
	virtual void setAngle(float angle); // +0xFC
	virtual float getAngle(); // +0x100
	virtual void v104(); virtual void v108(); virtual void v10C(); virtual void v110(); virtual void v114(); virtual void v118();
	virtual void v11C(); virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12C(); virtual void v130();
	virtual void slot134(); // +0x134
	virtual void slot138(); // +0x138
	virtual void v13C(); virtual void v140(); virtual void v144(); virtual void v148(); virtual void v14C(); virtual void v150();
	virtual void v154(); virtual void v158(); virtual void v15C(); virtual void v160(); virtual void v164(); virtual void v168();
	virtual void v16C();
	virtual void getLocation(ViewLocation *location); // +0x170
};

class Display
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
	virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
	virtual unsigned int getWidth(); // +0x40
	virtual unsigned int getHeight(); // +0x44
};

class MessageStream
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
	virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
	virtual GameMessage *appendMessage(int type); // +0x48
};

class Rva002D3627Host
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
	virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28();
	virtual void slot2C(ScrollOffset *offset, float extra); // +0x2C

	char m_pad04[0x18 - 4];
	bool m_18;          // +0x18
};

class GlobalData
{
public:
	char m_pad0[0xA9C];
	float m_horizontalScrollSpeedFactor; // +0xA9C
	float m_verticalScrollSpeedFactor;   // +0xAA0
	float m_AA4;                         // +0xAA4
	int m_edgeScrollTime;                // +0xAA8
	char m_padAAC[0xAF8 - 0xAAC];
	float m_keyboardScrollFactor;        // +0xAF8
	char m_padAFC[0xB70 - 0xAFC];
	bool m_saveCameraInReplay;           // +0xB70
	char m_padB71[0xC2C - 0xB71];
	float m_C2C;                         // +0xC2C
};

class Mouse
{
public:
	void *rva001EDFE9() const;
	char m_pad0[0x4FA4];
	int m_4FA4;                          // +0x4FA4
};

class Keyboard
{
public:
	bool rva00232643(unsigned char key);
};

class GameEngine
{
	friend class BfmeOwnVVD;
private:
	bool rva00225D38(void);
};

class Rva0023C666
{
public:
	bool rva0023C666();
};

class BfmeOwnVVD
{
public:
	virtual void bfmeSlot0VVD();
	void rva0042E804();
	void rva0042F213();

private:
	ICoord2D m_anchor;                   // +0x04
	ICoord2D m_0C;                       // +0x0C
	ICoord2D m_currentPos;               // +0x14
	char m_pad1C[0x38 - 0x1C];
	bool m_isScrolling;                  // +0x38
	char m_pad39[0x148 - 0x39];
	int m_scrollType;                    // +0x148
	unsigned int m_scrollStart;          // +0x14C
	int m_150;                           // +0x150
	bool m_154;                          // +0x154
	bool m_155;                          // +0x155
	bool m_156;                          // +0x156
	bool m_157;                          // +0x157
};

extern InGameUI *TheInGameUI;
extern View *TheTacticalView;
extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;
extern Mouse *TheMouse;
extern Keyboard *TheKeyboard;
extern GameEngine *TheGameEngine;
extern GameLogic *TheGameLogic;
extern MessageStream *TheMessageStream;
extern Rva002D3627Host *g_00DFEF18;
extern bool g_00E03218[4];
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

void BfmeOwnVVD::rva0042F213()
{
	ScrollOffset offset;
	offset.x = 0.0f;
	offset.y = 0.0f;
	if (m_isScrolling && (!TheInGameUI->isScrolling() || TheInGameUI->slot17C()))
	{
		TheInGameUI->setScrollAmount(offset);
		rva0042E804();
	}
	else if (m_isScrolling)
	{
		switch (m_scrollType)
		{
		case 1:
			{
				if (TheInGameUI->slotCC())
				{
					TheInGameUI->setScrollAmount(offset);
					rva0042E804();
					break;
				}
				{
					ICoord2D pos = *(const ICoord2D *)TheMouse->rva001EDFE9();
					ICoord2D delta;
					delta.x = m_currentPos.x - pos.x;
					delta.y = m_currentPos.y - pos.y;
					if (TheInGameUI->m_8C4)
					{
						int maxX = TheDisplay->getWidth() / 2;
						int maxY = TheDisplay->getHeight() / 2;

						if (m_currentPos.x + maxX < m_anchor.x)
							m_anchor.x = m_currentPos.x + maxX;
						else if (m_currentPos.x - maxX > m_anchor.x)
							m_anchor.x = m_currentPos.x - maxX;

						if (m_currentPos.y + maxY < m_anchor.y)
							m_anchor.y = m_currentPos.y + maxY;
						else if (delta.y - maxY > m_anchor.y)
							m_anchor.y = m_currentPos.y - maxY;
					}

				}
				offset.x = TheWritableGlobalData->m_horizontalScrollSpeedFactor * (m_currentPos.x - m_anchor.x);
				offset.y = TheWritableGlobalData->m_verticalScrollSpeedFactor * (m_currentPos.y - m_anchor.y);
				{
					Coord2D vec;
					vec.x = offset.x;
					vec.y = offset.y;
					vec.normalize();
					offset.x += TheWritableGlobalData->m_horizontalScrollSpeedFactor * vec.x * sqr(TheWritableGlobalData->m_keyboardScrollFactor);
					offset.y += TheWritableGlobalData->m_verticalScrollSpeedFactor * vec.y * sqr(TheWritableGlobalData->m_keyboardScrollFactor);
				}
			}
			break;
		case 2:
			{
				if (g_00E03218[0])
					offset.y -= TheWritableGlobalData->m_verticalScrollSpeedFactor * 100.0f * TheWritableGlobalData->m_keyboardScrollFactor;
				if (g_00E03218[1])
					offset.y += TheWritableGlobalData->m_verticalScrollSpeedFactor * 100.0f * TheWritableGlobalData->m_keyboardScrollFactor;
				if (g_00E03218[2])
					offset.x -= TheWritableGlobalData->m_horizontalScrollSpeedFactor * 100.0f * TheWritableGlobalData->m_keyboardScrollFactor;
				if (g_00E03218[3])
					offset.x += TheWritableGlobalData->m_horizontalScrollSpeedFactor * 100.0f * TheWritableGlobalData->m_keyboardScrollFactor;
			}
			break;
		case 3:
			{
				int elapsed = timeGetTime() - m_scrollStart;
				int amount;
				if (elapsed > TheWritableGlobalData->m_edgeScrollTime)
					amount = 100;
				else
					amount = elapsed * 100 / TheWritableGlobalData->m_edgeScrollTime;
				unsigned int height = TheDisplay->getHeight();
				unsigned int width = TheDisplay->getWidth();
				if (m_currentPos.y < 3)
					offset.y -= amount * TheWritableGlobalData->m_verticalScrollSpeedFactor * TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_AA4;
				if (m_currentPos.y >= height - 3)
					offset.y += amount * TheWritableGlobalData->m_verticalScrollSpeedFactor * TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_AA4;
				if (m_currentPos.x < 3)
					offset.x -= amount * TheWritableGlobalData->m_horizontalScrollSpeedFactor * TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_AA4;
				if (m_currentPos.x >= width - 3)
					offset.x += amount * TheWritableGlobalData->m_horizontalScrollSpeedFactor * TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_AA4;
			}
			break;
		}

		if (g_00DFEF18 && g_00DFEF18->m_18)
		{
			g_00DFEF18->slot2C(&offset, 0.0f);
		}
		else
		{
			TheInGameUI->setScrollAmount(offset);
			unsigned int clamped = TheTacticalView->scrollBy(&offset);
			if (clamped && m_scrollType == 1)
			{
				float angle = fabs(TheTacticalView->getAngle());
				bool sideways = false;
				if (angle > 0.7853982f && angle < 2.3561945f)
					sideways = true;
				if ((clamped & 1) || (clamped & 2))
				{
					if (sideways)
						m_anchor.y = m_currentPos.y;
					else
						m_anchor.x = m_currentPos.x;
				}
				if ((clamped & 4) || (clamped & 8))
				{
					if (sideways)
						m_anchor.x = m_currentPos.x;
					else
						m_anchor.y = m_currentPos.y;
				}
			}
		}
	}
	else
	{
		TheInGameUI->setScrollAmount(offset);
	}

	if (TheInGameUI->m_15 && TheInGameUI->m_16)
	{
		if (m_154)
			TheTacticalView->setAngle(TheTacticalView->getAngle() - TheWritableGlobalData->m_C2C);
		if (m_155)
			TheTacticalView->setAngle(TheTacticalView->getAngle() + TheWritableGlobalData->m_C2C);
		if (m_156)
			TheTacticalView->slot134();
		if (m_157)
			TheTacticalView->slot138();
	}

	if (TheWritableGlobalData->m_saveCameraInReplay && TheGameEngine->rva00225D38() &&
		(((Rva0023C666 *)TheGameLogic)->rva0023C666() || TheGameLogic->m_110 == 2 || TheGameLogic->isInMultiplayerGame()))
	{
		ViewLocation currentView;
		TheTacticalView->getLocation(&currentView);
		GameMessage *msg = TheMessageStream->appendMessage(0x447);
		msg->appendLocationArgument(currentView.m_pos);
		msg->appendRealArgument(currentView.m_angle);
		msg->appendRealArgument(currentView.m_pitch);
		msg->appendRealArgument(currentView.m_zoom);
		msg->appendRealArgument(currentView.m_1C);
		msg->appendIntegerArgument(TheMouse->m_4FA4);
		msg->appendPixelArgument(m_currentPos);
	}

	if (m_isScrolling)
	{
		if (!TheKeyboard->rva00232643(0xC8))
			g_00E03218[0] = false;
		if (!TheKeyboard->rva00232643(0xD0))
			g_00E03218[1] = false;
		if (!TheKeyboard->rva00232643(0xCB))
			g_00E03218[2] = false;
		if (!TheKeyboard->rva00232643(0xCD))
			g_00E03218[3] = false;
		if (!g_00E03218[0] && !g_00E03218[1] && !g_00E03218[2] && !g_00E03218[3] && m_scrollType == 2)
			rva0042E804();
	}

	if (m_154 && !TheKeyboard->rva00232643(0x4B))
		m_154 = false;
	if (m_155 && !TheKeyboard->rva00232643(0x4D))
		m_155 = false;
	if (m_156 && !TheKeyboard->rva00232643(0x48))
		m_156 = false;
	if (m_157 && !TheKeyboard->rva00232643(0x50))
		m_157 = false;
}
