// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2's client frame gate totals the command counts held by its eight
// per-player frame rings.  The local ring stores the expected total; the
// aggregate is complete only when those values agree for the requested frame.

struct FrameDataManager
{
	bool getIsQuitting(void);
	unsigned int getCommandCount(unsigned int frame);
	unsigned int getFrameCommandCount(unsigned int frame);
};

class BFMEConnectionManager
{
public:
	bool areFrameCommandsComplete(unsigned int frame, bool debugSpewage);

private:
	char unknown[0x12028];
	unsigned int m_localSlot;
	char unknown1202c[0xd8];
	FrameDataManager *m_frameData[8];
};

bool BFMEConnectionManager::areFrameCommandsComplete(unsigned int frame,
	bool debugSpewage)
{
	FrameDataManager **manager;
	unsigned int commandCount = 0;
	manager = m_frameData;
	int slotsRemaining = 8;
	do
	{
		if (*manager != 0 && !(*manager)->getIsQuitting())
			commandCount += (*manager)->getCommandCount(frame);
		++manager;
	}
	while (--slotsRemaining != 0);

	unsigned int expected = m_frameData[m_localSlot]->getFrameCommandCount(frame);
	if (expected != commandCount)
		return false;
	return true;
}
