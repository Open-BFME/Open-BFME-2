// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: DefaultModuleTemplate (ledger $05 / N=6) copy ctor
// Retail: CategoryModuleTemplate copy 0x0004CB7B, the null-preserving
// DefaultDrawModuleInfo copy 0x003A643C on +8, then the class's own tables.

#include "../../../../Include/GameClient/DefaultModuleTemplate.h"

namespace FXParticleSystem
{

// ??0?$DefaultModuleTemplate@$05@FXParticleSystem@@QAE@ABV01@@Z
DefaultModuleTemplate<6>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
    : CategoryModuleTemplate<6>(that), DefaultDrawModuleInfo(that)
{
}

}
