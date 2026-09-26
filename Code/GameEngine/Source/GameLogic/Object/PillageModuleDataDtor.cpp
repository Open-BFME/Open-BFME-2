// cl: /O1 /DNDEBUG /MD /GX
//
// ??1PillageModuleData@@UAE@XZ, retail 0x0025501B, 48 bytes.
// ModuleData dtor: tears down the filter at +0x10 through the folded 0x360D26
// body (Rva003623E5Filter pin), then restores the Snapshot base vtable
// 0x00BBB554. Empty derived body with EH state 0 (EH prolog 0xB71C4A, no base
// call since Snapshot dtor is inline). Shape follows the landed
// SpecialEnemySenseUpdateModuleDataDtor (TU-local Snapshot with inline
// BBB554-restoring dtor, novtable derived to suppress own store, empty body).
// Layout from the rowed ctor 0x253830 (vtable 0xBF0568 at +0, PillageAmount
// at +8, NumDamageEvents at +0xC, PillageFilter at +0x10 via 0x3623E5, size
// 0x14 via factory 0x25388A) and table 0xBF0620. Caller is the slot-0 ??_G at
// 0x254FFF (vtable 0xBF0568).

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

class __declspec(novtable) PillageModuleData : public Snapshot
{
public:
	virtual ~PillageModuleData();

private:
	int m_unused04; // +0x04
	int m_pillageAmount; // +0x08
	int m_numDamageEvents; // +0x0C
	Rva003623E5Filter m_pillageFilter; // +0x10
};

PillageModuleData::~PillageModuleData()
{
}
