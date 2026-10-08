// cl: -GR- -EHsc-
// ?MpOwnerSelectStrategicScenario@AptOnlineCustomMatch@@QAE_NH@Z @0x0059EB6F 64B: gated notify-set-go. With
// the info singleton present and its flag word nonzero, fire the slot-0xDC
// virtual on the info, forward the arg to the pinned 1-arg callee 0x44D5EE
// (matched as GameModePreferences::setStrategicScenario) on the +0x40C
// sub-object, then fire that sub-object's slot-0xC virtual. Else false.
struct Rva0059EB6FInfo
{
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void d23();
	virtual void d24();
	virtual void d25();
	virtual void d26();
	virtual void d27();
	virtual void d28();
	virtual void d29();
	virtual void d30();
	virtual void d31();
	virtual void d32();
	virtual void d33();
	virtual void d34();
	virtual void d35();
	virtual void d36();
	virtual void d37();
	virtual void d38();
	virtual void d39();
	virtual void d40();
	virtual void d41();
	virtual void d42();
	virtual void d43();
	virtual void d44();
	virtual void d45();
	virtual void d46();
	virtual void d47();
	virtual void d48();
	virtual void d49();
	virtual void d50();
	virtual void d51();
	virtual void d52();
	virtual void d53();
	virtual void d54();
	virtual void Notify();
};

struct Rva0059EB6FSub
{
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void Go();

	void SetScenario(int mode);
};

struct AptOnlineCustomMatch
{
	char pad[0x40c];
	Rva0059EB6FSub m_40C;

	bool MpOwnerSelectStrategicScenario(int mode);
};

extern class GameSpyInfoInterface *TheGameSpyInfo;
extern int g_rva0059EB6FFlag;

bool AptOnlineCustomMatch::MpOwnerSelectStrategicScenario(int mode)
{
	Rva0059EB6FInfo *info = (*(Rva0059EB6FInfo **)&TheGameSpyInfo);
	if (info == 0)
		return false;
	if (g_rva0059EB6FFlag == 0)
		return false;
	info->Notify();
	m_40C.SetScenario(mode);
	m_40C.Go();
	return true;
}
