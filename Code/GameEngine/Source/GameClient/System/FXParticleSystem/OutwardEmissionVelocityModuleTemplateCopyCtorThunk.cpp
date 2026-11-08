// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: OutwardEmissionVelocityModuleTemplate copy ctor
// Retail: CategoryModuleTemplate<4> copy 0x0004CB7B, the null-preserving
// OutwardEmissionVelocityInfo copy on +8, then the class's own tables.

#include "../../../../Include/GameClient/OutwardEmissionVelocityModuleTemplate.h"

namespace FXParticleSystem
{

// ??0OutwardEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
OutwardEmissionVelocityModuleTemplate::OutwardEmissionVelocityModuleTemplate(const OutwardEmissionVelocityModuleTemplate &that)
    : CategoryModuleTemplate<4>(that), OutwardEmissionVelocityInfo(that)
{
}

}
