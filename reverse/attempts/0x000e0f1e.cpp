// ?doPartialUpdate@FlatHeightMapRenderObjClass@@QAEXABUIRegion2D@@PAVWorldHeightMap@@PAVRefRenderObjListIterator@@@Z
// partial score=0.8352941176470589 date=2026-10-10
// BFME1 575ba2b0 FlatHeightMap.cpp:277 and pinned ZH same-name donor
// supply the refcount/tile traversal guide. Named WB7B78B0 is polluted
// by an inlined RefCount.h name; identity is a supported reference lead,
// not a claim recovered from that accidental name. Native4E0F1E..4E1072
// is complete340B RET12 and independently proves clipped sixteen-cell
// bounds, D4-byte tiles, map37C0, tile3888, dimensions3890/3894, flag37E0
// and final byte3930. Original BaseType.h:182 helper is a proven x87
// blocker: ordinary casts and QIfist produce a different qword conversion.
// This is BANKED, not a recovery: frame18 vs native20 and conversion/bound
// slot allocation differ. Tile resource113110 is unrowed and unpinned;
// tile update retains the existing neutral115044 four-arg declaration.
// The field views are incomplete and must be reconciled with the existing
// FlatHeightMap home before admission; no complete class layout is asserted.
// cl: /O1 /G7 /arch:SSE  /MD /EHsc
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) double __cdecl ceil(double);
__forceinline long fast_float2long_round(float f){long i;__asm {
 fld [f]
 fistp [i]
 } return i;}
struct IRegion2D {int minX,minY,maxX,maxY;};
class RefRenderObjListIterator;
class WorldHeightMap {public:virtual void Delete_This();int refs;};
class Rva00113110Holder {public:void rva00113110(void *);};
class Rva00115044 {public:void rva00115044(int *,int,int,unsigned char);};
struct TerrainTileView {char data[0xd4];};
class FlatHeightMapRenderObjClass {public:
 void doPartialUpdate(const IRegion2D &,WorldHeightMap *,RefRenderObjListIterator *);
private:
 char pad[0x37c0]; WorldHeightMap *m_map;
 char pad37c4[0x37e0-0x37c4];unsigned char m_nativeFlag;
 char pad37e1[0x3888-0x37e1];TerrainTileView *m_tiles;
 int m_numTiles,m_tilesWidth,m_tilesHeight;
 char pad3898[0x3930-0x3898];bool m_needUpdate;
};
void FlatHeightMapRenderObjClass::doPartialUpdate(const IRegion2D &range,WorldHeightMap *map,RefRenderObjListIterator *) {
 if(map){++map->refs; WorldHeightMap *old=m_map; if(old && --old->refs==0)old->Delete_This();m_map=map;}
 int minX=fast_float2long_round((float)floor(range.minX/16.0f));
 int minY=fast_float2long_round((float)floor(range.minY/16.0f));
 int maxX=fast_float2long_round((float)ceil(range.maxX/16.0f));
 int maxY=fast_float2long_round((float)ceil(range.maxY/16.0f));
 if(minX<0)minX=0;
 if(minY<0)minY=0;
 if(maxX>=m_tilesWidth)maxX=m_tilesWidth;
 if(maxY>=m_tilesHeight)maxY=m_tilesHeight;
 for(int i=minX;i<maxX;++i)for(int j=minY;j<maxY;++j) {
  TerrainTileView *tile=m_tiles+j*m_tilesWidth+i;
  ((Rva00113110Holder *)tile)->rva00113110(map);
  ((Rva00115044 *)tile)->rva00115044((int *)&range,(int)map,1,m_nativeFlag);
 }
 m_needUpdate=false;
}
