### The real link's two duplicates (2026-11-03)

`MapCache::addMap`: `MapUtil.cpp` holds an unrowed donor copy; the matched body is in
`MapCacheAddMap.cpp`. Deleting the copy is not enough. It is the only user of `getExtent`, and retail's
`getExtent` (0x003000B5) takes `extent` in `eax` with no stack load, which the compiler does only for
a `static` whose every caller it sees, so retail's `addMap` was in this same unit. Making `getExtent`
external fails its bytes. The two template instantiations it also held pass as explicit instantiations
of `std::map<AsciiString, Coord3D>` and `std::vector<ICoord2D>`. Next: merge the matched body into
`MapUtil.cpp` and drop the copy.

Rechecked 2026-11-03 at `86f87c9a1b` (lk19): same result for the tree rows (17/19 with the copy and its
static `calcCRC`/`loadMap`/parser chain deleted). The merge is refused because `MapUtil.cpp` is mixed:
two rows approved for `BfmeResourceEnumerator.cpp`, two for `meshgeometry.cpp` (0x0016D590, 0x0016D760),
one for `dx8fvf.cpp` (0x00181770) and one for `render2dsentence.cpp`. All are implicit STLport
instantiations, and `--split` cannot carve them (`0x00181770: no definition spells its name`).
0x00181770 has an exact emitter in `BfmeFVFDescriptorVertexDeclaration.cpp`, whose rows are all
`dx8fvf.cpp`'s. The meshgeometry pair have no honest emitter there. `MapCacheAddMap.cpp` also has
private 256-byte `MapMetaData`/`MapCache` views at /O1. The patch and evidence are banked in
`reverse/attempt_support/maputil-addmap-dup-20261103-lk19/`.

`@_RTC_CheckStackVars@8`: already recorded in
`reverse/attempt_support/rtc-stack-owner-20261028-codex.md`; it needs the stack unit's ownership settled.

Settled 2026-11-04 by the owner: 0x0075A5A2 is placed with `RtcStack.cpp`. `__RTC_CheckEsp` consumes the caller's ZF, so
it cannot be C++ and the anti-lift rule bars a naked body, so it is the sibling `Code/masm_dumps/RTC_CheckEsp.asm` again.
The link then has no reason to pull `stack.obj`. The next real link verifies that; if another name still pulls it, this
is not cleared.
