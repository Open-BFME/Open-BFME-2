## WeaponSet TU merge, 2026-11-04

Allocated shard 1/5; `consolidation_queue.py --check-tu` passed. The current
planner snapshot passed `name_lane.py consolidate --check`. `--plan` showed 54
approved rows, 17 pull donors and five mixed sources. Dry run and apply accepted
four unchanged donors (10 rows): `Rva002C7492Or.cpp`, `Rva00751B90Get.cpp`,
`WeaponSetRva002C752F.cpp`, and `Rva002C76B2Build.cpp`. The TU build passed
(10/10 matched, 2 data rows byte-verified); `find_declared_unmatched.py`
reported no unmatched definitions. LinkGuard allowed the composition and listed
the existing census-linked units it protected.

Other donors remain untouched. Compile refusals identify donor-private class
views (`AsciiString`, `Weapon`, `WeaponSet`, `GameLogic`/`Coord3D`, and
`BitFlags`), incompatible constructor signatures, flag/template mismatches, and
duplicate placement-new definitions. `WeaponSetDtor.cpp` was rejected on
bytes. These need their owning header/linking lanes; do not retry this merge
until prerequisites change. Five mixed donors were not split.

The staged identity scan reports four duplicate definitions for
`Rva002C8C06Parse` and the three `Rva002C74AB/B2/B9ByteField::get` symbols.
All four definitions are already in `WeaponSet.cpp` at HEAD before this merge;
the scan surfaced existing unregistered identity debt, not a new moved body.
Code-identity mode remains shadow and no identity key was retired. Data identity
reported zero findings; the merge carried two data-ledger rows and preserved
hatch totals. The active-path search found no references to the deleted donor
paths in tools, hooks, workflows, includes, or build configuration; historical
name evidence remains intentionally keyed to the original source paths.
