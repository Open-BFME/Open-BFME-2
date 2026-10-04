// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /G7 /GX
// ?addNetCommandMsg@FrameDataManager@@QAEPAVNetCommandRef@@PAVNetCommandMsg@@@Z RVA 0x0058B6AB size 38
// Evidence: donor Open-BFME-1 game/GameEngine/Source/GameNetwork/FrameDataManager.cpp
// FrameDataManager::addNetCommandMsg does frame = msg->getExecutionFrame() then
// frame % FRAME_DATA_LENGTH then m_frameData[frameindex].addCommand(msg). Neighbours
// 0x0058B666 reset and 0x0058B6F5 getFrameCommandList prove FrameDataManager with
// m_frameData at +4 and 0x14 stride. Callee row ?addCommand@FrameData@@QAEPAVNetCommandRef@@PAVNetCommandMsg@@@Z.
// Callers at 0x004CF622 0x004CF756 0x004CFFD6. Retail inlines getExecutionFrame to [edi+8].
extern int FRAME_DATA_LENGTH;

class NetCommandMsg
{
public:
	char m_pad[8];
	unsigned int m_executionFrame;
};

class NetCommandRef
{
};

class FrameData
{
public:
	NetCommandRef *addCommand(NetCommandMsg *msg);

private:
	char m_pad[0x14];
};

class FrameDataManager
{
public:
	NetCommandRef *addNetCommandMsg(NetCommandMsg *msg);

private:
	void *m_vtable;
	FrameData *m_frameData;
	bool m_isLocal;
	bool m_isQuitting;
	unsigned int m_quitFrame;
};

NetCommandRef *FrameDataManager::addNetCommandMsg(NetCommandMsg *msg)
{
	unsigned int frame = msg->m_executionFrame;
	unsigned int frameindex = frame % FRAME_DATA_LENGTH;
	return m_frameData[frameindex].addCommand(msg);
}
