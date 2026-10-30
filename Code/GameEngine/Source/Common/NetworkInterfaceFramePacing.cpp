// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// platformsdk
//
// BFME2's native network vtable stores the concrete pacing query at +0x58.
// The fields below are deliberately laid out from the constructor and the
// retail body; no network policy is changed by exposing this query.

#include <windows.h>
#include "ascii_string.h"

extern class CommandList *TheCommandList;
extern class GameLogic *TheGameLogic;

extern int BfmeLogicFramesPerSecond;

struct GameLogicFrame
{
public:
	char m_pad00[0x40];
	unsigned int frame; // +0x40
};

class Transport;
class BFMEConnectionManager
{
public:
	bool isPacketRouter(void);
	bool isPlayerConnected(int arg);
	bool areFrameCommandsComplete(unsigned int frame, bool debugSpewage);
	bool hasPacketRouterFrameStall(void);
	int isPlayerSlotActive(int playerID);
	char m_pad00[0x12024];
	Transport *m_transport12024;
	char m_pad12028[0x34];
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
	virtual void updateNetwork(int flush);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	int getFrameAdvanceCount(void);
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

	int getFramePacingStatus(void);
	void ProcessDestroyPlayerCommand(NetWrapperCommandMsg *msg);

private:
	char m_unknown04[4];
	BFMEConnectionManager *m_connectionManager;
	int m_state;
	char m_unknown14[4];
	__int64 m_frequency;
	__int64 m_lastCounter;
	__int64 m_accumulator;
	bool m_stallTimerRunning;
	char m_unknown31[3];
	unsigned int m_stallCount;
	bool m_flag38;
	int m_lastValue;
};

#define LogicFramesPerSecond BfmeLogicFramesPerSecond
#define OneAndHalf 1.5f

int NetworkInterface::getFramePacingStatus(void)
{
	if (m_state != 1)
		return 1;

	if (!isPacketRouter())
		return m_connectionManager->frameCeiling
			- *(const int *)((const char *)TheGameLogic + 0x40);

	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	m_accumulator += now.QuadPart - m_lastCounter;
	m_lastCounter = now.QuadPart;

	now.QuadPart = m_frequency / LogicFramesPerSecond;
	if (m_accumulator < now.QuadPart)
		return 0;

	if ((float)m_accumulator < (float)now.QuadPart * OneAndHalf)
		return 1;

	return 2;
}

// ?ProcessDestroyPlayerCommand@NetworkInterface@@QAEXPAVNetWrapperCommandMsg@@@Z at 0x0025E539 (187B).
// Thiscall handler: slot index from NetWrapperCommandMsg::getData, GameSlot name
// to NameKey to Player, new Rva0030F47A((void*)0x448) with bool true, +0x14 from
// Player+0x54, virtual send at +0x38 on global 0xA00954. Evidence: caller
// 0x0025E5F4 push edi + mov ecx,esi, all callees rowed/pinned, ret 4.


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

template <int N> class Rva0025E75FSlots : public Rva0025E75FSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0025E75FSlots<0>
{
};

class GameInfo : public Rva0025E75FSlots<19>
{
public:
	GameSlot *getSlot(int n);
	virtual bool rva0025E75FSlot13(); // +0x4C
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

union GameMessageArgumentType;
class GameMessage
{
public:
	void appendIntegerArgument(int value);
	void appendBooleanArgument(bool arg);
	const GameMessageArgumentType *getArgument(int argIndex) const; // 0x0030F4EA
	GameMessage *next() { return m_next; }
	int getType() const { return m_type; }
	unsigned char getArgumentCount() const { return m_argCount; }
	virtual void *deleteInstance(int flags); // slot 0
	GameMessage *m_next; // +0x04 +0x04
	char m_pad08[0x8];
	int m_type; // +0x10 +0x10
	char m_pad14[0x4];
	unsigned char m_argCount; // +0x18 +0x18
	char m_pad19[0x3];
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

void NetworkInterface::ProcessDestroyPlayerCommand(NetWrapperCommandMsg *msg)
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
