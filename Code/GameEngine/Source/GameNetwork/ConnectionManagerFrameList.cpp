// cl: /O1 /G7 /MD /EHsc
// ZH ConnectionManager::getFrameCommandList, donor BFME1 6583b3c1.
// Target 0x004D0027..0x004D00BB keeps the eight-slot list merge, but uses
// frame managers at +0x12104, resetFrame(frame, true), and a Network call
// at vtable +0x60 before the loop. The slot's semantic name is unproven.
// Existing recovered list and FrameDataManager bodies establish all callees.

class NetCommandList
{
public:
	NetCommandList();
	void reset();
	void appendList(NetCommandList *);
private:
	void *m_vtable;
	void *m_first;
	void *m_last;
	void *m_lastMessageInserted;
};

class FrameDataManager
{
public:
	NetCommandList *getFrameCommandList(unsigned int frame);
	void resetFrame(unsigned int frame, bool isAdvancing);
};

class NetworkInterface;
struct FrameListNetworkVTable
{
	void *unknown[24];
	void (__fastcall *slot24)(NetworkInterface *);
};
class NetworkInterface
{
public:
	__forceinline void frameListSlot24() { m_vtable->slot24(this); }
private:
	FrameListNetworkVTable *m_vtable;
};
extern NetworkInterface *TheNetwork;

// ZH NetworkUtil.cpp defines (MAX_FRAMES_AHEAD/2)+1. Target VA 0x00DD2DBC
// contains 65; this body reads it as a runtime global rather than a constant.
int FRAMES_TO_KEEP = 65;

class ConnectionManager
{
public:
	NetCommandList *getFrameCommandList(unsigned int frame);
private:
	char m_prefix[0x12104];
	FrameDataManager *m_frameData[8];
};

NetCommandList *ConnectionManager::getFrameCommandList(unsigned int frame)
{
	NetCommandList *result = new NetCommandList;
	result->reset();
	TheNetwork->frameListSlot24();
	for (int i = 0; i < 8; ++i) {
		if (m_frameData[i]) {
			result->appendList(m_frameData[i]->getFrameCommandList(frame));
			if (frame > FRAMES_TO_KEEP)
				m_frameData[i]->resetFrame(frame - FRAMES_TO_KEEP, true);
		}
	}
	return result;
}
