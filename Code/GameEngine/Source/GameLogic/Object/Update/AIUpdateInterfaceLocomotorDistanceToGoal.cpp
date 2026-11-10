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
#include "../../../../Include/GameLogic/Module/Gen_000E5A50.h"
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
#include "../../../../Include/GameLogic/AIStateMachineClass.h"
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
struct Delta3 { float x,y,z; Delta3(const Coord3D &c):x(c.x),y(c.y),z(c.z){} void sub(const Coord3D &p){x-=p.x;y-=p.y;z-=p.z;} };
float AIUpdateInterface::getLocomotorDistanceToGoal(){
 Coord3D goalPos;
 switch(m_field1FC){
 case 0:case 3:return 0.0f;
 case 2:case 4:{
  const Coord3D *dest=&m_field200;const Coord3D *pos=m_object->getPosition();
  Delta3 d(*dest);d.sub(*pos);_ReadWriteBarrier();goalPos.x=d.x;goalPos.y=d.y;goalPos.z=d.z;
  float len=goalPos.length();return len;
 }
 case 1:{
  if(!m_path)return 100.0f;
  if(!m_curLocomotor)break;
  if(isCloseEnoughDist3D(m_curLocomotor)||(m_object->templ->m_kindof[0] & 0x2000000U)){
   const Object *obj=m_object;PathNode *last=m_path->m_pathTail;const Coord3D *p=&m_stateMachine->m_goalPosition;
   goalPos.x=p->x;goalPos.y=p->y;goalPos.z=p->z;
   if(last)goalPos=last->m_pos;
   return (float)sqrt(((const Gen_000E5A50*)obj)->Get3DCenterDistanceSquared((const BfmeVec3EJ*)&goalPos));
  } else {
  if(m_curLocomotor->m_template->type==5)break;
  bool aircraft=getTreatAsAircraftForLocoDistToGoal();float dist;
  Path *current=m_path;
  if(aircraft){const Coord3D *pos=(m_object ? m_object : m_object)->getPosition();dist=current->computeFlightDistToGoal(pos,goalPos);}
  else{
   Rva003642DFResult info=current->rva00364521((const Rva0008BB38FloatField*)m_curLocomotor);
   goalPos=info.position;dist=((Rva00363D20*)&info)->rva00363D20();
  }
  if(m_path->m_pathTail)goalPos=m_path->m_pathTail->m_pos;
  float dx=goalPos.x-m_object->getPosition()->x,dy=goalPos.y-m_object->getPosition()->y;
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
