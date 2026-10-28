// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE /MD /EHsc
//
// ?rva002FF07B@Rva002FFFCA@@QAEPAXPAVObject@@PBUCoord3D@@MIHHH@Z,
// retail 0x002FF07B..0x002FF8DD (2146 bytes, RET 28): the enemy search
// worker the rowed 0x002FFFCA wrapper forwards its seven arguments to (bit
// 0x100 set when the search point is not the owner's position).
//
// Target facts: the native boundary and RET 28; the receiver is TheAI (it
// reads its +0x18 AI data friendly-fire ratio at +0xF0 through `this`); the
// filter vftables and out-of-line filter constructors named below; every
// call resolves to an existing row or pin. WorldBuilder twin inside the
// 0x00D75E90 range at 0x00D78204 (callgraph lead) carries the same filter
// chain and flow and fixes the source shape used here: the enemy loop is a
// `while` over the iterator, the zero-priority and status 0x4F rejects are two
// separate `continue`s, and the "improves" flag is one boolean expression
// tested together with the best-is-approachable flag.
//
// Donor semantics (Zero Hour AI::findClosestEnemy, carried, not asserted):
// an owner that cannot attack finds nothing; a garrisoned owner asks its
// container's slot 55 first; without priority info the closest filtered
// object is returned (adjusted for an attack); otherwise every object in
// range (or the whole map past 9000) is rated by priority, raised by a
// transport's or its contents' priority, less its distance over the AI
// data's +0x54, preferring approachable targets and rejecting those whose
// splash would hit too many allies.
#include "Coord3D.h"
#include "ascii_string.h"
#include "PartitionRangeQueryCallView.h"
#include <math.h>
extern PartitionManager *ThePartitionManager;
class Object;
class Player;
class AttackPriorityInfo;
class PartitionFilter;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	bool allows(Object *obj);	// 0x00625720
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF8FE4, allow 0x0026109D: +0x08 the object's controlling player
// (or none), +0x0C a flag.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// vftable 0x00BF8FF0: +0x08 the object, +0x0C whether its controlling
// player's +0x5C is 1.
class PartitionFilterRejectBuildings : public Rva000421C8
{
public:
	PartitionFilterRejectBuildings(Object *obj);
	virtual bool allow(Object *obj);
	Object *m_obj;
	bool m_flag;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C07190, allow 0x002614DF.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C07150, allow 0x002619C1.
class Rva002619C1Filter : public Rva000421C8
{
public:
	Rva002619C1Filter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C07178, allow 0x00261BFB: the repulsor filter of
// AI::findClosestRepulsor (ZH's PartitionFilterRepulsor).
class Rva00261BFBFilter : public Rva000421C8
{
public:
	Rva00261BFBFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C071B4, allow 0x002FE13D, getPlayerMask 0x002FE108: the live
// map enemies of +0x08 (ZH's PartitionFilterLiveMapEnemies, AI.cpp-local).
class Rva002FE13DFilter : public Rva000421C8
{
public:
	Rva002FE13DFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
};

// vftable 0x00C071C0, allow 0x002FE371: within +0x08's attack range (ZH's
// PartitionFilterWithinAttackRange, AI.cpp-local).
class Rva002FE371Filter : public Rva000421C8
{
public:
	Rva002FE371Filter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BF91B0, allow 0x00260FD0: +0x08 the object, +0x0C the attack
// type, +0x10 the command source (ZH's PartitionFilterPossibleToAttack).
class Rva00260FD0Filter : public Rva000421C8
{
public:
	Rva00260FD0Filter(const Object *obj, int attackType, int source)
		: m_obj(obj), m_attackType(attackType), m_source(source) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
	int m_attackType;
	int m_source;
};

// vftable 0x00C07160, allow 0x00261246: two flags (ZH's
// PartitionFilterInsignificantBuildings).
class Rva00261246Filter : public Rva000421C8
{
public:
	Rva00261246Filter(bool a, bool b) : m_a(a), m_b(b) {}
	virtual bool allow(Object *obj);
	bool m_a;
	bool m_b;
};

// vftable 0x00C0716C, allow 0x00261353: +0x08 a player index (ZH's
// PartitionFilterFreeOfFog).
class Rva00261353Filter : public Rva000421C8
{
public:
	Rva00261353Filter(int playerIndex) : m_playerIndex(playerIndex) {}
	virtual bool allow(Object *obj);
	int m_playerIndex;
};

// A 128-bit ObjectStatusMaskType; 0x0023DA79 clears it and sets one bit.
class BfmeObject872Header
{
	unsigned int m_words[4];
};

class Rva0023DA79 : public BfmeObject872Header
{
public:
	Rva0023DA79 *rva0023DA79(int base, int bit) throw();	// 0x0023DA79
};

// vftable 0x00C071CC; the out-of-line ctor 0x002FDF1C: status must / must not.
class Rva002FDF1C : public Rva000421C8
{
public:
	Rva002FDF1C(const BfmeObject872Header &a, const BfmeObject872Header &b) throw();	// 0x002FDF1C
	virtual bool allow(Object *obj);
	BfmeObject872Header m_8;
	BfmeObject872Header m_18;
};

// KindOf masks: the accept / reject filters take two 28-byte masks.
template<int N> class BitFlags { public: unsigned int bits[7]; };
extern BitFlags<116> KINDOFMASK_NONE;
class BfmeFixedStorage0004543D { public: char bits[28]; };
struct Rva0006EE7A { Rva0006EE7A(int, int, int) throw(); char bits[28]; };
struct Rva00045411BitSet { Rva00045411BitSet(int, int) throw(); char bits[28]; };
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &, const BfmeFixedStorage0004543D &) throw();
	virtual bool allow(Object *);
	char storage[56];
};
class Rva002FDF47 : public Rva000421C8
{
public:
	Rva002FDF47(const BfmeFixedStorage0004543D &, const BfmeFixedStorage0004543D &) throw();
	virtual bool allow(Object *);
	char storage[56];
};

// vftable 0x00C071A8: +0x08 the object, +0x0C a flag, +0x10 the range.
class Rva00261513Filter : public Rva000421C8
{
public:
	Rva00261513Filter(const Object *o, bool b, float r) : obj(o), flag(b), range(r) {}
	virtual bool allow(Object *);
	const Object *obj;
	bool flag;
	float range;
};

// vftable 0x00C0719C: the owner and its player's skirmish AI (the rowed
// PartitionFilterSkirmishAI::Allow 0x00261535 fills base slot 1).
class SkirmishAI;
class PartitionFilterSkirmishAI : public Rva000421C8
{
public:
	PartitionFilterSkirmishAI(Object *o, SkirmishAI *a) : owner(o), ai(a) {}
	virtual bool allow(Object *);
	Object *owner;
	SkirmishAI *ai;
};

// The tactical AI registry (0x00DFEEF8) and its per-player lookup 0x002A8AB1.
struct Rva002A8AB1Record;
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *); };
extern Rva002A8F24 *TheSkirmishAIManager;

