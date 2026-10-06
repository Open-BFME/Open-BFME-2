// cl: /DNDEBUG /MD /EHsc
//
// ?rva0023CF8B@GameLogic@@QAEXXZ, RVA 0x0023CF8B, 67 bytes.
// GameLogic method filling timeout array at +0x130 with timeGetTime per
// network peer. Evidence: sits between GameLogic rows 0x0023CF83 (m_150
// byte setter) and 0x0023CFCE GameLogic::getObjectCount; +0x130 array of
// 8 DWORDs ending at +0x150 matches GameLogicSetGamePaused timeouts layout;
// TheNetwork global 0x009FEA28 with virtual at +0xB4 returning peer count;
// timeGetTime IAT winmm call; caller 0x0043ADA5.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

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
	virtual void slot43(void);
	virtual void slot44(void);
	virtual int getCount(void);
};

extern NetworkInterface *TheNetwork;

class GameLogic
{
public:
	void rva0023CF8B();

private:
	char m_pad[0x130];
	unsigned long m_times[8];
};

void GameLogic::rva0023CF8B()
{
	if (TheNetwork == 0)
		return;
	int i = 0;
	int count = TheNetwork->getCount();
	if (count <= 0)
		return;
	unsigned long *dst = m_times;
	do {
		*dst = timeGetTime();
		++i;
		++dst;
		count = TheNetwork->getCount();
	} while (i < count);
}
