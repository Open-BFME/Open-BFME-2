// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// The first BFME2 connection-manager virtual after the two destructors
// reinitializes frame data and clears the announced frame horizon.  This is a
// reset path, not a normal frame-advance writer.

struct FrameDataManager
{
	void reset(void);
};

class BFMEConnectionManager
{
public:
	void init(void);

private:
	char unknown0[4];
	char unknownConnections[8 * 4];
	char unknown24[0x12004];
	int m_localSlot;
	int m_packetRouterSlot;
	char unknown12030[0x2c];
	int m_frameCeiling;
	int m_playerLatestFrame[8];
	int m_playerState[8];
	int m_playerFlags[8];
	int m_playerFrameCounts[8];
	char unknown120e0[0x24];
	FrameDataManager *m_frameData[8];
	char unknown12124[0x10];
	unsigned char m_initialized;
};

void BFMEConnectionManager::init(void)
{
	FrameDataManager **manager = m_frameData;
	int slotsRemaining = 8;
	do
	{
		if (*manager != 0)
			(*manager)->reset();
		++manager;
	}
	while (--slotsRemaining != 0);

	m_frameCeiling = 0;
	int *frame = (int *)((char *)this + 0x120C0);
	int framesRemaining = 8;
	do
	{
		frame[-24] = 0;
		frame[0] = 0;
		frame[-16] = 0;
		frame[-8] = 1;
		++frame;
	}
	while (--framesRemaining != 0);
	m_initialized = 0;
}
