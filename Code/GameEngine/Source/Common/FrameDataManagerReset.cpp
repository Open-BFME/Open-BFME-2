// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// FrameDataManager::reset clears every fixed-size frame ring entry, marks the
// local manager's expected counts as unknown, and clears its quit state.  The
// ring length and 0x14-byte entry stride are taken directly from retail.

struct FrameData
{
	void init(void);
	void setFrameCommandCount(unsigned int count);
};

class FrameDataManager
{
public:
	void reset(void);

private:
	char unknown0[4];
	FrameData *m_frameData;
	unsigned char m_isLocal;
	unsigned char m_isQuitting;
	char unknownA[2];
	int m_quitFrame;
};

#define FrameDataLength (*(const int *)0x00DD2DB8)

void FrameDataManager::reset(void)
{
	int frame = 0;
	if (FrameDataLength > 0)
	{
		int offset = 0;
		do
		{
			((FrameData *)((char *)m_frameData + offset))->init();
			if (m_isLocal)
				((FrameData *)((char *)m_frameData + offset))
					->setFrameCommandCount((unsigned int)-1);
			++frame;
			offset += 0x14;
		}
		while (frame < FrameDataLength);
	}
	m_quitFrame = 0;
	m_isQuitting = 0;
}
