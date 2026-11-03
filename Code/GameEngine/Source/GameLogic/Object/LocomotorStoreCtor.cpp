// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0LocomotorStore@@QAE@XZ, retail 0x0022078E (54 bytes).
// LocomotorStore default ctor: nulls +0/+4, constructs the +0x08 member
// through the opaque 0x3623E5 pin (same member-pin as the landed
// AnimationSteeringUpdateModuleData ctor 0x4BD651, which shares the
// lea-ecx-[esi+8] + call shape), returns this. SEH B8+E8 head with two
// EH states (0 after the null stores, 1 across the member call).
// Unlike ZH's SubsystemInterface-based store, retail stores no vtable here:
// +0/+4 are plain zeroed scalars, so the class is modeled without a
// polymorphic base. The companion68B destructor2207C4 and shared native EH map prove string
// lifetimes at +0/+4. The +8 handle role remains unproven.

#include "ascii_string.h"

#include "../../../Include/GameLogic/Module/Rva003623E5Member.h"

class LocomotorStore
{
public:
	LocomotorStore();

private:
	AsciiString m_slot00;
	AsciiString m_slot04;
	Rva003623E5Member m_templates;
};

// ??0LocomotorStore@@QAE@XZ
LocomotorStore::LocomotorStore()
{
}
