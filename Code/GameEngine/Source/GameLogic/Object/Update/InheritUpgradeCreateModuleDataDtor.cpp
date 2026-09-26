// cl: /O1 /GX /DNDEBUG /MD /arch:SSE
//
// ??1InheritUpgradeCreateModuleData@@UAE@XZ, retail 0x004B9569, 51 bytes.
// ModuleData dtor: tears down ObjectFilter at +0x8C through the folded
// 0x360D26 body (Rva003623E5Filter pin, same ICF address as the pool-aware
// member dtors), then restores the Snapshot base vtable 0x00BBB554. Empty
// derived body with EH state 0 (EH prolog, no base call since Snapshot dtor
// is inline). Shape follows the landed RefundDieModuleDataDtor/
// RebuildHoleExposeDieModuleDataDtor (TU-local Snapshot with inline
// BBB554-restoring dtor, novtable derived, empty body). Layout from the rowed
// ctor 0x4B9508 (vtable 0x00C59768, Radius at +0x08, Upgrade helper at +0x0C
// size 0x80 via clear80, ObjectFilter at +0x8C via pinned nullary ctor,
// size 0x90 via factory 0x250CC3, INI table 0x00C59728). Caller is the slot-0
// ??_G at 0x4B954D (vtable 0xC59768).

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
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

class __declspec(novtable) InheritUpgradeCreateModuleData : public Snapshot
{
public:
	virtual ~InheritUpgradeCreateModuleData();

private:
	unsigned char m_pad04[0x8C - 4]; // +0x04..+0x8B (Radius, Upgrade helper, POD, no dtors)
	Rva003623E5Filter m_objectFilter; // +0x8C
};

InheritUpgradeCreateModuleData::~InheritUpgradeCreateModuleData()
{
}
