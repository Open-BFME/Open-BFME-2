// ?update@SiegeDeploySpecialPowerUpdateReceiver@@QAE?AW4UpdateSleepTime@@XZ
// partial score=0.86 date=2026-10-09
// cl: /O1 /Ob2 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// WB1264270 is the semantic guide for SiegeDeploySpecialPower::setPhase.
// Retail4C5BE3 proves primary this, phase38/frame3C/target40 and Object condition offsets.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include <math.h>
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
class AICommandInterface {public:void aiEvacuate(bool,CommandSourceType);void aiExit(Object*,CommandSourceType);void rva0045003E(int,CommandSourceType);void aiMoveToPosition(const Coord3D*,CommandSourceType);void aiFacePosition(const Coord3D*,int);};
class SiegePhaseAIHead {unsigned char pad[0x20];};
class AIUpdateInterface : public SiegePhaseAIHead,public AICommandInterface {public:AttitudeType getAttitude()const;void rva0026DE3B(int);void ignoreObstacle(const Object*);};
template<int N> class SiegePhaseSlots : public SiegePhaseSlots<N-1> {public:virtual void gap(char(*)[N])=0;};
template<> class SiegePhaseSlots<0> {};
class SiegePhaseContain : public SiegePhaseSlots<70> {public:virtual Rva0036AE51ListView slot70()=0;virtual Rva0036AE51ListView slot71()=0;};
struct SiegePhaseConditions {unsigned words[19];__forceinline unsigned test(int i)const{return words[i>>5]&(1u<<(i&31));}__forceinline void set(int i){words[i>>5]|=1u<<(i&31);}__forceinline void clear(int i){words[i>>5]&=~(1u<<(i&31));}};
class Drawable;class Thing {public:Drawable *getDrawable()const;};
class Object : public Thing {
public:float GetRelativeAngle(const Coord3D*)const;bool rva0028B35B(const Object*)const;void setStatus(ObjectStatusTypes,bool);void setDisabledUntil(DisabledType,unsigned);void rva0028AE6D();const Rva0028AC4EEntry *rva0028AC4E()const;
 unsigned char pad[0x38];Coord3D position;unsigned char pad44[0x10c-0x44];SiegePhaseConditions conditions;unsigned char pad158[0x250-0x158];SiegePhaseContain *contain;unsigned char pad254[4];AIUpdateInterface *ai;unsigned char pad25c[0x438-0x25c];unsigned char privateStatus;
};
struct SiegePhaseData {unsigned char pad[0x18];unsigned delay,disabledDuration;bool evacuate,exit;};
extern GameLogic *TheGameLogic;
struct Rva004598F2Point {Rva004598F2Point(){}Rva004598F2Point(const Coord3D&o):x(o.x),y(o.y),z(o.z){}Rva004598F2Point(const Rva004598F2Point&o):x(o.x),y(o.y),z(o.z){}float x,y,z;};
class SiegeDeploySpecialPowerUpdateReceiver;
class SiegeDeploySpecialPower {
 friend class SiegeDeploySpecialPowerUpdateReceiver;
public:void rva004C573C();void rva004C5E62();Rva004598F2Point computeApproachPoint(Object*,Rva004598F2Point*,bool*);
private:void rva004C5BE3(int);
public:
 unsigned vptr;const SiegePhaseData *data;Object *object;unsigned char padC[0x38-0xc];int phase;unsigned frame,target;unsigned char pad44[0x54-0x44];Rva004598F2Point approach;bool turn;unsigned char pad61[3];Coord3D direction;bool stop;
};

