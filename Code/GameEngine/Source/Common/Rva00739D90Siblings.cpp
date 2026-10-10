// cl: /GX
// ?rva00739D90@Rva00739D90@@QAEXPBUBfmePointFC@@MHHH@Z 171B @0x00739D90:
// sibling of rowed ?bfmeApplyCircleWorld@BfmeTaintManager@@ 0x006C0AB0
// (170B). Same ceil/floor world-to-cell shape, but the grid sits at +0x10
// with originX@+4 originY@+8 scale@+0x20 (the Gen_008F7CD0 layout, not
// BfmeTaintManager's cellSizeInv/region), and the paint call targets the
// address-derived Gen_008F7CD0 apply entry at 0x0073CE90. Its signed amount
// is a full integer, established by the complete provider and undo caller.
// Evidence: body
// bytes match the template instruction for instruction except the field
// offsets, the scale member and the final E8 displacement.
extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

__forceinline float bfmeFloatFloorFC(float value)
{
	return (float)floor((double)value);
}

__forceinline float bfmeFloatCeilFC(float value)
{
	return (float)ceil((double)value);
}

__forceinline long bfmeFloatToLongFC(float value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

struct BfmePointFC
{
	float x;
	float y;
};

class Gen_008F7CD0
{
public:
	void rva0073CE90(int x, int y, int radius, int counter, int amount, int mode);
	float m_pad00;
	float m_originX;
	float m_originY;
	char m_pad0C[0x14];
	float m_scale;
};

class Rva00739D90
{
public:
	void rva00739D90(const BfmePointFC *point, float radius, int counter, int amount, int mode);
private:
	char m_pad00[0x10];
	Gen_008F7CD0 *m_grid;
};

void Rva00739D90::rva00739D90(const BfmePointFC *point, float radius, int counter, int amount, int mode)
{
	int cellRadius = bfmeFloatToLongFC(bfmeFloatCeilFC(radius * m_grid->m_scale));
	int y = bfmeFloatToLongFC(bfmeFloatFloorFC((point->y - m_grid->m_originY) * m_grid->m_scale));
	int x = bfmeFloatToLongFC(bfmeFloatFloorFC((point->x - m_grid->m_originX) * m_grid->m_scale));
	m_grid->rva0073CE90(x, y, cellRadius, counter, amount, mode);
}
