// cl: /O1 /Oy- /GX /arch:SSE /DNDEBUG /MD
//
// ??1PickupStuffUpdateModuleData@@UAE@XZ retail 0x00491F76 48B.
// Dtor lane: ctor rowed at 0x00491E37 in PickupStuffUpdateModuleDataCtor.cpp vtable
// 0x00C4DDE0 with slot0 ??_G at 0x00491F5A. Destroys filter at +0x10 through
// pinned 0x360D26 then restores Snapshot base vtable 0x00BBB554. Layout follows
// ctor TU (+0 vtable +4 unused +8 bool +0xC float +0x10 filter 4B +0x14 float
// size 0x18 matching factory 0x24D95B news 0x18). Shape follows AttachUpdateModuleDataDtor
// (TU-local Snapshot with inline BBB554 restore empty derived body novtable
// suppresses entry derived store retail lacks). Single tracked member gives
// and-state-0 exactly as retail. Caller is ??_G at 0x00491F5D.

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

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned char m_data[4];
};

class __declspec(novtable) PickupStuffUpdateModuleData : public Snapshot
{
public:
	virtual ~PickupStuffUpdateModuleData();

private:
	int m_unused04; // +4
	bool m_skirmishAIOnly; // +8
	float m_scanRange; // +0xC
	Rva00360D26Member m_stuffToPickUp; // +0x10
	float m_scanIntervalSeconds; // +0x14
};

PickupStuffUpdateModuleData::~PickupStuffUpdateModuleData()
{
}
