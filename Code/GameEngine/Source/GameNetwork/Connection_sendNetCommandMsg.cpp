// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
// stlport
// ?sendNetCommandMsg@Connection@@QAEXPAVNetCommandMsg@@E@Z, retail 0x0058BDFA
// 430 bytes through RET 8.
// Donor: Open-BFME-1 game/GameEngine/Source/GameNetwork/Connection_sendNetCommandMsg.cpp
// (BFME Connection::sendNetCommandMsg 0x006624A0), carried with its names and
// loop shape. Target evidence: six ConnectionManager call sites 0x004CF52E..
// 0x004D0007; quitFrame -1 test at +0x0 and command list at +0x18; the static
// reusable packet at 0x00A063AC built with operator new 0x204 + NetPacket ctor
// 0x0058E5B4 and reset 0x0058D160; NetCommandRef ctor 0x0058B88A with relay at
// +0xC and ~NetCommandRef 0x0058B8AE; NetPacket::addCommand 0x005944D8;
// NetCommandList::addMessage 0x0058B2C6; ConstructBigCommandPacketList
// 0x005946E1 returning the packet list through a hidden pointer, each packet's
// getCommandList 0x00593F15, packets and lists released through their slot-0
// deleting dtors with flag 0 plus the global operator delete, and the list
// destroyed through _List_base's dtor (ICF-folded with list<int> at 0x004EC395).
// BFME 2 adds the leading NetGameCommandMsg::constructGameMessage 0x004D68C6
// call for game commands (type 4), its result unused. /EHs (not /EHsc) keeps the
// EH state reset before the list's destructor, as AIGroupGroupEnter.cpp found.
#include <list>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

class GameMessage;

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

class NetGameCommandMsg : public NetCommandMsg
{
public:
	GameMessage *constructGameMessage();
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

class NetPacket;
typedef _STL::list<NetPacket *> NetPacketList;

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
	void reset();
	static NetPacketList ConstructBigCommandPacketList(NetCommandRef *ref);
	NetCommandList *getCommandList();

private:
	unsigned char m_packet[0x1dc];
	int m_packetLen;
	NetPacketAddress m_address;
	int m_numCommands;
	unsigned char m_pad1F0[0x204 - 0x1f0];
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

void Connection::sendNetCommandMsg(NetCommandMsg *msg, UnsignedByte relay)
{
	static NetPacket *packet = 0;

	if (msg->getNetCommandType() == 4)
		((NetGameCommandMsg *)msg)->constructGameMessage();

	if (packet == 0)
		packet = new NetPacket;

	if (m_id != -1)
		return;
	if (m_netCommandList == 0)
		return;

	packet->reset();
	NetCommandRef *netCommandRef = new NetCommandRef(msg);
	Bool msgFits = packet->addCommand(netCommandRef);
	delete netCommandRef;
	netCommandRef = 0;

	if (!msgFits) {
		NetCommandRef *origref = new NetCommandRef(msg);
		origref->setRelay(relay);
		NetPacketList packetList = NetPacket::ConstructBigCommandPacketList(origref);
		NetPacketList::iterator packetIt = packetList.begin();
		while (packetIt != packetList.end()) {
			NetPacket *packet = *packetIt;
			NetCommandList *list = packet->getCommandList();
			NetCommandRef *ref1 = list->getFirstMessage();
			while (ref1 != 0) {
				NetCommandRef *ref2 = m_netCommandList->addMessage(ref1->getCommand());
				ref2->setRelay(relay);
				ref1 = ref1->getNext();
			}
			::delete packet;
			packet = 0;
			++packetIt;
			::delete list;
			list = 0;
		}
		delete origref;
		origref = 0;
	} else {
		NetCommandRef *ref = m_netCommandList->addMessage(msg);
		if (ref != 0)
			ref->setRelay(relay);
	}
}
