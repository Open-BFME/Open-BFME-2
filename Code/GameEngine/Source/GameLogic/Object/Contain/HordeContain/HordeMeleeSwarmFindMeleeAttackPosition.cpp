// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// HordeMeleeSwarm::findMeleeAttackPosition, retail 0x00583D54..0x005842F7 (1443B), thiscall ret 0x1C; sole caller
// 0x0058492D (the swarm's unit update).
//
// Picks a melee attack position for a horde member around its target: from
// the member's position (adjusted through 0x002EDE5B) it first steps out on
// rings of 10-unit cells until the pathfinder's horde melee line test passes,
// then scans rings up to twice the 0x002E9B31 count for the cell closest to
// the target that is free (or, when overlap is allowed, held only by two
// same-team units already in attack range), on a compatible layer within 40
// of the member's height and reachable from the last good cell; the scan
// stops early once a near enough candidate is found. The result frames are
// two (good angle) or four (no position) seconds of logic frames.
//
// Evidence (target): WorldBuilder twin 0x0147B280 is
// HordeMeleeSwarm::findMeleeAttackPosition (HordeMeleeSwarm.cpp assert at
// line 349, DEBUG logs "Allowed backwards due to overlap" and "Moving too far
// away from group."); callees are rowed or pinned under the spellings used
// here.
// Codegen notes: the ObjectID lookup chain (ObjectIdMap::find 0x002888D4 and
// GameLogic::findObjectByID 0x00049DC5, rowed COMDAT copies as in
// ProjectileNuggetObjectEffect.cpp) is visible in this unit, which gives
// retail's register allocation; the two ring searches share one i/j pair,
// which gives retail's loop-counter frame slots.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Common/GameLogicObjectLookupView.h"
#include <math.h>

typedef int Int;
typedef bool Bool;
typedef float Real;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_WALL = 0x10
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

#include "../../../../../Include/GameLogic/Weapon.h"

class AIUpdateInterface
{
public:
	void *getLocomotorSet() const { return m_1dc; }
private:
	unsigned char m_pad000[0x1DC];
	void *m_1dc;					// +0x1DC
};

class Object
{
public:
	Int rva0028B511() const;
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Real rva002C97E8(const Coord3D *a, const Coord3D *b) const;
	const Coord3D *getPosition() const { return &m_pos; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Int getTeamValue() const { return m_274; }
private:
	unsigned char m_pad000[0x38];
	Coord3D m_pos;					// +0x38
	unsigned char m_pad044[0x258 - 0x44];
	AIUpdateInterface *m_ai;			// +0x258
	unsigned char m_pad25c[0x274 - 0x25C];
	Int m_274;					// +0x274
};

class Pathfinder
{
public:
	int GetOverlapGoalUnits(Object *,const Coord3D *,int *);
	bool IsHordeMeleeLinePassable(void *obj, void *locomotorSet, PathfindLayerEnum layer, const Coord3D *from, const Coord3D *to);
	bool rva002EDFF9(Object *obj, Coord3D *pos);
};

class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;			// +0x10
};
extern AI *TheAI;

class TerrainLogic
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal, Bool clip);	// slot 7
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

extern GameLogic *TheGameLogic;

