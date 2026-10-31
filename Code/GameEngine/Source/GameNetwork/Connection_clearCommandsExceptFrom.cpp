// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;

class NetCommandMsg
{
public:
	unsigned int getTimestamp() const { return m_timestamp; }
	unsigned int getExecutionFrame() const { return m_executionFrame; }
	int getNetCommandType() const { return m_commandType; }
	void *m_vptr; // +0x00 +0x00
	unsigned int m_timestamp; // +0x04 +0x04
	unsigned int m_executionFrame; // +0x08 +0x08
	unsigned int m_playerID; // +0x0C +0x0C
	unsigned short m_id; // +0x10 +0x10
	char m_pad12[0x2];
	int m_commandType; // +0x14 +0x14
	int m_referenceCount; // +0x18 +0x18
};

class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	~NetCommandRef();
	__declspec(dllimport) __forceinline NetCommandMsg *getCommand() { return m_msg; }
	__declspec(dllimport) __forceinline NetCommandRef *getNext() { return m_next; }
	unsigned int getTimeLastSent() { return m_timeLastSent; }
	unsigned int getTimeLastSent() const { return m_timeLastSent; }
	void setTimeLastSent(unsigned int timeLastSent) { m_timeLastSent = timeLastSent; }
	void setRelay(unsigned char relay) { m_relay = relay; }
	NetCommandMsg *m_msg; // +0x00 +0x00
	NetCommandRef *m_next; // +0x04 +0x04
	NetCommandRef *m_prev; // +0x08 +0x08
	unsigned char m_relay; // +0x0C +0x0C
	char m_pad0D[0x3];
	unsigned int m_timeLastSent; // +0x10 +0x10
};

class NetCommandList
{
public:
	NetCommandList();
	NetCommandRef *getFirstMessage() { return m_first; }
	void removeMessage(NetCommandRef *msg);
	void reset();
	NetCommandRef *addMessage(NetCommandMsg *msg);
	// The vfptr occupies +0x00.
	virtual ~NetCommandList();
	NetCommandRef *m_first; // +0x04 +0x04
private:
	NetCommandRef *m_last; // +0x08 +0x08
	NetCommandRef *m_lastMessageInserted; // +0x0C +0x0C
};

class Connection
{
public:
	void clearCommandsExceptFrom(Int playerIndex);

	char m_unknown00[0x18];
	NetCommandList *m_netCommandList;
};

void Connection::clearCommandsExceptFrom(Int playerIndex)
{
	NetCommandRef *netCommandRef = m_netCommandList->getFirstMessage();
	while (netCommandRef != 0)
	{
		if (netCommandRef->getCommand()->m_playerID != playerIndex)
		{
			m_netCommandList->removeMessage(netCommandRef);
			NetCommandRef *toDelete = netCommandRef;
			netCommandRef = netCommandRef->getNext();
			delete toDelete;
		}
		else
		{
			netCommandRef = netCommandRef->getNext();
		}
	}
}
