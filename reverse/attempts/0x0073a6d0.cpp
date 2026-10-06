// ?getShroudedStatus@PartitionData@@QAE?AW4ObjectShroudStatus@@H@Z
// partial score=0.95 date=2026-10-06
// ?getShroudedStatus@PartitionData@@QAE?AW4ObjectShroudStatus@@H@Z
// partial score=0.95 date=2026-10-04
// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2
// ?getShroudedStatus@PartitionData@@QAE?AW4ObjectShroudStatus@@H@Z @0x0073A6D0 392B via BFME1 donor PartitionManager.cpp simplified shroud loop
// Evidence: pinned name; callers W3DGhostObjectScene 0x6350F and 0x28D2BA; donor game/GameEngine/Source/GameLogic/Object/PartitionManager.cpp getShroudedStatus; retail drops updatedSinceLastReset and inlines cell shroud word at [cell+player*8+4]

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

class PartitionCell
{
public:
	void *m_first;
	ShroudEntry m_shroud[20];
};

struct CellAndObjectIntersection
{
	PartitionCell *m_cell;
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

class PartitionData
{
public:
	ObjectShroudStatus getShroudedStatus(int playerIndex);

private:
	void *m_owner;
	ShroudObject *m_object;
	ShroudGhost *m_ghost;
	void *m_next;
	void *m_prev;
	void *m_prevDirty;
	void *m_nextDirty;
	CellAndObjectIntersection *m_coiArray;
	int m_coiInUseCount;
	int m_shroudedness[20];
	int m_shroudednessPrevious[20];
	unsigned char m_everSeen[20];
};

// ?getShroudedStatus@PartitionData@@QAE?AW4ObjectShroudStatus@@H@Z present-unmatched
ObjectShroudStatus PartitionData::getShroudedStatus(int playerIndex)
{
	if (playerIndex < 0 || playerIndex >= 20)
		return OBJECTSHROUD_SHROUDED;
	if (m_shroudedness[playerIndex] != OBJECTSHROUD_INVALID)
		return (ObjectShroudStatus)m_shroudedness[playerIndex];

	int shroudedCells = 0;
	int total = 0;
	int foggedCells = 0;
	CellAndObjectIntersection *coi = m_coiArray;
	CellAndObjectIntersection *end = (CellAndObjectIntersection *)((char *)coi + m_coiInUseCount * 16);
	for (; coi != end; ++coi)
	{
		PartitionCell *cell = coi->m_cell;
		if (!cell)
			continue;
		unsigned short s = cell->m_shroud[playerIndex].status;
		++total;
		int kind = (s == 0xFFFF) ? 2 : (s == 0);
		switch (kind)
		{
		case 1:
			++foggedCells;
			break;
		case 2:
			++shroudedCells;
			break;
		}
	}

	if (total == 0 || shroudedCells == total)
	{
		m_shroudedness[playerIndex] = OBJECTSHROUD_SHROUDED;
		m_everSeen[playerIndex] = 0;
		if (m_ghost && m_shroudednessPrevious[playerIndex] == OBJECTSHROUD_FOGGED)
			m_ghost->freeSnapShot(playerIndex);
	}
	else if (shroudedCells + foggedCells == total)
	{
		m_shroudedness[playerIndex] = OBJECTSHROUD_FOGGED;
		if (m_object && m_ghost)
		{
			if (m_object->checkVisible(playerIndex))
				m_shroudedness[playerIndex] = OBJECTSHROUD_SHROUDED;
			else if (m_shroudednessPrevious[playerIndex] != OBJECTSHROUD_FOGGED)
				m_ghost->snapShot(playerIndex);
		}
	}
	else if (shroudedCells == 0 && foggedCells == 0)
	{
		m_everSeen[playerIndex] = 1;
		m_shroudedness[playerIndex] = OBJECTSHROUD_CLEAR;
		if (m_ghost && m_shroudednessPrevious[playerIndex] != OBJECTSHROUD_CLEAR)
			m_ghost->freeSnapShot(playerIndex);
	}
	else
	{
		m_everSeen[playerIndex] = 1;
		m_shroudedness[playerIndex] = OBJECTSHROUD_PARTIAL_CLEAR;
		if (m_ghost && m_shroudednessPrevious[playerIndex] != OBJECTSHROUD_PARTIAL_CLEAR)
			m_ghost->freeSnapShot(playerIndex);
	}

	if (total)
		m_shroudednessPrevious[playerIndex] = m_shroudedness[playerIndex];

	return (ObjectShroudStatus)m_shroudedness[playerIndex];
}
