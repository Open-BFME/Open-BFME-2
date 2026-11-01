// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva00111FCF@W3DTerrainBackground@@QAEXXZ, retail 0x00111FCF (124 bytes,
// RET), directly before isEdgeAligned (0x0011204B) on the same terrain
// prefix (origins +0x50/+0x54, tile width +0x58, map +0x5C, map extents
// +0x08/+0x0C). WorldBuilder's twin 0x007CA830 shapes the body: for every
// cell of the (width+1)^2 tile it clamps origin+i / origin+j to the last map
// row/column with a MIN-style self assignment and clears that cell through
// the rowed grid bit setter 0x000AD9AB. Address-derived method name.
typedef int Int;

class Rva000AD9AB
{
public:
	void rva000AD9AB(Int x, Int y, bool value);
};

class WorldHeightMap
{
public:
	// Keep prefix accessors inline without competing canonical getter copies.
	__declspec(dllimport) __forceinline Int getXExtent() { return m_width; }
	__declspec(dllimport) __forceinline Int getYExtent() { return m_height; }
private:
	unsigned char m_pad00[0x08];
	Int m_width;
	Int m_height;
};

class W3DTerrainBackground
{
public:
	void rva00111FCF();
private:
	unsigned char m_pad00[0x50];
	Int m_xOrigin;
	Int m_yOrigin;
	Int m_width;
	WorldHeightMap *m_map;
};

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void W3DTerrainBackground::rva00111FCF()
{
	Int xMax = m_map->getXExtent() - 1;
	Int yMax = m_map->getYExtent() - 1;
	Int xOrg = m_xOrigin;
	Int yOrg = m_yOrigin;
	for (Int i = 0; i <= m_width; i++) {
		for (Int j = 0; j <= m_width; j++) {
			Int x = xOrg + i;
			x = MIN(x, xMax);
			Int y = yOrg + j;
			y = MIN(y, yMax);
			((Rva000AD9AB *)m_map)->rva000AD9AB(x, y, false);
		}
	}
}
