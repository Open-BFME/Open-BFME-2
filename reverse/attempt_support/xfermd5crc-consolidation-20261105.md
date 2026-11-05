# XferMD5CRC consolidation, 2026-11-05

Base: `c1a5a2b848`; declaration prerequisite: `2620447df6`.
Scope: absorb `Code/GameEngine/Source/Common/Rva0052B4B6XferOpen.cpp`
into `Code/GameEngine/Source/Common/XferMD5CRC.cpp` with `tu_skeleton --merge`.
One source file removed; eight matched rows retained (298 bytes including EH).

## Evidence and checks

- The consolidation planner surveyed `Common/`. Its WorldBuilder and BFME 1
  paths remain donor hints, including conflicting `XferImpl` paths; this move
  uses the mapper's approved provisional TU, not a newly proven retail path.
  The merge tool refreshed approval in memory and changed only the moved row's
  source column in the committed TU map.
- Before repair, the open donor failed compilation because the seed's
  `XferSave` view lacked `Open`. Adding the donor's existing declaration in a
  separate commit preserved all seven seed rows and its clean link preview.
- Automatic whole-class reconciliation reverted: it would add an external
  `XferEnum` reference to the destructor donor. No such rewrite was retained.
- The merge accepted the seed and open donor, repointed the function row and
  naming basis, and retained the destructor donor. `./build.sh` reports 8/8;
  `find_declared_unmatched.py` reports all definitions matched. `eh_verify.py`
  reports one EXACT EH graph, including the renamed compiler funclet label.
- Current-object `link_check.py` reports LINKS, 280 executable bytes in the
  merged TU, against index `c95fcfcfcd`, 2026-11-05 05:17. The old seed's 207
  bytes and donor's 73 bytes were already census-linked: this is consolidation,
  not a linked-coverage gain. No census or runtime run is claimed.
- `check_csv.py`, `check_case_collisions.py`, `tu_ownership.py --staged`, and
  `git diff --cached --check` pass.
- The staged code-identity gate finds zero new findings across eight rows;
  both shadow and enforced converged data checks find zero findings.

## Path and debt audit

Audited the outgoing declaration plus this merge against fetched
`origin/master` at `c1a5a2b848`. The only removed path is the donor above.
Searches for its basename across `tools/`, hooks, workflows, `Code/`, docs and
`reverse/` found no active build/include consumer requiring a change.
Remaining mentions are provenance in the destination, historical attempts and
naming votes/agreement receipts, and the published census's `link_status.csv`;
these retain their historical meaning. Active function, TU-map source and
`name_basis.csv` references point to the destination.

Neither source has keys in the code-identity, data, hatch, header or Microsoft
header debt registers, or a flag override/data-identity/body-owner row to move.
The merge's header-source transfer and Microsoft-header refresh leave no queue
row for the donor. A fresh targeted Microsoft-header scan finds zero local
Microsoft declarations and leaves the committed queue unchanged. No debt key
is retired, no alias removed, and no hatch added.

## Remaining donor

`Rva0052B497Dtor.cpp` still fails the merge link guard on
`??_7Rva0052B497@@6B@`. The retained seed `XferSave` view introduces virtual
`XferEnum` after its destructor, whereas the external emitter in
`OpaqueScalarDeletingDtorsB12.cpp` declares only a destructor for `Rva0052B497`.
The prior attempt at the end of `reverse/re_attempts.log` identifies this same
one-slot kept copy. The next repair must reconcile that emitter/derived-class
identity and verify its consumers before absorbing the destructor. The
31-byte destructor and the mixed `VslotSmallBodiesAJ.cpp` remain untouched.
