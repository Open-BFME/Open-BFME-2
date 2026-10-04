// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0059192A@NetPacket@@QAEEPAVNetCommandRef@@@Z @0x0059192A (133B).
// NetPacket room check with a wide-string term: charges type 2, relay 2,
// timestamp 5 and player 2 when they differ from the packet's last values,
// a fixed 2, then the UnicodeString length*2 from the getter at 0x004D6119,
// against MAX 0x1DC. Target facts: NetPacket tail +0x1E0/+0x1F8/+0x1FE/
// +0x1FF/+0x200 and NetCommandMsg +0x04/+0x0C/+0x14 as in the rowed siblings
// NetPacket_rva0059188C and NetPacket_rva005919AF.
// Donor lead: the shape is Zero Hour's isRoomForDisconnectChatMessage
// (NetPacket.cpp) plus BFME's timestamp field; the name is not adopted
// without caller evidence. Retail selects the type charge with cmovne,
// which MSVC 7.1 emits only under /arch:SSE.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
enum { MAX_PACKET_SIZE = 0x1DC };

#include "unicode_string.h"

class Rva004D6119
{
public:
	UnicodeString rva004D6119() const;
};

class NetCommandMsg
{
public:
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	UnsignedShort m_pad12;
	UnsignedInt m_commandType;
	UnsignedInt m_referenceCount;
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
	UnsignedByte rva0059192A(NetCommandRef *msg);
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

UnsignedByte NetPacket::rva0059192A(NetCommandRef *msg)
{
	Int len = 0;
	NetCommandMsg *cmdMsg = msg->getCommand();
	if (m_lastCommandType != cmdMsg->m_commandType) {
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->getRelay()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->m_playerID) {
		++len;
		len += sizeof(UnsignedByte);
	}

	++len;
	len += sizeof(UnsignedByte);
	UnsignedByte textLen = ((Rva004D6119 *)cmdMsg)->rva004D6119().getLength();
	len += textLen * sizeof(UnsignedShort);
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}
