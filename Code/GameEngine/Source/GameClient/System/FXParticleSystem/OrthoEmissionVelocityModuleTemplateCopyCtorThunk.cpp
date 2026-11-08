// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: OrthoEmissionVelocityModuleTemplate copy ctor
// Retail: CategoryModuleTemplate<4> copy 0x0004CB7B, the null-preserving
// OrthoEmissionVelocityInfo copy on +8, then the class's own tables.

#include "../../../../Include/GameClient/OrthoEmissionVelocityModuleTemplate.h"

namespace FXParticleSystem
{

// ??0OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
OrthoEmissionVelocityModuleTemplate::OrthoEmissionVelocityModuleTemplate(const OrthoEmissionVelocityModuleTemplate &that)
    : CategoryModuleTemplate<4>(that), OrthoEmissionVelocityInfo(that)
{
}

}
