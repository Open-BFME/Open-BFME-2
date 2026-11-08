// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Split from PathfindLayerReset_~PathfindLayer.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Split from PathfindLayerReset.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Reference: Open-BFME-1 968ca36c3265b295297e6aed45a6bd89ffe59c40,
// game/GameEngine/Source/GameLogic/AI/PathfindLayerResetFull.cpp.
// Target identity: the adjacent verified PathfindLayer::getCell and
// DoBoundsOverlap bodies share cells +4, dimensions +8/+C and triggers +38.
// Target adaptation: bridge +34, triggers +38, trigger ID +3C; +2C becomes
// -1 and +30 is retained. The original name of this 66-byte wrapper and its
// 105-byte allocation-clear helper remain unknown.

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Region2D.h"
// Keep math.h's unused out-of-line floorf copy local.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>

inline float Coord3D::length() const { return (float)sqrt(x*x+y*y+z*z); }
inline void Coord3D::normalize() { float len=length(); if(len!=0.0f){float scale=1.0f/len;x*=scale;y*=scale;z*=scale;} }
inline float Coord3D::GetLengthSqrd() const { float x_value=x,y_value=y,z_value=z; return x_value*x_value+y_value*y_value+z_value*z_value; }

template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include <new>

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

// The primitive virtual order is measured by the rowed Common/System/Xfer.cpp
// providers: ICoord2D slot 19, int slot 31, bool slot 36. Version1 is the
// existing 23-byte provider at 0x000053EE. Other entries are ABI placeholders.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/GameLogic/PathfindCell.h"

// Native vslot zero is called with flags zero; its returned pointer is
// passed to the rowed global operator delete. Only that ABI is asserted.
class Rva00366DECVirtual
{
public:
	virtual void *slot0(unsigned int flags);
};

#include "../../../Include/GameLogic/PathfindLayer.h"




// Native 0x00366B77..0x00366CEA, RET0. WB F29A70 names
// PathfindLayer::ClassifyWallCells and carries the same corner tests and
// reset/type classification. Target cell zone +8 and layer/zone flags +C
// are read from native stores and the already verified setter providers.
// Native tests nonzero in the branch reached when the count is not positive.
// Bitfield setter providers are already verified under their ledger owner.
class Rva00366500 { public: bool rva00366500(int);bool rva0036652D(int);};
// Native 00366CEA..00366DEC RET16; WB F29DE0 names ConnectsZones.
// BFME1 clean source supplies the zone-walk semantics. Native accesses prove
// cells4, dimensions8/C, destroyed30, zone flags10..15, and LocomotorSet10/15.
// The scheduling fence preserves the native loop-index load before cell-base load.
enum PathfindLayerEnum{LAYER_INVALID=-1,LAYER_GROUND=1,LAYER_FIRST_BRIDGE=16};
int isGroundOrBridgeLayer(int);
#include "../../../Include/GameLogic/LocomotorSet.h"
#include "../../../Include/GameLogic/PathfindZoneManager.h"
#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;


// Native 0x00366E2E..0x00367369, RET 0. ZH AIPathfind.cpp PathfindLayer::classifyCells
// with classifyLayerMapCell inlined; the endpoint conversions are ZH's
// REAL_TO_INT_FLOOR spelled with the CRT floorf (BFME uses the floor import).
class Rva0027C36A 
{
 public: Rva0027C36A();
 Rva0027C36A &operator=(const Rva0027C36A&);
 Coord3D from,to;
 unsigned char rest[0xa8-24];
 
}
;
class Bridge 
{
 public: bool isPointOnBridge(const Coord3D*);
 bool isCellOnSide(const Region2D*);
 bool isCellOnEnd(const Region2D*);
 bool isCellEntryPoint(const Region2D*,float*);
 float getBridgeHeight(const Coord3D*,Coord3D*);
 unsigned char prefix[12];
 Rva0027C36A info;
 
}
;
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
// ZH BaseType.h fast_float2long_round, preserved for the proven x87
// conversion blocker: C++ casts call _ftol2 and /QIfist rejects /arch:SSE.
// Native endpoint conversions use this exact fld/fistp rounding primitive.
__forceinline long fast_float2long_round(float f)

{
 long i;
 __asm 
 {
  fld [f]
  fistp [i]
  
 }
 return i;
 
}
void PathfindLayer::ClassifyBridgeCells()

