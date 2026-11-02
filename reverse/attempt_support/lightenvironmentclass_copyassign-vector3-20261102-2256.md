# Adopt canonical Vector3 in LightEnvironmentClass_CopyAssign

Base `d41f899c6523ea356ddc9f90779eda2a8170094c`. Source `Code/Libraries/Source/WWVegas/WW3D2/LightEnvironmentClass_CopyAssign.cpp`; scope claimed before editing.

Use the existing registered storage header and preserve native layout, ABI, retained bytes and relocation targets. Local helpers retain the original inline operation order where required.

The normal byte gate preserves 1 matched row(s), with existing
extents 437 bytes. Actual COFF comparison
preserves 1 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
??4OutputLightStruct@LightEnvironmentClass@@QAEAAU01@ABU01@@Z, ??4Vector3@@QAEAAU0@ABU0@@Z.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/WWVegas/WW3D2/LightEnvironmentClass_CopyAssign.cpp: LINKS  LINKED 435 -> 435 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 435)
link_check: 1 of 1 link cleanly; LINKED 435 -> 435 bytes (3.4s)
```

Controls: ignored `build/up-to-eighteen-each-20261102-2256/b2-05-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
