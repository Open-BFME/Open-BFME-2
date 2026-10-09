// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?cellCallback@Rva002F4491Info@@QAEHPAVPathfindCell@@0HH@Z retail
// 0x002F4491..0x002F462C (411 bytes) RET 0x10. Line-walk callback (called
// with previous cell then current cell then x and y from the rowed walk at
// 0x002F69E3) of a BFME 2 descendant of Zero Hour's
// Pathfinder::examineCellsCallback; WB twin 0x00D69330 (callgraph 2.0) keeps
// the same order with GetCostSoFar SetCostSoFar SetParentCell SetTotalCost
// and AddToOpenList. Without a previous cell it returns 0; a current cell
// already open or closed (rowed getters 0x002E6AF3 and 0x002E6B06) aborts
// as does a cell whose world point (x*10 y*10) lies on a burning grid cell
// of TheTriggerManager (inline grid at +0x70 sized +0x78/+0x7C with a
// 0x14-byte cell counter at +6) or one whose achieved clearance (pinned
// Pathfinder 0x002E7749) is not the requested one at +0xC. Otherwise the
// cell info is allocated from TheMixFileInfoPool (rowed 0x0052DBCD and
// 0x002E8B7A) or its +0xC cleared and the +0x2C bit 0 dropped; its cost so
// far becomes the previous cell's plus 2 (bit 21 set) or 5 and its total
// adds the rowed Pathfinder 0x002F0A72 estimate to the goal at +0x8 before
// the rowed SetParentCell 0x0052DAC4 and AddToOpenList 0x002F436F.
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

struct In002E6BA1
{
	Int m_00;
	Int m_04;
};

class MixFileInfoBuffer
{
public:
	char m_pad00[0x0C];
	Int m_0C;
	unsigned short m_totalCost;
	unsigned short m_costSoFar;
	char m_pad14[0x2C - 0x14];
	unsigned int m_flags;
};

extern int TheMixFileInfoPool;
void Rva0052DBCDInit(void);
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, int a, In002E6BA1 *in);

class Rva002E6AF3
{
public:
	int get() const;
};

class Rva002E6B06
{
public:
	int rva002E6B06();
};

class PathfindCell
{
public:
	Bool getOpen() const { return (unsigned char)reinterpret_cast<const Rva002E6AF3 *>(this)->get() != 0; }
	Bool getClosed() { return (unsigned char)reinterpret_cast<Rva002E6B06 *>(this)->rva002E6B06() != 0; }
	Int getLayer() const { return (m_flags >> 4) & 0x3F; }
	Bool getBit21() const { return ((m_flags >> 21) & 1) != 0; }
	unsigned short getCostSoFar() const { return m_info->m_costSoFar; }
	void setCostSoFar(unsigned short cost) { m_info->m_costSoFar = cost; }
	void setTotalCost(unsigned short cost) { m_info->m_totalCost = cost; }
	void SetParentCell(int *source);
	__forceinline void allocateInfo(In002E6BA1 *coord)
	{
		if (!m_info)
		{
			if (TheMixFileInfoPool == 0)
				Rva0052DBCDInit();
			m_info = Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool, (int)this, coord);
		}
		else
		{
			m_info->m_0C = 0;
		}
	}
	void setBlockedByAlly() { m_info->m_flags &= ~1u; }

	MixFileInfoBuffer *m_info;
	char m_pad04[0x0C - 4];
	unsigned int m_flags;
};

struct Rva002F4491FireCell
{
	char m_pad00[6];
	unsigned short m_count;
	char m_pad08[0x14 - 8];
};

class Rva002872BA
{
public:
	static __forceinline Int realToIntFloor(Real f)
	{
		Real floored = (Real)floor(f);
		long i;
		__asm {
			fld [floored]
			fistp [i]
		}
		return i;
	}
	__forceinline Bool isBurning(const Coord3D &pos) const
	{
		Int x = realToIntFloor((pos.x + 0.5f) * 0.1f);
		Int y = realToIntFloor((pos.y + 0.5f) * 0.1f);
		if (x >= 0 && x < m_width && y >= 0 && y < m_height)
			return m_cells[x][y].m_count > 0;
		return false;
	}

private:
	char m_pad00[0x70];
	Rva002F4491FireCell **m_cells;
	char m_pad74[4];
	Int m_width;
	Int m_height;
};
extern Rva002872BA *TheTriggerManager;

class Pathfinder
{
public:
	int rva002E7749(void *object, int x, int y, int layer, int clearance, bool exact);
	int rva002F0A72(PathfindCell *cell, PathfindCell *goal);
	void AddToOpenList(PathfindCell *cell);
};

struct Rva002F4491Info
{
	Pathfinder *pathfinder;
	int m_04;
	PathfindCell *goalCell;
	int clearance;
	int cellCallback(PathfindCell *from, PathfindCell *to, int x, int y);
};

int Rva002F4491Info::cellCallback(PathfindCell *from, PathfindCell *to, int x, int y)
{
	if (!from)
		return 0;
	if (to->getOpen() || to->getClosed())
		return 1;
	{
		Coord3D pos;
		pos.x = (Real)(x * 10);
		pos.y = (Real)(y * 10);
		if (TheTriggerManager->isBurning(pos))
			return 1;
	}
	if (pathfinder->rva002E7749(0, x, y, to->getLayer(), clearance, true) != clearance)
		return 1;
	{
		In002E6BA1 coord;
		coord.m_00 = x;
		coord.m_04 = y;
		to->allocateInfo(&coord);
	}
	to->setBlockedByAlly();
	unsigned int newCostSoFar = from->getCostSoFar() + (to->getBit21() ? 2 : 5);
	Int costRemaining = pathfinder->rva002F0A72(to, goalCell);
	to->setCostSoFar((unsigned short)newCostSoFar);
	to->SetParentCell((int *)from);
	to->setTotalCost((unsigned short)(to->getCostSoFar() + costRemaining));
	pathfinder->AddToOpenList(to);
	return 0;
}
