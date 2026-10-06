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

void operator delete[](void *p);

class Rva005DA4DC
{
public:
	~Rva005DA4DC();
private:
	char m_pad[0x14];
};

extern int FRAME_DATA_LENGTH;

class FrameDataManager
{
public:
	virtual ~FrameDataManager();
private:
	FrameData *m_frameData;
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
