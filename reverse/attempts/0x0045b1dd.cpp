// ??0AimWeaponBehaviorModuleData@@QAE@XZ
// partial score=0.98 date=2026-09-21
// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0AimWeaponBehaviorModuleData@@QAE@XZ, retail 0x0045B1DD,
// 55 bytes. Frameless store-only ctor over table 0xC41948
// (AimLowThreshold@8 = -0.05f, AimHighThreshold@C = +0.05f,
// AimNearDistance@10 = 0.0f, AimFarDistance@14 = 0.0f).
// Identity is the rowed poolkey 0x45B198 (AimWeaponBehavior), which ends
// exactly where this ctor begins, plus factory 0x24B0F7 (news 0x18, sole
// caller) plus proc 0x45B215 (same table). Shape follows the
// DualWeapon/SlaveWatcher trivial-ctor precedent: flat TU-local class
// with explicit void*m_vtable (no virtuals, no vtable emission) plus
// plain-data members; body assignments in retail order; /arch:SSE emits
// mem-load movss for the pool literals. The float literals merge into the
// retail pool (Oathbreakers precedent). Vtable 0x00C4ED70 is ICF-folded,
// so the install proves nothing by itself; table plus size plus stores do.

// Retail pool float at VA 0x00BBB8E8 (value 0.0f); loaded, not xorred.
// extern (non-const) keeps the movss shape; the slot is DIR32-masked.
extern float g_aimFarDistanceDefault;

class AimWeaponBehaviorModuleData
{
public:
	AimWeaponBehaviorModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
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
	m_aimFarDistance = g_aimFarDistanceDefault;
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
}
