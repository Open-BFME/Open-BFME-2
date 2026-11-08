// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: QuadDrawModuleTemplate copy ctor
// Retail: CategoryModuleTemplate<6> copy 0x0004CB7B, the null-preserving
// QuadDrawModuleInfo copy on +8, then the class's own tables.

#include "../../../../Include/GameClient/QuadDrawModuleTemplate.h"

namespace FXParticleSystem
{

// ??0QuadDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
QuadDrawModuleTemplate::QuadDrawModuleTemplate(const QuadDrawModuleTemplate &that)
    : CategoryModuleTemplate<6>(that), QuadDrawModuleInfo(that)
{
}

}
