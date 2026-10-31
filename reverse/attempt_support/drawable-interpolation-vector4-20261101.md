# Adopt canonical Vector4 storage in Drawable interpolation

Base `3afc11f2b480c1bd621be1b243c286e7dd89029e`. Source `Code/GameEngine/Source/GameClient/DrawableInterpolationRebuild.cpp`; scope claimed before editing.

Use the registered Vector4 row storage. Preserve the former row assignment expression grouping through a TU-local inline component-copy helper and the existing Matrix3D assignment. All interpolation branches, cached transforms, condition flags and notification calls retain their original order. The pre-existing donor attribution and unknown concrete owner identity remain unchanged.

The normal byte gate preserves 1 matched row(s), with existing
extents 1129 bytes. Actual COFF comparison
preserves 7 external code bodies and relocation lists.
Added external code definitions: zero. Removed definitions:
??4Vector4@@QAEAAV0@ABV0@@Z.

Removed definitions have only debug incoming edges in the original object; retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameClient/DrawableInterpolationRebuild.cpp: LINKS  LINKED 1,125 -> 1,125 bytes (census 2026-10-31 22:52 at e78b61f1b2; file's own bytes 1,125)
link_check: 1 of 1 link cleanly; LINKED 1,125 -> 1,125 bytes (2.8s)
```

Controls: ignored `build/six-each-no-qwen-20261101-0015/b2-04-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.
