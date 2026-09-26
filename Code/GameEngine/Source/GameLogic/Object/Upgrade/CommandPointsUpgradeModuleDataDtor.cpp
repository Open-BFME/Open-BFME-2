// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1CommandPointsUpgradeModuleData@@UAE@XZ, retail 0x00255959, 51 bytes.
// ModuleData dtor: tears down the RequiredObject filter at +0x11C through
// the folded 0x360D26 body (Rva00360D26Member pin), then restores the
// Snapshot base vtable 0x00BBB554. Empty derived body with EH state 0
// (EH prolog 0xB71C4A, no base call since Snapshot dtor is inline).
// Shape follows PillageModuleDataDtor / SpecialEnemySenseUpdateModuleDataDtor
// (TU-local Snapshot with inline BBB554-restoring dtor, novtable derived
// to suppress own store, empty body). Layout from the rowed ctor 0x254891
// (vtable 0xBF2658 at +0, CommandPoints at +0x118, RequiredObject at +0x11C
// via 0x3623E5, size 0x120 via factory 0x2548D2) and table 0xC590E8.
// Caller is the slot-0 ??_G at 0x25593D (vtable 0xBF2658).

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
};

class __declspec(novtable) CommandPointsUpgradeModuleData : public Snapshot
{
public:
	virtual ~CommandPointsUpgradeModuleData();

private:
	unsigned char m_pad04[0x118]; // +0x04..+0x11B (base extent + CommandPoints)
	Rva00360D26Member m_requiredObject; // +0x11C
};

CommandPointsUpgradeModuleData::~CommandPointsUpgradeModuleData()
{
}
