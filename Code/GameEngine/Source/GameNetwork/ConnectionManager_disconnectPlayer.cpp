// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ConnectionManager::disconnectPlayer, retail 0x004D13F8, 511 bytes.
//
// Reference: Zero Hour GameEngine/Source/GameNetwork/ConnectionManager.cpp
// disconnectPlayer (slot range test, the game slot's last frame, the "player
// left" message, freeing the slot's frame data and connection, packet router
// succession and removal from the fallback plan, and the leave code).
// BFME 2 differences read from this body: the sound is the chat notification
// 0x004CF145; the connection is freed only when its +0 field is -1 (Zero Hour
// tested isQuitting) through its non-virtual destructor 0x004D060B; the slot's
// state at +0x12080 becomes 3; and router succession clears the command-ID
// histories (0x2000-byte bitsets from +0x24, cleared by 0x004D04C9) of the old
// and new router, plus the ninth (client) history when this machine is not the
// new router. The history array and the fallback plan at +0x12030 follow
// Open-BFME-1's BFMEConnectionManager layout (native_connection_timing.cpp).
// Retail forms a router history's address before moving it to ECX, which the
// named pointer reproduces.

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum PlayerLeaveCode
{
	PLAYERLEAVECODE_CLIENT = 0,
	PLAYERLEAVECODE_LOCAL,
	PLAYERLEAVECODE_PACKETROUTER,
	PLAYERLEAVECODE_UNKNOWN
};

enum
{
	MAX_SLOTS = 8
};

class GameSlot
{
public:
	UnsignedInt lastFrameInGame() const { return m_lastFrameInGame; }
	void setLastFrameInGame(UnsignedInt frame) { m_lastFrameInGame = frame; }

private:
	char m_pad00[0x44];
	UnsignedInt m_lastFrameInGame;
};

class GameInfo
{
public:
	GameSlot *getSlot(Int index);
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	char m_pad00[0x40];
	UnsignedInt m_frame;
};

class InGameUI
{
public:
#define UI_SLOT(n) virtual void slot##n();
	UI_SLOT(00) UI_SLOT(01) UI_SLOT(02) UI_SLOT(03) UI_SLOT(04)
	UI_SLOT(05) UI_SLOT(06) UI_SLOT(07) UI_SLOT(08) UI_SLOT(09)
	UI_SLOT(10) UI_SLOT(11) UI_SLOT(12) UI_SLOT(13) UI_SLOT(14)
	UI_SLOT(15) UI_SLOT(16) UI_SLOT(17)
#undef UI_SLOT
	virtual void __cdecl message(AsciiString stringManagerLabel, ...); // +0x48
};

// The frame data ring: deleted through its slot-0 virtual destructor.
class FrameDataManager
{
public:
	virtual ~FrameDataManager();
	Bool getIsQuitting();
};

// Connection, held in the ledger under its destructor's address name.
class Rva004D060B
{
public:
	~Rva004D060B();
	Int getQuitState() const { return m_quitState; }

private:
	Int m_quitState;
};

// One 0x2000-byte command-ID bitset; 0x004D04C9 clears it.
class Rva004D04C9
{
public:
	void *rva004D04C9();

private:
	UnsignedInt m_bits[0x800];
};

extern GameInfo *TheGameInfo;
extern GameLogic *TheGameLogic;
extern InGameUI *TheInGameUI;

void Rva004CF145();

class ConnectionManager
{
public:
	PlayerLeaveCode disconnectPlayer(Int slot);
	UnicodeString getPlayerName(Int playerID);

private:

	void *m_vptr;
	Rva004D060B *m_connections[MAX_SLOTS];
	Rva004D04C9 m_commandHistory[MAX_SLOTS + 1];
	void *m_transport;
	UnsignedInt m_localSlot;
	UnsignedInt m_packetRouterSlot;
	Int m_packetRouterFallback[MAX_SLOTS];
	char m_pad12050[0x12080 - 0x12050];
	Int m_playerState[MAX_SLOTS];
	char m_pad120A0[0x12104 - 0x120a0];
	FrameDataManager *m_frameData[MAX_SLOTS];
};

PlayerLeaveCode ConnectionManager::disconnectPlayer(Int slot)
{
	PlayerLeaveCode retval = PLAYERLEAVECODE_CLIENT;

	if ((slot < 0) || (slot >= MAX_SLOTS))
		return PLAYERLEAVECODE_UNKNOWN;

	if (TheGameInfo)
	{
		GameSlot *gSlot = TheGameInfo->getSlot(slot);
		if (gSlot && !gSlot->lastFrameInGame())
			gSlot->setLastFrameInGame(TheGameLogic->getFrame());
	}

	UnicodeString unicodeName;
	unicodeName = getPlayerName(slot);
	if (unicodeName.getLength() > 0 && m_connections[slot])
	{
		TheInGameUI->message("Network:PlayerLeftGame", unicodeName.str());
		Rva004CF145();
	}

	if ((m_frameData[slot] != 0) && (m_frameData[slot]->getIsQuitting() == false))
	{
		::delete m_frameData[slot];
		m_frameData[slot] = 0;
	}

	if (m_connections[slot] != 0 && m_connections[slot]->getQuitState() == -1)
	{
		delete m_connections[slot];
		m_connections[slot] = 0;
	}

	m_playerState[slot] = 3;

	if (slot == m_packetRouterSlot)
	{
		if (m_packetRouterSlot < MAX_SLOTS)
		{
			Rva004D04C9 *history = &m_commandHistory[m_packetRouterSlot];
			history->rva004D04C9();
		}
		UnsignedInt index = 0;
		while ((index < (MAX_SLOTS - 1)) && (m_packetRouterFallback[index] != m_packetRouterSlot))
			++index;
		++index;
		m_packetRouterSlot = m_packetRouterFallback[index];
		if (m_packetRouterSlot < MAX_SLOTS)
		{
			Rva004D04C9 *history = &m_commandHistory[m_packetRouterSlot];
			history->rva004D04C9();
		}
		if (m_localSlot != m_packetRouterSlot)
			m_commandHistory[MAX_SLOTS].rva004D04C9();
		retval = PLAYERLEAVECODE_PACKETROUTER;
	}
	if (m_localSlot == slot)
		retval = PLAYERLEAVECODE_LOCAL;

	// Take the player out of the fallback plan
	Int fallbackindex = 0;
	while ((fallbackindex < MAX_SLOTS) && (m_packetRouterFallback[fallbackindex] != slot))
		++fallbackindex;

	for (Int i = fallbackindex; i < MAX_SLOTS - 1; ++i)
		m_packetRouterFallback[i] = m_packetRouterFallback[i + 1];
	m_packetRouterFallback[MAX_SLOTS - 1] = -1;

	return retval;
}
