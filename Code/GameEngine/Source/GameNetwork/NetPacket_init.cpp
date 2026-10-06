// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?init@NetPacket@@QAEXXZ, RVA 0x0058D10A, size 86.
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameNetwork/NetPacket_init.cpp
// (NetPacket::init flat stores + NetPacketAddress stack-temp dest assignment).
// Target evidence: flat 86B store run with EBP frame; callers 0x0058D160 reset
// tail-jmps here, ctors 0x0058E5B4/0x0058E5EC call here after vtable 0x00870A28;
// layout matches sibling NetPacket_isRoomForWrapperMessage/FrameMessage TUs
// (+0x1E0 len, +0x1E4/+0x1E8 dest, +0x1EC count, +0x1F0 lastCmd, +0x1F4 frame,
// +0x1F8 timestamp, +0x1FC id, +0x1FE/+0x1FF/+0x200 player/type/relay).
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

class NetCommandRef
{
public:
	~NetCommandRef();
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

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);

class NetPacket
{
public:
	virtual ~NetPacket();
	NetPacket();
	NetPacket(TransportMessage *msg);
	void init();
	void reset();

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

NetPacket::~NetPacket()
{
	if (m_lastCommand != 0) {
		delete m_lastCommand;
		m_lastCommand = 0;
	}
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
