# Use canonical Matrix3D storage in maintain-position transforms

Base `640a2cfb086a67f392bd0cc366effafb09a5d214`. Source `Code/GameEngine/Source/GameLogic/Object/LocomotorMaintainCurrentPosition.cpp`; scope claimed before editing.

Adopt the registered storage while preserving the existing target-specific offsets, interfaces, arithmetic, copy grouping and provider bindings. No inferred identity, layout change or new native row is introduced.

The normal byte gate preserves 1 matched row(s), with existing
extents 491 bytes. Actual COFF comparison
preserves 4 external code bodies and relocation lists.
Added external code definitions: ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
none.

Compiler-local $L/$T code labels renumbered. Raw reports are preserved; only defined local code labels are compared by their unchanged external code owner and section-relative offset. No external symbol identity, code byte, relocation kind/position or data target is normalized. Normal native switch-table/byte gates remain unchanged.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret; the optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations, and has an existing native owner at000423C5 in colmathsphere.cpp. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/LocomotorMaintainCurrentPosition.cpp: LINKS  LINKED 491 -> 491 bytes (census 2026-11-01 14:31 at 86db074988; file's own bytes 491)
link_check: 1 of 1 link cleanly; LINKED 491 -> 491 bytes (2.9s)
```

Controls: ignored `build/six-each-half-resources-20261101-1634/b2-01-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.
