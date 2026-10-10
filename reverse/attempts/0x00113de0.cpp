// ?rva00113DE0@W3DTerrainBackground@@QAEXPAGPAVVector3@@HHH0AAH@Z
// partial score=0.9994746236 date=2026-10-10
// ?rva00113DE0@W3DTerrainBackground@@QAEXPAGPAVVector3@@HHH0AAH@Z
// partial score=0.9994746236 date=2026-10-10
// ?rva00113DE0@W3DTerrainBackground@@QAEXPAGPAVVector3@@HHH0AAH@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva00113DE0@W3DTerrainBackground@@QAEXPAGPAVVector3@@HHH0AAH@Z
// Native [00113DE0,001149EB) 3083B RET28. BFME 2 recursive tile index
// filler (ZH fillVBRecursive analogue).
// NEAR DRAFT (helper agent): replacement for
// Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainBackgroundRva00113C07.cpp
// (that unit's 0x00113C07 body is carried verbatim and stays an exact match).
// The target needs rva00113C07 defined earlier in the same TU: only then does
// MSVC 7.1 know the four done-flag pointers do not escape and turn the last
// recursive call into the retail loop (jmp back to +0x16). Separate-TU builds
// keep four calls and miss by ~900 bytes. With C07 visible this body is
// 3083B with exactly 2 differing instructions: at 0x001144FE retail loads
// prevLeft.x (mov ecx,[ebp+0x14]) before m_xOrigin (mov eax,[esi+0x50]); ours
// swaps the pair. Retail treats prevLeft as a memory variable (scalars or an
// address-taken struct reproduce the order but change the frame).
// The x/y limit test uses minY for the second compare because retail CSEs
// m_yOrigin+yOffset (the WB twin writes m_yOrigin+yOffset there).

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short UnsignedShort;

#define MAP_XY_FACTOR 10.0f
#define MAP_HEIGHT_SCALE (10.0f / 256.0f)

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;
};

struct ICoord2D
{
	Int x;
	Int y;
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

class Rva0006AB49BitPlane
{
public:
	bool test(Int x, Int y) const;
};

class Rva000ABD19
{
public:
	bool rva000AF841(Int x, Int y);
};

class Rva007497A0
{
public:
	void setBit(Int x, Int y, bool value);
};

class WorldHeightMap
{
public:
	Int getXExtent() { return m_width; }
	Int getYExtent() { return m_height; }
	Int getBorderSize() { return m_borderSize; }
	UnsignedShort getHeight(Int x, Int y) { return ((BoundedShortGrid *)this)->rva00062A58(x, y); }
	bool isInMesh(Int x, Int y) { return ((const Rva00729300BitPlane *)this)->test(x, y); }
	bool isCellPresent(Int x, Int y) { return ((const Rva0006AB49BitPlane *)this)->test(x, y); }
	bool getFlipState(Int x, Int y) { return ((Rva000ABD19 *)this)->rva000AF841(x, y); }
	void setFlipState(Int x, Int y, bool value) { ((Rva007497A0 *)this)->setBit(x, y, value); }

private:
	Int m_pad00[2];
	Int m_width;
	Int m_height;
	Int m_borderSize;
};

class Rva00112ED3TerrainPrefix
{
public:
	void checkUnsetEdges(int xOffset, int yOffset, int width,
		bool *top, bool *right, bool *bottom, bool *left);
};

class Rva001127F2TerrainPrefix
{
public:
	bool advanceScan(ICoord2D &right, Int xOffset, Int yOffset, Int width, Int height);
	bool advanceYThenX(ICoord2D &point, Int xOffset, Int yOffset, Int width, Int height);
};

class W3DTerrainBackground
{
public:
	void rva00113DE0(UnsignedShort *ib, Vector3 *heights, Int xOffset, Int yOffset, Int width,
		UnsignedShort *ndx, Int &curIndex);
	void rva00113399(unsigned short *ib, void *aux, int x, int y, int w, int h,
		unsigned short *ndx, int &curIndex);
	void rva00113C07(UnsignedShort *ib, void *aux, Int x, Int y, Int width,
		bool *done0, bool *done1, bool *done2, bool *done3,
		UnsignedShort *ndx, Int &curIndex);
	void getTriangleIntersection(Vector3 *heights, Int x, Int y, Int width, Int height,
		const Vector3 &v0, const Vector3 &v1, const Vector3 &v2);

