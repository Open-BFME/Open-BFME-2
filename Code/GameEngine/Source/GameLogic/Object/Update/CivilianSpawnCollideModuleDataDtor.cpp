// cl: /O1 /DNDEBUG /MD /GX
//
// ??1CivilianSpawnCollideModuleData@@UAE@XZ, retail 0x004BD72A, 48 bytes.
// ModuleData dtor: tears down the filter at +0x08 through the folded 0x360D26
// body (Rva003623E5Filter pin), then restores the Snapshot base vtable
// 0x00BBB554. Empty derived body with EH state 0 (EH prolog 0xB8F889, no base
// call since Snapshot dtor is inline). Shape follows the landed
// PillageModuleDataDtor/SpecialEnemySenseUpdateModuleDataDtor (TU-local Snapshot
// with inline BBB554-restoring dtor, novtable derived to suppress own store,
// empty body). Layout from the rowed ctor 0x004BD651 (vtable 0xC5AAB8 at +0,
// filter at +0x08 via 0x3623E5, size 0x0C via factory 0x00251324 pushing 0xC)
// and table 0xC5AB48. Caller is the slot-0 ??_G at 0x004BD70E (vtable 0xC5AAB8).
// Donor: BFME1 CivilianSpawnCollideModuleDataCtorThunk.cpp virtual dtor.

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

class __declspec(novtable) CivilianSpawnCollideModuleData : public Snapshot
{
public:
	virtual ~CivilianSpawnCollideModuleData();

private:
	int m_unused04; // +0x04 tag
	Rva003623E5Filter m_filter; // +0x08
};

CivilianSpawnCollideModuleData::~CivilianSpawnCollideModuleData()
{
}
