// cl: /I. /O1 /G7 /arch:SSE /MD /EHsc
// Native34612C..346214 (232B RET0); WB E2C440 names AICombineState::internalUpdate.
// Called by the named combine-state onEnter at34FCAC; WB callgraph and
// target owner/goal flags establish the identity independently of old pins.
// No clean BF1/ZH method body exists at donor575ba2b04; native and WB bodies
// establish machine18/owner14/goalPosition20, Object position38/contain250/
// AI258/flags438, and contain31/Horde29,68 virtual slots.
// Combine/target role names follow the WB assertion and call relationships;
// precise virtual method names, access and full class extents remain inferred.
#include "Code/Libraries/Include/Lib/Coord3D.h"
typedef unsigned UnsignedInt;
enum StateReturnType{STATE_CONTINUE=0,STATE_SUCCESS=-1,STATE_FAILURE=-2};
class Object;
template<int N>class Slots:public Slots<N-1>{public:virtual void gap(char(*)[N]);};template<>class Slots<0>{};
class AIUpdateInterface:public Slots<143>{public:virtual int getCommandSource();};
class HordeContainInterface:public Slots<29>{public:virtual void combine(Object*,void*,bool);virtual void slot30();virtual void slot31();virtual void slot32();virtual void slot33();virtual void slot34();virtual void slot35();virtual void slot36();virtual void slot37();virtual void slot38();virtual void slot39();virtual void slot40();virtual void slot41();virtual void slot42();virtual void slot43();virtual void slot44();virtual void slot45();virtual void slot46();virtual void slot47();virtual void slot48();virtual void slot49();virtual void slot50();virtual void slot51();virtual void slot52();virtual void slot53();virtual void slot54();virtual void slot55();virtual void slot56();virtual void slot57();virtual void slot58();virtual void slot59();virtual void slot60();virtual void slot61();virtual void slot62();virtual void slot63();virtual void slot64();virtual void slot65();virtual void slot66();virtual void slot67();virtual void *getCombineTarget();};
class ContainModuleInterface:public Slots<31>{public:virtual HordeContainInterface*getHordeContainInterface();};
class Object{public:
 float rva00263763(const void*)const;
 bool cannotCombine()const{return (m_flags&1)!=0;}
 char pad00[0x38];Coord3D m_position;char pad44[0x250-0x44];ContainModuleInterface*m_contain;char pad254[4];AIUpdateInterface*m_ai;char pad25c[0x438-0x25c];unsigned char m_flags;
};
class StateMachine{public:Object*getGoalObject();char pad00[0x14];Object*m_owner;};
class ActionManager{public:bool Rva0041B94AGet(Object*,Object*,int);};extern ActionManager*TheActionManager;
extern "C" double __cdecl fabs(double);
class AICombineState{public:virtual ~AICombineState();StateReturnType internalUpdate();char pad04[0x18-4];StateMachine*m_machine;char pad1c[4];Coord3D m_goalPosition;};
StateReturnType AICombineState::internalUpdate(){
 Object *owner=m_machine->m_owner;Object *goal=m_machine->getGoalObject();
 if(owner->cannotCombine())return STATE_FAILURE;
 if(goal){
  if(goal->cannotCombine())return STATE_FAILURE;
  if(!TheActionManager->Rva0041B94AGet(owner,goal,owner->m_ai->getCommandSource()))return STATE_FAILURE;
  m_goalPosition=goal->m_position;
  float distance=owner->rva00263763(goal);
  if(2500.0f>distance){
   float height=(float)fabs(goal->m_position.z-owner->m_position.z);
   if(height<10.0f){
HordeContainInterface *horde=0;Object *other=goal;ContainModuleInterface *contain=owner->m_contain;if(contain)horde=contain->getHordeContainInterface();if(!horde){ContainModuleInterface *otherContain=goal->m_contain;if(otherContain){horde=otherContain->getHordeContainInterface();other=owner;}}
    if(horde){void *target=horde->getCombineTarget();if(target)horde->combine(other,target,false);}
   }
  }
 }else{return STATE_FAILURE;}
 return STATE_CONTINUE;
}
