// ?rva003449C5@@YA_NPAUCoord3D@@PAVObject@@1@Z
// partial score=0.9650028477340173 date=2026-10-10
// ?rva003449C5@@YA_NPAUCoord3D@@PAVObject@@1@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /EHsc /MD /arch:SSE /I.
//
// ?rva003449C5@@YA_NPAUCoord3D@@PAVObject@@1@Z retail 0x003449C5..0x00344D60 923B.
// cdecl melee fallback goal helper (goal; source; victim) called from
// 0x00345AB7 and 0x00348E9F; BFME 1 places the same body at 0x001752A0
// (called from AIAttackMeleeEngageState::computePath). WorldBuilder twin
// 0x00E10AB0 has the same call graph.
// Without an AI (+0x258) it fails. A victim of kind 93 whose
// SiegeDeploySpecialPower module reports set (0x004C5772) keeps the goal.
// When the source can approach the target (victim position or the goal)
// and a quick path to the goal exists the goal is kept. Otherwise it walks
// back from the goal toward the source in 20-unit steps until a quick path
// exists (fails when none does) and notes cells on an upper layer or on a
// blocked gate; such a goal is pulled back by the AI data radius (+0xD4)
// plus the source radius (+0xB8) unless the target was approachable. An
// unadjusted point must be at least 20 units closer than the goal. The point
// is fitted with adjustToPossibleDestination and written to the goal.
// R6: canonical Coord3D plus scalar-copy derived value wrapper restores native
// assignment copies without extra conversion temporaries. Whole923B and all
// existing callee spellings resolve; only firstscale and loop SSE allocation
// remain. Pointer goal query uses the legacy owned integer ABI spelling of
// 2E98EA with explicit address conversion and byte-result test; native/WB prove
// the first input denotes a Coord3D pointer. Future type repair should rename
// that owner's ABI, rather than add another pin on the same address.

#include "Code/Libraries/Include/Lib/Coord3D.h"
struct ApproachCoordCopy:Coord3D{
 __forceinline ApproachCoordCopy(const Coord3D&r){x=r.x;y=r.y;z=r.z;}
 __forceinline void sub(const Coord3D*p){x-=p->x;y-=p->y;z-=p->z;}
 __forceinline void scale(float r){x*=r;y*=r;z*=r;}
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class Weapon;
class Rva002C9B80Owner;
class LocomotorSet;

class Rva004C5772CmpBoolField
{
public:
	bool get() const;
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int kind) const
	{
		return (m_kindOf[kind >> 3] & (1 << (kind & 7))) != 0;
	}

	char m_pad00[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
};

class AIUpdateInterface
{
public:
	char m_pad00[0x1CC];
	LocomotorSet *locomotorSet() { return (LocomotorSet *)((char *)this + 0x1CC); }
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() { return m_ai; }
	protected:
 Module *findModule(NameKeyType key) const;
 friend bool rva003449C5(Coord3D*,Object*,Object*);
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;

	char m_pad00[4];
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	char m_pad44[0xB8 - 0x44];
	float m_radius; // +0xB8
	char m_padBC[0x258 - 0xBC];
	AIUpdateInterface *m_ai; // +0x258
};

class Pathfinder
{
public:
	bool CanApproachToTarget(Object *obj, const Coord3D *pos, Rva002C9B80Owner *weapon, bool flag);
	bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, int flags);
	int isBlockedGateObstacleCell(int pos, int layer);
	bool adjustToPossibleDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest);
};

struct Rva003449C5AIData
{
	char m_pad00[0xD4];
	float m_meleeOffset; // +0xD4
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	Rva003449C5AIData *getAiData() { return m_aiData; }

	char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
	char m_pad14[4];
	Rva003449C5AIData *m_aiData; // +0x18
};

extern AI *TheAI;

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

bool rva003449C5(Coord3D *goal, Object *source, Object *victim)
{
	AIUpdateInterface *ai = source->getAI();
	if (ai == 0)
		return false;

	ApproachCoordCopy delta = *goal;
	delta.sub(source->getPosition());
	delta.z = 0.0f;
	float goalDist = delta.GetLength();

	ApproachCoordCopy target = *goal;
	if (victim)
	{
		static_cast<Coord3D&>(target) = *victim->getPosition();
		if (victim->getTemplate()->isKindOf(93))
		{
			static NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
			Module *module = victim->findModule(key);
			if (module && ((Rva004C5772CmpBoolField *)module)->get())
				return true;
		}
	}

	bool canApproach = TheAI->pathfinder()->CanApproachToTarget(source, &target, (Rva002C9B80Owner *)source->getCurrentWeapon(0), false);
	if (canApproach && TheAI->pathfinder()->QuickDoesPathExist(source, source->getPosition(), goal, 0))
		return true;

	ApproachCoordCopy pos = *goal;
	static_cast<Coord3D&>(delta) = *goal;
	delta.sub(source->getPosition());
	delta.z = 0.0f;
	int steps = -(int)(-delta.length() / 20.0f) - 1;
	delta.Normalize();
	delta.scale(20.0f);
	bool found = false;
	bool blocked = false;
	for (int i = 0; i < steps; ++i)
	{
		pos.sub(&delta);
		if (TheAI->pathfinder()->QuickDoesPathExist(source, source->getPosition(), &pos, 0))
		{
			found = true;
			break;
		}
		if (TheTerrainLogic->getLayerForDestination(source, &pos) > LAYER_GROUND)
			blocked = true;
		else if ((unsigned char)TheAI->pathfinder()->isBlockedGateObstacleCell((int)&pos, LAYER_GROUND))
			blocked = true;
	}
	if (!found)
		return false;

	bool adjusted = false;
	if (blocked && !canApproach)
	{
		float offset = source->m_radius + TheAI->getAiData()->m_meleeOffset;
		delta.normalize();
		delta.scale(offset);
		pos.sub(&delta);
		adjusted = true;
	}

	static_cast<Coord3D&>(delta) = *goal;
	delta.sub(&pos);
	delta.z = 0.0f;
	float newDist = delta.GetLength();
	if (!adjusted && newDist + 20.0f > goalDist)
		return false;

	TheAI->pathfinder()->adjustToPossibleDestination(source, *ai->locomotorSet(), &pos);
	*goal = pos;
	return true;
}
