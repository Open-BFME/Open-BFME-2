// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ??1FrameDataManager@@UAE@XZ, retail 0x0058B623, 67 bytes.
// FrameDataManager virtual dtor: stores vtable 0x00870A0C, re-inits each
// 0x14-byte FrameData via rowed ?init@FrameData@@QAEXXZ looping over
// FRAME_DATA_LENGTH (VA 0x00DD2DB8, defined in FrameDataManagerCounts.cpp),
// then delete[]s the array via rowed vector deleting dtor
// ??_ERva005DA4DC@@QAEPAXI@Z (flags 3) and nulls +4. Called from deleting
// dtor 0x0058B86E (28B, test flag bit1 + scalar delete). Evidence: vtable
// store, init loop with 0x14 stride, push 3 + call 0x0058B5D8, FrameData
// neighbours FrameDataManagerReset/Counts.
//

class FrameData
{
public:
	void init();
private:
	char m_pad[0x14];
};

void *operator new[](unsigned int size);
void operator delete[](void *p);

class Rva005DA4DC
{
public:
	Rva005DA4DC();
	~Rva005DA4DC();
private:
	char m_pad[0x14];
};

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
		delete[] (Rva005DA4DC *)m_frameData;
		m_frameData = 0;
	}
}

// Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20
// FrameDataManager.cpp; BFME2's array iterator uses the rowed 20-byte
// Rva005DA4DC element constructor/destructor pair, not the distinct
// FrameData destructor at 0x70A5D0. The manager's existing methods establish
// the storage view and quit-state offsets.
FrameDataManager::FrameDataManager(bool isLocal)
{
 m_isLocal = isLocal;
 m_frameData = (FrameData *)new Rva005DA4DC[FRAME_DATA_LENGTH];
 m_isQuitting = false;
 m_quitFrame = 0;
}
