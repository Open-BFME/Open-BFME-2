// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// ?rva002E9EA7@Pathfinder@@QAE_NPAVObject@@HHW4PathfindLayerEnum@@HEPAH@Z
// retail 0x002E9EA7..0x002EA0BA (531 B, ret 0x1c). WorldBuilder twin va 0xD5AC00
// (1071 B debug, callgraph 3.0): same callees (getCell 0x2E6D62, the cell
// point 0x2E79A8, TheTerrainLogic slot 50, IsObstaclePresent 0x2E6C23,
// getRelationship 0x28D156, IsAtGoalPosition 0x28ADB0, getIgnoredObstacleID
// 0x6E009) and constants (kindOf bits 0x6D/0x5A/8, layer 1, ALLIES, +1/+3).
// Shape follows WB literally; semantics are the ZH Pathfinder::checkDestination
// family (radius/centerInCell rectangle, IS_IMPASSABLE, ignoreId/objID).
// The name stays address-derived: WB has no symbol for it.
typedef bool Bool;
typedef int Int;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

#include "../../../../Libraries/Include/Lib/Coord3D.h"
struct PathfinderCellPoint : Coord3D {
	__forceinline PathfinderCellPoint() {}
	__forceinline PathfinderCellPoint(const PathfinderCellPoint &pathfinderCellPoint) { x = pathfinderCellPoint.x; y = pathfinderCellPoint.y; z = pathfinderCellPoint.z; }
	__forceinline ~PathfinderCellPoint() {}
};
enum Relationship { ENEMIES = 0, NEUTRAL, ALLIES };
enum PathfindLayerEnum { LAYER_GROUND = 0, LAYER_WALL = 1 };
enum ObjectID { INVALID_ID = 0 };
PathfinderCellPoint rva002E79A8(Bool centerInCell, Int cellX, Int cellY, PathfindLayerEnum layer);

#include "../../../Include/Common/ThingTemplate.h"

#include "../../../Include/GameLogic/Module/AIUpdate.h"

class Object
{
public:
	Bool rva0028AFBB() const;
	Relationship getRelationship(const Object *other) const;
	Bool IsAtGoalPosition() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Object *getContainedBy() const { return m_containedBy; }
private:
	char m_pad000[4];
	ThingTemplate *m_template;			// +0x004
	char m_pad008[0x74 - 8];
	ObjectID m_id;						// +0x074
	char m_pad078[0x258 - 0x78];
	AIUpdateInterface *m_ai;			// +0x258
	char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy;				// +0x274
};

struct PathfindObjectNode
{
	PathfindObjectNode *m_next;			// +0x00
	char m_pad04[4];
	Object *m_obj;						// +0x08
};

struct PathfindCellInfo
{
	char m_pad00[0x14];
	PathfindObjectNode *m_goalList;		// +0x14
	char m_pad18[8];
	PathfindObjectNode *m_presentList;	// +0x20
};

class PathfindCell
{
public:
	enum CellType
	{
		CELL_CLEAR = 0, CELL_WATER = 1, CELL_CLIFF = 2, CELL_RUBBLE = 3,
		CELL_OBSTACLE = 4, CELL_BRIDGE_IMPASSABLE = 5, CELL_IMPASSABLE = 6
	};
	Bool IsObstaclePresent(ObjectID id) const;
	CellType getType() const { return (CellType)(m_flags & 0xf); }
	UnsignedByte getFlag18() const { return (UnsignedByte)((m_flags >> 18) & 1); }
	PathfindCellInfo *getInfo() const { return m_info; }
private:
	PathfindCellInfo *m_info;			// +0x00
	char m_pad04[8];
	UnsignedInt m_flags;				// +0x0C
};

#include "../../../Include/GameLogic/AIPathfind.h"

// TheTerrainLogic vtable slot 50 (+0xC8): a bool probe of a world point.
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

// ZH AIPathfind.cpp IS_IMPASSABLE; BFME tests in WB's order 5, 4, 6.
static inline Bool IS_IMPASSABLE(PathfindCell::CellType type)
{
	if (type == PathfindCell::CELL_BRIDGE_IMPASSABLE)
		return true;
	if (type == PathfindCell::CELL_OBSTACLE)
		return true;
	if (type == PathfindCell::CELL_IMPASSABLE)
		return true;
	return false;
}

bool Pathfinder::rva002E9EA7(Object *obj, Int cellX, Int cellY, PathfindLayerEnum layer, Int iRadius, UnsignedByte centerInCell, Int *count)
{
	if ((obj->getTemplate()->m_kindof[3] & (1U << (0x6d & 0x1f))))
	{
		if (layer != LAYER_WALL)
		{
			iRadius = 1;
			centerInCell = true;
		}
		else
		{
			PathfinderCellPoint pos = rva002E79A8(true, cellX, cellY, LAYER_WALL);
			if (TheTerrainLogic->slot50(&pos))
			{
				iRadius = 1;
				centerInCell = true;
			}
		}
	}
	if ((obj->getTemplate()->m_kindof[2] & (1U << (0x5a & 0x1f))) && (obj->getTemplate()->m_kindof[0] & (1U << (8 & 0x1f))) && layer != LAYER_WALL)
	{
		iRadius = 1;
		centerInCell = false;
	}
	Int numCellsAbove = iRadius;
	if (centerInCell)
		numCellsAbove++;
	ObjectID ignoreId = INVALID_ID;
	ObjectID objID = INVALID_ID;
	*count = 0;
	if (obj->getAI())
	{
		ignoreId = obj->getAI()->getIgnoredObstacleID();
		objID = obj->getID();
	}
	for (Int i = cellX - iRadius; i < cellX + numCellsAbove; i++)
	{
		for (Int j = cellY - iRadius; j < cellY + numCellsAbove; j++)
		{
			PathfindCell *cell = getCell(layer, i, j);
			if (cell == 0)
				return false;
			if (cell->getType() == PathfindCell::CELL_BRIDGE_IMPASSABLE)
				return false;
			if (cell->getFlag18() && obj->rva0028AFBB())
				return false;
			if (cell->getType() == PathfindCell::CELL_CLIFF)
				return false;
			if (cell->getType() == PathfindCell::CELL_OBSTACLE)
			{
				if (cell->IsObstaclePresent(ignoreId))
					continue;
				return false;
			}
			if (IS_IMPASSABLE(cell->getType()))
				return false;
			if (cell->getFlag18() && obj->rva0028AFBB())
				return false;
			for (PathfindObjectNode *node = cell->getInfo() ? cell->getInfo()->m_goalList : 0; node; node = node->m_next)
			{
				if (node->m_obj->getID() == objID)
					continue;
				if (node->m_obj->getID() == ignoreId)
					continue;
				Object *unit = node->m_obj;
				if (unit->getContainedBy() == obj)
					continue;
				if (obj->getRelationship(unit) == ALLIES)
					(*count)++;
				else if (unit->IsAtGoalPosition())
					return false;
			}
			for (PathfindObjectNode *pathfindObjectNode = cell->getInfo() ? cell->getInfo()->m_presentList : 0; pathfindObjectNode; pathfindObjectNode = pathfindObjectNode->m_next)
			{
				if (pathfindObjectNode->m_obj->getID() == objID)
					continue;
				Object *unit = pathfindObjectNode->m_obj;
				if (unit->getContainedBy() == obj)
					continue;
				if (obj->getRelationship(unit) == ALLIES)
					*count += 3;
				else
					(*count)++;
			}
		}
	}
	return true;
}
