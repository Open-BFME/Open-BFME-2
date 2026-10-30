// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
// ?rva0058BAA7@Connection@@QAEXPAUInitAddrs@@ABVUnicodeString@@H@Z @0x0058BAA7 181B Connection init with address block plus name plus id new NetCommandList plus latencies; evidence: StringBase wide set 0x00037150 NetCommandList new 0x10 ctor 0x0058B06A reset 0x0058B283x2 rep stosd 0xC8 frameGrouping 0x344; callers 0x004D1703 0x004D175B
struct InitAddrs { unsigned int a; unsigned int b; };
class NetCommandRef;
class NetCommandMsg;

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
void Connection::rva0058BAA7(InitAddrs *addrs, const UnicodeString &name, int id)
{
	m_unknown08 = reinterpret_cast<Transport *>(id);
	m_block0C.m_address = *reinterpret_cast<const NetPacketAddress *>(addrs);
	m_block0C.m_name.set(name);
	if (!m_netCommandList) {
		m_netCommandList = new NetCommandList;
		m_netCommandList->reset();
	}
	m_netCommandList->reset();
	m_lastTimeSent = 0;
	m_unknown34C = 0;
	m_numRetries = 0;
	m_retryMetricsTime = 0;
	m_frameGrouping = 1;
	for (int i = 0; i < 200; ++i)
		m_latencies[i] = 0.0f;
	m_id = -1;
	m_openedTime = 0;
	m_averageLatency = 0.0f;
}
