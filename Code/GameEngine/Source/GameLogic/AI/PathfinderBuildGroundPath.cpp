// ?BuildGroundPath@Pathfinder@@QAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z
// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
//
// Pathfinder::BuildGroundPath: retail 0x002EF908..0x002EFB3A (562 bytes;
// ret 0x10). WorldBuilder twin 0x00D4F370 (pathfinder.cpp asserts at lines
// 7315..7316) names it; Zero Hour's buildGroundPath supplies the spine:
// allocate a Path (operator new 0x28 and the rowed Path::Path 0x00363DC8),
// prepend the cells (rowed PrependCells 0x002EE1C7) and ground-optimize it
// with the path diameter (rowed Path::optimizeGroundPath). BFME 2 then smooths each
// interior corner as the WB twin does: the sum of the incoming and outgoing
// segments is normalized (rowed Coord3D::Normalize 0x00005A70) and scaled
// by twice TheAI's AI data +0xA0 value; the point is pushed sideways by the
// sign of the 2D cross product and adjusted by the rowed
// AdjustGroundPathPosition 0x002EDFBD and the node moves half way there.
// The WB twin's debug-only overlay drawing and SetDebugPath are absent from
// retail. Coordinates go through a TU-local Coord3D adapter with member-wise
// copies as the WB twin's Coord3D methods; the halving is written per
// component with the y and z halves held in the direction as retail's
// register use shows.
#include "Lib/Coord3D.h"
typedef int Int;typedef bool Bool;
enum PathfindLayerEnum { PATHFIND_LAYER_UNKNOWN=0, PATHFIND_LAYER_GROUND=1 };
struct PathCollisionNode;
struct PathCollisionInfo {
    char prefix[0x14]; PathCollisionNode *occupants;
    char gap18[8]; PathCollisionNode *goals,*reservations;
};
#include "../../../Include/GameLogic/PathfindCell.h"
static __forceinline Bool cellBit(const PathfindCell *cell, int bitIndex) { return ((cell->m_0C>>bitIndex)&1)!=0; }
static __forceinline PathCollisionInfo *cellInfo(const PathfindCell *cell) { return (PathCollisionInfo *)cell->m_info; }
static __forceinline Bool cellHasOccupants(const PathfindCell *cell) { return cellInfo(cell) ? cellInfo(cell)->occupants!=0 : false; }
static __forceinline Bool cellHasGoals(const PathfindCell *cell) { return cellInfo(cell) ? cellInfo(cell)->goals!=0 : false; }
static __forceinline Bool cellHasReservations(const PathfindCell *cell) { return cellInfo(cell) ? cellInfo(cell)->reservations!=0 : false; }
class Pathfinder;
struct IRegion2D;
class Xfer;
#include "../../../Include/GameLogic/PathfindLayer.h"
#include "../../../Include/GameLogic/TAiData.h"
#include "../../../Include/GameLogic/AI.h"
struct PathGroundNode {PathGroundNode *next,*previous,*nextOptimized;Coord3D pos;int layer;};
class Path {public:Path();void optimizeGroundPath(Int);void *vtable;PathGroundNode *first,*last;char padC[0x28-0xC];};
#include "../../../Include/GameLogic/AIPathfind.h"
static __forceinline void copyCoord3D(Coord3D *dest,const Coord3D *src){dest->x=src->x;dest->y=src->y;dest->z=src->z;}
static __forceinline void subCoord3D(Coord3D *dest,const Coord3D *src){dest->x-=src->x;dest->y-=src->y;dest->z-=src->z;}
struct PathGroundCoord : Coord3D {
PathGroundCoord() {}
PathGroundCoord(const Coord3D &sourceCoord) { x=sourceCoord.x; y=sourceCoord.y; z=sourceCoord.z; }
PathGroundCoord(const PathGroundCoord &pathGroundCoord) { x=pathGroundCoord.x; y=pathGroundCoord.y; z=pathGroundCoord.z; }
void Sub(const Coord3D *subtractCoord) { x-=subtractCoord->x; y-=subtractCoord->y; z-=subtractCoord->z; }
void Add(const Coord3D *addCoord) { x+=addCoord->x; y+=addCoord->y; z+=addCoord->z; }
void Set(const Coord3D &v) { Coord3D::operator=(v); }
};
Path *Pathfinder::BuildGroundPath(const Coord3D *fromPos, PathfindCell *goalCell, Bool center, Int pathDiameter)
{
Path *path = new Path;
PrependCells(path, fromPos, goalCell, center);
path->optimizeGroundPath(pathDiameter);
Bool havePrev = false;
PathGroundCoord prevPos;
for (PathGroundNode *node = path->first; node; node = node->nextOptimized) {
PathGroundNode *next = node->nextOptimized;
if (!next) break;
PathGroundCoord curPos(node->pos);
if (havePrev) {
PathGroundCoord v1(node->pos);
v1.Sub(&prevPos);
PathGroundCoord v2(next->pos);
v2.Sub(&node->pos);
float cross = v1.x * v2.y - v1.y * v2.x;
Coord3D dir;
copyCoord3D(&dir, &v1);
dir.x += v2.x;
dir.y += v2.y;
dir.z = 0;
dir.Normalize();
float cornerOffsetDistance = 2.0f * TheAI->getAiData()->m_formationColumnWidth;
dir.x *= cornerOffsetDistance;
dir.y *= cornerOffsetDistance;
PathGroundCoord newPos(node->pos);
if (cross < 0) {
newPos.x += -dir.y;
newPos.y += dir.x;
} else {
newPos.x += dir.y;
newPos.y += -dir.x;
}
AdjustGroundPathPosition(&node->pos, &newPos);
dir = newPos;
subCoord3D(&dir, &node->pos);
newPos.Set(node->pos);
newPos.x += dir.x * 0.5f;
dir.y *= 0.5f;
newPos.y += dir.y;
dir.z *= 0.5f;
newPos.z += dir.z;
node->pos = newPos;
}
havePrev = true;
prevPos = curPos;
}
return path;
}

