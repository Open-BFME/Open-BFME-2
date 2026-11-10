# Replay fixtures

Two frozen populations for `test_boundary_validator.py`. They are committed
rather than rebuilt in-test because both derive from inputs the fleet rewrites
every few minutes (`reverse/functions.csv`, `reverse/re_attempts.log`,
`reverse/zh_sweep/drift_report.csv`), and a measurement whose population moves
under you is not a measurement. The Ghidra inventory is pinned the same way, by
the commit named in that test.

**Pin only a SHA `origin/master` already contains.** `tools/push.py` rebases
onto `origin/master` before every push, so a SHA read from local history before
pushing is rewritten and becomes unreachable: `git fetch origin <sha>` then
answers `not our ref`, and the pin is dead for every other clone. Re-pin from
the landed commit, after the push. `INVENTORY_COMMIT` in
`test_boundary_validator.py` is currently in that state
(`2459fa69ba123a663651e181afe70ad9e5ded7c3`, not on origin), so those two tests
skip with that reason instead of failing — the inventory cannot be rebuilt from
these fixtures, because `BoundaryValidator.starts_inside()` counts the function
starts between two addresses and so needs the whole population, not the `size`
column these files carry. Re-cutting all three together is what clears it.

- `dead_ends.csv` — 2,291 `no-match` rows from `reverse/re_attempts.log` whose
  boundary could be resolved to an rva and a size (from the row's own evidence
  text, else the drift candidate it was queued from, else the ledger). Each one
  is a work slot the fleet already spent proving the address was wrong.
- `structural_queue.csv` — the 3,923 structural candidates over 1,200 addresses
  the queue served at that commit, after `drop_logged`.

To re-cut them, enumerate the same two populations and write the three columns
each file carries. Re-pin the counts asserted in `test_boundary_validator.py`
in the same commit: they are exact by design, so a moved population must show
up as a deliberate edit rather than a silently different number.
