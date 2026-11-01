# Use canonical Matrix3D storage in locomotor orientation

Base `b99031448961992d38bf44c77e6be064d00f6b34`. Source `Code/GameEngine/Source/GameLogic/Object/LocomotorRva001E41FASetOrientation.cpp`; scope claimed before editing.

Adopt the registered storage while preserving the existing target-specific offsets, interfaces, arithmetic, copy grouping and provider bindings. No inferred identity, layout change or new native row is introduced. Translation getters and matrix-value stores remain local helpers over canonical rows; preserve the original cross products and call/evaluation order.

The normal byte gate preserves 1 matched row(s), with existing
extents 241 bytes. Actual COFF comparison
preserves 3 external code bodies and relocation lists.
Added external code definitions: ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
?Get_X_Translation@Matrix3D@@QBEMXZ, ?Get_Y_Translation@Matrix3D@@QBEMXZ, ?Get_Z_Translation@Matrix3D@@QBEMXZ, ?Set@Matrix3D@@QAEXMMMMMMMMMMMM@Z.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret; the optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations, and has an existing native owner at000423C5 in colmathsphere.cpp. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/LocomotorRva001E41FASetOrientation.cpp: LINKS  LINKED 241 -> 241 bytes (census 2026-11-01 14:31 at 86db074988; file's own bytes 241)
link_check: 1 of 1 link cleanly; LINKED 241 -> 241 bytes (2.8s)
```

Controls: ignored `build/six-each-half-resources-20261101-1634/b2-03-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.
