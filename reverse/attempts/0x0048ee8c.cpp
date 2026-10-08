// DeployStyleAIUpdate::update
// partial score=0.94 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /ICode/Libraries/Include /ICode/GameEngine/Source/Common /DNDEBUG /MD /GX
// Scratch reference reconstruction; donor 6c1e0b51, target WB11D9170.
#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1, UPDATE_SLEEP_FOREVER=0x3fffffff };
enum WhichTurretType { TURRET_INVALID=-1 };
enum WeaponSlotType;
enum CommandSourceType { CMD_FROM_AI=2 };
enum DeployStateTypes { READY_TO_MOVE, DEPLOY, READY_TO_ATTACK, UNDEPLOY, ALIGNING_TURRETS };
class Weapon;
class Object {
public:
 const Weapon *getCurrentWeapon(WeaponSlotType *slot=0) const;
 const Coord3D *getPosition() const { return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this)+0x38); }
 ObjectID getID() const { return m_id; }
 Bool isEffectivelyDead() const { return (m_dead & 1)!=0; }
 char pad00[0x74]; ObjectID m_id; char pad78[0x438-0x78]; unsigned char m_dead;
};
class Weapon {
public:
 Bool isWithinAttackRange(const Object *, const Object *, float, int) const;
};
class Rva002C9B80Owner {
public:
 Bool isWithinAttackRange(Object *, const Coord3D *, Object *, const Coord3D *, float, Bool);
};
class TurretStateMachine { public: Object *getGoalObject(); };
class ObjectModule {
public:
 virtual void slot00(); const void *m_moduleData; Object *m_object;
};
class BehaviorModuleInterface { public: virtual void slot00(); };
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface {};
class UpdateModuleInterface { public: virtual UpdateSleepTime update(); };
class UpdateModule : public BehaviorModule, public UpdateModuleInterface {
public: unsigned int nextFrame; int index, reserved;
};
class AICommandInterface {
public:
 virtual void slot00();
 void aiIdle(CommandSourceType);
 void rva0026C2D9(Object *, int, CommandSourceType);
};
class AIUpdateInterface24 { public: virtual void slot00(); };
class AIUpdateInterface : public UpdateModule, public AICommandInterface, public AIUpdateInterface24 {
public:
 virtual UpdateSleepTime update();
 WhichTurretType getWhichTurretForCurWeapon() const;
 Object *getTurretTargetObject(WhichTurretType);
 Object *getNextMoodTarget(Bool, Bool);
 Bool isMoving() const;
 Bool isTurretInNaturalPosition(WhichTurretType) const;
 Bool isWaitingForPath() const { return waiting; }
 void *getPath() const { return path; }
 Object *getObject() const { return m_object; }
 char pad28[0x30-0x28]; TurretStateMachine *machine;
 char pad34[0x140-0x34]; void *path;
 char pad144[0x3b1-0x144]; Bool waiting;
 char pad3b2[0x3e4-0x3b2];
};
class Rva0048E61F { public: int rva0048E61F(); };
class DeployStyleAIUpdate : public AIUpdateInterface {
public:
 virtual UpdateSleepTime update();
 void rva0048EB53(DeployStateTypes);
 void doLastOutsideCommand();
 void reset();
 Bool shouldDoLastOutsideCommand() { return (unsigned char)reinterpret_cast<Rva0048E61F *>(this)->rva0048E61F()!=0; }
 Bool mustCenter() const { return *(reinterpret_cast<const unsigned char *>(m_moduleData)+0x6e)!=0; }
 Bool functionsOnlyDeployed() const { return *(reinterpret_cast<const unsigned char *>(m_moduleData)+0x6f)!=0; }
 void clearOutsideCommand() { *reinterpret_cast<int *>(stored)=-1; replayOutside=false; reset(); }
 char stored[0xc4]; Bool hasOutside, replayOutside; char pad4aa[2];
 int lastCommand; int motionState; DeployStateTypes state;
 UnsignedInt wake, designatedID, attackID; Coord3D position;
 Bool multiple, objectAttack, positionAttack, guarding, overridden, forceDeploy, forceUndeploy;
};
extern GameLogic *TheGameLogic;
UpdateSleepTime DeployStyleAIUpdate::update()
{
 Object *self=getObject();
 const Weapon *weapon=self->getCurrentWeapon();
 Bool inRange=false;
 Object *target=0;
 Bool attacking=false;
 if(weapon) {
  if(positionAttack) {
   inRange=reinterpret_cast<Rva002C9B80Owner *>(const_cast<Weapon *>(weapon))->isWithinAttackRange(self,self->getPosition(),0,&position,0.0f,true);
   attacking=true;
  } else if(objectAttack) {
   target=TheGameLogic->findObjectByID((ObjectID)attackID);
   if(target && target->isEffectivelyDead()) target=0;
   if(target) { inRange=weapon->isWithinAttackRange(self,target,0.0f,1); attacking=true; }
  } else if(multiple) {
   Bool newTarget=false;
   WhichTurretType tur=getWhichTurretForCurWeapon();
   if(tur!=TURRET_INVALID) target=getTurretTargetObject(tur);
   else target=machine->getGoalObject();
   if(!target) target=TheGameLogic->findObjectByID((ObjectID)designatedID);
   if(target && target->isEffectivelyDead()) { target=getNextMoodTarget(true,false); newTarget=true; }
   if(!target && guarding) {
    target=getNextMoodTarget(false,false);
    if(target) {
     inRange=weapon->isWithinAttackRange(self,target,0.0f,1); attacking=true;
     if(inRange) { rva0026C2D9(target,0x7fffffff,CMD_FROM_AI); overridden=true; designatedID=target->getID(); }
     else target=0;
    } else target=0;
   } else if(target) {
    inRange=weapon->isWithinAttackRange(self,target,0.0f,1); attacking=true; designatedID=target->getID();
    if(overridden && newTarget && inRange) rva0026C2D9(target,0x7fffffff,CMD_FROM_AI);
   } else designatedID=0;
  }
 }
 Bool remain=guarding && !target && !isMoving() && !isWaitingForPath();
 if(attacking) motionState=inRange ? 2:3;
 else if(isMoving() || isWaitingForPath()) motionState=1;
 else motionState=0;
 UnsignedInt now=TheGameLogic->getFrame();
 switch(state) {
  case READY_TO_MOVE:
   if(forceDeploy) {
    rva0048EB53(DEPLOY); forceDeploy=false;
    if(lastCommand==2) replayOutside=true;
    else if(hasOutside) { *reinterpret_cast<int *>(stored)=-1; replayOutside=false; reset(); }
   } else if(remain || (inRange && attacking && functionsOnlyDeployed())) {
    rva0048EB53(DEPLOY);
    if(!hasOutside || lastCommand!=0) replayOutside=true;
   }
   break;
  case READY_TO_ATTACK:
   if((!remain && ((!inRange && attacking) || (!attacking && (isWaitingForPath() || getPath())))) || forceUndeploy) {
    WhichTurretType tur=getWhichTurretForCurWeapon();
    if(tur!=TURRET_INVALID && mustCenter()) { rva0048EB53(ALIGNING_TURRETS); break; }
    rva0048EB53(UNDEPLOY);
    if(!hasOutside || lastCommand!=0) replayOutside=true;
    if(forceUndeploy) {
     forceUndeploy=false;
     if(functionsOnlyDeployed() && hasOutside && (lastCommand==2 || lastCommand==3)) { *reinterpret_cast<int *>(stored)=-1; replayOutside=false; reset(); }
    }
   } else if(!target && overridden && shouldDoLastOutsideCommand()) doLastOutsideCommand();
   break;
  case DEPLOY:
   if(wake!=0 && now>=wake) {
    rva0048EB53(READY_TO_ATTACK);
    if(multiple && inRange && attacking && target) { rva0026C2D9(target,0x7fffffff,CMD_FROM_AI); overridden=true; }
   }
   break;
  case UNDEPLOY:
   if(wake!=0 && now>=wake) rva0048EB53(READY_TO_MOVE);
   break;
  case ALIGNING_TURRETS:
   { WhichTurretType tur=getWhichTurretForCurWeapon();
     if(tur!=TURRET_INVALID && isTurretInNaturalPosition(tur)) rva0048EB53(UNDEPLOY); }
   break;
 }
 UpdateSleepTime mine=UPDATE_SLEEP_FOREVER;
 switch(state) {
  case READY_TO_ATTACK: case READY_TO_MOVE: mine=UPDATE_SLEEP_FOREVER; break;
  case DEPLOY: case UNDEPLOY: mine=(wake>now) ? (UpdateSleepTime)(wake-now):UPDATE_SLEEP_NONE; aiIdle(CMD_FROM_AI); break;
  case ALIGNING_TURRETS: mine=UPDATE_SLEEP_NONE; aiIdle(CMD_FROM_AI); break;
 }
 UpdateSleepTime ret=AIUpdateInterface::update();
 return mine<ret ? mine:ret;
}
