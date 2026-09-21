// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
//
// ??0DominateEnemySpecialPowerModuleData@@QAE@XZ, retail 0x004CCA24, 122 bytes.
// SpecialPower-side ModuleData for the DominateEnemy power. The class runs
// 0xDC bytes: the pinned Rva0044EB54 SpecialPower base (0xC8) plus a float
// DominateRadius at +0xC8 plus TriggerFX at +0xCC plus DominatedFX at +0xD0
// plus PermanentlyConvert at +0xD4 plus a 4-byte filter member at +0xD8.
// The table at 0x00C5F638 (DominateRadius plus TriggerFX plus DominatedFX
// plus PermanentlyConvert plus AttributeModifierAffects) ends at +0xDC,
// exactly the factory news size, and the DominateEnemySpecialPower pool key
// at 0x4CC9DF ends where this ctor begins. NOTE: BFME1's identically-named
// ModuleData is a different, larger class (0x260 over a SpecialAbility base);
// the BFME2 layout here is retail-proven, not donor-derived. The filter
// member is built by the shared 0x3623E5 nullary (existing Rva003623E5Member
// construct pin, MobNexus-convergent) and then fed a 28-byte temp copied
// from the 0xDFEFA4 global through the rowed BfmeFixedStorage0004543D copy
// (single call; the temp doubles as the by-value arg block the 0x362120
// method cleans with ret 0x1C). Virtual base plus virtual derived with
// declared-only dtors (no code) arm the two EH states with the derived vtable
// store compiler-emitted mid-init; /Oy- forces the ebp frame with the
// __EH_prolog prologue; /arch:SSE keeps the float zero as xorps plus movss.

class Rva0044EB54
{
public:
	Rva0044EB54();
	virtual ~Rva0044EB54();

private:
	unsigned char m_pad[0xC8 - 4];
};

class BfmeFixedStorage0004543D
{
	char m_bytes[28];
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
};

extern const BfmeFixedStorage0004543D g_dominateFilterDefaults;

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	void applyFilter(BfmeFixedStorage0004543D arg);
	~Rva003623E5Filter();

private:
	int m_handle;
};

class DominateEnemySpecialPowerModuleData : public Rva0044EB54
{
public:
	DominateEnemySpecialPowerModuleData();
	virtual ~DominateEnemySpecialPowerModuleData();

private:
	float m_dominateRadius; // +0xC8
	int m_triggerFX; // +0xCC
	int m_dominatedFX; // +0xD0
	bool m_permanentlyConvert; // +0xD4
	Rva003623E5Filter m_filter; // +0xD8
};

// ??0DominateEnemySpecialPowerModuleData@@QAE@XZ @0x4CCA24
DominateEnemySpecialPowerModuleData::DominateEnemySpecialPowerModuleData()
	: m_dominateRadius(0.0f)
	, m_triggerFX(0)
	, m_dominatedFX(0)
	, m_permanentlyConvert(false)
	, m_filter()
{
	m_filter.applyFilter(g_dominateFilterDefaults);
}
