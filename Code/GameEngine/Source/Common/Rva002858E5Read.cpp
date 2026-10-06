// cl: /DNDEBUG /MD
// ?rva002858E5@Rva002858E5@@QAE_NPAMPAH1111@Z @ 0x002858E5 195B
// Grid cell-field read for a world pos: floor((x+g_Va007C26F0)*INV) row/col via IAT
// floor, bounds-check vs +0x78/+0x7C, imul 0x14 cell lookup, outs are word +4/+6 and
// packed +8 fields 0x3ff/0xff/0xfff. Evidence: same +0x70/+0x78/+0x7c and 0x14 stride
// as Rva00285D34Cell/Rva00285DC5Paint, g_Va007C26F0 0x007C26F0, INV 0x007C2424,
// caller at 0x00048D15.
extern "C" __declspec(dllimport) double __cdecl floor(double);

__forceinline long FloatToLong(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class Rva002858E5
{
public:
	bool rva002858E5(float *p, int *o1, int *o2, int *o3, int *o4, int *o5);
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

bool Rva002858E5::rva002858E5(float *p, int *o1, int *o2, int *o3, int *o4, int *o5)
{
	float fx = (float)floor((p[0] + 0.5f) * 0.1f);
	int row = FloatToLong(fx);
	float fy = (float)floor((p[1] + 0.5f) * 0.1f);
	int col = FloatToLong(fy);
	if (row < 0 || row >= m_numRows || col < 0 || col >= m_numCols)
		return false;
	Cell *cell = (Cell *)((char *)m_cells[row] + col * 20);
	*o1 = cell->m_add;
	*o2 = cell->m_check;
	*o3 = cell->m_packed & 0x3ff;
	*o4 = (cell->m_packed >> 10) & 0xff;
	*o5 = (cell->m_packed >> 18) & 0xfff;
	return true;
}
