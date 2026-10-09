// ?FindAttackPathSideways@Pathfinder@@QAEPAVPath@@PAVObject@@@Z
// partial score=0.71 date=2026-10-10
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// NEAR (helper draft, not landed): ?FindAttackPathSideways@Pathfinder@@QAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@02PAVRva002C9B80Owner@@@Z
// retail 0x002FC9B1..0x002FCFCF (1566 bytes, __EH_prolog, ret 0x18). WB twin 0xD64870 Pathfinder::FindAttackPathSideways.
// Best: compiled 1581 bytes, ratio 0.71. All calls resolve except 0x002F8B00 (needs its name pinned).
// Remaining: frame 0xA0 vs retail 0x98 (retail shares startIndex's slot -0x34 with the sideways Coord2D v,
// same ICoord2D/Coord2D slot-sharing quirk as 0x002F8B00), retail caches &m_zoneManager and the start
// cell in edi (edi is not kept zero), and retail emits the open-list loop test at the top and bottom.
// Logic decoded from retail: hierarchical goal adjust + range recheck, sideOffset = attackDistance-40,
// perpendicular test |dot(facing, perp(norm(cell-goal)))| >= 0.85, BuildActualPath with m_1BEB6 set.
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef float Real;
enum PathfindLayerEnum
{
	PATHFIND_LAYER_UNKNOWN = 0,
	PATHFIND_LAYER_GROUND = 1
};
typedef int LocomotorSurfaceTypeMask;
struct ICoord2D { Int x, y; };

class LocomotorSet
{
public:
	LocomotorSurfaceTypeMask getValidSurfaces() const { return m_validLocomotorSurfaces; }
private:
	char m_pad[0x10];
	LocomotorSurfaceTypeMask m_validLocomotorSurfaces;
};

// Retail copy-constructs these points member-wise (movss per field).
struct PathfinderAttackCoord : Coord3D
{
	__forceinline PathfinderAttackCoord() {}
	__forceinline PathfinderAttackCoord(const Coord3D &v) { x = v.x; y = v.y; z = v.z; }
	__forceinline PathfinderAttackCoord(const PathfinderAttackCoord &v) { x = v.x; y = v.y; z = v.z; }
};

inline float sqr(float v) { return v * v; }
// class-gate: allow Coord2D BFME 2's MathCoord2D Coord2D has user ctors and an empty dtor (WorldBuilder twin 0xD64870 tracks each instance as an EH object); the canonical plain Coord2D has neither
class Coord2D
{
public:
	Coord2D() {}
	Coord2D(const Coord2D &that) : x(that.x), y(that.y) {}
	Coord2D(float ix, float iy) : x(ix), y(iy) {}
	Coord2D(Int ix, Int iy) : x((float)ix), y((float)iy) {}
	~Coord2D() {}
	float dot(const Coord2D &c) const { return y * c.y + x * c.x; }
	Coord2D &operator-=(const Coord2D &c) { x -= c.x; y -= c.y; return *this; }
	__forceinline float GetLength() const { return (float)sqrt(x * x + sqr(y)); }
	__forceinline void Normalize() { float inv = 1.0f / GetLength(); x *= inv; y *= inv; }
	float x;
	float y;
};

float Sin(float x);
float Cos(float x);

class Player
{
public:
	char m_pad00[0x5c];
	Int m_playerType;					// +0x5C (1: computer)
};

struct PathfinderTemplateView
{
	char pad[0x108];
	unsigned char kinds[24];
	__forceinline bool hasKind(int bit) const { return (kinds[bit / 8] & (1 << (bit % 8))) != 0; }
};

