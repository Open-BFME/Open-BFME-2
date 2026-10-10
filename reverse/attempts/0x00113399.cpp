// ?rva00113399@W3DTerrainBackground@@QAEXPAGPAXHHHH0AAH@Z
// partial score=0.7464549916629483 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?rva00113399@W3DTerrainBackground@@QAEXPAGPAXHHHH0AAH@Z
// partial score=0.86 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [00113399,00113C07),2158B, RET32. WorldBuilder places the body in
// W3DTerrainBackground.cpp (unnamed there). Rectangle form of the ZH
// fillVBRecursive triangle fan: clamp the (width x height) block at
// (xOffset, yOffset) to the map extent, walk its left and right edges with
// the advance helpers 0x0011274C / 0x001127F2 and emit three indices per
// fan triangle into ib (when present), counting through curIndex. Corner
// triangles are emitted only for in-mesh corners (0x001126FD); when the
// auxiliary height buffer is present every emitted triangle is also cast
// through getTriangleIntersection (0x0011319A). Retail computes the last
// triangle's right-vertex Y from the X origin (+0x50); kept as found.

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

class WorldHeightMap
{
public:
	Int getXExtent() { return m_width; }
	Int getYExtent() { return m_height; }
	Int getBorderSize() { return m_borderSize; }
	UnsignedShort getHeight(Int x, Int y) { return ((BoundedShortGrid *)this)->rva00062A58(x, y); }
	bool isInMesh(Int x, Int y) { return ((const Rva00729300BitPlane *)this)->test(x, y); }

private:
	unsigned char m_pad00[0x08];
	Int m_width;
	Int m_height;
	Int m_borderSize;
};

class Rva001127F2TerrainPrefix
{
public:
	bool advanceScan(ICoord2D &right, int xOffset, int yOffset, int width, int height);
	bool advanceYThenX(ICoord2D &point, int xOffset, int yOffset, int width, int height);
};

class W3DTerrainBackground
{
public:
	void getTriangleIntersection(Vector3 *heights, int x, int y, int width, int height,
		const Vector3 &v0, const Vector3 &v1, const Vector3 &v2);
	void rva00113399(UnsignedShort *ib, void *heights, Int xOffset, Int yOffset,
		Int width, Int height, UnsignedShort *ndx, Int &curIndex);

private:
	bool advanceLeft(ICoord2D &left, Int xOffset, Int yOffset, Int width, Int height)
	{
		return ((Rva001127F2TerrainPrefix *)this)->advanceYThenX(left, xOffset, yOffset, width, height);
	}
	bool advanceRight(ICoord2D &right, Int xOffset, Int yOffset, Int width, Int height)
	{
		return ((Rva001127F2TerrainPrefix *)this)->advanceScan(right, xOffset, yOffset, width, height);
	}

	unsigned char m_pad00[0x50];
	Int m_xOrigin;
	Int m_yOrigin;
	Int m_width;
	WorldHeightMap *m_map;
};

