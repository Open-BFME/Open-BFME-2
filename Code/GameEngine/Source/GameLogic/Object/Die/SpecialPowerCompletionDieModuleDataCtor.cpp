// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0SpecialPowerCompletionDieModuleData@@QAE@XZ, retail 0x004C230E,
// 22 bytes. Frameless ctor over the pinned SEH base
// (??0Rva00253510@@QAE@XZ at 0x253510, shared with the UpgradeDie ctor):
// base call, then the compact and-zero of the SpecialPowerTemplate word
// at +0x38, then the folded-trivial vtable literal 0x00C4ED70 (shared by
// DeletionUpdate plus SlotToLock plus ReflectDamage, so the install alone
// proves nothing). Unlike the UpgradeDie sibling, retail keeps the natural
// /O1 and-before-mov order here, so no barrier is needed. Size 0x3C
// matches the 0x253B05 factory news. Class identity is the rowed
// SpecialPowerCompletionDieModuleData::buildFieldParse proc (single
// SpecialPowerTemplate field at +0x38 per the BFME1 donor) beside the
// rowed SpecialPowerCompletionDie pool key and behavior rows.

class Rva00253510
{
public:
	Rva00253510();
};

class SpecialPowerCompletionDieModuleData : public Rva00253510
{
public:
	SpecialPowerCompletionDieModuleData();

private:
	void *m_vtable; // +0 (explicit; no virtuals declared, so no vtable is emitted)
	unsigned char m_pad[0x34]; // +4..0x37 (BFME2 base runs 4 wider than BFME1's 0x34)
	int m_specialPowerTemplate; // +0x38 (name key; BFME1 int m_34)
};

// ??0SpecialPowerCompletionDieModuleData@@QAE@XZ @0x4C230E
SpecialPowerCompletionDieModuleData::SpecialPowerCompletionDieModuleData()
{
	m_specialPowerTemplate = 0;
	m_vtable = reinterpret_cast<void *>(0x00C4ED70);
}
