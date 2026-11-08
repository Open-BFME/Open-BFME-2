// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: CylindricalEmissionVelocityModuleTemplate copy ctor
// Retail: CategoryModuleTemplate<4> copy 0x0004CB7B, the null-preserving
// CylindricalEmissionVelocityInfo copy on +8, then the class's own tables.

#include "../../../../Include/GameClient/CylindricalEmissionVelocityModuleTemplate.h"

namespace FXParticleSystem
{

// ??0CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
CylindricalEmissionVelocityModuleTemplate::CylindricalEmissionVelocityModuleTemplate(const CylindricalEmissionVelocityModuleTemplate &that)
    : CategoryModuleTemplate<4>(that), CylindricalEmissionVelocityInfo(that)
{
}

}
