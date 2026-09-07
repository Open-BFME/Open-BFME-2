// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2's native-network vtable slot +0x54 decides how many logic frames may
// advance during the current client tick.  The two branches are deliberately
// kept here as the retail code expresses them: clients use the connection
// manager's announced frame ceiling and command-count gate, while the packet
// router uses a QPC accumulator and the same logic-frame quantum as the pacing
// query at slot +0x58.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *counter);

struct GameLogicFrame
{
	char unknown[0x40];
	unsigned int frame;
};

class BFMEConnectionManager
{
public:
	bool areFrameCommandsComplete(unsigned int frame, bool debugSpewage);
	bool hasPacketRouterFrameStall(void);

	char unknown[0x1205C];
	volatile int frameCeiling;
};

class NetworkInterface
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void updateNetwork(int flush);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	int getFrameAdvanceCount(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual void slot37(void);
	virtual void slot38(void);
	virtual void slot39(void);
	virtual void slot40(void);
	virtual void slot41(void);
	virtual void slot42(void);
	virtual bool isPacketRouter(void);

private:
	char m_unknown04[4];
	BFMEConnectionManager *m_connectionManager;
	int m_state;
	char m_unknown14[4];
	__int64 m_frequency;
	__int64 m_lastCounter;
	__int64 m_accumulator;
	bool m_stallTimerRunning;
	char m_unknown31[3];
	unsigned int m_stallCount;
	bool m_flag38;
	int m_lastValue;
};

#define TheGameLogic (*(volatile GameLogicFrame **)0x00DFE78C)
#define LogicFramesPerSecond (*(const int *)0x00DBA4E4)
#define StallStartTime (*(unsigned long *)0x00DFEA2C)
#define LastAdvanceTime (*(unsigned long *)0x00DFEA30)
#define LastStallFrame (*(unsigned int *)0x00DFEA38)

// The compiler's external-data form is intentional: retail increments this
// global with the one-byte `inc [absolute]` encoding.  The byte verifier binds
// this relocation to the fixed BFME2 address 0x00DFEA34.
extern int NetworkTimingOverruns;

int NetworkInterface::getFrameAdvanceCount(void)
{
	if (m_state != 1)
		return 1;

	if (!isPacketRouter())
	{
		if (!m_stallTimerRunning)
		{
			StallStartTime = timeGetTime();
			m_stallTimerRunning = true;
		}

		BFMEConnectionManager *manager = m_connectionManager;
		volatile GameLogicFrame *logic = TheGameLogic;
		unsigned int ceiling = (unsigned int)manager->frameCeiling;
		unsigned int currentFrame = logic->frame;
		int allowance;
		if (ceiling >= currentFrame)
			allowance = ceiling - currentFrame;
		else
			allowance = -1;

		if (allowance > 0)
		{
			if (!manager->areFrameCommandsComplete(currentFrame + 1, false))
			{
				updateNetwork(0);
				return 0;
			}

			m_stallTimerRunning = false;
		}
		else if (currentFrame != LastStallFrame)
		{
			++m_stallCount;
			LastStallFrame = TheGameLogic->frame;
		}
		return allowance;
	}

	if (m_connectionManager->hasPacketRouterFrameStall())
	{
		m_accumulator = 0;
		return 0;
	}

	__int64 now;
	QueryPerformanceCounter(&now);
	m_accumulator += now - m_lastCounter;
	m_lastCounter = now;

	__int64 quantum = m_frequency / LogicFramesPerSecond;
	if (m_accumulator < quantum)
		return 0;

	m_accumulator -= quantum;
	if (m_accumulator > m_frequency * 2)
	{
		++NetworkTimingOverruns;
		m_accumulator = 0;
	}
	else
	{
		NetworkTimingOverruns = 0;
	}

	LastAdvanceTime = timeGetTime();
	return 1;
}
