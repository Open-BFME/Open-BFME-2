# HorseHordeContain name-key donor

Inspected input: `384350437864ebc5130387af5f2ccb3f9a40b3d3`.

The approved provisional TU is
`Code/GameEngine/Source/GameLogic/Object/Contain/HorseHordeContain.cpp`.
The scoped consolidation planner reports separate mixed/incomplete and declaration
prerequisites; it does not approve a move. The current-map merge planner independently
selects the name-key donor and its two compiler-generated EH rows for this TU.

Target evidence: retail primary table VA `0x00C45C38` has slot 4 VA
`0x008766E8`, the existing 69-byte `HorseHordeContain::getModuleNameKey() const`
row. Base table VA `0x00C45050` has a different getter in the same slot
(VA `0x0086F860`). The root primary view already reserves this slot as `s04`.
Replacing that unused declaration with the getter signature and declaring the
derived override preserves all later slots and the existing ledger identities.
No external donor facts are needed and no real source-path recovery is claimed.

Before reconciliation, `tu_skeleton --merge --dry-run` accepts no donor: the
name-key definition is absent from the seed class. After reconciliation it accepts
the seed and `HorseHordeContainPoolKey.cpp`, six rows together. The other five
donors still fail on their distinct private base, member or include declarations.

Verification of the declaration repair:

- `./build.sh .../HorseHordeContain.cpp`: 3/3 exact, string/float/import checks pass.
- `find_declared_unmatched.py`: all defined functions already matched.
- `link_check.py`: LINKS, 1,402 -> 1,402 bytes against census `5a13f2cd61`
  (2026-11-04 02:25); prediction only, no census gain claimed.

Next: commit this verified prerequisite separately, then apply the accepted
composition through `tu_skeleton.py`, verify its EH graph and path consumers,
and retain all remaining donors and their debt.

## Applied composition and audit

Prerequisite commit: `7e3e2f768e`. `tu_skeleton.py --merge` then accepted only
the seed and name-key donor, removed the donor, and repointed its three code
rows and two data owners. SOURCE FILES decreases by one. The map change is
three source-column repoints, with no regenerated assignments or approvals.

- Normal build: 6/6 exact, including the compiler-renumbered unwind label
  (`$L310` -> `$L4601`, proven by the parent's EH graph).
- EH verifier: one EXACT graph, no baseline findings or missing objects.
- Declared-unmatched check: all defined functions already matched.
- Current-object preview: merged TU LINKS, 1,481 bytes; this incorporates the
  donor's already-covered rows, so no linking gain is claimed.
- The merge's link guard protects all seven census-linked input units; five
  rejected donors retain their original source, bodies and provider bindings.
- No source is keyed to the removed donor in code/data identity debt, header
  queues, flag overrides or the hatch register. Two `data_ledger.csv` keys are
  transferred, without retirement. Existing seed header debt remains queued.
- Path-consumer audit over the pending batch: no active tool, hook, workflow,
  source include or configuration names the donor. Ledger/map/data ownership
  repoints are complete. The remaining source mention is provenance in the
  merged TU. Historical attempt notes, `deleted_rows.csv` prose and the last
  census's `link_status.csv` deliberately retain the former path.

The outgoing hook/fleet publisher still owns the batch consumer audit and the
next scheduled census owns headline confirmation. The remaining constructor,
destructor, transfer and movement declaration conflicts are unchanged.
