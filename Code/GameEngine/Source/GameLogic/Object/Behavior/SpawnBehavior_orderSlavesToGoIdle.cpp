// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?orderSlavesToGoIdle@SpawnBehavior@@UAEXW4CommandSourceType@@@Z,
// retail 0x004607A0, 65 bytes. Dedicated TU.
// BFME1 donor pattern (reference/open-bfme-1/Code/GameEngine/Source/
// GameLogic/Object/Behavior/SpawnBehavior_orderSlavesToGoIdle.cpp): the AI
// call goes through AIUpdateInterface::m_commands (AICommandInterface at
// +0x20, hence retail lea ecx,[eax+0x20]); the BFME2 delta is that the AI
// pointer is read directly from Object+0x258 (modeled as m_aiDirect) instead
// of the +0x19C getAI member. Callee aiIdle is the arity-1 thiscall at
// 0x001E8A38 (pinned). BFME2 layout: m_spawnIDs at secondary-this+0x2C.
// Vtable slot 0x8425CC, between canAnySlavesAttack and the 0x45F37D entry,
// matching the ZH SpawnBehaviorInterface order.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
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
	void aiIdle(CommandSourceType commandSource);
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
	virtual void orderSlavesToGoIdle(CommandSourceType cmdSource);

private:
	char m_pad[0x28];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?orderSlavesToGoIdle@SpawnBehavior@@UAEXW4CommandSourceType@@@Z
void SpawnBehavior::orderSlavesToGoIdle(CommandSourceType cmdSource)
{
	for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			AIUpdateInterface *ai = obj->m_aiDirect;
			if (ai)
			{
				ai->m_commands.aiIdle(cmdSource);
			}
		}
	}
}
