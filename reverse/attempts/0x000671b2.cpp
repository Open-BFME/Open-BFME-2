// ?rva000671B2@BaseHeightMapRenderObjClass@@QAE_NMM@Z
// partial score=0.92 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE2
// ?rva000671B2@BaseHeightMapRenderObjClass@@QAE_NMM@Z @0x000671B2 115B: bit-plane passability check via Gen_0074BA50. Evidence: member +0x37C0 fits BaseHeightMapRenderObjClass 0x386C pad; next loadRoadsAndBridges same class; callee bfmeBitA 0xAE13E; float scale g_00BC5CD0.
#include <math.h>

extern float g_00BC5CD0;

class Gen_0074BA50
{
public:
	bool bfmeBitA(int x, int y) const;
private:
	unsigned char m_opaque00[0x08];
	int m_width;
	int m_height;
	int m_10;
	unsigned char m_pad14[0x20];
	int m_stride;
	unsigned char m_pad38[8];
};

class BaseHeightMapRenderObjClass
{
public:
	bool rva000671B2(float x, float y);
private:
	unsigned char m_pad0000[0x37C0];
	Gen_0074BA50 * volatile m_gen;
	unsigned char m_pad37C4[0x3874 - 0x37C4];
};

// ?rva000671B2@BaseHeightMapRenderObjClass@@QAE_NMM@Z present-unmatched
bool BaseHeightMapRenderObjClass::rva000671B2(float x, float y)
{
	Gen_0074BA50 * volatile *pp = &m_gen;
	Gen_0074BA50 *gen = *pp;
	if (gen == 0)
		return false;
	int base = *(int *)((char *)*pp + 0x10);
	float fx = x;
	float fy = y;
	float fg = g_00BC5CD0;
	int ix = (int)(fx * fg);
	int iy = (int)(fy * fg);
	int dx = base - ix;
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
