// cl: /DNDEBUG /MD /EHsc

// Target boundary 0x0070A5D0/24 (Ghidra). The BFME2 FrameData::init body at
// 0x005DA4F9 establishes m_commandList at +0x08. Retail here null-checks
// that field, dispatches its vtable slot +0x04, then clears the field.
// The BFME1 FrameData destructor performs this same deleteInstance-and-null
// operation; this is distinct from FrameData::destroyGameMessages, which
// resets the list and clears the command count.

class NetCommandList
{
public:
	virtual void reservedSlot0();
	virtual void deleteInstance();
};

class FrameData
{
public:
	~FrameData();

private:
	unsigned int m_frameCommandCount;
	unsigned int m_commandCount;
	NetCommandList *m_commandList;
	unsigned int m_lastFailedCC;
	unsigned int m_lastFailedFrameCC;
};

FrameData::~FrameData()
{
	NetCommandList *commandList = m_commandList;
	if (commandList != 0)
	{
		commandList->deleteInstance();
		*(volatile unsigned int *)((char *)this + 0x08) = 0;
	}
}
