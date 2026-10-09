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
enum StateReturnType { CONTINUE=0, SUCCESS=-1, FAILURE=-2 };
class Object; class Team; class Player;
class AIUpdateInterface {
public:
unsigned getMoodMatrixActionAdjustment(MoodMatrixAction) const;
void setCurrentVictim(const Object*);
    virtual void slot000(); virtual void slot001(); virtual void slot002(); virtual void slot003();
    virtual void slot004(); virtual void slot005(); virtual void slot006(); virtual void slot007();
    virtual void slot008(); virtual void slot009(); virtual void slot010(); virtual void slot011();
    virtual void slot012(); virtual void slot013(); virtual void slot014(); virtual void slot015();
    virtual void slot016(); virtual void slot017(); virtual void slot018(); virtual void slot019();
    virtual void slot020(); virtual void slot021(); virtual void slot022(); virtual void slot023();
    virtual void slot024(); virtual void slot025(); virtual void slot026(); virtual void slot027();
    virtual void slot028(); virtual void slot029(); virtual void slot030(); virtual void slot031();
    virtual void slot032(); virtual void slot033(); virtual void slot034(); virtual void slot035();
    virtual void slot036(); virtual void slot037(); virtual void slot038(); virtual void slot039();
    virtual void slot040(); virtual void slot041(); virtual void slot042(); virtual void slot043();
    virtual void slot044(); virtual void slot045(); virtual void slot046(); virtual void slot047();
    virtual void slot048(); virtual void slot049(); virtual void slot050(); virtual void slot051();
    virtual void slot052(); virtual void slot053(); virtual void slot054(); virtual void slot055();
    virtual void slot056(); virtual void slot057(); virtual void slot058(); virtual void slot059();
    virtual void slot060(); virtual void slot061(); virtual void slot062(); virtual void slot063();
    virtual void slot064(); virtual void slot065(); virtual void slot066(); virtual void slot067();
    virtual void slot068(); virtual void slot069(); virtual void slot070(); virtual void slot071();
    virtual void slot072(); virtual void slot073(); virtual void slot074(); virtual void slot075();
    virtual void slot076(); virtual void slot077(); virtual void slot078(); virtual void slot079();
    virtual void slot080(); virtual void slot081(); virtual void slot082(); virtual void slot083();
    virtual void slot084(); virtual void slot085(); virtual void slot086(); virtual void slot087();
    virtual void slot088(); virtual void slot089(); virtual void slot090(); virtual void slot091();
    virtual void slot092(); virtual void slot093(); virtual void slot094(); virtual void slot095();
    virtual void slot096(); virtual void slot097(); virtual void slot098(); virtual void slot099();
    virtual void slot100(); virtual void slot101(); virtual void slot102(); virtual void slot103();
    virtual void slot104(); virtual void slot105(); virtual void slot106(); virtual void slot107();
    virtual void slot108(); virtual void slot109(); virtual void slot110(); virtual void slot111();
    virtual void slot112(); virtual void slot113(); virtual void slot114(); virtual void slot115();
    virtual void slot116(); virtual void slot117(); virtual void slot118(); virtual void slot119();
    virtual void slot120(); virtual void slot121(); virtual void slot122(); virtual void slot123();
    virtual void slot124(); virtual void slot125(); virtual void slot126(); virtual void slot127();
    virtual void slot128(); virtual void slot129(); virtual void slot130(); virtual void slot131();
    virtual void slot132(); virtual void slot133(); virtual void slot134(); virtual void slot135();
    virtual void slot136(); virtual void slot137(); virtual void slot138(); virtual void slot139();
    virtual void slot140(); virtual void slot141(); virtual void slot142(); virtual void slot143();
virtual void notifyVictimIsDead();
protected: void playAttackVoiceResponse(Object*);
friend class AIAttackState;
};
struct AttackThingTemplateView { char pad[0x108]; unsigned char kinds[0x20]; };
class WeaponTemplate { public:
 char pad00[8]; AsciiString name;
 char pad0c[0x76]; bool field82;
 char pad83[0xC5]; float m_continueAttackRange;
};
class Weapon { public: char pad00[4]; WeaponTemplate *m_template; char pad08[0x2C]; unsigned m_field34; };
class Object {
public:
 const Weapon *getCurrentWeapon(WeaponSlotType*) const;
 bool isOutOfAmmo() const;
 int rva0028B38D() const;
 bool testStatus(ObjectStatusTypes) const;
 void setStatus(ObjectStatusTypes,bool);
 Object *adjustVictim(Object*,int,int);
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
class Rva003413B2 { public: bool rva003413B2(); };
class Rva002C9400ByteField { public: unsigned char get() const; };
class Rva002C940EByteField { public: unsigned char get() const; };
class Rva0028B7B5CmpBoolField { public: bool get() const; };
struct CurrentStateIDView { char pad[4]; unsigned id; };
class StateMachine {
public:
 virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
 virtual void slot04();virtual void slot05();virtual void slot06();
 virtual StateReturnType initDefaultState();
 virtual void slot08();virtual void slot09();virtual void slot10();virtual void slot11();
 virtual void slot12();virtual void slot13();virtual void setGoalObject(const Object*);
 void setGoalPosition(const Coord3D*);
 Object *getGoalObject();
 unsigned getCurrentStateID() const { return currentState ? currentState->id : 999999; }
 CurrentStateIDView *currentState; char pad08[0xC]; Object *owner;
 char pad18[0xC]; Coord3D goal;
};
class AttackExitConditionsInterface { public: virtual bool shouldExit(const StateMachine*) const; };
struct AttackControllingPlayerView { char pad[0x5C]; unsigned type; };
class AIAttackState {
public:
 virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
 virtual StateReturnType onEnter();
 StateMachine *getMachine() const { return machine; }
 char pad04[0x14];StateMachine *machine;char pad1c[8];StateMachine *attackMachine;
 AttackExitConditionsInterface *parameters;Team *victimTeam;Coord3D victimPos;
 AsciiString lockedWeapon;
 bool follow,attackingObject,force;char pad43;
 unsigned objectID44;unsigned char flag48;bool flag49;char pad4a[2];unsigned machineType;
protected: void createAttackMachine(Object*);
};
StateReturnType AIAttackState::onEnter() {
 Object *source=machine->owner;
 Object *victim=machine->getGoalObject();
 if(!source) return FAILURE;
 AIUpdateInterface *ai=source->ai;
 if(!(ai->getMoodMatrixActionAdjustment((MoodMatrixAction)2)&1)) return SUCCESS;
 if(parameters && parameters->shouldExit(getMachine())) return SUCCESS;
 if(source->isOutOfAmmo() && !(source->m_template->kinds[3]&2)) return FAILURE;
 if(!reinterpret_cast<Rva003413B2*>(this)->rva003413B2()) return FAILURE;
 Weapon *weapon=const_cast<Weapon*>(source->getCurrentWeapon(0));
 if(!weapon) return FAILURE;
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
 else if(weapon->m_template->field82) machineType=8;
 else if(melee) machineType=reinterpret_cast<const Rva002C940EByteField*>(weapon->m_template)->get()?1:2;
 else machineType=attackingObject?3:4;
 createAttackMachine(source);
 StateMachine *attack=attackMachine;
 if(!attack) return FAILURE;
 flag49=false;
 if(attackingObject) {
  if(!victim || (victim->status438&1) || victim->testStatus((ObjectStatusTypes)50)) {
   ai->notifyVictimIsDead();return FAILURE;
  }
  objectID44=victim->id;
  victimTeam=victim->team;
  attack->setGoalObject(victim);
  victimPos=victim->position;
  flag49=source->getRelationship(victim)==0;
 } else {
  attack->setGoalPosition(&machine->goal);
  victimPos=machine->goal;
 }
 source->setStatus((ObjectStatusTypes)22,true);
 weapon->m_field34=0x7FFFFFFF;
 if(weapon->m_template->m_continueAttackRange>0) source->setStatus((ObjectStatusTypes)27,true);
 if(reinterpret_cast<const Rva0028B7B5CmpBoolField*>(source)->get() && source->getCurrentWeapon(0))
  lockedWeapon=source->getCurrentWeapon(0)->m_template->name;
 else lockedWeapon.clear();
 StateReturnType ret=attackMachine->initDefaultState();
 if(ret==CONTINUE) {
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
