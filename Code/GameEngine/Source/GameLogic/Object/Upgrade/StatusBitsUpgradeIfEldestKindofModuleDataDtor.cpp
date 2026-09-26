// cl: /O1 /DNDEBUG /MD /GX
//
// ??1StatusBitsUpgradeIfEldestKindofModuleData@@UAE@XZ, retail 0x0025575C,
// 57 bytes. EldestKindof dtor over the rowed StatusBitsUpgradeModuleData
// base (0x00254775, size 0x138): destroys the +0x138 filter through the
// pinned 0x00360D26 (state 0) then restores the Snapshot base vtable
// 0x00BBB554 with no base call since Snapshot dtor is inline. The filter
// rides as a second base to reproduce retail's null-checked this-adjustment
// (neg plus sbb plus and plus lea) which a plain member does not emit.
// Layout from the rowed ctor 0x002547D1 (base plus filter at +0x138 via
// rowed 0x00485ADC size 0x13C via factory 0x002556EC) and own vtable
// 0x00BF25D8. Caller is the slot-0 ??_G at 0x00255740. Shape follows
// CreateObjectDieIfEldestKindofModuleDataDtor (second-base filter) plus
// PillageModuleDataDtor (inline BBB554 restore).

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

class StatusBitsUpgradeModuleData : public Snapshot
{
public:
	virtual ~StatusBitsUpgradeModuleData();

private:
	unsigned char m_pad04[0x138 - 4]; // +0x04..+0x137, real base tail
};

// ??1StatusBitsUpgradeModuleData@@UAE@XZ present-unmatched
inline StatusBitsUpgradeModuleData::~StatusBitsUpgradeModuleData()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

class __declspec(novtable) StatusBitsUpgradeIfEldestKindofModuleData : public StatusBitsUpgradeModuleData, public Rva00360D26Member
{
public:
	virtual ~StatusBitsUpgradeIfEldestKindofModuleData();
};

StatusBitsUpgradeIfEldestKindofModuleData::~StatusBitsUpgradeIfEldestKindofModuleData()
{
}
