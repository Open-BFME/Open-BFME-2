// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0AutoFindHealingUpdateModuleData@@QAE@XZ, retail 0x004950F9,
// 47 bytes. Frameless SSE store-only ctor over table 0xC4EC68
// (ScanRate@8, ScanRange@C, NeverHeal@10, AlwaysHeal@14). Identity is
// the table (stores match field offsets exactly) plus the rowed
// AutoFindHealingUpdate poolkey 0x4950B4 ending where this ctor begins
// plus factory 0x24DEFE news 0x18 sole caller plus proc 0x495128 rowed.
// Shape follows SupplyWarehouse trivial-ctor precedent: flat TU-local
// class with explicit void*m_vtable (no virtuals, no vtable emission)
// plus plain-data members; body assignments in retail order; /O1 emits
// integer zero as AND, /arch:SSE emits float zeros as xorps/movss.
// Vtable 0x00C4ED70 is ICF-folded. Floats are clean literals pooled
// by the compiler (float-ref verify matches values, not addresses).

class AutoFindHealingUpdateModuleData
{
public:
	AutoFindHealingUpdateModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	int m_scanRate; // +8
	float m_scanRange; // +0xC
	float m_neverHeal; // +0x10
	float m_alwaysHeal; // +0x14
};

// ??0AutoFindHealingUpdateModuleData@@QAE@XZ @0x4950F9
AutoFindHealingUpdateModuleData::AutoFindHealingUpdateModuleData()
{
	m_scanRate = 0;
	m_scanRange = 0.0f;
	m_neverHeal = 0.95f;
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
	m_alwaysHeal = 0.25f;
}
