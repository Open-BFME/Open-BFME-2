// cl:  /O1 /G7 /arch:SSE /MD /EHsc
// Native34612C..346214 (232B RET0); WB E2C440 names AICombineState::internalUpdate.
// Called by the named combine-state onEnter at34FCAC; WB callgraph and
// target owner/goal flags establish the identity independently of old pins.
// No clean BF1/ZH method body exists at donor575ba2b04; native and WB bodies
// establish machine18/owner14/goalPosition20, Object position38/contain250/
// AI258/flags438, and contain31/Horde29,68 virtual slots.
// Combine/target role names follow the WB assertion and call relationships;
// precise virtual method names, access and full class extents remain inferred.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef unsigned UnsignedInt;
#include "../../../Include/Common/StateMachineClass.h"
class Object;
#include "../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../Include/GameLogic/Module/HordeContainInterface.h"
#include "../../../Include/GameLogic/Module/ContainModule.h"
class Object{public:
 float rva00263763(const void*)const;
 bool cannotCombine()const{return (m_flags&1)!=0;}
 char pad00[0x38];Coord3D m_position;char pad44[0x250-0x44];ContainModuleInterface*m_contain;char pad254[4];AIUpdateInterface*m_ai;char pad25c[0x438-0x25c];unsigned char m_flags;
};
#include "../../../Include/GameLogic/ActionManager.h"
extern ActionManager*TheActionManager;
#include <math.h>
class AICombineState{public:virtual ~AICombineState();StateReturnType internalUpdate();char pad04[0x18-4];StateMachine*m_machine;char pad1c[4];Coord3D m_goalPosition;};
StateReturnType AICombineState::internalUpdate(){
 Object *owner=m_machine->m_owner;Object *goal=m_machine->getGoalObject();
 if(owner->cannotCombine())return STATE_FAILURE;
 if(goal){
  if(goal->cannotCombine())return STATE_FAILURE;
  if(!TheActionManager->Rva0041B94AGet(owner,goal,owner->m_ai->vslot143()))return STATE_FAILURE;
  m_goalPosition=goal->m_position;
  float distance=owner->rva00263763(goal);
  if(2500.0f>distance){
   float height=(float)fabs(goal->m_position.z-owner->m_position.z);
   if(height<10.0f){
HordeContainInterface *horde=0;Object *other=goal;ContainModuleInterface *contain=owner->m_contain;if(contain)horde=contain->slot31();if(!horde){ContainModuleInterface *otherContain=goal->m_contain;if(otherContain){horde=otherContain->slot31();other=owner;}}
    if(horde){void *target=horde->getCombineTarget();if(target)horde->combine(other,target,false);}
   }
  }
 }else{return STATE_FAILURE;}
 return STATE_CONTINUE;
}
