// cl: /DNDEBUG /MD /EHs-c- /Ob2
// ?getShroudedStatus@PartitionData@@QAE?AW4ObjectShroudStatus@@H@Z, retail 0x0073A6D0, 392 bytes.
// Identity: the pinned name; callers W3DGhostObjectScene 0x6350F and 0x28D2BA.
// Donor: BFME1 game/GameEngine/Source/GameLogic/Object/PartitionManager.cpp
// getShroudedStatus (cached per-player status, counted cell shroud states,
// ghost snapshot bookkeeping). Target evidence: retail drops the donor's
// updatedSinceLastReset test, reads the cell shroud word at
// [cell + player*8 + 4] (0xFFFF shrouded, 0 fogged, else clear) and has one
// return of the cached status shared by the early-out.
// Structural inference: the inline cell-status helper and field names follow
// the donor; layout offsets are from retail.

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID = 0,
	OBJECTSHROUD_CLEAR = 1,
	OBJECTSHROUD_PARTIAL_CLEAR = 2,
	OBJECTSHROUD_FOGGED = 3,
	OBJECTSHROUD_SHROUDED = 4
};

struct ShroudEntry
{
	unsigned short status;
	unsigned char pad[6];
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0,
	CELLSHROUD_FOGGED = 1,
	CELLSHROUD_SHROUDED = 2
};

// This partial cell view reads the BFME2 shroud layout directly; the
// donor PartitionCell method has a different layout and remains out of line.
class PartitionDataShroudCellView
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const
	{
		unsigned short s = m_shroud[playerIndex].status;
		if (s == 0xFFFF)
			return CELLSHROUD_SHROUDED;
		return (CellShroudStatus)(s == 0);
	}
	void *m_first;
	ShroudEntry m_shroud[20];
};

struct CellAndObjectIntersection
{
	PartitionDataShroudCellView *m_cell;
	void *m_module;
	void *m_prev;
	void *m_next;
};

class ShroudObject
{
public:
	virtual ~ShroudObject();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void d4();
	virtual bool checkVisible(int playerIndex);
};

class ShroudGhost
{
public:
	virtual ~ShroudGhost();
	virtual void d1();
	virtual void snapShot(int playerIndex);
	virtual void freeSnapShot(int playerIndex);
};

#include "../../Include/GameLogic/PartitionData.h"

ObjectShroudStatus PartitionData::getShroudedStatus(int playerIndex)
{
	if (playerIndex < 0 || playerIndex >= 20)
		return OBJECTSHROUD_SHROUDED;
	if (m_shroudedness[playerIndex] == OBJECTSHROUD_INVALID)
	{
		int shroudedCells = 0;
		int total = 0;
		int foggedCells = 0;
		CellAndObjectIntersection *end = m_coiArray + m_coiInUseCount;
		for (CellAndObjectIntersection *coi = m_coiArray; coi != end; ++coi)
		{
			PartitionDataShroudCellView *cell = coi->m_cell;
			if (cell)
			{
				++total;
				switch (cell->getShroudStatusForPlayer(playerIndex))
				{
				case CELLSHROUD_FOGGED:
					++foggedCells;
					break;
				case CELLSHROUD_SHROUDED:
					++shroudedCells;
					break;
				}
			}
		}

		if (total == 0 || shroudedCells == total)
		{
			m_shroudedness[playerIndex] = OBJECTSHROUD_SHROUDED;
			m_everSeenByPlayer[playerIndex] = 0;
			if (((ShroudGhost *)m_field08) && m_shroudednessPrevious[playerIndex] == OBJECTSHROUD_FOGGED)
				((ShroudGhost *)m_field08)->freeSnapShot(playerIndex);
		}
		else if (shroudedCells + foggedCells == total)
		{
			m_shroudedness[playerIndex] = OBJECTSHROUD_FOGGED;
			if (((ShroudObject *)m_field04) && ((ShroudGhost *)m_field08))
			{
				if (((ShroudObject *)m_field04)->checkVisible(playerIndex))
					m_shroudedness[playerIndex] = OBJECTSHROUD_SHROUDED;
				else if (m_shroudednessPrevious[playerIndex] != OBJECTSHROUD_FOGGED)
					((ShroudGhost *)m_field08)->snapShot(playerIndex);
			}
		}
		else if (shroudedCells == 0 && foggedCells == 0)
		{
			m_everSeenByPlayer[playerIndex] = 1;
			m_shroudedness[playerIndex] = OBJECTSHROUD_CLEAR;
			if (((ShroudGhost *)m_field08) && m_shroudednessPrevious[playerIndex] != OBJECTSHROUD_CLEAR)
				((ShroudGhost *)m_field08)->freeSnapShot(playerIndex);
		}
		else
		{
			m_everSeenByPlayer[playerIndex] = 1;
			m_shroudedness[playerIndex] = OBJECTSHROUD_PARTIAL_CLEAR;
			if (((ShroudGhost *)m_field08) && m_shroudednessPrevious[playerIndex] != OBJECTSHROUD_PARTIAL_CLEAR)
				((ShroudGhost *)m_field08)->freeSnapShot(playerIndex);
		}

		if (total)
			m_shroudednessPrevious[playerIndex] = m_shroudedness[playerIndex];
	}

	return (ObjectShroudStatus)m_shroudedness[playerIndex];
}
