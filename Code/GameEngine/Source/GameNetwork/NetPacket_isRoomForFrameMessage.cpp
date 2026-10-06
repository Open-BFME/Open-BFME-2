// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME1 donor: Code/GameEngine/Source/GameNetwork/NetPacket.cpp.
// Target boundary 0x58D686 (133 B) has the same packet-capacity sequence and
// command fields as BFME1 isRoomForFrameMessage (0x678180, 128 B), with the
// target packet's post-frame state shifted by four bytes. The local class below
// is a TU-only byte-backed layout; it does not assert names for those fields.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
enum { MAX_PACKET_SIZE = 0x1DC };

class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedShort getID() { return m_id; }
	Int getNetCommandType() { return m_commandType; }
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
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
	static class NetCommandMsg *rva0058DE5B(UnsignedByte *data, Int &readOffset);
protected:
	UnsignedByte m_packet[0x1DC];
	Int m_packetLen;
	UnsignedInt m_destAddress;
	UnsignedShort m_destPort;
	UnsignedShort m_unknown1EA;
	Int m_numCommands;
	NetCommandRef *m_lastCommand;
	UnsignedInt m_unknown1F4;
	UnsignedInt m_unknown1F8;
	UnsignedShort m_lastCommandID;
	UnsignedByte m_lastPlayerID;
	UnsignedByte m_lastCommandType;
 UnsignedByte m_lastRelay;
 Bool isRoomForFrameMessage(NetCommandRef *msg);
 UnsignedByte rva0058D513(NetCommandRef *msg);
};

Bool NetPacket::isRoomForFrameMessage(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->getCommand());
	if (m_lastCommandType != cmdMsg->m_commandType) {
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->getRelay()) {
		++len;
		++len;
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		++len;
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}
	if (*(UnsignedInt *)((char *)this + 0x1F8) != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (*(UnsignedInt *)((char *)this + 0x1F4) != cmdMsg->m_executionFrame) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	++len;
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
 if ((len + m_packetLen) > MAX_PACKET_SIZE) {
 	return false;
 }
 return true;
}

UnsignedByte NetPacket::rva0058D513(NetCommandRef *msg)
{
 Int len = 0;
 Bool needNewCommandID = false;
 NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->getCommand());
 if (m_lastCommandType != cmdMsg->m_commandType) {
 	++len;
 	len += sizeof(UnsignedByte);
 }
 if (m_lastRelay != msg->getRelay()) {
 	++len;
 	++len;
 }
 if (m_unknown1F8 != cmdMsg->m_timestamp) {
 	len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
 }
 if (m_lastPlayerID != cmdMsg->getPlayerID()) {
 	++len;
 	++len;
 	needNewCommandID = true;
 }
 if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) ||
 	(needNewCommandID == true)) {
 	len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
 }
 Int total = m_packetLen + len + 6;
 return total <= MAX_PACKET_SIZE;
}

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);

class Rva004D57AE : public NetCommandMsg
{
public:
	Rva004D57AE();
	void setPlayerIndex(UnsignedInt v);
private:
	UnsignedInt m_playerIndex; // +0x1C: NetCommandMsg is 0x1C bytes
};

NetCommandMsg *NetPacket::rva0058DE5B(UnsignedByte *data, Int &readOffset)
{
	Rva004D57AE *msg = new Rva004D57AE;
	UnsignedInt v = 0;
	memcpy(&v, data + readOffset, sizeof(v));
	readOffset += sizeof(v);
	msg->setPlayerIndex(v);
	return msg;
}
