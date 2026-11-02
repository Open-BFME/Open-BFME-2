# Use canonical Matrix3D storage in matrix inverse widening

Base `13e6860fd1bfd2260bdcb8394c9d001afce868e2`. Source `Code/Libraries/Source/WWVegas/WWMath/Rva007133F0MatrixInverse.cpp`; scope claimed before editing.

The existing canonical Matrix3DData.h establishes three Vector4 rows, 48 bytes. Preserve witnessed offsets, original arithmetic/copy grouping and provider bindings; private compile and normal gates establish the scope separately.

The normal byte gate preserves 1 matched row(s), with existing
extents 332 bytes. Actual COFF comparison
preserves 4 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
none.

All 6 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/WWVegas/WWMath/Rva007133F0MatrixInverse.cpp: LINKS  LINKED 332 -> 332 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 332)
link_check: 1 of 1 link cleanly; LINKED 332 -> 332 bytes (2.9s)
```

Controls: ignored `build/six-each-full-resources-20261102-1509/b2-02-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
