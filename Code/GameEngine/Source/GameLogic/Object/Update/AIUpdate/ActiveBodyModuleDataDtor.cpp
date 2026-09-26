// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1ActiveBodyModuleData@@UAE@XZ, retail 0x00256CB0, 93 bytes. Virtual
// dtor over vtable 0x0085AFB8 (slot 0 deleting dtor at 0x004BF9B8 calls
// this body). Frees the damage-creation vector buffer at +0x58 through
// the rowed _free at 0x00030830 then destroys the grab strings at +0x34
// +0x30 +0x2C through the pinned StringBase teardown at 0x00036410 then
// restores the Snapshot base vtable 0x00BBB554. Layout from the rowed
// ctor TU at 0x004BF59F (news 0x64 vtable 0xC5AFB8 vector +0x58 via
// 0x00211E58 strings +0x2C/+0x30/+0x34). Shape follows RankInfoDtor
// (inline vector dtor emitting test-free plus inline string dtors) over
// the SupplyTruck precedent. Unblocks SymbioticStructuresBody 0x002570F9
// plus deleting dtor 0x004BF9B8.

void free(void *p);

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

struct DamageCreationVec
{
	~DamageCreationVec()
	{
		if (m_start)
			free(m_start);
	}

	void *m_start;
	void *m_finish;
	void *m_end;
};

class __declspec(novtable) ActiveBodyModuleData : public Snapshot
{
public:
	virtual ~ActiveBodyModuleData();

private:
	int m_unused04; // +0x04
	float m_maxHealth; // +0x08
	float m_initialHealth; // +0x0C
	float m_maxHealthDamaged; // +0x10
	float m_maxHealthReallyDamaged; // +0x14
	float m_dodgePercent; // +0x18
	int m_enteringDamaged; // +0x1C
	int m_enteringReallyDamaged; // +0x20
	int m_recoveryTime; // +0x24
	unsigned char m_useDefault; // +0x28
	unsigned char m_pad29[3]; // +0x29
	AsciiString m_grabObject; // +0x2C
	AsciiString m_damagedAttr; // +0x30
	AsciiString m_reallyDamagedAttr; // +0x34
	int m_grabFX; // +0x38
	float m_grabDamage; // +0x3C
	float m_grabOffsetX; // +0x40
	float m_grabOffsetY; // +0x44
	const void *m_healingBuffFx; // +0x48
	float m_cheerRadius; // +0x4C
	unsigned char m_removeUpgrades; // +0x50
	unsigned char m_burningBehavior; // +0x51
	unsigned char m_pad52[2]; // +0x52
	int m_burningFX; // +0x54
	DamageCreationVec m_damageCreation; // +0x58 (0x0C bytes to 0x64)
};

ActiveBodyModuleData::~ActiveBodyModuleData()
{
}
