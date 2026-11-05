# W3DLightDraw module-data consolidation

Result: one fewer source file under `Code/`. The approved 107-byte constructor
at `0x000CFB3E` now lives in `Draw/W3DLightDraw.cpp`; all 12 rows in the composed
unit byte-match. This moves existing coverage and claims no census gain.

Prerequisite `65bdb8bb0e` replaced the constructor donor's explicit-vptr view
with the destination's `ModuleData`-derived declaration and declared its
constructor in the destination. The novtable base emits no additional code;
the constructor remains exactly 107 bytes. Both original units byte-matched
(12/12), had no declared unmatched bodies, and passed link previews (643
authored bytes combined). No alias or existing provider was removed by that
prerequisite.

The supported `tu_skeleton.py --merge` reused its verified dry-run composition,
absorbed only the constructor donor and repointed one function-ledger source
cell and one TU-map source cell. It rebuilt approval in memory; the committed
map change is only the source repoint. Four incompatible donors remain intact.

Verification:

- `./build.sh W3DLightDraw.cpp`: 12/12 exact, including the renumbered EH
  funclets; all four float literals and string/import checks pass.
- `find_declared_unmatched.py`: all defined functions matched.
- `check_csv.py` and staged whitespace checks pass.
- The merge's census-backed link guard passed, checking undefined symbols,
  duplicates, selected COMDAT copies, effects on other units' copies, and
  dropped providers still referenced by outside objects. The guard used the
  current composed object, not the removed donor's compiler receipt.
- `link_check.py`: LINKS, destination 537 -> 643 authored bytes against census
  `2026-11-05 15:19` / `f44cbcf5b0`. The donor already supplied the additional
  106 authored bytes in that preview's accounting; this is a preview.

Debt and tooling audit covered the outgoing range from common base
`fcb5a733c7` through `65bdb8bb0e`, plus this staged merge, after fetching
`origin/master` at `88c2f52fe3`. The two removed source paths in that batch are
`HeightDieUpdateModuleDataCtor.cpp` and
`W3DLightDrawModuleDataConstructor.cpp`. Combined searches of tooling, hooks,
workflows, includes, source/configuration consumers, active registers and
doxygen inputs found no active consumers requiring changes. Remaining mentions
are source provenance comments, historical attempt evidence and the unchanged
`reverse/link_status.csv` census snapshot. Active function and TU-map owners
resolve to the destinations.

The constructor donor has no gate, code-identity, data-check, hatch, flag,
header or MS-header debt keys. The merge's owning tools refreshed header and
MS-header queues without changes; the destination's existing five header
adoption entries remain. No debt retirement is claimed. The destination's
existing pool-key data ownership findings remain outside this change.

Remaining prerequisites: Xfer needs its base declarations; Draw, transform
and pool-key donors still conflict with the seed's field/method view. The
canonical W3DLightDraw header adoption also retains its separately recorded
snapshot-name and virtual-slot provider prerequisites. LINK-443 remains open
for these four donors.
