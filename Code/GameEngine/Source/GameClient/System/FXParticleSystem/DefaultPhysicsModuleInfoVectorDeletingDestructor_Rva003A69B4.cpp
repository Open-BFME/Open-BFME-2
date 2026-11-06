// Target DefaultPhysics RVA0x003A77A7; array stride0x24; table VA0x00C1BCB0 slot0.
// Historical filename reflects the disproven0x003A69B4/stride0x20 assignment.
// cl: -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/System/FXParticleSystem
// Historical BFME1 donor RVA 0x005D7F70. The wrapper's scalar-destructor operand is ILT
// 0x00042F28, which routes directly to the matched destructor at 0x005D7E90.
#include <new>

#include "../../../../Include/GameClient/DefaultPhysicsModuleInfo.h"

namespace FXParticleSystem
{

DefaultPhysicsModuleInfo *MakeDefaultPhysicsModuleInfoArray()
{
    return new DefaultPhysicsModuleInfo[2];
}

void DeleteDefaultPhysicsModuleInfoArray(DefaultPhysicsModuleInfo *array)
{
    delete[] array;
}
}
