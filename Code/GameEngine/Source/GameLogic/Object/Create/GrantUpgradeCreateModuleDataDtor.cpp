// cl: /O1 /GX /DNDEBUG /MD /arch:SSE
//
// ??1GrantUpgradeCreateModuleData@@UAE@XZ, retail 0x004B914B, 48 bytes.
// ModuleData dtor: tears down upgradeName at +0x08 through the folded 0x36410
// body (AsciiStringMember pin, same ICF address as StringBase), then restores
// the Snapshot base vtable 0x00BBB554. Empty derived body with EH state 0
// (EH prolog, no base call since Snapshot dtor is inline). Shape follows the
// landed RefundDieModuleDataDtor/RebuildHoleExposeDieModuleDataDtor (TU-local
// Snapshot with inline BBB554-restoring dtor, novtable derived, empty body).
// Layout from the rowed ctor 0x4B90E1 (vtable 0x00C594E0, unused04 at +0x04,
// upgradeName at +0x08 via StringBase::set, exemptStatus bitset at +0x0C via
// 0x24CA24, GiveOnBuildComplete at +0x1C, INI table 0x00C594A0). Caller is the
// slot-0 ??_G at 0x4B912F (vtable 0xC594E0).

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

class AsciiStringMember
{
public:
	~AsciiStringMember();
	char m_data[4];
};

class __declspec(novtable) GrantUpgradeCreateModuleData : public Snapshot
{
public:
	virtual ~GrantUpgradeCreateModuleData();

private:
	unsigned char m_pad04[0x08 - 4]; // +0x04..+0x07
	AsciiStringMember m_upgradeName; // +0x08
	unsigned char m_pad0C[0x1C - 0x0C]; // +0x0C..+0x1B (exemptStatus bitset, POD, no dtor)
	bool m_giveOnBuildComplete; // +0x1C
};

GrantUpgradeCreateModuleData::~GrantUpgradeCreateModuleData()
{
}
