// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
// platformsdk
// ?doSend@Connection@@QAEI_N@Z, retail 0x0058BB5C 499 bytes through RET 4.
// Donor: Open-BFME-1 game/GameEngine/Source/GameNetwork/Connection_doSend.cpp
// (BFME Connection::doSend 0x00661F10), carried with its loop shape and names.
// Target evidence: timeGetTime IAT call, quit window 30000 ms at +0x0/+0x4,
// NetCommandList::reset 0x0058B283 on the list at +0x18, frameGrouping +0x344,
// lastTimeSent +0x348, operator new 0x204 + NetPacket ctor 0x0058E5B4 and
// init 0x0058D10A, addCommand 0x005944D8, CommandRequiresAck 0x00581229,
// doRetryMetrics 0x0058BA7B (called, not inlined as in BFME), numRetries
// +0x350, removeMessage 0x0058B07E, ~NetCommandRef 0x0058B8AE,
// Transport::queueSend 0x004D4EC6 on the transport at +0x8, and the packet
// released through its slot-0 deleting dtor with flag 0 plus the global
// operator delete (::delete). BFME 2 adds a retire test before the donor's
// frame-slack test: a command stamped before TheGameLogic+0x38 is retired
// once TheGameLogic+0x40 exceeds the run-ahead slack (TheWritableGlobalData
// +0xC18).

#include <windows.h>
#include "../../Include/GameNetwork/Transport.h"
#include "../Common/GameLogicObjectLookupView.h"
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

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

class NetFrameCommandMsg : public NetCommandMsg
{
public:
	unsigned int getOriginalFrame() const { return m_originalFrame; }

private:
	unsigned int m_originalFrame;
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

struct NetPacketAddress
{
	NetPacketAddress() : ip(0), port(0) {}
	unsigned int ip;
	unsigned short port;
};

class NetPacket
{
public:
	NetPacket();
	virtual ~NetPacket();
	void init();
	bool addCommand(NetCommandRef *msg);
	int getNumCommands() const { return m_numCommands; }
	int getLength() const { return m_packetLen; }
	unsigned char *getData() { return m_packet; }
	NetPacketAddress *getAddress() { return &m_address; }
	void setAddress(const NetPacketAddress &address) { m_address = address; }

private:
	unsigned char m_packet[0x1dc];
	int m_packetLen;
	NetPacketAddress m_address;
	int m_numCommands;
	unsigned char m_pad1F0[0x204 - 0x1f0];
};


class GlobalData
{
public:
	char m_pad000[0xc18];
	unsigned int m_networkRunAheadSlack;
};


extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;
Bool CommandRequiresAck(NetCommandMsg *msg);

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

UnsignedInt Connection::doSend(Bool throttle)
{
	Int numPackets = 0;
	UnsignedInt currentTime = timeGetTime();
	if (currentTime < m_lastTimeSent)
		m_lastTimeSent = currentTime;
	Bool couldQueue = true;

	if (m_id != -1 && currentTime > m_openedTime + 30000) {
		m_netCommandList->reset();
		return 0;
	}
	if (currentTime - m_lastTimeSent < m_frameGrouping)
		return 0;

	NetCommandRef *msg = m_netCommandList->getFirstMessage();
	while (msg && couldQueue) {
		NetPacket *packet = new NetPacket;
		packet->init();
		packet->setAddress(m_block0C.m_address);
		Bool notDone = true;

		while (msg && notDone) {
			NetCommandRef *next = msg->getNext();
			UnsignedInt timeLastSent = msg->getTimeLastSent();
			if (currentTime - timeLastSent > m_retryTime || timeLastSent == -1) {
				notDone = packet->addCommand(msg);
				if (notDone) {
					if ((UnsignedByte)CommandRequiresAck(msg->getCommand())) {
						if (timeLastSent != -1)
							++m_numRetries;
						doRetryMetrics();
						msg->setTimeLastSent(currentTime);

						NetCommandMsg *cmd = msg->getCommand();
						UnsignedInt timestamp = cmd->getTimestamp();
						UnsignedInt frame;
						if (cmd->getNetCommandType() == 3)
							frame = ((NetFrameCommandMsg *)cmd)->getOriginalFrame();
						else
							frame = cmd->getExecutionFrame();

						if ((timestamp < TheGameLogic->getTimestamp() &&
								TheGameLogic->getFrame() > TheWritableGlobalData->m_networkRunAheadSlack) ||
							(frame != -1 && frame + TheWritableGlobalData->m_networkRunAheadSlack < TheGameLogic->getFrame())) {
							m_netCommandList->removeMessage(msg);
							delete msg;
						}
					} else {
						m_netCommandList->removeMessage(msg);
						delete msg;
					}
				}
			}
			msg = next;
		}

		++numPackets;
		if (packet->getNumCommands() > 0) {
			couldQueue = m_unknown08->queueSend(packet->getAddress(), packet->getData(), packet->getLength());
			if (numPackets > 5 && throttle)
				couldQueue = false;
			m_lastTimeSent = currentTime;
		}
		::delete packet;
	}
	return numPackets;
}
