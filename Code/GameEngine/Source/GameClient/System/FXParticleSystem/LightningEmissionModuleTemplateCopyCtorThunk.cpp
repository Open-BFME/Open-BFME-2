// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: LightningEmissionModuleTemplate copy ctor
// Retail: CategoryModuleTemplate<5> copy 0x0004CB7B, the null-preserving
// LightningEmissionInfo copy 0x003A6AF5 on +8, then the class's own tables.

#include "../../../../Include/GameClient/LightningEmissionModuleTemplate.h"

namespace FXParticleSystem
{

// ??0LightningEmissionModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
LightningEmissionModuleTemplate::LightningEmissionModuleTemplate(
	const LightningEmissionModuleTemplate &that)
	: CategoryModuleTemplate<5>(that), LightningEmissionInfo(that)
{
}

}
