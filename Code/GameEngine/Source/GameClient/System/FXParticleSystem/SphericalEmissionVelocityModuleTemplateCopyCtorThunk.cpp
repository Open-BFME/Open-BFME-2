// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: SphericalEmissionVelocityModuleTemplate copy ctor
// Retail: CategoryModuleTemplate<4> copy 0x0004CB7B, the null-preserving
// SphericalEmissionVelocityInfo copy on +8, then the class's own tables.

#include "../../../../Include/GameClient/SphericalEmissionVelocityModuleTemplate.h"

namespace FXParticleSystem
{

// ??0SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
SphericalEmissionVelocityModuleTemplate::SphericalEmissionVelocityModuleTemplate(const SphericalEmissionVelocityModuleTemplate &that)
    : CategoryModuleTemplate<4>(that), SphericalEmissionVelocityInfo(that)
{
}

}
