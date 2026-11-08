// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: DefaultModuleTemplate (ledger $02 / N=3) copy ctor
// Retail: CategoryModuleTemplate copy 0x0004CB7B, the null-preserving
// DefaultPhysicsModuleInfo copy 0x003A7736 on +8, then the class's own tables.

#include "../../../../Include/GameClient/DefaultModuleTemplate.h"

namespace FXParticleSystem
{

// ??0?$DefaultModuleTemplate@$02@FXParticleSystem@@QAE@ABV01@@Z
DefaultModuleTemplate<3>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
    : CategoryModuleTemplate<3>(that), DefaultPhysicsModuleInfo(that)
{
}

}
