// ?clearCellForDiameter@Pathfinder@@QAEHIHHW4PathfindLayerEnum@@H_N@Z
// partial score=0.65 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// Pathfinder::clearCellForDiameter, retail 0x002E7749 (300B, ret 0x18), and
// its TU-local cell test 0x002E76D3 (118B; cell in EDI, crusher level and the
// unit flag on the stack, caller-cleaned - MSVC's register convention for a
// static helper). Zero Hour's Pathfinder::clearCellForDiameter is the donor
// for the radius / numCellsAbove square, the trimmed outside corners when the
// radius exceeds one and the 2*radius (or 1) result. BFME 2 passes a crusher
// LEVEL instead of a bool, tests each cell through the static helper (the
// rowed cell query 0x0052DB11 gates a walk over the cell info's +0x20 object
// list comparing Object 0x0028CE7B crushable levels; obstacle cells, type 4,
// pass only for a non-zero level when info +0x2C bit 1 is set) and, when a
// corner-trimmed square fails and the last argument is clear, retries two
// cells narrower (the tail call is the native jump back to the top).
// The existing caller pin ?rva002E7749@Pathfinder@@QAEHPAXHHHH_N@Z names the
// same address.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum PathfindLayerEnum { LAYER_INVALID = 0 };

class Object
{
public:
	signed char rva0028CE7B() const;
};

struct PathfindObjectNode
{
	PathfindObjectNode *m_next;		// +0x00
	Int m_04;
	Object *m_object;			// +0x08
};

struct PathfindCellInfo
{
	unsigned char m_pad00[0x20];
	PathfindObjectNode *m_objects;		// +0x20
	unsigned char m_pad24[0x2C - 0x24];
	UnsignedInt m_blocked : 1;		// +0x2C bit 0
	UnsignedInt m_obstacleIsFence : 1;	// +0x2C bit 1
};

class PathfindCell
{
public:
	Bool rva0052DB11(Int arg);
	UnsignedInt isObstacleFence() const { return m_info ? m_info->m_obstacleIsFence : 0; }
	PathfindCellInfo *m_info;		// +0x00
	unsigned char m_pad04[0x0C - 4];
	UnsignedInt m_typeFlags;		// +0x0C, type in the low nibble
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	Int clearCellForDiameter(UnsignedInt crusherLevel, Int cellX, Int cellY, PathfindLayerEnum layer, Int pathDiameter, Bool exact);
};

static Bool isCellClearForCrusher(PathfindCell *cell, UnsignedInt crusherLevel, Bool checkUnits)
{
	if (checkUnits && cell->rva0052DB11(0))
	{
		for (PathfindObjectNode *node = cell->m_info ? cell->m_info->m_objects : 0; node; node = node->m_next)
		{
			if ((UnsignedInt)node->m_object->rva0028CE7B() > crusherLevel)
				return false;
		}
	}
	UnsignedInt type = cell->m_typeFlags & 0xf;
	if (type != 0)
	{
		if (type == 4)
			return crusherLevel && cell->isObstacleFence();
		return false;
	}
	return true;
}

Int Pathfinder::clearCellForDiameter(UnsignedInt crusherLevel, Int cellX, Int cellY, PathfindLayerEnum layer, Int pathDiameter, Bool exact)
{
	Int radius = pathDiameter / 2;
	Int numCellsAbove = radius;
	if (radius == 0)
		numCellsAbove++;
	Int iStart = cellX - radius;
	Int iEnd = cellX + numCellsAbove;
	if (radius > 1)
	{
		for (Int i = iStart; i < iEnd; i++)
		{
			Int jStart, jEnd;
			if (i == iStart || i == iEnd - 1)
			{
				jEnd = numCellsAbove + cellY - 1;
				jStart = -radius + cellY + 1;
			}
			else
			{
				jEnd = numCellsAbove + cellY;
				jStart = -radius + cellY;
			}
			for (Int j = jStart; j < jEnd; j++)
			{
				PathfindCell *cell = getCell(layer, i, j);
				if (!cell || !isCellClearForCrusher(cell, crusherLevel, true))
				{
					if (exact)
						return 0;
					return clearCellForDiameter(crusherLevel, cellX, cellY, layer, pathDiameter - 2, false);
				}
			}
		}
	}
	else
	{
		for (Int i = iStart; i < iEnd; i++)
		{
			for (Int j = cellY - radius; j < cellY + numCellsAbove; j++)
			{
				PathfindCell *cell = getCell(layer, i, j);
				if (!cell || !isCellClearForCrusher(cell, crusherLevel, true))
					return 0;
			}
		}
	}
	if (radius == 0)
		return 1;
	return 2 * radius;
}
