// ?cellCallback@Rva002ECE6AInfo@@QAEHPAVPathfindCell@@0HH@Z
// partial score=0.9536999396 date=2026-10-09
// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// Native2ECE6A..2ED01E RET16 full436. Existing init owner retained:
// callers2F1AF4 and2F1B66 construct this 60-byte context then pass it to
// the typed line walker2F0C78. Target facts are infoC, query4C, copy28,
// state5C/5D, Object template56C/634 and kind bits90/11/109/191.
// ZH line-passability queries guide purpose; original fields remain unnamed.
typedef bool Bool;typedef int Int;
struct LineContextTemplate {
 char pad00[0x108];unsigned char kinds[24];char pad120[0x56C-0x120];
 Int priority;char pad570[0x634-0x570];Bool flag;
};
class Object {public:Bool rva0028AC62()const;Bool rva0028AFBB()const;
 void *vtable;LineContextTemplate *definition;char pad08[0x258-8];void *ai;char pad25C[0x274-0x25C];Object *container;
};
class Rva0006E009DwordField {public:Int get()const;};
class Rva002E6FDF {public:Rva002E6FDF *rva002E6FDF();};
void Rva002EBCA7Split(void *,Int *,unsigned char *);
struct LineContextQuery {
 Int surfaces;Bool flag4,flag5;Int priority8;Bool flagC;
};
struct TCheckMovementInfo {
 Int x,y,layer,radius;Bool center;unsigned char flag11;char pad12[2];Int surfaces;unsigned ignored;
 LineContextQuery query;Int word2C;Bool flag30,flag31,flag32;char pad33;Int word34;
};
class Pathfinder;struct ICoord2D {Int x,y;};
struct Rva002ECE6AInfo {
 Rva002ECE6AInfo *init(void *,void *,void *,void *,Int,Int,Int);
 Int cellCallback(class PathfindCell *,class PathfindCell *,Int,Int);
 __forceinline Bool acceptCell(class PathfindCell *);
 Pathfinder *pathfinder;Object *object;unsigned char flag8;char pad9[3];
 TCheckMovementInfo movement;ICoord2D previous;LineContextQuery query;
 unsigned char flag5C,flag5D;char pad5E[2];
};

#include "Lib/Coord3D.h"
extern "C" __declspec(dllimport) double __cdecl floor(double);
struct LineOccupant {LineOccupant *next;void *word4;Object *object;};
struct LineCellInfo {char pad0[0x14];LineOccupant *occupants;};
class PathfindCell {public:LineCellInfo *info;void *word4;Int word8;unsigned flags;
 __forceinline Int layer()const{return (flags>>4)&0x3F;}
 __forceinline Bool bit21()const{return (unsigned char)((flags>>21)&1)!=0;}
};
struct LineFireCell {char pad0[6];unsigned short count;char pad8[0x14-8];};
class Rva002872BA {public:
 // Existing PathfinderRva002F4491CellCallback numeric shim. C++ casts use
 // truncation; target FISTP obeys the current x87 control word after floor.
 static __forceinline Int realToIntFloor(float f) {
  float rounded=(float)floor((double)f);Int result;
  __asm {
   fld [rounded]
   fistp [result]
  }
  return result;
 }
 __forceinline Bool isBurning(const Coord3D &pos)const {
  Int x=realToIntFloor((pos.x+0.5f)*0.1f);Int y=realToIntFloor((pos.y+0.5f)*0.1f);
  if(x>=0 && x<width && y>=0 && y<height)return cells[x][y].count>0;
  return false;
 }
 char pad00[0x70];LineFireCell **cells;char pad74[4];Int width,height;
};
extern Rva002872BA *TheTriggerManager;
class Pathfinder {public:
 Bool checkForMovement(Object *,TCheckMovementInfo &);
 Bool rva002EA658(Object *,TCheckMovementInfo &,const ICoord2D *);
};
class Rva002E6DC4 {public:Bool rva002E6DC4(void *,void *);};
Bool Rva001E3679(Int);
__forceinline Bool Rva002ECE6AInfo::acceptCell(PathfindCell *to) {

  if(!to->bit21()) {if(flag5D)return false;}else flag5D=1;
  LineOccupant *node=to->info?to->info->occupants:0;
  if(node){Object *current=object;do{Object *other=node->object;if(other!=current && other->container!=current)return false;node=node->next;}while(node); }

 return true;
}
Int Rva002ECE6AInfo::cellCallback(PathfindCell *from,PathfindCell *to,Int x,Int y)
{
 if(flag5C && !acceptCell(to))return 1;
 Coord3D point;point.x=(float)(x*10);point.y=(float)(y*10);
 if(TheTriggerManager->isBurning(point))return 1;
 movement.x=x;movement.y=y;movement.layer=to->layer();
 if(from) {if(!pathfinder->rva002EA658(object,movement,&previous))return 1;}else {if(!pathfinder->checkForMovement(object,movement))return 1;}
 if(movement.word34)return 1;
 previous.x=x;previous.y=y;
 if(!flag8 && ((unsigned char)((to->flags>>16)&1)!=0 || (unsigned char)((to->flags>>23)&1)!=0))return 1;
 if(from) {
  unsigned flags=to->flags;Int layer=(flags>>4)&0x3F;
  if(Rva001E3679(layer) && from->layer()==layer && !(flags&0xF))return 0;
 }
 return !((Rva002E6DC4 *)pathfinder)->rva002E6DC4(&query,to);
}
