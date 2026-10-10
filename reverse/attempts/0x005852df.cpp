// ?findMeleeAttackPosition@HordeMeleeFormation@@QAE_NPAVObject@@PAUCoord3D@@0PBU3@_NPAH3@Z
// partial score=0.9693 date=2026-10-10
// ?findMeleeAttackPosition@HordeMeleeFormation@@QAE_NPAVObject@@PAUCoord3D@@0PBU3@_NPAH3@Z
// partial score=0.92 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
//
// ?findMeleeAttackPosition@HordeMeleeFormation@@QAE_NPAVObject@@PAUCoord3D@@0PBU3@_NPAH3@Z,
// retail 0x005852DF..0x005858F3 (1556B), thiscall ret 0x1C; sole caller
// 0x0058697E (the formation's unit update).
//
// HordeMeleeSwarm::findMeleeAttackPosition (0x00583D54) with one formation
// difference: on the first ring the member's own cell is also tried, offset
// 14 units back from the target along the line to it (no distance test).
//
// Evidence (target): WorldBuilder twin 0x01475120 is
// HordeMeleeFormation::findMeleeAttackPosition (HordeMeleeFormation.cpp assert
// at line 511, same DEBUG logs as the swarm); callees are rowed or pinned
// under the spellings used here.

#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"
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

class Weapon;
class Rva002C9B80Owner
{
public:
	Bool isWithinAttackRange(Object *source, const Coord3D *pos, Object *victim, const Coord3D *victimPos, Real extra, Bool flag);
};

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
	Int GetOverlapGoalUnits(Object *obj, const Coord3D *pos, Int *ids);
	Int IsHordeMeleeLinePassable(void *obj, void *locomotorSet, PathfindLayerEnum layer, const Coord3D *from, const Coord3D *to);
	Bool rva002EDFF9(Object *obj, Coord3D *pos);
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
extern Int g_Va00DBA4E4;			// LOGICFRAMES_PER_SECOND

int Rva002EDE5B(void *obj, Coord3D *pos);
int Rva002E9B31Get(void *obj);

struct Rva005852DFHeld
{
	void *m_00;
	void *m_04;
	Object *m_leader;				// +0x08
};

class HordeMeleeFormation
{
public:
	Bool findMeleeAttackPosition(Object *obj, Coord3D *result, Object *victim, const Coord3D *victimPos,
		Bool unused, Int *frames, Bool allowOverlap);
private:
	void *m_vtable;
	Rva005852DFHeld *m_held;			// +0x04
};

static __forceinline void copyCoord(Coord3D &c, const Coord3D *a)
{
	c.x = a->x;
	c.y = a->y;
	c.z = a->z;
}

static __forceinline void subCoord(Coord3D &c, const Coord3D *a)
{
	c.x -= a->x;
	c.y -= a->y;
	c.z -= a->z;
}

Bool HordeMeleeFormation::findMeleeAttackPosition(Object *obj, Coord3D *result, Object *victim, const Coord3D *victimPos,
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
	copyCoord(lastGood, &pos);
	if (blocked)
	{
		for (Int r = 1; r <= 2 && blocked; r++)
		{
			for (Int i = -r; i <= r && blocked; i++)
			{
				for (Int j = -r; j <= r && blocked; j++)
				{
					if (i == r || j == r || i == -r || j == -r)
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
	for (Int r = 1; r <= rings; r++)
	{
		for (Int i = -r; i <= r; i++)
		{
			for (Int j = -r; j <= r; j++)
			{
				if ((i == 0 && j == 0 && r <= 1) || i == r || j == r || i == -r || j == -r)
				{
					Real ox = (Real)i * 10.0f;
					Real oy = (Real)j * 10.0f;
					Coord3D delta;
					delta.x = pos.x + ox;
					delta.y = pos.y + oy;
					delta.z = 0.0f;
					subCoord(delta, victimPos);
					delta.z = 0.0f;
					Real candDist;
					if (i == 0 && j == 0)
					{
						candDist = 0.0f;
						delta.Normalize();
						Real scaledX = delta.x * 14.0f;
						Real scaledY = delta.y * 14.0f;
						delta.z *= 14.0f;
						ox = 0.0f-scaledX;
						oy = 0.0f-scaledY;
					}
					else
					{
						candDist = delta.GetLength();
						if (candDist > dist && !overlapping)
							continue;
					}

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
							Object *a = TheGameLogic->findObjectByID((ObjectID)ids[0]);
							Object *b = TheGameLogic->findObjectByID((ObjectID)ids[1]);
							if (a && b && a->getTeamValue() == b->getTeamValue() && obj->getTeamValue() == a->getTeamValue())
							{
								if (((Rva002C9B80Owner *)weapon)->isWithinAttackRange(obj, &cand, victim, victimPos, 0.0f, true))
								{
									clear = true;
									candDist = dist + 1.0f;
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
			*frames = g_Va00DBA4E4 * 2;
	}
	else
	{
		*frames = g_Va00DBA4E4 * 4;
	}
	return found;
}
