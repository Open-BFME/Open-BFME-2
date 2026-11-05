# AerialPathfinder unreferenced-copy guard repair

Base: `9f8815d896`; census index: `c95fcfcfcd`, 2026-11-05 05:17.
This follows LINK-189 and the 2026-11-03 AerialPathfinder Object-view receipt.

`link_check.breaks_others` called `link_census.keep_rule` twice without the
index's reference status. Its default (`referenced=True`) charged other
objects for moving an unused, no-retail-address COMDAT before their copies.
The ordinary object preview already passes `is_referenced(index, name)`.
Passing that same fact to both comparisons makes the guard use the census's
existing unreferenced rule. Selected-body and ledger-owner checks still run.
There is no change to the census rule, index, source bytes or baselines.

Verification:

- New regression: an unused helper moved first was refused before the fix.
  The referenced and missing-graph controls retain the refusal; wrong selected
  bodies and displaced exclusive ledger owners remain refused with an empty
  reference graph.
- `python3 -m pytest -q tools/tests/test_link_check*.py
  tools/tests/test_tu_skeleton.py tools/tests/test_gate_exploits.py`:
  461 passed, 1 skipped, 86 subtests passed (15.28 seconds).
- `python3 tools/tu_skeleton.py --merge
  Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp --dry-run`:
  accepts the seed and `AerialPathfinderComputePath.cpp`, no rejected or mixed
  donors; 12 approved rows, `/MD /EHsc`, both census-linked inputs protected.
  Local receipt: `build/codex-aerial-merge-dry-run.log`.

The merge is not applied in this tooling change. Application, final byte/link
checks, register transfers and the path-consumer audit remain. No census or
real-link gain is claimed.
