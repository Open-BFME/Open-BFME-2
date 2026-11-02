# Adopt canonical Vector4 in W3DShadowMapManagerTextureMatrix

Base `6ce079924bc1f37e6870576a1ecbc151598e76b1`. Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowMapManagerTextureMatrix.cpp`; scope claimed before editing.

Use the existing registered Vector4 header. Preserve retained code, field offsets, evaluation order and relocation targets. Private per-unit compilation precedes the normal byte and acceptance gates.

The normal byte gate preserves 1 matched row(s), with existing
extents 206 bytes. Actual COFF comparison
preserves 9 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
none.

All 14 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowMapManagerTextureMatrix.cpp: LINKS  LINKED 206 -> 206 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 206)
link_check: 1 of 1 link cleanly; LINKED 206 -> 206 bytes (2.8s)
```

Controls: ignored `build/up-to-eighteen-each-20261102-1632/b2-09-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
