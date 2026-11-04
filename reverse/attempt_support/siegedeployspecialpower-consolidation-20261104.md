# SiegeDeploySpecialPower transfer consolidation, 2026-11-04

Scope: `Code/GameEngine/Source/GameLogic/Object/SpecialPower/`.
Reconciliation commit: `4ed340f35a`. The subsequent merge absorbs only
`SiegeDeploySpecialPowerXfer.cpp` into `SiegeDeploySpecialPower.cpp` through
`tools/tu_skeleton.py --merge`; source files decrease by one. No new row,
name pin, alias, hatch or debt retirement is claimed.

## Evidence and verification

- The refreshed `name_lane.py consolidate --under` snapshot supplied original-path
  evidence; the merge tool rebuilt the TU assignments in memory and accepted
  the transfer row at 0x004C5B39 in its approved TU. The committed TU-map change
  only repoints that row's source column; assignments are not regenerated.
- Standalone reconciliation: `./build.sh` verified the original destination
  and transfer donor (20 code rows and one data row). Both objects previewed
  `LINKS`, retaining 1,666 authored bytes in total.
- Applied merge: the saved plan reverified 20 code rows. Its LinkGuard checked
  the census-linked cohort and accepted the composed object with the donor
  removed. The census index is 2026-11-04 17:56, commit `8c757ea0db`.
- Final `./build.sh SiegeDeploySpecialPower.cpp`: 20/20 code rows, one data
  row, two strings, three compiler float literals and five renumbered funclet
  pins verified. `find_declared_unmatched.py`: all definitions matched.
- Final `link_check.py SiegeDeploySpecialPower.cpp`: `LINKS`, 1,666 authored
  bytes. This is a preview, not a new census or real-link measurement.
- `check_csv.py`, staged TU ownership, staged whitespace checks, and converged
  `data_check.py` pass (11 addresses, zero second names or unjudged rows).
- Shadow checks retain the pre-merge findings: duplicate
  `?get@Rva004C5772CmpBoolField@@QBE_NXZ` and two compiler-renumbered local
  guard names in the destination. No register entries are removed or added.

## Path and ownership audit

Audited `origin/master` (`21e82ce2f3`) through reconciliation `4ed340f35a`
plus the staged merge. The only removed path is the transfer donor above.
The ledger and TU-map source column now identify the destination; no approved
TU assignment changes. Neither the donor nor destination has registered data
or identity debt requiring transfer. The destination retains its data rows
and data-ledger ownership.

The merge tool refreshed header and Microsoft-header queues, with no changes.
The destination's existing `Rva00045411BitSet` header-queue entry remains;
the unmerged update donor's `Thing` entry also remains. The destructor donor's
four link-wide alternatename hatches are untouched.

A repository-wide search for `SiegeDeploySpecialPowerXfer`, including tools,
hooks, workflows, includes, build/configuration files, documentation and source
registers, found no remaining active path consumer. Remaining references are
the census snapshot `reverse/link_status.csv`, three historical attempt-support
files (fireweapon primary/update cohorts and SiegeDeploy QC12 providers), and
the merge provenance comment. They intentionally retain the old path. No
tooling compatibility edit is needed.

The transfer's complete function retains the already clear `xfer` and
`version` scoped names. Unknown member roles are not inferred from a byte match.

## Remaining composition prerequisites

The final dry run rejected the other four donors without changing them:

- Constructor: conflicting fake-base view; the composed class lacks the
  constructor donor's `WeaponModeSpecialPowerUpdateBase` definition.
- Destructor: composed bytes differ; its private base/vtable views still need
  reconciliation. Preserve its link-wide alternatename providers.
- Update: the composed `Object::findModule` access differs from its private
  view (`C2248`).
- Approach-point computation: its private typed `m_moduleData` cannot be used
  through the destination's `ModuleData` declaration (`C2027`/`C2227`).
  A scratch-only cast to `SiegeDeployModuleDataView` preserved all three donor
  rows in isolation, but the destination's `throw()` declaration then removed
  the computation's EH shape (681 versus 706 bytes). Removing `throw()` matched
  those three rows but changed `initiateIntentToDoSpecialPower`'s stack/EH shape
  at 0x004C6133 and its funclets at 0x00790176/0x00790183. Neither variant was
  retained in `Code/`. Reconcile this shared code-generation constraint before
  retrying a wider merge; simple field casts alone do not solve it.

The mixed `ConstIntGetters4.cpp` donor is also unmerged. No new SiegeDeploy
linking obstacle was found: both pre-merge objects and the composed TU preview
cleanly, while the existing broader `Rva00589079` obstacle entries remain
unchanged by this transfer composition.
