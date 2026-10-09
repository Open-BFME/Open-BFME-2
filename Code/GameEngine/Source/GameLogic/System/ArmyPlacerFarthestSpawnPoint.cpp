// cl: /O1 /arch:SSE /G7 /MD /ICode/Libraries/Include/Lib
#include "ArmyPlacerWaypoints.h"
#include "ArmyPlacerRecords.h"
#include "ArmyPlacerRegionLookup.h"

// WB ArmyPlacer::GetFarthestSpawnPointFromPlayerStart and native
// 0x0037F985..0x0037FAC6 RET16 establish identity and the full boundary.
// Record layouts come from the verified initializer/query/pair providers;
// region +0x12c and adjacent entries +0x1a8/+0x1ac are target accesses.
bool ArmyPlacer::GetFarthestSpawnPointFromPlayerStart(Rva0037F90FInput *region,
    int player, Coord3D *spawn, Coord3D *gather) {
    Rva0037F4EA start;
    start.rva0037F4EA(region->field_12c);
    start.rva0037F6EA(this,player);
    if(!start.m_1c) return false;
    if(unsigned(region->last-region->first)<1) return false;
    float highestCost=0.f;
    Rva0037F4EA farthest;
    farthest.rva0037F4EA(-1);
    for(unsigned i=0;i<unsigned(region->last-region->first);++i) {
        Rva0037F90FInput *otherRegion=reinterpret_cast<Rva0037F90FInput*>(
            TheLivingWorldLogic->getLookup()->rva0020EAF6(region->first[i].regionId));
        if(!otherRegion) continue;
        {
            Rva0037F4EA other;
            other.rva0037F4EA(otherRegion->field_12c);
            other.rva0037F87A(this);
            Rva0037F8AC pair;
            pair.rva0037F950(this,reinterpret_cast<Rva0037F51A*>(&start),
                reinterpret_cast<Rva0037F51A*>(&other));
            if(pair.m_44 && pair.m_40>=highestCost) {
                highestCost=pair.m_40;
                farthest=pair.m_20;
            }
        }
    }
    if(highestCost<=0.f) return false;
    *spawn=*reinterpret_cast<Coord3D*>(&farthest.m_04);
    *gather=*reinterpret_cast<Coord3D*>(&farthest.m_10);
    return true;
}
