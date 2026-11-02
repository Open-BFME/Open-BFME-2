# Use canonical Matrix3D storage in farm model-state transforms

Base `03347ee41668f41e8f65696847b7413f9fab084c`. Source `Code/Libraries/Source/WWVegas/WWLib/setModelStateRva000C4E23Farm.cpp`; scope claimed before editing.

The existing canonical Matrix3DData.h establishes three Vector4 rows, 48 bytes. Preserve witnessed offsets, original arithmetic/copy grouping and provider bindings; private compile and normal gates establish the scope separately.

The normal byte gate preserves 27 matched row(s), with existing
extents 22, 3553, 10, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 11, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 bytes. Actual COFF comparison
preserves 72 external code bodies and relocation lists.
Added external code definitions: ??0Matrix3D@@QAE@XZ, ??0Vector4@@QAE@XZ, ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
none.

Added emitted definitions form a component referenced only by debug data or other added definitions; no retained runtime code/data has an incoming edge. Their exact bytes and relocations are checked independently. Empty constructors are mov eax,ecx/ret; the optional22B Matrix3D constructor matches the independent original PristineQuery object including both existing Vector4/iterator relocations, and has an existing native owner at000423C5 in colmathsphere.cpp. The compiler array iterator is a measured34/48B profile. No new native row, authored-byte gain or full non-debug section equality is claimed.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/WWVegas/WWLib/setModelStateRva000C4E23Farm.cpp: LINKS  LINKED 3,581 -> 3,581 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 3,581)
  diagnostic  ??$__destroy_aux@PAVAsciiString@@@_STL@@YAXPAVAsciiString@@0ABU__false_type@0@@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
  diagnostic  ??$__destroy@PAVAsciiString@@V1@@_STL@@YAXPAVAsciiString@@00@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
link_check: 1 of 1 link cleanly; LINKED 3,581 -> 3,581 bytes (2.9s)
```

Controls: ignored `build/six-each-full-resources-20261102-1509/b2-04-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
