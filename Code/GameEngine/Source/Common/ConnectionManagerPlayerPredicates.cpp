// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// These predicates sit directly on the BFME2 frame-stall and command-routing
// paths.  The state predicate accepts states 1 through 3; the connection
// predicate treats the local slot as connected and otherwise requires the
// peer's open-state sentinel.

extern class GameLogic *TheGameLogic;

struct Connection
{
	int m_openState;
};

struct GameLogicFrame
{
	char unknown[0x40];
	unsigned int frame;
};

class GlobalData
{
public:
	char unknown[0xC18];
	unsigned int networkRunAheadSlack;
};

#define TheGameLogic (*(volatile GameLogicFrame **)&TheGameLogic)
extern GlobalData *TheWritableGlobalData;
// g_00E043F4: VA 0x00E043F4 (.data(bss)); retail initial value is zero.
unsigned int g_00E043F4 = 0;

class BFMEConnectionManager
{
public:
	bool isPlayerConnected(int slot);
	bool isPlayerInGame(int slot);
	int isPlayerSlotActive(int slot);
	bool hasPacketRouterFrameStall(void);

private:
	char unknown0[4];
	Connection *m_connections[8];
	char unknown24[0x12004];
	int m_localSlot;
	int m_packetRouterSlot;
	char unknown12030[0x2C];
	unsigned int m_frameCeiling;
	unsigned int m_playerLatestFrame[8];
	int m_playerState[8];
};

bool BFMEConnectionManager::isPlayerConnected(int slot)
{
	return slot == m_localSlot ||
		(m_connections[slot] != 0 && m_connections[slot]->m_openState == -1);
}

// Bool: its callers (doRelay 0x004D325F, the disconnect manager's slot loops)
// test al; returning the && chain gives the whole-register xor/inc tail.
bool BFMEConnectionManager::isPlayerInGame(int slot)
{
	return (unsigned int)slot < 8 && m_playerState[slot] == 1 &&
		isPlayerConnected(slot);
}

int BFMEConnectionManager::isPlayerSlotActive(int slot)
{
	if ((unsigned int)slot >= 8 || m_playerState[slot] < 1 ||
		m_playerState[slot] > 3 || !isPlayerConnected(slot))
		return 0;
	return 1;
}

bool BFMEConnectionManager::hasPacketRouterFrameStall(void)
{
	if (m_localSlot != m_packetRouterSlot)
		return false;

	unsigned int frame = TheGameLogic->frame;
	unsigned int slack = frame > 5 ? TheWritableGlobalData->networkRunAheadSlack : 3;
	int slot = 0;
	Connection **connectionSlot = m_connections;
	for (; slot < 8; ++slot, ++connectionSlot) {
		Connection *connection = *connectionSlot;
		if (connection != 0 && connection->m_openState == -1 &&
			(unsigned char)isPlayerSlotActive(slot) == 0 &&
			*(unsigned int *)((char *)connectionSlot + 0x1205C) + slack <= frame) {
			unsigned int stalledFrame = *(unsigned int *)((char *)this + slot * 4 + 0x12060);
			if (stalledFrame != g_00E043F4)
				g_00E043F4 = stalledFrame;
			return true;
		}
	}
	return false;
}
