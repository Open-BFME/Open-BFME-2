// ?rva0052E6E6@Pathfinder@@QAE_NHHPAVPathfindCell@@PAVPolygonTrigger@@H_N@Z
// partial score=0.9556259426847662 date=2026-10-10
// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
typedef bool Bool;
typedef int Int;
class ICoord3D { public: Int x,y;unsigned char unused[4]; };
class PolygonTrigger { public: Bool pointInTrigger(const ICoord3D &); };
struct WallCellInfo { char prefix[0x28];ObjectID owner; };
struct Rva0052DFB1Arg;
class Rva00366500 { public: Bool rva00366500(Int);Bool rva0036652D(Int); };
class Rva0052E001 { public: Bool rva0052E001(Bool); };
Int Rva002E6E8AGet(Int);
enum CellKind{CellClear=0,CellObstacle=4,CellEdge=8};
class PathfindCell {
public:
    Bool rva0052DFB1(const Rva0052DFB1Arg *);
    Bool SetType_Dirty(Int);
    __forceinline Int type()const{return flags&15;}
    __forceinline Int layer()const{return(flags>>4)&63;}
    __forceinline ObjectID owner()const{return info?info->owner:INVALID_OBJECT_ID;}
    __forceinline void unpinch(){flags&=~0x10000U;}
    WallCellInfo *info;
    char prefix[8];
    unsigned flags;
};
class PathfindZoneManager { public: void MarkDirty(Int,Int); };
class Pathfinder {
public:
    Bool rva0052E6E6(Int,Int,PathfindCell *,PolygonTrigger *,Int,Bool);
private:
    char prefix[0x460];
    PathfindZoneManager zones;
    char gap[0x1be78-0x461];
    float layerHeights[65];
};
// Native0052E6E6..0052E914 RET24. The four-corner classification spine is
// carried from BFME1 575ba2b047 AIPathfind::classifyWallMapCell and ZH's
// classifyLayerMapCell. Target independently uses integer coordinates and
// owned PolygonTrigger wrapper38 at2E3A13 (only x/y read); the opaque third
// word is copied but never observed. Layer-height comparison at1BE78+4*layer,
// zones460, cell flags0C and owner-ID atinfo+28 are native facts.
// Original BFME2 method and the purpose of flag17 remain uncertain.
Bool Pathfinder::rva0052E6E6(Int x,Int y,PathfindCell *cell,PolygonTrigger *polygon,Int layer,Bool insert)
{
    ICoord3D topLeft,bottomRight,point;
    topLeft.y=y*10;
    bottomRight.y=topLeft.y+10;
    topLeft.x=x*10;
    bottomRight.x=topLeft.x+10;
    Int covered=0;
    if(polygon->pointInTrigger(topLeft))++covered;
    point=topLeft;
    point.y=bottomRight.y;
    if(polygon->pointInTrigger(point))++covered;
    if(polygon->pointInTrigger(bottomRight))++covered;
    point=topLeft;
    point.x=bottomRight.x;
    if(polygon->pointInTrigger(point))++covered;
    if(!covered)return false;
    if(insert){
        Int oldLayer=cell->layer();
        if(!(unsigned char)Rva002E6E8AGet(oldLayer)||layerHeights[oldLayer]<layerHeights[layer]){
            if(reinterpret_cast<Rva00366500 *>(cell)->rva00366500(layer))zones.MarkDirty(x,y);
        }
        if(cell->type()==4){
            Object *object=TheGameLogic->findObjectByID(cell->owner());
            if(object&&cell->rva0052DFB1(reinterpret_cast<const Rva0052DFB1Arg *>(object)))zones.MarkDirty(x,y);
        }
        Bool changed=reinterpret_cast<Rva0052E001 *>(cell)->rva0052E001(true);
        changed|=reinterpret_cast<Rva00366500 *>(cell)->rva0036652D(0);
        changed|=cell->SetType_Dirty(0);
        if(changed)zones.MarkDirty(x,y);
        cell->unpinch();
    }else{
        if(covered==4){
            Bool changed=reinterpret_cast<Rva00366500 *>(cell)->rva00366500(1);
            changed|=reinterpret_cast<Rva00366500 *>(cell)->rva0036652D(0);
            if(changed)zones.MarkDirty(x,y);
            if(cell->type()!=4&&cell->SetType_Dirty(0))zones.MarkDirty(x,y);
        }else if(cell->type()==8){
            reinterpret_cast<Rva00366500 *>(cell)->rva00366500(1);
            cell->SetType_Dirty(0);
            reinterpret_cast<Rva00366500 *>(cell)->rva0036652D(0);
            zones.MarkDirty(x,y);
        }
        if(reinterpret_cast<Rva0052E001 *>(cell)->rva0052E001(false))zones.MarkDirty(x,y);
    }
    return true;
}
