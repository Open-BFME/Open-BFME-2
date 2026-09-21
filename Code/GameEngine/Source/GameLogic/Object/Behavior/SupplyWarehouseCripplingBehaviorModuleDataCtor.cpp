// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0SupplyWarehouseCripplingBehaviorModuleData@@QAE@XZ, retail 0x00483A61,
// 25 bytes. Frameless store-only ctor over the SelfHeal table 0xC49B40
// (SelfHealSupression@8, SelfHealDelay@C, SelfHealAmount@10). Identity is
// the table plus the rowed poolkey 0x483A46 (SupplyWarehouseCripplingBehavior)
// in the same cluster plus the BFME1 SupplyWarehouseCripplingBehaviorModuleData
// donor (same 0x14 size, 3-word layout; BFME2 third field is float) plus
// factory 0x24C4BC news 0x14 sole caller plus proc 0x483A7A rowed.
// Shape follows ReflectDamage trivial-ctor precedent: flat TU-local class
// with explicit void*m_vtable (no virtuals, no vtable emission) plus
// plain-data members; body assignments in retail order; /O1 emits integer
// zero as AND, /arch:SSE emits float zero as xorps/movss. Vtable 0x00C4ED70
// is ICF-folded (DeletionUpdate/SlotToLock/ReflectDamage share).

class SupplyWarehouseCripplingBehaviorModuleData
{
public:
	SupplyWarehouseCripplingBehaviorModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	int m_selfHealSupression; // +8
	int m_selfHealDelay; // +0xC
	float m_selfHealAmount; // +0x10
};

// ??0SupplyWarehouseCripplingBehaviorModuleData@@QAE@XZ @0x483A61
SupplyWarehouseCripplingBehaviorModuleData::SupplyWarehouseCripplingBehaviorModuleData()
{
	m_selfHealSupression = 0;
	m_selfHealDelay = 0;
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
	m_selfHealAmount = 0.0f;
}
