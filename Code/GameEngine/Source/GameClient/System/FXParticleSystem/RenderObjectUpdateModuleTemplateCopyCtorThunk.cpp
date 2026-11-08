// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: RenderObjectUpdateModuleTemplate copy ctor
// Retail: CategoryModuleTemplate<2> copy 0x0004CB7B, the null-preserving
// RenderObjectUpdateModuleInfo copy on +8, then the class's own tables.

#include "../../../../Include/GameClient/RenderObjectUpdateModuleTemplate.h"

namespace FXParticleSystem
{

// ??0RenderObjectUpdateModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
RenderObjectUpdateModuleTemplate::RenderObjectUpdateModuleTemplate(const RenderObjectUpdateModuleTemplate &that)
    : CategoryModuleTemplate<2>(that), RenderObjectUpdateModuleInfo(that)
{
}

}
