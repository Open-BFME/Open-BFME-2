// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// Native4C8C78..4C8D1B RET4; slot10 of secondary table85E828 installed by rowed HordeDispatch ctor4C89E6 and primary85E88C pool-key slot4 points named string-key body4C8A34. Thus old Defector identity refuted; exact163 dispatch propagates options to contained children template virtual6 through native list-fill67; rowed base49490F lookup28BB9E and containment28C197 all resolve. Visible real list-base constructor permits native empty allocator argument reuse; no new pins; original intermediate full layout remains opaque
// stlport
#include <list>
class Object;
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class SpecialPowerTemplate;
class SpecialPowerModuleInterface;
struct ThingTemplate {char p00[0x115];unsigned char flag;};
class BfmeVec3EJ {public:float x,y,z;};
class Gen_000E5A50 {public:float bfmeDistanceSquared(const BfmeVec3EJ*)const;};
class Object {public:
 void *rva0028C197()const;
 SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate*)const;
 const BfmeVec3EJ *getPosition()const {return &position;}
 char p00[4];ThingTemplate *data;char p08[0x38-8];BfmeVec3EJ position;
};
namespace _STL {

template<> _List_base<Object*,allocator<Object*> >::~_List_base();
}
#define V(n) virtual void s##n()=0;
class ContainInterface {public:
V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64) V(65) V(66) 
virtual void getContained(_STL::list<Object*>&)=0;
};
class ObjectModule {public:virtual void primaryAnchor();char *moduleData;Object *object;};
class BehaviorModuleOther {public:virtual void secondaryAnchor();};
class BehaviorModule:public ObjectModule,public BehaviorModuleOther {};
class SpecialPowerModuleInterface {public:
V(00) V(01) V(02) V(03) V(04) V(05)
virtual const SpecialPowerTemplate *getTemplate()const=0;
V(07) V(08) V(09)
virtual void doSpecialPower(unsigned)=0;
virtual void doSpecialPowerAtObject(Object*,unsigned)=0;
V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
virtual ObjectID lastTarget()const=0;
};
#undef V
class SpecialPowerModule:public BehaviorModule,public SpecialPowerModuleInterface {public:
 virtual void doSpecialPower(unsigned);
 virtual void doSpecialPowerAtObject(Object*,unsigned);
};
class HordeDispatchSpecialPower:public SpecialPowerModule {public:
 virtual void doSpecialPower(unsigned);
 virtual void doSpecialPowerAtObject(Object*,unsigned);
};
void HordeDispatchSpecialPower::doSpecialPower(unsigned options){
 Object *owner=object;
 if(!owner || !(owner->data->flag&0x20))return;
 ContainInterface *contain=(ContainInterface*)owner->rva0028C197();
 if(!contain)return;
 SpecialPowerModule::doSpecialPower(options);
 const SpecialPowerTemplate *power=getTemplate();
 _STL::list<Object*> list;
 contain->getContained(list);
 for(_STL::list<Object*>::iterator i=list.begin();i!=list.end();++i){
 SpecialPowerModuleInterface *module=(*i)->getSpecialPowerModule(power);
 if(module)module->doSpecialPower(options);
 }
}
