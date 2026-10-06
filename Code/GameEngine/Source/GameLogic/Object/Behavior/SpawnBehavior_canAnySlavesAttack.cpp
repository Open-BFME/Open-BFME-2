// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?canAnySlavesAttack@SpawnBehavior@@UAE_NXZ,
// retail 0x0045F99E, 58 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Behavior/
// SpawnBehavior.cpp:511) with the BFME2 layout: m_spawnIDs lives at
// secondary-this+0x2C (one word past the BFME1 spot). Modeled on the BFME1
// donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/
// Behavior/SpawnBehavior_canAnySlavesAttack.cpp. The `this` pointer is the
// SpawnBehaviorInterface secondary subobject (Object::isAbleToAttack reaches
// this body through getSpawnBehaviorInterface at slot 7).

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	Bool isAbleToAttack() const;
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
	virtual Bool canAnySlavesAttack();

private:
	char m_pad[0x28];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?canAnySlavesAttack@SpawnBehavior@@UAE_NXZ
Bool SpawnBehavior::canAnySlavesAttack()
{
	for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it._M_node != m_spawnIDs.end()._M_node; ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			if (obj->isAbleToAttack())
				return true;
		}
	}
	return false;
}
