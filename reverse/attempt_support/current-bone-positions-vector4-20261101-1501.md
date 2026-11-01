# Use canonical Vector4 rows in current bone positions

Base `5ebf1c8c5363219148c803deb7b7d92e0b49ac03`. Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawGetCurrentBonePositions.cpp`; scope claimed before editing.

Use existing registered Vector4 storage and preserve the former matrix arithmetic/copy grouping. Named component reads retain evaluation and alias-safe branches. Keep native parent bodies, EH lifetimes, field offsets and provider bindings unchanged; wider class reconciliation and complete consumer selection stay separate.

The normal byte gate preserves 4 matched row(s), with existing
extents 1145, 10, 243, 13 bytes. Actual COFF comparison
preserves 13 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
??4Vector4@@QAEAAV0@ABV0@@Z.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawGetCurrentBonePositions.cpp: LINKS  LINKED 1,392 -> 1,392 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 1,392)
link_check: 1 of 1 link cleanly; LINKED 1,392 -> 1,392 bytes (3.5s)
```

Controls: ignored `build/six-each-half-resources-20261101-1501/b2-04-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.
