# Adopt canonical Vector4 in W3DScriptedModelDraw

Base `d41f899c6523ea356ddc9f90779eda2a8170094c`. Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DScriptedModelDraw.cpp`; scope claimed before editing.

Use the existing registered storage header and preserve native layout, ABI, retained bytes and relocation targets. Local helpers retain the original inline operation order where required.

The normal byte gate preserves 19 matched row(s), with existing
extents 363, 259, 623, 1659, 10, 10, 10, 10, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 13 bytes. Actual COFF comparison
preserves 38 external code bodies and relocation lists.
Added external code definitions: ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
none.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret. The Vector3 value constructor matches the unchanged ShadowRenderMeshVolumeBounds37B profile or the independent isolated38B frame-pointer profile compiled with the unchanged target flags, both with no relocations (profile recorded in the diagnostic package); this is an emitted-code profile, not a new native identity. The optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations. The compiler array iterator has measured34/48B profiles; the additional34B frame-pointer form is independently reproduced with the unchanged target flags. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, native-address pin, alias, data row, source path or baseline changes. No compiler flag changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DScriptedModelDraw.cpp: LINKS  LINKED 2,938 -> 2,938 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 2,938)
link_check: 1 of 1 link cleanly; LINKED 2,938 -> 2,938 bytes (3.2s)
```

Controls: ignored `build/up-to-eighteen-each-20261102-2256/b2-13-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
