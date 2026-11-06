// cl: /GX /DNDEBUG /MD /Ireference/shims/moduledata
// ??0WindModuleInfo@FXParticleSystem@@QAE@XZ @0x003A53C4 186B: WindModuleInfo
// default ctor. Vtable 0x00BE15A4; +0x04 int 1; the ten float slots and the
// +0x3C bool and the two trailing zero floats are initialized in retail order.
// The vtable store is the compiler's own (DIR32). Float loads use .rdata constants and two distinct writable .data globals.
// Target .data: 0x00E02904 starts at 0.0f; 0x00DC0A9C starts at 5.4977874756f.
// Each has only this constructor as a direct code reference. Names below are
// address-derived; their original identities remain unknown. The readable
// floats and initial values come from movss loads and the loaded PE data,
// not from the earlier kG7 initializer (which incorrectly merged three sites).
//
// The recovered shape, and why it is this shape: retail is a strictly
// alternating load/store sequence -- every `movss xmm,[global]` is immediately
// followed by the `movss [eax+off],xmm` that consumes it, with no hoisting.
// Writing the ctor as an INIT LIST does not reproduce that: MSVC emits the
// members in DECLARATION order after folding the constants into globals, and
// it hoists the loads. Assigning in the BODY, in retail's order, does.
//
// Two ordering facts that the byte match pins and that declaration order would
// have hidden:
//   - +0x24 is stored AFTER +0x2C, and +0x30 after +0x38
//   - the global at 0xC1B2F8 is named twice, for +0x18 and +0x1C, and retail
//     reloads it rather than reusing the register
// Both are unrecoverable from declaration order alone.
//
// One `xorps xmm0,xmm0` supplies all four zeros (+0x14, +0x28, +0x40, +0x44);
// xmm0 carries the first three globals and xmm1 the rest. That split falls out
// of the assignment order rather than being requested.

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "Common/Snapshot.h"

#include "../../../../Include/GameClient/WindModuleInfo.h"

namespace FXParticleSystem {
inline WindModuleInfo::~WindModuleInfo() {}
inline void WindModuleInfo::LoadPostProcess() {}

const float WindModuleInfo::DEFAULT_STRENGTH = 2.0;
const float WindModuleInfo::DEFAULT_FULL_STRENGTH_DIST = 75.0;
const float WindModuleInfo::DEFAULT_ZERO_STRENGTH_DIST = 200.0;
const float WindModuleInfo::DEFAULT_ANGLE_CHANGE = 0.15;
const float WindModuleInfo::DEFAULT_ANGLE_CHANGE_MAX = 0.45;
const float WindModuleInfo::DEFAULT_MOTION_START_ANGLE_MAX = 0.78539818525314331;
#pragma const_seg(".data")
const float WindModuleInfo::DEFAULT_MOTION_START_ANGLE = 0.0f;
#pragma const_seg()
const float WindModuleInfo::DEFAULT_MOTION_END_ANGLE_MIN = 5.4977874755859375;
const float WindModuleInfo::DEFAULT_MOTION_END_ANGLE_MAX = 6.2831854820251465;
#pragma const_seg(".data")
const float WindModuleInfo::DEFAULT_MOTION_END_ANGLE = 5.4977874755859375f;
#pragma const_seg()
const float WindModuleInfo::DEFAULT_ANGLE = 0.0f;
const float WindModuleInfo::DEFAULT_ANGLE_CHANGE_MIN = 0.15f;
const float WindModuleInfo::DEFAULT_MOTION_START_ANGLE_MIN = 0.0f;
const char WindModuleInfo::DEFAULT_MOTION_MOVING_TO_END_ANGLE = 1;
const float WindModuleInfo::DEFAULT_TURBULENCE_AMPLITUDE = 0.0f;
const float WindModuleInfo::DEFAULT_TURBULENCE_FREQUENCY = 0.0f;

const WindMotion WindModuleInfo::DEFAULT_MOTION = WIND_MOTION_NOT_USED;

WindModuleInfo::WindModuleInfo()
{
	m_04 = DEFAULT_MOTION;
	m_08 = DEFAULT_STRENGTH;
	m_0C = DEFAULT_FULL_STRENGTH_DIST;
	m_10 = DEFAULT_ZERO_STRENGTH_DIST;
	m_14 = 0.0f;
	m_18 = DEFAULT_ANGLE_CHANGE;
	m_1C = DEFAULT_ANGLE_CHANGE;
	m_20 = DEFAULT_ANGLE_CHANGE_MAX;
	m_28 = 0.0f;
	m_2C = DEFAULT_MOTION_START_ANGLE_MAX;
	m_24 = static_cast<const volatile float &>(DEFAULT_MOTION_START_ANGLE);
	m_34 = DEFAULT_MOTION_END_ANGLE_MIN;
	m_38 = DEFAULT_MOTION_END_ANGLE_MAX;
	m_30 = static_cast<const volatile float &>(DEFAULT_MOTION_END_ANGLE);
	m_3C = true;
	m_40 = 0.0f;
	m_44 = 0.0f;
}
}

// ??0Rva005FEA50Base@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@1@PBX@Z
// retail 0x003A5856 56B: the Wind module base the rowed 0x003A58A6 module
// ctor calls. It builds the shared three-vtable default-module base through
// the rowed 0x0055BEE9 (both arguments passed straight through), then the
// WindModuleInfo at +0x1C through the rowed 0x003A53C4 above, then stores
// its own four address points: the primary (0x00C1B5A8), the two
// vtable-only bases at +0x14/+0x18 (both 0x00C1C780, ICF-folded tables)
// and the WindModuleInfo point (0x00C1B598). The class view of the base
// mirrors DefaultModuleBaseCopyCtors.cpp.
#include "../../../../Include/Common/RvaSmartPtr12.h"

#include "../../../../Include/GameClient/DefaultModuleHeadBase.h"

class DefaultModuleSecondBase
{
public:
	virtual ~DefaultModuleSecondBase();
};

class DefaultModuleThirdBase
{
public:
	virtual ~DefaultModuleThirdBase();
};

#include "../../../../Include/GameClient/Rva003AEEB3.h"

namespace FXParticleSystem {

class ParticleSystem;

template <class T> class TrackingPtr : public RvaSmartPtr12
{
};

class Rva005FEA50Base : public Rva003AEEB3, public WindModuleInfo
{
public:
	Rva005FEA50Base(TrackingPtr<ParticleSystem> &system, const void *source);
	virtual ~Rva005FEA50Base();
};

Rva005FEA50Base::Rva005FEA50Base(TrackingPtr<ParticleSystem> &system, const void *source)
	: Rva003AEEB3(system, (int)source)
{
}

}
