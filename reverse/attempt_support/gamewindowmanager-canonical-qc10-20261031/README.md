# GameWindowManager shared header, qc-10, 2026-10-31

This is a bounded target ABI header, not a claim that all virtual method signatures or names are recovered. The old BFME1/ZH shadow shim is not promoted: it explicitly guesses where five BFME2-only slots belong. No slot is placed from that guess.

## Target facts

The matched50-byte factory at RVA4C4C7 allocates0x40 and calls8FC51. That matched18-byte constructor calls2C5334, then installs VA BC7C90. The matched100-byte base constructor2C5334 calls canonical SubsystemInterface1B4E63, initializes a four-byte STLport list base at+30, clears pointer-width fields+C..+2C and+34/+38, and sets+3C=-1. The shared header retains canonical SubsystemInterface and verifies sizeof0x40. Native list representation and unreviewed tail fields remain opaque storage; no replacement list lifetime is emitted.

The manager table occupies slots0..77; VA BC7DC8 is independently the next push-button table (Rva0008FF3ECtor and scalar deleting destructor8FFC4), so a run-of-code-pointers scanner's95 entries is not a table boundary. retail-table.tsv retains78 entries and the first entry of that separate next table. The compiled primary slot offsets match the positions used by all admitted callers. Unresolved slots are PRIVATE opaque declarations; their void spelling is not a recovered callable signature or method identity. No constructor, destructor or vtable provider is claimed/admitted through that opaque surface.

Known typed methods preserve target dispatch: ID/allocator14/15; hide/enable38/39; parent-chain47; parent append56/57; system/input send58/59; find-by-ID60; font callback76. The font callback remains neutral slot76, since table/body equality does not prove the qualified non-virtual winFindFont helper is itself the virtual member. The helper's existing non-virtual declaration is retained. Target list head+C and keyboard focus+20 are established by existing body owners; other descriptive pointer member names follow the ZH donor and are not claimed as original target spelling.

## Donor adoption and provenance

GameWindowManager_dumpWindow and GameWindowManager_enableWindowsInRange replace their private classes with the shared header; the existing+20 field maps to keyboard focus, and slot59 uses the explicit winSendInputMsg interface. The record-create font calls use slot76. All seven rows are byte-exact.

window_layout.cpp consumes a BFME1-only partial manager through the reconstructed BFME1 window_layout.h. The adapted Code/GameEngine/Include/GameClient/WindowLayout.h retains that donor declaration projection, removes its obsolete manager class and includes the new BFME2 manager. BFME1 revision7a8a034afa7dd3530d9a99dc48cfec711626256c is unchanged. Original header addresses remain explicitly donor facts. The three admitted WindowLayout rows are byte-exact. No header provenance is asserted to prove original BFME2 source placement.

## Checks

Boat build.sh:10/10 matched across the three requested sources. Formal header_adopt_lane accept: PASS all three, including per-unit link prediction. Frozen-file checks pass both new headers and the source checks. Normal hooks decide admission; their final results are retained in the bundle handoff. Existing unadopted views are queued via the header lane queue writer.

Refresh against 3261895e6c5f780e8d3178546822b95b71c3df8c: original verified source/layout facts retained; canonical registry and adoption queue recreated through header_adopt_lane, and accept/hooks rerun. docs/linking_obstacles.md is held by hdr-player-2; its original append remains in item 5265 rejected bundle for a later register-only handoff. No edit to that held file is included in this refresh.
