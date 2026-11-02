# Adopt canonical Vector3 in BridgeGetBridgeHeight

Base `92f12c3fc4e42305d6c26c1da9290c17cc5d20cd`. Source `Code/GameEngine/Source/GameLogic/Map/BridgeGetBridgeHeight.cpp`; scope claimed before editing.

Use the existing registered Vector3 header and retain native storage offsets, code and provider bindings. Source-specific local helpers preserve the original inline copy/read shape where needed. Direct assignment introduced the canonical out-of-line Vector3 copy; a scalar-copy helper emitted SSE stores and memcpy added a call. The successful representation copy uses the already present Coord3D view (same established three-float12B footprint and existing implicit block assignment), retaining the original three MOVSD instructions and713B parent. No new compiler setting, raw-byte source or shared-header change.

The normal byte gate preserves 1 matched row(s), with existing
extents 713 bytes. Actual COFF comparison
preserves 7 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
none.

All 12 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Map/BridgeGetBridgeHeight.cpp: LINKS  LINKED 710 -> 710 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 710)
link_check: 1 of 1 link cleanly; LINKED 710 -> 710 bytes (3.1s)
```

Controls: ignored `build/up-to-eighteen-each-20261102-2226/b2-08-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
