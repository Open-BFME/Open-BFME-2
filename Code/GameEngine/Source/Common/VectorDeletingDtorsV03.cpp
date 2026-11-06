// cl: /O1 /DNDEBUG /MD /EHsc
//
// Vector deleting destructors (??_E), batch V03: 75-byte bodies that, for
// an array delete (flag bit 1), run the eh vector destructor iterator
// (0x00629110) over the count stored before the array with the destructor's
// address and the element size, then free the block from its count word with
// operator delete[] (0x0002FD80); otherwise they call the destructor and free
// through operator delete (0x0002FD60). The element size is the class size.
// Each class's destructor is declared, not defined (pinned); the anchor below
// (no retail counterpart) news an array of each class so this TU emits the
// vector deleting destructor. Owners are opaque unless the destructor already
// carried a ledger name.
//
//   ??_E        dtor        size  vtable#slot
//   0x003A66B2  0x0049B47C  0x14  0x00C1BB30#0
//   0x003A6833  0x0049B47C  0x0C  0x00C1BB60#0
//   0x003A70D1  0x0049B47C  0x28  0x00C1BC00#0
//   0x003A72AC  0x0049B47C  0x10  0x00C1BC30#0
//   0x003A7532  0x0049B47C  0x1C  0x00C1BC90#0
//   0x003A795A  0x0049B47C  0x68  0x00C1BCE0#0

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
#include <new>

// Complete-destructor providers exist for this collector; unresolved owners
// remain byte-verified in the corresponding _Unresolved unit.

#include "../../Include/GameClient/BoxEmissionVolumeInfo.h"
namespace FXParticleSystem
{
}

#include "../../Include/GameClient/SphereEmissionVolumeInfo.h"
namespace FXParticleSystem
{
}

#include "../../Include/GameClient/OrthoEmissionVelocityInfo.h"
namespace FXParticleSystem
{
}

#include "../../Include/GameClient/SphericalEmissionVelocityInfo.h"
namespace FXParticleSystem
{
}

#include "../../Include/GameClient/CylindricalEmissionVelocityInfo.h"
namespace FXParticleSystem
{
}

namespace FXParticleSystem
{
class DefaultUpdateModuleInfo
{
public:
	DefaultUpdateModuleInfo();
	virtual ~DefaultUpdateModuleInfo();
private:
	char m_unmodelled_04[0x68 - 0x04];
};
}

namespace FXParticleSystem {
// Retail exports share size0x1C and vector destructor3A7532 with Cylindrical.
class OutwardEmissionVelocityInfo : public EmissionVelocityInfo {
public: OutwardEmissionVelocityInfo(); virtual ~OutwardEmissionVelocityInfo();
private: ::GameClientRandomVariable m_04; ::GameClientRandomVariable m_10;
};
}

// ?<bfmeVectorDeleteAnchorV03> absent-from-retail
void bfmeVectorDeleteAnchorV03()
{
	new FXParticleSystem::BoxEmissionVolumeInfo[2];
	new FXParticleSystem::SphereEmissionVolumeInfo[2];
	new FXParticleSystem::OrthoEmissionVelocityInfo[2];
	new FXParticleSystem::SphericalEmissionVelocityInfo[2];
	new FXParticleSystem::CylindricalEmissionVelocityInfo[2];
	new FXParticleSystem::OutwardEmissionVelocityInfo[2];
	new FXParticleSystem::DefaultUpdateModuleInfo[2];
}
