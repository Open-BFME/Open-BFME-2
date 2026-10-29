// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
//
typedef bool Bool;typedef int Int;
struct LineContextTemplate {
 char pad00[0x108];unsigned char kinds[24];char pad120[0x56C-0x120];
 Int priority;char pad570[0x634-0x570];Bool flag;
};
class Object {public:Bool rva0028AC62()const;Bool rva0028AFBB()const;
 void *vtable;LineContextTemplate *definition;char pad08[0x258-8];void *ai;char pad25C[0x274-0x25C];Object *container;
};
class Rva0006E009DwordField
{
public:
	int get()const;
};
class Rva002E6FDF
{
public:
	Rva002E6FDF *rva002E6FDF();
	int m_00; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
	int m_0C; // +0x0C
	unsigned char m_10; // +0x10
	unsigned char m_11; // +0x11
	char m_pad12[0x2];
	int m_14; // +0x14
	int m_18; // +0x18
	int m_1C; // +0x1C
	unsigned char m_20; // +0x20
	unsigned char m_21; // +0x21
	char m_pad22[0x2];
	int m_24; // +0x24
	unsigned char m_28; // +0x28
	char m_pad29[0x3];
	int m_2C; // +0x2C
	unsigned char m_30; // +0x30
	unsigned char m_31; // +0x31
	unsigned char m_32; // +0x32
	char m_pad33[0x1];
	int m_34; // +0x34
};
void Rva002EBCA7Split(void *,Int *,unsigned char *);
struct LineContextQuery {
 Int surfaces;Bool flag4,flag5;Int priority8;Bool flagC;
};
class Pathfinder;struct ICoord2D {Int x,y;};
struct TCheckMovementInfo {
 Int x,y,layer,radius;Bool center;unsigned char flag11;char pad12[2];Int surfaces;unsigned ignored;
 LineContextQuery query;Int word2C;Bool flag30,flag31,flag32;char pad33;Int word34;
};
struct LineContextMovement : TCheckMovementInfo {
 __forceinline LineContextMovement(){((Rva002E6FDF *)this)->rva002E6FDF();}
};
struct Rva002ECE6AInfo {
 Rva002ECE6AInfo(Pathfinder *,const Object *,Int,Bool,Bool,Bool,Bool);
 Int cellCallback(class PathfindCell *,class PathfindCell *,Int,Int);
 Pathfinder *pathfinder;const Object *object;unsigned char flag8;char pad9[3];
 LineContextMovement movement;ICoord2D previous;LineContextQuery query;
 unsigned char flag5C,flag5D;char pad5E[2];
};
Rva002ECE6AInfo::Rva002ECE6AInfo(Pathfinder *a,const Object *b,Int c,Bool d,Bool e,Bool f,Bool g):pathfinder(a),object(b),flag8(e)
{
 const Object *obj=b;
 Int priority=obj->definition->priority;Bool templateFlag=obj->definition->flag;
 Bool flagA=obj->rva0028AC62();Bool flagB=obj->rva0028AFBB();
 LineContextQuery &value=query;
 value.surfaces=c;value.flag4=!templateFlag;value.flag5=flagB;value.flagC=flagA;value.priority8=priority-1;
 flag5D=false;
 *(LineContextQuery *)((char *)&movement+0x1C)=query;
 flag5C=(unsigned char)g;movement.flag11=d;
 movement.surfaces=(*(const unsigned *)(obj->definition->kinds+8)&0x4000000)?1:0x10;
 movement.surfaces|=0xC;
 if(!(unsigned char)f || !(obj->definition->kinds[1]&8))movement.surfaces|=2;
 obj=object;
 const Rva0006E009DwordField *ai=(const Rva0006E009DwordField *)obj->ai;movement.ignored=ai?ai->get():0;
 obj=object;
 if(!(obj->definition->kinds[13]&0x20) && !(obj->definition->kinds[23]&0x80))
  Rva002EBCA7Split((void*)obj,&movement.radius,(unsigned char *)&movement.center);
 else {movement.radius=1;movement.center=true;}

}

// ?cellCallback@Rva002ECE6AInfo@@QAEHPAVPathfindCell@@0HH@Z @0x002ECE6A 436B
// (native 0x002ECE6A..0x002ED01E, ret 0x10): the line walk's per-cell callback,
// called by the rowed walker 0x002EEF16. With +0x5C set it first rejects a cell
// whose bit 21 is clear once +0x5D has latched (a set bit latches it), and any
// cell holding an occupant that is neither the object nor its container
// (+0x274). Then the trigger manager's burning grid, the movement check
// (0x002EA658 with a previous cell, else 0x002EA34A), the +0x40 result, the
// cell's bits 16/23 unless +0x08, a same-layer clear-cell accept and finally
// 0x002E6DC4. The _WriteBarrier in the latched-flag reject keeps that return
// apart from the occupant reject, which leaves the flag test and its return
// one block that retail lays out after the occupant list load; the barrier
// emits no code. Field meanings are not recovered.
#include "Lib/Coord3D.h"
#include <math.h>
extern "C" void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
__forceinline long fast_float2long_round(float f)
{
 long i;
 __asm {
  fld [f]
  fistp [i]
 }
 return i;
}
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(floorf(x)))
struct LineOccupant {LineOccupant *next;void *word4;Object *object;};
struct LineCellInfo {char pad0[0x14];LineOccupant *occupants;};
class PathfindCell {public:LineCellInfo *info;void *word4;Int word8;unsigned flags;
 __forceinline Int layer()const{return (flags>>4)&0x3F;}
 __forceinline Bool bit21()const{return (unsigned char)((flags>>21)&1)!=0;}
};
struct LineFireCell {char pad0[6];unsigned short count;char pad8[0x14-8];};
class Rva002872BA {public:
 __forceinline Bool isBurning(const Coord3D &pos)const {
  Int x=REAL_TO_INT_FLOOR((pos.x+0.5f)*0.1f);Int y=REAL_TO_INT_FLOOR((pos.y+0.5f)*0.1f);
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
class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a_raw, void *b_raw);
	char m_pad00[0x48];
private:
	void *m_48; // +0x48
};
Bool Rva001E3679(Int);
Int Rva002ECE6AInfo::cellCallback(PathfindCell *from,PathfindCell *to,Int x,Int y)
{
 if(flag5C)
 {
  if(to->bit21()) flag5D=1;
  else if(flag5D) { _WriteBarrier(); return 1; }
  for(LineOccupant *node=to->info?to->info->occupants:0;node;node=node->next)
  {
   Object *other=node->object;
   if(other!=object && other->container!=object) return 1;
  }
 }
 Coord3D point;point.x=(float)(x*10);point.y=(float)(y*10);
 if(TheTriggerManager->isBurning(point)) return 1;
 movement.x=x;movement.y=y;movement.layer=to->layer();
 if(from) {if(!pathfinder->rva002EA658((Object *)object,movement,&previous)) return 1;}else {if(!pathfinder->checkForMovement((Object *)object,movement)) return 1;}
 if(movement.word34) return 1;
 previous.x=x;previous.y=y;
 if(!flag8 && ((unsigned char)((to->flags>>16)&1)!=0 || (unsigned char)((to->flags>>23)&1)!=0)) return 1;
 if(from) {
  unsigned flags=to->flags;Int layer=(flags>>4)&0x3F;
  if(Rva001E3679(layer) && from->layer()==layer && !(flags&0xF))return 0;
 }
 return !((Rva002E6DC4 *)pathfinder)->rva002E6DC4(&query,to);
}
