// ?getCommandCount@FrameDataManager@@QAEII@Z
// partial score=0.85 date=2026-09-09
// cl: /O1 /DNDEBUG /MD
//
// FrameDataManager::getCommandCount, retail 0x0058B74B, 32 bytes.
// Dedicated TU so FrameDataManagerCounts.cpp cannot see this body.
// Indexes the 20-byte frame ring by (frame % length) then reads commandCount.

#define FRAME_DATA_LENGTH (*(const unsigned *)0x00DD2DB8)

class FrameData
{
public:
	unsigned getCommandCount();
	unsigned getFrameCommandCount();

private:
	unsigned m_frameCommandCount;
	unsigned m_commandCount;
};

class FrameDataManager
{
	void *vtable;
	FrameData *m_frameData;

public:
	unsigned getCommandCount(unsigned frame);
};

unsigned FrameDataManager::getCommandCount(unsigned frame)
{
	unsigned rem = frame % FRAME_DATA_LENGTH;
	FrameDataManager *self = this;
	FrameData *frames = self->m_frameData;
	return ((FrameData *)((char *)frames + rem * 0x14))->getCommandCount();
}
