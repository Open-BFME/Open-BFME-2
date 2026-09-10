// ?getCommandCount@FrameDataManager@@QAEII@Z
// partial score=0.9 date=2026-09-10
// cl: /O1 /MD
//
// FrameDataManager::getCommandCount, retail 0x0058B74B, 32 bytes.
// Dedicated TU so FrameDataManagerCounts.cpp cannot see this body.
// Calls and FRAME_DATA_LENGTH DIR32 already match. Near-miss: /O1 emits
// the 29-byte lea form (load m_frameData then lea edx*5*4) matching BFME1.
// Retail is push esi / mov esi,ecx / mov ecx,edx / imul ecx,0x14 /
// add ecx,[esi+4] / call / pop esi. /Og- emits imul but adds an ebp frame.
// getFrameCommandCount at 0x0058B78F is the same leftover.

class FrameData
{
public:
	unsigned getCommandCount();

private:
	char _s[0x14];
};

class FrameDataManager
{
public:
	unsigned getCommandCount(unsigned frame);

private:
	void *vtable;
	FrameData *m_frameData;
};

#define FRAME_DATA_LENGTH (*(const int *)0x00DD2DB8)

unsigned FrameDataManager::getCommandCount(unsigned frame)
{
	unsigned frameindex = frame % FRAME_DATA_LENGTH;
	return m_frameData[frameindex].getCommandCount();
}
