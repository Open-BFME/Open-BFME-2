// cl: /D_OPERATOR_NEW_DEFINED_ /O1 /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// Reference: Open-BFME-1 575ba2b04743f190f069805fbdc59936123c45da,
// game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp
// Get_Obj_Space_Bounding_Box, with the original GeneralsMD body as semantic guide.
// Target: full native RVA 0x00069BCC..0x00069C5F, 147 bytes including RET4.
// Base terrain primary table VA 0x00BC5E5C slot25 points to VA 0x00469BCC.
// Retail and WB0x758A10 agree on map37C0, dimensions8/C, heights37D8/DC.
// Uses the canonical BaseHeightMap.h class and WWMath AABoxClass::Init.
#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"
#define REFCOUNT_H
#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"
void BaseHeightMapRenderObjClass::Get_Obj_Space_Bounding_Box(AABoxClass &box) const
{
    int x=0, y=0;
    if (m_map)
    {
        x=m_map->getXExtent();
        y=m_map->getYExtent();
    }
    Vector3 minPt(0,0,m_minHeight);
    Vector3 maxPt((float)x*10.0f,(float)y*10.0f,m_maxHeight);
    MinMaxAABoxClass bounds(minPt,maxPt);
    box.Init(bounds);
}
