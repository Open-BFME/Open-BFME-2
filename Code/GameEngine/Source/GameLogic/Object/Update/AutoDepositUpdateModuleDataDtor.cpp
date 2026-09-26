// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1AutoDepositUpdateModuleData@@UAE@XZ at retail 0x002552A7 (48B).
// Virtual dtor over vtable 0x00BF1BC8 (slot 0 deleting dtor at 0x0025528B).
// Layout from the rowed ctor TU at 0x002540ED (timing@8 amount@C bonus@10
// upgrade@14 percent@18 UpgradeMustBePresent@1C flags@20/21, news 0x1C, INI
// table 0xBF1CC8). Destruction is the UpgradeMustBePresent member at +0x1C
// via the pinned 0x00360D26 teardown then the Snapshot base vtable 0x00BBB554
// restored inline with no base call (RunOffMap/Building precedent).

class Snapshot
{
public:
	virtual ~Snapshot();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class Rva00360D26Member
{
public:
	~Rva00360D26Member();
private:
	unsigned char m_data[4];
};

class UpgradeTemplate;

class __declspec(novtable) AutoDepositUpdateModuleData : public Snapshot
{
public:
	virtual ~AutoDepositUpdateModuleData();
private:
	unsigned int m_unused04;
	unsigned int m_depositTiming;
	int m_depositAmount;
	int m_initialCaptureBonus;
	UpgradeTemplate *m_upgrade;
	float m_upgradeBonusPercent;
	Rva00360D26Member m_upgradeMustBePresent;
	bool m_giveNoXP;
	bool m_onlyWhenGarrisoned;
};

AutoDepositUpdateModuleData::~AutoDepositUpdateModuleData()
{
}
