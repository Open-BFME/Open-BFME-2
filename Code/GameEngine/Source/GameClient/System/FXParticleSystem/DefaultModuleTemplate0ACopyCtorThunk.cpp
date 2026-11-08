// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: DefaultModuleTemplate (ledger $0A@ / N=0) copy ctor
// Retail: CategoryModuleTemplate copy 0x0004CB7B, the null-preserving
// DefaultColorModuleInfo copy 0x003A62D9 on +8, then the class's own tables.

#include "../../../../Include/GameClient/DefaultModuleTemplate.h"

namespace FXParticleSystem
{

// ??0?$DefaultModuleTemplate@$0A@@FXParticleSystem@@QAE@ABV01@@Z
DefaultModuleTemplate<0>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
    : CategoryModuleTemplate<0>(that), DefaultColorModuleInfo(that)
{
}

}