class Rva00460DF6 {public:bool rva00460DF6(const Coord3D*);};
class SiegeUpdateAI : public SiegePhaseSlots<110> {
public:virtual bool slot110()=0;
virtual void slot111()=0;
virtual void slot112()=0;
virtual void slot113()=0;
virtual void slot114()=0;
virtual void slot115()=0;
virtual void slot116()=0;
virtual void slot117()=0;
virtual void slot118()=0;
virtual void slot119()=0;
virtual void slot120()=0;
virtual void slot121()=0;
virtual void slot122()=0;
virtual void slot123()=0;
virtual void slot124()=0;
virtual void slot125()=0;
virtual void slot126()=0;
virtual void slot127()=0;
virtual void slot128()=0;
virtual void slot129()=0;
virtual void slot130()=0;
virtual void slot131()=0;
virtual void slot132()=0;
virtual void slot133()=0;
virtual void slot134()=0;
virtual void slot135()=0;
virtual void slot136()=0;
virtual void slot137()=0;
virtual void slot138()=0;
virtual void slot139()=0;
virtual void slot140()=0;
virtual void slot141()=0;
virtual void slot142()=0;
virtual int slot143()=0;
};
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff };
class SiegeDeploySpecialPowerUpdateReceiver {public:UpdateSleepTime update();unsigned char pad[0x28];int phase;unsigned frame,target;unsigned char pad34[0x44-0x34];Rva004598F2Point approach;bool turn;unsigned char pad51[3];Coord3D direction;bool stop;};
UpdateSleepTime SiegeDeploySpecialPowerUpdateReceiver::update()
{
 Object *obj=*(Object**)((char*)this-8);
 if(obj->privateStatus&1){((SiegeDeploySpecialPower*)((char*)this-0x10))->rva004C573C();return UPDATE_SLEEP_FOREVER;}
 if(!phase)return UPDATE_SLEEP_FOREVER;
 if(stop){((SiegeDeploySpecialPower*)((char*)this-0x10))->rva004C5BE3(4);stop=false;return UPDATE_SLEEP_NONE;}
 AIUpdateInterface *ai=obj->ai;
 SiegeUpdateAI *view=(SiegeUpdateAI*)ai;
 if(!ai){((SiegeDeploySpecialPower*)((char*)this-0x10))->rva004C5E62();return UPDATE_SLEEP_FOREVER;}
 if(!obj->getDrawable())return UPDATE_SLEEP_FOREVER;
 if((!view->slot110() && view->slot143()!=2) || (view->slot110() && view->slot143()==0)){((SiegeDeploySpecialPower*)((char*)this-0x10))->rva004C5E62();return UPDATE_SLEEP_FOREVER;}
 Object *targetObject=0;
 if(target){
  targetObject=TheGameLogic->findObjectByID((ObjectID)target);
  if(!targetObject || (targetObject->privateStatus&1)){
   targetObject=0;target=0;
   if(phase==3)((SiegeDeploySpecialPower*)((char*)this-0x10))->rva004C5BE3(4);
  }
 }
 if(!targetObject)((SiegeDeploySpecialPower*)((char*)this-0x10))->rva004C5BE3(4);
 switch(phase){
 case 0:targetObject->setStatus((ObjectStatusTypes)64,false);return UPDATE_SLEEP_FOREVER;
 case 1:{
   Coord3D *offset=&direction;
   Rva004598F2Point face(obj->position);face.x+=offset->x;face.y+=offset->y;face.z+=offset->z;
   if(fabs(obj->GetRelativeAngle((const Coord3D*)&face))<0.15f && (obj->rva0028B35B(targetObject)||view->slot110())){
    Module *portal=DynamicPortalBehaviour::rva004608E0(obj);
    if(portal && ((Rva00460DF6*)portal)->rva00460DF6(0)){
     view->slot136();ai->rva0045003E(0,(CommandSourceType)2);((SiegeDeploySpecialPower*)((char*)this-0x10))->rva004C5BE3(2);break;
    }
   }
   if(view->slot110()){
    ai->ignoreObstacle(targetObject);
    turn=!turn;
    if(turn){
     bool docked=false;
     approach=((SiegeDeploySpecialPower*)((char*)this-0x10))->computeApproachPoint(targetObject,(Rva004598F2Point*)offset,&docked);
     if(docked)ai->aiMoveToPosition((const Coord3D*)&approach,(CommandSourceType)2);
    }else{
     face.x=obj->position.x;face.y=obj->position.y;face.z=obj->position.z;face.x+=offset->x;face.y+=offset->y;face.z+=offset->z;
     ai->aiFacePosition((const Coord3D*)&face,(CommandSourceType)2);
    }
   }
   break;}
 case 2:if(++frame>=(*(const SiegePhaseData**)((char*)this-0xc))->delay)((SiegeDeploySpecialPower*)((char*)this-0x10))->rva004C5BE3(3);break;
 case 4:((SiegeDeploySpecialPower*)((char*)this-0x10))->rva004C5BE3(0);break;
 }
 return UPDATE_SLEEP_NONE;
}
