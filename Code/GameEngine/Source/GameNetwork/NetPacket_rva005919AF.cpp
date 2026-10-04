// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva005919AF@NetPacket@@QAEEPAVNetCommandRef@@@Z @0x005919AF (182B).
// NetPacket room check with a wide-string term: charges type 2, timestamp 5,
// frame 5, relay 2, player 2 and command ID 3 when they differ from the
// packet's last values, a fixed 2, the UnicodeString length*2 from the getter
// at 0x004D6119 and a fixed 4, against MAX 0x1DC. Target facts: NetPacket
// tail +0x1E0/+0x1F4/+0x1F8/+0x1FC/+0x1FE/+0x1FF/+0x200 and NetCommandMsg
// +0x04/+0x08/+0x0C/+0x10/+0x14; caller 0x00593404.
// Donor lead: the shape is Zero Hour's isRoomForChatMessage (NetPacket.cpp),
// whose trailing 4 is the player mask, plus BFME's timestamp field; the name
// is not adopted without caller evidence. Retail selects the type charge
// with cmovne, which MSVC 7.1 emits only under /arch:SSE.
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
	UnsignedByte rva005919AF(NetCommandRef *msg);
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

UnsignedByte NetPacket::rva005919AF(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->getCommand();
	if (m_lastCommandType != cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastFrame != cmdMsg->m_executionFrame) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->getRelay()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->m_playerID) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != cmdMsg->m_id) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	UnsignedByte strLen = ((Rva004D6119 *)cmdMsg)->rva004D6119().getLength();
	len += strLen * sizeof(UnsignedShort);
	len += sizeof(Int);
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}
