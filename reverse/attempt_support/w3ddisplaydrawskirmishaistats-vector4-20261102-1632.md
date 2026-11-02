# Adopt canonical Vector4 in W3DDisplayDrawSkirmishAIStats

Base `6ce079924bc1f37e6870576a1ecbc151598e76b1`. Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDrawSkirmishAIStats.cpp`; scope claimed before editing.

Use the existing registered Vector4 header. Preserve retained code, field offsets, evaluation order and relocation targets. Private per-unit compilation precedes the normal byte and acceptance gates. Explicitly force-inline the existing empty Matrix3D construction to prevent an added out-of-line array-construction call after Vector4 adoption; accept only unchanged native code.

The normal byte gate preserves 1 matched row(s), with existing
extents 524 bytes. Actual COFF comparison
preserves 9 external code bodies and relocation lists.
Added external code definitions: ??0Matrix3D@@QAE@XZ, ??0Vector4@@QAE@XZ, ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
none.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret. The Vector3 value constructor matches the unchanged current ShadowRenderMeshVolumeBounds object byte-for-byte with no relocations (independent profile recorded in the diagnostic package); this is an emitted-code profile, not a new native identity. The optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDrawSkirmishAIStats.cpp: LINKS  LINKED 520 -> 520 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 520)
link_check: 1 of 1 link cleanly; LINKED 520 -> 520 bytes (2.8s)
```

Controls: ignored `build/up-to-eighteen-each-20261102-1632/b2-07-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
