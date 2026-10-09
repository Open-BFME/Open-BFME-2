// cl: /O1 /arch:SSE /G7 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
#include <vector>
#include "ArmyPlacerWaypoints.h"
#include "ArmyPlacerRecords.h"
#include "ArmyPlacerRegionLookup.h"
// PairStorage owns these outlined methods under the native STL settings.
// The caller uses /EHs for its cleanup; emitting them here would produce
// different exception machinery in their allocation helpers.
extern template void _STL::vector<Rva0037F8AC>::reserve(unsigned);
extern template void _STL::vector<Rva0037F8AC>::push_back(const Rva0037F8AC&);
namespace _STL {
template<> __declspec(nothrow) void _Construct<Rva0037F8AC,Rva0037F8AC>(Rva0037F8AC*,const Rva0037F8AC&);
}
// WB F61D40 ArmyPlacer::GetSpawnPointInFarthestPair; native
// 0x00380014..0x00380200 RET16. Builds valid unordered region pairs,
// chooses the last pair with the highest squared distance, and supplies
// the first/second record for player 0/1. Other player values fail.
bool ArmyPlacer::GetSpawnPointInFarthestPair(Rva0037F90FInput *region,int player,
    Coord3D *spawn,Coord3D *gather) {
    if(unsigned(region->last-region->first)<=1) return false;
    _STL::vector<Rva0037F8AC> pairs;
    unsigned count=region->last-region->first;
    pairs.reserve((count*(count-1))/2);
    for(unsigned i=0;i<unsigned(region->last-region->first);++i) {
        Rva0037F90FInput *first=reinterpret_cast<Rva0037F90FInput*>(
            TheLivingWorldLogic->getLookup()->rva0020EAF6(region->first[i].regionId));
        if(!first) continue;
        for(unsigned j=i+1;j<unsigned(region->last-region->first);++j) {
            Rva0037F90FInput *second=reinterpret_cast<Rva0037F90FInput*>(
                TheLivingWorldLogic->getLookup()->rva0020EAF6(region->first[j].regionId));
            if(!second) continue;
            Rva0037F8AC pair;
            pair.rva0037F90F(this,first,second);
            if(pair.m_44) pairs.push_back(pair);
        }
    }
    float highestCost=0.f;
    int highestIndex=-1;
    for(unsigned i=0;i<pairs.size();++i) {
        if(pairs[i].m_40>=highestCost) {
            highestCost=pairs[i].m_40;
            highestIndex=i;
        }
    }
    if(highestIndex==-1) return false;
    const Rva0037F8AC &farthest=pairs[highestIndex];
    switch(player) {
    case 0:
        *spawn=*reinterpret_cast<const Coord3D*>(&farthest.m_00.m_04);
        *gather=*reinterpret_cast<const Coord3D*>(&farthest.m_00.m_10);
        return true;
    case 1:
        *spawn=*reinterpret_cast<const Coord3D*>(&farthest.m_20.m_04);
        *gather=*reinterpret_cast<const Coord3D*>(&farthest.m_20.m_10);
        return true;
    }
    return false;
}
