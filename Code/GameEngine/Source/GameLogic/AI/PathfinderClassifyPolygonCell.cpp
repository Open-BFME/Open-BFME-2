// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
typedef bool Bool;
typedef int Int;
#include "Code/Libraries/Include/Lib/ICoord3D.h"
#include "../../../Include/GameLogic/PolygonTrigger.h"
struct WallCellInfo 
{
 char prefix[0x28];
 ObjectID owner;
 
}
;
struct Rva0052DFB1Arg;
#include "../../../Include/GameLogic/Rva00366500.h"
#include "../../../Include/GameLogic/Rva0052E001.h"
Int Rva002E6E8AGet(Int);
enum CellKind
{
 CellClear=0,CellObstacle=4,CellEdge=8
}
;
#include "Code/GameEngine/Include/GameLogic/PathfindCell.h"
static __forceinline ObjectID cellOwner(const PathfindCell *cell)
{
 WallCellInfo *info=(WallCellInfo *)cell->m_info;
 return info?info->owner:INVALID_OBJECT_ID;
}
static __forceinline void cellUnpinch(PathfindCell *cell)
{
 cell->m_0C&=~0x10000U;
}
#include "Code/GameEngine/Include/GameLogic/PathfindZoneManager.h"
class Pathfinder 
{
 public:
 Bool rva0052E6E6(Int,Int,PathfindCell *,PolygonTrigger *,Int,Bool);
 private:
 char prefix[0x460];
 PathfindZoneManager zones;
 // zones (0x1BA54 bytes) ends at +0x1BEB4; retail 0x0052E7B3/0x0052E7BC read
 // this+0x1BE78+4*layer, i.e. heights[layer-17] below.
 char pad1BEB4[0x1beb8-0x1beb4];
 Int heightCount;
 float heights[64];
 
}
;
// Native0052E6E6..0052E914 RET24. The four-corner classification spine is
// carried from BFME1 575ba2b047 AIPathfind::classifyWallMapCell and ZH's
// classifyLayerMapCell. Target independently uses integer coordinates and
// owned PolygonTrigger wrapper38 at2E3A13 (only x/y read); the opaque third
// word is copied but never observed. Layer-height comparison at1BE78+4*layer,
// zones460, cell flags0C and owner-ID atinfo+28 are native facts.
// Original BFME2 method and the purpose of flag17 remain uncertain.
// The covered==4 arm ORs the two bitfield setters in one condition as the WB
// twin does; a separate flag variable makes cl keep a zero register live into
// the following SetType_Dirty / rva0052E001 calls (push edi for push 0).
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
 if(insert)
 {
  Int oldLayer=cell->getLayer();
  if(!(unsigned char)Rva002E6E8AGet(oldLayer)||heights[oldLayer-17]<heights[layer-17])
  {
   if(reinterpret_cast<Rva00366500 *>(cell)->rva00366500(layer))zones.MarkDirty(x,y);
   
  }
  if(cell->getType()==4)
  {
   Object *object=TheGameLogic->findObjectByID(cellOwner(cell));
   if(object&&cell->rva0052DFB1(reinterpret_cast<const Rva0052DFB1Arg *>(object)))zones.MarkDirty(x,y);
   
  }
  unsigned char changed=reinterpret_cast<Rva0052E001 *>(cell)->rva0052E001(true);
  unsigned char changed2=reinterpret_cast<Rva00366500 *>(cell)->rva0036652D(0);
  changed=(unsigned char)(*(volatile unsigned char*)&changed|(unsigned char)changed2);
  *(volatile unsigned char*)&changed = (unsigned char)changed;
  changed|=(unsigned char)cell->SetType_Dirty(0);
  _ReadWriteBarrier();
  if(changed)zones.MarkDirty(x,y);
  cellUnpinch(cell);
  
 }
 else
 {
  if(covered==4)
  {
   if(reinterpret_cast<Rva00366500 *>(cell)->rva00366500(1)|reinterpret_cast<Rva00366500 *>(cell)->rva0036652D(0))zones.MarkDirty(x,y);
   if(cell->getType()!=4&&cell->SetType_Dirty(0))zones.MarkDirty(x,y);
   
  }
  else if(cell->getType()==8)
  {
   reinterpret_cast<Rva00366500 *>(cell)->rva00366500(1);
   cell->SetType_Dirty(0);
   reinterpret_cast<Rva00366500 *>(cell)->rva0036652D(0);
   zones.MarkDirty(x,y);
   
  }
  if(reinterpret_cast<Rva0052E001 *>(cell)->rva0052E001(false))zones.MarkDirty(x,y);
  
 }
 return true;
 
}
