// cl: /O1 /EHsc /MD /arch:SSE
// Network.cpp -- Network members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function (vtable
// pairing) and the member m_pConMgr at +0x0C (assert at Network.cpp:69);
// retail supplies the bytes. The address pair lands at ConnectionManager
// +0x12050/+0x12054 (Zero Hour's m_localAddr and m_localPort).

typedef unsigned int UnsignedInt;

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

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *frequency);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *counter);

// Retail keeps the vtable at +0 and m_pConMgr at +0x0C although the class
// holds 64-bit QPC fields; 4-byte packing reproduces that layout.
#pragma pack(push, 4)
class Network
{
public:
	virtual void SetLocalAddr(const NetLocalAddress &addr);
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
