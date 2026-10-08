// ?ClassifyBridgeCells@PathfindLayer@@QAEXXZ
// partial score=0.95 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Reference: Open-BFME-1 968ca36c3265b295297e6aed45a6bd89ffe59c40,
// game/GameEngine/Source/GameLogic/AI/PathfindLayerResetFull.cpp.
// Target identity: the adjacent verified PathfindLayer::getCell and
// DoBoundsOverlap bodies share cells +4, dimensions +8/+C and triggers +38.
// Target adaptation: bridge +34, triggers +38, trigger ID +3C; +2C becomes
// -1 and +30 is retained. The original name of this 66-byte wrapper and its
// 105-byte allocation-clear helper remain unknown.

#include "../Code/Libraries/Include/Lib/Coord3D.h"
#include "../Code/Libraries/Include/Lib/Coord2D.h"
#include <math.h>

void __cdecl operator delete(void *pointer);
void __cdecl operator delete[](void *pointer);

struct ICoord2D
{
	int x;
	int y;
};

// The primitive virtual order is measured by the rowed Common/System/Xfer.cpp
// providers: ICoord2D slot 19, int slot 31, bool slot 36. Version1 is the
// existing 23-byte provider at 0x000053EE. Other entries are ABI placeholders.
class Xfer
{
public:
	void Version1();
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual Xfer &xferICoord2D(ICoord2D &value);
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual Xfer &xferInt(int &value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual Xfer &xferBool(bool &value);
};

class PathfindCell
{
public:
	void rva0052DED3();
	void rva0052D84C(Xfer *xfer);
public:
	unsigned char m_storage[8];
	unsigned short m_zone;
	unsigned short m_padding;
	unsigned int m_flags;
	bool SetType_Dirty(int);
};

// Reuse the established provider's linker spelling for the native 75-byte
// vector destructor at 0x002E70E8 (16-byte elements, destructor 0x0052DD64).
// This adapter asserts that measured destruction ABI, not that pathfinding
// cells carry the provider's file-info payload identity.
class MixFileInfoBuffer;
class MixFileCreator
{
public:
	struct FileInfoStruct
	{
		~FileInfoStruct();
		MixFileInfoBuffer *m_buffer;
		unsigned long m_crc;
		unsigned long m_offset;
		unsigned long m_size;
	};
};

// Native vslot zero is called with flags zero; its returned pointer is
// passed to the rowed global operator delete. Only that ABI is asserted.
class Rva00366DECVirtual
{
public:
	virtual void *slot0(unsigned int flags);
};

class Bridge;
class PathfindLayer
{
public:
	void ClassifyBridgeCells();
	void ClassifyWallCells();
	void rva00366DEC();
	void rva003667D4();
	void rva003666FD(Xfer *xfer);
private:
	void *m_blockOfMapCells;
	PathfindCell **m_layerCells;
	int m_width;
	int m_height;
	int m_xOrigin;
	int m_yOrigin;
	ICoord2D m_startCell;
	ICoord2D m_endCell;
	int m_layer;
	int m_zone;
	bool m_destroyed;
	unsigned char m_pad31[3];
	Bridge *m_bridge;
	Rva00366DECVirtual *m_triggers;
	int m_triggerObjectID;
};

// Native 0x00366DEC..0x00366E2E, RET 0.
void PathfindLayer::rva00366DEC()
{
	m_bridge = 0;
	rva003667D4();
	m_layer = 1;
	if (m_triggers)
		::operator delete(m_triggers->slot0(0));
	m_triggers = 0;
	m_startCell.x = -1;
	m_startCell.y = -1;
	m_endCell.x = -1;
	m_endCell.y = -1;
	m_zone = -1;
	m_triggerObjectID = -1;
}

// Native 0x003667D4..0x0036683D, RET 0. Reference algorithm:
// game/GameEngine/Source/GameLogic/AI/PathfindLayerApplyZone.cpp bfmeReset
// at the same donor revision. Target adds the zone reset at +0x2C.
void PathfindLayer::rva003667D4()
{
	if (m_layerCells)
	{
		for (int i = 0; i < m_width; ++i)
		{
			for (int j = 0; j < m_height; ++j)
			{
				PathfindCell *cell = &m_layerCells[i][j];
				cell->rva0052DED3();
			}
		}
		delete[] m_layerCells;
		m_layerCells = 0;
	}
	if (m_blockOfMapCells)
		delete[] static_cast<MixFileCreator::FileInfoStruct *>(m_blockOfMapCells);
	m_zone = -1;
	m_blockOfMapCells = 0;
	m_width = 0;
	m_height = 0;
	m_xOrigin = 0;
	m_yOrigin = 0;
}

// Native 0x003666FD..0x003667D4, RET 4. Donor at the revision above:
// game/GameEngine/Source/GameLogic/AI/PathfindLayerXfer.cpp. Target uses the
// out-of-line Version1 helper, BFME2 primitive slots, bool +30 and ID +3C;
// the donor's additional field30 transfer is absent. Method name is unresolved.
void PathfindLayer::rva003666FD(Xfer *xfer)
{
	xfer->Version1();
	if (m_layerCells)
	{
		for (int x = 0; x < m_width; ++x)
		{
			for (int y = 0; y < m_height; ++y)
				m_layerCells[x][y].rva0052D84C(xfer);
		}
	}
	xfer->xferInt(m_width);
	xfer->xferInt(m_height);
	xfer->xferInt(m_xOrigin);
	xfer->xferInt(m_yOrigin);
	xfer->xferICoord2D(m_startCell);
	xfer->xferICoord2D(m_endCell);
	int layer = m_layer;
	xfer->xferInt(layer);
	xfer->xferInt(m_zone);
	xfer->xferBool(m_destroyed);
	xfer->xferInt(m_triggerObjectID);
}

// Native 0x00366B77..0x00366CEA, RET0. WB F29A70 names
// PathfindLayer::ClassifyWallCells and carries the same corner tests and
// reset/type classification. Target cell zone +8 and layer/zone flags +C
// are read from native stores and the already verified setter providers.
// Native tests nonzero in the branch reached when the count is not positive.
// Bitfield setter providers are already verified under their ledger owner.
class Rva00366500 { public: bool rva00366500(int);bool rva0036652D(int);};
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

struct Region2D {Coord2D lo,hi;};
class Rva0027C36A {public: Rva0027C36A();Rva0027C36A &operator=(const Rva0027C36A&);Coord3D from,to;unsigned char rest[0xa8-24];};
class Bridge {public: bool isPointOnBridge(const Coord3D*);bool isCellOnSide(const Region2D*);bool isCellOnEnd(const Region2D*);bool isCellEntryPoint(const Region2D*,float*);float getBridgeHeight(const Coord3D*,Coord3D*);unsigned char prefix[12];Rva0027C36A info;};
enum PathfindLayerEnum {LAYER_GROUND=1};
class Pathfinder {public: PathfindCell *getCell(PathfindLayerEnum,int,int);};
class PathfindZoneManager {public: void MarkDirty(int,int);};
extern void *g_00DFF0F8;
struct PathfindAIView {unsigned char prefix[16];Pathfinder *pathfinder;};
class TerrainLogic {public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();
 virtual float slot7(float,float,bool,Coord3D*,bool);
};
extern TerrainLogic *TheTerrainLogic;
int Rva002E6E6CGet(int);
// ZH BaseType.h fast_float2long_round, preserved for the proven x87
// conversion blocker: C++ casts call _ftol2 and /QIfist rejects /arch:SSE.
// Native endpoint conversions use this exact fld/fistp rounding primitive.
__forceinline long fast_float2long_round(float f)
{
 long i;
 __asm {
  fld [f]
  fistp [i]
 }
 return i;
}
void PathfindLayer::ClassifyBridgeCells()
{
 m_startCell.x=-1;m_startCell.y=-1;m_endCell.x=-1;m_endCell.y=-1;
 for(int x=0;x<m_width;++x) {
  for(int y=0;y<m_height;++y) {
   PathfindCell *cell=&m_layerCells[x][y];
   reinterpret_cast<Rva00366500*>(cell)->rva0036652D(0);
   reinterpret_cast<Rva00366500*>(cell)->rva00366500(m_layer);
   int worldX=x+m_xOrigin,worldY=y+m_yOrigin;
   Coord3D lo,hi,point;
   lo.y=worldY*10.0f;hi.y=lo.y+10.0f;lo.x=worldX*10.0f;hi.x=lo.x+10.0f;
   int inside=0;
   if(m_bridge->isPointOnBridge(&lo))++inside;
   point=lo;point.y=hi.y;
   if(m_bridge->isPointOnBridge(&point))++inside;
   if(m_bridge->isPointOnBridge(&hi))++inside;
   point=lo;point.x=hi.x;
   if(m_bridge->isPointOnBridge(&point))++inside;
   cell->rva0052DED3();
   reinterpret_cast<Rva00366500*>(cell)->rva00366500(m_layer);
   cell->SetType_Dirty(5);
   if(inside==4)cell->SetType_Dirty(0);
   else {
    if(inside!=0)cell->SetType_Dirty(6);
    Region2D region;
    region.lo.x=lo.x;region.lo.y=lo.y;region.hi.x=hi.x;region.hi.y=hi.y;
    if(m_bridge->isCellOnSide(&region))cell->SetType_Dirty(6);
    else {
     if(m_bridge->isCellOnEnd(&region))cell->SetType_Dirty(0);
     float height;
     if(m_bridge->isCellEntryPoint(&region,&height)) {
      cell->SetType_Dirty(0);
      reinterpret_cast<Rva00366500*>(cell)->rva0036652D(1);
      PathfindCell *ground=static_cast<PathfindAIView*>(g_00DFF0F8)->pathfinder->getCell(LAYER_GROUND,worldX,worldY);
      if(reinterpret_cast<Rva00366500*>(ground)->rva0036652D((cell->m_flags>>4)&0x3f))
       reinterpret_cast<PathfindZoneManager*>(reinterpret_cast<char*>(static_cast<PathfindAIView*>(g_00DFF0F8)->pathfinder)+0x460)->MarkDirty(worldX,worldY);
     }
    }
   }
   Coord3D center;center.z=lo.z;center.x=lo.x+5.0f;center.y=lo.y+5.0f;
   if((cell->m_flags&15)!=5 && ((cell->m_flags>>10)&0x3f)!=1) {
    float height=TheTerrainLogic->slot7(center.x,center.y,true,0,true)+10.0f;
    if(height>m_bridge->getBridgeHeight(&center,0)) {
     PathfindCell *ground=static_cast<PathfindAIView*>(g_00DFF0F8)->pathfinder->getCell(LAYER_GROUND,worldX,worldY);
     if((ground->m_flags&15)!=4 && ground->SetType_Dirty(6))
      reinterpret_cast<PathfindZoneManager*>(reinterpret_cast<char*>(static_cast<PathfindAIView*>(g_00DFF0F8)->pathfinder)+0x460)->MarkDirty(worldX,worldY);
    }
   }
  }
  Rva0027C36A info;
  info=m_bridge->info;
  Coord3D direction;
  direction.x=info.to.x-info.from.x;direction.y=info.to.y-info.from.y;direction.z=info.to.z-info.from.z;
  direction.normalize();
  direction.x*=7.0f;direction.y*=7.0f;
  m_startCell.x=fast_float2long_round(static_cast<float>(floor((info.from.x-direction.x)*0.1f)));
  m_startCell.y=fast_float2long_round(static_cast<float>(floor((info.from.y-direction.y)*0.1f)));
  m_endCell.x=fast_float2long_round(static_cast<float>(floor((info.to.x+direction.x)*0.1f)));
  m_endCell.y=fast_float2long_round(static_cast<float>(floor((info.to.y+direction.y)*0.1f)));
 }
 if(m_destroyed) {
  for(int x=0;x<m_width;++x)for(int y=0;y<m_height;++y) {
   PathfindCell *cell=&m_layerCells[x][y];
   if(static_cast<unsigned char>(Rva002E6E6CGet((cell->m_flags>>10)&0x3f))) {
    PathfindCell *ground=static_cast<PathfindAIView*>(g_00DFF0F8)->pathfinder->getCell(LAYER_GROUND,x+m_xOrigin,y+m_yOrigin);
    if(ground && reinterpret_cast<Rva00366500*>(ground)->rva0036652D(0))
      reinterpret_cast<PathfindZoneManager*>(reinterpret_cast<char*>(static_cast<PathfindAIView*>(g_00DFF0F8)->pathfinder)+0x460)->MarkDirty(x+m_xOrigin,y+m_yOrigin);
   }
   cell->SetType_Dirty(6);
  }
 }
}
