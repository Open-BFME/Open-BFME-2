# Saved-plan claim scope repair

The separate tooling repair loads the existing same-tree, same-input plan before
claiming. A well-formed accepted cohort claims its destination, accepted donor
files and all their ledger RVAs. Rejected candidates remain in the existing
LinkGuard input closure. Fresh byte, link, carry and final tree-state checks in
`reuse_merge_plan` are unchanged.

If reuse fails, the ordinary search must first acquire the full donor scope.
Contention there blocks the search and releases the partial acquisition,
including the previously claimed accepted cohort. Missing or malformed accepted
cohorts retain the ordinary full-scope claim. No claim bypass is introduced.

Verification on 2026-11-05:

- `python3 -m pytest tools/tests/test_tu_skeleton.py -q`: 186 passed,
  70 subtests passed. New cases reproduce rejection caused by a held rejected
  donor, retain blocking on a held accepted donor, require full claims before
  fallback search, and reject narrowing for malformed cohorts.
- `python3 -m pytest tools/tests/test_tu_skeleton_carry.py
  tools/tests/test_tu_skeleton_split.py tools/tests/test_gate_exploits.py -q`:
  156 passed, 15 subtests passed, one existing open red-team escape skipped.
- `find_declared_unmatched.py` passes for both edited Python files before and
  after the repair; `git diff --check` passes.

The game sources and ledgers have not changed. The original recorded refusal is
retained as history. Next: generate a new current-tree dry plan and retry the
normal AIPathfind merge; the old plan is deliberately invalidated by this repair.
No source-file, linked-coverage or debt reduction is claimed by the tool fix.
