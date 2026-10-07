// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ??1FrameDataManager@@UAE@XZ, retail 0x0058B623, 67 bytes.
// FrameDataManager virtual dtor: stores vtable 0x00870A0C, re-inits each
// 0x14-byte FrameData via rowed ?init@FrameData@@QAEXXZ looping over
// FRAME_DATA_LENGTH (VA 0x00DD2DB8, defined in FrameDataManagerCounts.cpp),
// then delete[]s the array via FrameData's vector deleting dtor
// ??_EFrameData@@QAEPAXI@Z (flags 3, emitted here) and nulls +4. Called from deleting
// dtor 0x0058B86E (28B, test flag bit1 + scalar delete). Evidence: vtable
// store, init loop with 0x14 stride, push 3 + call 0x0058B5D8, FrameData
// neighbours FrameDataManagerReset/Counts.
//

class FrameData
{
public:
	FrameData();
	~FrameData();
	void init();
private:
	char m_pad[0x14];
};

void *operator new[](unsigned int size);
void operator delete[](void *p);

extern int FRAME_DATA_LENGTH;

class FrameDataManager
{
public:
	FrameDataManager(bool isLocal);
	virtual ~FrameDataManager();
private:
	FrameData *m_frameData;
	bool m_isLocal;
	bool m_isQuitting;
	unsigned int m_quitFrame;
};

FrameDataManager::~FrameDataManager()
{
	int i = 0;
	if (FRAME_DATA_LENGTH > 0)
	{
		int off = 0;
		do
		{
			((FrameData *)((char *)m_frameData + off))->init();
			++i;
			off += 0x14;
		} while (i < FRAME_DATA_LENGTH);
	}
	if (m_frameData != 0)
	{
		delete[] m_frameData;
		m_frameData = 0;
	}
}

// Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20
// FrameDataManager.cpp; BFME2's array iterator uses the 20-byte FrameData
// element constructor 0x005DA4C8 and destructor 0x005DA4DC. The manager's existing methods establish
// the storage view and quit-state offsets.
FrameDataManager::FrameDataManager(bool isLocal)
{
 m_isLocal = isLocal;
 m_frameData = new FrameData[FRAME_DATA_LENGTH];
 m_isQuitting = false;
 m_quitFrame = 0;
}
