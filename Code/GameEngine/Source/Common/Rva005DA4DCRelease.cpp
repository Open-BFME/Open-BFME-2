// cl: /MD
//
// ??1FrameData@@QAE@XZ, retail 0x005DA4DC, 29 bytes.
// Zero Hour's FrameData::~FrameData: delete the command list at +8 and null
// it. BFME 2's deleteInstance is the slot-0 deleting destructor with flag 0
// followed by the global operator delete 0x0002FD60 (the ::delete form).
// Identity: FrameDataManager's constructor 0x0058B567 passes this body to the
// eh vector constructor iterator as the destructor of its FrameData array
// (constructor 0x005DA4C8), and FrameData's vector deleting destructor
// 0x0058B5D8 calls it per element.

class NetCommandList
{
public:
	virtual ~NetCommandList();
};

class FrameData
{
public:
	~FrameData();

private:
	unsigned int m_frameCommandCount;
	unsigned int m_commandCount;
	NetCommandList *m_commandList;
};

FrameData::~FrameData()
{
	if (m_commandList != 0)
	{
		::delete m_commandList;
		m_commandList = 0;
	}
}
