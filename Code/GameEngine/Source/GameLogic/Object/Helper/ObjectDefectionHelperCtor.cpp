// cl: /DNDEBUG /MD
//
// ??0ObjectDefectionHelper@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0028C955, 61 bytes.
// ObjectDefectionHelper behavior ctor over the rowed ObjectHelper base
// (0x28C8DF, thing plus data): detection-window zeros at +0x20/+0x24, FX flag
// false at +0x2C, the class's three vftables (0x00BFBD40 at +0, the UpdateModule
// family's 0x00BEFF90 at +0x0C, 0x00BFBD34 at +0x10), flash phase 0.0f at
// +0x28 last. BFME1 donor is ObjectDefectionHelper.cpp; BFME2 keeps the member
// order with the float store scheduled last. The rowed factory 0x2996CC
// (news 0x30, matching this layout) is the sole raw caller, and the
// ObjectDefectionHelper pool key at 0x28C992 immediately follows.
//
// Retail 0x00BFBD40 (13 slots): deleting dtor 0x0028C9DD, loadPostProcess
// 0x00483CEF (`jmp 0x00497805`, which jumps on to UpdateModule's 0x0058B03E),
// the name getter 0x0028C9D7, xfer 0x004DF76E, getModuleNameKey 0x0028C992,
// then UpdateModule's slots. 0x00BFBD34: update 0x004DF547,
// getDisabledTypesToProcess 0x004DF396 (Zero Hour's inline DISABLEDMASK_ALL override, a
// body ICF-folded across 8 tables), rva0044DF8D.

#include "../../../../Include/GameLogic/Module/ObjectHelper.h"

// BitFlags<11> by value, as FireWeaponWhenDeadBehavior.cpp spells it: retail's DISABLEDMASK_ALL
// getter 0x004DF396 copies the mask with a memcpy call.
#pragma function(memcpy)
#include <string.h>
template <int NUM_BITS> class BitFlags
{
public:
    __forceinline BitFlags(const BitFlags &other) { memcpy(m_bits, other.m_bits, sizeof(m_bits)); }
private:
    unsigned int m_bits[(NUM_BITS + 31) / 32];
};
extern DisabledMaskType DISABLEDMASK_ALL;

class ObjectDefectionHelper : public ObjectHelper
{
public:
	ObjectDefectionHelper(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectDefectionHelper();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	// Update-interface slot 1 (0x00BFBD34): Zero Hour's inline override, ICF-folded at 0x004DF396.
	virtual DisabledMaskType getDisabledTypesToProcess() const { return DISABLEDMASK_ALL; }

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_defectionDetectionStart;		// +0x20
	unsigned int m_defectionDetectionEnd;		// +0x24
	float m_defectionDetectionFlashPhase;		// +0x28
	bool m_doDefectorFX;						// +0x2C
};

// ??0ObjectDefectionHelper@@QAE@PAVThing@@PBVModuleData@@@Z @0x28C955
ObjectDefectionHelper::ObjectDefectionHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
	m_defectionDetectionEnd = 0;
	m_defectionDetectionStart = 0;
	m_doDefectorFX = false;
	m_defectionDetectionFlashPhase = 0.0f;
}

// Slot 1 of 0x00BFBD40: 0x00483CEF, `jmp 0x00497805` to ObjectHelper's; folded
// with the other helpers' overrides (Recovery 0x00BFBD98, Repulsor 0x00BFBDF0,
// WeaponStatus 0x00BFBE48 hold it too).
void ObjectDefectionHelper::loadPostProcess()
{
	ObjectHelper::loadPostProcess();
}
