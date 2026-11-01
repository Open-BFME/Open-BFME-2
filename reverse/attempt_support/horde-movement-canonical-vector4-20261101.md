# Use canonical Vector4 rows in horde movement transforms

Base `cf36afaa9728b55e941b86d9bc31085d1dc4aef9`. Source `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva0047A895.cpp`; scope claimed before editing.

Replace the private Vector4 row view with the registered header. Spell the known constant matrix components by name while preserving every rotation and translation expression. Retain both horde rank/member movement bodies, all locomotor/model-condition/position writes and the existing constructor import profile. The adjacent Coord3D companion and other class views remain independently scoped. The first direct-component probe preserves both native rows but changes an unreferenced Rotate_Z copy. Keep Rotate_Z visible as imported force-inline, the same documented technique already used for the identity constructor: it remains inlined in both native rows, while the standalone copy and its two now-unused CRT inline wrappers disappear. The ordinary native Rotate_Z owner remains Matrix3DRotateO1.cpp at00098CC0; no alias or provider rename is added. Removed definitions form a component referenced only by debug data or other removed definitions, with no incoming relocation from retained runtime code.

The normal byte gate preserves 2 matched row(s), with existing
extents 1018, 608 bytes. Actual COFF comparison
preserves 16 external code bodies and relocation lists.
Added external code definitions: ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
??AVector4@@QAEAAMH@Z, ?Rotate_Z@Matrix3D@@QAEXM@Z, _cosf, _sinf.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

The additional emitted definition(s) have no relocations and only debug incoming edges; their exact bytes are checked independently in the local controls. An empty canonical Vector4 constructor is `mov eax,ecx; ret`; the compiler array-constructor iterator, when present, is the 34-byte MSVC helper in this profile. Neither adds a call to retained runtime code. No new native row or authored-byte gain is claimed. Full non-debug section equality is not claimed for this unit.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva0047A895.cpp: LINKS  LINKED 1,616 -> 1,616 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 1,616)
link_check: 1 of 1 link cleanly; LINKED 1,616 -> 1,616 bytes (3.4s)
```

Controls: ignored `build/one-each-half-resources-20261101-1317/b2-01-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.

Final strict preparation passes both rows after the comment correction. Outgoing audit uses immutable base cf36afaa9728b55e941b86d9bc31085d1dc4aef9, source tip b7769508a0075a4b007dfd4edde3bee3e3daadce; INCONCLUSIVE (exit2): index/compiler baseline differs and affected 0CreateAHeroManager21FE49.cpp lacks a current receipt. Complete consumer selection is UNKNOWN. Bounded0d24c60eef preview preserves1616->1616. The existing Coord3D copy-constructor shadow divergence is unchanged: original/final retained COFF facts include that identical definition. No baseline or provider contract was changed to hide it. No new authored-byte, full-image, runtime or memory-performance claim. Resource budget14 jobs/48GiB; no local inference was needed.
