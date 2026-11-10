// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// BFME 1 semantic donor: 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/GameLogic/AI/AIAttackState_onEnter.cpp; ZH AIStates.cpp.
// Target identity: WB E23470 names AIAttackState::onEnter and C13B78 slot4
// points to the complete retail34B502..34B889 RET0, 903 bytes.
// Target deltas: null-owner failure; selector kinds0..8; kind bytes108/10B/115;
// template byte82 and range148; extra condition bit37 and attack voice response
// for player field5C==1. Consumed offsets, slots and status ordinals are native
// evidence. Donor supplies the victim/weapon/state semantics; opaque predicate
// names and flag48/49 meanings remain unproven. Current-state ID fallback999999
// is inlined as retail does. Declaration-only prefix views emit no vtables.
// Canonical AsciiString and Coord3D; all direct callees retain existing owners.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
enum WeaponSlotType {};
enum MoodMatrixAction {};
enum Relationship {};
enum ObjectStatusTypes {};
#include "../../../Include/Common/StateMachineClass.h"
class Object; class Team; class Player;
#include "../../../Include/GameLogic/Module/AIUpdate.h"
struct AttackThingTemplateView { char pad[0x108]; unsigned char kinds[0x20]; };
#include "../../../Include/GameLogic/WeaponTemplate.h"
#include "../../../Include/GameLogic/Weapon.h"
class Object {
public:
 const Weapon *getCurrentWeapon(WeaponSlotType*) const;
 bool isOutOfAmmo() const;
 int rva0028B38D() const;
 bool testStatus(ObjectStatusTypes) const;
 void setStatus(ObjectStatusTypes,bool);
 Object *adjustVictim(Object*,bool,int);
 Relationship getRelationship(const Object*) const;
 void rva0028AE6D();
 Player *getControllingPlayer() const;
 char pad00[4]; AttackThingTemplateView *m_template;
 char pad08[0x30]; Coord3D position;
 char pad44[0x30]; unsigned id;
 char pad78[0x94]; unsigned conditions[19];
 char pad158[0x100]; AIUpdateInterface *ai;
 char pad25c[0xA8]; Team *team;
 char pad308[0x130]; unsigned char status438;
};
#include "../../../Include/Common/Rva002C9400ByteField.h"
class Rva002C940EByteField { public: unsigned char get() const; };
class Rva0028B7B5CmpBoolField { public: bool get() const; };
struct CurrentStateIDView { char pad[4]; unsigned id; };
#include "../../../Include/Common/StateMachineClass.h"
class AttackExitConditionsInterface { public: virtual bool shouldExit(const StateMachine*) const; };
struct AttackControllingPlayerView { char pad[0x5C]; unsigned type; };
class AIAttackState {
public:
 virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
 virtual StateReturnType onEnter();
 bool rva003413B2(); // ZH chooseWeapon
 StateMachine *getMachine() const { return machine; }
 char pad04[0x14];StateMachine *machine;char pad1c[8];StateMachine *attackMachine;
 AttackExitConditionsInterface *parameters;Team *victimTeam;Coord3D victimPos;
 AsciiString lockedWeapon;
 bool follow,attackingObject,force;char pad43;
 unsigned objectID44;unsigned char flag48;bool flag49;char pad4a[2];unsigned machineType;
protected: void createAttackMachine(Object*);
};
StateReturnType AIAttackState::onEnter() {
 Object *source=machine->m_owner;
 Object *victim=machine->getGoalObject();
 if(!source) return STATE_FAILURE;
 AIUpdateInterface *ai=source->ai;
 if(!(ai->getMoodMatrixActionAdjustment((MoodMatrixAction)2)&1)) return STATE_SUCCESS;
 if(parameters && parameters->shouldExit(getMachine())) return STATE_SUCCESS;
 if(source->isOutOfAmmo() && !(source->m_template->kinds[3]&2)) return STATE_FAILURE;
 if(!rva003413B2()) return STATE_FAILURE;
 Weapon *weapon=const_cast<Weapon*>(source->getCurrentWeapon(0));
 if(!weapon) return STATE_FAILURE;
 flag48=reinterpret_cast<const Rva002C9400ByteField*>(weapon->m_template)->get();
 unsigned char melee=0;
 if(attackingObject && victim) {
  melee=reinterpret_cast<const Rva002C9400ByteField*>(weapon->m_template)->get();
  if(victim->m_template->kinds[13]&0x20) {
   victim=victim->adjustVictim(source,1,0);
   source->ai->setCurrentVictim(victim);
  }
 }
 if(source->m_template->kinds[0]&4) melee=0;
 if((unsigned char)source->rva0028B38D()) machineType=0;
 else if(source->testStatus((ObjectStatusTypes)37)) machineType=5;
 else if(source->m_template->kinds[13]&0x20) { if(!melee && !attackingObject) machineType=7; else machineType=6; }
 else if(weapon->m_template->m_field82) machineType=8;
 else if(melee) machineType=reinterpret_cast<const Rva002C940EByteField*>(weapon->m_template)->get()?1:2;
 else machineType=attackingObject?3:4;
 createAttackMachine(source);
 StateMachine *attack=attackMachine;
 if(!attack) return STATE_FAILURE;
 flag49=false;
 if(attackingObject) {
  if(!victim || (victim->status438&1) || victim->testStatus((ObjectStatusTypes)50)) {
   ai->notifyVictimIsDead();return STATE_FAILURE;
  }
  objectID44=victim->id;
  victimTeam=victim->team;
  attack->setGoalObject(victim);
  victimPos=victim->position;
  flag49=source->getRelationship(victim)==0;
 } else {
  attack->setGoalPosition(&machine->m_goalPosition);
  victimPos=machine->m_goalPosition;
 }
 source->setStatus((ObjectStatusTypes)22,true);
 weapon->m_maxShotCount=0x7FFFFFFF;
 if(weapon->m_template->m_continueAttackRange>0) source->setStatus((ObjectStatusTypes)27,true);
 if(reinterpret_cast<const Rva0028B7B5CmpBoolField*>(source)->get() && source->getCurrentWeapon(0))
  lockedWeapon=*(const AsciiString *)&(source->getCurrentWeapon(0)->m_template->m_field08);
 else lockedWeapon.clear();
 StateReturnType ret=attackMachine->initDefaultState();
 if(ret==STATE_CONTINUE) {
  if(attackMachine->getCurrentStateID()==228) {
   if(reinterpret_cast<const unsigned char*>(source->conditions)[4]&0x20) {source->conditions[1]&=~0x20;source->rva0028AE6D();}
   if(reinterpret_cast<const unsigned char*>(source->conditions)[4]&0x40) {source->conditions[1]&=~0x40;source->rva0028AE6D();}
   if(reinterpret_cast<const unsigned char*>(source->conditions)[4]&0x80) {source->conditions[1]&=~0x80;source->rva0028AE6D();}
  } else {
   if(!(reinterpret_cast<const unsigned char*>(source->conditions)[4]&0x20)) {source->conditions[1]|=0x20;source->rva0028AE6D();}
   if(victim && (victim->m_template->kinds[0]&0x80)) {
    if(!(reinterpret_cast<const unsigned char*>(source->conditions)[4]&0x40)) {source->conditions[1]|=0x40;source->rva0028AE6D();}
   }
   if(!melee && !attackingObject && !(reinterpret_cast<const unsigned char*>(source->conditions)[4]&0x80)) {source->conditions[1]|=0x80;source->rva0028AE6D();}
  }
  Player *player=source->getControllingPlayer();
  if(player && reinterpret_cast<const AttackControllingPlayerView*>(player)->type==1) ai->playAttackVoiceResponse(victim);
 } else source->setStatus((ObjectStatusTypes)22,false);
 return ret;
}
