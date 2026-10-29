// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7
// Native2ED236..2ED313 RET16 complete221. Object argument and a 12-byte
// by-value position proved by the six callers (TerrainLogicBridges,
// PathfinderUpdateLayer, pathfinder, PathfinderBridgeUpdateRva0052ED74,
// ObjectRva00291A8C, ObjectScriptStatus): each builds the argument with an
// inline member-wise copy and stores its address (mov [ebp+8],esp at
// 0x002F12A3), and the WorldBuilder twin (0x00D3FA00) enters EH state 0 for
// the parameter, so its class has a user ctor and a destructor, which the
// canonical aggregate Coord3D lacks. Its real name is unknown: Rva002ED236Pos is the
// callers' placeholder spelling. Bridge scan2..15 through
// enabled layer record; packed cell layer/type and fixed integer height.
// Independently decoded float literals: BC4EB8=5.0 and C52ACC=25.0.
#include "Lib/Coord3D.h"
#include "Lib/ICoord2D.h"
enum PathfindLayerEnum {UNKNOWN_LAYER=0,GROUND_LAYER=1};

struct RectTemplateView {char pad00[0x122];unsigned char flag122;};
class Object {public:bool rva0028AFBB()const;void *vtable;RectTemplateView *templ;char pad08[0x38-8];Coord3D pos;char pad44[0x74-0x44];int id;};
class Rva0028B984ByteField {public:unsigned char get()const;};
bool Rva002EBBFBIsOdd(void *);
struct Rva002ED236Pos {float x,y,z;Rva002ED236Pos(const Coord3D &p){x=p.x;y=p.y;z=p.z;}~Rva002ED236Pos(){}};
class Rva0036666B
{
public:
	bool rva0036666B();
	bool rva0036736E(bool flag);
	char m_pad00[0x34];
	int m_a34; // +0x34
	int m_b38; // +0x38
};
struct BridgeLayerEntry {Rva0036666B check;int height;};
struct BridgeLayerCell {char pad00[0xC];unsigned int flags;};
class Pathfinder {
public:
 PathfindLayerEnum rva002ED236(Object *,Rva002ED236Pos);
 bool rva002ED313(Object *);
 class PathfindCell *getCell(PathfindLayerEnum,int,int);
 void *rva001E3647Pos(int,const Coord3D *);
 char pad00[0xE0];BridgeLayerEntry entries[14];
};
PathfindLayerEnum Pathfinder::rva002ED236(Object *obj,Rva002ED236Pos pos)
{
 if(obj) {
  if(((Rva0028B984ByteField *)obj)->get())return GROUND_LAYER;
  if(!Rva002EBBFBIsOdd(obj)) {pos.x+=5.0f;pos.y+=5.0f;}
 }
 int layer=2;int *enabled=&entries[0].check.m_b38;
 for(;;) {
  Rva0036666B *check=(Rva0036666B *)(enabled-14);
  if(check->rva0036666B() && *enabled) {
   BridgeLayerCell *cell=(BridgeLayerCell *)rva001E3647Pos(layer,reinterpret_cast<const Coord3D *>(&pos));
   if(cell) {
    unsigned int flags=cell->flags;
    if(((flags>>4)&0x3F)==(unsigned int)layer && (flags&0xF)!=5) {
     float height=(float)enabled[1];float delta=height-pos.z;
     if(25.0f>delta)return (PathfindLayerEnum)layer;
    }
   }
  }
  ++layer;enabled+=16;if(layer>15)break;
 }
 BridgeLayerCell *cell=(BridgeLayerCell *)rva001E3647Pos(1,reinterpret_cast<const Coord3D *>(&pos));
 if(cell)return(PathfindLayerEnum)((cell->flags>>4)&0x3F);
 return GROUND_LAYER;
}

