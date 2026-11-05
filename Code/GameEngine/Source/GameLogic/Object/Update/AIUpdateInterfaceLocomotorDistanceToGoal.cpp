// cl:  /O1 /G7 /arch:SSE /DNDEBUG /MD /GX-
// ?getLocomotorDistanceToGoal@AIUpdateInterface@@QAEMXZ, retail 0x0026435E, 506 bytes
// (native 0x0026435E..0x00264558).
//
// Zero Hour's AIUpdateInterface::getLocomotorDistanceToGoal (AIUpdate.cpp line 2451): the
// goal type at +0x1FC picks the answer. BFME 2 adds an explicit-position case (types 2 and 4:
// the distance from the object to the goal stored at +0x200), returns 100 for a missing path
// and 0 for a missing locomotor, and tests the locomotor's flag bit 10 (isCloseEnoughDist3D)
// or object kind bit 1 of byte 0x10B (projectile) before the 3-D distance branch. The slot at
// vtable+0x25C is getTreatAsAircraftForLocoDistToGoal; locomotor type 5 (+0x74 of its template)
// is excluded. Facts: layouts and branch order from game.dat, the ZH body as the semantic guide.
//
// Codegen: the explicit case subtracts through a TU-local delta (copy then subtract) so the three
// goal loads precede the subtractions, with a compiler barrier before the result is stored, and
// returns through a named local so the shared return stub is not merged. The self-conditional
// owner in the aircraft branch keeps the receiver in the register retail uses.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include <math.h>
class BfmeVec3EJ;
class Gen_000E5A50 { public: float Get3DCenterDistanceSquared(const BfmeVec3EJ*)const; };
#include "../../../../Include/Common/ThingTemplate.h"
class Object { public: char pad[4];ThingTemplate *templ; char pad8[0x38-8];Coord3D position; const Coord3D*getPosition()const{return &position;} };
class LocomotorTemplate {public:char pad[0x74];int type;};
#include "../../../../Include/GameLogic/LocomotorClass.h"
static inline bool isCloseEnoughDist3D(const Locomotor *loco){return (loco->m_flags>>10)&1;}
#include "../../../../Include/GameLogic/PathNode.h"
struct Rva003642DFNode;
struct Rva003642DFResult { Rva003642DFResult();Rva003642DFNode*node;Coord3D position; };
class Rva00363D20 {public:double rva00363D20();};
class Rva0008BB38FloatField;
#include "../../../../Include/GameLogic/PathfindPath.h"
// Read the canonical +0x24 goal field directly; older getter copies use +0x28.
#include "../../../../Include/Common/StateMachineClass.h"
class AIUpdateInterface {public:
#define SLOT(n) virtual void slot##n();
#define TEN(n) SLOT(n##0) SLOT(n##1) SLOT(n##2) SLOT(n##3) SLOT(n##4) SLOT(n##5) SLOT(n##6) SLOT(n##7) SLOT(n##8) SLOT(n##9)
TEN(0) TEN(1) TEN(2) TEN(3) TEN(4) TEN(5) TEN(6) TEN(7) TEN(8) TEN(9) TEN(10) TEN(11) TEN(12) TEN(13) TEN(14) SLOT(150)
#undef TEN
#undef SLOT
virtual bool getTreatAsAircraftForLocoDistToGoal();
float getLocomotorDistanceToGoal();
char pad4[4];Object*owner;char padC[0x30-0xC];StateMachine*machine;char pad34[0x140-0x34];Path*path;char pad144[0x1F0-0x144];Locomotor*loco;char pad1F4[8];int goalType;Coord3D goal;
};
struct Delta3 { float x,y,z; Delta3(const Coord3D &c):x(c.x),y(c.y),z(c.z){} void sub(const Coord3D &p){x-=p.x;y-=p.y;z-=p.z;} };
float AIUpdateInterface::getLocomotorDistanceToGoal(){
 Coord3D goalPos;
 switch(goalType){
 case 0:case 3:return 0.0f;
 case 2:case 4:{
  const Coord3D *dest=&goal;const Coord3D *pos=owner->getPosition();
  Delta3 d(*dest);d.sub(*pos);_ReadWriteBarrier();goalPos.x=d.x;goalPos.y=d.y;goalPos.z=d.z;
  float len=goalPos.length();return len;
 }
 case 1:{
  if(!path)return 100.0f;
  if(!loco)break;
  if(isCloseEnoughDist3D(loco)||(owner->templ->m_kindof[0] & 0x2000000U)){
   const Object *obj=owner;PathNode *last=path->m_pathTail;const Coord3D *p=&machine->m_goalPosition;
   goalPos.x=p->x;goalPos.y=p->y;goalPos.z=p->z;
   if(last)goalPos=last->m_pos;
   return (float)sqrt(((const Gen_000E5A50*)obj)->Get3DCenterDistanceSquared((const BfmeVec3EJ*)&goalPos));
  } else {
  if(loco->m_template->type==5)break;
  bool aircraft=getTreatAsAircraftForLocoDistToGoal();float dist;
  Path *current=path;
  if(aircraft){const Coord3D *pos=(owner ? owner : owner)->getPosition();dist=current->computeFlightDistToGoal(pos,goalPos);}
  else{
   Rva003642DFResult info=current->rva00364521((const Rva0008BB38FloatField*)loco);
   goalPos=info.position;dist=((Rva00363D20*)&info)->rva00363D20();
  }
  if(path->m_pathTail)goalPos=path->m_pathTail->m_pos;
  float dx=goalPos.x-owner->getPosition()->x,dy=goalPos.y-owner->getPosition()->y;
  float distanceSquared=dx*dx+dy*dy;
  if(aircraft){if(dist*dist>distanceSquared)return (float)sqrt(distanceSquared);else return dist;}
  if(dist<10.0f || dist*dist<distanceSquared)return sqrtf(distanceSquared);
  return dist;
  }
 }
 default:break;
 }
 return 0.0f;
}
