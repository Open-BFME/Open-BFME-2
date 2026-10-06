// ?rva0058FBCA@NetPacket@@IAE_NPAVNetCommandRef@@@Z
// partial score=0.9544 date=2026-10-05
// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /G7
// ?rva0058FBCA@NetPacket@@IAE_NPAVNetCommandRef@@@Z, RVA 0x0058FBCA, size 587.
// Evidence: packet T/R/S/P/C/D tags with getPercentage 0x004C54EC and getDataOffset
// 0x00091A56 on same msg as Rva0058CB27Write; isRoom helper rva0058D513 row;
// NetPacket layout from NetPacket_init sibling; relay/player/type offsets.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

void __cdecl ji_006291a8();

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
	char m_pad12[2];
	Int m_commandType;
	Int m_referenceCount;
};

class NetProgressCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getPercentage();
};

class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getDataOffset();
};

class NetCommandNode
{
public:
	void detach();
	NetCommandMsg *m_msg;
	NetCommandNode *m_next;
	NetCommandNode *m_prev;
};

class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

struct NetPacketAddress
{
	NetPacketAddress() { ip = 0; port = 0; }
	UnsignedInt ip;
	UnsignedShort port;
};

class NetPacket
{
public:
	virtual ~NetPacket();
protected:
	UnsignedByte rva0058D513(NetCommandRef *msg);
	Bool rva0058FBCA(NetCommandRef *msg);
	UnsignedByte m_packet[0x1DC];
	Int m_packetLen;
	NetPacketAddress m_dest;
	Int m_numCommands;
	NetCommandRef *m_lastCommand;
	UnsignedInt m_lastFrame;
	UnsignedInt m_lastTimestamp;
	UnsignedShort m_lastCommandID;
	UnsignedByte m_lastPlayerID;
	UnsignedByte m_lastCommandType;
	UnsignedByte m_lastRelay;
};

// ?rva0058FBCA@NetPacket@@IAE_NPAVNetCommandRef@@@Z present-unmatched
Bool NetPacket::rva0058FBCA(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D513(msg) == 0) {
		return false;
	}
	NetCommandMsg *cmdMsg = msg->getCommand();
	if (m_lastCommandType != cmdMsg->getNetCommandType()) {
		m_packet[m_packetLen] = 'T';
		++m_packetLen;
		++m_packetLen;
		m_packet[m_packetLen] = (UnsignedByte)cmdMsg->getNetCommandType();
		m_lastCommandType = (UnsignedByte)cmdMsg->getNetCommandType();
	}
	if (m_lastRelay != msg->getRelay()) {
		m_packet[m_packetLen] = 'R';
		++m_packetLen;
		UnsignedByte newRelay = msg->getRelay();
		((void (__cdecl *)(void *, const void *, int))ji_006291a8)(m_packet + m_packetLen, &newRelay, 1);
		++m_packetLen;
		m_lastRelay = newRelay;
	}
	if (cmdMsg->m_timestamp != m_lastTimestamp) {
		m_packet[m_packetLen] = 'S';
		++m_packetLen;
		UnsignedInt ts = cmdMsg->m_timestamp;
		((void (__cdecl *)(void *, const void *, int))ji_006291a8)(m_packet + m_packetLen, &ts, 4);
		m_packetLen += 4;
		m_lastTimestamp = ts;
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		m_packet[m_packetLen] = 'P';
		++m_packetLen;
		m_packet[m_packetLen] = (UnsignedByte)cmdMsg->getPlayerID();
		++m_packetLen;
		m_lastPlayerID = (UnsignedByte)cmdMsg->getPlayerID();
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		m_packet[m_packetLen] = 'C';
		++m_packetLen;
		UnsignedShort id = cmdMsg->m_id;
		((void (__cdecl *)(void *, const void *, int))ji_006291a8)(m_packet + m_packetLen, &id, 2);
		m_packetLen += 2;
	}
	m_lastCommandID = cmdMsg->getID();
	m_packet[m_packetLen] = 'D';
	m_packetLen++;
	UnsignedByte pct = ((NetProgressCommandMsg *)cmdMsg)->getPercentage();
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(m_packet + m_packetLen, &pct, 1);
	++m_packetLen;
	UnsignedInt off = ((NetWrapperCommandMsg *)cmdMsg)->getDataOffset();
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(m_packet + m_packetLen, &off, 4);
	m_packetLen += 4;
	NetCommandRef *last = m_lastCommand;
	++m_numCommands;
	if (last != 0) {
		((NetCommandNode *)last)->detach();
		delete last;
		m_lastCommand = 0;
	}
	m_lastCommand = new NetCommandRef(msg->getCommand());
	m_lastCommand->setRelay(msg->getRelay());
	return true;
}
