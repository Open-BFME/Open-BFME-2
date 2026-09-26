// cl: /O1 /GX /DNDEBUG /MD
//
// ??1MonitorConditionUpdateModuleData@@UAE@XZ retail 0x00491711 63B.
// Dtor lane: ctor rowed at 0x004915FD in ModelConditionSpecialAbilityUpdateModuleDataCtor.cpp
// vtable 0x00C4DA50 with slot0 ??_G at 0x004916F5. Destroys AsciiString at +0x68
// then AsciiString at +0x54 through pinned 0x36410 then restores Snapshot base
// vtable 0x00BBB554. Layout follows ctor TU (+0 vtable +4 unused +8 filter 0x4C
// +0x54 string +0x58 flags 16B +0x68 string size 0x6C matching factory 0x24D849
// news 0x6C). Shape follows LargeGroupBonusUpdateModuleDataDtor and
// FlammableUpdateModuleDataDtor (TU-local Snapshot with inline BBB554 restore
// empty derived body novtable suppresses entry derived store retail lacks).
// Caller is ??_G at 0x004916F8. EH states 1 then 0 for the two strings.

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class Rva0042526Member
{
public:
	Rva0042526Member();

private:
	unsigned char m_pad[0x4C];
};

class __declspec(novtable) MonitorConditionUpdateModuleData : public Snapshot
{
public:
	virtual ~MonitorConditionUpdateModuleData();

private:
	int m_unused04; // +4
	Rva0042526Member m_modelConditionFlags; // +8
	AsciiString m_modelConditionCommandSet; // +0x54
	unsigned long m_weaponSetFlags[4]; // +0x58
	AsciiString m_weaponToggleCommandSet; // +0x68
};

MonitorConditionUpdateModuleData::~MonitorConditionUpdateModuleData()
{
}
