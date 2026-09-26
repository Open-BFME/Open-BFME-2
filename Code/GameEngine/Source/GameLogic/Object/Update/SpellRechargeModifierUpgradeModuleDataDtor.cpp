// cl: /O1 /GX /DNDEBUG /MD
//
// ??1SpellRechargeModifierUpgradeModuleData@@UAE@XZ, retail 0x004B608A,
// 75 bytes. ModuleData dtor: destroys the AsciiString at +0x128 through the
// folded StringBase<char> teardown at 0x00036410 (state 1) then frees the
// +0x118 vector buffer through the rowed _free at 0x00030830 (state 0) then
// restores the Snapshot base vtable 0x00BBB554. No base call since the large
// 0x118 base dtor is inline. Layout from the rowed ctor 0x004B6011 (base
// 0x118 via OpenContain 0x253487, vector at +0x118, flag at +0x124, string
// at +0x128, size 0x12C via factory 0x002503A2) and table 0x00C58460.
// Caller is the slot-0 ??_G at 0x004B606E (vtable 0x008583E0). Shape follows
// RemoveUpgradeUpgradeModuleDataDtor (TU-local Snapshot with inline
// BBB554-restoring dtor, novtable derived, empty body) plus OilSpillUpdateDtor
// (void* buffer modeled as inline-free vector since trivial destruction only
// frees) plus EmotionTrackerUpdateModuleDataDtor (custom EntryVec with
// null-checked free carrying the unwind state).

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x118 - 4];
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

template <typename T>
class StringBase
{
public:
	~StringBase();

private:
	T *m_data;
};

extern "C" void free(void *p);

struct Vec118
{
	~Vec118()
	{
		if (m_start != 0)
			free(m_start);
	}

	void *m_start;
	void *m_finish;
	void *m_end;
};

class __declspec(novtable) SpellRechargeModifierUpgradeModuleData : public Snapshot
{
public:
	virtual ~SpellRechargeModifierUpgradeModuleData();

private:
	Vec118 m_vec118; // +0x118
	bool m_flag124; // +0x124
	unsigned char m_pad125[3];
	StringBase<char> m_str128; // +0x128
};

SpellRechargeModifierUpgradeModuleData::~SpellRechargeModifierUpgradeModuleData()
{
}