class AIUpdateInterface { public: int rva00260DED() const; };
class AttackPriorityInfo { public: float getPriority(const Object *, const Object *, bool) const; };
class Rva0020391FLeaGetter { public: void *get() const; };
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
struct Rva002FDB93Best { float priority; const AttackPriorityInfo *info; const Object *hunter; };
void Rva002FDB93Callback(Object *, void *);
template<int N> class QuerySlots : public QuerySlots<N - 1> { public: virtual void slot(char (*)[N]) = 0; };
template<> class QuerySlots<0> {};
class ContainModuleInterface : public QuerySlots<55>
{
public:
	virtual bool slot55(Object *, Object **) = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void iterateContained(void (*)(Object *, void *), void *, bool) = 0;
};
enum ObjectStatusTypes { STATUS23 = 23, STATUS37 = 37, STATUS38 = 38, STATUS79 = 79 };
enum Relationship { ENEMY = 0, NEUTRAL = 1, ALLY = 2 };
enum WeaponSlotType { PRIMARY = 0 };
enum NameKeyType { NAMEKEY_INVALID = 0 };
class Rva002CA9CA { public: float getProjectileNuggetRadiusIfAlliesAffected(const void *); };
class Rva002C9400ByteField { public: unsigned char get() const; };
class WeaponTemplate { public: bool isContactWeapon() const; };
class Weapon { public: char pad0[4]; Rva002CA9CA *info; };
class BodyModuleInterface : public QuerySlots<6> { public: virtual float getHealth() const = 0; };
class GatePrimary : public QuerySlots<6> { public: virtual bool isOpen() const = 0; };
#include "../../../Include/Common/Module.h"
class GateBehavior : public GatePrimary, public Module {};
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Player
{
public:
	// Retail inlines this accessor; suppress its competing standalone copy.
	__declspec(dllimport) __forceinline const AsciiString &getPlayerName() const { return name; }
	char pad0[0x4c];
	AsciiString name;
	char pad50[4];
	int index;
};
class ThingTemplate { public: char pad0[0x108]; unsigned char kind[28]; };
class Rva002FFFCA;
class Object
{
public:
	bool isAbleToAttack() const;
	Player *getControllingPlayer() const;
	bool testStatus(ObjectStatusTypes) const;
	Object *adjustVictim(Object *owner, bool useWeaponRange, int index);	// 0x0028CCB9
	Object *rva002931F5(bool);
	float rva002636F6(const Coord3D *, const void *, const Coord3D *) const;
	const Weapon *getCurrentWeapon(WeaponSlotType *) const;
	Relationship getRelationship(const Object *) const;
protected:
	Module *findModule(NameKeyType) const;	// 0x0028B6D6
	friend class Rva002FFFCA;
public:
	const Coord3D *getPosition() const { return &pos; }
	ContainModuleInterface *getContain() const { return contain; }
	Object *getContainedBy() const { return containedBy; }
	char pad0[4];
	ThingTemplate *tmpl;
	char pad8[0x38 - 8];
	Coord3D pos;
	char pad44[0x250 - 0x44];
	ContainModuleInterface *contain;
	BodyModuleInterface *body;
	AIUpdateInterface *ai;
	char pad25c[0x274 - 0x25c];
	Object *containedBy;
	char pad278[0x438 - 0x278];
	unsigned char flags438;
};
class Rva002C9B80Owner;
class Pathfinder { public: bool CanApproachToTarget(Object *, const Coord3D *, Rva002C9B80Owner *, bool); };
struct TAiData { char pad0[0x54]; float distanceModifier; char pad58[0xF0 - 0x58]; float friendlyFireRatio; };
class AI { public: char pad0[0x10]; Pathfinder *pathfinder; char pad14[4]; TAiData *data; };
extern AI *TheAI;