	bool advanceLeft(ICoord2D &left, Int xOffset, Int yOffset, Int width)
	{
		return ((Rva001127F2TerrainPrefix *)this)->advanceYThenX(left, xOffset, yOffset, width, width);
	}
	bool advanceRight(ICoord2D &right, Int xOffset, Int yOffset, Int width)
	{
		return ((Rva001127F2TerrainPrefix *)this)->advanceScan(right, xOffset, yOffset, width, width);
	}

private:
	unsigned char m_pad00[0x50];
	Int m_xOrigin;
	Int m_yOrigin;
	Int m_width;
	WorldHeightMap *m_map;
	unsigned char m_pad60[0x88 - 0x60];
	Int m_leafWidth;
};

void W3DTerrainBackground::rva00113C07(unsigned short *ib, void *aux, int x, int y, int width,
	bool *done0, bool *done1, bool *done2, bool *done3,
	unsigned short *ndx, int &curIndex)
{
	*done3 = false;
	*done2 = false;
	*done1 = false;
	*done0 = false;

	bool top, right, bottom, left;
	((Rva00112ED3TerrainPrefix *)this)->checkUnsetEdges(x, y, width, &top, &right, &bottom, &left);
	int half = width / 2;

	if (right) {
		if (top) {
			rva00113399(ib, aux, x, y, half, width, ndx, curIndex);
			rva00113399(ib, aux, x, y + half, width, half, ndx, curIndex);
			*done3 = true;
		} else if (bottom) {
			rva00113399(ib, aux, x, y + half, width, half, ndx, curIndex);
			rva00113399(ib, aux, x + half, y, half, width, ndx, curIndex);
			*done2 = true;
		} else {
			rva00113399(ib, aux, x, y + half, width, half, ndx, curIndex);
			*done3 = true;
			*done2 = true;
		}
	} else if (left) {
		if (top) {
			rva00113399(ib, aux, x, y, half, width, ndx, curIndex);
			rva00113399(ib, aux, x, y, width, half, ndx, curIndex);
			*done1 = true;
		} else {
			rva00113399(ib, aux, x, y, width, half, ndx, curIndex);
			if (bottom) {
				rva00113399(ib, aux, x + half, y, half, width, ndx, curIndex);
			} else {
				*done1 = true;
			}
			*done0 = true;
		}
	} else if (top) {
		*done3 = true;
		*done1 = true;
		rva00113399(ib, aux, x, y, half, width, ndx, curIndex);
		return;
	} else if (bottom) {
		*done2 = true;
		*done0 = true;
		rva00113399(ib, aux, x + half, y, half, width, ndx, curIndex);
		return;
	} else {
		*done3 = true;
		*done2 = true;
		*done1 = true;
		*done0 = true;
	}
}

void W3DTerrainBackground::rva00113DE0(UnsignedShort *ib, Vector3 *heights, Int xOffset, Int yOffset,
	Int width, UnsignedShort *ndx, Int &curIndex)
{
	Int limitX = m_map->getXExtent() - 1;
	Int limitY = m_map->getYExtent() - 1;
	Bool match = true;
	Int minX = m_xOrigin + xOffset;
	Int minY = m_yOrigin + yOffset;
	Int maxX = xOffset + width;
	if (maxX + m_xOrigin > limitX)
		maxX = limitX - m_xOrigin;
	Int maxY = yOffset + width;
	if (maxY + m_yOrigin > limitY)
		maxY = limitY - m_yOrigin;
	Int bottomLeftNdx = ndx[(m_width + 1) * yOffset + xOffset];
	Int topRightNdx = ndx[(m_width + 1) * maxY + maxX];
	if (width > 1) {
		match = !((const Rva00729300BitPlane *)m_map)->test(xOffset + m_xOrigin + width / 2, yOffset + m_yOrigin + width / 2);
	}
	if (match) {
		if (m_xOrigin + xOffset >= limitX || minY >= limitY)
			return;
	}
	if (width == m_leafWidth) {
		match = true;
		if (!m_map->isCellPresent(minX, minY))
			return;
		Bool flip = m_map->getFlipState(minX, minY);
		m_map->setFlipState(minX, minY, flip);
		if (!flip) {
			Int bottomRightNdx = ndx[(m_width + 1) * yOffset + maxX];
			Int topLeftNdx = ndx[(m_width + 1) * maxY + xOffset];
			if (ib)
				ib[curIndex] = bottomLeftNdx;
			curIndex++;
			if (ib)
				ib[curIndex] = topRightNdx;
			curIndex++;
			if (ib)
				ib[curIndex] = topLeftNdx;
			curIndex++;
			if (ib)
				ib[curIndex] = bottomLeftNdx;
			curIndex++;
			if (ib)
				ib[curIndex] = bottomRightNdx;
			curIndex++;
			if (ib)
				ib[curIndex] = topRightNdx;
			curIndex++;
			if (heights) {
				Vector3 v1, v2, v3;
				v1.X = minX * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v1.Y = minY * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v1.Z = m_map->getHeight(minX, minY) * MAP_HEIGHT_SCALE;
				v2.X = (minX + width) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v2.Y = (minY + width) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v2.Z = m_map->getHeight(minX + width, minY + width) * MAP_HEIGHT_SCALE;
				v3.X = minX * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v3.Y = (minY + width) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v3.Z = m_map->getHeight(minX, minY + width) * MAP_HEIGHT_SCALE;
				getTriangleIntersection(heights, xOffset, yOffset, width, width, v1, v2, v3);
				v2.X = (minX + width) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v2.Y = minY * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v2.Z = m_map->getHeight(minX + width, minY) * MAP_HEIGHT_SCALE;
				v3.X = (minX + width) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v3.Y = (minY + width) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v3.Z = m_map->getHeight(minX + width, minY + width) * MAP_HEIGHT_SCALE;
				getTriangleIntersection(heights, xOffset, yOffset, width, width, v1, v2, v3);
			}
			return;
		}
	}
	if (match) {
		if (!m_map->isCellPresent(minX, minY))
			return;
		ICoord2D left;
		left.x = xOffset;
		left.y = yOffset;
		ICoord2D right;
		right.x = xOffset;
		right.y = yOffset;
		advanceLeft(left, xOffset, yOffset, width);
		advanceRight(right, xOffset, yOffset, width);

		if (ib)
			ib[curIndex] = bottomLeftNdx;
		curIndex++;
		UnsignedShort prevNdxRight = ndx[(m_width + 1) * right.y + right.x];
		if (ib)
			ib[curIndex] = prevNdxRight;
		curIndex++;
		UnsignedShort prevNdxLeft = ndx[(m_width + 1) * left.y + left.x];
		if (ib)
			ib[curIndex] = prevNdxLeft;
		curIndex++;
		if (heights) {
			Vector3 v1, v2, v3;
			v1.X = minX * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v1.Y = minY * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v1.Z = m_map->getHeight(minX, minY) * MAP_HEIGHT_SCALE;
			v2.X = (m_xOrigin + right.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v2.Y = (m_yOrigin + right.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v2.Z = m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * MAP_HEIGHT_SCALE;
			v3.X = (m_xOrigin + left.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v3.Y = (m_yOrigin + left.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v3.Z = m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * MAP_HEIGHT_SCALE;
			getTriangleIntersection(heights, xOffset, yOffset, width, width, v1, v2, v3);
		}
		Bool didLeft = true;
		Bool didRight = true;
		while (didLeft || didRight) {
			ICoord2D prevLeft = left;
			didLeft = advanceLeft(left, xOffset, yOffset, width);
			if (didLeft) {
				if (ib)
					ib[curIndex] = prevNdxLeft;
				curIndex++;
				if (ib)
					ib[curIndex] = prevNdxRight;
				curIndex++;
				prevNdxLeft = ndx[(m_width + 1) * left.y + left.x];
				if (ib)
					ib[curIndex] = prevNdxLeft;
				curIndex++;
				if (heights) {
					Vector3 v1, v2, v3;
					v1.X = (m_xOrigin + prevLeft.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
					v1.Y = (m_yOrigin + prevLeft.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
					v1.Z = m_map->getHeight(m_xOrigin + prevLeft.x, m_yOrigin + prevLeft.y) * MAP_HEIGHT_SCALE;
					v2.X = (m_xOrigin + right.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
					v2.Y = (m_yOrigin + right.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
					v2.Z = m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * MAP_HEIGHT_SCALE;
					v3.X = (m_xOrigin + left.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
					v3.Y = (m_yOrigin + left.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
					v3.Z = m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * MAP_HEIGHT_SCALE;
					getTriangleIntersection(heights, xOffset, yOffset, width, width, v1, v2, v3);
				}
			}
			ICoord2D prevRight = right;
			didRight = advanceRight(right, xOffset, yOffset, width);
			if (didRight) {
				if (ib)
					ib[curIndex] = prevNdxLeft;
				curIndex++;
				if (ib)
					ib[curIndex] = prevNdxRight;
				curIndex++;
				prevNdxRight = ndx[(m_width + 1) * right.y + right.x];
				if (ib)
					ib[curIndex] = prevNdxRight;
				curIndex++;
				if (heights) {
					Vector3 v1, v2, v3;
					v1.X = (m_xOrigin + left.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
					v1.Y = (m_yOrigin + left.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
					v1.Z = m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * MAP_HEIGHT_SCALE;
					v2.X = (m_xOrigin + prevRight.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
					v2.Y = (m_yOrigin + prevRight.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
					v2.Z = m_map->getHeight(m_xOrigin + prevRight.x, m_yOrigin + prevRight.y) * MAP_HEIGHT_SCALE;
					v3.X = (m_xOrigin + right.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
					v3.Y = (m_yOrigin + right.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
					v3.Z = m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * MAP_HEIGHT_SCALE;
					getTriangleIntersection(heights, xOffset, yOffset, width, width, v1, v2, v3);
				}
			}
		}
		if (ib)
			ib[curIndex] = prevNdxLeft;
		curIndex++;
		if (ib)
			ib[curIndex] = prevNdxRight;
		curIndex++;
		if (ib)
			ib[curIndex] = topRightNdx;
		curIndex++;
		if (heights) {
			Vector3 v1, v2, v3;
			v1.X = (m_xOrigin + left.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v1.Y = (m_yOrigin + left.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v1.Z = m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * MAP_HEIGHT_SCALE;
			v2.X = (m_xOrigin + right.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v2.Y = (m_yOrigin + right.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v2.Z = m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * MAP_HEIGHT_SCALE;
			v3.X = (minX + width) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v3.Y = (minY + width) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v3.Z = m_map->getHeight(minX + width, minY + width) * MAP_HEIGHT_SCALE;
			getTriangleIntersection(heights, xOffset, yOffset, width, width, v1, v2, v3);
		}
		return;
	}
	Int halfWidth = width / 2;
	bool done0, done1, done2, done3;
	rva00113C07(ib, heights, xOffset, yOffset, width, &done0, &done1, &done2, &done3, ndx, curIndex);
	if (done2)
		rva00113DE0(ib, heights, xOffset, yOffset, halfWidth, ndx, curIndex);
	if (done0)
		rva00113DE0(ib, heights, xOffset, yOffset + halfWidth, halfWidth, ndx, curIndex);
	if (done3)
		rva00113DE0(ib, heights, xOffset + halfWidth, yOffset, halfWidth, ndx, curIndex);
	if (done1)
		rva00113DE0(ib, heights, xOffset + halfWidth, yOffset + halfWidth, halfWidth, ndx, curIndex);
}
