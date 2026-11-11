// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Reference: Open-BFME-1 968ca36c3265b295297e6aed45a6bd89ffe59c40,
// game/GameEngine/Source/GameLogic/AI/PathfindLayerResetFull.cpp.
// Target identity: the adjacent verified PathfindLayer::getCell and
// DoBoundsOverlap bodies share cells +4, dimensions +8/+C and triggers +38.
// Target adaptation: bridge +34, triggers +38, trigger ID +3C; +2C becomes
// -1 and +30 is retained. The original name of this 66-byte wrapper and its
// 105-byte allocation-clear helper remain unknown.

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Region2D.h"
#include <math.h>

inline float Coord3D::length() const { return (float)sqrt(x*x+y*y+z*z); }
inline void Coord3D::normalize() { float len=length(); if(len!=0.0f){float scale=1.0f/len;x*=scale;y*=scale;z*=scale;} }
inline float Coord3D::GetLengthSqrd() const { float x_value=x,y_value=y,z_value=z; return x_value*x_value+y_value*y_value+z_value*z_value; }
__declspec(noinline) inline float Coord3D::GetLength() const { float x_value=x,y_value=y,z_value=z; return (float)sqrt(x_value*x_value+y_value*y_value+z_value*z_value); }
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void __cdecl operator delete(void *pointer);
void __cdecl operator delete[](void *pointer);

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

// The primitive virtual order is measured by the rowed Common/System/Xfer.cpp
// providers: ICoord2D slot 19, int slot 31, bool slot 36. Version1 is the
// existing 23-byte provider at 0x000053EE. Other entries are ABI placeholders.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
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



// Native 0x003666FD..0x003667D4, RET 4. Donor at the revision above:
// game/GameEngine/Source/GameLogic/AI/PathfindLayerXfer.cpp. Target uses the
// out-of-line Version1 helper, BFME2 primitive slots, bool +30 and ID +3C;
// the donor's additional field30 transfer is absent. Method name is unresolved.
void PathfindLayer::rva003666FD(Xfer *xfer)
{
	xfer->Version1();
	if (m_layerCells)
	{
		for (int cellX = 0; cellX < m_width; ++cellX)
		{
			for (int cellY = 0; cellY < m_height; ++cellY)
				m_layerCells[cellX][cellY].DoXfer(xfer);
		}
	}
	*xfer == m_width;
	*xfer == m_height;
	*xfer == m_xOrigin;
	*xfer == m_yOrigin;
	*xfer == m_startCell;
	*xfer == m_endCell;
	int layer = m_layer;
	*xfer == layer;
	*xfer == m_zone;
	*xfer == m_destroyed;
	*xfer == height;
}

// Native 0x00366B77..0x00366CEA, RET0. WB F29A70 names
// PathfindLayer::ClassifyWallCells and carries the same corner tests and
// reset/type classification. Target cell zone +8 and layer/zone flags +C
// are read from native stores and the already verified setter providers.
// Native tests nonzero in the branch reached when the count is not positive.
// Bitfield setter providers are already verified under their ledger owner.
#include "../../../Include/GameLogic/Rva00366500.h"
class Rva00366B30 { public: bool rva00366B30(const Coord3D*);};
void PathfindLayer::ClassifyWallCells()
{
 m_startCell.x=-1;m_startCell.y=-1;m_endCell.x=-1;m_endCell.y=-1;
 for(int x=0;x<m_width;++x) {
  for(int y=0;y<m_height;++y) {
   PathfindCell *cell=&m_layerCells[x][y];
   reinterpret_cast<Rva00366500*>(cell)->rva0036652D(0);
   reinterpret_cast<Rva00366500*>(cell)->rva00366500(m_layer);
   int worldX=x+m_xOrigin, worldY=y+m_yOrigin;
   Coord3D lo,hi,point;
   lo.y=worldY*10.0f;hi.y=lo.y+10.0f;
   lo.x=worldX*10.0f;hi.x=lo.x+10.0f;
   int inside=0;
   if(reinterpret_cast<Rva00366B30*>(this)->rva00366B30(&lo)) ++inside;
   point=lo;point.y=hi.y;
   if(reinterpret_cast<Rva00366B30*>(this)->rva00366B30(&point)) ++inside;
   if(reinterpret_cast<Rva00366B30*>(this)->rva00366B30(&hi)) ++inside;
   point=lo;point.x=hi.x;
   if(reinterpret_cast<Rva00366B30*>(this)->rva00366B30(&point)) ++inside;
   cell->rva0052DED3();
   reinterpret_cast<Rva00366500*>(cell)->rva00366500(m_layer);
   cell->m_zone=static_cast<unsigned short>(m_zone);
   cell->SetType_Dirty(5);
   if(inside>0)cell->SetType_Dirty(0);
   else if(inside!=0)cell->SetType_Dirty(6);
  }
 }
}


