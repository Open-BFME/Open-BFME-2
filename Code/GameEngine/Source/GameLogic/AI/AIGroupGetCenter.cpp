// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// platformsdk
// stlport
//
// ?getCenter@AIGroup@@QAE_NPAUCoord3D@@@Z, retail 0x0036D035, 282B.
// Zero Hour AIGroup::getCenter (GameLogic/AI/AIGroup.cpp): centroid of the
// members that are not DISABLED_HELD and have an AI, falling back to every
// non-held member when none has one; returns count > 0.
// Target evidence: list<Object*> at this+4 (node next/prev/value at +0/+4/+8),
// disabled mask byte test 8 at Object+0x1C8, AIUpdateInterface at +0x258 (as
// AIGroupIsIdle.cpp), position at +0x38. BFME2 adds a call to the rowed
// Object gate 0x002907A1 before the AI test; retail divides each axis by the
// count (one reciprocal, three multiplies). Callers: 11 matched rows already
// reference this name.
#include <windows.h>
#include <list>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

inline Real sqr(Real x) { return x * x; }

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

// Only the word computeGroundPath reads: Object::m_ai+0x1DC is handed to
// Pathfinder::IsLineBlocked as its second argument (Zero Hour passes the
// locomotor set's valid surfaces there to isLinePassable).
class AIUpdateInterface
{
public:
	void *getValidSurfaces() const { return m_validSurfaces; }

private:
	char m_pad0[0x1DC];
	void *m_validSurfaces;	// +0x1DC
};

#include "../../../Include/Common/ThingTemplate.h"

class Object
{
public:
	Bool isMobile() const;
	void rva0028AD32();
	Int rva0028B511() const;	// the pathfind layer (as Object::getLayer callers)
	Bool isDisabledByHeld() const { return (m_disabledMask[0] & 8) != 0; }
	UnsignedInt isKindOf(UnsignedInt mask) const { return (m_template->m_kindof[0] & mask); }
	const Coord3D *getPosition() const { return &m_position; }
	// Retail inlines this +0x258 load; suppress the surplus external copy.
	__declspec(dllimport) __forceinline AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	AIUpdateInterface *getAI() { return m_ai; }
	UnsignedInt getFormationID() const { return m_formationID; }

private:
	char m_pad0[4];
	const ThingTemplate *m_template;	// +0x04
	char m_pad8[0x38 - 0x08];
	Coord3D m_position;
	char m_pad44[0x1C8 - 0x44];
	unsigned char m_disabledMask[0x258 - 0x1C8];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x410-0x25C];
	UnsignedInt m_formationID;
};

#include "../../../Include/GameLogic/PathNode.h"

#include "../../../Include/GameLogic/PathfindPath.h"

#include "../../../Include/GameLogic/AIPathfind.h"

class AttackPriorityInfo;
class PartitionFilter;

#include "../../../Include/GameLogic/TAiData.h"

#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;

#include "../../../Include/GameLogic/TerrainLogic.h"

class AIGroup
{
public:
	Bool getCenter(Coord3D *center);
	Bool getMinMaxAndCenter(Coord2D *minimumBounds, Coord2D *maximumBounds, Coord3D *groupCenter);
	Bool computeGroundPath(const Coord3D *pos, CommandSourceType cmdSource);
	void rva0036CE87();

private:
	virtual ~AIGroup();
	void recompute();

	std::list<Object *> m_memberList;	// +0x04
	Real m_speed;						// +0x08
	Bool m_dirty;						// +0x0C
	char m_pad0D[0x14 - 0x0D];
	Path *m_groundPath;					// +0x14
	Coord3D m_pathStart;				// +0x18
	Coord3D m_pathEnd;					// +0x24
};

// getMinMaxAndCenter (0x0036D14F, declared above) lives in
// AIGroupRva00372571.cpp: the AIGroup formation move 0x00372571 relies on the
// compiler seeing its body (retail calls recompute after it without reloading
// ECX), and computeGroundPath below only calls it.

// AIGroup::getCenter is rowed in its home unit; this copy was a duplicate definition.

