// cl: /O1 /GX /DNDEBUG /MD /arch:SSE
//
// ??1RebuildHoleExposeDieModuleData@@UAE@XZ, retail 0x004869CC, 48 bytes.
// ModuleData dtor: tears down HoleName at +0x38 through the folded 0x36410
// body (AsciiStringMember pin, same ICF address as StringBase), then restores
// the Snapshot base vtable 0x00BBB554. Empty derived body with EH state 0
// (EH prolog, no base call since Snapshot dtor is inline). Shape follows the
// landed RefundDieModuleDataDtor/PillageModuleDataDtor (TU-local Snapshot
// with inline BBB554-restoring dtor, novtable derived, empty body). Layout
// from the rowed ctor 0x48671F (vtable 0x00C4AD40, HoleName and-zero at
// +0x38, HoleMaxHealth at +0x3C, FadeInTimeSeconds at +0x40, TransferAttackers
// at +0x44, size 0x48 via factory 0x24CB18) and buildFieldParse proc 0x486746
// (HoleName plus HoleMaxHealth table 0x00C4AE00). Caller is the slot-0 ??_G
// at 0x4869B0 (vtable 0xC4AD40).

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

class __declspec(novtable) RebuildHoleExposeDieModuleData : public Snapshot
{
public:
	virtual ~RebuildHoleExposeDieModuleData();

private:
	unsigned char m_pad04[0x38 - 4]; // +0x04..+0x37
	AsciiStringMember m_holeName; // +0x38
	float m_holeMaxHealth; // +0x3C
	float m_fadeInTimeSeconds; // +0x40
	bool m_transferAttackers; // +0x44
};

RebuildHoleExposeDieModuleData::~RebuildHoleExposeDieModuleData()
{
}
