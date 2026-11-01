# Use canonical Matrix3D storage in siege containment transfer

Base `0eff6e75d6f60ca6cc4ee561e22cc0db37bbcdb3`. Source `Code/GameEngine/Source/GameLogic/Object/Contain/SiegeEngineContainXfer.cpp`; scope claimed before editing.

Adopt the existing registered storage and retain the witnessed target interfaces, field offsets, arithmetic/copy grouping and provider bindings. No new native identity or behavior is inferred.

The normal byte gate preserves 6 matched row(s), with existing
extents 464, 1077, 10, 8, 8, 13 bytes. Actual COFF comparison
preserves 104 external code bodies and relocation lists.
Added external code definitions: ??0Matrix3D@@QAE@XZ, ??0Vector4@@QAE@XZ, ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
none.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret; the optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations, and has an existing native owner at000423C5 in colmathsphere.cpp. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/Contain/SiegeEngineContainXfer.cpp: LINKS  LINKED 1,542 -> 1,542 bytes (census 2026-11-01 20:19 at 0156fc269e; file's own bytes 1,542)
  diagnostic  ?_M_clear@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@IAEXXZ  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
link_check: 1 of 1 link cleanly; LINKED 1,542 -> 1,542 bytes (3.5s)
```

Controls: ignored `build/six-each-half-resources-20261101-2150/b2-04-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget47GiB, no Unreal process changed.