struct SwarmLookupNode { SwarmLookupNode *next; ObjectID key; Object *object; };
struct SwarmLookupBuckets {
 SwarmLookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 SwarmLookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct SwarmLookupMap { unsigned char hashEqual[4]; SwarmLookupBuckets buckets; };
inline ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 SwarmLookupMap *map=(SwarmLookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 SwarmLookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
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
extern Int BfmeLogicFramesPerSecond;			// LOGICFRAMES_PER_SECOND

int Rva002EDE5B(void *obj, Coord3D *pos);
int Rva002E9B31Get(void *obj);

struct Rva00583D54Held
{
	void *m_00;
	void *m_04;
	Object *m_leader;				// +0x08
};

class HordeMeleeSwarm
{
public:
	Bool findMeleeAttackPosition(Object *obj, Coord3D *result, Object *victim, const Coord3D *victimPos,
		Bool unused, Int *frames, Bool allowOverlap);
private:
	void *m_vtable;
	Rva00583D54Held *m_held;			// +0x04
};

static __forceinline void copyCoord(Coord3D &dest, const Coord3D *src)
{
	dest.x = src->x;
	dest.y = src->y;
	dest.z = src->z;
}

static __forceinline void subCoord(Coord3D &c, const Coord3D *a)
{
	c.x -= a->x;
	c.y -= a->y;
	c.z -= a->z;
}

Bool HordeMeleeSwarm::findMeleeAttackPosition(Object *obj, Coord3D *result, Object *victim, const Coord3D *victimPos,
	Bool unused, Int *frames, Bool allowOverlap)
{
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->rva0028B511();
	AIUpdateInterface *ai = obj->getAI();
	*frames = 0;
	if (!ai)
		return false;

	void *locomotorSet = ai->getLocomotorSet();
	const Real goodAngle = 0.7071f;
	const Real closeRatio = 0.5f;
	const Weapon *weapon = obj->getCurrentWeapon(0);
	Object *leader = m_held->m_leader;

	Coord3D pos;
	copyCoord(pos, obj->getPosition());
	Rva002EDE5B(obj, &pos);

	Real dist;
	{
		Coord3D dir;
		copyCoord(dir, victimPos);
		subCoord(dir, &pos);
		dir.z = 0.0f;
		dist = dir.Normalize();
	}

	Coord3D best;
	copyCoord(best, &pos);
	Bool found = false;
	Real bestOffset = 0.0f;
	Real bestGain = 0.0f;
	Int rings = Rva002E9B31Get(obj) * 2;
	Bool isFar = dist > (Real)(rings * 20);
	Real bestDist = dist + 100.0f;

	Int overlapIds[16];
	Bool overlapping = TheAI->pathfinder()->GetOverlapGoalUnits(obj, obj->getPosition(), overlapIds) > 0;
	Bool blocked = !TheAI->pathfinder()->IsHordeMeleeLinePassable(obj, locomotorSet, layer, &pos, &pos);

	Coord3D lastGood;
	Int i, j;
	copyCoord(lastGood, &pos);
	if (blocked)
	{
		for (Int ring = 1; ring <= 2 && blocked; ring++)
		{
			for (i = -ring; i <= ring && blocked; i++)
			{
				for (j = -ring; j <= ring && blocked; j++)
				{
					if (i == ring || j == ring || i == -ring || j == -ring)
					{
						Coord3D cand;
						copyCoord(cand, &pos);
						cand.x += (Real)i * 10.0f;
						cand.y += (Real)j * 10.0f;
						if (TheAI->pathfinder()->IsHordeMeleeLinePassable(obj, locomotorSet, layer, &cand, &cand))
						{
							lastGood = cand;
							blocked = false;
						}
					}
				}
			}
		}
	}

	PathfindLayerEnum objLayer = (PathfindLayerEnum)obj->rva0028B511();
	for (Int ring = 1; ring <= rings; ring++)
	{
		for (i = -ring; i <= ring; i++)
		{
			for (j = -ring; j <= ring; j++)
			{
				if (i == ring || j == ring || i == -ring || j == -ring)
				{
					Real ox = (Real)i * 10.0f;
					Real oy = (Real)j * 10.0f;
					Coord3D delta;
					delta.x = pos.x + ox;
					delta.y = pos.y + oy;
					delta.z = 0.0f;
					subCoord(delta, victimPos);
					delta.z = 0.0f;
					Real candDist = delta.GetLength();
					if (candDist > dist && !overlapping)
						continue;

					Coord3D cand;
					copyCoord(cand, &pos);
					cand.x += ox;
					cand.y += oy;
					leader->rva002C97E8(leader->getPosition(), &cand);

					PathfindLayerEnum candLayer = TheTerrainLogic->getLayerForDestination(obj, &cand);
					if (candLayer != objLayer)
					{
						if (candLayer != LAYER_WALL && objLayer != LAYER_WALL)
							continue;
						cand.z = TheTerrainLogic->getLayerHeight(cand.x, cand.y, candLayer, 0, true);
						if (fabs(cand.z - pos.z) > 40.0f)
							continue;
					}

					Bool ok = false;
					Bool clear = TheAI->pathfinder()->rva002EDFF9(obj, &cand);
					if (!clear && allowOverlap && weapon)
					{
						Int ids[16];
						if (TheAI->pathfinder()->GetOverlapGoalUnits(obj, &cand, ids) == 2 && weapon)
						{
							Object *object = TheGameLogic->findObjectByID((ObjectID)ids[0]);
							Object *b = TheGameLogic->findObjectByID((ObjectID)ids[1]);
							if (object && b && object->getTeamValue() == b->getTeamValue() && obj->getTeamValue() == object->getTeamValue())
							{
								if (const_cast<Weapon *>(weapon)->isWithinAttackRange(obj, &cand, victim, victimPos, 0.0f, true))
								{
									clear = true;
									candDist = dist - 5.0f;
								}
							}
						}
					}
					if (clear)
					{
						if (blocked)
							ok = true;
						else
							ok = TheAI->pathfinder()->IsHordeMeleeLinePassable(obj, locomotorSet, layer, &lastGood, &cand);
					}
					if (ok && candDist < bestDist)
					{
						best = cand;
						bestDist = candDist;
						bestOffset = (Real)sqrt(oy * oy + ox * ox);
						bestGain = dist - candDist;
						found = true;
					}
				}
			}
		}
		if (!isFar && found && bestGain / bestOffset > goodAngle)
			break;
	}

	if (found)
	{
		*result = best;
		if (bestGain / bestOffset < closeRatio)
			*frames = BfmeLogicFramesPerSecond * 2;
	}
	else
	{
		*frames = BfmeLogicFramesPerSecond * 4;
	}
	return found;
}


