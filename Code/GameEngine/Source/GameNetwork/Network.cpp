// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// Network.cpp -- Network members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function (vtable
// pairing) and the member m_pConMgr at +0x0C (assert at Network.cpp:69);
// retail supplies the bytes. The address pair lands at ConnectionManager
// +0x12050/+0x12054 (Zero Hour's m_localAddr and m_localPort).

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;

#include "ascii_string.h"
#include "unicode_string.h"

struct NetLocalAddress
{
	UnsignedInt m_addr;
	UnsignedInt m_port;
};

class ConnectionManager
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	void sendDisconnectChat(UnicodeString text);
	void sendFile(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID);
	void rva004D0E8B(void);

	void SetLocalAddr(const NetLocalAddress &addr)
	{
		m_localAddr = addr.m_addr;
		m_localPort = addr.m_port;
	}

private:
	unsigned char m_pad04[0x12050 - 4];
	UnsignedInt m_localAddr;		// +0x12050
	UnsignedInt m_localPort;		// +0x12054
};

class GameLogic
{
public:
	void rva0023D17D(void);
};

extern GameLogic *TheGameLogic;

class GameMessage
{
public:
	void appendIntegerArgument(int value);
};

class MessageStream
{
public:
#define MESSAGE_STREAM_SLOT(n) virtual void slot##n(void) = 0
	MESSAGE_STREAM_SLOT(00);
	MESSAGE_STREAM_SLOT(01);
	MESSAGE_STREAM_SLOT(02);
	MESSAGE_STREAM_SLOT(03);
	MESSAGE_STREAM_SLOT(04);
	MESSAGE_STREAM_SLOT(05);
	MESSAGE_STREAM_SLOT(06);
	MESSAGE_STREAM_SLOT(07);
	MESSAGE_STREAM_SLOT(08);
	MESSAGE_STREAM_SLOT(09);
	MESSAGE_STREAM_SLOT(10);
	MESSAGE_STREAM_SLOT(11);
	MESSAGE_STREAM_SLOT(12);
	MESSAGE_STREAM_SLOT(13);
	MESSAGE_STREAM_SLOT(14);
	MESSAGE_STREAM_SLOT(15);
	MESSAGE_STREAM_SLOT(16);
	MESSAGE_STREAM_SLOT(17);
	virtual GameMessage *appendMessage(UnsignedInt type) = 0;
#undef MESSAGE_STREAM_SLOT
};

extern MessageStream *MessageStreamSubsystem;

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *frequency);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *counter);

// Retail keeps the vtable at +0 and m_pConMgr at +0x0C although the class
// holds 64-bit QPC fields; 4-byte packing reproduces that layout.
#pragma pack(push, 4)
class Network
{
public:
	virtual void SetLocalAddr(const NetLocalAddress &addr);
	virtual void sendDisconnectChat(UnicodeString text);
	virtual void sendFile(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID);
	void quitGame(void);
	void startNewSession(void);

private:
	unsigned char m_pad04[8];
	ConnectionManager *m_pConMgr;		// +0x0C
	int m_state;						// +0x10
	char m_unknown14[4];
	__int64 m_performanceFrequency;		// +0x18
	__int64 m_lastPerformanceCounter;	// +0x20
	__int64 m_accumulator;				// +0x28
	bool m_stallTimerRunning;			// +0x30
	char m_unknown31[3];
	unsigned int m_stallCount;			// +0x34
	bool m_flag38;						// +0x38
	int m_lastValue;					// +0x3C
};
#pragma pack(pop)

