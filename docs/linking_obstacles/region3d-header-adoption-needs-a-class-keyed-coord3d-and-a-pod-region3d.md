### Region3D header adoption needs a class-keyed Coord3D and a POD Region3D view (2026-10-29)

At base `ab249dd2c4` the `class:Region3D` header item stays blocked after
re-testing both queued units against the canonical
`Code/Libraries/Include/Lib/Region3D.h`.

Retail's `Coord3D` is class-keyed: the export table carries
`??0Coord3D@@QAE@ABV0@@Z` (0x004216D3), `??4Coord3D@@QAEAAV0@ABV0@@Z`
(0x0000353A) and `??8Coord3D@@QBE_NABV0@@Z` (0x00003702), and region.cpp's
own rows spell `ABVCoord3D`/`PBVCoord3D` (`?expandBy@Region3D@@QAEXABVCoord3D@@@Z`
0x00006495, `?isInRegionNoZ@Region3D@@QBE_NPBVCoord3D@@@Z` 0x00004E0F,
`?isInRegionWithZ@Region3D@@QBE_NPBVCoord3D@@@Z` 0x00004E46,
`??6@YAAAVDebug@@AAV0@ABVCoord3D@@@Z` 0x000050BA). The canonical `Coord3D.h`
still spells `struct` (its contract key is decided by "bytes", which cannot
see a class key), so every unit that includes it emits `ABUCoord3D` names.
region.cpp also needs `Coord3D::scale` as a header inline (its 0x000036D1 row
is that inline, forced out by `_bfmeRegion3DInlineAnchor`), which only
`Coord3DCtorView.h`'s `COORD3D_VIEW_INLINE` variant provides, and that
companion header is struct-keyed too. Flipping the key is a coordinated
rename, not a per-class adoption: 696 ledger rows in files that include
`Lib/Coord3D.h` carry U-keyed `Coord3D` names and stop building until they
are renamed with the header.

2026-11-01 follow-up (Cortys): the six remaining Coord3D queue sources were
tested through the supported adoption dry run; none passed. The current
matrix private trial also proves that a preceding class forward declaration
does not retain V-key mangling once the canonical struct definition is seen.
The weapon wrapper cannot simply replace its custom constructor with a POD or
existing constructor-companion return object: the resulting 45--63-byte
temporary/copy paths differ from native's 30-byte direct result construction.
No source, header, contract or queue row was changed. Complete scoped verdicts
and prerequisites: `reverse/attempt_support/coord3d-header-prerequisites-20261101/`.

The second queued unit, `W3DViewGetAxisAlignedViewRegion.cpp`, does compose
with `Region3D.h` (the two units' views dedupe and the file compiles), but the
canonical header's user-provided default constructor, copy constructor and
destructor make its `Region3D mapExtent` EH-registered: the object built now
calls `??0Region3D@@QAE@XZ` and sets `c6 45 fc 01` where retail's local is a
POD, so `?getAxisAlignedViewRegion@W3DView@@AAEXAAURegion3D@@@Z` fails byte
comparison. region.cpp's rows need exactly those ctor/copy/dtor members
(0x00003F3A and the copy row), so the two queue rows need incompatible
shapes: a Region3D companion view, as `Coord3DCtorView.h` is for Coord3D, is
the missing piece. Both trial edits were reverted; no path moved and no
census gain is claimed.

**Debug streamer provider and donor survey (2026-10-30, coord3d-2; base `520c4d3ddd`, index `ccafe54d1d`):**
The `operator<<(Debug&, const Coord3D&)` that stopped pk-coord3d's region.cpp
apply is not missing. Retail exports it at 0x000050BA as
`??6@YAAAVDebug@@AAV0@ABVCoord3D@@@Z` (`reverse/exports.csv` ordinal 738),
the matched 103-byte row in `Code/Libraries/Source/WWVegas/WWMath/coord3d.cpp`
carries that name, and the census index defines it strongly in `coord3d.obj`
(retail COMDAT). The U-keyed spelling the struct header makes region.cpp call,
`??6@YAAAVDebug@@AAV0@ABUCoord3D@@@Z`, has no definition, reference or pin
anywhere. Neither supported route closes the gap. `pin_admission.py` refuses a
second real name on 0x000050BA, and a class-key twin is not an ICF fold. A
rename would replace an exported retail name with a non-retail one. The provider
stays as it is; region.cpp keeps its private class view until the key flip above.
Dry runs of the packet's TUs (`tu_skeleton.py --merge TU --dry-run`) find no
donor that a donor-side switch to `Lib/Coord3D.h` would admit. The Coord3D
donors already include the canonical header or a companion, and the conflicting
definition comes from the seed. In GarrisonContain, FlammableUpdate,
OCLSpecialPower, AssistedTargetingUpdate and DefaultProductionExitUpdate it is
Zero Hour's `Lib/BaseType.h` through `PreRTS.h`; in W3DTerrainVisual and
W3DPropDraw it is the same header through the seed's Zero Hour includes; in
Team it is the BFME 1 WWMath `coord3d.h`. GarrisonContain alone has 12 such
donors, and its other rejections (Thing, Team, GameLogic, Xfer, AsciiString
redefinitions) come from the same seed headers. TerrainLogic shows the
key conflict inside one retail TU: `FindClosestBeacon` and the segment helper
(0x0028077A, 0x0027F383) are V-keyed, `Bridge::getBridgeHeight` (0x0027FD2A)
and `Bridge::createTower` (0x0027EDBC) are U-keyed, so no single Coord3D
definition compiles all four. The prerequisites are, in order, the Coord3D key
flip with its ledger renames, then each Zero Hour seed moving off `PreRTS.h`.
No source or ledger changed and no census gain is claimed.

2026-11-04: PathDebugOutput's queued PathNode adoption reaches the same U/V-keyed debug-streamer prerequisite; trials reverted and its 93-byte control restored. [Consumer evidence](../../reverse/attempt_support/pathnode-debug-header-20261104-codex5/readme.md).

2026-11-04: W3DTerrainVisual absorbed two donors with six exact rows and passing link previews; its canonically adopted Init/update donors now expose SubsystemInterface redefinitions too. Move the seed off the Zero Hour class closure before retrying these donors. [Merge and prerequisite evidence](../../reverse/attempt_support/w3dterrain-merge-20261104/README.md).

2026-11-05 (claude-opus-5-5): the class key now blocks the real link directly. The real
link at `4f0e20847d` (run 42093361060, `errors.tsv`) lists two `exit.exp` LNK2001 errors
owned by Common/System/Snapshot.cpp: retail exports 285 `??0Matrix4D@@QAE@ABVCoord3D@@M@Z`
and 1391 `?Set@Matrix4D@@QAEAAV1@ABVCoord3D@@M@Z`, both at 0x00004079, but the row there is
`??0Matrix4D@@QAE@ABUCoord3D@@M@Z` because Snapshot.cpp includes the struct-keyed
canonical Coord3D.h (retested: a preceding `class Coord3D;` still emits ABU). Retail's
export table spells Coord3D with the class key in all 15 exports that name it. The third
Snapshot.cpp export error, 1799 `?lineSegmentIntersects@Region2D@@QAE_NABVCoord2D@@0@Z` at
0x000062FD (rowed as the placeholder `?rva000062FD@Rva000062FDRegion@@QBE...`), is
separate: it needs a non-const `lineSegmentIntersects` declaration in the canonical
Region2D.h, the body on Region2D's lo/hi, the one caller Rva00261D2EFilter.cpp and a row
rename; `class:Region2D` was held by another seat, so nothing was changed.
