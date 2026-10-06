// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?orderSlavesToAttackPosition@SpawnBehavior@@UAEXPBUCoord3D@@HW4CommandSourceType@@@Z,
// retail 0x00460757, 73 bytes. Dedicated TU.
// BFME1 donor (Code/GameEngine/Source/GameLogic/Object/Behavior/
// SpawnBehavior.cpp:350) through AIUpdateInterface::m_commands
// (AICommandInterface at +0x20, hence retail lea ecx,[eax+0x20]); the BFME2
// delta is the AI pointer read directly from Object+0x258 (m_aiDirect).
// Callee aiAttackPosition is the arity-3 thiscall at 0x0029599A (pinned).
// BFME2 layout: m_spawnIDs at secondary-this+0x2C. Vtable slot 0x8425BC,
// between orderSlavesToAttackTarget and getCanAnySlavesAttackSpecificTarget,
// matching the ZH SpawnBehaviorInterface order.

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

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiAttackPosition(const Coord3D *pos, int maxShotsToFire, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	AICommandInterface m_commands;
};

class Object
{
public:
	char m_pad[0x258];
	AIUpdateInterface *m_aiDirect;
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
	virtual void orderSlavesToAttackPosition(const Coord3D *pos, int maxShotsToFire, CommandSourceType cmdSource);

private:
	char m_pad[0x28];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?orderSlavesToAttackPosition@SpawnBehavior@@UAEXPBUCoord3D@@HW4CommandSourceType@@@Z
void SpawnBehavior::orderSlavesToAttackPosition(const Coord3D *pos, int maxShotsToFire, CommandSourceType cmdSource)
{
	for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it._M_node != m_spawnIDs.end()._M_node; ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			AIUpdateInterface *ai = obj->m_aiDirect;
			if (ai)
			{
				ai->m_commands.aiAttackPosition(pos, maxShotsToFire, cmdSource);
			}
		}
	}
}
