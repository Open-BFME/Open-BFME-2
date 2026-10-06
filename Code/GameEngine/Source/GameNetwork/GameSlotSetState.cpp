// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?setState@GameSlot@@QAEXW4SlotState@@VUnicodeString@@PBUGameSlotConnectInfo@@@Z @0x003FFC28 (399B):
// GameSlot::setState. BFME1 GameInfo.cpp donor (GameSlot::setState) with BFME2
// deltas proven by retail: SLOT_PLAYER 6 with new AI state 5, clear of six ints
// (color/start/bfme14 -1, template -2, team -1, bfme20 0), virtual reset at +0x10,
// GUI:Open/EasyAI/MediumAI/HardAI/BrutalAI/Closed fetch+set with EH temps,
// connectInfo 8B copy to +0x38. Callees isAI rowed 0x3FF127, set pinned 0x37150,
// releaseBuffer rowed 0x36E70. TheGameText VA 0x009FF0BC fetch slot 0x3C.

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

#include "ascii_string.h"


#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

struct GameSlotConnectInfo
{
	unsigned int m_nat;
	unsigned int m_port;
};

class GameSlot
{
public:
	virtual void _v0();
	virtual void _v4();
	virtual void _v8();
	virtual void _vC();
	virtual void reset();
	Bool isAI() const;
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo);

private:
	Int m_state;                    // +0x04
	Bool m_isAccepted;              // +0x08
	Bool m_hasMap;                  // +0x09
	Bool m_isMuted;                 // +0x0A
	char m_pad0B;                   // +0x0B
	Int m_color;                    // +0x0C
	Int m_startPos;                 // +0x10
	Int m_bfme14;                   // +0x14
	Int m_playerTemplate;           // +0x18
	Int m_teamNumber;               // +0x1C
	Int m_bfme20;                   // +0x20
	Int m_origColor;                // +0x24
	Int m_origStartPos;             // +0x28
	Int m_origPlayerTemplate;       // +0x2C
	UnicodeString m_name;           // +0x30
	AsciiString m_ip;               // +0x34
	GameSlotConnectInfo m_connectInfo; // +0x38
};

void GameSlot::setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo)
{
	if (!(isAI() && (state == SLOT_EASY_AI || state == SLOT_MED_AI || state == SLOT_BRUTAL_AI || state == SLOT_AI_5)))
	{
		m_color = -1;
		m_startPos = -1;
		m_bfme14 = -1;
		m_playerTemplate = -2;
		m_teamNumber = -1;
		m_bfme20 = 0;
	}
	if (state == SLOT_PLAYER)
	{
		reset();
		m_state = state;
		m_name = name;
	}
	else
	{
		m_state = state;
		m_isAccepted = true;
		m_hasMap = true;
		switch (state)
		{
		case SLOT_OPEN:
			m_name = TheGameText->fetch("GUI:Open");
			break;
		case SLOT_EASY_AI:
			m_name = TheGameText->fetch("GUI:EasyAI");
			break;
		case SLOT_MED_AI:
			m_name = TheGameText->fetch("GUI:MediumAI");
			break;
		case SLOT_BRUTAL_AI:
			m_name = TheGameText->fetch("GUI:HardAI");
			break;
		case SLOT_AI_5:
			m_name = TheGameText->fetch("GUI:BrutalAI");
			break;
		case SLOT_CLOSED:
		default:
			m_name = TheGameText->fetch("GUI:Closed");
			break;
		}
	}
	m_connectInfo = *connectInfo;
}
