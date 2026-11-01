# Use canonical Matrix3D storage in movement angle transforms

Base `57a0d1bc68b123f9e88900a5733c4e8312b705b6`. Source `Code/GameEngine/Source/GameLogic/Object/LocomotorMoveTowardsAngle.cpp`; scope claimed before editing.

Adopt the registered storage while preserving the existing target-specific offsets, interfaces, arithmetic, copy grouping and provider bindings. No inferred identity, layout change or new native row is introduced. Keep the original twelve-word bit-copy and its barrier after the fifth store through a TU-local helper over canonical storage; the complete native parent stays exact.

The normal byte gate preserves 1 matched row(s), with existing
extents 475 bytes. Actual COFF comparison
preserves 1 external code bodies and relocation lists.
Added external code definitions: ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
?set@Matrix3D@@QAEXABV1@@Z.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret; the optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations, and has an existing native owner at000423C5 in colmathsphere.cpp. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/LocomotorMoveTowardsAngle.cpp: LINKS  LINKED 475 -> 475 bytes (census 2026-11-01 14:31 at 86db074988; file's own bytes 475)
link_check: 1 of 1 link cleanly; LINKED 475 -> 475 bytes (2.8s)
```

Controls: ignored `build/six-each-half-resources-20261101-1634/b2-02-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.
