// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameNetwork/NetPacketCommandBodies.cpp.
// Target boundary 0x58D387 is the wrapper-capacity helper: it charges packet
// type, relay, timestamp, player and command-ID data then calls the pinned
// NetWrapperCommandMsg::getDataLength target at 0x0030D377. The +0x1F8 packet
// field is compared with command +0x04 in target bytes; its timestamp meaning
// is inferred from the donor's message layout and the sibling frame handler.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
enum { MAX_PACKET_SIZE = 0x1DC };

class NetCommandMsg
{
public:
	Int getNetCommandType() { return m_commandType; }
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedShort getID() { return m_id; }
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
};

class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getDataLength();
};

class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

class NetPacket
{
public:
	virtual ~NetPacket();
protected:
	UnsignedByte m_packet[0x1DC];
	Int m_packetLen;
	UnsignedInt m_destAddress;
	UnsignedShort m_destPort;
	UnsignedShort m_unknown1EA;
	Int m_numCommands;
	NetCommandRef *m_lastCommand;
	UnsignedInt m_unknown1F4;
	UnsignedInt m_lastCommandTimestamp;
	UnsignedShort m_lastCommandID;
	UnsignedByte m_lastPlayerID;
	UnsignedByte m_lastCommandType;
	UnsignedByte m_lastRelay;
	Bool isRoomForWrapperMessage(NetCommandRef *msg);
};

Bool NetPacket::isRoomForWrapperMessage(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)(msg->getCommand());
	if (m_lastCommandType != cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->getRelay()) {
		++len;
		++len;
	}
	if (m_lastCommandTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		++len;
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	++len;
	len += sizeof(UnsignedShort);
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
	len += cmdMsg->getDataLength();
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}
