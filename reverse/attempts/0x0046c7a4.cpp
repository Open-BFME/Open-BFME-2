// ?rva0046C7A4@HordeContain@@UAEPAVObject@@_NPBUCoord3D@@MPAV2@H@Z
// partial score=0.85 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_CRTIMP= /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7 /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// stlport
//
// ?rva0046C7A4@HordeContain@@UAEPAVObject@@_NPBUCoord3D@@MPAV2@H@Z
// retail 0x0046C7A4..0x0046CB2B (904 bytes) thiscall RET 0x14.
//
// Slot 18 of HordeContain's +0x11C interface (vtable 0x00C44C58 entry 18;
// also entry 18 of the HorseHordeContain copy 0x00C45838 and of 0x00C46958),
// the sibling of the matched slot 19-21 picks in HordeContainIface11CSlots.cpp
// and compiled with the same +0x11C subobject this. Picks a member Object:
// the contained Objects (the +0x20 contain interface's slot 70 pair) or,
// when none, the live Objects of the +0x170 ID set. With a position, the
// nearest one inside maxDistance (default 99999), the distance jittered by a
// logic or client random factor in [0.66 1.33] when maxDistance is positive
// (HordeContain.cpp lines 5247/5251 for the ID set and 5314/5318 for the
// contained list) and, for contained Objects, gated by the pinned
// Rva003430A3Check(attacker Object, candidate, attacker's current weapon).
// Without a position, the first Object not in status 0x3F when the flag is
// set, else the first member. The flag also skips status-0x3F Objects in the
// nearest search.
//
// NEAR (helper draft, not under Code/): 892 of 904 bytes, every block and
// call in retail order (WB twin 0x010C54A0 confirms the structure: post-
// increment loops, best distance before best Object, logic random first,
// the canAttack weapon gate). What is left is register allocation: retail
// keeps this in esi only until the loops and spills it to [ebp-0x10],
// holding pos in ebx (ID set path) / edi (contained list path) and the
// list end in ebx; this draft keeps this in ebx throughout and reloads pos
// from its argument slot, which also shifts the frame slots (limit at -8
// not -4) and costs the arg-slot reuse for the random factor. Tried
// without effect: limit/weapon order, ternaries, pos copies, /O2 and
// /Oy- variants. The scoped diff block is what gives retail's grouped
// load/sub/store difference.
#include <list>
#include <set>
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

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
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);	// pinned 0x0028AEBD
	bool testStatus(ObjectStatusTypes bit) const;		// rowed 0x0004E536
	const Coord3D *getPosition() const { return &m_position; }
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
private:
	unsigned char m_pad000[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x438 - 0x44];
	unsigned char m_438; // +0x438
};

// The difference triple whose length is Coord3D::length (0x00003571).
struct Coord3DDiff : public Coord3D
{
	__forceinline Coord3DDiff(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};

// The pinned free check at 0x003430A3 (attacker, candidate, weapon).
bool Rva003430A3Check(void *attacker, Object *candidate, int weapon);

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

struct Rva0046247DPair
{
	void *m00;
	const _STL::list<Object *> *m04;
};

class UpdateModule : public Rva0046C7A4Slots<1>
{
protected:
	const void *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
	unsigned char m_pad14[0x20 - 0x14];
};
// The +0x20 contain interface (vtable 0x00C44EC8): slot 70 fills the
// contained-items pair.
class ContainModuleInterface : public Rva0046C7A4Slots<70>
{
public:
	virtual void rva0046D27ASlot70(Rva0046247DPair &p) = 0;
};
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
	Rva0046247DPair p;
	rva0046D27ASlot70(p);

	float limit = 99999.0f;
	if (maxDistance > 0.0f)
		limit = maxDistance;

	Weapon *weapon = 0;
	if (attacker)
		weapon = attacker->getCurrentWeapon();

	if (p.m04->empty())
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
		for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); it++)
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
					if (attacker && weapon && !Rva003430A3Check(attacker, obj, (int)weapon))
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
		for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); it++)
		{
			Object *obj = *it;
			if (obj && !obj->testStatus(OBJECT_STATUS_HORDE_3F))
				return obj;
		}
	}
	return p.m04->front();
}
