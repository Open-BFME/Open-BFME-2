// ?FindCollisionFreeQuickPath@Pathfinder@@UAEPAVPath@@PAVObject@@PBUCoord3D@@PAUPathNode@@@Z
// partial score=0.69 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /Ireference/shims/bfme2_ascii
//
// ?FindCollisionFreeQuickPath@Pathfinder@@UAEPAVPath@@PAVObject@@PBUCoord3D@@PAUPathNode@@@Z
// retail 0x002F64DD 1286B: slot 10 (+0x28) of the vtable at VA 0x00C053F8
// (its only reference). WorldBuilder's twin 0x00D624A0 is
// Pathfinder::FindCollisionFreeQuickPath (pathfinder.cpp asserts 11798..11853).
// An A* search from the object's cell to the destination cell that also
// accepts up to nineteen cells along the given path nodes as goals. The
// shape is the matched CheckPathCost (pathfinder.cpp): the object's radius
// split (rowed 0x002EBCA7) and cell conversion (rowed 0x002E7875), the
// surface filter (rowed 0x002E8BCF/0x002E6DC4), the inline path-info
// allocation, the open/closed list helpers and the eight-neighbour step
// with the diagonal rule. Each neighbour adds the rowed
// CalcCollisionFreeExtraCosts (a negative cost closes the cell), ten for a
// flagged cell far from the goal and a thousand for an obstacle cell; the
// search gives up after 3000 opened cells. A reached goal is turned into a
// new Path (rowed ctor 0x00363DC8) through the rowed PrependCells and marked
// at +0x0C. +0x48 is cleared on entry.

typedef bool Bool;
typedef int Int;

enum PathfindLayerEnum
{
	PATHFIND_LAYER_UNKNOWN = 0,
	PATHFIND_LAYER_GROUND = 1
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct ICoord2DBase
{
	Int x, y;
};

struct ICoord2D : ICoord2DBase
{
	bool operator==(const ICoord2DBase &other) const;
};

ICoord2D *Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);
void Rva002EBCA7Split(void *obj, Int *radius, unsigned char *center);

struct PathfinderTemplateView
{
	char m_pad000[0x56c];
	Int priority; // +0x56C
	char m_pad570[0x634 - 0x570];
	Bool flag; // +0x634
};

struct Rva002E8BCFSrc;

struct AIUpdateView
{
	char m_pad000[0x1cc];
	char m_locomotorSet[1]; // +0x1CC
};

class Object
{
public:
	bool rva0028AFBB() const;
	Int rva0028B511() const;
	const Coord3D *getPosition() const { return &m_position; }

	void *m_vtable;
	PathfinderTemplateView *m_template; // +0x04
	char m_pad08[0x38 - 8];
	Coord3D m_position; // +0x38
	char m_pad44[0x258 - 0x44];
	AIUpdateView *m_ai; // +0x258
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

struct In002E6BA1
{
	Int x, y;
};

class MixFileInfoBuffer;
extern Int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pool, Int cell, In002E6BA1 *pos);

struct PathfinderGroundInfo
{
	Int x, y; // +0x00
	Int parent;
	void *parentWaypoint; // +0x0C
	unsigned short totalCost; // +0x10
	unsigned short costSoFar; // +0x12
	char m_pad14[0x2c - 0x14];
	unsigned int flags; // +0x2C
};

class Rva002E6AF3
{
public:
	Int get() const;
};

class Rva002E6B06
{
public:
	Int rva002E6B06();
};

class Rva002E6C79;

class PathfindCell
{
public:
	Bool StartPathfind(Int goal);
	void ReleaseInfo();
	void SetParentCell(Int *parent);
	void PutOnClosedList(MixFileInfoBuffer **list);
	Int CalcCostSoFar(const Rva002E6C79 *parent);

	__forceinline void allocateInfo(In002E6BA1 *pos)
	{
		if (!m_pathInfo)
		{
			if (!TheMixFileInfoPool)
				Rva0052DBCDInit();
			m_pathInfo = (PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool, (Int)this, pos);
		}
		else
			m_pathInfo->parentWaypoint = 0;
	}

