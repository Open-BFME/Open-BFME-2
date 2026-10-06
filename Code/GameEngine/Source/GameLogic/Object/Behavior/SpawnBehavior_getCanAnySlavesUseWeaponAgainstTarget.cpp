// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?getCanAnySlavesUseWeaponAgainstTarget@SpawnBehavior@@UAE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@PBUCoord3D@@W4CommandSourceType@@@Z,
// retail 0x0045F93D, 97 bytes. Dedicated TU.
// BFME1 donor verbatim (reference/open-bfme-1/Code/GameEngine/Source/
// GameLogic/Object/Behavior/SpawnBehavior.cpp:458), including the early
// POSSIBLE returns (retail cmp-eax-3/jle-to-epilogue returns result, same as
// the 93B sibling at 0x0045F8E0). Callee getAbleToUseWeaponAgainstTarget is
// the arity-4 thiscall at 0x0028AF2B (pinned; forwards to the WeaponSet at
// this+0x330). BFME2 layout: m_spawnIDs at secondary-this+0x2C, same as
// ?canAnySlavesAttack@SpawnBehavior@@UAE_NXZ at 0x0045F99E.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

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

class Object
{
public:
	CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType attackType, const Object *victim, const Coord3D *pos, CommandSourceType commandSource) const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class SpawnBehavior
{
public:
	virtual CanAttackResult getCanAnySlavesUseWeaponAgainstTarget(AbleToAttackType attackType, const Object *victim, const Coord3D *pos, CommandSourceType cmdSource);

private:
	char m_pad[0x28];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?getCanAnySlavesUseWeaponAgainstTarget@SpawnBehavior@@UAE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@PBUCoord3D@@W4CommandSourceType@@@Z
CanAttackResult SpawnBehavior::getCanAnySlavesUseWeaponAgainstTarget(AbleToAttackType attackType, const Object *victim, const Coord3D *pos, CommandSourceType cmdSource)
{
	Bool invalidShot = false;
	for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it._M_node != m_spawnIDs.end()._M_node; ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			CanAttackResult result = obj->getAbleToUseWeaponAgainstTarget(attackType, victim, pos, cmdSource);

			switch (result)
			{
				case ATTACKRESULT_POSSIBLE:
				case ATTACKRESULT_POSSIBLE_AFTER_MOVING:
					return result;

				case ATTACKRESULT_NOT_POSSIBLE:
					break;

				case ATTACKRESULT_INVALID_SHOT:
					invalidShot = true;
					break;

				default:
					break;
			}
		}
	}
	// Prioritize the reasonings!
	if (invalidShot)
	{
		return ATTACKRESULT_INVALID_SHOT;
	}
	return ATTACKRESULT_NOT_POSSIBLE;
}
