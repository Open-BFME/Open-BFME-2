# Use canonical Matrix3D storage in drawable transform cache

Base `0fb5149c2c6712eacccc60661d4c98f0444e3321`. Source `Code/GameEngine/Source/Common/Rva000E459F.cpp`; scope claimed before editing.

Adopt the registered storage while preserving the existing target-specific offsets, interfaces, arithmetic, copy grouping and provider bindings. No inferred identity, layout change or new native row is introduced. A TU-local component-reference accessor retains the dynamic row/column float access; the existing explicit twelve-integer copy, comparison and state updates remain intact. Both native bodies and all three retained external code/relocation definitions are exact.

The normal byte gate preserves 2 matched row(s), with existing
extents 315, 101 bytes. Actual COFF comparison
preserves 3 external code bodies and relocation lists.
Added external code definitions: ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
none.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret; the optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations, and has an existing native owner at000423C5 in colmathsphere.cpp. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/Rva000E459F.cpp: LINKS  LINKED 416 -> 416 bytes (census 2026-11-01 14:31 at 86db074988; file's own bytes 416)
link_check: 1 of 1 link cleanly; LINKED 416 -> 416 bytes (2.8s)
```

Controls: ignored `build/six-each-half-resources-20261101-1634/b2-06-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.
