// ?calcBlendHeight@W3DTerrainBackground@@QAEXMHPAM@Z
// partial score=0.93 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [00115A5B,00115DA7),844B, RET12. W3DTerrainBackground::
// calcBlendHeight (WorldBuilder name and "Bad ndxNdx" assert in
// W3DTerrainBackground.cpp). When the float argument is zero it rebuilds the
// tile's 0x0C-byte height records (+0xD0, X = map height * MAP_HEIGHT_SCALE
// copied to Z and Y) over the clamped tile, swaps in the coarse step for
// mode 2 (+0x88/+0x8C/+0x94), refreshes the map bit plane and the in-mesh
// flags (0x00112898), numbers the in-mesh cells and lets the recursive filler
// 0x00113DE0 write the second height (Y); afterwards it restores the step or
// re-tessellates (0x001159F1 with +0x94). It then blends every in-mesh
// cell's Z from X and Y by +0xCC, pins tile edges to Y (mode 1) or X (mode 2)
// and, for a zero argument, reports the largest |Y - X|. Offsets are target
// evidence; the receivers of the rowed map/tile helpers keep their ledger
// names.

#include <string.h>

typedef int Int;
typedef float Real;
typedef unsigned short UnsignedShort;

#define MAP_HEIGHT_SCALE (10.0f / 256.0f)

extern "C" double __cdecl fabs(double);
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *p);

template <class T> inline T clampMin(T a, T b) { return a < b ? a : b; }

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;
};

class BoundedShortGrid
{
public:
	short rva00062A58(Int x, Int y);
};

class Rva00729300BitPlane
{
public:
	bool test(Int x, Int y) const;
};

class Rva000AD9AB
{
public:
	void rva000AD9FE();
};

class WorldHeightMap
{
public:
	Int getXExtent() { return m_width; }
	Int getYExtent() { return m_height; }
	UnsignedShort getHeight(Int x, Int y) { return ((BoundedShortGrid *)this)->rva00062A58(x, y); }
	bool isInMesh(Int x, Int y) { return ((const Rva00729300BitPlane *)this)->test(x, y); }
	void refreshBitPlane() { ((Rva000AD9AB *)this)->rva000AD9FE(); }

private:
	unsigned char m_pad00[0x08];
	Int m_width;
	Int m_height;
};

class Rva0011216CSlotQuartet
{
public:
	void rva00112153();
};

class Rva00113110Holder
{
public:
	void rva00112898(int, int, void *);
};

class Rva001159F1
{
public:
	void rva001159F1(void *value);
};

class W3DTerrainBackground
{
public:
	void calcBlendHeight(Real param, Int mode, Real *maxDelta);
	void rva00113DE0(UnsignedShort *ib, Vector3 *heights, Int xOffset, Int yOffset, Int width,
		UnsignedShort *ndx, Int &curIndex);

private:
	void setInMeshRecursive(Int xOffset, Int yOffset, Int width)
	{
		((Rva00113110Holder *)this)->rva00112898(xOffset, yOffset, (void *)width);
	}

	unsigned char m_pad00[0x50];
	Int m_xOrigin;
	Int m_yOrigin;
	Int m_width;
	WorldHeightMap *m_map;
	unsigned char m_pad60[0x88 - 0x60];
	Int m_step;
	Int m_savedStep;
	unsigned char m_pad90[0x94 - 0x90];
	Int m_coarseStep;
	unsigned char m_pad98[0xC8 - 0x98];
	Int m_mode;
	Real m_blend;
	Vector3 *m_heights;
};

void W3DTerrainBackground::calcBlendHeight(Real param, Int mode, Real *maxDelta)
{
	Int xOrigin = m_xOrigin;
	Int yOrigin = m_yOrigin;
	Int xLimit = m_xOrigin + m_width;
	Int yLimit = m_yOrigin + m_width;
	Int mapYMax = m_map->getYExtent() - 1;
	Int mapXMax = m_map->getXExtent() - 1;
	if (xLimit > mapXMax)
		xLimit = mapXMax;
	if (yLimit > mapYMax)
		yLimit = mapYMax;

	Int x, y;
	if (param == 0.0f) {
		((Rva0011216CSlotQuartet *)this)->rva00112153();
		Int count = (m_width + 1) * (m_width + 1);
		m_heights = new Vector3[count];
		for (y = yOrigin; y <= yLimit; y++) {
			for (x = xOrigin; x <= xLimit; x++) {
				Int idx = (x - xOrigin) + (m_width + 1) * (y - yOrigin);
				m_heights[idx].X = m_map->getHeight(clampMin(x, mapXMax), clampMin(y, mapYMax)) * MAP_HEIGHT_SCALE;
				m_heights[idx].Z = m_heights[idx].X;
				m_heights[idx].Y = m_heights[idx].Z;
			}
		}

		if (m_mode == 2) {
			m_savedStep = m_step;
			m_step = m_coarseStep;
		}
		m_map->refreshBitPlane();
		setInMeshRecursive(0, 0, m_width);

		Int ndxCount = 0;
		UnsignedShort *ndx = new UnsignedShort[count];
		memset(ndx, 0, count * sizeof(UnsignedShort));
		for (y = yOrigin; y <= yLimit; y += m_step) {
			for (x = xOrigin; x <= xLimit; x += m_step) {
				if (m_map->isInMesh(x, y)) {
					ndx[(y - yOrigin) * (m_width + 1) + (x - xOrigin)] = ndxCount++;
				}
			}
		}
		Int curIndex = 0;
		rva00113DE0(0, m_heights, 0, 0, m_width, ndx, curIndex);
		delete[] ndx;

		if (mode == 2)
			m_step = m_savedStep;
		if (mode == 1)
			((Rva001159F1 *)this)->rva001159F1((void *)m_coarseStep);
	}

	m_map->refreshBitPlane();
	setInMeshRecursive(0, 0, m_width);

	Real largest = 0.0f;
	for (Int j = yOrigin; j <= yLimit; j += m_step) {
		for (Int i = xOrigin; i <= xLimit; i += m_step) {
			if (m_map->isInMesh(i, j)) {
				Int idx = (j - yOrigin) * (m_width + 1) + (i - xOrigin);
				m_heights[idx].Z = (1.0f - m_blend) * m_heights[idx].X + m_heights[idx].Y * m_blend;
				Real delta = fabs(m_heights[idx].Y - m_heights[idx].X);
				if (!(largest > delta))
					largest = delta;
				if (i - xOrigin == 0 || j - yOrigin == 0 || i - xOrigin == m_width || j - yOrigin == m_width) {
					if (mode == 1)
						m_heights[idx].Z = m_heights[idx].Y;
					else if (mode == 2)
						m_heights[idx].Z = m_heights[idx].X;
				}
			}
		}
	}
	if (param == 0.0f)
		*maxDelta = largest;
}
