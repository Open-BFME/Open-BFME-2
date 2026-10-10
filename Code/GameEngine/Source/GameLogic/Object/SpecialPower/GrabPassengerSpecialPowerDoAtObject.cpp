// cl: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG /I.
// Complete native4C504E..4C51A0 RET8,338B. WB lead names
// GrabPassengerSpecialPower::doSpecialPowerAtObject; neighbouring641B
// options dispatcher4C51A0 selects this slot11 of secondary interface+10.
// ZH SpecialPowerModule::doSpecialPowerAtObject supplies intent/trigger
// purpose and disabled/paused guards. BF2 horde-member selection, Defector27
// validation, bypass bit18 and status63 are independent native extensions.
// Numbered virtual slots are ABI views; no original method names are asserted.
// Accessed primary prefixes: moduleData4/owner8, interfacesC/10, paused1C;
// these mirror the already-verified neighbour and native accesses, not a
// reconstructed complete base extent. Object disabled mask1C8 is one DWORD.
// The selected child remains live through setStatus before assigning obj; this
// gives the native EBX reload. A barrier after forming the disabled-mask
// pointer selects native MOV ECX/ADD instead of MOV EAX/LEA.
// slot6 is the no-argument template getter: two arguments pushed BEFORE that
// virtual call remain for ActionManager's six-argument call (they are not
// arguments to the getter). Every direct helper is owned.
#include "Code/Libraries/Include/Lib/Coord3D.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Object;class SpecialPowerTemplate;class SpecialPowerModuleInterface;class Waypoint;
template<int N> class BitFlags {public:bool any()const;unsigned words[(N+31)/32];};
class Overridable {public:const Overridable *friend_getFinalOverride()const;};
class SpecialPowerTemplate:public Overridable {};
struct GrabFinalTemplateView {char head[0x1C];int type;};
enum SpecialPowerType { GRAB_POWER27=0x27 };
enum ObjectStatusTypes { GRAB_STATUS63=0x3F };
enum CommandSourceType { GRAB_SOURCE0=0,GRAB_SOURCE1=1 };
class Object {public:char head[0x1C8];BitFlags<11> disabled;public:bool isDisabled()const{return disabled.any();}SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType)const;void setStatus(ObjectStatusTypes,bool);};
class ActionManager {public:bool canDoSpecialPowerAtObject(const Object*,const Object*,CommandSourceType,const SpecialPowerTemplate*,unsigned,bool);};
extern ActionManager *TheActionManager;
class SpecialPowerModule;
class SpecialPowerModuleInterface {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual const SpecialPowerTemplate *s6()const;virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void doSpecialPowerAtObject(Object*,unsigned);};
class GrabHordeView {public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual Object *s18(bool,bool,float,int,int);
};
class GrabContainView {public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual GrabHordeView *s30();
};
struct GrabThingView {char head[0x115];unsigned char flag115;};
struct GrabObjectView {char head[4];GrabThingView *what;char rest8[0x38-8];Coord3D position;char rest44[0x250-0x44];GrabContainView *contain;};
struct GrabDataView {char head[0xC];bool startsAttack;};
class BehaviorModule {public:virtual ~BehaviorModule();protected:const GrabDataView *data;Object *owner;};
class BehaviorModuleInterface {public:virtual void anchor();};
class SpecialPowerModule:public BehaviorModule,public BehaviorModuleInterface,public SpecialPowerModuleInterface {
public:void initiateIntentToDoSpecialPower(const Object*,const Coord3D*,unsigned,const Waypoint*);void triggerSpecialPower(const Coord3D*);
protected:char spare14[8];int paused;Object *getOwner()const{return owner;}const GrabDataView *getData()const{return data;}
};
class GrabPassengerSpecialPower:public SpecialPowerModule {public:virtual void doSpecialPowerAtObject(Object*,unsigned);};

void GrabPassengerSpecialPower::doSpecialPowerAtObject(Object *obj,unsigned options) {
 if(!(options&0x40000)) {
  if(paused>0)return;
  Object *o=getOwner();const BitFlags<11> *disabled=&o->disabled;_ReadWriteBarrier();if(disabled->any())return;
 }
 if(((GrabObjectView*)obj)->what->flag115&0x20) {
  GrabHordeView *horde=((GrabObjectView*)obj)->contain->s30();
  if(horde) {
   Object *selected=horde->s18(true,false,0.0f,0,0);if(!selected)return;
   if(((const GrabFinalTemplateView*)s6()->friend_getFinalOverride())->type==0x27) {
    SpecialPowerModuleInterface *power=getOwner()->findSpecialPowerModuleInterface(GRAB_POWER27);if(!power)return;
    if(!TheActionManager->canDoSpecialPowerAtObject(getOwner(),obj,(CommandSourceType)((options>>18)&1),power->s6(),options,true))return;
   }
   selected->setStatus(GRAB_STATUS63,true);obj=selected;
  }
 }else {
  if(((const GrabFinalTemplateView*)s6()->friend_getFinalOverride())->type==0x27) {
   SpecialPowerModuleInterface *power=getOwner()->findSpecialPowerModuleInterface(GRAB_POWER27);if(!power)return;
   if(!TheActionManager->canDoSpecialPowerAtObject(getOwner(),obj,(CommandSourceType)((options>>18)&1),power->s6(),options,true))return;
  }
 }
 SpecialPowerModule *base=this;
 base->initiateIntentToDoSpecialPower(obj,0,options,0);
 if(!getData()->startsAttack)base->triggerSpecialPower(&((GrabObjectView*)obj)->position);
}
