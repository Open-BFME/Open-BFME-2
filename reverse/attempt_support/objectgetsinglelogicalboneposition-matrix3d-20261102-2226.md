# Adopt canonical Matrix3D in ObjectGetSingleLogicalBonePosition

Base `92f12c3fc4e42305d6c26c1da9290c17cc5d20cd`. Source `Code/GameEngine/Source/GameLogic/Object/ObjectGetSingleLogicalBonePosition.cpp`; scope claimed before editing.

Use the existing registered Matrix3D header and retain native storage offsets, code and provider bindings. Source-specific local helpers preserve the original inline copy/read shape where needed.

The normal byte gate preserves 2 matched row(s), with existing
extents 161, 120 bytes. Actual COFF comparison
preserves 5 external code bodies and relocation lists.
Added external code definitions: ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
??4Matrix3D@@QAEAAV0@ABV0@@Z.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret. The Vector3 value constructor matches the unchanged ShadowRenderMeshVolumeBounds37B profile or the independent isolated38B frame-pointer profile compiled with the unchanged target flags, both with no relocations (profile recorded in the diagnostic package); this is an emitted-code profile, not a new native identity. The optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/ObjectGetSingleLogicalBonePosition.cpp: LINKS  LINKED 281 -> 281 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 281)
link_check: 1 of 1 link cleanly; LINKED 281 -> 281 bytes (3.1s)
```

Controls: ignored `build/up-to-eighteen-each-20261102-2226/b2-12-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
