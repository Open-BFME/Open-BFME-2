// cl: /O1 /GX /MD /DNDEBUG
//
// ??1MonsterDockUpdateModuleData@@UAE@XZ, retail 0x004A156E, 48 bytes.
// ModuleData dtor: tears down the filter at +0x10 through the folded 0x360D26
// body (Rva003623E5Filter pin), then restores the Snapshot base vtable
// 0x00BBB554. Empty derived body with EH state 0 (EH prolog 0xB8DB78, no base
// call since Snapshot dtor is inline). Shape follows the landed
// PillageModuleDataDtor/SpecialEnemySenseUpdateModuleDataDtor (TU-local Snapshot
// with inline BBB554-restoring dtor, novtable derived to suppress own store,
// empty body). Layout from the rowed ctor 0x004A1517 (vtable 0xC51DA8 at +0,
// filter at +0x10 via 0x3623E5, zero at +0x14, size 0x18 via factory 0x0024EB2C)
// and table 0xC51CE4. Caller is the slot-0 ??_G at 0x004A1552 (vtable 0x851DA8).
// Donor: BFME1 MonsterDockUpdateModuleDataCtorThunk.cpp virtual dtor.

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

class Rva003623E5Filter
{
public:
	~Rva003623E5Filter();
};

class __declspec(novtable) MonsterDockUpdateModuleData : public Snapshot
{
public:
	virtual ~MonsterDockUpdateModuleData();

private:
	int m_unused04; // +0x04
	int m_unused08; // +0x08
	int m_unused0C; // +0x0C
	Rva003623E5Filter m_filter; // +0x10
	int m_dockedAnimationTime; // +0x14
};

MonsterDockUpdateModuleData::~MonsterDockUpdateModuleData()
{
}
