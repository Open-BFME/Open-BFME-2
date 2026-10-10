// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Trimmed from Open-BFME-1
// (Code/GameEngine/Source/GameNetwork/Connection.cpp): only the placed
// Connection::isQueueEmpty and Connection::setQuitting bodies are defined
// here. The constructor and doRetryMetrics stay declared-only and the
// donor's other members stay out, so the unmatched-definition gate passes.
// Layout is the donor's: connection id +0x00, opened-time +0x04, stamped by
// winmm timeGetTime; the NetCommandList pointer at +0x18.
//
// ?isQueueEmpty@Connection@@QAE_NXZ, retail 0x0058B9A9, 11 bytes: Zero Hour
// Connection::isQueueEmpty (true when m_netCommandList->getFirstMessage(), the
// list head at +0x04, is NULL). Retail places it directly before setQuitting
// 0x0058B9B4 as Zero Hour's Connection.cpp orders them; its only callers are
// ConnectionManager::areAllQueuesEmpty (0x004CF3C6) and ConnectionManager::update
// (0x004D36B2), which name it. BFME 1 row of the same name: 0x00661C90.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef int Bool;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class NetCommandRef;

class NetCommandList
{
public:
	NetCommandRef *getFirstMessage() { return m_first; }

private:
	void *m_vtbl; // +0x00
	NetCommandRef *m_first; // +0x04
};

class Connection
{
public:
	Connection();
	bool isQueueEmpty();
	void setQuitting(UnsignedInt quitFrame);

protected:
	void doRetryMetrics();

private:
	Int m_id;
	UnsignedInt m_openedTime;
	char m_pad08[0x18 - 0x08];
	NetCommandList *m_netCommandList; // +0x18
};

bool Connection::isQueueEmpty()
{
	if (m_netCommandList->getFirstMessage() == 0) {
		return true;
	}
	return false;
}

void Connection::setQuitting(UnsignedInt quitFrame)
{
	m_id = quitFrame;
	m_openedTime = timeGetTime();
}
