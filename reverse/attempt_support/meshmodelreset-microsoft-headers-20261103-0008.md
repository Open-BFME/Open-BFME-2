# Remove redundant scalar-delete declaration in MeshModelReset

Source: Code/Libraries/Source/WWVegas/WW3D2/MeshModelReset.cpp.

Remove the redundant file-local declaration and retain its existing included header provider. Unlike the nonthrowing array-delete family, this declaration has the same unspecialized scalar-delete contract already supplied by existing always.h. Remove only the duplicate. No header, macro, compiler or linker option changes. Every native/EH body and complete non-debug section must remain exact; the native scoped Microsoft audit owns file-key retirement.

Normal/frozen/EH and strict provider checks pass. All 3 existing native/EH rows, 4 retained external code bodies/relocations and all non-debug sections remain exact. The owning scoped Microsoft-header scan retires 1 queue record(s), preserving unrelated records. No shared header, native pin, alias, baseline, optimization or ABI switch changes. Declaration cleanup or queue maintenance is not new native coverage or runtime improvement.

Bounded dated preview:

Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/WWVegas/WW3D2/MeshModelReset.cpp: LINKS  LINKED 214 -> 214 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 214)
link_check: 1 of 1 link cleanly; LINKED 214 -> 214 bytes (2.7s)
