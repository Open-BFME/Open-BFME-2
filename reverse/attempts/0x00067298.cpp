// ?rva00067298@Rva00067298@@QAE_NMM@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva00067298@Rva00067298@@QAE_NMM@Z, retail 0x00067298, 115 bytes.
// Leaf: clamped bit test via rowed Gen_0074BB30::bfmeBitA 0x000AE1DC.
// Scale from g_00BC5CD0, origin base at +0x10, dims at +8/+0xC, table at +0x37C0.
// Evidence: caller at 0x00062E08, rowed callee, BaseHeightMap neighbour 0x00067800.

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
	Gen_0074BB30 *m_gen;
};

// ?rva00067298@Rva00067298@@QAE_NMM@Z present-unmatched
bool Rva00067298::rva00067298(float a, float b)
{
	if (!m_gen)
		return false;
	int base = m_gen->m_base10;
	int dx = base - (int)(a * g_00BC5CD0);
	int dy = base - (int)(b * g_00BC5CD0);
	if (dx < 0)
		dx = 0;
	if (dy < 0)
		dy = 0;
	int w = m_gen->m_width;
	if (dx >= w - 1)
		dx = w - 2;
	int h = m_gen->m_height;
	if (dy >= h - 1)
		dy = h - 2;
	return m_gen->bfmeBitA(dx, dy);
}
