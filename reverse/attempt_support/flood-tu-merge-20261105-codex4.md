# FloodUpdate TU merge audit

Base: `bfefd7187d` (module-data reconciliation); 2026-11-05,
worker `yasinschroeder-codex4`.

`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Update/FloodUpdate.cpp`
absorbed FloodUpdateModuleDataCtor.cpp and FloodUpdateModuleDataDtor.cpp into
their approved TU. Source files decrease by two; seven existing rows move,
and the TU retains all 21 matched rows. The committed TU map changes only
those seven source-column values, preserving assignments and evidence.
No map regeneration or row deletion was committed.

Verification:

- `./build.sh` on the final TU: 21/21 exact, six renumbered funclets verified,
  one string and one float reference verified.
- `find_declared_unmatched.py`, `check_csv.py`, `git diff --check`: pass.
- `eh_verify.py` after the final object build: five exact records, no failures
  or missing objects.
- `link_check.py`: combined TU LINKS, 1,571 own bytes, against the fetched
  2026-11-05 05:17 census/index at `c95fcfcfcd`. This is a preview, not a new
  census or a claimed LINKED increase.
- The merger's current-object link guard covers all four candidate units
  already recorded as census-linked. It accepts the two donors and verifies
  retained providers, selected COMDATs and outside consumer bindings.
- `code_identity_gate.py --staged` remains shadow: one unregistered divergent
  list<int>::size definition, already reported before composition. The
  separate module-data destructor's AsciiString binding finding is absent
  from the combined TU. No identity debt is retired in this merge.
- `data_check.py --staged`: no findings. `tu_ownership.py --staged`: passes.

Debt and tooling audit:

- Neither absorbed donor owns code/data-identity, duplicate-definition,
  gate, hatch, flag-override or header-queue keys. No key is deleted or
  hand-retired. Existing Matrix3D, Thing, UpdateModule and Vector3 header
  findings remain attached to the surviving TU. The merge tool runs its
  header-source transfer and scoped Microsoft-header queue refresh; neither
  queue changes.
- Data providers at 0x00A0395C and 0x00A03960 remain owned by the destination.
  The literal FloodUpdateModuleData vtable has no path-keyed owner to move.
  No alternatename pragma is removed.
- Combined old-path/basename searches across tools, hooks, workflows,
  source/includes, shims, root build/configuration files, docs and registers
  find no active tooling or include consumer needing a change. Ledger and
  TU-map source columns follow the merger's repointing. Remaining mentions
  are provenance comments, an older attempt receipt and historical
  reverse/link_status.csv census rows; these intentionally retain old paths.
- The supported consolidation planner was regenerated after reconciliation
  and the publication rebase, before applying the merge. Its path evidence
  is advisory; the current TU map approves the seven moved addresses.

Rva0048E16CCtor.cpp and the mixed-source candidates remain untouched. The
remaining constructor reconciliation attempt and exception/inlining boundary
are recorded in [the preceding receipt](flood-moduledata-reconcile-20261105-codex4.md).
