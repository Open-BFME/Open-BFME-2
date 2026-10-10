// ?getLocomotorDistanceToGoal@AIUpdateInterface@@QAEMXZ
// partial score=0.9401185770750988 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?getLocomotorDistanceToGoal@AIUpdateInterface@@QAEMXZ
// partial score=0.9088476740650654 date=2026-10-09
// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /GX-
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include <math.h>
class BfmeVec3EJ;
class Gen_000E5A50 { public: float bfmeDistanceSquared(const BfmeVec3EJ*)const; };
class ThingTemplate { public: char pad[0x10B];unsigned char kinds; };
class Object { public: char pad[4];ThingTemplate *templ; char pad8[0x38-8];Coord3D position; const Coord3D*getPosition()const{return &position;} };
class LocomotorTemplate {public:char pad[0x74];int type;};
class Locomotor {public: char pad[4];LocomotorTemplate*templ;char pad8[0x44-8];unsigned int flags;bool isCloseEnoughDist3D()const{return (flags>>10)&1;} };
struct PathNode {char pad[0xC];Coord3D position;};
struct Rva003642DFNode;
struct Rva003642DFResult { Rva003642DFResult();Rva003642DFNode*node;Coord3D position; };
class Rva00363D20 {public:double rva00363D20();};
class Rva0008BB38FloatField;
class Path {public:float computeFlightDistToGoal(const Coord3D*,Coord3D&);Rva003642DFResult rva00364521(const Rva0008BB38FloatField*);char pad[8];PathNode*tail;};
class StateMachine {public:char pad[0x24];Coord3D goal;const Coord3D*getGoalPosition()const{return &goal;} };
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
float AIUpdateInterface::getLocomotorDistanceToGoal(){
 Coord3D goalPos;
 switch(goalType){
 case 2:case 4:{
  const Coord3D *dest=&goal;const Coord3D *pos=owner->getPosition();
  float x=dest->x,y=dest->y,z=dest->z;y-=pos->y;z-=pos->z;_ReadWriteBarrier();x-=pos->x;goalPos.x=x;goalPos.y=y;goalPos.z=z;return goalPos.length();
 }
 case 1:{
  if(!path)return 100.0f;
  if(!loco)break;
  if(loco->isCloseEnoughDist3D()||(owner->templ->kinds&2)){
   const Object *obj=owner;PathNode *last=path->tail;const Coord3D *p=machine->getGoalPosition();
   goalPos.x=p->x;goalPos.y=p->y;goalPos.z=p->z;
   if(last)goalPos=last->position;
   return (float)sqrt(((const Gen_000E5A50*)obj)->bfmeDistanceSquared((const BfmeVec3EJ*)&goalPos));
  }
  if(loco->templ->type!=5){
  bool aircraft=getTreatAsAircraftForLocoDistToGoal();float dist;
  Path *current=path;
  if(aircraft){const Coord3D *pos=(owner ? owner : owner)->getPosition();dist=current->computeFlightDistToGoal(pos,goalPos);}
  else{
   Rva003642DFResult info=current->rva00364521((const Rva0008BB38FloatField*)loco);
   goalPos=info.position;dist=((Rva00363D20*)&info)->rva00363D20();
  }
  if(path->tail)goalPos=path->tail->position;
  float dx=goalPos.x-owner->getPosition()->x,dy=goalPos.y-owner->getPosition()->y;
  float distanceSquared=dx*dx+dy*dy;
  if(aircraft){if(dist*dist>distanceSquared)return (float)sqrt(distanceSquared);else return dist;}
  if(dist<10.0f || dist*dist<distanceSquared)return sqrtf(distanceSquared);
  return dist;
 } break;
 }
 case 0:case 3:return 0.0f;
 default:break;
 }
 return 0.0f;
}