// ?rva002ED313@Pathfinder@@QAE_NPAVObject@@@Z @0x002ED313 369B (RET4), the
// next function in retail: can the object stand on its footprint? Target
// facts: the footprint cell comes from 0x002EBC34 (ECX pathfinder, the object
// and its position) and the half/rest radius split from 0x002EBCD6; a negative
// cell x fails; every footprint cell must exist, not be impassable (5) or an
// obstacle (4), not carry bit 18 for an object whose 0x0028AFBB test holds;
// an occupied cell (actual list +0x20 or reserved list +0x14 of its info)
// fails for an object with template flag 0x122 bit 4 when another object of
// the actual list (id +0x74) also sits on the reserved list with that flag,
// and otherwise when the cell's 0x0052DB11 query for the object id holds.
// Structural inference: ZH checkForMovement's rectangular footprint loop; the
// ZH-style inline loop bounds (cell.y - below .. cell.y + above recomputed per
// row) are what lets cl hoist them into the dead cell.y/above homes.
// The three callees that receive local addresses are visible (select-any
// copies of their rows: Rva002EBC34.cpp, pathfinder.cpp): retail packs the
// split's out-word into the dead object home, which cl only does once it can
// see that none of those addresses escape.
struct RectNode {RectNode *next;void *previous;Object *object;};
struct RectCellInfo {char pad00[0x14];RectNode *reserved;char pad18[8];RectNode *actual;};
class PathfindCell {public:RectCellInfo *info;char pad04[8];unsigned int flags;
 __forceinline bool hasActual()const {RectCellInfo *i=info;return i?i->actual!=0:false;}
 __forceinline bool hasReserved()const {RectCellInfo *i=info;return i?i->reserved!=0:false;}
};
class Rva0052DB11
{
public:
	bool rva0052DB11(int);
};
int __cdecl Rva002E9B31Get(void *p);
struct IRegion2DV {ICoord2D lo,hi;};
ICoord2D *Rva002E7875WorldToCell(ICoord2D *,bool,const Coord3D *);
class Rva002E7964 {public:void rva002E7964(ICoord2D *out,unsigned char center,const Coord3D *pos);char pad[0x14];IRegion2DV extent;};
// Select-any copy of pathfinder.cpp's row 0x002E7964 (same body).
__declspec(noinline) inline void Rva002E7964::rva002E7964(ICoord2D *out,unsigned char center,const Coord3D *pos){
 ICoord2D tmp;
 typedef ICoord2D *(__cdecl *CellCall)(ICoord2D*,unsigned char,const Coord3D*);
 reinterpret_cast<CellCall>(Rva002E7875WorldToCell)(&tmp,center,pos);
 if(tmp.x<extent.lo.x || tmp.y<extent.lo.y || tmp.x>extent.hi.x || tmp.y>extent.hi.y)tmp.x=-1;
 *(out?out:out)=tmp;
}
class Rva002EBC34
{
public:
	ICoord2D *rva002EBC34(ICoord2D *a1, void *a2, const Coord3D *a3);
};
// Select-any copy of Rva002EBC34.cpp's row 0x002EBC34 (same body).
__declspec(noinline) inline ICoord2D *Rva002EBC34::rva002EBC34(ICoord2D *a1, void *a2, const Coord3D *a3)
{
	((Rva002E7964 *)this)->rva002E7964(a1, Rva002EBBFBIsOdd(a2), a3);
	return a1;
}
// Select-any copy of pathfinder.cpp's row 0x002EBCD6 (same body).
__declspec(noinline) inline void __cdecl Rva002EBCD6Split(void *p, int *outHalf, int *outRest)
{
	int v = Rva002E9B31Get(p);
	int h = v / 2;
	*outHalf = h;
	*outRest = v - h;
}
class TerrainLogic {public:PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *);};
extern TerrainLogic *TheTerrainLogic;
bool Pathfinder::rva002ED313(Object *obj)
{
 ICoord2D cell;((Rva002EBC34 *)this)->rva002EBC34(&cell,obj,&obj->pos);
 int centerX=cell.x;if(centerX<0)return false;
 PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(obj,&obj->pos);
 int below,above;Rva002EBCD6Split(obj,&below,&above);
 int id=obj->id;
 for(int x=cell.x-below;x<cell.x+above;++x) {
  for(int y=cell.y-below;y<cell.y+above;++y) {
   PathfindCell *pathfindCell=getCell(layer,x,y);
   if(!pathfindCell || (pathfindCell->flags&0xF)==5)return false;
   if(((unsigned char)(pathfindCell->flags>>18)&1) && obj->rva0028AFBB())return false;
   if((pathfindCell->flags&0xF)==4)return false;
   if(pathfindCell->hasActual() || pathfindCell->hasReserved()) {
    RectCellInfo *info=pathfindCell->info;
    if(obj->templ->flag122&0x10) {
     if(info)for(RectNode *rectNode=info->actual;rectNode;rectNode=rectNode->next) {
      Object *other=rectNode->object;
      if(other->id!=id) {
       for(RectNode *reservedNode=info->reserved;reservedNode;reservedNode=reservedNode->next)
        if(reservedNode->object==other){if(reservedNode->object->templ->flag122&0x10)return false;break;}
      }
     }
    } else if(((Rva0052DB11 *)pathfindCell)->rva0052DB11(id))return false;
   }
  }
 }
 return true;
}
