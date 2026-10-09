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

class Rva002E713FOwner
{
public:
	void rva0052F294();
};

class PathfindCell
{
public:
	enum CellType
	{
		CELL_CLEAR = 0,
		CELL_WATER = 1,
		CELL_CLIFF = 2,
		CELL_DEEP_WATER = 7
	};

	CellType getType() const { return (CellType)m_type; }
	bool getPinched() const { return m_pinched; }
	void setPinched(bool pinch) { m_pinched = pinch; }
	bool getBit22() const { return m_bit22; }
	bool getBit23() const { return m_bit23; }
	bool SetType_Dirty(int type);
	void setBit22(bool on) { reinterpret_cast<Rva0052E02F *>(this)->rva0052E02F(on); }
	void setBit23(bool on) { reinterpret_cast<Rva0052E0CE *>(this)->rva0052E0CE(on); }

private:
	char m_head[0x0C];
	unsigned int m_type : 4;
	unsigned int m_low : 12;
	unsigned int m_pinched : 1;
	unsigned int m_mid : 5;
	unsigned int m_bit22 : 1;
	unsigned int m_bit23 : 1;
	unsigned int m_high : 8;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class Pathfinder
{
public:
	static void classifyMapCell(Int cellX, Int cellY, PathfindCell *cell);
	void Rva0052F2EC();

private:
	char m_head[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
};

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
			if (m_map[i][j].getType() == PathfindCell::CELL_CLIFF)
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
							m_map[k][l].setPinched(true);
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
				m_map[i][j].SetType_Dirty(PathfindCell::CELL_CLIFF);
			}
		}
	}

	reinterpret_cast<Rva002E713FOwner *>(this)->rva0052F294();

	for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
	{
		for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
		{
			PathfindCell *cell = &m_map[i][j];
			if (cell->getType() == PathfindCell::CELL_DEEP_WATER)
			{
				if ((i > m_extent.lo.x && m_map[i - 1][j].getType() != PathfindCell::CELL_DEEP_WATER)
					|| (i < m_extent.hi.x && m_map[i + 1][j].getType() != PathfindCell::CELL_DEEP_WATER)
					|| (j > m_extent.lo.y && m_map[i][j - 1].getType() != PathfindCell::CELL_DEEP_WATER)
					|| (j < m_extent.hi.y && m_map[i][j + 1].getType() != PathfindCell::CELL_DEEP_WATER))
				{
					cell->setBit23(true);
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
				if (m_map[i][j].getBit23())
				{
					if (i > m_extent.lo.x && (m_map[i - 1][j].getType() == PathfindCell::CELL_DEEP_WATER || m_map[i - 1][j].getType() == PathfindCell::CELL_WATER))
						m_map[i - 1][j].setBit22(true);
					if (i < m_extent.hi.x && (m_map[i + 1][j].getType() == PathfindCell::CELL_DEEP_WATER || m_map[i + 1][j].getType() == PathfindCell::CELL_WATER))
						m_map[i + 1][j].setBit22(true);
					if (j > m_extent.lo.y && (m_map[i][j - 1].getType() == PathfindCell::CELL_DEEP_WATER || m_map[i][j - 1].getType() == PathfindCell::CELL_WATER))
						m_map[i][j - 1].setBit22(true);
					if (j < m_extent.hi.y && (m_map[i][j + 1].getType() == PathfindCell::CELL_DEEP_WATER || m_map[i][j + 1].getType() == PathfindCell::CELL_WATER))
						m_map[i][j + 1].setBit22(true);
				}
			}
		}

		for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
		{
			for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
			{
				Int type = m_map[i][j].getType();
				if (m_map[i][j].getBit22()
					&& (type == PathfindCell::CELL_DEEP_WATER || type == PathfindCell::CELL_WATER))
				{
					m_map[i][j].setBit22(false);
					m_map[i][j].setBit23(true);
				}
			}
		}
	}
}