// ?rva00113399@W3DTerrainBackground@@QAEXPAGPAXHHHH0AAH@Z
void W3DTerrainBackground::rva00113399(UnsignedShort *ib, void *heights, Int xOffset, Int yOffset,
	Int width, Int height, UnsignedShort *ndx, Int &curIndex)
{
	Int minX = m_xOrigin + xOffset;
	Int minY = m_yOrigin + yOffset;
	Int limitX = (*(WorldHeightMap*volatile*)&m_map)->getXExtent() - 1;
	Int limitY = m_map->getYExtent() - 1;
	Int maxX = xOffset + width;
	if (maxX + m_xOrigin > limitX)
		maxX = limitX - m_xOrigin;
	Int maxY = yOffset + height;
	if (maxY + m_yOrigin > limitY)
		maxY = limitY - m_yOrigin;
	Bool topRightInMesh = m_map->isInMesh(m_xOrigin + maxX, m_yOrigin + maxY);
	Int pitch = m_width + 1;
	Int topRightNdx = ndx[maxX + maxY * pitch];

	ICoord2D left;
	left.x = xOffset;
	left.y = yOffset;
	ICoord2D right;
	right.x = xOffset;
	right.y = yOffset;
	advanceLeft(left, xOffset, yOffset, width, height);
	advanceRight(right, xOffset, yOffset, width, height);

	UnsignedShort prevNdxLeft;
	UnsignedShort prevNdxRight;
	if (m_map->isInMesh(minX, minY)) {
		if (ib)
			ib[curIndex] = ndx[xOffset + yOffset * pitch];
		curIndex++;
		prevNdxRight = ndx[right.x + right.y * (m_width + 1)];
		if (ib)
			ib[curIndex] = prevNdxRight;
		curIndex++;
		prevNdxLeft = ndx[left.x + left.y * (m_width + 1)];
		if (ib)
			ib[curIndex] = prevNdxLeft;
		curIndex++;
		if (heights) {
			Vector3 v0;
			Vector3 v1;
			Vector3 v2;
			v0.X = minX * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v0.Y = minY * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v0.Z = m_map->getHeight(minX, minY) * MAP_HEIGHT_SCALE;
			v1.X = (m_xOrigin + right.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v1.Y = (m_yOrigin + right.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v1.Z = m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * MAP_HEIGHT_SCALE;
			v2.X = (m_xOrigin + left.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v2.Y = (m_yOrigin + left.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v2.Z = m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * MAP_HEIGHT_SCALE;
			getTriangleIntersection((Vector3 *)heights, xOffset, yOffset, width, height, v0, v1, v2);
		}
	} else {
		prevNdxRight = ndx[right.x + right.y * (m_width + 1)];
		prevNdxLeft = ndx[left.x + left.y * (m_width + 1)];
		curIndex++;
		curIndex++;
		curIndex++;
	}

	Bool didLeft = true;
	Bool didRight = true;
	while (didLeft || didRight) {
		ICoord2D prevLeft = left;
		didLeft = advanceLeft(left, xOffset, yOffset, width, height);
		if (didLeft) {
			if (ib)
				ib[curIndex] = prevNdxLeft;
			curIndex++;
			if (ib)
				ib[curIndex] = prevNdxRight;
			curIndex++;
			prevNdxLeft = ndx[left.x + left.y * (m_width + 1)];
			if (ib)
				ib[curIndex] = prevNdxLeft;
			curIndex++;
			if (heights) {
				Vector3 v0;
				Vector3 v1;
				Vector3 v2;
				v0.X = (m_xOrigin + prevLeft.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v0.Y = (m_yOrigin + prevLeft.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v0.Z = m_map->getHeight(m_xOrigin + prevLeft.x, m_yOrigin + prevLeft.y) * MAP_HEIGHT_SCALE;
_ReadWriteBarrier();
				v1.X = (m_xOrigin + right.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v1.Y = (m_yOrigin + right.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v1.Z = m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * MAP_HEIGHT_SCALE;
				v2.X = (m_xOrigin + left.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v2.Y = (m_yOrigin + left.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v2.Z = m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * MAP_HEIGHT_SCALE;
				getTriangleIntersection((Vector3 *)heights, xOffset, yOffset, width, height, v0, v1, v2);
			}
		}
		ICoord2D prevRight = right;
		didRight = advanceRight(right, xOffset, yOffset, width, height);
		if (didRight) {
			if (ib)
				ib[curIndex] = prevNdxLeft;
			curIndex++;
			if (ib)
				ib[curIndex] = prevNdxRight;
			curIndex++;
			prevNdxRight = ndx[right.x + right.y * (m_width + 1)];
			if (ib)
				ib[curIndex] = prevNdxRight;
			curIndex++;
			if (heights) {
				Vector3 v0;
				Vector3 v1;
				Vector3 v2;
				v0.X = (m_xOrigin + left.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v0.Y = (m_yOrigin + left.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v0.Z = m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * MAP_HEIGHT_SCALE;
				v1.X = (m_xOrigin + prevRight.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v1.Y = (m_yOrigin + prevRight.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v1.Z = m_map->getHeight(m_xOrigin + prevRight.x, m_yOrigin + prevRight.y) * MAP_HEIGHT_SCALE;
				v2.X = (m_xOrigin + right.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v2.Y = (m_yOrigin + right.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
				v2.Z = m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * MAP_HEIGHT_SCALE;
				getTriangleIntersection((Vector3 *)heights, xOffset, yOffset, width, height, v0, v1, v2);
			}
		}
	}

	if (topRightInMesh) {
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
			Vector3 v0;
			Vector3 v1;
			Vector3 v2;
			v0.X = (m_xOrigin + left.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v0.Y = (m_yOrigin + left.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v0.Z = m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * MAP_HEIGHT_SCALE;
			v1.X = (m_xOrigin + right.x) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v1.Y = (m_xOrigin + right.y) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v1.Z = m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * MAP_HEIGHT_SCALE;
			v2.X = (minX + width) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v2.Y = (minY + width) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			v2.Z = m_map->getHeight(minX + width, minY + width) * MAP_HEIGHT_SCALE;
			getTriangleIntersection((Vector3 *)heights, xOffset, yOffset, width, height, v0, v1, v2);
		}
	}
}
