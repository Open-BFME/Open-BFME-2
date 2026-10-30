// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
// platformsdk
//
// ?processAck@Connection@@QAEPAVNetCommandRef@@GEII@Z @0x0058B9CA (177B):
// Connection ack retire: walks the pending list at +0x18 via +4 links,
// matches id word at +0x10, player byte at +0x0C, frame at +8 vs arg +0x14,
// timestamp at +4 vs arg +0x10, updates RTT average at +0x20 with per-id
// sample at +0x24[idx] (idx = id % 200) scaled by g_00C1B4F0, stamps
// timeGetTime, handles 32-bit wrap via g_00BC26EC, removes the message via
// rowed removeMessage and returns it (null if none). Evidence: unlock lane,
// BFME1 donor Connection_processAck.cpp 3-arg processAck plus timestamp,
// neighbours setQuitting/doRetryMetrics, sole callee rowed plus IAT
// timeGetTime, caller 0x0058BD71 forwards +0x1C/+0x1E/+0x20/+0x24.
#include <windows.h>

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

extern const float g_00BC26EC;

class NetCommandMsg
{
public:
	unsigned int getTimestamp() const { return m_timestamp; }
	unsigned int getExecutionFrame() const { return m_executionFrame; }
	int getNetCommandType() const { return m_commandType; }

	void *m_vptr; // +0x00
	unsigned int m_timestamp; // +0x04
	unsigned int m_executionFrame; // +0x08
	unsigned int m_playerID; // +0x0C
	unsigned short m_id; // +0x10
	int m_commandType; // +0x14
	int m_referenceCount; // +0x18
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

	NetCommandMsg *m_msg; // +0x00
	NetCommandRef *m_next; // +0x04
	NetCommandRef *m_prev; // +0x08
	unsigned char m_relay; // +0x0C
	unsigned int m_timeLastSent; // +0x10
};


class NetCommandList
{
public:
	NetCommandList();
	// The vfptr occupies +0x00.
	virtual ~NetCommandList();
	NetCommandRef *getFirstMessage() { return m_first; }
	void removeMessage(NetCommandRef *msg);
	void reset();
	NetCommandRef *addMessage(NetCommandMsg *msg);

private:
	NetCommandRef *m_first; // +0x04
	NetCommandRef *m_last; // +0x08
	NetCommandRef *m_lastMessageInserted; // +0x0C
};

#define CONNECTION_LATENCY_HISTORY_LENGTH 200

struct NetPacketAddress
{
	NetPacketAddress() : ip(0), port(0) {}
	unsigned int ip;
	unsigned short port;
};

struct ConnectionBlock0C
{
	NetPacketAddress m_address;
	UnicodeString m_name;
};

class Transport;
class NetAckBothCommandMsg;
struct InitAddrs;

class Connection
{
public:
	Connection();
	bool isQueueEmpty();
	void setQuitting(unsigned int quitFrame);
	NetCommandRef *processAck(unsigned short commandID, unsigned char playerID, unsigned int timestamp, unsigned int executionFrame);
	void rva0058BAA7(InitAddrs *addrs, const UnicodeString &name, int id);
	unsigned int doSend(bool throttle);
	NetCommandRef *rva0058BD4F(void *msg);
	NetCommandRef *processAck(NetCommandMsg *msg);
	NetCommandRef *processAck(NetAckBothCommandMsg *msg);
	void sendNetCommandMsg(NetCommandMsg *msg, unsigned char relay);

protected:
	void doRetryMetrics();

private:
	int m_id;
	unsigned int m_openedTime;
	Transport *m_unknown08;
	ConnectionBlock0C m_block0C;
	NetCommandList *m_netCommandList;
	long m_retryTime;
	float m_averageLatency;
	float m_latencies[200];
	long m_frameGrouping;
	long m_lastTimeSent;
	unsigned int m_unknown34C;
	int m_numRetries;
	unsigned int m_retryMetricsTime;
};

NetCommandRef *Connection::processAck(UnsignedShort commandID, UnsignedByte playerID, UnsignedInt timestamp, UnsignedInt executionFrame)
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
	m_averageLatency -= m_latencies[latencyHistoryIndex] * 0.005f;
	Real roundTripMilliseconds = (Real)(timeGetTime() - pendingCommandRef->getTimeLastSent());
	m_averageLatency += roundTripMilliseconds * 0.005f;
	m_latencies[latencyHistoryIndex] = roundTripMilliseconds;
	m_netCommandList->removeMessage(pendingCommandRef);
	return pendingCommandRef;
}
