# PolygonTrigger shared target header, qc-10, 2026-10-31

The admitted scope is the two class-item donors Rva002E3A39Pair.cpp and PolygonTriggerCtor.cpp. No new retail row, pin, alias, body, or original-name claim is introduced.

## Layout and hierarchy

The complete matched constructor at RVA2E3FAB (158 bytes, hidden most-derived flag) and parser new0x64 prove the complete size. The base constructor330C50 (114 bytes), its standalone vbtable{-4,38}, and all seven native vtordisp thunks2E3E80..2E3EB0 establish real virtual inheritance. Their existing C++ declarations are extracted from the matched constructor donor into the shared header. PolygonLink remains first in declaration order: its next-link store must precede the primary base call even though MSVC places that data-only base after the polymorphic bases. No flattening, field relocation, hand-written table, stub body or added compiler control is used.

layout-comparison.json contains fresh private-object layouts before and after extraction. All five owner/base classes preserve size, class-key, base offsets/order, fields, virtual slots and vfptr state. The complete PolygonTrigger sizeof assertion is0x64. This is stronger than assuming one smaller private projection describes the whole class.

## Container view and geometry donor

The container begins at the primary owner's+8. Matched Rva0030B9DD constructor30B9DD and its base30B980 establish its2C-byte extent; existing330C50 bodies establish begin/end/capacity at+0/+4/+8 and index+28, with eight-byte point stride. Those fields replace the constructor donor's opaque same-size storage. Its destructor remains declaration-only, matching that donor's existing EH binding to the rowed folded worker7FAB3; no private copy of the point class is introduced.

The new pointCount inline helper is an implementation accessor, not a recovered retail entry/name. It computes the proven byte difference and arithmetic shift3, so the geometry donor can consume the real primary base without exposing a second flat PolygonTrigger class or depending on an incomplete point type's sizeof. Both geometry bodies remain byte-exact, including the723-byte camera movement routine.

The seven virtual interface declarations, address-derived base names and unrecovered fields retain their existing target evidence and neutral spellings. The ZH PolygonTrigger header supplies a destination lead only; its MemoryPoolObject/Snapshot layout is not copied into BFME2.

## Verification

Boat build.sh:4/4 existing rows across both donors, with the naturally emitted unwind handler resolved. Frozen-file checks pass both sources and the new header. header_adopt_lane accept passes both including per-unit link prediction. The scoped header gate reports12 dependent ledger sources and zero red chunks. Final normal-hook results are retained in the bundle handoff. Other old private views remain in the header queue; no full class-name/source recovery or census gain is claimed.

## Shadow identity finding

The normal hook reports one outside-register shadow finding for emitted
??0Coord3D@@QAE@ABU0@@Z. A controlled comparison compiled the ORIGINAL donor
through build.sh, read that helper's complete COFF bytes/relocations, restored
the changed donor and reverified it through build.sh. Original and changed
helper bytes and relocation lists are IDENTICAL. Thus the existing divergent
inline copy is not introduced or altered by this header adoption. The shadow
finding is retained for lander visibility, not baselined or silently retired.
coord-copy-comparison.json retains both byte strings and the original gate.

Refresh against 3261895e6c5f780e8d3178546822b95b71c3df8c: original verified source/layout facts retained; canonical registry and adoption queue recreated through header_adopt_lane, and accept/hooks rerun. docs/linking_obstacles.md is held by hdr-player-2; its original append remains in item 5837 rejected bundle for a later register-only handoff. No edit to that held file is included in this refresh.
