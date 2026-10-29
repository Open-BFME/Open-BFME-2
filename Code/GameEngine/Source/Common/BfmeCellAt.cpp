// BFME1 Bfme5SeventySeven.cpp row-major lookup adapted to target stride.
// Donor labels are provisional; target 0x73BD70 directly calls this lookup.
// The cell record is incomplete here: retail evidence establishes its 0xA8 stride,
// but this function only returns its address.
// cl: /O2 /DNDEBUG /MD /EHsc
class BfmeCellFD;

class Gen_008F7CD0
{
public:
	BfmeCellFD *bfmeAt(int x, int y) const;
	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int firstColumn, int lastColumn, int scanRow);

private:
	char m_bfmeHead[0x24];
	int m_bfmeWidth;
	int m_bfmeHeight;
	BfmeCellFD *m_bfmeCells;
};

BfmeCellFD *Gen_008F7CD0::bfmeAt(int x, int y) const
{
	if (x < 0 || x >= m_bfmeWidth || y < 0 || y >= m_bfmeHeight)
		return 0;

	unsigned char *base = reinterpret_cast<unsigned char *>(m_bfmeCells);
	return reinterpret_cast<BfmeCellFD *>(base + (y * m_bfmeWidth + x) * 0xA8);
}

// ?rva0073A2A0@Gen_008F7CD0@@QAEXPAPAVBfmeCellFD@@0HHH@Z @0x0073A2A0 135B: row-range sibling of bfmeAt; same width+0x24 height+0x28 cells+0x2C and 0xA8 stride; callers 0x73A650 0x73AAE0 0x73BAA0 0x73BB40 0x73BBE0 pass grid as this; donor BfmeGridRasterCircle.cpp bfmeGetCellRange plus x2<x1 clamp and *last reload.
void Gen_008F7CD0::rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int firstColumn, int lastColumn, int scanRow)
{
	if (lastColumn < 0 || firstColumn >= m_bfmeWidth || scanRow < 0 || scanRow >= m_bfmeHeight)
	{
		*last = 0;
		*first = 0;
		return;
	}

	unsigned char *base = reinterpret_cast<unsigned char *>(m_bfmeCells);
	unsigned char *row = base + (scanRow * m_bfmeWidth) * 0xA8;
	*last = reinterpret_cast<BfmeCellFD *>(row);
	*first = reinterpret_cast<BfmeCellFD *>(row);
	if (lastColumn < firstColumn)
		lastColumn = firstColumn;
	if (firstColumn > 0)
		*first = reinterpret_cast<BfmeCellFD *>(row + firstColumn * 0xA8);
	*last = reinterpret_cast<BfmeCellFD *>(reinterpret_cast<unsigned char *>(*last) + (lastColumn < m_bfmeWidth ? lastColumn + 1 : m_bfmeWidth) * 0xA8);
}

// The related native grid callback uses origins4/8 and cell size1C.
// Its owner remains address-derived; it shares this grid-family unit
// with the verified x87 coordinate/lookup operations.
// ?rva0073BEA0@Rva0073BEA0@@UAEXHH@Z @0x0073BEA0 106B RET8.
// Address-derived name; layout is a view of the witnessed offsets. Native:
// converts integer cell coordinates (a, b) to the cell centre in the
// grid at this+4 (cell size at +0x1C, origins at +8 for the first and +4 for
// the second coordinate, centre = c * size + origin + size * 0.5, truncated),
// swaps them into a float pair (second, first) and reports it through slot 0
// of the sink at this+0xC. 0x0073BE00 is the same body with a guarded frame.
struct Rva0073BEA0Grid
{
	char m_pad0[4];
	float m_4;
	float m_8;
	char m_padC[0x1C - 0xC];
	float m_cellSize;
};

struct Rva0073BEA0Point
{
	float x;
	float y;
};

struct Rva0073BEA0Grid2 : Rva0073BEA0Grid
{
	int centreA(int cellRow) const { return (int)((float)cellRow * m_cellSize + m_8 + m_cellSize * 0.5); }
	int centreB(int cellColumn) const { return (int)((float)cellColumn * m_cellSize + m_4 + m_cellSize * 0.5); }
};

class Rva0073BEA0Sink
{
public:
	virtual void slot0(const Rva0073BEA0Point *point);
};

class Rva0073BEA0
{
public:
	virtual void rva0073BEA0(int gridColumn, int gridRow);
private:
	Rva0073BEA0Grid2 *m_grid;
	char m_pad8[4];
	Rva0073BEA0Sink *m_sink;
};

void Rva0073BEA0::rva0073BEA0(int gridColumn, int gridRow)
{
	int x = m_grid->centreA(gridRow);
	int y = m_grid->centreB(gridColumn);
	Rva0073BEA0Point worldPosition;
	worldPosition.x = (float)y;
	worldPosition.y = (float)x;
	m_sink->slot0(&worldPosition);
}

// Native 0x73BE00 has one unwind state: cleanup 0x7AB130 calls the
// shared empty RET at 0x0B3FD0 on the point local; no try blocks are present.
// Both coordinates are initialized by the point constructor before its
// lifetime begins. The destructor barrier emits RET while preserving that
// cleanup scope. CF13A0 contains this owner's single virtual slot.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva0073BE00Point
{
	float x;
	float y;
	Rva0073BE00Point(float pointX, float pointY) : x(pointX), y(pointY) {}
	~Rva0073BE00Point();
};

// ?Rva0073BE00Point::~Rva0073BE00Point present-unmatched
Rva0073BE00Point::~Rva0073BE00Point()
{
	_ReadWriteBarrier();
}

class Rva0073BE00
{
public:
	virtual void rva0073BE00(int columnIndex, int rowIndex);
private:
	Rva0073BEA0Grid2 *m_grid;
	void *m_unknown8;
	Rva0073BEA0Sink *m_sink;
};

void Rva0073BE00::rva0073BE00(int columnIndex, int rowIndex)
{
	int centerY = m_grid->centreA(rowIndex);
	int centerX = m_grid->centreB(columnIndex);
	Rva0073BE00Point p((float)centerX, (float)centerY);
	m_sink->slot0(reinterpret_cast<const Rva0073BEA0Point *>(&p));
}
