# MapUtil.cpp: dropping Zero Hour's `MapCache::addMap` (banked, 2026-11-03, seat halilkkaya-lk19)

Base `86f87c9a1b`. Patch: `maputil-drop-zh-addmap.patch` (MapUtil.cpp only, +28/-330).

## What the patch does

- Deletes Zero Hour's unrowed `MapCache::addMap` (a strong duplicate of retail's
  0x00304E64 row in `MapCacheAddMap.cpp`) and the static chain only it reached:
  `calcCRC`, `ParseObjectDataChunk`, `ParseObjectsDataChunk`, `ParseSizeOnly`,
  `ParseSizeOnlyInChunk`, `loadMap`. Retail's own versions are the external rows
  0x0030050E, 0x00302907, 0x00302B06, 0x00302F1B and 0x00302F2B.
- Emits the four waypoint-tree rows (0x0016DB20, 0x0016D590, 0x0016D760,
  0x0073B560) by explicit instantiation of the single members. All four verify.
- Makes `getExtent` external. That fails, see below.

## Result on `./build.sh MapUtil.cpp`: 17/19

- `?getExtent@@YAXPAURegion3D@@@Z` 0x003000B5 fails. Retail takes `extent` in EAX
  (`f3 0f 10 0d ...`, no stack load); the external copy starts `8b 44 24 04`.
  The compiler uses that convention only for a `static` whose callers it all
  sees, and it emits the out-of-line copy only when a later function in the unit
  references it. Retail's image has no E8/E9 or absolute reference to 0x003000B5
  (raw scan of every section), so its caller inlined it: retail's `addMap`, whose
  extent stores (lo.x, lo.y, hi.x, hi.y, lo.z, hi.z) are getExtent's order.
- `_M_insert_overflow<ICoord2D>` 0x00181770 is no longer emitted here.
  `BfmeFVFDescriptorVertexDeclaration.cpp` emits retail's 259-byte body (its
  header comment says so) and calls it from push_back 0x00181880; all its rows
  are approved for `dx8fvf.cpp`, as is 0x00181770.

## Why the merge is blocked

`tu_skeleton.py --merge MapUtil.cpp` refuses: the file holds rows of other TUs.
`--split MapUtil.cpp` (fresh in-memory map): 13 rows with no TU, 2
`BfmeResourceEnumerator.cpp` (0x00620720, 0x00620E90), 2 `meshgeometry.cpp`
(0x0016D590, 0x0016D760), 1 `dx8fvf.cpp` (0x00181770), 1 `render2dsentence.cpp`.
All are implicit STLport instantiations: `--split ... --for dx8fvf.cpp --dry-run`
answers `0x00181770: no definition spells its name`. The meshgeometry pair are
ICF-shaped generic tree bodies at addresses retail never references; nothing in
meshgeometry.cpp can honestly instantiate an AsciiString/Coord3D tree.
`MapCacheAddMap.cpp` also carries private 256-byte `MapMetaData`, `WaypointMap`
and `MapCache` views and builds at /O1, against MapUtil.cpp's Zero Hour layout.

## Link effect measured on current objects (base)

`link_check`: MapCacheAddMap.cpp 1,191 -> 0 and MapCacheLoadUserMapsBFME2.cpp
1,198 -> 0 since the census (duplicate and selected `addMap`); MapUtil.cpp does
not link (14 unresolved, 7 of them reached only by the dropped chain:
CachedFileInputStream ctor/dtor/open, MapObject ctor, getWaypointName,
Dict::getType, registerParser, FileSystem::openFile).

## Next

Land retail's addMap in MapUtil.cpp through a merge once the foreign template
rows have an honest home (or a TU-map decision for them), reconcile
MapCacheAddMap.cpp's private views with MapUtil.cpp's, then apply this patch
without the `getExtent` hunk.
