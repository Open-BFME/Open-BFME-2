// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?getCanAnySlavesAttackSpecificTarget@SpawnBehavior@@UAE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@W4CommandSourceType@@@Z,
// retail 0x0045F8E0, 93 bytes. Dedicated TU.
// BFME1 donor verbatim (reference/open-bfme-1/Code/GameEngine/Source/
// GameLogic/Object/Behavior/SpawnBehavior.cpp:419), including the early
// POSSIBLE returns: retail proves them via cmp-eax-3/jle-to-epilogue (the
// jle lands past the invalidShot tail and returns result untouched).
// Callee getAbleToAttackSpecificObject is the arity-3 thiscall at 0x0028D051
// (pinned). BFME2 layout: m_spawnIDs at secondary-this+0x2C, same as
// ?canAnySlavesAttack@SpawnBehavior@@UAE_NXZ at 0x0045F99E.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
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
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType t, const Object *target, CommandSourceType commandSource) const;
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
	virtual CanAttackResult getCanAnySlavesAttackSpecificTarget(AbleToAttackType attackType, const Object *target, CommandSourceType cmdSource);

private:
	char m_pad[0x28];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?getCanAnySlavesAttackSpecificTarget@SpawnBehavior@@UAE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@W4CommandSourceType@@@Z
CanAttackResult SpawnBehavior::getCanAnySlavesAttackSpecificTarget(AbleToAttackType attackType, const Object *target, CommandSourceType cmdSource)
{
	Bool invalidShot = false;
	for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			CanAttackResult result = obj->getAbleToAttackSpecificObject(attackType, target, cmdSource);

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
