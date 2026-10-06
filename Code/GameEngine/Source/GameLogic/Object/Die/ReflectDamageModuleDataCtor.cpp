// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0ReflectDamageModuleData@@QAE@XZ, retail 0x004BAB9A, 26 bytes.
// Frameless trivial ctor: the BFME1 ReflectDamageModuleDataConstructor.cpp
// donor models a trivial base (vptr at +0 plus an untouched word at +4) with
// three zeroed members; the BFME2 table extends the semantics to a damage
// bitmask at +8 plus two float percentages at +0xC/+0x10 (see the rowed
// buildFieldParse proc holding DamageTypesToReflect plus
// ReflectDamagePercentage plus MinimumDamageToReflect). The TU-local class
// keeps an explicit vtable slot (factory-TU precedent, so no vtable is
// emitted) and plain-data members, so the body statements reproduce retail
// order: integer zero, vtable literal 0x00C4ED70, then the two float zeros
// (/arch:SSE keeps them as xorps plus movss per the DemoTrap precedent;
// /O1 keeps the integer zero as the compact and form). Size 0x14 matches the
// rowed 0x250DC2 factory news.

extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

class ReflectDamageModuleData
{
public:
	ReflectDamageModuleData();

private:
	void *m_vtable; // +0
	int m_baseTail; // +4
	int m_damageTypesToReflect; // +8
	float m_reflectDamagePercentage; // +0xC
	float m_minimumDamageToReflect; // +0x10
};

// ??0ReflectDamageModuleData@@QAE@XZ @0x4BAB9A
ReflectDamageModuleData::ReflectDamageModuleData()
{
	m_damageTypesToReflect = 0;
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00C4ED70));
	m_reflectDamagePercentage = 0.0f;
	m_minimumDamageToReflect = 0.0f;
}