class AIUpdateInterface;
class Object
{
public:
	Player *getControllingPlayer() const;
	bool rva0028AFBB() const;
	char rva00294815();
	void rva0028C2DD(Coord3D *pos) const;
	Int rva0028B511() const;
	bool isSignificantlyAboveTerrain() const;
	const Coord3D *getPosition() const { return &m_position; }
	Real getOrientation() const { return m_orientation; }
	AIUpdateInterface *getAI() const { return m_ai; }
	void *m_vtable;
	PathfinderTemplateView *m_template;
	char m_pad08[0x38 - 8];
	Coord3D m_position;					// +0x38
	Real m_orientation;					// +0x44
	char m_pad48[0x258 - 0x48];
	AIUpdateInterface *m_ai;			// +0x258
};

class Path;
class Rva002C9B80Owner
{
public:
	Bool isWithinAttackRange(Object *obj, const Coord3D *pos, Object *victim, const Coord3D *victimPos, float range, Bool flag);
};
class PartitionManager
{
public:
	float rva002C9C37(const Object *obj, const Object *victim, void *victimPos);
};
class Rva002EAD62 { public: void rva002EAD62(); };
class HierarchicalPath { public: Int lookUpPositionOnPath(const Coord3D *pos); };
struct PathfinderAttackHandle
{
	Path *path;
	__forceinline PathfinderAttackHandle(Path *p) : path(p) {}
	__forceinline ~PathfinderAttackHandle() { ((Rva002EAD62 *)this)->rva002EAD62(); }
};

class GlobalData
{
public:
	char gap[0x1218];
	unsigned int sidewaysAttackLimit;	// +0x1218
};
extern GlobalData *TheWritableGlobalData;
extern Int g_00DFF0CC;
extern unsigned char g_00DBD4AC;

void Rva002EBCA7Split(void *obj, Int *radius, unsigned char *center);
ICoord2D *Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);
struct Rva002E8C23Param;
int Rva002E8C23Call(int out, unsigned char center, Rva002E8C23Param *cell);

struct In002E6BA1 { Int x, y; };
class MixFileInfoBuffer;
extern Int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **, Int, In002E6BA1 *);
struct PathfinderGroundInfo { Int x, y; Int parent; Int m_0C; };
class PathfindCell
{
public:
	Bool StartPathfind(Int);
	void PutOnClosedList(MixFileInfoBuffer **list);
	float rva0052DD75(float facing, Int count, float weight);
	__forceinline void allocateInfo(In002E6BA1 *pos)
	{
		if (!m_pathInfo) { if (!TheMixFileInfoPool) Rva0052DBCDInit(); m_pathInfo = (PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool, (Int)this, pos); }
		else m_pathInfo->m_0C = 0;
	}
	Int getXIndex() const { return m_pathInfo->x; }
	Int getYIndex() const { return m_pathInfo->y; }
	Int getLayer() const { return (m_info & 0x3f0) >> 4; }
	PathfinderGroundInfo *m_pathInfo;
	char m_pad04[8];
	unsigned int m_info;				// +0x0C
};

class PathfindZoneManager
{
public:
	void rva005312BE();
	void rva00531300();
};

