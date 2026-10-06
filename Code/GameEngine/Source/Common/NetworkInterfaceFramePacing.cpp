// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// BFME2's native network vtable stores the concrete pacing query at +0x58.
// The fields below are deliberately laid out from the constructor and the
// retail body; no network policy is changed by exposing this query.

extern class CommandList *TheCommandList;
extern class GameLogic *TheGameLogic;

extern int g_Va00DBA4E4;

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *counter);

struct GameLogicFrame
{
	char unknown[0x40];
};

struct BFMEConnectionManager
{
	char unknown[0x1205C];
	volatile int frameCeiling;
};

class NetWrapperCommandMsg;

class NetworkInterface
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	int getFramePacingStatus(void);
	void rva0025E539(NetWrapperCommandMsg *msg);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual void slot37(void);
	virtual void slot38(void);
	virtual void slot39(void);
	virtual void slot40(void);
	virtual void slot41(void);
	virtual void slot42(void);
	virtual bool isPacketRouter(void);

private:
	char m_unknown04[4];
	BFMEConnectionManager *m_connectionManager;
	int m_state;
	char m_unknown14[4];
	__int64 m_frequency;
	__int64 m_lastCounter;
	__int64 m_accumulator;
};

#define TheGameLogic (*(volatile GameLogicFrame **)&TheGameLogic)
#define LogicFramesPerSecond g_Va00DBA4E4
#define OneAndHalf 1.5f

int NetworkInterface::getFramePacingStatus(void)
{
	if (m_state != 1)
		return 1;

	if (!isPacketRouter())
		return m_connectionManager->frameCeiling
			- *(const int *)((const char *)TheGameLogic + 0x40);

	__int64 now;
	QueryPerformanceCounter(&now);
	m_accumulator += now - m_lastCounter;
	m_lastCounter = now;

	now = m_frequency / LogicFramesPerSecond;
	if (m_accumulator < now)
		return 0;

	if ((float)m_accumulator < (float)now * OneAndHalf)
		return 1;

	return 2;
}

// ?rva0025E539@NetworkInterface@@QAEXPAVNetWrapperCommandMsg@@@Z at 0x0025E539 (187B).
// Thiscall handler: slot index from NetWrapperCommandMsg::getData, GameSlot name
// to NameKey to Player, new Rva0030F47A((void*)0x448) with bool true, +0x14 from
// Player+0x54, virtual send at +0x38 on global 0xA00954. Evidence: caller
// 0x0025E5F4 push edi + mov ecx,esi, all callees rowed/pinned, ret 4.

#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GameSlot
{
public:
	char m_pad[0x34];
	AsciiString m_name;
};

class GameInfo
{
public:
	GameSlot *getSlot(int n);
};
extern GameInfo *TheGameInfo;

class Player
{
public:
	char m_pad[0x54];
	void *m_54;
};

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};
extern PlayerList *ThePlayerList;

class NetWrapperCommandMsg
{
public:
	unsigned char *getData();
};

class GameMessage
{
public:
	void appendBooleanArgument(bool arg);
};

class Rva0030F47A
{
public:
	Rva0030F47A(void *arg);
	void *m_vft;
	int m_04;
	int m_08;
	int m_0C;
	void *m_10;
	void *m_14;
	bool m_18;
	int m_1C;
	int m_20;
};

class MessageTarget
{
public:
	virtual void s00(void);
	virtual void s01(void);
	virtual void s02(void);
	virtual void s03(void);
	virtual void s04(void);
	virtual void s05(void);
	virtual void s06(void);
	virtual void s07(void);
	virtual void s08(void);
	virtual void s09(void);
	virtual void s10(void);
	virtual void s11(void);
	virtual void s12(void);
	virtual void s13(void);
	virtual void s14(Rva0030F47A *m);
};

#define TheMessageTarget (*(MessageTarget **)&TheCommandList)

void NetworkInterface::rva0025E539(NetWrapperCommandMsg *msg)
{
	unsigned int idx = (unsigned int)msg->getData();
	if (idx >= 8)
		return;
	GameSlot *slot = TheGameInfo->getSlot((int)idx);
	AsciiString tmp(slot->m_name);
	NameKeyType key = TheNameKeyGenerator->nameToKey(tmp);
	Player *player = ThePlayerList->findPlayerWithNameKey(key);
	if (player)
	{
		Rva0030F47A *m = new Rva0030F47A((void *)0x448);
		((GameMessage *)m)->appendBooleanArgument(true);
		m->m_14 = player->m_54;
		TheMessageTarget->s14(m);
	}
}
