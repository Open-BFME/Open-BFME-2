// cl: /O1 /G7 /arch:SSE /MD /EHsc /ICode/Libraries/Include
// ?doPartialUpdate@FlatHeightMapRenderObjClass@@... retail 0x000E0F1E..0x000E1072
// (340 bytes, RET 12). BFME1 575ba2b0 FlatHeightMap.cpp:277 and the ZH
// same-name body supply the refcount/tile traversal guide (donor facts).
// Target facts from the native body: REF_PTR_SET of the map at +0x37C0,
// the partial range clipped to sixteen-cell tile bounds, 0xD4-byte tiles at
// +0x3888, tile dimensions +0x3890/+0x3894, the flag byte +0x37E0 passed to
// the per-tile update, and the +0x3930 byte cleared at the end. WB 0x7B78B0
// carries an accidental inlined RefCount.h name, so identity rests on the
// donor lead. The tile bounds are an IRegion2D local (its lo.x member is
// enregistered, leaving retail's unused frame slot) converted with
// REAL_TO_INT_FLOOR/CEIL spelled fast_float2long_round(floorf/ceilf(x)).
// Tile callees: rowed rva00113110 and W3DTerrainBackground::doPartialUpdate (0x00115044).
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
#include "Lib/ICoord2D.h"
#include "Lib/IRegion2D.h"
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(floorf(x)))
#define REAL_TO_INT_CEIL(x) (fast_float2long_round(ceilf(x)))
class RefRenderObjListIterator;
#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"
class Rva00113110Holder { public: void rva00113110(void *); };
class W3DTerrainBackground { public: void doPartialUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, bool doTextures, bool flag); };
struct TerrainTileView { char data[0xd4]; };
class FlatHeightMapRenderObjClass
{
public:
	void doPartialUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, RefRenderObjListIterator *pLightsIterator);
private:
	char m_pad0[0x37c0];
	WorldHeightMap *m_map;
	char m_pad37c4[0x37e0 - 0x37c4];
	bool m_tileFlag;
	char m_pad37e1[0x3888 - 0x37e1];
	TerrainTileView *m_tiles;
	int m_numTiles, m_tilesWidth, m_tilesHeight;
	char m_pad3898[0x3930 - 0x3898];
	bool m_needUpdate;
};
void FlatHeightMapRenderObjClass::doPartialUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, RefRenderObjListIterator *)
{
	if (htMap) {
		++htMap->NumRefs;
		WorldHeightMap *old = m_map;
		if (old && 0 == --old->NumRefs)
			old->Delete_This();
		m_map = htMap;
	}
	IRegion2D tiles;
	tiles.lo.x = REAL_TO_INT_FLOOR(partialRange.lo.x / 16.0f);
	tiles.lo.y = REAL_TO_INT_FLOOR(partialRange.lo.y / 16.0f);
	tiles.hi.x = REAL_TO_INT_CEIL(partialRange.hi.x / 16.0f);
	tiles.hi.y = REAL_TO_INT_CEIL(partialRange.hi.y / 16.0f);
	if (tiles.lo.x < 0) tiles.lo.x = 0;
	if (tiles.lo.y < 0) tiles.lo.y = 0;
	if (tiles.hi.x >= m_tilesWidth) tiles.hi.x = m_tilesWidth;
	if (tiles.hi.y >= m_tilesHeight) tiles.hi.y = m_tilesHeight;
	for (int i = tiles.lo.x; i < tiles.hi.x; ++i)
		for (int j = tiles.lo.y; j < tiles.hi.y; ++j) {
			TerrainTileView *tile = m_tiles + j * m_tilesWidth + i;
			((Rva00113110Holder *)tile)->rva00113110(htMap);
			((W3DTerrainBackground *)tile)->doPartialUpdate(partialRange, htMap, true, m_tileFlag);
		}
	m_needUpdate = false;
}
