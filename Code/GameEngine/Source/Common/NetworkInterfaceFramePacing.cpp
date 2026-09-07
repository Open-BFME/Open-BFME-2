// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX /arch:SSE
//
// BFME2's native network vtable stores the concrete pacing query at +0x58.
// The fields below are deliberately laid out from the constructor and the
// retail body; no network policy is changed by exposing this query.

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *counter);

struct GameLogicFrame
{
	char unknown[0x40];
};

struct BFMEConnectionManager
{
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
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	int getFramePacingStatus(void);
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
};

#define TheGameLogic (*(volatile GameLogicFrame **)0x00DFE78C)
#define LogicFramesPerSecond (*(const int *)0x00DBA4E4)
#define OneAndHalf (*(const float *)0x00BC8980)

int NetworkInterface::getFramePacingStatus(void)
{
	if (m_state != 1)
		return 1;

	if (!isPacketRouter())
		return m_connectionManager->frameCeiling
			- *(const int *)((const char *)TheGameLogic + 0x40);

	__int64 now;
	QueryPerformanceCounter(&now);
	m_accumulator += now - m_lastCounter;
	m_lastCounter = now;

	now = m_frequency / LogicFramesPerSecond;
	if (m_accumulator < now)
		return 0;

	if ((float)m_accumulator < (float)now * OneAndHalf)
		return 1;

	return 2;
}
