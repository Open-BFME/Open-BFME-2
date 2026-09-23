// cl: /O1 /MD /DNDEBUG
//
// ??0LockWeaponCreateModuleData@@QAE@XZ, retail 0x00254C8E,
// 12 bytes. Frameless store-only ctor installing the folded trivial
// ModuleData vtable 0x00C4ED70 plus zero at +8. Identity is the rowed
// factory 0x002509CE (news 0xC, sole SlotToLock user, pushes rowed proc
// 0x004B8C9C whose table starts with SlotToLock) whose sole ctor call is
// the pin this row supersedes. Shape follows the FloatUpdate trivial-ctor
// precedent: flat TU-local class with explicit void*m_vtable (no virtuals,
// no vtable emission) plus plain-data members; body assignments in retail
// order. Under /O1 the zero store selects the short AND form and the
// scheduler hoists AND-mem above MOV-mem (MarkerType precedent probes
// AND-first in every spelling without a barrier), reproducing retail
// mov-eax-ecx, and-[eax+8]-0, mov-[eax]-vtable. Size 0x0C matches the
// factory news. The body is ICF-folded with the StancesBehavior use at the
// same address; this row claims the LockWeaponCreate name, the alias pin
// stays parked.

class LockWeaponCreateModuleData
{
public:
	LockWeaponCreateModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	int m_slotToLock; // +8
};

// ??0LockWeaponCreateModuleData@@QAE@XZ @0x254C8E
LockWeaponCreateModuleData::LockWeaponCreateModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
	m_slotToLock = 0;
}
