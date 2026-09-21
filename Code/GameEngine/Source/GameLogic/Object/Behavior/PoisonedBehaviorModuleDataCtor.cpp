// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0PoisonedBehaviorModuleData@@QAE@XZ, retail 0x00253CDD, 17 bytes.
// Frameless trivial ctor with no base call: the and-zeros of the
// PoisonDamageInterval word at +8 and the PoisonDuration word at +0xC,
// then the folded-trivial vtable literal 0x00C4ED70 (shared by many
// ModuleData classes, so the install alone proves nothing). Size 0x10
// matches the 0x24C3A6 factory news. The row supersedes the sole-caller
// pin. Class identity is the rowed PoisonedBehaviorModuleData::
// buildFieldParse proc (PoisonDamageInterval at +0x8 plus PoisonDuration
// at +0xC) beside the rowed PoisonedBehavior pool key (0x482F27).

class PoisonedBehaviorModuleData
{
public:
	PoisonedBehaviorModuleData();

private:
	void *m_vtable; // +0 (explicit; no virtuals declared, so no vtable is emitted)
	int m_unused04; // +4
	int m_poisonDamageInterval; // +8
	int m_poisonDuration; // +0xC
};

// ??0PoisonedBehaviorModuleData@@QAE@XZ @0x253CDD
PoisonedBehaviorModuleData::PoisonedBehaviorModuleData()
{
	m_poisonDamageInterval = 0;
	m_poisonDuration = 0;
	m_vtable = reinterpret_cast<void *>(0x00C4ED70);
}
