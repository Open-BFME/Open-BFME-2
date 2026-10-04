// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// The native network allocation path constructs a 0x40-byte object at
// 0x0065E4A8, then calls this body before invoking the virtual init slot. The
// base constructor is a separately pinned retail body at 0x005B4E63.

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *frequency);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *counter);

extern class GameLogic *TheGameLogic;

extern const void *const g_00BF6040[];

class GameLogic
{
public:
	void rva0023D17D(void);
};

class ManagerView
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
};

class BFME2NativeNetwork
{
public:
	void *construct(void);
	void rva0025DFA1(void);
	void baseConstruct(void);

private:
	void *m_vtable;
	char m_baseFields[8];
	void *m_connectionManager;
	int m_state;
	char m_unknown14[4];
	__int64 m_performanceFrequency;
	__int64 m_lastPerformanceCounter;
	__int64 m_accumulator;
	bool m_stallTimerRunning;
	char m_unknown31[3];
	unsigned int m_stallCount;
	bool m_flag38;
	int m_lastValue;
};

void *BFME2NativeNetwork::construct(void)
{
	baseConstruct();
	m_lastValue = -1;
	m_connectionManager = 0;
	m_state = 0;
	m_accumulator = 0;
	m_stallTimerRunning = false;
	m_stallCount = 0;
	m_flag38 = false;
	m_vtable = (void *)g_00BF6040;
	QueryPerformanceFrequency(&m_performanceFrequency);
	QueryPerformanceCounter(&m_lastPerformanceCounter);
	return this;
}

// ?rva0025DFA1@BFME2NativeNetwork@@QAEXXZ @0x0025DFA1 71B: QPC freq/counter at +0x18/+0x20, zero +0x28-0x38, TheGameLogic->rva0023D17D, -1 at +0x3C, virtual slot +8 on +0x0C. Same 0x40 layout and // cl: as construct above.
void BFME2NativeNetwork::rva0025DFA1(void)
{
	QueryPerformanceFrequency(&m_performanceFrequency);
	QueryPerformanceCounter(&m_lastPerformanceCounter);
	m_accumulator = 0;
	m_stallTimerRunning = false;
	m_stallCount = 0;
	m_flag38 = false;
	TheGameLogic->rva0023D17D();
	m_lastValue = -1;
	if (m_connectionManager != 0)
		((ManagerView *)m_connectionManager)->slot02();
}
