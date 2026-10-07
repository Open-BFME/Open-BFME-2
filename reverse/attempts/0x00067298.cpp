// ?rva00067298@Rva00067298@@QAE_NMM@Z
// partial score=0.92 date=2026-10-05
// ?rva00067298@Rva00067298@@QAE_NMM@Z
// partial score=0.92 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva00067298@Rva00067298@@QAE_NMM@Z, retail 0x00067298, 115 bytes.
// Leaf: clamped bit test via rowed Gen_0074BB30::bfmeBitA 0x000AE1DC.
// Scale from g_00BC5CD0, origin base at +0x10, dims at +8/+0xC, table at +0x37C0.
// Evidence: caller at 0x00062E08, rowed callee, BaseHeightMap neighbour 0x00067800.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern float g_00BC5CD0;

class Gen_0074BB30
{
public:
	bool bfmeBitA(int x, int y) const;
	unsigned char m_opaque00[0x08];
	int m_width;
	int m_height;
	int m_base10;
};

class Rva00067298
{
public:
	bool rva00067298(float a, float b);
private:
	unsigned char m_pad[0x37C0];
	Gen_0074BB30 * volatile m_gen;
};

// ?rva00067298@Rva00067298@@QAE_NMM@Z present-unmatched
bool Rva00067298::rva00067298(float a, float b)
{
	Gen_0074BB30 * volatile *pp = &m_gen;
	Gen_0074BB30 *gen = *pp;
	if (gen == 0)
		return false;
	int base = *(int *)((char *)*pp + 0x10);
	float fg = g_00BC5CD0;
	float sa = a;
	float sb = b;
	int ix = (int)(sa * fg);
	int dx = base - ix;
	_ReadWriteBarrier();
	int iy = (int)(sb * fg);
	int dy = base - iy;
	if (dx < 0)
		dx = 0;
	if (dy < 0)
		dy = 0;
	int w = *(int *)((char *)gen + 8);
	if (dx >= w - 1)
		dx = w - 2;
	int h = *(int *)((char *)gen + 12);
	if (dy >= h - 1)
		dy = h - 2;
	return gen->bfmeBitA(dx, dy);
}