// ?computeGroundPath@AIGroup@@QAE_NPBUCoord3D@@W4CommandSourceType@@@Z,
// retail 0x0036D3A3, 785B. WorldBuilder lead AIGroup::computeGroundPath
// (AIGroup.cpp); Zero Hour friend_computeGroundPath is the same function:
// recompute when dirty, min/max/center, the member walk that keeps the
// closest distance to pos and the member closest to the center, the extent
// test against the group distance and the ground path from the center to pos.
// BFME2 deltas, all from the bytes: an up-front ground-layer and terrain slot
// 50 test on pos; the per-member call is Object 0x0028AD32; members are
// sorted into three kind buckets (0x1000 skipped) and the vehicle, other or
// infantry pick is checked for a nearby enemy (AI::findClosestEnemy with the
// +0x70 range, qualifiers 0xE4) before pathing; the center snaps to the center
// member only when IsLineBlocked; the path endpoints are cached at +0x18/+0x24
// and every node is re-tested with terrain slot 50.
Bool AIGroup::computeGroundPath(const Coord3D *pos, CommandSourceType cmdSource)
{
	Bool bad = TheTerrainLogic->getLayerForDestination(NULL, pos) != LAYER_GROUND ||
		TheTerrainLogic->slot50(pos);
	if (bad)
		return false;

	if (m_dirty)
		recompute();

	std::list<Object *>::iterator i;
	// compute current centroid of the team
	Coord3D center;
	Coord2D min;
	Coord2D max;
	Real dx, dy;

	getMinMaxAndCenter(&min, &max, &center);
	Real distSqr = sqr(TheAI->getAiData()->m_minDistanceForGroup * 4.0f);
	m_pathStart = center;
	m_pathEnd = *pos;

	Real distSqrCenterVeh = distSqr * 10;
	Object *infantry = NULL;
	Object *other = NULL;
	Object *vehicle = NULL;
	Object *centerVehicle = NULL;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = (*i);
		obj->rva0028AD32();
		if (obj->isDisabledByHeld())
			continue;
		if (obj->getAI() == NULL)
			continue;
		if (obj->isKindOf(0x1000))
			continue;
		if (obj->isKindOf(0x100))
			infantry = obj;
		else if (obj->isKindOf(0x400))
			vehicle = obj;
		else if (obj->isKindOf(0xA00))
			other = obj;
		const Coord3D *unitPos = (*i)->getPosition();
		Real ux = unitPos->x;
		Real uy = unitPos->y;

		dx = ux - pos->x;
		dy = uy - pos->y;
		if (dx * dx + dy * dy < distSqr)
			distSqr = dx * dx + dy * dy;

		// find object closest to the center.
		dx = ux - center.x;
		dy = uy - center.y;
		if (centerVehicle == NULL || dx * dx + dy * dy < distSqrCenterVeh)
		{
			centerVehicle = (*i);
			distSqrCenterVeh = dx * dx + dy * dy;
		}
	}

	if (centerVehicle == NULL)
		return false;
	if (TheAI->pathfinder()->IsLineBlocked(centerVehicle, centerVehicle->getAI()->getValidSurfaces(),
			(PathfindLayerEnum)centerVehicle->rva0028B511(), centerVehicle->getPosition(), &center))
		center = *centerVehicle->getPosition();

	dx = max.x - min.x;
	dy = max.y - min.y;
	if (dx * dx + dy * dy > sqr(TheAI->getAiData()->m_minDistanceForGroup * 4.0f))
		distSqr = dx * dx + dy * dy;
	if (distSqr < sqr(TheAI->getAiData()->m_minDistanceForGroup))
		return false;

	Object *obj = infantry;
	if (other)
		obj = other;
	if (vehicle)
		obj = vehicle;
	if (obj == NULL)
		return false;
	if (TheAI->findClosestEnemy(obj, TheAI->getAiData()->m_distanceRequiresGroup, 0xE4, NULL, NULL, 0))
		return false;

	rva0036CE87();
	m_groundPath = TheAI->pathfinder()->FindGroundPath(obj, &center, pos, 4);
	m_pathStart = center;
	m_pathEnd = *pos;
	if (m_groundPath)
	{
		PathNode *node = m_groundPath->getFirstNode();
		if (node)
		{
			if (node->getNextOptimized())
			{
				m_pathStart = *node->getPosition();
				m_pathEnd = *node->getNextOptimized()->getPosition();
			}
			for (; node; node = node->getNextOptimized())
			{
				if (TheTerrainLogic->slot50(node->getPosition()))
				{
					rva0036CE87();
					return false;
				}
			}
		}
	}
	if (m_groundPath != NULL)
		return true;
	return false;
}
