// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /Oy- /Op
//
// ??0FirewallHelperClass@@QAE@XZ, retail 0x00594cdd, 154 bytes. Banked partial (score 0.92) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Evidence: vtable 0x00870A2C at [this]; layout matches ZH FirewallHelper.h (spareSockets 8x8 at +0x14, manglers 4 at +0x54, sparePorts/mangledPorts at +0x68/+0x78, packetID +0x88, messages 8x30 at +0x8A length at +0x14, state/timeouts at +0x17C..+0x18C); timeGetTime IAT + div/div global g_00DD31F4; caller 0x00595143.
class UDP;

#pragma pack(push, 1)
struct ManglerData
{
	unsigned int m_crc;
	unsigned short m_magic;
	unsigned short m_packetID;
	unsigned short m_mangledPortNumber;
	unsigned short m_originalPortNumber;
	unsigned char m_mangledAddress[4];
	unsigned char m_netCommandType;
	unsigned char m_blitzMe;
	unsigned short m_padding;
};

struct ManglerMessage
{
	ManglerData m_data;
	int m_length;
	unsigned int m_ip;
	unsigned short m_port;
};
#pragma pack(pop)

struct SpareSocketStruct
{
	UDP *udp;
	unsigned short port;
};

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern unsigned int g_00DD31F4;

class FirewallHelperClass
{
public:
	FirewallHelperClass();
	virtual ~FirewallHelperClass();

private:
	int m_behavior;
	int m_lastBehavior;
	int m_sourcePortAllocationDelta;
	int m_lastSourcePortAllocationDelta;
	SpareSocketStruct m_spareSockets[8];
	unsigned int m_manglers[4];
	int m_numManglers;
	unsigned short m_sparePorts[8];
	unsigned short m_mangledPorts[8];
	unsigned short m_packetID;
	ManglerMessage m_messages[8];
	int m_currentState;
	int m_timeoutStart;
	int m_timeoutLength;
	int m_numResponses;
	int m_currentTry;
};

FirewallHelperClass::FirewallHelperClass()
{
	m_currentTry = 0;
	m_numManglers = 0;
	m_numResponses = 0;
	m_packetID = 0;
	m_timeoutLength = 0;
	m_timeoutStart = 0;
	m_behavior = 0;
	m_lastBehavior = 0;
	m_sourcePortAllocationDelta = 0;
	m_lastSourcePortAllocationDelta = 0;
	for (int i = 0; i < 8; i++)
	{
		m_spareSockets[i].port = 0;
		m_mangledPorts[i] = 0;
		m_spareSockets[i].udp = 0;
		m_messages[i].m_length = 0;
		m_sparePorts[i] = 0;
	}
	for (int i = 0; 4 > i; ++i)
		m_manglers[i] = 0;
	m_currentState = 0;
	g_00DD31F4 = timeGetTime() / 1000 % 1000 + 0x1000;
}
