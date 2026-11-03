// BFME1 BfmeConv1574.cpp adapted to the target constants below.
// Target identity: Ghidra boundary 0x73BD70/131 bytes and the direct calls
// to the target-matched coordinate helpers at 0x739840 and 0x739870.
// Target bytes establish three accepted index values, a 20-bit mask, and
// four 16-bit words of stride between corresponding bits. Target helper
// 0x73A260 supplies the cell pointer; its observed row-major stride is 0xA8.
// Gen_008F7CD0, BfmeCellFD and member names are provisional donor labels;
// the complete target cell layout is not asserted here.

typedef float Real;

struct BfmePointFD
{
	Real x;
	Real y;
};

struct BfmeCellOut
{
	Real x;
	Real y;
	Real z;
};

class BfmeCellFD;

class Gen_008F7CD0
{
public:
	int bfmeCellSum(const BfmePointFD *point, int valueIndex,
		unsigned int selectionMask) const;
	BfmeCellFD *bfmeAt(int x, int y) const;
	int bfmeCellX(Real value) const;
	int bfmeCellY(Real value) const;
	void rva0073BC60(int selectionMask, int valueIndex, BfmeCellOut *bestPosition) const;

private:
	char m_bfmeHead[4];					// +0x00
	Real m_bfmeOriginX;					// +0x04
	Real m_bfmeOriginY;					// +0x08
	char m_bfmeMid[16];					// +0x0C
	Real m_bfmeStep;					// +0x1C
	Real m_bfmeScale;					// +0x20
	int m_bfmeWidth;					// +0x24
	int m_bfmeHeight;					// +0x28
	BfmeCellFD *m_bfmeCells;				// +0x2C
};

// ?bfmeCellSum@Gen_008F7CD0@@QBEHPBUBfmePointFD@@HI@Z
int Gen_008F7CD0::bfmeCellSum(const BfmePointFD *point, int valueIndex,
	unsigned int selectionMask) const
{
	if (selectionMask == 0)
		return 0;

	if (valueIndex < 0 || valueIndex >= 3)
		return 0;

	selectionMask &= 0xfffff;

	BfmeCellFD *cell = bfmeAt(bfmeCellX(point->x), bfmeCellY(point->y));

	if (cell == 0)
		return 0;

	int valueSum = 0;
	if (selectionMask != 0)
	{
		unsigned short *selectedValue = (unsigned short *)((char *)cell
			+ valueIndex * 2 + 6);

		do
		{
			if ((selectionMask & 1) != 0)
				valueSum += *selectedValue;

			selectionMask >>= 1;
			selectedValue += 4;
		}
		while (selectionMask != 0);
	}

	return valueSum;
}

// Retail 0x0073BC60, 262 bytes: the cell with the largest index-masked
// bit sum, reported as step-scaled column/row with a zero third lane.
// Same 20-bit mask, three indices and 0xA8 row stride as bfmeCellSum; the
// +0x1C step scales the winning column and row. The sums and the running
// best compare unsigned (jbe), so an empty mask never replaces the first
// cell and ties keep the earlier cell.
// Native entry: thunk 0x00739810 forwards through this+0x10, like its
// neighbour 0x00739800. The result z is an integer zero store, as in
// GetNearestGroupWithValue (the SSE region default would zero it via xorps).
// ?rva0073BC60@Gen_008F7CD0@@QBEXHHPAUBfmeCellOut@@@Z
void Gen_008F7CD0::rva0073BC60(int selectionMask, int valueIndex, BfmeCellOut *bestPosition) const
{
	if (selectionMask == 0)
		return;
	if (valueIndex < 0 || valueIndex >= 3)
		return;
	selectionMask &= 0xFFFFF;
	const char *bestCell = (const char *)m_bfmeCells;
	const char *cellsEnd = (const char *)m_bfmeCells + m_bfmeHeight * m_bfmeWidth * 0xA8;
	unsigned int bestValueSum = 0;
	for (const char *cell = (const char *)m_bfmeCells; cell != cellsEnd; cell += 0xA8)
	{
		unsigned int cellValueSum = 0;
		unsigned int remainingMask = (unsigned int)selectionMask;
		if (remainingMask != 0)
		{
			const unsigned short *selectedValue = (const unsigned short *)(cell + valueIndex * 2 + 6);
			do
			{
				if ((remainingMask & 1) != 0)
					cellValueSum += *selectedValue;
				remainingMask >>= 1;
				selectedValue += 4;
			} while (remainingMask != 0);
		}
		if (cellValueSum > bestValueSum)
		{
			bestCell = cell;
			bestValueSum = cellValueSum;
		}
	}
	unsigned int cellIndex = (unsigned int)((bestCell - (const char *)m_bfmeCells) / 0xA8);
	bestPosition->x = (Real)(cellIndex % (unsigned int)m_bfmeWidth) * m_bfmeStep;
	bestPosition->y = (Real)(cellIndex / (unsigned int)m_bfmeWidth) * m_bfmeStep;
	*(int *)&bestPosition->z = 0;
}
