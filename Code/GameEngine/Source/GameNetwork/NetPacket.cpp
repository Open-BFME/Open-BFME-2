// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// NetPacket.cpp: the NetPacket bodies retail links from this TU (tu_map approved),
// folded from 24 one-function split units that shared these exact flags.
// One NetPacket view replaces the per-unit ones; every field offset below is the
// one each folded body was byte-verified against:
//   +0x004 packet[0x1DC], +0x1E0 len, +0x1E4/+0x1E8 dest, +0x1EC count,
//   +0x1F0 lastCmd, +0x1F4 frame, +0x1F8 timestamp, +0x1FC id,
//   +0x1FE/+0x1FF/+0x200 player/type/relay.
// Field names for +0x1F4/+0x1F8 are inferred from the BFME1 donor's message
// layout and the sibling frame handler, not from target symbols.
// The room checks read NetCommandRef's m_msg/m_relay directly: the inline
// getters inline to the same bytes, but emitting them here adds COMDAT copies
// that lose to ConnectionManager's and would stop this unit linking.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
enum { MAX_PACKET_SIZE = 0x1DC };

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
void *__cdecl operator new(unsigned int size);
void *__cdecl operator new[](unsigned int size);

class NetCommandMsg
{
public:
	NetCommandMsg();
	UnsignedInt getTimestamp() { return m_timestamp; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
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

// The 0x2C data-carrying message: the room check at 0x0058D296 charges its
// +0x28 payload length, rva0058EDEF serializes +0x1C/+0x20/+0x28 and the +0x24
// buffer, and the static reader rva0058E20D rebuilds it in the same order
// through the rowed ctor 0x004D58DE and rva004D5925(data, len). One class
// across the three is a structural inference from that shared layout.
class Rva004D58DE : public NetCommandMsg
{
public:
	Rva004D58DE();
	void rva004D5925(unsigned char *data, unsigned int len);
	UnsignedInt get1c() { return m_1c; }
	UnsignedShort get20() { return m_20; }
	unsigned char *getData() { return m_24; }
	UnsignedInt getDataLength() { return m_28; }
	UnsignedInt m_1c;
	UnsignedShort m_20;
	unsigned char *m_24;
	UnsignedInt m_28;
};

// The wrapper getters are out of line under their ledger names. Retail folds
// the same-offset getters of the other message classes onto these (and onto
// NetProgressCommandMsg::getPercentage, Rva004D5767WordField::get), so the
// add* bodies below call them under these names: getData (+0x1C dword),
// getDataLength (+0x20) and getDataOffset (+0x24).
class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getWrappedCommandID();
	UnsignedInt getChunkNumber();
	UnsignedInt getNumChunks();
	UnsignedInt getTotalDataLength();
	UnsignedInt getDataLength();
	UnsignedInt getDataOffset();
	UnsignedByte *getData();
};

// +0x1C byte getter.
class NetProgressCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getPercentage();
};

// +0x1C word getter.
class Rva004D5767WordField
{
public:
	UnsignedShort get() const;
};

// Frame message addFrameCommand serializes: three dwords after the base.
class NetFrameCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt get1c() { return m_1c; }
	UnsignedInt get20() { return m_20; }
	UnsignedInt get24() { return m_24; }
	UnsignedInt m_1c;
	UnsignedInt m_20;
	UnsignedInt m_24;
};

class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	~NetCommandRef();
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

struct TransportMessageHeader
{
	UnsignedInt crc;
};

struct TransportMessage
{
	TransportMessageHeader header;
	UnsignedByte data[0x400];
	Int length;
	UnsignedInt addr;
	UnsignedShort port;
};

class NetPacket
{
public:
	virtual ~NetPacket();
	NetPacket();
	NetPacket(TransportMessage *msg);
	void init();
	void reset();
	Bool rva0058D18C(NetCommandRef *msg);
	Bool rva0058D211(NetCommandRef *msg);
	Bool rva0058D296(NetCommandRef *msg);
	Bool rva0058D310(NetCommandRef *msg);
	Bool rva0058D58A(NetCommandRef *msg);
	Bool rva0058D601(NetCommandRef *msg);
	Int rva0058E57B();

