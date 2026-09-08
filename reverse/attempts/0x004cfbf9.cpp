// ?hasPacketRouterFrameStall@BFMEConnectionManager@@QAE_NXZ
// partial score=0.8 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// The packet router stalls when an open peer that is not in an active
// connection state falls farther behind the current logic frame than the
// configured run-ahead slack.  BFME2 keeps the same test as BFME1, but the
// network timing fields and the frame-state predicate are BFME2-local.

struct Connection
{
	int m_openState;
};

struct GameLogicFrame
{
	char unknown[0x40];
	unsigned int frame;
};

struct GlobalData
{
	char unknown[0xC18];
	unsigned int networkRunAheadSlack;
};

#define TheGameLogic (*(volatile GameLogicFrame **)0x00DFE78C)
#define TheGlobalData (*(volatile GlobalData **)0x00DFE758)
#define LastPacketRouterStallFrame (*(volatile unsigned int *)0x00E043F4)

class BFMEConnectionManager
{
public:
	bool hasPacketRouterFrameStall(void);
	int isPlayerSlotActive(int slot);

private:
	char unknown0[4];
	Connection *m_connections[8];
	char unknown24[0x12004];
	int m_localSlot;
	int m_packetRouterSlot;
	char unknown12030[0x2C];
	unsigned int m_frameCeiling;
	unsigned int m_playerLatestFrame[8];
};

bool BFMEConnectionManager::hasPacketRouterFrameStall(void)
{
	if (m_localSlot != m_packetRouterSlot)
		return false;

	unsigned int frame = TheGameLogic->frame;
	unsigned int slack = frame > 5 ? TheGlobalData->networkRunAheadSlack : 3;
	int slot = 0;
	Connection **connectionSlot = m_connections;
	for (; slot < 8; ++slot, ++connectionSlot) {
		Connection *connection = *connectionSlot;
		if (connection != 0 && connection->m_openState == -1 &&
			!isPlayerSlotActive(slot) &&
			*(unsigned int *)((char *)connectionSlot + 0x1205C) + slack < frame) {
			unsigned int stalledFrame = *(unsigned int *)((char *)this + slot * 4 + 0x12060);
			if (stalledFrame != LastPacketRouterStallFrame)
				LastPacketRouterStallFrame = stalledFrame;
			return true;
		}
	}
	return false;
}
