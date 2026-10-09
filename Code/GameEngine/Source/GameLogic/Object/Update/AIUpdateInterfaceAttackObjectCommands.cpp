// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX- /I.
// Native268BD5..268CAC (215B), 26BCD2..26BE86 (436B), and
// 26BEE6..26BFD9 (243B). Old360B force extent included already-owned
// attackTeam117B26BFD9; the true RET12 boundary is checked independently.
// ZH AIUpdate.cpp privateAttackObject/privateForceAttackObject and BF1f989
// private-command siblings give the clear/goal/state/max-shot semantics.
// Target vtable C47B98 slots34/38 and command dispatch prove caller names.
// The extra holder274/linkID78/kind109 redirection and horde interfaces are
// derived from native215B helper; original helper name remains unknown.
// Private helper and both real callers belong in this TU: static noinline
// lets MSVC pass target in EAX plus two caller-popped stack arguments.
// A bool-returning status accessor keeps native dword-load/shift/test.
// Ordinary attack retains command in its parameter home (volatile parameter)
// and owner in EBX; force attack caches the owner before its helper call.
// Separate byte-exact Squad162 provider4D6DF3 supplies the group goal.
// All894B exact, no pins/asm/new shared headers or compiler override.
#include <new>
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"
extern GameLogic *TheGameLogic;
enum ObjectStatusTypes { STATUS38=38 };
enum WeaponSlotType { SLOT0=0 };
enum WeaponChoiceCriteria { CRITERION0=0 };
class Object; class Squad;
template<int N> class AttackSlots : public AttackSlots<N-1> {public:virtual void gap(char(*)[N])=0;};template<> class AttackSlots<0>{};
class AttackHordeView : public AttackSlots<18> {public:virtual Object *slot18(int,int,float,int,int)=0;
virtual void h19()=0;
virtual void h20()=0;
virtual void h21()=0;
virtual void h22()=0;
virtual void h23()=0;
virtual void h24()=0;
virtual void h25()=0;
virtual void h26()=0;
virtual void h27()=0;
virtual void h28()=0;
virtual void h29()=0;
virtual void h30()=0;
virtual void h31()=0;
virtual void h32()=0;
virtual void h33()=0;
virtual void h34()=0;
virtual void h35()=0;
virtual void h36()=0;
virtual void h37()=0;
virtual void h38()=0;
virtual void h39()=0;
virtual void h40()=0;
virtual void h41()=0;
virtual void h42()=0;
virtual void h43()=0;
virtual void h44()=0;
virtual void h45()=0;
virtual void h46()=0;
virtual void h47()=0;
virtual void h48()=0;
virtual void h49()=0;
virtual void h50()=0;
virtual void h51()=0;
virtual void h52()=0;
virtual void h53()=0;
virtual void h54()=0;
virtual void h55()=0;
virtual void h56()=0;
virtual void h57()=0;
virtual void h58()=0;
virtual void h59()=0;
virtual void h60()=0;
virtual void h61()=0;
virtual void h62()=0;
virtual void h63()=0;
virtual void h64()=0;
virtual void h65()=0;
virtual void h66()=0;
virtual void h67()=0;
virtual void h68()=0;
virtual void h69()=0;
virtual void h70()=0;
virtual void h71()=0;
virtual void h72()=0;
virtual void h73()=0;
virtual void h74()=0;
virtual void h75()=0;
virtual void h76()=0;
virtual void h77()=0;
virtual void h78()=0;
virtual void h79()=0;
virtual void h80()=0;
virtual void h81()=0;
virtual void h82()=0;
virtual void h83()=0;
virtual void h84()=0;
virtual void h85()=0;
virtual void h86()=0;
virtual void h87()=0;
virtual void h88()=0;
virtual void h89()=0;
virtual void h90()=0;
virtual void h91()=0;
virtual void h92()=0;
virtual void h93()=0;
virtual void h94()=0;
virtual void h95()=0;
virtual unsigned slot96(int) const=0;};
class AttackContainView : public AttackSlots<31> {public:virtual AttackHordeView *slot31()=0;};
class SpawnBehaviorInterface : public AttackSlots<3> {public:virtual void slot3(Object*,int,CommandSourceType)=0;};
class Rva0028B7AELeaGetter {public:void *get() const;bool testBit8()const{return (unsigned)((*(const unsigned*)get()>>8)&1);}};
class Rva002C9400ByteField {public:unsigned char get() const;};
class Weapon {public:char pad0[4];Rva002C9400ByteField *data;char pad8[0x20-8];int shots;char pad24[0x34-0x24];int maximum;};
class AttackTemplate {public:char pad0[0x112];unsigned char flag112;char pad113;unsigned flags114;};
class AttackAIGate {public:char pad0[0x34];int word34;};
class Object {public:bool testStatus(ObjectStatusTypes) const;bool chooseBestWeaponForTarget(const Object*,WeaponChoiceCriteria,CommandSourceType);const Weapon *getCurrentWeapon(WeaponSlotType*) const;SpawnBehaviorInterface *getSpawnBehaviorInterface()const;
char pad0[4];AttackTemplate *thing;char pad8[0x74-8];ObjectID id,linkedID;char pad7C[0x250-0x7C];AttackContainView *contain;void*body;AttackAIGate *ai;char pad25C[0x274-0x25C];Object *holder;char pad278[0x438-0x278];unsigned flags438;char pad43C[0x488-0x43C];ObjectID victim;
};
static __declspec(noinline) Object *Rva00268BD5(Object *target,Object *owner,bool *horde){
 if(!owner->testStatus(STATUS38)){
 Object *container=target->holder;
 if(container && (container->thing->flags114 & 0x2000))target=container;
 else {container=TheGameLogic->findObjectByID(target->linkedID);if(container && (container->thing->flags114 & 0x2000))target=container;}
 }else if(target->thing->flags114 & 0x2000){
 AttackContainView *contain=target->contain;
 if(contain){AttackHordeView *group=contain->slot31();if(group){
 if(group->slot96(0)>0){target=group->slot18(0,0,0.0f,0,0);if(!target)return 0;}else return 0;
 }}
 }
 *horde=(unsigned char)(target->thing->flags114>>13)&1;
 if((owner->thing->flags114 & 0x800000)||owner->testStatus(STATUS38))*horde=false;
 return target;
}
class Squad {public:Squad();virtual void *slot0(int);void rva004D6DF3(Object*,bool);char pad4[0x18];};
class AIStateMachine : public AttackSlots<5> {public:virtual void clear()=0;virtual void s6()=0;virtual void s7()=0;virtual void setState(int)=0;virtual void s9()=0;virtual void s10()=0;virtual void s11()=0;virtual void s12()=0;virtual void s13()=0;virtual void setGoalObject(Object*)=0;void setGoalSquad(const Squad*);};
class AIUpdateInterface : public AttackSlots<34> {public:char pad0[4];Object *owner;char padC[0x30-0xC];AIStateMachine *machine;char pad34[0x48-0x34];CommandSourceType source;char pad4C[0x1A4-0x4C];ObjectID forcedTarget;
protected:virtual void privateAttackObject(Object*,int,CommandSourceType);virtual void a35()=0;virtual void a36()=0;virtual void a37()=0;virtual void privateForceAttackObject(Object*,int,CommandSourceType);void playAttackVoiceResponse(Object*);
};
void AIUpdateInterface::privateAttackObject(Object *target,int shots,volatile CommandSourceType command){
 Object *obj=owner;
 if(((const Rva0028B7AELeaGetter*)obj)->testBit8()||!target||(obj->flags438&8))return;
 obj->chooseBestWeaponForTarget(target,(WeaponChoiceCriteria)5,command);
 Weapon *weapon=const_cast<Weapon*>(obj->getCurrentWeapon(0));
 obj->victim=INVALID_OBJECT_ID;
 if(command==0 && target->testStatus(STATUS38) && weapon && !weapon->data->get())obj->victim=target->id;
 if(obj->ai && obj->ai->word34)return;
 bool horde=false;target=Rva00268BD5(target,obj,&horde);if(!target)return;
 machine->clear();
 if(horde){Squad *squad=new Squad;squad->rva004D6DF3(target,true);machine->setGoalSquad(squad);source=command;machine->setState(23);::operator delete(squad?squad->slot0(0):0);}
 else{machine->setGoalObject(target);source=command;machine->setState(10);}
 if(weapon){weapon->maximum=shots;weapon->shots=0;if(weapon->data->get()&&(command==0||command==1))forcedTarget=target->id;}
 if(command==0||command==1)playAttackVoiceResponse(target);
 if(obj->thing->flag112&0x10){SpawnBehaviorInterface *spawn=obj->getSpawnBehaviorInterface();if(spawn)spawn->slot3(target,shots,command);}
}
void AIUpdateInterface::privateForceAttackObject(Object *target,int shots,CommandSourceType command){
 if(!target)return;
 if(((const Rva0028B7AELeaGetter*)owner)->testBit8())return;
 machine->clear();Object *obj=owner;bool horde=false;target=Rva00268BD5(target,obj,&horde);if(!target)return;
 if(horde){Squad *squad=new Squad;squad->rva004D6DF3(target,true);machine->setGoalSquad(squad);source=command;machine->setState(23);::operator delete(squad?squad->slot0(0):0);}
 else{machine->setGoalObject(target);source=command;machine->setState(11);}
 Weapon *weapon=const_cast<Weapon*>(owner->getCurrentWeapon(0));if(weapon){weapon->maximum=shots;weapon->shots=0;}
 if(command==0||command==1)playAttackVoiceResponse(target);
}
