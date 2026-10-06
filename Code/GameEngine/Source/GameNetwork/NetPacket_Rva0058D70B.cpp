// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058D70B@NetPacket@@IAEEPAVNetCommandRef@@@Z @0x0058D70B 60B.
// NetPacket room check beside isRoomForFrameMessage 0x0058D686: lastCommandType
// vs +0x14 and lastPlayerID vs +0x0C each add 2 then +12 vs 0x1DC.
// Evidence: unlock lane plus sibling TU layout plus caller 0x00591BAB.
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
	UnsignedInt m_unknown1F8;
	UnsignedShort m_lastCommandID;
	UnsignedByte m_lastPlayerID;
	UnsignedByte m_lastCommandType;
	UnsignedByte m_lastRelay;
	UnsignedByte rva0058D70B(NetCommandRef *msg);
};

UnsignedByte NetPacket::rva0058D70B(NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = msg->getCommand();
	Int len = 0;
	if (m_lastCommandType != cmdMsg->m_commandType) {
		len = 2;
	}
	if (m_lastPlayerID != cmdMsg->m_playerID) {
		++len;
		++len;
	}
	Int total = m_packetLen + len + 12;
	return total <= MAX_PACKET_SIZE;
}
