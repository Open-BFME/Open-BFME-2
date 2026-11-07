// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0ToggleMountedSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x004AE0AC, 67 bytes.
// ModuleData ctor over the pinned SpecialAbilityUpdateModuleData intermediate base (0x44EB54,
// 0xC8 bytes, opaque). The chained proc 0x24F66F (rowed, on the rowed base
// proc 0x44ED95 plus table 0x00BEF770) plus the rowed ModuleData factory
// 0x24F6C5 (news 0xE0, sole caller) prove the class; the table gives the
// member names and offsets (OpacityTarget@C8/TriggerInstantlyOnCreate@CC/
// CancelDisguiseWhenDismounting@CD/MountedTemplate@D0/
// SynchronizeTimerOnSpecialPower@D4). Row supersedes the ctor pin.
//
// +0xD0 MountedTemplate is an AsciiString: retail's destructor 0x004AE10B
// releases it through 0x00036410. With that member type and the float and both
// flags in the initializer list, the compiler installs the class's own vftable
// (retail 0x00C55220, 31 ModuleData slots) second, after the two flag bytes, as
// retail does; the earlier explicit store of a zero s_vtableAnchor (a schedule
// forced by a pointer-typed +0xD0) is gone (crash-prevention, 2026-11-07).
// The 16-byte vector element is a stand-in: its
// Vector_base call resolves through the ICF-folded rowed 0x211E58 body, and
// the qualified explicit init call emits the bare call with no guard (the
// allocator temp materializes at [esp+7] exactly as retail). Row supersedes
// the ctor pin; the ??_7 vtable pin stands for identity.

#include <vector>


#include "../../../../../Libraries/Include/Lib/BfmeE16.h"


#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

class ToggleMountedSpecialAbilityUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	ToggleMountedSpecialAbilityUpdateModuleData();
	virtual ~ToggleMountedSpecialAbilityUpdateModuleData();

private:
	float m_opacityTarget;	// +0xC8 OpacityTarget
	bool m_triggerInstantlyOnCreate;	// +0xCC TriggerInstantlyOnCreate
	bool m_cancelDisguiseWhenDismounting;	// +0xCD CancelDisguiseWhenDismounting
	AsciiString m_mountedTemplate;	// +0xD0 MountedTemplate (retail dtor releases it through 0x00036410)
	unsigned char m_synchronizeTimerPad[12];	// +0xD4 SynchronizeTimerOnSpecialPower (_STL::vector raw; explicit body init)
};

// ??0ToggleMountedSpecialAbilityUpdateModuleData@@QAE@XZ @0x004AE0AC
ToggleMountedSpecialAbilityUpdateModuleData::ToggleMountedSpecialAbilityUpdateModuleData()
	: m_opacityTarget(0.0f),
	  m_triggerInstantlyOnCreate(false),
	  m_cancelDisguiseWhenDismounting(false)
{
	_STL::vector<BfmeE16> &synchronizeTimer = (_STL::vector<BfmeE16> &)m_synchronizeTimerPad;
	synchronizeTimer._STL::vector<BfmeE16>::vector();
}