	Int getLayer() const { return (m_info >> 4) & 0x3f; }

	PathfinderGroundInfo *m_pathInfo; // +0x00
	void *m_waypoint;
	Int m_word8;
	unsigned int m_info; // +0x0C: type bits 0-3, layer bits 4-9, connect layer bits 10-15
};

class Rva002E8BCF
{
public:
	Rva002E8BCF(const Rva002E8BCFSrc *src, Bool flag, Int priority, Bool crusher);

	Int surfaces;
	Bool field4, field5;
	Int maxLayer;
	Bool fieldC;
};

class Rva002E6DC4
{
public:
	Bool rva002E6DC4(void *info, void *cell);
};

class Path
{
public:
	Path();

	void *m_word0;
	void *m_firstNode;
	Int m_word8;
	char m_wordC; // +0x0C
	char m_padD[0x28 - 0xd];
};

// One node of the path whose cells are extra goals.
struct PathNode
{
	PathNode *m_next; // +0x00
	char m_pad04[0xc - 4];
	Coord3D m_position; // +0x0C
	PathfindLayerEnum m_layer; // +0x18
};

struct Rva002EBC7FPair
{
	Int x, y;
};

extern "C" int __cdecl abs(int);

class Pathfinder
{
public:
	virtual Path *FindCollisionFreeQuickPath(Object *obj, const Coord3D *to, PathNode *nodes);

	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	PathfindCell *rva002E8BF8(PathfindLayerEnum layer, const Coord3D *pos);
	PathfindCell *rva002F36E5();
	Int rva002F40E7();
	void CheckChangeLayers(PathfindCell *cell, Object *obj);
	Int rva002F0A72(PathfindCell *from, PathfindCell *to);
	void *rva001E3647Pos(int layer, const Coord3D *pos);
	void AddToOpenList(PathfindCell *cell);
	int CalcCollisionFreeExtraCosts(Object *obj, PathfindCell *parent, Rva002EBC7FPair *destination, PathfindLayerEnum layer, int lower, int upper, bool ignoreReservations);
	void PrependCells(Path *path, const Coord3D *fromPos, PathfindCell *goalCell, Bool center);

private:
	char m_pad004[0x34 - 4];
	MixFileInfoBuffer *m_closedList; // +0x34
	char m_pad038[0x48 - 0x38];
	Int m_48; // +0x48
};

