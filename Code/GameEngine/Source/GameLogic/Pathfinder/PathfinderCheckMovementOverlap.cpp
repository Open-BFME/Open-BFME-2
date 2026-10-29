// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
// Pathfinder second-footprint movement check, retail 002EA658..002EAA41
// (1001 bytes, RET 12). WorldBuilder D5B720 calls the per-cell check D5B030;
// retail inlines it. The established 002EA0BA/002EA34A sibling layouts and
// Zero Hour AIPathfind.cpp checkForMovement supply the semantic guide.
// Cells shared with otherCell only contribute terrain flags. Other cells
// additionally check occupants, allies, crushing and the current target.
// WB D5B1FD..D5B22E uses one compound skip condition for the mover, ignored
// object and last object. Keeping that condition joined reproduces the EBX
// owner and final full-word kind-BA test without a volatile pointer read.
// The ordinal kind bits and neutral field names describe observed BFME2
// accesses; the original helper name is not asserted.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 0
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

#include "Lib/ICoord2D.h"

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(UnsignedInt bit) const { return m_kindOf[bit >> 5] & (1U << (bit & 0x1f)); }

	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[8]; // +0x108
};

class Object;

class StateMachine
{
public:
	Object *getGoalObject();
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;

	unsigned char m_pad00[0x30];
	StateMachine *m_stateMachine; // +0x30
};

class Object
{
public:
	Bool rva0028AFBB() const;
	Relationship getRelationship(const Object *that) const;
	Bool IsAtGoalPosition() const;
	Bool canCrushOrSquishNoAlly(Object *other, Int test);

	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() const { return m_ai; }

	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_274; // +0x274
};

struct PathfindCellObjectNode
{
	PathfindCellObjectNode *m_next;
	int m_04;
	Object *m_object; // +0x08
};

struct PathfindCellInfo
{
	unsigned char m_pad00[0x14];
	int m_14;
	unsigned char m_pad18[0x20 - 0x18];
	PathfindCellObjectNode *m_objects; // +0x20
};

class PathfindCell
{
public:
	Int getType() const { return m_flags & 0xf; }
	Int getLayer() const { return (m_flags >> 4) & 0x3f; }
	Bool rvaBit18() const { return (Bool)((m_flags >> 18) & 1); }
	Bool rvaInfo14() const { return m_info ? m_info->m_14 != 0 : false; }
	Bool hasObjects() const { return m_info ? m_info->m_objects != 0 : false; }
	PathfindCellObjectNode *getObjects() const { return m_info ? m_info->m_objects : 0; }

	PathfindCellInfo *m_info;
	unsigned char m_pad04[0x0C - 0x04];
	UnsignedInt m_flags; // +0x0C
};

struct TCheckMovementInfo
{
	ICoord2D cell; // +0x00
	PathfindLayerEnum layer; // +0x08
	Int radius; // +0x0C
	Bool centerInCell; // +0x10
	Bool m_11;
	unsigned char m_pad12[2];
	UnsignedInt m_14; // +0x14 option bits
	ObjectID m_18; // +0x18 an object to ignore
	unsigned char m_1C[0x10]; // +0x1C
	Int m_2C;
	Bool m_30;
	Bool m_31;
	Bool m_32;
	unsigned char m_pad33;
	Int m_34; // +0x34 count of blocking cells
};

int Rva002E6E8AGet(int layer);

class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a_raw, void *b_raw);
	char m_pad00[0x48];
private:
	void *m_48; // +0x48
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	Bool rva002EA658(Object *obj, TCheckMovementInfo &info, const ICoord2D *otherCell);

