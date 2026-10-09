// cl: /O1 /MD /ICode/GameEngine/Source/Common
// ?rva00271BDE@Rva00271BDE@@QAE_NXZ, retail 0x00271BDE (62 bytes). Owner unproven (address token, like the rowed
// Rva00271C1C / Rva00271B03 at +0x384 / +0x594). Whether the held object (+0xFC) is not of kind 0x25 and the
// game's frame has reached the deadline stored at +0x384.
enum KindOfType
{
	KINDOF_0x25 = 0x25
};

class Object
{
public:
	bool rva00293926(KindOfType kind);	// 0x00293926, isKindOf
};

#include "GameLogicObjectLookupView.h"

// The frame counter at +0x40 (the shared GameLogic view keeps it private).
struct GameLogicFrameView
{
	unsigned char m_pre[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class Rva00271BDE
{
public:
	bool rva00271BDE();

private:
	unsigned char m_pre00[0xFC];
	Object *m_fc;
	unsigned char m_mid[0x384 - 0x100];
	unsigned int m_384;
};

bool Rva00271BDE::rva00271BDE()
{
	if (TheGameLogic == 0)
		return false;
	if (m_fc == 0)
		return false;
	return !m_fc->rva00293926(KINDOF_0x25) && ((GameLogicFrameView *)TheGameLogic)->m_frame >= m_384;
}
