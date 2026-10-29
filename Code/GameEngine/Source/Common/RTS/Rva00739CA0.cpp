// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?rva00739CA0@Rva00739CA0@@QAEXPAUFloatRect0073CE30@@HI@Z 229B @0x00739CA0: world-to-cell rect via floor then rowed Gen wrapper 0x0073CE30. Computes cell floats as (float)(int)floor((double)((world-origin)*scale)) with Gen originX@+4 originY@+8 scale@+0x20 then calls gen->rva0073CE30 with extra mask passthrough. Layout caller Gen* at +0x10. Evidence: 4x floor plus fistp/fild plus rowed 0x0073CE30 plus callers at 0x00357926 0x003C01A0.
#include <math.h>

static __forceinline float fast_floor(float f)
{
	return (float)floor((double)f);
}

static __forceinline long fast_round(float number)
{
	long i;
	__asm {
		fld [number]
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

class Gen_008F7CD0
{
public:
	void rva0073A2A0(void *first, void *last, int x1, int x2, int y);
	void rva0073CE30(FloatRect0073CE30 *rect, int extra, unsigned int mask);
	float m_pad00;
	float m_originX;
	float m_originY;
	char m_pad0C[20];
	float m_scale;
};

class Rva00739CA0
{
public:
	void rva00739CA0(FloatRect0073CE30 *world, int extra, unsigned int mask);
private:
	char m_pad00[16];
	Gen_008F7CD0 *m_gen10;
};

void Rva00739CA0::rva00739CA0(FloatRect0073CE30 *world, int extra, unsigned int mask)
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
	m_gen10->rva0073CE30(&cell, extra, mask);
}
