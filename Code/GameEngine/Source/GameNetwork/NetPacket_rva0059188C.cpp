// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0059188C@NetPacket@@QAEEPAVNetCommandRef@@@Z @0x0059188C (158B).
// NetPacket room check with string-length term: charges type 2 relay 2
// timestamp 5 player 2 ID 3 plus fixed 1, adds AsciiString length from the
// +0x1C getter (rowed as CDDrive::getPath 0x002D9BA6 via identical bytes)
// and fixed 4 against MAX 0x1DC. Evidence: NetPacket tail +0x1E0/+0x1F8/
// +0x1FC/+0x1FE/+0x1FF/+0x200 and NetCommandMsg +0x04/+0x0C/+0x10/+0x14
// as siblings; callers 0x00592F44; callees rowed.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
enum { MAX_PACKET_SIZE = 0x1DC };

#include "ascii_string.h"


class CDDrive
{
public:
	virtual AsciiString getPath();
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
	NetCommandMsg *getCommand();
	UnsignedByte getRelay() const;
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
	UnsignedByte rva0059188C(NetCommandRef *msg);
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

UnsignedByte NetPacket::rva0059188C(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
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
	Int strLen = ((CDDrive *)cmdMsg)->CDDrive::getPath().getLength();
	return m_packetLen + strLen + len + 4 <= MAX_PACKET_SIZE;
}