private:
	__forceinline void checkCellFlags(Object *obj, PathfindCell *cell, TCheckMovementInfo &info)
	{
		if (cell->getType() == 5)
			info.m_34++;
		if (cell->rvaBit18() && obj->rva0028AFBB())
			info.m_34++;
		if (info.m_14 & 8)
		{
			Int layer = cell->getLayer();
			if (info.layer != layer)
			{
				if (info.layer == 1 && layer != 0x10)
					info.m_34++;
				else if ((unsigned char)Rva002E6E8AGet(info.layer) && layer != 0x10)
					info.m_34++;
			}
		}
		if ((info.m_14 & 4) && !((Rva002E6DC4 *)this)->rva002E6DC4(info.m_1C, cell))
			info.m_34++;
	}

	__forceinline Bool checkPairCellUnits(Object *&obj, PathfindCell *cell, TCheckMovementInfo &info, ObjectID *lastID)
	{
		if (cell->rvaInfo14())
			info.m_32 = true;

		for (PathfindCellObjectNode *node = cell->getObjects(); node; node = node->m_next)
		{
			Object *unit = node->m_object;
			if (unit == obj || unit->getID() == info.m_18 || unit->getID() == *lastID)
				continue;
			*lastID = unit->getID();

			Bool check = false;
			Bool isAlly;
			unsigned occupied = cell->hasObjects();
			Object *owner = obj;
			if (occupied)
			{
				isAlly = owner->getRelationship(unit) == ALLIES;
				if (isAlly)
					info.m_31 = true;
				if (info.m_11)
					check = true;
				if (!isAlly && (info.m_14 & 0x10))
					check = true;
			}
			if (unit->IsAtGoalPosition())
			{
				isAlly = owner->getRelationship(unit) == ALLIES;
				check = true;
			}
			if (!check)
				continue;

			if (isAlly && owner->getTemplate()->isKindOf(0x74) && unit->getTemplate()->isKindOf(0x74))
				continue;
			if (owner->getTemplate()->isKindOf(0x7D) && unit->getTemplate()->isKindOf(8))
				continue;
			if (isAlly && owner->getTemplate()->isKindOf(0xBA) && !unit->getTemplate()->isKindOf(0xBA))
			{
				info.m_32 = false;
				continue;
			}
			if (owner->getTemplate()->isKindOf(0xBB))
			{
				info.m_32 = false;
				continue;
			}

			if (isAlly)
			{
				if (!unit->getAI())
					return false;
				if (info.m_14 & 2)
					return false;
				info.m_2C = 1;
				if (unit->getTemplate()->isKindOf(0xBA) && !owner->getTemplate()->isKindOf(0xBA))
					return false;
				continue;
			}

			if (owner->canCrushOrSquishNoAlly(unit, 2))
				continue;
			if (!(info.m_14 & 0x11))
				continue;
			AIUpdateInterface *ai = obj->getAI();
			if (!ai)
				return false;
			Object *goal = ai->m_stateMachine->getGoalObject();
			if (goal)
			{
				if (unit == goal || unit->m_274 == goal)
					continue;
				goal = goal->m_274;
				if (goal && (unit == goal || unit->m_274 == goal))
					continue;
			}
			Object *victim = ai->getCurrentVictim();
			if (!victim)
				return false;
			if (unit == victim || unit->m_274 == victim)
				continue;
			victim = victim->m_274;
			if (!victim)
				return false;
			if (unit == victim || unit->m_274 == victim)
				continue;
			return false;
		}
		return true;
	}
};

__declspec(noinline) inline Bool Pathfinder::rva002EA658(Object *obj, TCheckMovementInfo &info, const ICoord2D *otherCell)
{
	info.m_2C = 0;
	info.m_31 = false;
	info.m_32 = false;
	info.m_30 = false;
	info.m_34 = 0;

	Int numCellsAbove = info.radius;
	if (info.centerInCell)
		numCellsAbove++;

	ObjectID lastID = INVALID_ID;
	for (Int i = info.cell.x - info.radius; i < info.cell.x + numCellsAbove; i++)
	{
		Bool inOtherX = i >= otherCell->x - info.radius && i < otherCell->x + numCellsAbove;
		for (Int j = info.cell.y - info.radius; j < info.cell.y + numCellsAbove; j++)
		{
			PathfindCell *cell = getCell(info.layer, i, j);
			if (!cell)
				return false;
			if (inOtherX && j >= otherCell->y - info.radius && j < otherCell->y + numCellsAbove)
			{
				checkCellFlags(obj, cell, info);
			}
			else
			{
				checkCellFlags(obj, cell, info);
				if (!checkPairCellUnits(obj, cell, info, &lastID))
					return false;
			}
		}
	}
	return true;
}

// Select-any: PathfinderRva002F83F5Neighbors.cpp compiles an identical copy; the anchor keeps the rowed body emitted.
// ?bfmeAnchorRva002EA658 absent-from-retail
Bool bfmeAnchorRva002EA658(Pathfinder *pathfinder, Object *obj, TCheckMovementInfo &info, const ICoord2D *otherCell) { return pathfinder->rva002EA658(obj, info, otherCell); }
