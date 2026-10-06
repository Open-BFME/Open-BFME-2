// cl: /DNDEBUG /MD
//
// ?getAbleToUseWeaponAgainstTarget@Object@@QBE?AW4CanAttackResult@@W4AbleToAttackType@@PBV1@PBUCoord3D@@W4CommandSourceType@@@Z,
// retail 0x0028AF2B, 31 bytes. Arity-4 const forwarder: passes attackType,
// this, victim, pos and commandSource to the WeaponSet member at this+0x330
// (pinned at 0x002C7907). Shape follows the BFME1 Object.cpp donor for the
// arity-5 sibling (attackType, this, victim, pos, commandSource,
// specificSlot); the arity-4 retail drops the slot. Row supersedes the
// SpawnBehavior-slave-loop pin at this address.

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum WeaponChoiceCriteria
{
	PREFER_MOST_DAMAGE = 0,
	PREFER_LONGEST_RANGE = 1
};

class Object;
struct Coord3D;

class WeaponSet
{
public:
	CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType attackType, const Object *source, const Object *victim, const Coord3D *pos, CommandSourceType commandSource) const;
	bool chooseBestWeaponForTarget(const Object *obj, const Object *victim, WeaponChoiceCriteria criteria, CommandSourceType cmdSource);
};

class Object
{
public:
	CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType attackType, const Object *victim, const Coord3D *pos, CommandSourceType commandSource) const;
	bool chooseBestWeaponForTarget(const Object *target, WeaponChoiceCriteria criteria, CommandSourceType cmdSource);

private:
	char m_pad[0x330];
	WeaponSet m_weaponSet;
};

// ?getAbleToUseWeaponAgainstTarget@Object@@QBE?AW4CanAttackResult@@W4AbleToAttackType@@PBV1@PBUCoord3D@@W4CommandSourceType@@@Z @0x28AF2B
CanAttackResult Object::getAbleToUseWeaponAgainstTarget(AbleToAttackType attackType, const Object *victim, const Coord3D *pos, CommandSourceType commandSource) const
{
	return m_weaponSet.getAbleToUseWeaponAgainstTarget(attackType, this, victim, pos, commandSource);
}

// ?chooseBestWeaponForTarget@Object@@QAE_NPBV1@W4WeaponChoiceCriteria@@W4CommandSourceType@@@Z
// @0x0028AF4A 27B, the next function in Zero Hour's Object.cpp: forwards
// this and its three arguments to the +0x330 WeaponSet. The callee
// 0x002C7D03 opens with Zero Hour's locked-weapon early return (a nonzero
// +0x24 status answers true).
bool Object::chooseBestWeaponForTarget(const Object *target, WeaponChoiceCriteria criteria, CommandSourceType cmdSource)
{
	return m_weaponSet.chooseBestWeaponForTarget(this, target, criteria, cmdSource);
}
