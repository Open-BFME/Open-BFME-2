// ?rva004C5BE3@SiegeDeploySpecialPower@@AAEXH@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /Ob2 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// WB1264270 is the semantic guide for SiegeDeploySpecialPower::setPhase.
// Retail4C5BE3 proves primary this, phase38/frame3C/target40 and Object condition offsets.
#include "../../../../Include/GameLogic/ContainmentListView.h"
#include "../../../Common/GameLogicObjectLookupView.h"
namespace _STL {
template<class T,class Traits> static inline bool operator!=(const _List_iterator<T,Traits>&a,const _List_iterator<T,Traits>&b){return a._M_node!=b._M_node;}
template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();
}
enum ObjectStatusTypes { STATUS_ZERO=0 };
enum DisabledType { DISABLED_ZERO=0 };
enum CommandSourceType { SOURCE_ZERO=0 };
enum AttitudeType { ATTITUDE_ZERO=0 };
class Object;
class Rva001E46E1 {public:void rva001E53D8(float,Object*);};
struct Rva0028AC4EEntry;
class Module;
class DynamicPortalBehaviour {public:static Module *rva004608E0(Object*);};
class Rva00460F90 {public:void rva00460F90();};
class AICommandInterface {public:void aiEvacuate(bool,CommandSourceType);void aiExit(Object*,CommandSourceType);};
class SiegePhaseAIHead {unsigned char pad[0x20];};
class AIUpdateInterface : public SiegePhaseAIHead,public AICommandInterface {public:AttitudeType getAttitude()const;void rva0026DE3B(int);};
template<int N> class SiegePhaseSlots : public SiegePhaseSlots<N-1> {public:virtual void gap(char(*)[N])=0;};
template<> class SiegePhaseSlots<0> {};
class SiegePhaseContain : public SiegePhaseSlots<70> {public:virtual Rva0036AE51ListView slot70()=0;virtual Rva0036AE51ListView slot71()=0;};
struct SiegePhaseConditions {unsigned words[19];__forceinline unsigned test(int i)const{return words[i>>5]&(1u<<(i&31));}__forceinline void set(int i){words[i>>5]|=1u<<(i&31);}__forceinline void clear(int i){words[i>>5]&=~(1u<<(i&31));}};
class Object {
public:void setStatus(ObjectStatusTypes,bool);void setDisabledUntil(DisabledType,unsigned);void rva0028AE6D();const Rva0028AC4EEntry *rva0028AC4E()const;
 unsigned char pad[0x10c];SiegePhaseConditions conditions;unsigned char pad158[0x250-0x158];SiegePhaseContain *contain;unsigned char pad254[4];AIUpdateInterface *ai;
};
struct SiegePhaseData {unsigned char pad[0x18];unsigned delay,disabledDuration;bool evacuate,exit;};
extern GameLogic *TheGameLogic;
class SiegeDeploySpecialPower {
public:void rva004C573C();
private:void rva004C5BE3(int);
public:
 unsigned vptr;const SiegePhaseData *data;Object *object;unsigned char padC[0x38-0xc];int phase;unsigned frame,target;
};
void SiegeDeploySpecialPower::rva004C5BE3(int next)
{
 if(next==phase)return;
 Object *obj=object;
 switch(phase){
 case 2:if(obj->conditions.test(96)){obj->conditions.clear(96);obj->rva0028AE6D();}break;
 case 3:obj->setStatus((ObjectStatusTypes)59,false);if(obj->conditions.test(100)){obj->conditions.clear(100);obj->rva0028AE6D();}rva004C573C();break;
 case 4:target=0;if(obj->conditions.test(94)){obj->conditions.clear(94);obj->rva0028AE6D();}break;
 }
 phase=next;frame=0;
 switch(phase){
 case 2:{
  if(!obj->conditions.test(96)){obj->conditions.set(96);obj->rva0028AE6D();}
  if(obj->rva0028AC4E())((Rva001E46E1*)obj->rva0028AC4E())->rva001E53D8(0.0f,obj);
  SiegePhaseContain *contained=obj->contain;
  if(contained){Rva0036AE51ListView view=contained->slot70();for(ContainmentList::iterator it=view.b->begin();it!=view.b->end();++it){Object *child=(Object*)containmentFirstWord(*it);if(!child->conditions.test(96)){child->conditions.set(96);child->rva0028AE6D();}}}
  break;}
 case 3:
  obj->setStatus((ObjectStatusTypes)59,true);
  if(!obj->conditions.test(100)){obj->conditions.set(100);obj->rva0028AE6D();}
  if(obj->conditions.test(61)){obj->conditions.clear(61);obj->rva0028AE6D();}
  {Module *portal=DynamicPortalBehaviour::rva004608E0(obj);if(portal)((Rva00460F90*)portal)->rva00460F90();}
  if(data->evacuate){AIUpdateInterface *ai=obj->ai;if(ai)ai->aiEvacuate(0,(CommandSourceType)2);}
  if(data->exit){SiegePhaseContain *contain=object->contain;if(contain){ContainmentList list=contain->slot71().rva0036AE51();for(ContainmentList::iterator it=list.begin();it!=list.end();++it){Object *child=(Object*)containmentFirstWord(*it);AIUpdateInterface *ai=child->ai;if(ai){ai->rva0026DE3B(object->ai->getAttitude());Object *owner=object;child->ai->aiExit(owner,(CommandSourceType)2);}}}}
  break;
 case 4:
  if(!obj->conditions.test(94)){obj->conditions.set(94);obj->rva0028AE6D();}
  obj->setDisabledUntil((DisabledType)8,TheGameLogic->getFrame()+data->disabledDuration);break;
 }
}
