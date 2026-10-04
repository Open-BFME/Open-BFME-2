// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva00591A65@NetPacket@@QAEEPAVNetCommandRef@@@Z @0x00591A65 (182B).
// NetPacket room check with a wide-string term: charges type 2, timestamp 5,
// frame 5, relay 2, player 2 and command ID 3 when they differ from the
// packet's last values, a fixed 2, the UnicodeString length*2 from the +0x24
// getter (rowed Rva0023E928 0x0023E928) and a fixed 8, against MAX 0x1DC.
// Target facts: NetPacket tail +0x1E0/+0x1F4/+0x1F8/+0x1FC/+0x1FE/+0x1FF/
// +0x200 and NetCommandMsg +0x04/+0x08/+0x0C/+0x10/+0x14; caller 0x005936F4.
// Donor lead: same shape as Zero Hour's isRoomForChatMessage with eight
// trailing bytes instead of the four-byte player mask. Retail selects the
// type charge with cmovne, which MSVC 7.1 emits only under /arch:SSE.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
enum { MAX_PACKET_SIZE = 0x1DC };

#include "unicode_string.h"

class Rva0023E928
{
public:
	UnicodeString rva0023E928() const;
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
	UnsignedByte rva00591A65(NetCommandRef *msg);
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

UnsignedByte NetPacket::rva00591A65(NetCommandRef *msg)
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
		++len;
		++len;
	}
	if (m_lastPlayerID != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != cmdMsg->m_id) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	++len;
	++len;
	UnsignedByte slen = ((Rva0023E928 *)cmdMsg)->rva0023E928().getLength() & 0xFF;
	len += slen * sizeof(UnsignedShort);
	len += sizeof(Int) + sizeof(Int);
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}
