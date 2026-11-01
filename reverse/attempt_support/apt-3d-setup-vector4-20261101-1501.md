# Use canonical Vector4 rows in apt 3d setup

Base `7eef47e04c476f089a2323da309a4ee96738dd27`. Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DAptComponentView3DSetup.cpp`; scope claimed before editing.

Use existing registered Vector4 storage and preserve the former matrix arithmetic/copy grouping. Named component reads retain evaluation and alias-safe branches. Keep native parent bodies, EH lifetimes, field offsets and provider bindings unchanged; wider class reconciliation and complete consumer selection stay separate. Measured import-inline profiles for Matrix3D(bool), Rotate_Y and Rotate_Z preserve all four native rows while dropping unused standalone copies. The only added array-iterator copy has no retained runtime incoming edge.

The normal byte gate preserves 4 matched row(s), with existing
extents 661, 10, 10, 10 bytes. Actual COFF comparison
preserves 4 external code bodies and relocation lists.
Added external code definitions: ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
??0Matrix3D@@QAE@_N@Z, ??AVector4@@QAEAAMH@Z, ?Make_Identity@Matrix3D@@QAEXXZ, ?Rotate_Y@Matrix3D@@QAEXM@Z, ?Rotate_Z@Matrix3D@@QAEXM@Z, ?Set@Vector4@@QAEXMMMM@Z, _cosf, _sinf.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret; the optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations, and has an existing native owner at000423C5 in colmathsphere.cpp. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DAptComponentView3DSetup.cpp: LINKS  LINKED 669 -> 669 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 669)
link_check: 1 of 1 link cleanly; LINKED 669 -> 669 bytes (3.4s)
```

Controls: ignored `build/six-each-half-resources-20261101-1501/b2-03-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.
