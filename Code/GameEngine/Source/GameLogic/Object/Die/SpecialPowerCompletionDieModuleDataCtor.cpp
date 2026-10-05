// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0SpecialPowerCompletionDieModuleData@@QAE@XZ, retail 0x004C230E,
// 22 bytes. Frameless ctor over the pinned SEH base
// (??0DestroyDieModuleData@@QAE@XZ at 0x253510, shared with the UpgradeDie ctor):
// base call, then the compact and-zero of the SpecialPowerTemplate word
// at +0x38, then the folded-trivial vtable literal 0x00C4ED70 (shared by
// DeletionUpdate plus SlotToLock plus ReflectDamage, so the install alone
// proves nothing). Unlike the UpgradeDie sibling, retail keeps the natural
// /O1 and-before-mov order here, so no barrier is needed. Size 0x3C
// matches the 0x253B05 factory news. Class identity is the rowed
// SpecialPowerCompletionDieModuleData::buildFieldParse proc (single
// SpecialPowerTemplate field at +0x38 per the BFME1 donor) beside the
// rowed SpecialPowerCompletionDie pool key and behavior rows.

extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

class DestroyDieModuleData
{
public:
	DestroyDieModuleData();
};

class SpecialPowerCompletionDieModuleData : public DestroyDieModuleData
{
public:
	SpecialPowerCompletionDieModuleData();

private:
	void *m_vtable; // +0 (explicit; no virtuals declared, so no vtable is emitted)
	unsigned char m_pad[0x34]; // +4..0x37 (BFME2 base runs 4 wider than BFME1's 0x34)
	int m_specialPowerTemplate; // +0x38 (name key; BFME1 int m_34)
};

// ??0SpecialPowerCompletionDieModuleData@@QAE@XZ @0x4C230E
inline SpecialPowerCompletionDieModuleData::SpecialPowerCompletionDieModuleData()
{
	m_specialPowerTemplate = 0;
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00C4ED70));
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeSpecialPowerCompletionDieModuleDataInlineAnchor@@YAXPAVSpecialPowerCompletionDieModuleData@@@Z absent-from-retail
void _bfmeSpecialPowerCompletionDieModuleDataInlineAnchor(SpecialPowerCompletionDieModuleData *p)
{
    p->SpecialPowerCompletionDieModuleData::SpecialPowerCompletionDieModuleData();
}
#pragma inline_depth()