class Pathfinder
{
public:
	Path *FindAttackPathSideways(Object *obj, const LocomotorSet &locos, const Coord3D *from,
		Object *victim, const Coord3D *victimPos, Rva002C9B80Owner *weapon);
	PathfindCell *rva002E8BF8(PathfindLayerEnum layer, const Coord3D *pos);
	void AddToOpenList(PathfindCell *cell);
	PathfindCell *rva002F36E5();
	Int rva002F40E7();
	void CheckChangeLayers(PathfindCell *cell, Object *obj);
	Bool CheckDestination(Object *obj, Int x, Int y, PathfindLayerEnum layer, Int radius, Bool center, Int *distance, Bool flag);
	Bool isAttackViewBlockedByObstacle(const Object *obj, const Coord3D *pos, const Object *victim, const Coord3D *victimPos);
	Int ExamineNeighboringCellsForSidewaysAttack(PathfindCell *parentCell, const ICoord2D *targetNdx, Int offset,
		const LocomotorSet &locomotorSet, Bool isHuman, Bool centerInCell, Int radius, const ICoord2D &startCellNdx,
		Object *obj, Int attackDistance);
	Path *BuildActualPath(Object *obj, LocomotorSurfaceTypeMask surfaces, const Coord3D *fromPos,
		PathfindCell *goalCell, Bool center, Bool blocked, Bool faceDirection);
protected:
	Path *FindClosestHierarchicalPath(Bool isHuman, const LocomotorSet &locomotorSet, Object *obj,
		const Coord3D *from, const Coord3D *to, Bool crusher, Coord3D *adjustedTo);
private:
	char m_pad000[8];
	Bool m_isMapReady;					// +0x08
	char m_pad009[0x34 - 0x09];
	MixFileInfoBuffer *m_closedList;	// +0x34
	Bool m_isTunneling;					// +0x38
	char m_pad039[0x460 - 0x39];
	PathfindZoneManager m_zoneManager;	// +0x460
	char m_pad461[0x1BEB6 - 0x461];
	Bool m_1BEB6;						// +0x1BEB6
	char m_pad1BEB7[0x1C1D8 - 0x1BEB7];
	Int m_searchWord;					// +0x1C1D8
	Int m_destMineshaft;				// +0x1C1DC
};

