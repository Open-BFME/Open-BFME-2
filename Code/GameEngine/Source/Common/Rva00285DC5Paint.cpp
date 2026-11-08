// cl: /DNDEBUG /MD
// ?rva00285DC5@FireLogicSystem@@QAEXHHHHHHH_N@Z @ 0x00285DC5 382B
// Grid row-range paint over fixed column: bounds-checks row/col against +0x78/+0x7C,
// clamps ranges, converts coords via 0.5/10.0 floats, skips cells where
// TheTerrainLogic slot 0x4C returns true, saturating word add plus 12/10/8-bit packed
// field max/max/min updates. Evidence: same +0x70/+0x78/+0x7C layout and 0x14 stride
// as Rva00285D34Cell, TheTerrainLogic 0x009FEC50, callers at 0x002865C5/0x002865EB.
#include "../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

class FireLogicSystem
{
public:
	void rva00285DC5(int startRow, int endRow, int col, int add, int maxBurnRate, int decay, int resistance, bool flag);
private:
	struct Cell
	{
		int m_type;
		unsigned short m_add;
		unsigned short m_check;
		unsigned int m_packed;
		char m_pad[8];
	};
	char m_pad[0x70];
	Cell **m_cells;
	int m_pad74;
	int m_numRows;
	int m_numCols;
};

void FireLogicSystem::rva00285DC5(int startRow, int endRow, int col, int add, int maxBurnRate, int decay, int resistance, bool flag)
{
	if (col < 0)
		return;
	if (col >= m_numCols)
		return;
	if (startRow >= m_numRows)
		return;
	if (endRow < 0)
		return;
	if (startRow < 0)
		startRow = 0;
	if (endRow >= m_numRows)
		endRow = m_numRows - 1;
	if (maxBurnRate > 0xfff)
		maxBurnRate = 0xfff;
	if (decay > 0x3ff)
		decay = 0x3ff;
	if (resistance < 0)
		resistance = 0;
	if (startRow > endRow)
		return;
	float colF = (float)(((double)col + 0.5) * 10.0);
	for (; startRow <= endRow; startRow++) {
		if (TheTerrainLogic->isUnderwater((float)(((double)startRow + 0.5) * 10.0), colF, 0, 0, 0))
			continue;
		Cell *cell = (Cell *)((char *)m_cells[startRow] + col * 20);
		if (flag != false && cell->m_check < 1)
			continue;
		int t = (int)cell->m_add + add;
		if (t < 0)
			cell->m_add = 0;
		else if (t > 0xffff)
			cell->m_add = 0xffff;
		else
			cell->m_add = (unsigned short)t;
		unsigned int packed = cell->m_packed;
		if (((packed >> 18) & 0xfff) < (unsigned int)maxBurnRate)
			cell->m_packed = (packed & ~0x3ffc0000) | ((maxBurnRate << 18) & 0x3ffc0000);
		packed = cell->m_packed;
		if ((packed & 0x3ff) < (unsigned int)decay)
			cell->m_packed = (packed & ~0x3ff) | (decay & 0x3ff);
		packed = cell->m_packed;
		if (((packed >> 10) & 0xff) > (unsigned int)resistance)
			cell->m_packed = (packed & ~0x3fc00) | ((resistance << 10) & 0x3fc00);
		cell->m_type = 0;
	}
}
