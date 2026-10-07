// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?getClosestSlave@SpawnBehavior@@UAEPAVObject@@PBUCoord3D@@@Z,
// retail 0x0045F87C, 100 bytes. Dedicated TU.
// BFME2 outline of the BFME1 donor (reference/open-bfme-1/Code/GameEngine/
// Source/GameLogic/Object/Behavior/SpawnBehavior_getClosestSlave.cpp): BFME1
// inlines the 2D distSq over m_position (+0x38); BFME2 outlines it into the
// 0x2615E3 helper (rowed as Rva000CBA20::distSq, same (dx*dx + dy*dy) body
// over +0x38/+0x3C), so this TU reuses that spelling to resolve the call
// with no new pins. Source hoists end() into a named local: retail homes the
// list head in edi across the loop while this stays in ecx for its single
// use. BFME2 layout: m_spawnIDs at secondary-this+0x2C, same as
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

class Rva000CBA20Point
{
public:
	float x;
	float y;
};

#include "../../../Common/RTS/XYDistanceCallView.h"


class Object
{
public:
	char m_pad[0x38];
	Coord3D m_position;
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
	virtual Object *getClosestSlave(const Coord3D *pos);

private:
	char m_pad[0x28];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?getClosestSlave@SpawnBehavior@@UAEPAVObject@@PBUCoord3D@@@Z
Object *SpawnBehavior::getClosestSlave(const Coord3D *pos)
{
	Object *closest = NULL;
	Real closestDistance;
	_STL::list<ObjectID>::iterator end = m_spawnIDs.end();
	for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it._M_node != end._M_node; ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			Real distance = ((Rva000CBA20 *)obj)->distSq((const Rva000CBA20Point *)pos);
			if (!closest || closestDistance > distance)
			{
				closest = obj;
				closestDistance = distance;
			}
		}
	}
	return closest; // Could be null!
}
