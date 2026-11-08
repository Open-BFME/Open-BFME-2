// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: DefaultModuleTemplate (ledger $01 / N=2) copy ctor
// Retail: CategoryModuleTemplate copy 0x0004CB7B, the null-preserving
// DefaultUpdateModuleInfo copy 0x003A789E on +8, then the class's own tables.

#include "../../../../Include/GameClient/DefaultModuleTemplate.h"

namespace FXParticleSystem
{

// ??0?$DefaultModuleTemplate@$01@FXParticleSystem@@QAE@ABV01@@Z
DefaultModuleTemplate<2>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
    : CategoryModuleTemplate<2>(that), DefaultUpdateModuleInfo(that)
{
}

}
