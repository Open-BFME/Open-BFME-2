# Use canonical Vector4 storage in screen highlight filter

Base `5de8c98c9ac981f786188dd465cafa7771cece0c`. Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/ScreenHilightFilter.cpp`; scope claimed before editing.

Use existing registered Vector4 storage and preserve the former matrix arithmetic/copy grouping. Named component reads retain evaluation and alias-safe branches. Keep native parent bodies, EH lifetimes, field offsets and provider bindings unchanged; wider class reconciliation and complete consumer selection stay separate. A TU-local component initializer preserves the original four-float constructor evaluation/store shape; the canonical layout remains the actual pixel-shader storage. All 28 retained external code bodies/relocations are unchanged. The only added empty canonical constructor has debug-only incoming edges.

The normal byte gate preserves 12 matched row(s), with existing
extents 59, 53, 1436, 961, 196, 438, 10, 15, 8, 8, 8, 8 bytes. Actual COFF comparison
preserves 28 external code bodies and relocation lists.
Added external code definitions: ??0Vector4@@QAE@XZ. Removed definitions:
none.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret; the optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations, and has an existing native owner at000423C5 in colmathsphere.cpp. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngineDevice/Source/W3DDevice/GameClient/ScreenHilightFilter.cpp: LINKS  LINKED 3,165 -> 3,165 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 3,165)
link_check: 1 of 1 link cleanly; LINKED 3,165 -> 3,165 bytes (4.1s)
```

Controls: ignored `build/six-each-half-resources-20261101-1501/b2-07-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.
