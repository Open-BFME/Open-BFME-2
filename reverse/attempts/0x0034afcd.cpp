// ?update@AIAttackPositionFireWeaponState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include
// Native34AFCD..34B08A (189B); WB E21A70 callgraph+debug literal independently
// names AIAttackPositionFireWeaponState and preserves full update control flow.
// ZH AIStates AIAttackFireWeaponState provides weapon/status semantic guide;
// position-state prefire and interface callbacks are BFME target evidence.
#include "Lib/Coord3D.h"
enum WeaponSlotType { PRIMARY_WEAPON=0 };
enum WeaponStatus { READY_TO_FIRE=0, PRE_ATTACK=4 };
enum ObjectStatusTypes { IS_FIRING=13, STATUS_BIT_27=27, STATUS_BIT_82=82 };
enum StateReturnType { STATE_CONTINUE=0, STATE_SUCCESS=-1, STATE_FAILURE=-2 };
class Weapon { public: WeaponStatus getStatus() const; };
class Object {
public:
 const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
 bool testStatus(ObjectStatusTypes) const;
 void setStatus(ObjectStatusTypes,bool);
 void preFireCurrentWeapon(const Object *,const Coord3D *);
 void fireCurrentWeapon(const Coord3D *);
 void rva0028FC8F();
 bool isEffectivelyDead() const { return (flags & 1)!=0; }
private:
 unsigned char prefix[0x438];
 unsigned char flags;
};
// Getter owner is the existing provider's spelling. This overlay asserts only
// native +20 goal-ID ABI, not that the context is a TurretStateMachine object.
class TurretStateMachine { public: Object *getGoalObject(); };
struct AttackPositionMachineView {
 unsigned char prefix[0x14];
 Object *owner;
 unsigned char gap[0x24-0x18];
 Coord3D goalPosition;
};
class AttackPositionFireInterfaceView {
public:
 virtual void fired();
 virtual void unknownSlot1();
 virtual bool canFire(WeaponSlotType);
};
class AIAttackPositionFireWeaponState {
public:
 virtual StateReturnType update();
private:
 unsigned char prefix[0x18-4];
 AttackPositionMachineView *machine;
 unsigned char gap[4]; // native +1C opaque
 AttackPositionFireInterfaceView *fireInterface;
 bool needsPreFire;
};
StateReturnType AIAttackPositionFireWeaponState::update()
{
 Object *obj=machine->owner;
 WeaponSlotType slot;
 WeaponStatus status;
 const Weapon *weapon=obj->getCurrentWeapon(&slot);
 if (!weapon || obj->isEffectivelyDead() || obj->testStatus(STATUS_BIT_82))
  goto fail;
 if (needsPreFire) {
  needsPreFire=false;
  obj->setStatus(IS_FIRING,true);
  Object *victim=reinterpret_cast<TurretStateMachine *>(machine)->getGoalObject();
  obj->preFireCurrentWeapon(victim,&machine->goalPosition);
  return STATE_CONTINUE;
 }
 status=weapon->getStatus();
 if (status==PRE_ATTACK) return STATE_CONTINUE;
 if (status!=READY_TO_FIRE) goto fail;
 if (!fireInterface || fireInterface->canFire(slot)) goto fire;
fail:
 return STATE_FAILURE;
fire:
 obj->rva0028FC8F();
 obj->fireCurrentWeapon(&machine->goalPosition);
 obj->setStatus(STATUS_BIT_27,false);
 fireInterface->fired();
 return STATE_SUCCESS;
}