Path *Pathfinder::FindCollisionFreeQuickPath(Object *obj, const Coord3D *to, PathNode *nodes)
{
	m_48 = 0;
	Int radius;
	Bool center;
	Rva002EBCA7Split(obj, &radius, (unsigned char *)&center);
	const Coord3D *pos = obj->getPosition();
	Coord3D from;
	from.x = pos->x;
	from.y = pos->y;
	from.z = pos->z;
	ICoord2D startCell;
	Rva002E7875WorldToCell(&startCell, center, &from);
	ICoord2D goalCell;
	Rva002E7875WorldToCell(&goalCell, center, to);
	if (startCell == goalCell)
		return 0;
	Int priority = obj->m_template->priority;
	Bool flag = obj->m_template->flag;
	Rva002E8BCF info((const Rva002E8BCFSrc *)obj->m_ai->m_locomotorSet, !flag, priority - 1, obj->rva0028AFBB());
	PathfindLayerEnum goalLayer = TheTerrainLogic->getLayerForDestination(obj, to);
	PathfindCell *goals[20];
	goals[0] = getCell(goalLayer, goalCell.x, goalCell.y);
	Int numGoals = 1;
	if (!goals[0] || !((Rva002E6DC4 *)this)->rva002E6DC4(&info, goals[0]))
		return 0;
	PathfindCell *parent = rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(), &from);
	if (!parent)
		return 0;
	goals[0]->allocateInfo((In002E6BA1 *)&goalCell);
	parent->allocateInfo((In002E6BA1 *)&startCell);
	parent->StartPathfind((Int)goals[0]);
	parent->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parent, goals[0]);
	AddToOpenList(parent);
	Int cellCount = 0;
	while (nodes && numGoals < 20)
	{
		nodes = nodes->m_next;
		if (nodes)
		{
			goals[numGoals] = (PathfindCell *)rva001E3647Pos(nodes->m_layer, &nodes->m_position);
			if (goals[numGoals])
				++numGoals;
		}
	}
	Path *path;
	while ((parent = rva002F36E5()) != 0)
	{
		for (Int g = 0; g < numGoals; ++g)
		{
			if (parent == goals[g])
			{
				path = new Path;
				PrependCells(path, pos, parent, center);
				path->m_wordC = 1;
				goto done;
			}
		}
		parent->PutOnClosedList(&m_closedList);
		if (cellCount > 3000)
			break;
		CheckChangeLayers(parent, obj);
		static Int deltaX[] = {1, 0, -1, 0, 1, -1, -1, 1};
		static Int deltaY[] = {0, 1, 0, -1, 1, 1, -1, -1};
		const Int adjacent[5] = {0, 1, 2, 3, 0};
		Bool neighborFlags[8];
		for (Int i = 0; i < 8; ++i)
		{
			neighborFlags[i] = false;
			ICoord2D next;
			next.x = parent->m_pathInfo->x + deltaX[i];
			next.y = parent->m_pathInfo->y + deltaY[i];
			PathfindCell *neighbor = getCell((PathfindLayerEnum)parent->getLayer(), next.x, next.y);
			if (!neighbor)
				continue;
			if ((unsigned char)((Rva002E6B06 *)neighbor)->rva002E6B06())
				continue;
			if ((unsigned char)((Rva002E6AF3 *)neighbor)->get())
				continue;
			Int neighborLayer = (neighbor->m_info >> 4) & 0x3f;
			Int parentLayer = (parent->m_info >> 4) & 0x3f;
			if (neighborLayer != parentLayer)
			{
				Int parentConnect = (parent->m_info >> 10) & 0x3f;
				if (neighborLayer != parentConnect)
				{
					Int neighborConnect = (neighbor->m_info >> 10) & 0x3f;
					if (neighborConnect != parentLayer && (parentConnect != 0x10 || neighborConnect != 0x10))
						continue;
				}
			}
			if (i >= 4 && !neighborFlags[adjacent[i - 4]] && !neighborFlags[adjacent[i - 3]])
				continue;
			Int extra = CalcCollisionFreeExtraCosts(obj, parent, (Rva002EBC7FPair *)&next, (PathfindLayerEnum)neighborLayer, radius, radius + (center ? 1 : 0), true);
			if (extra < 0 || !((Rva002E6DC4 *)this)->rva002E6DC4(&info, neighbor))
			{
				neighbor->allocateInfo((In002E6BA1 *)&next);
				neighbor->PutOnClosedList(&m_closedList);
				continue;
			}
			neighborFlags[i] = true;
			if (!neighbor->m_pathInfo)
			{
				++cellCount;
				if (!TheMixFileInfoPool)
					Rva0052DBCDInit();
				neighbor->m_pathInfo = (PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool, (Int)neighbor, (In002E6BA1 *)&next);
			}
			else
				neighbor->m_pathInfo->parentWaypoint = 0;
			Int cost = neighbor->CalcCostSoFar((const Rva002E6C79 *)parent);
			Int dx = abs(next.x - goals[0]->m_pathInfo->x);
			Int dy = abs(next.y - goals[0]->m_pathInfo->y);
			if ((neighbor->m_info & 0x10000) && dx + dy > 3)
				cost += 10;
			neighbor->m_pathInfo->flags &= ~1U;
			Int remaining = rva002F0A72(neighbor, goals[0]);
			if ((neighbor->m_info & 0xf) == 4)
				cost += 1000;
			neighbor->m_pathInfo->costSoFar = (unsigned short)(extra + cost);
			neighbor->SetParentCell((Int *)parent);
			neighbor->m_pathInfo->totalCost = (unsigned short)(neighbor->m_pathInfo->costSoFar + remaining);
			AddToOpenList(neighbor);
		}
	}
	path = 0;
done:
	rva002F40E7();
	goals[0]->ReleaseInfo();
	return path;
}
