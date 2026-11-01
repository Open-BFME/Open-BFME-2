# Use canonical Matrix3D storage in drawable instance transforms

Base `c4e325f8114fbe622368a8b84174a850b6795447`. Source `Code/GameEngine/Source/GameClient/DrawableSetInstanceMatrix.cpp`; scope claimed before editing.

Adopt the registered storage while preserving the existing target-specific offsets, interfaces, arithmetic, copy grouping and provider bindings. No inferred identity, layout change or new native row is introduced. Keep the original per-row float copies and identity row initialization through TU-local helpers, since the implicit canonical matrix assignment otherwise emitted out-of-line calls. Four unused private method copies are removed as a component; complete native605B remains exact, and only the unreferenced existing compiler iterator is added.

The normal byte gate preserves 1 matched row(s), with existing
extents 605 bytes. Actual COFF comparison
preserves 1 external code bodies and relocation lists.
Added external code definitions: ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
??4Matrix3D@@QAEAAV0@ABV0@@Z, ??4Vector4@Matrix3D@@QAEAAV01@ABV01@@Z, ?Make_Identity@Matrix3D@@QAEXXZ, ?Set@Vector4@Matrix3D@@QAEXMMMM@Z.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret; the optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations, and has an existing native owner at000423C5 in colmathsphere.cpp. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameClient/DrawableSetInstanceMatrix.cpp: LINKS  LINKED 601 -> 601 bytes (census 2026-11-01 14:31 at 86db074988; file's own bytes 601)
link_check: 1 of 1 link cleanly; LINKED 601 -> 601 bytes (2.8s)
```

Controls: ignored `build/six-each-half-resources-20261101-1634/b2-04-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.
