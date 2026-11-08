// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: DefaultModuleTemplate (ledger $00 / N=1) copy ctor
// Retail: CategoryModuleTemplate copy 0x0004CB7B, the null-preserving
// DefaultAlphaModuleInfo copy 0x003A616F on +8, then the class's own tables.

#include "../../../../Include/GameClient/DefaultModuleTemplate.h"

namespace FXParticleSystem
{

// ??0?$DefaultModuleTemplate@$00@FXParticleSystem@@QAE@ABV01@@Z
DefaultModuleTemplate<1>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
    : CategoryModuleTemplate<1>(that), DefaultAlphaModuleInfo(that)
{
}

}