// The whole-map query 0x006256F0 is rowed returning a one-word result; the
// call here uses it as the iterator.
struct BfmeResultA { void *value; BfmeResultA(); BfmeResultA(const BfmeResultA &); ~BfmeResultA(); };
class BfmeResultForwardB { public: BfmeResultA bfmeForwardResultB(int); };
typedef BfmeWideResult (BfmeResultForwardB::*AllObjectsCall)(int);
// Retail inlines the result copy (bump the shared record's +0x10 count) when
// the ternary's temporary initialises the iterator; the shared view only
// declares it out of line.
// ??0BfmeWideResult@@QAE@ABU0@@Z present-unmatched
__forceinline BfmeWideResult::BfmeWideResult(const BfmeWideResult &other)
{
	void *value = other.m_value;
	++((unsigned *)value)[4];
	m_value = value;
}
__forceinline const float &MaxPriority(const float &a, const float &b) { return a > b ? a : b; }

class Rva002FFFCA
{
public:
	void *rva002FF07B(Object *, const Coord3D *, float, unsigned, int, int, int);
};

void *Rva002FFFCA::rva002FF07B(Object *me, const Coord3D *pos, float range, unsigned qualifiers,
	int infoAddress, int optionalAddress, int extra)
{
	const AttackPriorityInfo *info = (const AttackPriorityInfo *)infoAddress;
	Rva000421C8 *optional = (Rva000421C8 *)optionalAddress;
	if ((qualifiers & 2) && !me->isAbleToAttack())
		return 0;
	if ((qualifiers & 0x40) && me->testStatus(STATUS23))
		return 0;

	Rva002FE13DFilter filterOwner(me);
	Rva0026119DFilter filterAlive;
	Rva002FE371Filter filterRange(me);
	PartitionFilterRejectBuildings filterBuildings(me);
	Rva00261058 filterPlayer(me, false);
	Rva002FDF1C filterStatus(*Rva0023DA79().rva0023DA79(0, 0x32), *Rva0023DA79().rva0023DA79(0, 0));
	Rva002619C1Filter filterLOS(me);
	Rva00260FD0Filter filterAttack(me, 2, 0);
	Rva00261246Filter filterInsignificant(true, false);
	Rva00261353Filter filterFogged(me->getControllingPlayer()->index);
	Rva0004584D filterAccept((const BfmeFixedStorage0004543D &)KINDOFMASK_NONE, (const BfmeFixedStorage0004543D &)Rva0006EE7A(0, 130, 136));
	Rva002FDF47 filterReject((const BfmeFixedStorage0004543D &)Rva0006EE7A(0, 130, 136), (const BfmeFixedStorage0004543D &)Rva00045411BitSet(0, 38));
	Rva00261513Filter filterDistance(me, true, range);
	PartitionFilterSkirmishAI filterSkirmish(me, (SkirmishAI *)TheSkirmishAIManager->rva002A8AB1(me->getControllingPlayer()));

	filterOwner.link(&filterAlive);
	if (!(qualifiers & 8))
		filterOwner.link(&filterBuildings);
	if (qualifiers & 0x40)
	{
		if (!TheSkirmishAIManager->rva002A8AB1(me->getControllingPlayer()))
			filterOwner.link(&filterAccept);
		else
			filterOwner.link(&filterReject);
	}
	if (qualifiers & 0x10)
		filterOwner.link(&filterRange);
	if (qualifiers & 1)
		filterOwner.link(&filterLOS);
	if (qualifiers & 0x20)
		filterOwner.link(&filterFogged);
	if (qualifiers & 4)
		filterOwner.link(&filterInsignificant);
	filterOwner.link(&filterPlayer);
	filterOwner.link(&filterStatus);
	if (!(qualifiers & 0x100))
		filterOwner.link(&filterDistance);
	if (me->ai->rva00260DED() == 0x21 && TheSkirmishAIManager->rva002A8AB1(me->getControllingPlayer()))
		filterOwner.link(&filterSkirmish);
	if (qualifiers & 2)
		filterOwner.link(&filterAttack);

	if ((qualifiers & 2) && me->testStatus(STATUS37))
	{
		Object *container = me->getContainedBy();
		if (container)
		{
			ContainModuleInterface *contain = container->getContain();
			if (contain)
			{
				Object *target;
				if (contain->slot55(me, &target))
				{
					if (!target)
						return 0;
					if (!filterOwner.allows(target))
						return 0;
					if (target && info && info != ((const Rva0020391FLeaGetter *)TheScriptEngine)->get()
						&& info->getPriority(me, target, false) == 0.0f)
						return 0;
					return target;
				}
			}
		}
	}

	if (!info)
	{
		Object *found = ThePartitionManager->getClosestObject(pos, range, 1, &filterOwner);
		return found && (qualifiers & 2) ? found->adjustVictim(me, 1, extra) : found;
	}

	BfmeWideResult iter = range < 9000.0f
		? ThePartitionManager->iterateObjectsInRange(pos, range, 1, &filterOwner, 0)
		: (((BfmeResultForwardB *)ThePartitionManager)->*reinterpret_cast<AllObjectsCall>(&BfmeResultForwardB::bfmeForwardResultB))((int)&filterOwner);
	Object *best = 0;
	float bestPriority = 0.0f, bestRaw = 0.0f;
	bool bestApproachable = false;
	const Weapon *weapon = me->getCurrentWeapon(0);
	Object *enemy;
	while ((enemy = iter.next()) != 0)
	{
		float priority = info->getPriority(me, enemy, true);
		if (enemy->testStatus(STATUS38))
		{
			Object *transport = enemy->rva002931F5(false);
			if (transport)
			{
				if (!transport->getContainedBy())
				{
					float transportPriority = info->getPriority(me, transport, true);
					priority = MaxPriority(priority, transportPriority);
				}
				else
					priority = 0.0f;
			}
		}
		if (priority == 0.0f)
			continue;
		if (enemy->testStatus(STATUS79))
			continue;
		if (enemy->tmpl->kind[17] & 2)
		{
			static NameKeyType gateKey = TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
			GateBehavior *gate = static_cast<GateBehavior *>(enemy->findModule(gateKey));
			if (gate && gate->isOpen())
				continue;
		}
		ContainModuleInterface *contain = enemy->getContain();
		if (contain)
		{
			Rva002FDB93Best data;
			data.priority = priority;
			data.info = info;
			data.hunter = me;
			contain->iterateContained(Rva002FDB93Callback, &data, true);
			if (data.priority > priority)
				priority = data.priority;
		}
		float dist = (float)sqrt(me->rva002636F6(pos, enemy, enemy->getPosition()));
		float weightedDistance = dist / TheAI->data->distanceModifier;
		float effective = priority + 100.0f - weightedDistance;
		if ((qualifiers & 0x80)
			&& (enemy->getControllingPlayer()->getPlayerName().compare("PlyrCreeps") == 0 || (enemy->tmpl->kind[21] & 0x40)))
			effective = 1.0f;
		bool improves = effective > bestPriority || (effective == bestPriority && priority > bestRaw);
		if (!improves && bestApproachable)
			continue;
		Pathfinder *pathfinder = TheAI->pathfinder;
		bool approachable = ((Pathfinder *volatile &)pathfinder)->CanApproachToTarget(me, enemy->getPosition(),
			(Rva002C9B80Owner *)me->getCurrentWeapon(0), true);
		if (!approachable && bestApproachable)
			continue;
		if (weapon)
		{
			float radius = weapon->info->getProjectileNuggetRadiusIfAlliesAffected(weapon);
			if (radius > 0.0f)
			{
				BfmeWideResult splash = ThePartitionManager->rva006255D0(enemy->getPosition(), radius, 4, 0);
				float friends = 0.0f, others = 0.0f;
				Object *obj;
				while ((obj = splash.next()) != 0)
				{
					if (obj->flags438 & 1)
						continue;
					if (me->getRelationship(obj) == ALLY)
						friends += obj->body->getHealth();
					else
						others += obj->body->getHealth();
				}
				if (friends + others < 1.0f)
					continue;
				if (friends / (friends + others) >= ((AI *)this)->data->friendlyFireRatio)
					continue;
			}
		}
		if ((improves || (approachable && !bestApproachable)) && (!optional || optional->allows(enemy))
			&& (approachable || !bestApproachable || !best))
		{
			bestPriority = effective;
			bestRaw = priority;
			best = enemy;
			bestApproachable = approachable;
		}
	}
	if (best && !bestApproachable && weapon)
	{
		if (((Rva002C9400ByteField *)weapon->info)->get() || ((WeaponTemplate *)weapon->info)->isContactWeapon())
			best = 0;
	}
	return best && (qualifiers & 2) && !(qualifiers & 0x10) ? best->adjustVictim(me, 1, extra) : best;
}