// Target vtable view for Network slot 39 (byte offset 0x9C). The method name
// and all preceding slots remain unresolved; this view emits only the target
// virtual call shape used at 0x0025E270.
class NetworkSlot39View
{
public:
#define NETWORK_SLOT(n) virtual void slot##n(void) = 0
	NETWORK_SLOT(00);
	NETWORK_SLOT(01);
	NETWORK_SLOT(02);
	NETWORK_SLOT(03);
	NETWORK_SLOT(04);
	NETWORK_SLOT(05);
	NETWORK_SLOT(06);
	NETWORK_SLOT(07);
	NETWORK_SLOT(08);
	NETWORK_SLOT(09);
	NETWORK_SLOT(10);
	NETWORK_SLOT(11);
	NETWORK_SLOT(12);
	NETWORK_SLOT(13);
	NETWORK_SLOT(14);
	NETWORK_SLOT(15);
	NETWORK_SLOT(16);
	NETWORK_SLOT(17);
	NETWORK_SLOT(18);
	NETWORK_SLOT(19);
	NETWORK_SLOT(20);
	NETWORK_SLOT(21);
	NETWORK_SLOT(22);
	NETWORK_SLOT(23);
	NETWORK_SLOT(24);
	NETWORK_SLOT(25);
	NETWORK_SLOT(26);
	NETWORK_SLOT(27);
	NETWORK_SLOT(28);
	NETWORK_SLOT(29);
	NETWORK_SLOT(30);
	NETWORK_SLOT(31);
	NETWORK_SLOT(32);
	NETWORK_SLOT(33);
	NETWORK_SLOT(34);
	NETWORK_SLOT(35);
	NETWORK_SLOT(36);
	NETWORK_SLOT(37);
	NETWORK_SLOT(38);
	virtual void slot39(int value) = 0;
#undef NETWORK_SLOT
};

// Network::SetLocalAddr, retail 0x0025DBDC.
void Network::SetLocalAddr(const NetLocalAddress &addr)
{
	if (m_pConMgr)
		m_pConMgr->SetLocalAddr(addr);
}

// Network::startNewSession, retail 0x0025DFA1 (71B). WB vtable pairing names
// it (Network.cpp assert line 269); WB resets the QPC frequency/counter, the
// accumulator and stall fields, calls TheGameLogic (retail 0x0023D17D), sets
// -1 and pokes the connection manager's virtual slot 2, as retail does.
// Retail's field offsets past +0x2C sit 8 bytes below WB's debug layout.
void Network::startNewSession(void)
{
	QueryPerformanceFrequency(&m_performanceFrequency);
	QueryPerformanceCounter(&m_lastPerformanceCounter);
	m_accumulator = 0;
	m_stallTimerRunning = false;
	m_stallCount = 0;
	m_flag38 = false;
	TheGameLogic->rva0023D17D();
	m_lastValue = -1;
	if (m_pConMgr != 0)
		m_pConMgr->slot02();
}

// Target evidence at 0x0025E2E3: the receiver's connection-manager pointer is
// at +0x0C; the body copies a UnicodeString by value, forwards it, releases the
// temporary, and returns with one stack argument. The Network name and
// forwarding operation follow Open-BFME-1's Network::sendDisconnectChat; the
// donor supplies identity, while the target body supplies the layout and ABI.
void Network::sendDisconnectChat(UnicodeString text)
{
	m_pConMgr->sendDisconnectChat(text);
}

// Target evidence at 0x0025E327: an AsciiString copy plus byte and word
// arguments is forwarded through the connection-manager pointer at +0x0C.
// Open-BFME-1's Network::sendFile supplies the operation name and semantics;
// the BFME2 target bytes establish this body's signature and receiver layout.
void Network::sendFile(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID)
{
	m_pConMgr->sendFile(path, playerMask, commandID);
}

// Target evidence at 0x0025E233: if Network+0x0C is set it calls the
// address-derived ConnectionManager helper at 0x004D0E8B; it then appends
// message type 0x1D, conditionally adds integer argument 2, invokes Network
// vtable slot 39 with zero, and stores state 3 at +0x10. The BFME1
// Network_update.cpp donor carries the disconnect-transition semantics
// (manager disconnect plus message 0x1D and state 3); the target method name
// and the condition's absolute 0x114 read remain unresolved.
void Network::quitGame(void)
{
	if (m_pConMgr)
		m_pConMgr->rva004D0E8B();

	GameMessage *message = MessageStreamSubsystem->appendMessage(0x1D);
	if (TheGameLogic != 0 || *(const int *)0x114 != 3)
		message->appendIntegerArgument(2);

	((NetworkSlot39View *)this)->slot39(0);
	m_state = 3;
}
