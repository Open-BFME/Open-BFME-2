// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0DualWeaponBehaviorModuleData@@QAE@XZ, retail 0x0045AE25,
// 31 bytes. Frameless store-only ctor over table 0xC41858
// (SwitchWeaponOnCloseRangeDistance@8, UseCloseRangeWhileMounted@C,
// MinimumSwitchTime@10, UseHordeRangeWeapon@14, UseRealVictimRange@15).
// Identity is the rowed poolkey 0x45ADE0 (DualWeaponBehavior), which ends
// exactly where this ctor begins, plus factory 0x24B06E (news 0x18, sole
// caller) plus proc 0x45AE44 (same table). Shape follows the
// ReflectDamage/SlaveWatcher trivial-ctor precedent: flat TU-local class
// with explicit void*m_vtable (no virtuals, no vtable emission) plus
// plain-data members; body assignments in retail order; /arch:SSE emits
// the float zero as xorps/movss. Vtable 0x00C4ED70 is ICF-folded
// (DeletionUpdate/SlotToLock/ReflectDamage share it), so the install
// proves nothing by itself; table plus size plus stores do.

class DualWeaponBehaviorModuleData
{
public:
	DualWeaponBehaviorModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	float m_switchWeaponOnCloseRangeDistance; // +8
	bool m_useCloseRangeWhileMounted; // +0xC
	unsigned int m_minimumSwitchTime; // +0x10
	bool m_useHordeRangeWeapon; // +0x14
	bool m_useRealVictimRange; // +0x15
};

// ??0DualWeaponBehaviorModuleData@@QAE@XZ @0x45AE25
DualWeaponBehaviorModuleData::DualWeaponBehaviorModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
	m_switchWeaponOnCloseRangeDistance = 0.0f;
	m_useCloseRangeWhileMounted = false;
	m_minimumSwitchTime = 0;
	m_useHordeRangeWeapon = false;
	m_useRealVictimRange = false;
}
