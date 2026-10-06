// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?clearSlotList@GameInfo@@QAEXXZ @0x003FFDB7 (67B):
// GameInfo::clearSlotList. BFME1 GameInfo.cpp donor verbatim shape: loop 8 slots
// via +0x18 array, null check, zeroed GameSlotConnectInfo (nat 0 port 0 via
// dword+word ands under /O1), setState(CLOSED, TheEmptyString, &info).
// Callees setState rowed 0x3FFC28, StringBase copy pinned 0x37050,
// TheEmptyString data 0x00A0C898. TheGameText not touched here.

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED = 1,
	SLOT_EASY_AI = 2,
	SLOT_MED_AI = 3,
	SLOT_BRUTAL_AI = 4,
	SLOT_AI_5 = 5,
	SLOT_PLAYER = 6
};

enum { MAX_SLOTS = 8 };

#include "unicode_string.h"


struct GameSlotConnectInfo
{
	Int m_nat;
	unsigned short m_port;
	unsigned short m_pad;
};

class GameSlot
{
public:
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo);
};

class GameInfo
{
public:
	void clearSlotList();

private:
	char m_pad[0x18];
	GameSlot *m_slot[MAX_SLOTS];
};

void GameInfo::clearSlotList()
{
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		if (m_slot[i])
		{
			GameSlotConnectInfo info;
			info.m_nat = 0;
			info.m_port = 0;
			m_slot[i]->setState(SLOT_CLOSED, UnicodeString::TheEmptyString, &info);
		}
	}
}
