# Six BFME 2 Vector4 adoptions: bounded batch evidence

Outgoing base `c691e0eefb91defcaa999782881348ad9fd6e64f`; source-audit tip `87c399ab832e3cc25b2eb93fe4c1a5d936d9107c` before this documentation-only
amendment. Six claimed sources replace six private Vector4 copies with the
registered storage. Normal gates preserve 104 existing function/EH rows,
18422 bytes of ledger extents and 404 retained external code/relocation
instances. Six Vector4 queue keys were retired by owning acceptance, not by hand.
No new matched row or native/authored-byte gain is claimed.

- [Use canonical Vector4 rows in pristine query](pristine-query-vector4-20261101-1501.md): 3 rows, 744 bytes, 16 retained bodies.
- [Use canonical Vector4 rows in debris draw](debris-draw-vector4-20261101-1501.md): 3 rows, 569 bytes, 6 retained bodies.
- [Use canonical Vector4 rows in apt 3d setup](apt-3d-setup-vector4-20261101-1501.md): 4 rows, 691 bytes, 4 retained bodies.
- [Use canonical Vector4 rows in current bone positions](current-bone-positions-vector4-20261101-1501.md): 4 rows, 1411 bytes, 13 retained bodies.
- [Use canonical Vector4 rows in shader sas matrices](shader-sas-matrices-vector4-20261101-1501.md): 78 rows, 11807 bytes, 337 retained bodies.
- [Use canonical Vector4 storage in screen highlight filter](screen-hilight-vector4-20261101-1501.md): 12 rows, 3200 bytes, 28 retained bodies.

Normal/frozen/EH/strict provider preparation and owning acceptance pass on each
source. Removed-definition components have no retained runtime/data incoming
edge; added emitted copies form measured components with no retained runtime
root. The debris constructor is 22B, identical to an independent original
PristineQuery copy and its existing colmathsphere native owner; it is not empty.
Its nested Vector4/iterator references are internal to the added component.
The final shader source preserves 337 retained bodies; its local pointer-based
component accessor retains the original quaternion expansion schedule.

The quadruped POD-to-constructor experiment is blocked and is not counted.
Its matched source and better historical bank remain untouched; see
[handoff](foot-vector4-pod-codegen-block-20261101-1501.md).

Final bounded preview (old index at 0d24c60eef, not a new census):

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva000C4069PristineQuery.cpp: LINKS  LINKED 731 -> 731 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 731)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDrawModule.cpp: LINKS  LINKED 569 -> 569 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 569)
Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DAptComponentView3DSetup.cpp: LINKS  LINKED 669 -> 669 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 669)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawGetCurrentBonePositions.cpp: LINKS  LINKED 1,392 -> 1,392 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 1,392)
Code/Libraries/Source/WWVegas/WW3D2/fxshadernamespacesas.cpp: LINKS  LINKED 11,703 -> 11,703 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 11,703)
Code/GameEngineDevice/Source/W3DDevice/GameClient/ScreenHilightFilter.cpp: LINKS  LINKED 3,165 -> 3,165 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 3,165)
link_check: 6 of 6 link cleanly; LINKED 18,229 -> 18,229 bytes (4.9s)
```

Immutable outgoing audit (exit 2):

```text
link batch audit: INCONCLUSIVE baseline: index at 0d24c60eef, outgoing base c691e0eefb91defcaa999782881348ad9fd6e64f; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

The audit does not prove complete current consumer/provider selection.
An older index/compiler baseline and any missing broad consumer receipt remain
explicit uncertainty, not proof of no regression. Full-image linking and runtime
remain unproved; no memory/leak/crash/FPS improvement is claimed. No baseline,
pin, alias, shared header, compiler flag or native identity was changed.
BUILD_POOL=14; memory budget about48GiB. No local inference was needed.
