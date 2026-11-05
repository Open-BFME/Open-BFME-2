# CivilianSpawnCollide canonical handle prerequisite

Inspected revision: `20fa09df4e`; 2026-11-05. Scope:
`Code/GameEngine/Source/GameLogic/Object/Update/CivilianSpawnCollide.cpp`
and `CivilianSpawnCollideModuleDataDtor.cpp` in that directory.

## Target facts and applied cleanup

The constructor at RVA `0x004BD651` already uses the canonical
`Rva003623E5Member` at offset `+0x08`. Its header records the retail accesses
that bound this nonvirtual handle to four bytes. The destructor at
`0x004BD72A` tears down the same member through `0x00360D26`, then restores
Snapshot's vtable. Both the former private `Rva003623E5Filter` destructor
pin and the canonical handle's destructor pin resolve to that address.

Replaced the destructor unit's private Filter declaration with the existing
canonical header and member type. No pin, alias, class header or ledger row
changed. This reconciles the member identity; it does not establish the
complete containing class's base layout.

## Verification

- Baseline `./build.sh` for both sources: 7/7 matched, including the
  constructor's native EH rows and folded ModuleDataBase cleanup.
- Edited destructor `./build.sh`: 1/1 matched, 48 bytes; string, float and
  import checks pass. `find_declared_unmatched.py`: all definitions matched.
- Combined `link_check.py`: both LINKS, 202 -> 202 LINKED preview bytes
  (154 + 48); index census 2026-11-05 05:17 at `c95fcfcfcd`.
  This is a preview, not a new census or real-link result.
- No entries for these two paths in the gate, code-identity, data-check,
  hatch, header or MS-header debt queues. No debt retired and no source paths
  moved. The seed's existing data-ledger bindings remain untouched.

## Remaining merge blocker and rejected trial

The evidence planner was regenerated with
`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/`.
Its source-group hint is not TU approval. `tu_skeleton` checks the current
approved assignment itself.

`tu_views.py .../CivilianSpawnCollide.cpp --dry-run` reports incompatible
declspecs. The seed uses a nonvirtual `ModuleDataBase` cleanup plus an explicit
vtable pointer; the destructor uses a novtable class derived from Snapshot.
The seed also carries native constructor EH ownership, which must survive a
real lifetime reconciliation. Canonicalizing the member alone does not resolve
this difference.

A bounded trial removed novtable from the destructor view. Compilation then
inserted a derived-vtable store before member teardown, increasing the body
and failing the 48-byte retail comparison. The trial was restored before the
canonical-member change; no nonmatching body remains in Code.

After the cleanup, `tu_skeleton.py --merge .../CivilianSpawnCollide.cpp
--dry-run` still accepts no donors and rejects the destructor for `bytes`.
Both sources are census-linked, so its link guard also remains in force.
The other two donors are mixed and were not edited.

Next useful work is to reconcile the primary base lifetime and the constructor's
vptr installation order while retaining its exact associative EH graph, then
verify both original units before retrying the tool-driven merge. Simply
removing novtable or unifying the handle type is insufficient. No file-count
or linked-byte gain is claimed.
