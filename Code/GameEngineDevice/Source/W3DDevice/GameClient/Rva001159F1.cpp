// cl: /DNDEBUG /MD /EHsc /O1
// Native1159F1-115A5A takes one pointer. Retail saves the old member at
// +0x88 into +0x8C then stores the argument. The subsequent calls and the
// rectangle {0, 0, +0x50 + +0x58, +0x54 + +0x58} are direct target evidence.
// Receiver identity is unknown; fields are an address-derived ABI view.

#include <math.h>
#include <string.h>
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/IRegion2D.h"

class Rva000AD9AB
{
public:
	void rva000AD9FE();
};

typedef int Int;
typedef float Real;
typedef unsigned short UnsignedShort;

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;
};

// 0x00112898 is rowed as W3DTerrainBackground::setFlipRecursive and
// 0x00113DE0 as its rva00113DE0 index builder; the fields are the ones
// calcBlendHeight (0x00115A5B) reads.
class WorldHeightMap;
class W3DTerrainBackground
{
public:
	void setFlipRecursive(int, int, int);
	void doPartialUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, bool doTextures, bool flag);
	void calcBlendHeight(Real param, Int mode, Real *maxDelta);
	void rva00113DE0(UnsignedShort *ib, Vector3 *heights, Int xOffset, Int yOffset, Int width,
		UnsignedShort *ndx, Int &curIndex);

private:
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

class Rva00111F0E
{
public:
	void rva00111F0E();
};

class Rva001159F1
{
	char m_pad00[0x50];
	int m_x;
	int m_y;
	int m_span;
	Rva000AD9AB *m_bitPlane;
	unsigned char m_flags;
	bool m_mode;
	char m_pad62[0x26];
	void *m_current;
	void *m_previous;

public:
	void rva001159F1(void *value);
};

void Rva001159F1::rva001159F1(void *value)
{
	m_previous = m_current;
	m_current = value;
	m_bitPlane->rva000AD9FE();
	reinterpret_cast<W3DTerrainBackground *>(this)->setFlipRecursive(
		0, 0, m_span);
	reinterpret_cast<Rva00111F0E *>(this)->rva00111F0E();

	IRegion2D rectangle;
	rectangle.lo.x = 0;
	rectangle.lo.y = 0;
	rectangle.hi.x = m_x + m_span;
	rectangle.hi.y = m_y + m_span;
	reinterpret_cast<W3DTerrainBackground *>(this)->doPartialUpdate(
		rectangle, 0, false, m_mode);
}


// ---------------------------------------------------------------------------
// W3DTerrainBackground::calcBlendHeight, retail 0x00115A5B (844 B); the WB
// debug twin 0x7CC9D0 names it (W3DTerrainBackground.cpp, assert line 2426).
// Statement shapes follow that twin: the clamped grid coordinates and the
// vertex index are separate locals, the largest delta is a ternary update and
// the edge test reads dx/dy locals. Map/bit-plane/heights helpers are the
// rowed address-named bodies (BoundedShortGrid 0x00062A58, bit plane test
// 0x001126FD, refresh 0x000AD9FE, slot reset 0x00112153).

#define MAP_HEIGHT_SCALE (10.0f / 256.0f)

#include <new>

class BoundedShortGrid
{
public:
	short load(Int x, Int y);
};

class Rva00729300BitPlane
{
public:
	bool test(Int x, Int y) const;
};

class WorldHeightMap
{
public:
	Int getXExtent() { return m_width; }
	Int getYExtent() { return m_height; }
	bool isInMesh(Int gridX, Int gridY) { return ((const Rva00729300BitPlane *)this)->test(gridX, gridY); }
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

void W3DTerrainBackground::calcBlendHeight(Real param, Int mode, Real *maxDelta)
{
	Int xOrigin = m_xOrigin;
	Int yOrigin = m_yOrigin;
	Int xLimit = m_xOrigin + m_width;
	Int yLimit = m_yOrigin + m_width;
	Int mapXMax = m_map->getXExtent() - 1;
	Int mapYMax = m_map->getYExtent() - 1;
	if (xLimit > mapXMax)
		xLimit = mapXMax;
	if (yLimit > mapYMax)
		yLimit = mapYMax;

	Int gridX, y;
	if (param == 0.0f) {
		((Rva0011216CSlotQuartet *)this)->rva00112153();
		Int count = (m_width + 1) * (m_width + 1);
		m_heights = new Vector3[count];
		for (y = yOrigin; y <= yLimit; y++) {
			for (gridX = xOrigin; gridX <= xLimit; gridX++) {
				Int cx = gridX < mapXMax ? gridX : mapXMax;
				Int cy = y < mapYMax ? y : mapYMax;
				Int idx = (gridX - xOrigin) + (m_width + 1) * (y - yOrigin);
				m_heights[idx].X = (UnsignedShort)((BoundedShortGrid *)m_map)->load(cx, cy) * MAP_HEIGHT_SCALE;
				m_heights[idx].Z = m_heights[idx].X;
				m_heights[idx].Y = m_heights[idx].Z;
			}
		}

		if (m_mode == 2) {
			m_savedStep = m_step;
			m_step = m_coarseStep;
		}
		m_map->refreshBitPlane();
		setFlipRecursive(0, 0, m_width);

		Int ndxCount = 0;
		UnsignedShort *ndx = new UnsignedShort[count];
		memset(ndx, 0, count * sizeof(UnsignedShort));
		for (y = yOrigin; y <= yLimit; y += m_step) {
			for (gridX = xOrigin; gridX <= xLimit; gridX += m_step) {
				if (m_map->isInMesh(gridX, y)) {
					ndx[(y - yOrigin) * (m_width + 1) + (gridX - xOrigin)] = ndxCount++;
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
	setFlipRecursive(0, 0, m_width);

	Real largest = 0.0f;
	for (Int j = yOrigin; j <= yLimit; j += m_step) {
		for (Int i = xOrigin; i <= xLimit; i += m_step) {
			if (m_map->isInMesh(i, j)) {
				Int idx = (j - yOrigin) * (m_width + 1) + (i - xOrigin);
				m_heights[idx].Z = (1.0f - m_blend) * m_heights[idx].X + m_heights[idx].Y * m_blend;
				Real delta = fabs(m_heights[idx].Y - m_heights[idx].X);
				largest = largest > delta ? largest : delta;
				Int dx = i - xOrigin;
				Int dy = j - yOrigin;
				if (dx == 0 || dy == 0 || dx == m_width || dy == m_width) {
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