	static NetCommandMsg *rva0058DA7E(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DB4D(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DC1C(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DCEB(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DD89(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DDF2(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DE5B(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DEC5(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DEF7(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DFB8(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E047(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E0B0(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E20D(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E2D7(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E367(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E3F4(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E481(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E511(UnsignedByte *data, Int &readOffset);

protected:
	Bool isRoomForWrapperMessage(NetCommandRef *msg);
	Bool rva0058D461(NetCommandRef *msg);
	Bool rva0058D4BA(NetCommandRef *msg);
	UnsignedByte rva0058D513(NetCommandRef *msg);
	Bool isRoomForFrameMessage(NetCommandRef *msg);
	UnsignedByte rva0058D70B(NetCommandRef *msg);
	void rva0058D826(Int a, Int b, Int c, Int d, Int e);
	Bool addInformPlayerLeaveFrameCommand(NetCommandRef *msg);
	Bool rva0058E8EA(NetCommandRef *msg);
	Bool addDisconnectFrameCommand(NetCommandRef *msg);
	Bool rva0058EDEF(NetCommandRef *msg);
	Bool addFileProgressCommand(NetCommandRef *msg);
	Bool addWrapperCommand(NetCommandRef *msg);
	Bool rva0058F5E3(NetCommandRef *msg);
	Bool addProgressMessage(NetCommandRef *msg);
	Bool addDisconnectVoteCommand(NetCommandRef *msg);
	Bool addDisconnectPlayerCommand(NetCommandRef *msg);
	Bool rva0058FE15(NetCommandRef *msg);
	Bool addDestroyPlayerCommand(NetCommandRef *msg);
	Bool addRouterFallbackCommand(NetCommandRef *msg);
	Bool addPlayerLeaveCommand(NetCommandRef *msg);
	Bool addFrameCommand(NetCommandRef *msg);

public:
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

// Message classes the static readers construct, sized from their rowed ctors.
class Rva004D57AE : public NetCommandMsg
{
public:
	Rva004D57AE();
	void setPlayerIndex(UnsignedInt v);
private:
	UnsignedInt m_playerIndex; // +0x1C: NetCommandMsg is 0x1C bytes
};

class NetAckBothCommandMsg
{
public:
	NetAckBothCommandMsg();
private:
	char m_pad[0x1C];
public:
	unsigned short m_1c;
	unsigned char m_1e;
	char m_pad1f;
	unsigned int m_20;
	unsigned int m_24;
};

class NetAckStage1CommandMsg
{
public:
	NetAckStage1CommandMsg();
private:
	char m_pad[0x1C];
public:
	unsigned short m_1c;
	unsigned char m_1e;
	char m_pad1f;
	unsigned int m_20;
	unsigned int m_24;
};

class NetAckStage2CommandMsg
{
public:
	NetAckStage2CommandMsg();
private:
	char m_pad[0x1C];
public:
	unsigned short m_1c;
	unsigned char m_1e;
	char m_pad1f;
	unsigned int m_20;
	unsigned int m_24;
};

class Rva004CEEC3
{
public:
	Rva004CEEC3();
private:
	char m_pad[0x1C];
public:
	unsigned int m_1c;
	unsigned int m_20;
	unsigned int m_24;
};

class Rva004CEEE8
{
public:
	Rva004CEEE8();
private:
	char m_pad[0x3C];
};

class NetKeepAliveCommandMsg
{
public:
	NetKeepAliveCommandMsg();
private:
	char m_pad[0x1C];
};

class NetDisconnectKeepAliveCommandMsg
{
public:
	NetDisconnectKeepAliveCommandMsg();
private:
	char m_pad[0x1C];
};

class Rva004D580E
{
public:
	Rva004D580E();
private:
	char m_pad[0x24];
};

class Rva004D582B
{
public:
	Rva004D582B();
private:
	char m_pad[0x20];
};

class Rva004D5795
{
public:
	Rva004D5795();
private:
	char m_pad[0x20];
};

class Rva004D598E
{
public:
	Rva004D598E();
private:
	char m_pad[0x24];
};

class Rva004D59D1
{
public:
	Rva004D59D1();
private:
	char m_pad[0x24];
};

class Rva004D5A10
{
public:
	Rva004D5A10();
private:
	char m_pad[0x24];
};

class Rva004D5A30
{
public:
	Rva004D5A30();
private:
	char m_pad[0x24];
};

class Rva004D59B8
{
public:
	Rva004D59B8();
private:
	char m_pad[0x20];
};

// Setters the readers call through casts of the constructed message.
class Rva004D59ACWordSlot
{
public:
	void set(unsigned short value);
};

class Rva004D576CByteSlot
{
public:
	void set(unsigned char value);
};

class BFMENetRouterFallbackCommandMsg : public NetCommandMsg
{
public:
	void setPlayerOrder(const int *players);
	Int m_playerOrder[8]; // +0x1C, per the BFME1 donor
};

class BFMENetInformPlayerLeaveFrameCommandMsg
{
public:
	void setLeavingPlayerID(Int playerID);
	void setLeaveFrame(UnsignedInt frame);
};

enum DozerTask
{
	DOZER_TASK_ZERO = 0
};

class Script
{
public:
	void setActive(bool active);
};

class DozerAIUpdate
{
public:
	virtual void setCurrentTask(DozerTask task);
};

// ---------------------------------------------------------------------------
// ??1NetPacket@@UAE@XZ 0x0058D0E2, ?init@NetPacket@@QAEXXZ 0x0058D10A (86B),
// ?reset@NetPacket@@QAEXXZ 0x0058D160, ??0NetPacket 0x0058E5B4/0x0058E5EC.
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameNetwork/NetPacket_init.cpp
// (NetPacket::init flat stores + NetPacketAddress stack-temp dest assignment).
// Target evidence: flat 86B store run with EBP frame; callers 0x0058D160 reset
// tail-jmps here, ctors 0x0058E5B4/0x0058E5EC call here after vtable 0x00870A28.
NetPacket::~NetPacket()
{
	if (m_lastCommand != 0) {
		delete m_lastCommand;
		m_lastCommand = 0;
	}
}

void NetPacket::init()
{
	NetPacketAddress dest;
	m_dest = dest;
	m_numCommands = 0;
	m_packetLen = 0;
	m_packet[0] = 0;
	m_lastPlayerID = 0;
	m_lastFrame = 0;
	m_lastTimestamp = 0;
	m_lastCommandID = 0;
	m_lastCommandType = 0;
	m_lastRelay = 0;
	m_lastCommand = 0;
}

void NetPacket::reset()
{
	if (m_lastCommand != 0) {
		delete m_lastCommand;
		m_lastCommand = 0;
	}
	init();
}

// ?rva0058D18C@NetPacket@@QAE_NPAVNetCommandRef@@@Z, retail 0x0058D18C, 133 bytes:
// rva0058D211 with a fixed 9 instead of 5, the room check of the two bodies
// that serialize two dwords (addInformPlayerLeaveFrameCommand, rva0058E8EA).
Bool NetPacket::rva0058D18C(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != (UnsignedInt)cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastFrame != cmdMsg->m_executionFrame) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayerID;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastCommandID;
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

// ?rva0058D211@NetPacket@@QAE_NPAVNetCommandRef@@@Z, retail 0x0058D211, 133 bytes,
// and its siblings 0x0058D296/0x0058D310/0x0058D58A/0x0058D601.
// NetPacket room check sibling of isRoomForWrapperMessage 0x0058D387: charges
// type/relay/timestamp/frame/player/ID deltas (2/2/5/5/2/3) plus fixed 5 over
// base +0x1E0 and returns room<=0x1DC. Evidence: identical NetPacket tail
// layout +0x1F4/+0x1F8/+0x1FC/+0x1FE/+0x1FF/+0x200 and MAX 0x1DC as the
// sibling; callers 0x0058EB9A 0x0058FFBD. Honest address method of NetPacket.
Bool NetPacket::rva0058D211(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != (UnsignedInt)cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastFrame != cmdMsg->m_executionFrame) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayerID;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastCommandID;
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

Bool NetPacket::rva0058D296(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != (UnsignedInt)cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayerID;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastCommandID;
	UnsignedInt cmdID = cmdMsg->m_id;
	if (((lastID + 1) != cmdID) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	Int base = m_packetLen + ((Rva004D58DE *)cmdMsg)->m_28;
	if ((len + base + 0xB) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::rva0058D310(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != (UnsignedInt)cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayerID;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastCommandID;
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

// ?isRoomForWrapperMessage@NetPacket 0x0058D387 (129B).
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameNetwork/NetPacketCommandBodies.cpp.
// Target boundary 0x58D387 is the wrapper-capacity helper: it charges packet
// type, relay, timestamp, player and command-ID data then calls the pinned
// NetWrapperCommandMsg::getDataLength target at 0x0030D377. The +0x1F8 packet
// field is compared with command +0x04 in target bytes; its timestamp meaning
// is inferred from the donor's message layout and the sibling frame handler.
Bool NetPacket::isRoomForWrapperMessage(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)(msg->m_msg);
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

// ?rva0058D461@NetPacket@@IAE_NPAVNetCommandRef@@@Z @0x0058D461 (89B).
// NetPacket capacity check sibling of isRoomForWrapperMessage 0x0058D387:
// charges type 2 relay 1+1 timestamp 5 playerID 1+1 plus fixed 1 against
// MAX 0x1DC. No command-ID or data-length steps. Unblocks 0x0058F5E3
// and 0x0058FE15. Same layout and flags as wrapper precedent.
Bool NetPacket::rva0058D461(NetCommandRef *msg)
{
	Int len = 0;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->m_msg);
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
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		++len;
	}
	if ((len + m_packetLen + 1) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

// ?rva0058D4BA@NetPacket@@IAE_NPAVNetCommandRef@@@Z @0x0058D4BA (89B).
// Same charges as sibling rva0058D461 plus fixed 2. Unblocks 0x0058F7D8.
Bool NetPacket::rva0058D4BA(NetCommandRef *msg)
{
	Int len = 0;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->m_msg);
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
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		++len;
	}
	if ((len + m_packetLen + 2) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

// ?rva0058D513@NetPacket@@IAEEPAVNetCommandRef@@@Z 0x0058D513 (119B), the
// frame-message sibling without the execution-frame charge.
UnsignedByte NetPacket::rva0058D513(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->m_msg);
	if (m_lastCommandType != cmdMsg->m_commandType) {
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
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

Bool NetPacket::rva0058D58A(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != (UnsignedInt)cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayerID;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastCommandID;
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

Bool NetPacket::rva0058D601(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != (UnsignedInt)cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastFrame != cmdMsg->m_executionFrame) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayerID;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastCommandID;
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

// ?isRoomForFrameMessage@NetPacket 0x0058D686 (133B).
// BFME1 donor: Code/GameEngine/Source/GameNetwork/NetPacket.cpp.
// Same packet-capacity sequence and command fields as BFME1
// isRoomForFrameMessage (0x678180, 128 B), with the target packet's post-frame
// state shifted by four bytes.
Bool NetPacket::isRoomForFrameMessage(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->m_msg);
	if (m_lastCommandType != cmdMsg->m_commandType) {
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
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

// ?rva0058D70B@NetPacket@@IAEEPAVNetCommandRef@@@Z @0x0058D70B 60B.
// NetPacket room check beside isRoomForFrameMessage 0x0058D686: lastCommandType
// vs +0x14 and lastPlayerID vs +0x0C each add 2 then +12 vs 0x1DC.
// Evidence: unlock lane plus sibling TU layout plus caller 0x00591BAB.
UnsignedByte NetPacket::rva0058D70B(NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = msg->m_msg;
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

// ?rva0058D826@NetPacket@@IAEXHHHHH@Z @0x0058D826 265B.
// NetPacket packet append by kind copying raw stack args via memcpy.
// Evidence: unlock lane plus sibling TU layout plus caller 0x00590C71.
void NetPacket::rva0058D826(Int a, Int b, Int c, Int d, Int e)
{
	if (a == 0) {
		memcpy(m_packet + m_packetLen, &b, 4);
		m_packetLen += 4;
	} else if (a == 1) {
		memcpy(m_packet + m_packetLen, &b, 4);
		m_packetLen += 4;
	} else if (a == 2) {
		memcpy(m_packet + m_packetLen, &b, 1);
		m_packetLen += 1;
	} else if (a == 3) {
		memcpy(m_packet + m_packetLen, &b, 4);
		m_packetLen += 4;
	} else if (a == 4) {
		memcpy(m_packet + m_packetLen, &b, 4);
		m_packetLen += 4;
	} else if (a == 5) {
		memcpy(m_packet + m_packetLen, &b, 4);
		m_packetLen += 4;
	} else if (a == 6) {
		memcpy(m_packet + m_packetLen, &b, 12);
		m_packetLen += 12;
	} else if (a == 7) {
		memcpy(m_packet + m_packetLen, &b, 8);
		m_packetLen += 8;
	} else if (a == 8) {
		memcpy(m_packet + m_packetLen, &b, 16);
		m_packetLen += 16;
	} else if (a == 9) {
		memcpy(m_packet + m_packetLen, &b, 4);
		m_packetLen += 4;
	} else if (a == 10) {
		memcpy(m_packet + m_packetLen, &b, 2);
		m_packetLen += 2;
	}
}

// ?rva0058DA7E@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DA7E 207B.
// Static NetAckBoth factory reading word + byte + two dwords from data+offset.
// Evidence: sibling 0x0058DB4D 207B plus new-0x28 plus rowed
// ??0NetAckBothCommandMsg@@QAE@XZ 0x004D568F plus triple memcpy plus word
// setter 0x004D59AC byte setter 0x004D576C plus direct stores to +0x20 +0x24.
NetCommandMsg *NetPacket::rva0058DA7E(unsigned char *data, int &readOffset)
{
	NetAckBothCommandMsg *msg = new NetAckBothCommandMsg();
	unsigned int v0 = 0;
	memcpy(&v0, data + readOffset, 2);
	readOffset += 2;
	((Rva004D59ACWordSlot *)msg)->set((unsigned short)v0);
	unsigned char v1 = 0;
	memcpy(&v1, data + readOffset, 1);
	readOffset += 1;
	((Rva004D576CByteSlot *)msg)->set(v1);
	unsigned int v2 = (unsigned int)-1;
	memcpy(&v2, data + readOffset, 4);
	readOffset += 4;
	msg->m_20 = v2;
	unsigned int v3 = (unsigned int)-1;
	memcpy(&v3, data + readOffset, 4);
	readOffset += 4;
	msg->m_24 = v3;
	return (NetCommandMsg *)msg;
}

// ?rva0058DB4D@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DB4D 207B.
// Static NetAckStage1 factory; rowed ??0NetAckStage1CommandMsg@@QAE@XZ 0x004D56E6.
NetCommandMsg *NetPacket::rva0058DB4D(unsigned char *data, int &readOffset)
{
	NetAckStage1CommandMsg *msg = new NetAckStage1CommandMsg();
	unsigned int v0 = 0;
	memcpy(&v0, data + readOffset, 2);
	readOffset += 2;
	((Rva004D59ACWordSlot *)msg)->set((unsigned short)v0);
	unsigned char v1 = 0;
	memcpy(&v1, data + readOffset, 1);
	readOffset += 1;
	((Rva004D576CByteSlot *)msg)->set(v1);
	unsigned int v2 = (unsigned int)-1;
	memcpy(&v2, data + readOffset, 4);
	readOffset += 4;
	msg->m_20 = v2;
	unsigned int v3 = (unsigned int)-1;
	memcpy(&v3, data + readOffset, 4);
	readOffset += 4;
	msg->m_24 = v3;
	return (NetCommandMsg *)msg;
}

// ?rva0058DC1C@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DC1C 207B.
// Static NetAckStage2 factory; rowed ??0NetAckStage2CommandMsg@@QAE@XZ.
NetCommandMsg *NetPacket::rva0058DC1C(unsigned char *data, int &readOffset)
{
	NetAckStage2CommandMsg *msg = new NetAckStage2CommandMsg();
	unsigned int v0 = 0;
	memcpy(&v0, data + readOffset, 2);
	readOffset += 2;
	((Rva004D59ACWordSlot *)msg)->set((unsigned short)v0);
	unsigned char v1 = 0;
	memcpy(&v1, data + readOffset, 1);
	readOffset += 1;
	((Rva004D576CByteSlot *)msg)->set(v1);
	unsigned int v2 = (unsigned int)-1;
	memcpy(&v2, data + readOffset, 4);
	readOffset += 4;
	msg->m_20 = v2;
	unsigned int v3 = (unsigned int)-1;
	memcpy(&v3, data + readOffset, 4);
	readOffset += 4;
	msg->m_24 = v3;
	return (NetCommandMsg *)msg;
}

// ?rva0058DCEB@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DCEB 158B.
// Static NetCommandMsg factory reading three 4-byte fields from data+offset.
// Evidence: unlock lane plus sibling 0x0058E047 plus new-0x28 plus
// Rva004CEEC3 ctor plus triple memcpy-4 direct store to +0x1c +0x20 +0x24.
NetCommandMsg *NetPacket::rva0058DCEB(unsigned char *data, int &readOffset)
{
	Rva004CEEC3 *msg = new Rva004CEEC3();
	unsigned int v0 = 0;
	memcpy(&v0, data + readOffset, 4);
	readOffset += 4;
	msg->m_1c = v0;
	unsigned int v1 = 0;
	memcpy(&v1, data + readOffset, 4);
	readOffset += 4;
	msg->m_20 = v1;
	unsigned int v2 = 0;
	memcpy(&v2, data + readOffset, 4);
	readOffset += 4;
	msg->m_24 = v2;
	return (NetCommandMsg *)msg;
}

// ?rva0058DD89@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @ 0x0058DD89 (105B): static
// factory news 0x3C Rva004CEEE8 then reads 8 bytes into local order and calls
// setPlayerOrder. Evidence: sibling factories 0x0058DCEB and 0x0058E047 plus
// rowed Rva004CEEE8 0x004CEEE8 plus rowed setPlayerOrder 0x004D577B. Callers
// 0x00592756 and 0x00594089.
NetCommandMsg *NetPacket::rva0058DD89(unsigned char *data, int &readOffset)
{
	Rva004CEEE8 *msg = new Rva004CEEE8();
	int order[8];
	for (int i = 0; i < 8; ++i, ++readOffset)
		order[i] = data[readOffset];
	((BFMENetRouterFallbackCommandMsg *)msg)->setPlayerOrder(order);
	return (NetCommandMsg *)msg;
}

// ?rva0058DDF2@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z, retail 0x0058DDF2, 105 bytes:
// the same 1-byte-flag reader as rva0058E047 constructing the rowed Rva004D5795
// message (same 0x20 size) instead of Rva004D582B.
NetCommandMsg *NetPacket::rva0058DDF2(unsigned char *data, int &readOffset)
{
	Rva004D5795 *msg = new Rva004D5795();
	bool flag = false;
	memcpy(&flag, data + readOffset, 1);
	readOffset += 1;
	((Script *)msg)->setActive(flag);
	return (NetCommandMsg *)msg;
}

// ?rva0058DE5B@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z 0x0058DE5B (106B).
NetCommandMsg *NetPacket::rva0058DE5B(UnsignedByte *data, Int &readOffset)
{
	Rva004D57AE *msg = new Rva004D57AE;
	UnsignedInt v = 0;
	memcpy(&v, data + readOffset, sizeof(v));
	readOffset += sizeof(v);
	msg->setPlayerIndex(v);
	return msg;
}

// ?rva0058DEC5@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DEC5 50B.
// Static NetCommandMsg factory constructing KeepAlive with no fields read.
// Evidence: unlock lane plus sibling 0x0058E047 plus new-0x1c plus
// NetKeepAliveCommandMsg ctor plus uniform factory signature.
NetCommandMsg *NetPacket::rva0058DEC5(unsigned char *data, int &readOffset)
{
	(void)data;
	(void)readOffset;
	NetKeepAliveCommandMsg *msg = new NetKeepAliveCommandMsg();
	return (NetCommandMsg *)msg;
}

// ?rva0058DEF7@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DEF7 50B.
// Static NetCommandMsg factory constructing DisconnectKeepAlive with no fields read.
NetCommandMsg *NetPacket::rva0058DEF7(unsigned char *data, int &readOffset)
{
	(void)data;
	(void)readOffset;
	NetDisconnectKeepAliveCommandMsg *msg = new NetDisconnectKeepAliveCommandMsg();
	return (NetCommandMsg *)msg;
}

// ?rva0058DFB8@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DFB8 143B.
// Static NetCommandMsg factory reading 1-byte bool plus 4-byte enum from data+offset.
// Evidence: unlock lane plus sibling 0x0058E047 plus new-0x24 plus
// Rva004D580E ctor plus memcpy-1-4 plus dup_0006ede3 row TYPES wrong
// (object-symbol ?setActive@Script@@QAEX_N@Z) plus dup_00317b9b row TYPES wrong
// (object-symbol ?setCurrentTask@DozerAIUpdate@@UAEXW4DozerTask@@@Z); declared as used.
NetCommandMsg *NetPacket::rva0058DFB8(unsigned char *data, int &readOffset)
{
	Rva004D580E *msg = new Rva004D580E();
	bool flag = false;
	memcpy(&flag, data + readOffset, 1);
	readOffset += 1;
	((Script *)msg)->setActive(flag);
	DozerTask task = DOZER_TASK_ZERO;
	memcpy(&task, data + readOffset, 4);
	readOffset += 4;
	((DozerAIUpdate *)msg)->DozerAIUpdate::setCurrentTask(task);
	return (NetCommandMsg *)msg;
}

// ?rva0058E047@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E047 105B.
// Static NetCommandMsg factory reading 1-byte relay flag from data+offset.
// Evidence: unlock lane plus sibling 0x0058E511 plus new-0x20 plus
// Rva004D582B ctor plus memcpy-1 plus dup_0006EDE3 row TYPES wrong;
// retail calls thiscall bool setter at 0x0006EDE3 whose row is gen-alias
// YAXXZ but object-symbol is ?setActive@Script@@QAEX_N@Z; declared as used.
NetCommandMsg *NetPacket::rva0058E047(unsigned char *data, int &readOffset)
{
	Rva004D582B *msg = new Rva004D582B();
	bool flag = false;
	memcpy(&flag, data + readOffset, 1);
	readOffset += 1;
	((Script *)msg)->setActive(flag);
	return (NetCommandMsg *)msg;
}

// ?rva0058E0B0@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E0B0 50B.
// Static NetCommandMsg factory allocating base message only.
// Evidence: neighbours 0x0058E047 and 0x0058E367 same NetPacket static factory
// shape PAEAAH plus same flags; new-0x1C plus NetCommandMsg base ctor row;
// same two free-function callers as 0x0058E481 family; no payload reads.
NetCommandMsg *NetPacket::rva0058E0B0(unsigned char *data, int &readOffset)
{
	return new NetCommandMsg();
}

// ?rva0058E20D@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E20D 202B.
// Static NetPacket factory for Rva004D58DE (0x2C): new via rowed ctor 0x004D58DE,
// dword at +0x1C via 4B memcpy, word at +0x20 via 2B memcpy, dword len via 4B
// memcpy then new[] buffer plus memcpy plus rowed SetData 0x004D5925.
NetCommandMsg *NetPacket::rva0058E20D(unsigned char *data, int &readOffset)
{
	Rva004D58DE *msg = new Rva004D58DE();
	UnsignedInt v0 = 0;
	memcpy(&v0, data + readOffset, 4);
	readOffset += 4;
	msg->m_1c = v0;
	UnsignedInt v1 = 0;
	memcpy(&v1, data + readOffset, 2);
	readOffset += 2;
	msg->m_20 = (UnsignedShort)v1;
	UnsignedInt len = 0;
	memcpy(&len, data + readOffset, 4);
	readOffset += 4;
	unsigned char *buf = new unsigned char[len];
	memcpy(buf, data + readOffset, len);
	readOffset += len;
	msg->rva004D5925(buf, len);
	return (NetCommandMsg *)msg;
}

// ?rva0058E2D7@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z, retail 0x0058E2D7, 144 bytes.
// Static NetPacket factory reading word then dword: new Rva004D598E (0x24)
// via rowed ctor 0x004D598E, memcpy 2B into v0 then WordSlot set at +0x1C
// via rowed 0x004D59AC, memcpy 4B into v1 then setLeavingPlayerID at +0x20
// via rowed 0x00317B9B.
NetCommandMsg *NetPacket::rva0058E2D7(unsigned char *data, int &readOffset)
{
	Rva004D598E *msg = new Rva004D598E();
	unsigned int v0 = 0;
	memcpy(&v0, data + readOffset, 2);
	readOffset += 2;
	((Rva004D59ACWordSlot *)msg)->set((unsigned short)v0);
	Int v1 = 0;
	memcpy(&v1, data + readOffset, 4);
	readOffset += 4;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(v1);
	return (NetCommandMsg *)msg;
}

// ?rva0058E367@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E367 141B.
// Static NetCommandMsg factory reading leaving-player ID then leave frame.
// Evidence: BFME1 donor NetPacket_read.cpp readInformPlayerLeaveFrameMessage
// (same new plus setLeavingPlayerID plus setLeaveFrame order); neighbours
// 0x0058E047/0x0058E511 (same NetPacket static factory shape PAEAAH);
// Rva004D59D1 ctor row (type 8 plus vtable 0x860274); setLeaveFrame row.
// Retail defaults playerID to -1 where the donor uses 0 (or -1 proves it).
// The 10B setter at 0x00317B9B is rowed YAXXZ (TYPES wrong); declared as used.
NetCommandMsg *NetPacket::rva0058E367(unsigned char *data, int &readOffset)
{
	Rva004D59D1 *msg = new Rva004D59D1();
	Int playerID = -1;
	memcpy(&playerID, data + readOffset, 4);
	readOffset += 4;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(playerID);
	UnsignedInt leaveFrame = 0;
	memcpy(&leaveFrame, data + readOffset, 4);
	readOffset += 4;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeaveFrame(leaveFrame);
	return (NetCommandMsg *)msg;
}

// ?rva0058E3F4@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E3F4 141B.
// Static NetCommandMsg factory reading player index then leaving-player ID.
// Evidence: neighbours 0x0058E367 and 0x0058E481 same NetPacket static factory
// shape PAEAAH; new-0x24 plus Rva004D5A10 ctor row; memcpy plus Rva004D57AE
// setter plus-0x1C; second setter at 0x00317B9B writes plus-0x20; first dword
// defaults -1 like 0x0058E367.
NetCommandMsg *NetPacket::rva0058E3F4(unsigned char *data, int &readOffset)
{
	Rva004D5A10 *msg = new Rva004D5A10();
	UnsignedInt playerIndex = (UnsignedInt)-1;
	memcpy(&playerIndex, data + readOffset, 4);
	readOffset += 4;
	((Rva004D57AE *)msg)->setPlayerIndex(playerIndex);
	Int field20 = 0;
	memcpy(&field20, data + readOffset, 4);
	readOffset += 4;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(field20);
	return (NetCommandMsg *)msg;
}

// ?rva0058E481@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E481 144B.
// Static NetCommandMsg factory reading player index then second dword.
// Evidence: neighbours 0x0058E367 and 0x0058E511; new-0x24 plus Rva004D5A30
// ctor row type 9 vtable 0x860294; memcpy plus Rva004D57AE setter row at
// plus-0x1C; second setter at 0x00317B9B writes plus-0x20.
NetCommandMsg *NetPacket::rva0058E481(unsigned char *data, int &readOffset)
{
	Rva004D5A30 *msg = new Rva004D5A30();
	UnsignedInt playerIndex = 0;
	memcpy(&playerIndex, data + readOffset, 4);
	readOffset += 4;
	((Rva004D57AE *)msg)->setPlayerIndex(playerIndex);
	Int field20 = 0;
	memcpy(&field20, data + readOffset, 4);
	readOffset += 4;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(field20);
	return (NetCommandMsg *)msg;
}

// ?rva0058E511@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E511 106B.
// Static NetCommandMsg factory reading player index from data+offset.
// Evidence: new-0x20 plus Rva004D59B8 ctor plus memcpy plus Rva004D57AE setter.
NetCommandMsg *NetPacket::rva0058E511(unsigned char *data, int &readOffset)
{
	Rva004D59B8 *msg = new Rva004D59B8();
	UnsignedInt playerIndex = 0;
	memcpy(&playerIndex, data + readOffset, 4);
	readOffset += 4;
	((Rva004D57AE *)msg)->setPlayerIndex(playerIndex);
	return (NetCommandMsg *)msg;
}

// ?rva0058E57B@NetPacket@@QAEHXZ @0x0058E57B 57B.
// NetPacket thiscall reading m_packetLen at plus-0x1E0: idiv-8 plus remainder
// inc is ceil len-div-8; nested 8-step loops with break on len.
Int NetPacket::rva0058E57B()
{
	Int n = m_packetLen / 8;
	if (m_packetLen % 8 != 0) {
		++n;
	}
	for (Int i = 0; i < n; ++i) {
		for (Int j = 0; j < 8; ++j) {
			if (i * 8 + j >= m_packetLen) {
				break;
			}
		}
	}
	return n;
}

NetPacket::NetPacket()
{
	init();
}

NetPacket::NetPacket(TransportMessage *msg)
{
	init();
	m_dest.ip = msg->addr;
	m_dest.port = msg->port;
	m_packetLen = msg->length;
	memcpy(m_packet, msg->data, sizeof(m_packet));
	m_numCommands = -1;
}

// ?addInformPlayerLeaveFrameCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058E652, 664 bytes:
// addCommand's type-8 arm (dispatcher 0x005944D7, table 0x0059460D), BFME1's
// NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME. Same T/F/R/P/C/D blocks and two-dword
// payload as the BFME1 donor body, plus BFME's S block; payload +0x20 then +0x1C.
Bool NetPacket::addInformPlayerLeaveFrameCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D18C(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)msg->getCommand();
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedInt dataLength = cmdMsg->getDataLength();
		memcpy(m_packet + m_packetLen, &dataLength, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		UnsignedByte * data = cmdMsg->getData();
		memcpy(m_packet + m_packetLen, &data, sizeof(UnsignedByte *));
		m_packetLen += sizeof(UnsignedByte *);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}

// ?rva0058E8EA@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058E8EA, 664 bytes:
// addCommand's arm for types 7 and 9 (BFME1's REQUESTPLAYERLEAVE and
// REQUESTFRAMEDATA, whose identical bodies fold here): T/S/F/R/P/C/D, then the
// +0x1C and +0x20 dwords. Folded, so it keeps its address name.
Bool NetPacket::rva0058E8EA(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D18C(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)msg->getCommand();
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedByte * data = cmdMsg->getData();
		memcpy(m_packet + m_packetLen, &data, sizeof(UnsignedByte *));
		m_packetLen += sizeof(UnsignedByte *);
		UnsignedInt dataLength = cmdMsg->getDataLength();
		memcpy(m_packet + m_packetLen, &dataLength, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}

// ?addDisconnectFrameCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058EB82, 621 bytes:
// addCommand's type-28 arm. BFME2's enum inserts one type after FILE (the
// enum gap moves from 23 to 24 and router fallback from 22 to 23), so this is
// BFME1's DISCONNECTFRAME: ZH's T/F/R/P/C/D plus S, then one dword.
Bool NetPacket::addDisconnectFrameCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D211(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)msg->getCommand();
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedByte * data = cmdMsg->getData();
		memcpy(m_packet + m_packetLen, &data, sizeof(UnsignedByte *));
		m_packetLen += sizeof(UnsignedByte *);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}

