// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?rva00739AF0@Rva00739AF0@@QAEXPAUFloatRect0073CE30@@HI@Z 229B @0x00739AF0:
// byte-for-byte sibling of the rowed 0x00739CA0 body except for the final
// rowed-callee displacement, which targets the address-derived updater at
// 0x0073CC60 instead of 0x0073CE30. Same world-to-cell floor/round shape,
// same Gen layout (originX@+4 originY@+8 scale@+0x20) and same caller Gen*
// at +0x10. Evidence: identical 229-byte body except the E8 displacement.
#include <math.h>

static __forceinline float fast_floor(float f)
{
	return (float)floor((double)f);
}

static __forceinline long fast_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

struct FloatRect0073CE30
{
	float x1;
	float y1;
	float x2;
	float y2;
};

// The partition cell grid: origins +4/+8, cell-size reciprocal +0x20 and
// row-major 0xA8-byte cells (bfmeAt); one view for the whole TU.
class BfmeCellFD;
struct FloatRect0073CE30;

class Gen_008F7CD0
{
public:
	BfmeCellFD *bfmeAt(int x, int y) const;
	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int firstColumn, int lastColumn, int scanRow);
	int bfmeCellX(float value) const;
	int bfmeCellY(float value) const;
	int bfmeCellExtent8F74E0(float value) const;
	void rva0073CC60(FloatRect0073CE30 *rect, int extra, unsigned int mask);
	void rva0073CE30(FloatRect0073CE30 *rect, int extra, unsigned int mask);

	char m_pad00[4];				// +0x00
	float m_originX;				// +0x04
	float m_originY;				// +0x08
	char m_pad0C[20];				// +0x0C
	float m_scale;					// +0x20
	int m_bfmeWidth;				// +0x24
	int m_bfmeHeight;				// +0x28
	BfmeCellFD *m_bfmeCells;			// +0x2C
};

class Rva00739AF0
{
public:
	void rva00739AF0(FloatRect0073CE30 *world, int extra, unsigned int mask);
private:
	char m_pad00[16];
	Gen_008F7CD0 *m_gen10;
};

void Rva00739AF0::rva00739AF0(FloatRect0073CE30 *world, int extra, unsigned int mask)
{
	FloatRect0073CE30 cell;
	int ix1 = fast_round(fast_floor((world->x1 - m_gen10->m_originX) * m_gen10->m_scale));
	cell.x1 = (float)ix1;
	int ix2 = fast_round(fast_floor((world->x2 - m_gen10->m_originX) * m_gen10->m_scale));
	cell.x2 = (float)ix2;
	int iy1 = fast_round(fast_floor((world->y1 - m_gen10->m_originY) * m_gen10->m_scale));
	cell.y1 = (float)iy1;
	int iy2 = fast_round(fast_floor((world->y2 - m_gen10->m_originY) * m_gen10->m_scale));
	cell.y2 = (float)iy2;
	m_gen10->rva0073CC60(&cell, extra, mask);
}
