// cl: /DNDEBUG /MD
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
// platformsdk
//
// Connection::processAck(NetCommandMsg *), retail 0x0058BD7B (37 bytes),
// ported from Zero Hour's GameEngine/Source/GameNetwork/Connection.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference):
// stage-1 and both-stage acks go to processAck for their type. Retail folds
// the two typed overloads (processAck(NetAckStage1CommandMsg *) and
// processAck(NetAckBothCommandMsg *)) into the one rowed body 0x0058BD4F
// (ConnectionRva0058BD4F.cpp), so both branches call it. The command type
// is NetCommandMsg +0x14 (target evidence).

#include <windows.h>

class NetCommandRef;
enum NetCommandType
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1
};
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
class NetAckBothCommandMsg : public NetCommandMsg
{
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
class NetCommandList;
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

NetCommandRef * Connection::processAck(NetCommandMsg *msg) {
	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE1) {
		return rva0058BD4F(msg);
	}

	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH) {
		NetAckBothCommandMsg *ackmsg = (NetAckBothCommandMsg *)msg;
		return processAck(ackmsg);
	}

	return NULL;
}

// Both branches reach the existing owner below. Keep the second overload
// distinct here: using rva0058BD4F in both branches coalesces their call sites,
// whereas retail preserves the two calls to the folded overloads.
//   0x0058BD4F reads ?rva0058BD4F@Connection@@QAEPAVNetCommandRef@@PAX@Z
#pragma comment(linker, "/alternatename:?processAck@Connection@@QAEPAVNetCommandRef@@PAVNetAckBothCommandMsg@@@Z=?rva0058BD4F@Connection@@QAEPAVNetCommandRef@@PAX@Z")
