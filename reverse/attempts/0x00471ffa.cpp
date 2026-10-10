// ?attackTargetNow@HordeContain@@UAEXPAVObject@@H@Z
// partial score=0.9554964731 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native471FFA..472235 571B RET8; secondary interfaceC44C58 slot1 and WB10BF040 attackTargetNow.
// Target layouts/ABI from native and existing HordeContain interface TU; no reference body supplies this method.
#include <list>
#include <map>
#include <set>
struct Coord3D {float x,y,z;};
enum CommandSourceType {CMD_FROM_AI=2};
enum ObjectStatusTypes {OBJECT_STATUS_NONE=0};
enum WeaponSlotType;
class Object;class Weapon;class Rva00468CB6A;
class Rva002C9400ByteField {public:unsigned char get()const;};
class Weapon {public:float getAttackRange(const Object*)const;char pad00[4];const Rva002C9400ByteField*data;};
class AICommandInterface {public:virtual void anchor();void aiIdle(CommandSourceType);void rva0026C2D9(Object*,int,CommandSourceType);};
class AIUpdateInterface {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual void slot87();
virtual void slot88();
virtual void slot89();
virtual void slot90();
virtual void slot91();
virtual void slot92();
virtual void slot93();
virtual void slot94();
virtual void slot95();
virtual void slot96();
virtual void slot97();
virtual void slot98();
virtual void slot99();
virtual void slot100();
virtual void slot101();
virtual void slot102();
virtual void slot103();
virtual void slot104();
virtual void slot105();
virtual void slot106();
virtual void slot107();
virtual void slot108();
virtual void slot109();
virtual void slot110();
virtual void slot111();
virtual void slot112();
virtual bool slot113();
bool isMoving()const;char pad04[0x20-4];AICommandInterface command;};
class AttackTargetInterface {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual Object*choose(int,const Coord3D*,float,Object*,bool);
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual Object*fallback();
};
struct ThingTemplate {char pad[0x115];unsigned char flag115;};
class Object {public:
 Weapon*getCurrentWeapon(WeaponSlotType*slot=0);bool testStatus(ObjectStatusTypes)const;void rva00295F05(bool);void*rva0028C197()const;
 int getID()const{return id;}
 char pad00[4];const ThingTemplate*data;char pad08[0x38-8];Coord3D pos;char pad44[0x74-0x44];int id;char pad78[0x258-0x78];AIUpdateInterface*ai;char pad25C[0x274-0x25C];Object*container;
};
class AI {public:static bool rva002FE193(Object*,Object*);};
struct Rva0046247DPair {void*first;const _STL::list<Object*>*second;};
class Rva0046247D {public:void rva0046247D(Rva0046247DPair&);};
class Rva0046D946 {public:Object*rva0046D946(Object*);};
struct HordeData {char pad[0x1B8];_STL::map<int,int> keys;};
class HordePrimary {public:virtual void anchor();const HordeData*data;Object*owner;char pad0C[0x11C-0x0C];};
class HordeIface {public:virtual void slot0();virtual void attackTargetNow(Object*,int);virtual void slot2();virtual void slot3();virtual void reset(bool);};
struct HordeSlot {int key;char remainder[24];};
class HordeContain:public HordePrimary,public HordeIface {public:
 virtual void attackTargetNow(Object*,int);unsigned char usingMeleeAttack();bool rva00468CB6(Rva00468CB6A*,Object*);
 bool moving;char pad121[0x170-0x121];_STL::set<int> memberSetView;_STL::map<int,int> memberSlots;HordeSlot*slots;HordeSlot*end;HordeSlot*cap;
};
void HordeContain::attackTargetNow(Object*target,int select)
{
 if(usingMeleeAttack())return;
 if(memberSetView.size()!=0)reset(false);
 Rva0046247DPair members;
 ((Rva0046247D*)(HordePrimary*)this)->rva0046247D(members);
 const _STL::map<int,int>*keys=&data->keys;
 Object*container=(target->data->flag115&0x20)?target:target->container;
 Object*only=0;
 if(select==1)only=((Rva0046D946*)(HordePrimary*)this)->rva0046D946(target);
 _STL::list<Object*>::const_iterator it=members.second->begin();
 while(it!=members.second->end()){
  Object*obj=*it;
  if(!only||obj==only){
   int id=obj->getID();
   if(memberSlots.find(id)!=memberSlots.end()){
    AIUpdateInterface*ai=obj->ai;
    if(ai&&!ai->isMoving()){
     if(obj->getCurrentWeapon()&&obj->getCurrentWeapon()->data->get()){
      if(ai->slot113())ai->command.aiIdle(CMD_FROM_AI);
      if(!obj->testStatus((ObjectStatusTypes)28))obj->rva00295F05(false);
     }else{
      int memberID=obj->getID();
      int key=slots[memberSlots.find(memberID)->second].key;
      if(keys->find(key)!=keys->end()&&!rva00468CB6((Rva00468CB6A*)ai,target)){
       Object*chosen=target;
       Weapon*weapon=obj->getCurrentWeapon();
       if(container){
        AttackTargetInterface*contain=(AttackTargetInterface*)container->rva0028C197();
        if(contain){
         float range=0.0f;
         if(weapon&&!weapon->data->get())range=weapon->getAttackRange(obj);
         chosen=contain->choose(0,&obj->pos,range,obj,false);
         if(!chosen)chosen=contain->fallback();
        }
       }
       if(AI::rva002FE193(obj,chosen))ai->command.rva0026C2D9(chosen,0x7FFFFFFF,CMD_FROM_AI);
       else moving=true;
      }
     }
    }
   }
  }
  ++it;
 }
}
