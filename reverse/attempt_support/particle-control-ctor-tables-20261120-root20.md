# ParticleControlCtorFamily table and handle blockers

Base `08a1e0c2208`. The native build verifies all 17 function and EH rows
in `Code/GameEngine/Source/Common/System/ParticleControlCtorFamily.cpp`.
The declared-body check reports that every definition is matched. The source
and its ledger rows remain unchanged.

## Confirmed table state

Scheduled real-link run 387 lists these three bridges. The constructor objects
each emit a four-byte vftable. Retail has 14 slots in each table.

| RVA | Constructor RVA | Retail deleting destructor |
| --- | --- | --- |
| `0x00837C30` | `0x003FC58C` | `0x003FD173` |
| `0x00837DA0` | `0x003FDAAE` | `0x003FDC25` |
| `0x00837DD8` | `0x003FDBD1` | `0x003FDC25` |

The base constructor and destructor both store `0x00C37C30` at +0. The
constructor owns the `Rva003FD14DBase` view, the destructor owns
`Rva003FCE38`, and slots 8 and 12 already have `LivingWorldVisual` rows.
The [earlier fold review](livingworldvisual-table-c37c30-fold-order-20261113.md)
records the complete base slots. Current `rename.py` still requires a
different transaction for this cohort.

- `fold_evidence` rejects the third class name bound to the base table.
  `--with` cannot carry `Rva003FCE38` as an alias because it is registered
  and owns a genuine complete destructor and a deleting destructor.
- An intermediate fold into `Rva003FCE38` has a frozen alternate-name key.
  `Rva003FD14D.cpp` maps `Rva003FD14DBase::vbfunc` to the sibling deleting
  destructor. The constructor file also depends on that mapping.
  The canonical destructor view describes eight bytes, while the constructor
  requires the 0xAC-byte object. The migration needs both shared layout
  and actual lifetime providers before the alternate name can be removed.
- `--merge-existing` requires an unregistered destination with no scoped
  ledger rows. `LivingWorldVisual` is registered and has function rows.
  Its virtual `setHouseColor` provider at `0x003FB602` appears in the base
  and all three known derived tables, so it cannot establish a unique table
  through `virtual_slot_tie`.

The sibling tables differ from the base in slots 0, 3, 7, 9 and 10. Their
common deleting destructor reaches the base destructor through the five-byte
tail wrapper at `0x003FDC41`. Their distinct slot 3 providers are
`0x003FDB90` and `0x003FDCEB`. The latter has an existing `int` return
view and a tail-call alternate name to the void provider `0x003FDC46`.
The canonical base declares `void vslot03()`. Slot 7 needs reconciliation
between base `const Vector3 &`, sibling `const Coord3D &` at
`0x003FD9A3`, and sibling `const Coord3D *` at `0x003FDA19`.
The current owner-move operation preserves these signatures. Both sibling
tables use the existing `0x003FDD05` and `0x003FDD15` for slots 9 and 10.
Include `LivingWorldManagerDoomSetup.cpp` in the cohort because it also
declares both derived layouts.

## Handle adoption

A scratch candidate replaces the private `RvaSmartPtr12` with the canonical
header and the established TU-local inline destructor that tests `field00`
before calling `rva0004CBC0`. This compiles and verifies 16 of 17 rows. All
nine EH rows pass. The 311-byte constructor at `0x003FC58C` differs at two
single-byte store operands, offsets `+0x3B` and `+0x3E`. Retail and the
baseline clear object fields +0x1C, +0x24, +0x20. The canonical initializer
clears +0x1C, +0x20, +0x24. The candidate retains the constructor length
and the same relocation positions and symbols.

The shared default constructor's store order has a separate target witness
in `Particle` at `0x001F4B63`. A header-wide reorder does not resolve both
consumers. Keep the outstanding header item until a shared lifetime
representation can preserve both sequences and their exact unwind code.
