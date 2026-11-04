// cl: /DNDEBUG /MD /EHsc /O1 /Ob2 /arch:SSE

// Emission info default constructors.
//
// SphericalEmissionVelocityInfo retail 0x003A721F: implicit base, own
// vtable 0x00C1BC30, inline zeroing of the single random variable, then
// setRange(0, 0) through the default UNIFORM distribution at rowed
// 0x002341E7. Needs /EHsc (outlined prologue with unwind state), unlike
// the /GX- copy ctors in EmissionInfoCopyCtors.cpp.

#include "../../../../Include/GameClient/GameClientRandomVariable.h"
#include "../../../../Include/GameClient/GameClientRandomVariableInlines.h"

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

#include "../../../../Include/GameClient/EmissionVolumeInfo.h"
#include "../../../../Include/GameClient/EmissionVelocityInfo.h"
#include "../../../../Include/GameClient/CylindricalEmissionVelocityInfo.h"
#include "../../../../../Libraries/Include/Lib/Coord3DInline.h"
#include "../../../../Include/GameClient/DefaultPhysicsModuleInfo.h"
#include "../../../../Include/GameClient/TerrainFireEmissionInfo.h"
#include "../../../../Include/GameClient/SphericalEmissionVelocityInfo.h"
#include "../../../../Include/GameClient/OrthoEmissionVelocityInfo.h"
namespace FXParticleSystem
{


inline SphericalEmissionVelocityInfo::~SphericalEmissionVelocityInfo() {}

// ??0SphericalEmissionVelocityInfo@FXParticleSystem@@QAE@XZ @0x3A721F
inline SphericalEmissionVelocityInfo::SphericalEmissionVelocityInfo()
{
	m_04.setRange(0.0f, 0.0f);
}

// ??0CylindricalEmissionVelocityInfo@FXParticleSystem@@QAE@XZ @0x3A7489
// (Outward folds its default body here too; pin 5263.)
CylindricalEmissionVelocityInfo::CylindricalEmissionVelocityInfo()
{
	m_04.setRange(0.0f, 0.0f);
	m_10.setRange(0.0f, 0.0f);
}

// ??0OrthoEmissionVelocityInfo@FXParticleSystem@@QAE@XZ @0x3A6FD0
OrthoEmissionVelocityInfo::OrthoEmissionVelocityInfo()
{
	m_04.setRange(0.0f, 0.0f);
	m_10.setRange(0.0f, 0.0f);
	m_1C.setRange(0.0f, 0.0f);
}

// Retail 0x3A6D5F orders the flag store before the single vtable store:
// the flag is set by the volume base's own inline default (its vtable
// store dies against the derived one, as in the velocity defaults above),
// so the bool lives in the base here. The virtual destructor is only
// declared: it resolves to the folded 0x0049B47C family and supplies the
// unwinding behind the EH frame.

// ??0TerrainFireEmissionInfo@FXParticleSystem@@QAE@XZ @0x3A6D5F
TerrainFireEmissionInfo::TerrainFireEmissionInfo()
{
	m_08.setRange(0.0f, 0.0f);
	m_14.setRange(0.0f, 0.0f);
	m_20.setRange(0.0f, 0.0f);
	m_2C = 0.7f;
}

// DefaultPhysicsModuleInfo retail 0x0055EE5E, the out-of-line default the
// DefaultModuleTemplate<3> constructor calls. The base is Snapshot: the
// folded 0x0049B47C destructor stores its vtable 0x00BBB554, and the base's
// unwind state is the one EH state retail sets. The WorldBuilder twin
// (0x0141ED90) builds the +0x04 coordinate through its own inline default
// (which leaves nothing behind in the release build), the random variable
// through its zeroing default, then assigns +0x10, zeroes the coordinate,
// sets the range and clears the two flags.
// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ @0x55EE5E
__declspec(noinline) DefaultPhysicsModuleInfo::DefaultPhysicsModuleInfo()
{
	m_10 = 0.0f;
	m_04.zero();
	m_14.setRange(0.0f, 0.0f);
	m_20 = false;
	m_21 = false;
}

}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0OutwardEmissionVelocityInfo@FXParticleSystem@@QAE@XZ=??0CylindricalEmissionVelocityInfo@FXParticleSystem@@QAE@XZ")

// ??0SphericalEmissionVelocityInfo is a header inline elsewhere: another unit
// emits a select-any copy of it, so a strong definition here was a duplicate
// symbol in the linked build. This anchor only makes this unit emit its copy
// for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitEmissionInfoDefaultCtors@@YAXPAVSphericalEmissionVelocityInfo@FXParticleSystem@@@Z present-unmatched
void bfmeEmitEmissionInfoDefaultCtors(FXParticleSystem::SphericalEmissionVelocityInfo *p)
{
	p->SphericalEmissionVelocityInfo::SphericalEmissionVelocityInfo();
}
#pragma inline_depth()
