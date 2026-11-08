// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_CRTIMP= /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7 /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// stlport
//
// HordeContain +0x11C interface slot 18 (vtable 0x00C44C58), retail 0x0046C7A4 (904 bytes), thiscall RET 0x14: the
// nearest contained Object (else nearest live +0x170 ID-set Object) within maxDistance, distance jittered by a
// random factor in [0.66, 1.33]; without a position the first Object not in status 0x3F, else the first member.
#include <list>

// Use the typed node comparison here; the iterator-base out-of-line wrapper
// belongs to the retail STLport owner compiled with its own settings.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include <set>
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

// The ObjectID lookup chain (ObjectIdMap::find 0x002888D4, GameLogic::findObjectByID 0x00049DC5) and
// Object::testStatus are visible here as header inlines; that gives retail's register allocation.
struct Rva0046C7A4LookupNode { Rva0046C7A4LookupNode *next; ObjectID key; Object *object; };
struct Rva0046C7A4LookupBuckets
{
	Rva0046C7A4LookupNode **begin, **end, **capacity;
	unsigned int size() const { return end - begin; }
	Rva0046C7A4LookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct Rva0046C7A4LookupMap { unsigned char hashEqual[4]; Rva0046C7A4LookupBuckets buckets; };
inline ObjectIdNode *ObjectIdMap::find(const ObjectID &id)
{
	Rva0046C7A4LookupMap *map = (Rva0046C7A4LookupMap *)this;
	unsigned int bucket = (unsigned int)id % map->buckets.size();
	Rva0046C7A4LookupNode *node;
	for (node = map->buckets[bucket]; node && node->key != id; node = node->next) {}
	return (ObjectIdNode *)node;
}

inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}

#define HORDECONTAIN_SOURCE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp"

float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
float GetGameClientRandomValueReal(float lo, float hi, char *file, int line);

enum ObjectStatusTypes
{
	OBJECT_STATUS_HORDE_3F = 0x3F
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
class Weapon;
class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);	// rowed 0x0028AEBD
	bool testStatus(ObjectStatusTypes bit) const;		// rowed 0x0004E536
	const Coord3D *getPosition() const { return &m_position; }
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
private:
	unsigned char m_pad000[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x94 - 0x44];
	unsigned int m_statusBits[4]; // +0x94
	unsigned char m_pad0A4[0x438 - 0xA4];
	unsigned char m_438; // +0x438
};

inline bool Object::testStatus(ObjectStatusTypes bit) const
{
	return (m_statusBits[(unsigned int)bit >> 5] & (1 << (bit & 31))) != 0;
}

// The rowed attack line-of-sight check 0x003430A3 (attacker, candidate, weapon).
bool rva003430A3(Object *attacker, Object *candidate, Weapon *weapon);

template <int N> class Rva0046C7A4Slots : public Rva0046C7A4Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0046C7A4Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

#include "../../../../Include/GameLogic/Module/Rva0046247DPair.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
// The +0x20 contain interface (vtable 0x00C44EC8): slot 70 fills the
// contained-items pair.
#include "../../../../Include/GameLogic/Module/ContainModule.h"
class TransportContain : public UpdateModule, public BehaviorModuleInterface, public UpdateModuleInterface, public ContainModuleInterface
{
private:
	unsigned char m_pad024[0x11C - 0x24];
};
// HordeContain's +0x11C interface (vtable 0x00C44C58); slot 18 is this pick.
class Rva0046BB38Iface11C : public Rva0046C7A4Slots<18>
{
public:
	virtual Object *rva0046C7A4(bool skipStatus, const Coord3D *pos, float maxDistance, Object *attacker, int useClientRandom) = 0;
};

class HordeContain : public TransportContain, public Rva0046BB38Iface11C
{
public:
	virtual Object *rva0046C7A4(bool skipStatus, const Coord3D *pos, float maxDistance, Object *attacker, int useClientRandom);
private:
	unsigned char m_pad120[0x170 - 0x120];
	_STL::set<int> m_170; // +0x170 (Object IDs)
};

