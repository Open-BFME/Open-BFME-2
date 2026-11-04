# MeshModelReadDcg: canonical MeshModelClass adoption

Inspected revision: 94a2e5cf89. Scope: only
`Code/Libraries/Source/WWVegas/WW3D2/MeshModelReadDcg.cpp` and its
MeshModelClass header-queue row.

The private view used VertexCount at +0x28 and DefMatDesc at +0x8C;
`MeshModelClass.h` provides both through its evidenced base/derived layout.
The adoption tool initially rejected the unit with C2371: its local uint32
was unsigned int, while the shared header's multilist dependencies define
uint32 as unsigned long. Remove the local alias and preserve the field's
existing unsigned int type explicitly. No shared header changes.

Verification:

- `header_adopt_lane.py adopt --class MeshModelClass --header
  Code/Libraries/Source/WWVegas/WW3D2/MeshModelClass.h --apply <source>`: PASS.
- `./build.sh <source>`: 1/1 matched, retail RVA 0x00188BB0, 562 bytes;
  all eight compiler float literals verified.
- `find_declared_unmatched.py <source>`: passing before and after.
- `header_adopt_lane.py accept --class MeshModelClass <source>`: PASS;
  structural/byte checks and census-linked-byte preservation guard passed;
  the owning tool retired exactly one queue row. This claims no census gain.
- `check_csv.py`: PASS (99,450 function rows).

The separate DX8Wrapper queue row remains: its canonical header declares
Convert_Color out of line, while this unit's byte-matched implementation
requires local dllimport force-inline definitions with the existing x87
packing sequence. Adopting MeshModelClass does not address that dependency.
No functions, pins, aliases, hatch counts, paths or ledger extents changed.
