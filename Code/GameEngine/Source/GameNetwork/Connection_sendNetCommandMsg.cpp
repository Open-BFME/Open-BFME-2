// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

class GameMessage;

class NetCommandMsg
{
public:
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
	NetCommandMsg *getCommand() { return m_msg; }
	NetCommandRef *getNext() { return m_next; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }

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
	virtual ~NetCommandList();
	NetCommandRef *addMessage(NetCommandMsg *msg);
	NetCommandRef *getFirstMessage() { return m_first; }

private:
	NetCommandRef *m_first;
	NetCommandRef *m_last;
	NetCommandRef *m_lastMessageInserted;
};

class NetPacket;
typedef _STL::list<NetPacket *> NetPacketList;

class NetPacket
{
public:
	NetPacket();
	virtual ~NetPacket();
	void reset();
	Bool addCommand(NetCommandRef *msg);
	static NetPacketList ConstructBigCommandPacketList(NetCommandRef *ref);
	NetCommandList *getCommandList();

private:
	UnsignedByte m_data[0x200];
};

class Connection
{
public:
	void sendNetCommandMsg(NetCommandMsg *msg, UnsignedByte relay);

private:
	Int m_quitFrame;
	UnsignedInt m_quitTime;
	void *m_transport;
	UnsignedInt m_address[2];
	void *m_name;
	NetCommandList *m_netCommandList;
};

void Connection::sendNetCommandMsg(NetCommandMsg *msg, UnsignedByte relay)
{
	static NetPacket *packet = 0;

	if (msg->getNetCommandType() == 4)
		((NetGameCommandMsg *)msg)->constructGameMessage();

	if (packet == 0)
		packet = new NetPacket;

	if (m_quitFrame != -1)
		return;
	if (m_netCommandList == 0)
		return;

	packet->reset();
	NetCommandRef *tempref = new NetCommandRef(msg);
	Bool msgFits = packet->addCommand(tempref);
	delete tempref;
	tempref = 0;

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