Object *HordeContain::rva0046C7A4(bool skipStatus, const Coord3D *pos, float maxDistance, Object *attacker, int useClientRandom)
{
	Rva0046247DPair p = slot70();

	float limit = 99999.0f;
	if (0.0f < maxDistance)
		limit = maxDistance;

	Weapon *weapon = 0;
	if (attacker)
		weapon = attacker->getCurrentWeapon();

	if (((const _STL::list<Object *> *)p.m04)->empty())
	{
		if (m_170.size() == 0)
			return 0;

		if (pos)
		{
			float bestDist = 99999.0f;
			Object *best = 0;
			for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); k++)
			{
				Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
				if (obj && obj->isEffectivelyDead())
					obj = 0;
				if (!obj)
					continue;
				if (obj->testStatus(OBJECT_STATUS_HORDE_3F) && skipStatus)
					continue;

				float dist;
				{
					Coord3D diff;
					diff.x = pos->x;
					diff.y = pos->y;
					diff.z = pos->z;
					diff.x -= obj->getPosition()->x;
					diff.y -= obj->getPosition()->y;
					diff.z -= obj->getPosition()->z;
					dist = diff.length();
				}
				if (dist < limit)
				{
					if (maxDistance > 0.0f)
					{
						float factor;
						if (!useClientRandom)
							factor = GetGameLogicRandomValueReal(0.66f, 1.33f, HORDECONTAIN_SOURCE_FILE, 5247);
						else
							factor = GetGameClientRandomValueReal(0.66f, 1.33f, HORDECONTAIN_SOURCE_FILE, 5251);
						dist = factor * dist;
					}
					if (dist < bestDist)
					{
						best = obj;
						bestDist = dist;
					}
				}
			}
			return best;
		}

		if (skipStatus)
		{
			for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); k++)
			{
				Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
				if (obj && !obj->testStatus(OBJECT_STATUS_HORDE_3F))
					return obj;
			}
			return 0;
		}
		ObjectID id = (ObjectID)*m_170.begin();
		return TheGameLogic->findObjectByID(id);
	}

	if (pos)
	{
		float bestDist = 99999.0f;
		Object *best = 0;
		for (_STL::list<Object *>::const_iterator it = ((const _STL::list<Object *> *)p.m04)->begin(); it != ((const _STL::list<Object *> *)p.m04)->end(); it++)
		{
			Object *obj = *it;
			if (!obj)
				continue;
			if (obj->testStatus(OBJECT_STATUS_HORDE_3F) && skipStatus)
				continue;

			float dist;
			{
				Coord3D diff;
				diff.x = pos->x;
				diff.y = pos->y;
				diff.z = pos->z;
				diff.x -= obj->getPosition()->x;
				diff.y -= obj->getPosition()->y;
				diff.z -= obj->getPosition()->z;
				dist = diff.length();
			}
			if (dist < limit)
			{
				if (maxDistance > 0.0f)
				{
					float factor;
					if (!useClientRandom)
						factor = GetGameLogicRandomValueReal(0.66f, 1.33f, HORDECONTAIN_SOURCE_FILE, 5314);
					else
						factor = GetGameClientRandomValueReal(0.66f, 1.33f, HORDECONTAIN_SOURCE_FILE, 5318);
					dist = factor * dist;
				}
				if (dist < bestDist)
				{
					if (attacker && weapon && !rva003430A3(attacker, obj, weapon))
						continue;
					best = obj;
					bestDist = dist;
				}
			}
		}
		return best;
	}

	if (skipStatus)
	{
		for (_STL::list<Object *>::const_iterator it = ((const _STL::list<Object *> *)p.m04)->begin(); it != ((const _STL::list<Object *> *)p.m04)->end(); it++)
		{
			Object *obj = *it;
			if (obj && !obj->testStatus(OBJECT_STATUS_HORDE_3F))
				return obj;
		}
	}
	return ((const _STL::list<Object *> *)p.m04)->front();
}