Path *Pathfinder::FindAttackPathSideways(Object *obj, const LocomotorSet &locos, const Coord3D *from,
	Object *victim, const Coord3D *victimPos, Rva002C9B80Owner *weapon)
{
	if (!m_isMapReady)
		return 0;
	if (!obj->getAI())
		return 0;
	m_searchWord = 0;
	m_destMineshaft = 0;
	Int radius;
	Bool center;
	Rva002EBCA7Split(obj, &radius, (unsigned char *)&center);
	obj->rva0028AFBB();
	Bool isHuman = true;
	if (obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType == 1)
		isHuman = false;
	PathfinderAttackCoord goal(*victimPos);
	if (victim && victim->m_template->hasKind(150))
		victim->rva0028C2DD(&goal);
	m_zoneManager.rva005312BE();
	PathfinderAttackCoord adjusted(goal);
	PathfinderAttackHandle hierarchical(FindClosestHierarchicalPath(isHuman, locos, obj, from, &goal, obj->rva00294815() > 0, &adjusted));
	if (hierarchical.path)
	{
		if (adjusted.x != goal.x || adjusted.y != goal.y)
		{
			if (!weapon->isWithinAttackRange(obj, &adjusted, victim, victimPos, 10.0f, false))
				return 0;
		}
	}
	else
	{
		m_zoneManager.rva00531300();
	}
	Int attackDistance = (Int)((PartitionManager *)weapon)->rva002C9C37(obj, victim, (void *)victimPos) + 30;
	Bool checkLOS;
	if (!victim)
		checkLOS = true;
	else
		checkLOS = !victim->isSignificantlyAboveTerrain();
	PathfinderAttackCoord objPos(*obj->getPosition());
	ICoord2D startIndex;
	Rva002E7875WorldToCell(&startIndex, center, &objPos);
	PathfindCell *startCell = rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(), &objPos);
	if (!startCell)
		return 0;
	startCell->allocateInfo((In002E6BA1 *)&startIndex);
	startCell->StartPathfind(0);
	ICoord2D goalIndex;
	Rva002E7875WorldToCell(&goalIndex, true, victim ? victim->getPosition() : victimPos);
	Int sideOffset = (Int)((PartitionManager *)weapon)->rva002C9C37(obj, victim, (void *)victimPos) - 10;
	AddToOpenList(startCell);
	unsigned int count = 0;
	g_00DFF0CC = 0;
	PathfindCell *acceptable = 0;
	PathfindCell *closest = 0;
	Int closestOrder = 0;
	Int dx = goalIndex.x - startCell->getXIndex();
	Int dy = goalIndex.y - startCell->getYIndex();
	float closestDistance = (float)(dx * dx + dy * dy);
	closestDistance *= 0.9f;
	Int acceptableDistance = 9999999;
	PathfindCell *parent;
	while ((parent = rva002F36E5()) != 0)
	{
		Coord3D cellCenter;
		Rva002E8C23Call((Int)&cellCenter, center, (Rva002E8C23Param *)parent);
		if (hierarchical.path)
		{
			Int order = ((HierarchicalPath *)hierarchical.path)->lookUpPositionOnPath((const Coord3D *)parent->m_pathInfo);
			Int cdx = goalIndex.x - parent->getXIndex();
			Int cdy = goalIndex.y - parent->getYIndex();
			float distance = (float)(cdx * cdx + cdy * cdy);
			if (order > closestOrder || (order == closestOrder && distance < closestDistance))
			{
				closest = parent;
				closestOrder = order;
				closestDistance = distance;
			}
		}
		Int destinationDistance = 0;
		Int cellState = parent->m_pathInfo ? parent->m_pathInfo->m_0C : 0;
		if (!cellState && weapon->isWithinAttackRange(obj, &cellCenter, victim, victimPos, 10.0f, true))
		{
			if (CheckDestination(obj, parent->getXIndex(), parent->getYIndex(), (PathfindLayerEnum)parent->getLayer(), radius, center, &destinationDistance, false))
			{
				Bool blocked = false;
				if (checkLOS)
					blocked = isAttackViewBlockedByObstacle(obj, &cellCenter, victim, victimPos);
				if (startCell == parent)
				{
					blocked = true;
				}
				else
				{
					Coord3D pos;
					Rva002E8C23Call((Int)&pos, center, (Rva002E8C23Param *)parent);
					float px = pos.x - objPos.x;
					float py = pos.y - objPos.y;
					if (px * px + py * py < 5.0f * 5.0f)
						blocked = true;
				}
				if (!blocked)
				{
					float angle = parent->rva0052DD75(obj->getOrientation(), 10, 0.5f);
					Coord2D dir(Cos(angle), Sin(angle));
					Coord2D cellWorld(parent->getXIndex() * 10, parent->getYIndex() * 10);
					Coord2D goalWorld(goalIndex.x * 10, goalIndex.y * 10);
					if (center)
					{
						cellWorld.x += 5.0f;
						cellWorld.y += 5.0f;
					}
					Coord2D v(cellWorld);
					v -= goalWorld;
					v.Normalize();
					Coord2D perp(-v.y, v.x);
					if (fabs(dir.dot(perp)) < 0.85f)
						blocked = true;
				}
				if (!blocked && destinationDistance > 1)
				{
					blocked = true;
					if (destinationDistance < acceptableDistance)
					{
						acceptable = parent;
						acceptableDistance = destinationDistance;
					}
				}
				if (!blocked)
				{
					parent->PutOnClosedList(&m_closedList);
					m_1BEB6 = true;
					Path *path = BuildActualPath(obj, locos.getValidSurfaces(), obj->getPosition(), parent, center, false, g_00DBD4AC);
					m_1BEB6 = false;
					rva002F40E7();
					return path;
				}
			}
		}
		parent->PutOnClosedList(&m_closedList);
		if (count < TheWritableGlobalData->sidewaysAttackLimit)
		{
			CheckChangeLayers(parent, obj);
			count += ExamineNeighboringCellsForSidewaysAttack(parent, &goalIndex, sideOffset, locos, isHuman, center, radius, startIndex, obj, attackDistance);
		}
	}
	Path *path = 0;
	if (acceptable)
	{
		m_1BEB6 = true;
		path = BuildActualPath(obj, locos.getValidSurfaces(), obj->getPosition(), acceptable, center, false, true);
		m_1BEB6 = false;
	}
	else if (closest)
	{
		m_1BEB6 = true;
		path = BuildActualPath(obj, locos.getValidSurfaces(), obj->getPosition(), closest, center, false, true);
		m_1BEB6 = false;
	}
	else
	{
		m_isTunneling = false;
	}
	rva002F40E7();
	return path;
}
