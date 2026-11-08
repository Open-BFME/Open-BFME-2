// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: LightningDrawModuleTemplate copy ctor
// Retail: CategoryModuleTemplate<6> copy 0x0004CB7B, the null-preserving
// LightningDrawModuleInfo copy 0x003A7DCA on +8, then the class's own tables.

#include "../../../../Include/GameClient/LightningDrawModuleTemplate.h"

namespace FXParticleSystem
{

// ??0LightningDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
LightningDrawModuleTemplate::LightningDrawModuleTemplate(
	const LightningDrawModuleTemplate &that)
	: CategoryModuleTemplate<6>(that), LightningDrawModuleInfo(that)
{
}

}
