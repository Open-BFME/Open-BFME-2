# Use canonical Vector4 rows in debris draw

Base `572afb6fabdd19076a1bba8cd101b0c14ce2e6c9`. Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDrawModule.cpp`; scope claimed before editing.

Use existing registered Vector4 storage and preserve the former matrix arithmetic/copy grouping. Named component reads retain evaluation and alias-safe branches. Keep native parent bodies, EH lifetimes, field offsets and provider bindings unchanged; wider class reconciliation and complete consumer selection stay separate. Canonical row default construction initially emitted a10B constructor call in the522B parent. An explicit local force-inline empty Matrix3D constructor restores all bytes; its emitted copy is the measured 22B constructor described below. Import-inline Scale preserves native inlining while removing its unused, otherwise changed standalone copy. Original/final incoming-edge checks exclude retained code/data roots into the removed component. Added constructor/iterator copies have no incoming edge from retained runtime code/data; nested edges remain inside that added component.

The normal byte gate preserves 3 matched row(s), with existing
extents 22, 522, 25 bytes. Actual COFF comparison
preserves 6 external code bodies and relocation lists.
Added external code definitions: ??0Matrix3D@@QAE@XZ, ??0Vector4@@QAE@XZ, ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
??4Vector4@@QAEAAV0@ABV0@@Z, ??AVector4@@QAEAAMH@Z, ?Scale@Matrix3D@@QAEXM@Z.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret; the optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations, and has an existing native owner at000423C5 in colmathsphere.cpp. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDrawModule.cpp: LINKS  LINKED 569 -> 569 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 569)
link_check: 1 of 1 link cleanly; LINKED 569 -> 569 bytes (3.3s)
```

Controls: ignored `build/six-each-half-resources-20261101-1501/b2-02-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.
