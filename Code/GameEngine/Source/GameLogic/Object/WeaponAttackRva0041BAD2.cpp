// Native Ghidra41BAD2..41BB26 RET16: source/target guards, Object+330 WeaponSet,
// attack results3 or2, then the established Weapon helper2CCED3.
// InGameUI29CE45/29CE67 loads TheActionManager into ECX before this member call.
// ECX is unused by the leaf. Reference canFireWeaponAtObject guides semantics;
// the original wrapper/helper names remain uncertain and address-derived.
// cl: /O1 /arch:SSE /G7 /MD /Oy-
enum WeaponSlotType { PRIMARY_WEAPON = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };
enum AbleToAttackType { ATTACK_NEW_TARGET = 0 };
enum CanAttackResult { ATTACKRESULT_NOT_POSSIBLE=0, ATTACKRESULT_INVALID_SHOT=1, ATTACKRESULT_POSSIBLE_AFTER_MOVING=2, ATTACKRESULT_POSSIBLE=3 };
class Object;
class Weapon { public: bool rva002CCED3(const Object*,const Object*); };
class WeaponSet { public: Weapon *getWeaponInWeaponSlot(WeaponSlotType) const; };
class Object { public: CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType,const Object*,CommandSourceType) const; };
class ActionManager { public: bool rva0041BAD2(const Object*,const Object*,CommandSourceType,WeaponSlotType); };
bool ActionManager::rva0041BAD2(const Object *source,const Object *target,CommandSourceType command,WeaponSlotType slot) {
 if(source && target) {
  const WeaponSet *weapons=reinterpret_cast<const WeaponSet*>(reinterpret_cast<const char*>(source)+0x330);
  Weapon *weapon=weapons->getWeaponInWeaponSlot(slot);
  if(weapon) {
   CanAttackResult result=source->getAbleToAttackSpecificObject(ATTACK_NEW_TARGET,target,command);
   if(result==ATTACKRESULT_POSSIBLE || result==ATTACKRESULT_POSSIBLE_AFTER_MOVING) return weapon->rva002CCED3(source,target);
  }
 }
 return false;
}