// The native debug draw call sites push coord/float/duration/12-byte color;
// the layer reset call supplies only ECX. Both release bodies fold to the
// existing single RET at B3FD0. Separate full C++ providers preserve their ABIs.
struct PathfinderDebugColor { float red,green,blue; };
void Rva000B3FD0PathDebug(const Coord3D *,float,Int,PathfinderDebugColor);


struct PathfinderDebugWaypoint {
    char prefix[0xc]; Coord3D position;
    char gap18[4]; PathfinderDebugWaypoint *next;
    char gap20[0x44-0x20]; int word44;
};
template<int N> class PathfinderNativeSlots : public PathfinderNativeSlots<N-1> { public: virtual void unusedSlot(PathfinderNativeSlots<N> *); };
template<> class PathfinderNativeSlots<0> {};
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
class PathfinderTerrainWaypoints : public PathfinderNativeSlots<33> { public: virtual PathfinderDebugWaypoint *slot84(); };
class Rva0052DB4D
{
public:
	Bool rva0052DB4D(Int);
};
class Rva002E6ECA { public: int get() const; };
float Rva002E7BB8Get();
#include "../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
extern int BfmeLogicFramesPerSecond;
// Pathfinder debug-icon pass, retail 0x002EFB3A..0x002F00C9 (1423 bytes of
// code plus its 32-byte switch jump table; ret). Zero Hour's
// Pathfinder::doDebugIcons supplies the grid/color/display semantics; WB
// D54500 corroborates BFME2's waypoint mode and cell overlay branches but
// carries no name, so the address name stays. Native kind/layer masks,
// dimensions and color values establish every delta. The cell flag tests
// are Bool getters over the packed word at +0xC (retail shifts and tests the
// low bit after reloading the word); the connect-layer compare is a masked
// word compare, and the info tests are conditional-value getters.
void Pathfinder::rva002EFB3A()
{
    Int x,y;
    const PathfindCell *cell;
    Int duration=BfmeLogicFramesPerSecond*3;
    Int mode=TheWritableGlobalData->field09B8;
    if (mode==3 || mode==2 || mode==7 || mode==5) {
        PathfinderDebugColor color;
        color.blue=0; color.green=0; color.red=0;
        Rva000B3FD0PathDebug(0,0,0,color);
        if (TheWritableGlobalData->field09B8==7) {
            for (PathfinderDebugWaypoint *point=((PathfinderTerrainWaypoints *)TheTerrainLogic)->slot84();point;point=point->next) {
                color.blue=0; color.green=0; color.red=0;
                if ((unsigned char)((const Rva002E6ECA *)point)->get()) color.green=1;
                else if (point->word44!=0) color.blue=1;
                else color.red=1;
                Rva000B3FD0PathDebug(&point->position,5.0f,BfmeLogicFramesPerSecond*3,color);
            }
        } else {
            Coord3D topLeftCorner;
            Bool showCells=TheWritableGlobalData->field09B8==3 || TheWritableGlobalData->field09B8==5;
            for (Int layer=0;layer<16;++layer) m_layers[layer].rva000B3FD0();
            for (x=0;x<m_extent.hi.x;++x) {
                for (y=0;y<m_extent.hi.y;++y) {
                    topLeftCorner.x=(float)x*10.0f;
                    topLeftCorner.y=(float)y*10.0f;
                    color.blue=0; color.green=0; color.red=0;
                    Bool empty=true;
                    cell=TheAI->m_pathfinder->getCell(PATHFIND_LAYER_GROUND,x,y);
                    if (cell) {
                        switch (cell->getType()) {
                        case 2: color.red=1; empty=false; break;
                        case 6: color.red=1; color.blue=1; empty=false; break;
                        case 5: color.green=1; empty=false; break;
                        case 1: color.blue=1; color.green=0.3f; color.red=0.3f; empty=false; break;
                        case 7:
                            color.blue=0.8f; empty=false;
                            if (cellBit(cell,23)) color.green=0.2f;
                            break;
                        case 8:
                            color.blue=Rva002E7BB8Get(); color.red=Rva002E7BB8Get(); color.green=Rva002E7BB8Get(); empty=false;
                            break;
                        case 3: color.red=1; color.green=0.5f; empty=false; break;
                        case 4: color.green=1; color.red=1; empty=false; break;
                        default:
                            if (cellBit(cell,16)) { color.green=0.7f; color.blue=0.7f; empty=false; }
                            if (cell->getLayer()==16) { color.blue=0.5f; empty=false; }
                            else if (cell->getLayer()!=1 || (cell->m_0C&0xfc00)==0x4000) { color.blue=0.7f; color.red=0.7f; empty=false; }
                            break;
                        }
                    }
                    if (empty && cellBit(cell,18)) { color.red=0.3f; empty=false; }
                    Coord3D position;
                    position.x=topLeftCorner.x+5.0f; position.y=topLeftCorner.y+5.0f; position.z=0;
                    if (cell->getLayer()!=1) position.z=GetWallHeight((PathfindLayerEnum)cell->getLayer(),&position,0);
                    else position.z=TheTerrainLogic->getGroundHeight(position.x,position.y,0);
                    if (showCells) {
                        empty=true;
                        color.blue=0; color.green=0; color.red=0;
                        if (cell) {
                        if (cellHasOccupants(cell)) { empty=false; color.red=1; }
                        if (cellHasGoals(cell)) { empty=false; color.green=1; }
                        if (cellHasReservations(cell)) { empty=false; color.blue=1; }
                        if (((Rva0052DB4D *)cell)->rva0052DB4D(0)) { empty=false; color.red=0; color.blue=1; color.green=1; }
                        if (empty && cellBit(cell,17)) { empty=false; color.blue=0; color.green=0; color.red=0; }
                        }
                    }
                    if (!empty) {
                        Int remaining=duration-1;
                        Rva000B3FD0PathDebug(&position,8.0f,remaining,color);
                        if (((cell->m_0C>>10)&63)!=0) {
                            color.blue=1; color.green=1; color.red=1;
                            Rva000B3FD0PathDebug(&position,3.0f,remaining,color);
                        }
                    }
                    if (cell && cellBit(cell,17)) {
                        color.blue=0; color.green=0; color.red=0;
                        Rva000B3FD0PathDebug(&position,3.0f,duration-1,color);
                    }
                    if (cell && (Int)((cell->m_0C>>19)&3)>0) {
                        color.red=(float)(Int)((cell->m_0C>>19)&3)*0.5f; color.blue=0; color.green=0;
                        Rva000B3FD0PathDebug(&position,1.5f,duration-1,color);
                    }
                    if (cell && cellBit(cell,21)) {
                        color.red=0; color.green=0.5f; color.blue=0;
                        Rva000B3FD0PathDebug(&position,10.0f,duration-1,color);
                    }
                }
            }
        }
    }
}
