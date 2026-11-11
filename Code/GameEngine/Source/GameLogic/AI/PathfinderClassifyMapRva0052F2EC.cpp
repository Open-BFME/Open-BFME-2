// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?Rva0052F2EC@Pathfinder@@QAEXXZ retail 0x0052F2EC..0x0052F63F (851 bytes).
// BFME 2's Pathfinder::classifyMap twin (Zero Hour AIPathfind.cpp; Open-BFME-1
// PathfinderClassifyMap.cpp is BFME 1's shape): over the logical extent at
// +0x14..+0x20 of the column table at +0x10 (16-byte cells) it classifies
// every cell through the rowed static Pathfinder::classifyMapCell 0x0052E11A
// then pinches clear cells next to cliffs (bit 16) and turns pinched clear
// cells into cliffs through the rowed PathfindCell::SetType_Dirty 0x0052DA1C.
// It then calls the rowed 0x0052F294 on itself and grows a deep-water edge
// mask: type-7 cells with a non type-7 neighbour set bit 23 (rowed setter
// 0x0052E0CE) and six passes spread it through type 7/1 neighbours via bit
// 22 (rowed setter 0x0052E02F). Callgraph twin WB 0x012D86D0.

typedef int Int;

class Rva0052E02F
{
public:
	bool rva0052E02F(bool value);
};

class Rva0052E0CE
{
public:
	bool rva0052E0CE(bool value);
};

#include "../../../Include/GameLogic/Rva002E713FOwner.h"

#include "../../../Include/GameLogic/PathfindCell.h"

// Cell types 2 and 7 have no name in PathfindCell::CellType yet.
static const Int CELL_TYPE_CLIFF = 2;
static const Int CELL_TYPE_DEEP_WATER = 7;

// Retail inlines these accesses to the packed dword at +0x0C: pinched bit 16,
// edge bits 22 and 23; the bit 22/23 setters are the rowed out-of-line bodies.
static __forceinline void setCellPinched(PathfindCell *cell)
{
	cell->m_0C |= 0x10000u;
}
static __forceinline bool getCellBit22(const PathfindCell *cell)
{
	return ((cell->m_0C >> 22) & 1) != 0;
}
static __forceinline bool getCellBit23(const PathfindCell *cell)
{
	return ((cell->m_0C >> 23) & 1) != 0;
}
static __forceinline void setCellBit22(PathfindCell *cell, bool on)
{
	reinterpret_cast<Rva0052E02F *>(cell)->rva0052E02F(on);
}
static __forceinline void setCellBit23(PathfindCell *cell, bool on)
{
	reinterpret_cast<Rva0052E0CE *>(cell)->rva0052E0CE(on);
}

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/IRegion2D.h"

#include "../../../Include/GameLogic/AIPathfind.h"

void Pathfinder::Rva0052F2EC()
{
	Int i, j;
	for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
	{
		for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
		{
			classifyMapCell(i, j, &m_map[i][j]);
		}
	}

	for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
	{
		for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
		{
			if (m_map[i][j].getType() == CELL_TYPE_CLIFF)
			{
				for (Int k = i - 1; k < i + 2; k++)
				{
					if (k < m_extent.lo.x || k > m_extent.hi.x)
						continue;
					for (Int l = j - 1; l < j + 2; l++)
					{
						if (l < m_extent.lo.y || l > m_extent.hi.y)
							continue;
						if (m_map[k][l].getType() == PathfindCell::CELL_CLEAR)
						{
							setCellPinched(&m_map[k][l]);
						}
					}
				}
			}
		}
	}

	for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
	{
		for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
		{
			if (m_map[i][j].getPinched() && m_map[i][j].getType() == PathfindCell::CELL_CLEAR)
			{
				m_map[i][j].SetType_Dirty(CELL_TYPE_CLIFF);
			}
		}
	}

	reinterpret_cast<Rva002E713FOwner *>(this)->rva0052F294();

	for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
	{
		for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
		{
			PathfindCell *cell = &m_map[i][j];
			if (cell->getType() == CELL_TYPE_DEEP_WATER)
			{
				if ((i > m_extent.lo.x && m_map[i - 1][j].getType() != CELL_TYPE_DEEP_WATER)
					|| (i < m_extent.hi.x && m_map[i + 1][j].getType() != CELL_TYPE_DEEP_WATER)
					|| (j > m_extent.lo.y && m_map[i][j - 1].getType() != CELL_TYPE_DEEP_WATER)
					|| (j < m_extent.hi.y && m_map[i][j + 1].getType() != CELL_TYPE_DEEP_WATER))
				{
					setCellBit23(cell, true);
				}
			}
		}
	}

	for (Int pass = 0; pass < 6; pass++)
	{
		for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
		{
			for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
			{
				if (getCellBit23(&m_map[i][j]))
				{
					if (i > m_extent.lo.x && (m_map[i - 1][j].getType() == CELL_TYPE_DEEP_WATER || m_map[i - 1][j].getType() == PathfindCell::CELL_WATER))
						setCellBit22(&m_map[i - 1][j], true);
					if (i < m_extent.hi.x && (m_map[i + 1][j].getType() == CELL_TYPE_DEEP_WATER || m_map[i + 1][j].getType() == PathfindCell::CELL_WATER))
						setCellBit22(&m_map[i + 1][j], true);
					if (j > m_extent.lo.y && (m_map[i][j - 1].getType() == CELL_TYPE_DEEP_WATER || m_map[i][j - 1].getType() == PathfindCell::CELL_WATER))
						setCellBit22(&m_map[i][j - 1], true);
					if (j < m_extent.hi.y && (m_map[i][j + 1].getType() == CELL_TYPE_DEEP_WATER || m_map[i][j + 1].getType() == PathfindCell::CELL_WATER))
						setCellBit22(&m_map[i][j + 1], true);
				}
			}
		}

		for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
		{
			for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
			{
				Int type = m_map[i][j].getType();
				if (getCellBit22(&m_map[i][j])
					&& (type == CELL_TYPE_DEEP_WATER || type == PathfindCell::CELL_WATER))
				{
					setCellBit22(&m_map[i][j], false);
					setCellBit23(&m_map[i][j], true);
				}
			}
		}
	}
}
