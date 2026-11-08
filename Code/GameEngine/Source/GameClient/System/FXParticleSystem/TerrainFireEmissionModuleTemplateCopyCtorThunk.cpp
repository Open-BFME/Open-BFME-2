// cl: /DNDEBUG /MD /GX- /Ob2 /Ireference/shims/moduledata

// Open-BFME5: TerrainFireEmissionModuleTemplate copy ctor
// Retail: CategoryModuleTemplate<5> copy 0x0004CB7B, the null-preserving
// TerrainFireEmissionInfo copy on +8, then the class's own tables.

#include "../../../../Include/GameClient/TerrainFireEmissionModuleTemplate.h"

namespace FXParticleSystem
{

// ??0TerrainFireEmissionModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
TerrainFireEmissionModuleTemplate::TerrainFireEmissionModuleTemplate(const TerrainFireEmissionModuleTemplate &that)
    : CategoryModuleTemplate<5>(that), TerrainFireEmissionInfo(that)
{
}

}
