// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
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

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

class NetCommandMsg
{
public:
	UnsignedInt getTimestamp() const { return m_timestamp; }
	UnsignedInt getExecutionFrame() const { return m_executionFrame; }
	Int getNetCommandType() const { return m_commandType; }

protected:
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
};

class NetFrameCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getOriginalFrame() const { return m_originalFrame; }

private:
	UnsignedInt m_originalFrame;
};

class NetCommandRef
{
public:
	~NetCommandRef();
	NetCommandMsg *getCommand() { return m_msg; }
	NetCommandRef *getNext() { return m_next; }
	UnsignedInt getTimeLastSent() const { return m_timeLastSent; }
	void setTimeLastSent(UnsignedInt timeLastSent) { m_timeLastSent = timeLastSent; }

private:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

class NetCommandList
{
public:
	void reset();
	void removeMessage(NetCommandRef *msg);
	NetCommandRef *getFirstMessage() { return m_first; }

private:
	void *m_vptr;
	NetCommandRef *m_first;
	NetCommandRef *m_last;
	NetCommandRef *m_lastMessageInserted;
};

struct NetPacketAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

class NetPacket
{
public:
	NetPacket();
	virtual ~NetPacket();
	void init();
	Bool addCommand(NetCommandRef *msg);
	Int getNumCommands() const { return m_numCommands; }
	Int getLength() const { return m_packetLen; }
	UnsignedByte *getData() { return m_packet; }
	NetPacketAddress *getAddress() { return &m_address; }
	void setAddress(const NetPacketAddress &address) { m_address = address; }

private:
	UnsignedByte m_packet[0x1dc];
	Int m_packetLen;
	NetPacketAddress m_address;
	Int m_numCommands;
	UnsignedByte m_pad1F0[0x204 - 0x1f0];
};

#include "../../Include/GameNetwork/Transport.h"

class GlobalData
{
public:
	char m_pad000[0xc18];
	UnsignedInt m_networkRunAheadSlack;
};

class GameLogic
{
public:
	char m_pad00[0x38];
	UnsignedInt m_timestampFrame;
	char m_pad3C[4];
	UnsignedInt m_frame;
};

extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;
Int CommandRequiresAck(NetCommandMsg *msg);

class Connection
{
public:
	UnsignedInt doSend(Bool throttle);

protected:
	void doRetryMetrics();

private:
	Int m_quitFrame;
	UnsignedInt m_quitTime;
	Transport *m_transport;
	NetPacketAddress m_address;
	void *m_name;
	NetCommandList *m_netCommandList;
	UnsignedInt m_retryTime;
	float m_averageLatency;
	float m_latencies[200];
	UnsignedInt m_frameGrouping;
	UnsignedInt m_lastTimeSent;
	UnsignedInt m_unknown34C;
	Int m_numRetries;
	UnsignedInt m_retryMetricsTime;
};

UnsignedInt Connection::doSend(Bool throttle)
{
	Int numPackets = 0;
	UnsignedInt currentTime = timeGetTime();
	if (currentTime < m_lastTimeSent)
		m_lastTimeSent = currentTime;
	Bool couldQueue = true;

	if (m_quitFrame != -1 && currentTime > m_quitTime + 30000) {
		m_netCommandList->reset();
		return 0;
	}
	if (currentTime - m_lastTimeSent < m_frameGrouping)
		return 0;

	NetCommandRef *msg = m_netCommandList->getFirstMessage();
	while (msg && couldQueue) {
		NetPacket *packet = new NetPacket;
		packet->init();
		packet->setAddress(m_address);
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

						if ((timestamp < TheGameLogic->m_timestampFrame &&
								TheGameLogic->m_frame > TheWritableGlobalData->m_networkRunAheadSlack) ||
							(frame != -1 && frame + TheWritableGlobalData->m_networkRunAheadSlack < TheGameLogic->m_frame)) {
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
			couldQueue = m_transport->queueSend(packet->getAddress(), packet->getData(), packet->getLength());
			if (numPackets > 5 && throttle)
				couldQueue = false;
			m_lastTimeSent = currentTime;
		}
		::delete packet;
	}
	return numPackets;
}