// Native 003666C6..003666FD: constructor callback of the 16x64-byte
// layer array in Pathfinder 002F6E22. ZH/BF1 constructor is the semantic
// lead; all defaults and BFME2 field offsets are independent retail facts.
PathfindLayer::PathfindLayer()
{
 m_blockOfMapCells=0; m_layerCells=0;
 m_width=0; m_height=0; m_xOrigin=0; m_yOrigin=0;
 m_startCell.x=-1; m_startCell.y=-1; m_endCell.x=-1; m_endCell.y=-1;
 m_layer=0; m_zone=-1; m_destroyed=false;
 m_bridge=0; m_triggers=0; height=-1;
}

// Native 00366CEA..00366DEC RET16; WB F29DE0 names ConnectsZones.
// BFME1 clean source supplies the zone-walk semantics. Native accesses prove
// cells4, dimensions8/C, destroyed30, zone flags10..15, and LocomotorSet10/15.
// The scheduling fence preserves the native loop-index load before cell-base load.
enum PathfindLayerEnum{LAYER_INVALID=-1,LAYER_GROUND=1,LAYER_FIRST_BRIDGE=16};
int isGroundOrBridgeLayer(int);
class LocomotorSet{public:char pad0[0x10];int m_surfaces;char pad14;unsigned char m_15;int getValidSurfaces()const{return m_surfaces;}};
struct PathfindMovementProfile{int m_surfaces;bool m_crusher,m_terrainOnly;char pad6[2];int m_layer;unsigned char m_C;PathfindMovementProfile(int s):m_surfaces(s),m_crusher(false),m_terrainOnly(false),m_layer(-1){} };
#include "../../../Include/GameLogic/Rva002E99F9Sub460.h"
#include "../../../Include/GameLogic/PathfindZoneManager.h"
#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;
 bool PathfindLayer::ConnectsZones(PathfindZoneManager *zoneManager,const LocomotorSet &locomotorSet,int zone1,int zone2)
{
 if(!m_destroyed)return false;
 bool found1=false,found2=false;
 for(int i=0;i<m_width;++i){
  for(int j=0;j<m_height;++j){
   PathfindCell *cell=&m_layerCells[i][j];
   int connectLayer=(cell->m_0C>>10)&0x3f;
   _ReadWriteBarrier(); if((unsigned char)isGroundOrBridgeLayer(connectLayer)){
    PathfindCell *groundCell=TheAI->m_pathfinder->getCell(LAYER_GROUND,i+m_xOrigin,j+m_yOrigin);
    if(groundCell){
     PathfindMovementProfile profile(locomotorSet.getValidSurfaces());profile.m_C=locomotorSet.m_15;
     unsigned short zone=((Rva002E99F9Sub460 *)zoneManager)->rva0053241F(&profile,groundCell->m_zone);
     zone=((Rva002E99F9Sub460 *)zoneManager)->rva00531FD4(&profile,zone);
     if(zone==zone1)found1=true;
     if(zone==zone2)found2=true;
    }
   }
  }
 }
 return found1&&found2;
}

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

