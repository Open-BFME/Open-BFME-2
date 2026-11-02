# Use canonical Matrix3D storage in matrix comparisons

Base `0806fba4f8e357fa6932c19cc1dc888517f87c47`. Source `Code/Libraries/Source/WWVegas/WWMath/matrix3d_equal.cpp`; scope claimed before editing.

The existing canonical Matrix3DData.h establishes three Vector4 rows, 48 bytes. Preserve witnessed offsets, original arithmetic/copy grouping and provider bindings; private compile and normal gates establish the scope separately.

The normal byte gate preserves 2 matched row(s), with existing
extents 61, 70 bytes. Actual COFF comparison
preserves 2 external code bodies and relocation lists.
Added external code definitions: ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
??AMatrix3D@@QBEABVVector4@@H@Z.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret; the optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations, and has an existing native owner at000423C5 in colmathsphere.cpp. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/WWVegas/WWMath/matrix3d_equal.cpp: LINKS  LINKED 131 -> 131 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 131)
link_check: 1 of 1 link cleanly; LINKED 131 -> 131 bytes (2.8s)
```

Controls: ignored `build/six-each-full-resources-20261102-1509/b2-06-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
