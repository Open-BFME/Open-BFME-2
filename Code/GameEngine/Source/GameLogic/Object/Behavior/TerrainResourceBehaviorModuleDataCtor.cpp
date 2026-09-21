// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
//
// ??0TerrainResourceBehaviorModuleData@@QAE@XZ, retail 0x0048202F, 91 bytes.
// EH ctor over the Income table 0xC494F0 (Radius@8, MaxIncome@C,
// IncomeInterval@10, HighPriority@14, Visible@15, UpgradeMustBePresent@18,
// Upgrade@1C, UpgradeBonusPercent@20). Identity is the table plus the
// TerrainResourceBehavior poolkey 0x481FBD in the same cluster plus factory
// 0x24C2A4 (news 0x24, sole caller) plus rowed proc 0x48208A.
// Shape follows Devastate V5 precedent: virtual base (declared-only virtual
// dtor, no code) is the TU's sole unwindable, which arms retail's EH frame
// with its single state-0 store; the member has no declared dtor so the
// 0x3623E5 call advances no state. The derived vtable store is
// compiler-emitted (virtual classes, TU-local, nothing defined so no vtable
// is emitted here; the store resolves through the ??_7 pin at the true
// vtable 0x00C49440, whose slot0 is the scalar-deleting dtor 0x482259).
// /Oy- forces the ebp frame with the __EH_prolog prologue; /arch:SSE keeps
// the float zeros as xorps plus movss; init-list (-1) emits the or form.

class TerrainResourceModuleDataBase
{
public:
	TerrainResourceModuleDataBase() {}
	virtual ~TerrainResourceModuleDataBase();

private:
	unsigned char m_pad[8 - 4];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();

	unsigned int m_data; // +0, 4-aligned: retail pads +0x16/+0x17 before +0x18
};

class TerrainResourceBehaviorModuleData : public TerrainResourceModuleDataBase
{
public:
	TerrainResourceBehaviorModuleData();
	virtual ~TerrainResourceBehaviorModuleData();

private:
	float m_radius; // +8
	int m_maxIncome; // +0xC
	int m_incomeInterval; // +0x10
	bool m_highPriority; // +0x14
	bool m_visible; // +0x15
	Rva003623E5Member m_upgradeMustBePresent; // +0x18
	int m_upgrade; // +0x1C
	float m_upgradeBonusPercent; // +0x20
};

// ??0TerrainResourceBehaviorModuleData@@QAE@XZ @0x48202F
TerrainResourceBehaviorModuleData::TerrainResourceBehaviorModuleData()
	: TerrainResourceModuleDataBase()
	, m_radius(0.0f)
	, m_maxIncome(0)
	, m_incomeInterval(-1)
	, m_highPriority(false)
	, m_visible(true)
	, m_upgradeMustBePresent()
	, m_upgrade(0)
	, m_upgradeBonusPercent(1.0f)
{
}
