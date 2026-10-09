// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ?rva0058B9CA@Connection@@QAEPAVNetCommandRef@@GEII@Z @0x0058B9CA (177B):
// Connection ack retire: walks the pending list at +0x18 via +4 links,
// matches id word at +0x10, player byte at +0x0C, frame at +8 vs arg +0x14,
// timestamp at +4 vs arg +0x10, updates RTT average at +0x20 with per-id
// sample at +0x24[idx] (idx = id % 200) scaled by g_00C1B4F0, stamps
// timeGetTime, handles 32-bit wrap via g_00BC26EC, removes the message via
// rowed removeMessage and returns it (null if none). Evidence: unlock lane,
// BFME1 donor Connection_processAck.cpp 3-arg processAck plus timestamp,
// neighbours setQuitting/doRetryMetrics, sole callee rowed plus IAT
// timeGetTime, caller 0x0058BD71 forwards +0x1C/+0x1E/+0x20/+0x24.
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

extern const float g_00C1B4F0;
extern const float g_00BC26EC;

class NetCommandMsg
{
public:
	void *m_vptr; // +0x00
	UnsignedInt m_timestamp; // +0x04
	UnsignedInt m_executionFrame; // +0x08
	UnsignedInt m_playerID; // +0x0C
	UnsignedShort m_id; // +0x10
	Int m_commandType; // +0x14
	Int m_referenceCount; // +0x18
};

class NetCommandRef
{
public:
	__declspec(dllimport) __forceinline NetCommandMsg *getCommand() { return m_msg; }
	__declspec(dllimport) __forceinline NetCommandRef *getNext() { return m_next; }
	UnsignedInt getTimeLastSent() { return m_timeLastSent; }

	NetCommandMsg *m_msg; // +0x00
	NetCommandRef *m_next; // +0x04
	NetCommandRef *m_prev; // +0x08
	UnsignedInt m_retryCount; // +0x0C
	UnsignedInt m_timeLastSent; // +0x10
};

class NetCommandList
{
public:
	NetCommandRef *getFirstMessage() { return m_first; }
	void removeMessage(NetCommandRef *msg);

	void *m_vptr; // +0x00
	NetCommandRef *m_first; // +0x04
};

enum { CONNECTION_LATENCY_HISTORY_LENGTH = 200 };

class Connection
{
public:
	NetCommandRef *rva0058B9CA(UnsignedShort commandID, UnsignedByte playerID, UnsignedInt timestamp, UnsignedInt executionFrame);

	char m_beforeCommandList[0x18]; // +0x00
	NetCommandList *m_netCommandList; // +0x18
	UnsignedInt m_betweenListAndLatency; // +0x1C
	Real m_averageLatency; // +0x20
	Real m_latencies[CONNECTION_LATENCY_HISTORY_LENGTH]; // +0x24
};

NetCommandRef *Connection::rva0058B9CA(UnsignedShort commandID, UnsignedByte playerID, UnsignedInt timestamp, UnsignedInt executionFrame)
{
	NetCommandRef *pendingCommandRef = m_netCommandList->getFirstMessage();
	NetCommandMsg *cmd = 0;
	while (pendingCommandRef != 0) {
		cmd = pendingCommandRef->getCommand();
		if (cmd->m_id == commandID && cmd->m_playerID == playerID &&
			cmd->m_executionFrame == executionFrame && cmd->m_timestamp == timestamp)
			break;
		pendingCommandRef = pendingCommandRef->getNext();
	}
	if (pendingCommandRef == 0) {
		return 0;
	}
	Int latencyHistoryIndex = cmd->m_id % CONNECTION_LATENCY_HISTORY_LENGTH;
	m_averageLatency -= m_latencies[latencyHistoryIndex] * g_00C1B4F0;
	Real roundTripMilliseconds = (Real)(timeGetTime() - pendingCommandRef->getTimeLastSent());
	m_averageLatency += roundTripMilliseconds * g_00C1B4F0;
	m_latencies[latencyHistoryIndex] = roundTripMilliseconds;
	m_netCommandList->removeMessage(pendingCommandRef);
	return pendingCommandRef;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00C1B4F0@@3MB=?g_00C1B4F0@@3MA")
