// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0AimWeaponBehaviorModuleData@@QAE@XZ, retail 0x0045B1DD, 55 bytes.
// Frameless store-only ctor over the Aim table 0xC41948 (AimLowThreshold@8,
// AimHighThreshold@C, AimNearDistance@10, AimFarDistance@14). Identity is the
// table plus the rowed AimWeaponBehavior poolkey 0x45B1B0 ending exactly
// where this ctor begins plus factory 0x24B0F7 (news 0x18, sole caller) plus
// rowed proc 0x45B215. Shape follows the HeightDie trivial-ctor precedent:
// flat TU-local class with explicit void*m_vtable (no virtuals, no vtable
// emission) plus plain-data members; body assignments in retail order; /O1
// keeps the float pool-loads in place and /arch:SSE emits the near-zero as
// xorps plus movss. Vtable 0x00C4ED70 is ICF-folded
// (DeletionUpdate/SlotToLock/ReflectDamage share). Defaults come from the
// retail pool (-0.05/+0.05/FLT_MAX, float-ref verified).

#include <cfloat>

class AimWeaponBehaviorModuleData
{
public:
	AimWeaponBehaviorModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4 (retail never stores it)
	float m_aimLowThreshold; // +8
	float m_aimHighThreshold; // +0xC
	float m_aimNearDistance; // +0x10
	float m_aimFarDistance; // +0x14
};

// ??0AimWeaponBehaviorModuleData@@QAE@XZ @0x45B1DD
AimWeaponBehaviorModuleData::AimWeaponBehaviorModuleData()
{
	m_aimLowThreshold = -0.05f;
	m_aimHighThreshold = 0.05f;
	m_aimNearDistance = 0.0f;
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
	m_aimFarDistance = FLT_MAX;
}
