// cl: /DNDEBUG /MD
// ?rva00285DC5@FireLogicSystem@@QAEXHHHHHHH_N@Z @ 0x00285DC5 382B
// Grid row-range paint over fixed column: bounds-checks row/col against +0x78/+0x7C,
// clamps ranges, converts coords via 0.5/10.0 floats, skips cells where
// TheTerrainLogic slot 0x4C returns true, saturating word add plus 12/10/8-bit packed
// field max/max/min updates. Evidence: same +0x70/+0x78/+0x7C layout and 0x14 stride
// as Rva00285D34Cell, TheTerrainLogic 0x009FEC50, callers at 0x002865C5/0x002865EB.
class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18();
	virtual bool IsBlocked(float x, float y, int a, int b, int c);
};

extern TerrainLogic *TheTerrainLogic;

class FireLogicSystem
{
public:
	void rva00285DC5(int r0, int r1, int col, int add, int f12, int f10, int f8, bool flag);
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

void FireLogicSystem::rva00285DC5(int r0, int r1, int col, int add, int f12, int f10, int f8, bool flag)
{
	if (col < 0)
		return;
	if (col >= m_numCols)
		return;
	if (r0 >= m_numRows)
		return;
	if (r1 < 0)
		return;
	if (r0 < 0)
		r0 = 0;
	if (r1 >= m_numRows)
		r1 = m_numRows - 1;
	if (f12 > 0xfff)
		f12 = 0xfff;
	if (f10 > 0x3ff)
		f10 = 0x3ff;
	if (f8 < 0)
		f8 = 0;
	if (r0 > r1)
		return;
	float colF = (float)(((double)col + 0.5) * 10.0);
	for (; r0 <= r1; r0++) {
		if (TheTerrainLogic->IsBlocked((float)(((double)r0 + 0.5) * 10.0), colF, 0, 0, 0))
			continue;
		Cell *cell = (Cell *)((char *)m_cells[r0] + col * 20);
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
		if (((packed >> 18) & 0xfff) < (unsigned int)f12)
			cell->m_packed = (packed & ~0x3ffc0000) | ((f12 << 18) & 0x3ffc0000);
		packed = cell->m_packed;
		if ((packed & 0x3ff) < (unsigned int)f10)
			cell->m_packed = (packed & ~0x3ff) | (f10 & 0x3ff);
		packed = cell->m_packed;
		if (((packed >> 10) & 0xff) > (unsigned int)f8)
			cell->m_packed = (packed & ~0x3fc00) | ((f8 << 10) & 0x3fc00);
		cell->m_type = 0;
	}
}
