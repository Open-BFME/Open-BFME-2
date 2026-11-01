# Use canonical Vector4 rows in shader sas matrices

Base `bad582ecb06d03951da7373f187f0d6633bbf1e0`. Source `Code/Libraries/Source/WWVegas/WW3D2/fxshadernamespacesas.cpp`; scope claimed before editing.

Use existing registered Vector4 storage and preserve the former matrix arithmetic/copy grouping. Named component reads retain evaluation and alias-safe branches. Keep native parent bodies, EH lifetimes, field offsets and provider bindings unchanged; wider class reconciliation and complete consumer selection stay separate. Anonymous local derived row temporaries retain the four-float construction shape while canonical Vector4 remains the actual storage. A local component-reference helper preserves the original pointer-based quaternion expansion access; direct members otherwise changed three native/helper bodies. The final isolated object preserves all 337 retained external code bodies and relocations, with no added definition.

The normal byte gate preserves 78 matched row(s), with existing
extents 87, 87, 87, 92, 6, 11, 154, 9, 9, 9, 9, 9, 390, 126, 52, 87, 87, 27, 35, 35, 44, 47, 163, 49, 97, 105, 179, 133, 92, 159, 24, 159, 197, 218, 468, 93, 20, 44, 404, 300, 404, 674, 929, 828, 1000, 1227, 154, 160, 122, 122, 182, 71, 301, 17, 9, 9, 9, 9, 9, 23, 790, 10, 10, 10, 10, 10, 10, 10, 156, 8, 8, 8, 8, 8, 13, 13, 52, 11 bytes. Actual COFF comparison
preserves 337 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
??4Vector4@@QAEAAV0@ABV0@@Z, ??AVector4@@QAEAAMH@Z, ??AVector4@@QBEABMH@Z.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/WWVegas/WW3D2/fxshadernamespacesas.cpp: LINKS  LINKED 11,703 -> 11,703 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 11,703)
link_check: 1 of 1 link cleanly; LINKED 11,703 -> 11,703 bytes (3.8s)
```

Controls: ignored `build/six-each-half-resources-20261101-1501/b2-06-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.
