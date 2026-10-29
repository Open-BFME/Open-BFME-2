// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include
// The body after the blocked test is that test's else block (retail block order).
// Reference lead: Open-BFME-1 f98983a7d LinePassableStruct_linePassableCallback.cpp,
// with Zero Hour AIPathfind.cpp::linePassableCallback. Native callback 002ED15A
// keeps its existing address-derived payload identity; retail extends the
// query with a one-pinched-cell allowance at +38/+58. Layout comes from target
// accesses, not a donor class-layout claim.
#include "Lib/ICoord2D.h"
enum PathfindLayerEnum { LAYER_GROUND=0 };
class Object;
class PathfindCell {
public:
 int getLayer() const { return (flags>>4)&0x3f; }
 int getType() const { return flags&0xf; }
 char pad[0xc]; unsigned int flags;
};
struct TCheckMovementInfo {
 ICoord2D cell; PathfindLayerEnum layer;
 char rest[0x30-0xc]; bool pinched; char pad31[3]; int blocked;
};
class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a_raw, void *b_raw);
	char m_pad00[0x48];
private:
	void *m_48; // +0x48
};
bool Rva001E3679(int);
class Pathfinder { public: bool checkForMovement(Object *,TCheckMovementInfo &); bool rva002EA658(Object *,TCheckMovementInfo &,const ICoord2D *); };
struct Rva002ED15AInfo {
 Pathfinder *pathfinder; Object *object; TCheckMovementInfo info;
 ICoord2D previous; int valid[4]; int pinchedCount;
 int cellCallback(PathfindCell *,PathfindCell *,int,int);
};
int Rva002ED15AInfo::cellCallback(PathfindCell *from,PathfindCell *to,int x,int y) {
 info.cell.x=x; info.cell.y=y; info.layer=(PathfindLayerEnum)to->getLayer();
 if(from) { if(!pathfinder->rva002EA658(object,info,&previous)) return 1; }
 else { if(!pathfinder->checkForMovement(object,info)) return 1; }
 if(info.blocked) return 1;
 else
 {
  if(info.pinched && ++pinchedCount>1) return 1;
  previous.x=x; previous.y=y;
  if(from) {
   unsigned int bits=to->flags; int layer=(bits>>4)&0x3f;
   if(Rva001E3679(layer) && from->getLayer()==layer && (bits&0xf)==0) return 0;
  }
  return !((Rva002E6DC4 *)pathfinder)->rva002E6DC4(valid,to);
 }
}

// Native 002ED01E..002ED0CC is a complete 174-byte callback (RET16).
// The rowed cell walker 002EF016 and IsLineBlocked wrapper 002F1B32 identify
// the existing address-derived context; its original class name is unresolved.
// Rowed initializer 002E931F and WB D3E0E0 establish the 58-byte layout,
// with validity payload +40 and the previous coordinate pair +50/+54.
// BFME1 cee35b7d8 LinePassableStruct_linePassableCallback.cpp and Zero Hour
// AIPathfind.cpp::linePassableCallback guide semantics; native accesses prove
// BFME2 flag masks, helper selection and layout. The current-cell bits must
// be compared with the previous cell's layer. Grouping the success path in
// the blocked test's else gives retail's shared return-one branch.
struct Rva002ED01EInfo {
 Pathfinder *pathfinder; Object *object; TCheckMovementInfo info;
 int valid[4]; ICoord2D previous;
 int cellCallback(PathfindCell *,PathfindCell *,int,int);
};
int Rva002ED01EInfo::cellCallback(PathfindCell *from,PathfindCell *to,int x,int y) {
 info.cell.x=x; info.cell.y=y; info.layer=(PathfindLayerEnum)to->getLayer();
 if(from) { if(!pathfinder->rva002EA658(object,info,&previous)) return 1; }
 else { if(!pathfinder->checkForMovement(object,info)) return 1; }
 if(info.blocked) return 1;
 else {
  previous.x=x; previous.y=y;
  if(from) {
   unsigned int bits=to->flags; int layer=(bits>>4)&0x3f;
   if(Rva001E3679(layer) && from->getLayer()==layer && (bits&0xf)==0) return 0;
  }
  return !((Rva002E6DC4 *)pathfinder)->rva002E6DC4(valid,to);
 }
}
