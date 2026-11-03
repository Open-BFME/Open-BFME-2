// Identity correction: ModuleFactory registers OpenContain with ctor 0x465124,
// not this 0x253487 ctor. Its 0x118-byte upgrade-base layout remains PC-proven;
// the earlier OpenContain/DieMuxData donor attribution below is withdrawn.
// cl: /O1 /MD -D_STLP_NO_EXCEPTIONS /EHs-c-
// ??0Rva00253487Base@@QAE@XZ @ 0x00253487 (21B): base ctor installing
// the folded vtable 0x00BF2558 (shared with derived HealContainModuleData,
// whose 36B ctor is matched in HealContainModuleDataCtorThunk.cpp) then
// constructing the member at +8.
// ?construct@Rva0025342CMember@@QAEPAV1@XZ @ 0x0025342C (73B): zeroes two
// 0x80-byte blocks through the shared clear80 helper, initializes the
// trailing state at +0x100, and returns this.
// The +8 member's semantic identity is unproven: ZH OpenContain.h says the
// first member is DieMuxData and DieModule.cpp already carries a
// ??0DieMuxData@@ present-unmatched marker for the concept, but the body at
// 0x0025342C has no independent identity yet, so the callee keeps an
// address-derived name here (pinned) instead of a guessed class name.
extern "C" const void *const __identifier("??_7WeaponSetUpgradeModuleData@@6B@")[];  // vftable 0x00BF2558

#include "../../../../Include/GameLogic/Module/Rva00253487Base.h"



// ?construct@Rva0025342CMember@@QAEPAV1@XZ, retail 0x0025342C, 73 bytes.
// Zeroes two 0x80-byte blocks through the shared helper, then initializes
// the trailing state at +0x100. Helper identity unproven (pinned opaque).

// ?construct@Rva0025342CMember@@QAEPAV1@XZ
Rva0025342CMember *Rva0025342CMember::construct()
{
	m_sub0.clear80();
	m_sub1.clear80();
	int *tail = &m_tail0;
	tail[0] = -1;
	tail[1] = 0;
	tail[2] = 0;
	m_tail0 = -1;
	m_tailByte0 = 0;
	m_tailByte1 = 0;
	m_tail1 = 0;
	m_tail2 = 0;
	m_tailByte2 = 0;
	return this;
}

// ??0Rva00253487Base@@QAE@XZ
Rva00253487Base::Rva00253487Base()
{
	*(unsigned int *)this = ((unsigned int)__identifier("??_7WeaponSetUpgradeModuleData@@6B@"));
	m_member08.construct();
}
