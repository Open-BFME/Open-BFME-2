// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0FireSpreadUpdateModuleData@@QAE@XZ, retail 0x0048B73C, 28 bytes.
// Frameless store-only ctor over the OCLEmbers table 0xC4C000
// (OCLEmbers@8, MinSpreadDelay@C, MaxSpreadDelay@10, SpreadTryRange@14).
// Identity is the table matching every store below plus the rowed poolkey
// 0x48B6BA (FireSpreadUpdate) in the same cluster plus the BFME1
// FireSpreadUpdateModuleData donor (same 4 fields in order) plus factory
// 0x24CECD news 0x18 sole caller plus proc 0x48B758 rowed. Shape follows
// ReflectDamage trivial-ctor precedent: flat TU-local class with explicit
// void*m_vtable (no virtuals, no vtable emission) plus plain-data members;
// body assignments in retail order; /O1 emits integer zero as AND,
// /arch:SSE emits float zero as xorps/movss. Vtable 0x00C4ED70 is
// ICF-folded (DeletionUpdate/SlotToLock/ReflectDamage share).

class FireSpreadUpdateModuleData
{
public:
	FireSpreadUpdateModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	int m_oclEmbers; // +8
	int m_minSpreadDelay; // +0xC
	int m_maxSpreadDelay; // +0x10
	float m_spreadTryRange; // +0x14
};

// ??0FireSpreadUpdateModuleData@@QAE@XZ @0x48B73C
FireSpreadUpdateModuleData::FireSpreadUpdateModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
	m_minSpreadDelay = 0;
	m_maxSpreadDelay = 0;
	m_oclEmbers = 0;
	m_spreadTryRange = 0.0f;
}
