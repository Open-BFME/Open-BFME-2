// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: StreakDrawModuleTemplate copy ctor
// Retail: CategoryModuleTemplate<6> copy 0x0004CB7B, the null-preserving
// StreakDrawModuleInfo copy on +8, then the class's own tables.

#include "../../../../Include/GameClient/StreakDrawModuleTemplate.h"

namespace FXParticleSystem
{

// ??0StreakDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
StreakDrawModuleTemplate::StreakDrawModuleTemplate(const StreakDrawModuleTemplate &that)
    : CategoryModuleTemplate<6>(that), StreakDrawModuleInfo(that)
{
}

}