{
 m_startCell.x=-1;
 m_startCell.y=-1;
 m_endCell.x=-1;
 m_endCell.y=-1;
 for(int x=0;x<m_width;++x) 
 {
  for(int y=0;y<m_height;++y) 
  {
   PathfindCell *cell=&m_layerCells[x][y];
   reinterpret_cast<Rva00366500*>(cell)->rva0036652D(0);
   reinterpret_cast<Rva00366500*>(cell)->rva00366500(m_layer);
   int worldX=x+m_xOrigin,worldY=y+m_yOrigin;
   Coord3D lo,hi,point;
   lo.y=worldY*10.0f;
   hi.y=lo.y+10.0f;
   lo.x=worldX*10.0f;
   hi.x=lo.x+10.0f;
   int inside=0;
   if(m_bridge->isPointOnBridge(&lo))++inside;
   point=lo;
   point.y=hi.y;
   if(m_bridge->isPointOnBridge(&point))++inside;
   if(m_bridge->isPointOnBridge(&hi))++inside;
   point=lo;
   point.x=hi.x;
   if(m_bridge->isPointOnBridge(&point))++inside;
   cell->rva0052DED3();
   reinterpret_cast<Rva00366500*>(cell)->rva00366500(m_layer);
   cell->SetType_Dirty(5);
   if(inside==4)cell->SetType_Dirty(0);
   else 
   {
    if(inside!=0)cell->SetType_Dirty(6);
    Region2D region;
    region.lo.x=lo.x;
    region.lo.y=lo.y;
    region.hi.x=hi.x;
    region.hi.y=hi.y;
    if(m_bridge->isCellOnSide(&region))cell->SetType_Dirty(6);
    else 
    {
     if(m_bridge->isCellOnEnd(&region))cell->SetType_Dirty(0);
     float height;
     if(m_bridge->isCellEntryPoint(&region,&height)) 
     {
      cell->SetType_Dirty(0);
      reinterpret_cast<Rva00366500*>(cell)->rva0036652D(1);
      PathfindCell *ground=TheAI->m_pathfinder->getCell(LAYER_GROUND,worldX,worldY);
      if((reinterpret_cast<Rva00366500*>(ground)->rva0036652D((cell->m_0C>>4)&0x3f)))
      reinterpret_cast<PathfindZoneManager*>(reinterpret_cast<char*>(TheAI->m_pathfinder)+0x460)->MarkDirty(worldX,worldY);
      
     }
     
    }
    
   }
   Coord3D center;
   center.z=lo.z;
   center.x=lo.x+5.0f;
   center.y=lo.y+5.0f;
   if((cell->m_0C&15)!=5 && ((cell->m_0C>>10)&0x3f)!=1) 
   {
    float height=TheTerrainLogic->getLayerHeight(center.x,center.y,(PathfindLayerEnum)1,0,true)+10.0f;
    if(height>m_bridge->getBridgeHeight(&center,0)) 
    {
     PathfindCell *ground=TheAI->m_pathfinder->getCell(LAYER_GROUND,worldX,worldY);
     if((ground->m_0C&15)!=4 && ground->SetType_Dirty(6))
     reinterpret_cast<PathfindZoneManager*>(reinterpret_cast<char*>(TheAI->m_pathfinder)+0x460)->MarkDirty(worldX,worldY);
     
    }
    
   }
   
  }
  Rva0027C36A info;
  info=m_bridge->info;
  Coord3D direction;
  direction.x=__vref(info.to.x)-info.from.x;
  direction.y=__vref(info.to.y)-info.from.y;
  direction.z=info.to.z-info.from.z;
  direction.normalize();
  direction.x*=7.0f;
  direction.y*=7.0f;
  m_startCell.x=fast_float2long_round(floorf((info.from.x-direction.x)*0.1f));
  m_startCell.y=fast_float2long_round(floorf((info.from.y-direction.y)*0.1f));
  m_endCell.x=fast_float2long_round(floorf((info.to.x+direction.x)*0.1f));
  m_endCell.y=fast_float2long_round(floorf((info.to.y+direction.y)*0.1f));
  
 }
 if(m_destroyed) 
 {
  for(int x=0;x<m_width;++x)for(int y=0;y<m_height;++y) 
  {
   PathfindCell *cell=&m_layerCells[x][y];
   if(static_cast<unsigned char>(isGroundOrBridgeLayer((cell->m_0C>>10)&0x3f))) 
   {
    PathfindCell *ground=TheAI->m_pathfinder->getCell(LAYER_GROUND,x+m_xOrigin,y+m_yOrigin);
    if(ground && reinterpret_cast<Rva00366500*>(ground)->rva0036652D(0))
    reinterpret_cast<PathfindZoneManager*>(reinterpret_cast<char*>(TheAI->m_pathfinder)+0x460)->MarkDirty(x+m_xOrigin,y+m_yOrigin);
    
   }
   cell->SetType_Dirty(6);
   
  }
  
 }
 
}
