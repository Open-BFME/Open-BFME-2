// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ?rva0058D211@NetPacket@@QAE_NPAVNetCommandRef@@@Z, retail 0x0058D211, 133 bytes.
// NetPacket room check sibling of isRoomForWrapperMessage 0x0058D387: charges
// type/relay/timestamp/frame/player/ID deltas (2/2/5/5/2/3) plus fixed 5 over
// base +0x1E0 and returns room<=0x1DC. Evidence: identical NetPacket tail
// layout +0x1F4/+0x1F8/+0x1FC/+0x1FE/+0x1FF/+0x200 and MAX 0x1DC as the
// sibling; callers 0x0058EB9A 0x0058FFBD. Honest address method of NetPacket.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
enum { MAX_PACKET_SIZE = 0x1DC };

class NetCommandMsg
{
public:
	UnsignedByte m_pad0[4];
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	UnsignedShort m_pad0C;
	UnsignedInt m_commandType;
	UnsignedByte m_pad18[0x28 - 0x18];
	UnsignedInt m_dataLen28;
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
	UnsignedByte m_pad0D[3];
	UnsignedInt m_timeLastSent;
};

class NetPacket
{
public:
	Bool rva0058D211(NetCommandRef *msg);
	Bool rva0058D310(NetCommandRef *msg);
	Bool rva0058D58A(NetCommandRef *msg);
	Bool rva0058D296(NetCommandRef *msg);
	Bool rva0058D601(NetCommandRef *msg);
private:
	UnsignedByte m_pad0[0x1E0];
	Int m_packetLen;
	UnsignedByte m_pad1[0x1F4 - 0x1E0 - 4];
	UnsignedInt m_lastFrame1F4;
	UnsignedInt m_lastTimestamp1F8;
	UnsignedShort m_lastID1FC;
	UnsignedByte m_lastPlayer1FE;
	UnsignedByte m_lastType1FF;
	UnsignedByte m_lastRelay200;
};

Bool NetPacket::rva0058D211(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->getCommand();
	if (m_lastType1FF != cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay200 != msg->getRelay()) {
		++len;
		++len;
	}
	if (m_lastTimestamp1F8 != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastFrame1F4 != cmdMsg->m_executionFrame) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayer1FE;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastID1FC;
	UnsignedInt cmdID = cmdMsg->m_id;
	if (((lastID + 1) != cmdID) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	if ((len + m_packetLen + 5) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::rva0058D310(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->getCommand();
	if (m_lastType1FF != cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay200 != msg->getRelay()) {
		++len;
		++len;
	}
	if (m_lastTimestamp1F8 != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayer1FE;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastID1FC;
	UnsignedInt cmdID = cmdMsg->m_id;
	if (((lastID + 1) != cmdID) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	if ((len + m_packetLen + 7) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::rva0058D58A(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->getCommand();
	if (m_lastType1FF != cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay200 != msg->getRelay()) {
		++len;
		++len;
	}
	if (m_lastTimestamp1F8 != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayer1FE;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastID1FC;
	UnsignedInt cmdID = cmdMsg->m_id;
	if (((lastID + 1) != cmdID) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	if ((len + m_packetLen + 9) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::rva0058D296(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->getCommand();
	if (m_lastType1FF != cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay200 != msg->getRelay()) {
		++len;
		++len;
	}
	if (m_lastTimestamp1F8 != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayer1FE;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastID1FC;
	UnsignedInt cmdID = cmdMsg->m_id;
	if (((lastID + 1) != cmdID) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	Int base = m_packetLen + cmdMsg->m_dataLen28;
	if ((len + base + 0xB) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::rva0058D601(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->getCommand();
	if (m_lastType1FF != cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay200 != msg->getRelay()) {
		++len;
		++len;
	}
	if (m_lastTimestamp1F8 != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastFrame1F4 != cmdMsg->m_executionFrame) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayer1FE;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastID1FC;
	UnsignedInt cmdID = cmdMsg->m_id;
	if (((lastID + 1) != cmdID) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	if ((len + m_packetLen + 2) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}
