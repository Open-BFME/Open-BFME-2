# AI group creation: canonical header adoption

Scope: `Code/GameEngine/Source/GameLogic/AI/AI_createGroup.cpp`, based on
`ed00a9fcf0` after rebasing onto origin/master `fbe9ceac7e`.

The private AI declaration is replaced by the registered AI header. The
existing list operation views canonical `field14` as `_STL::list<AIGroup *>`.
The header's target evidence places group-list construction/destruction at
AI+0x14; this unit's original matched body already uses that offset and element
type. No shared layout, provider name, pin or linker alias changes.

Verification:

- Before and after, `./build.sh` passes all four rows: createGroup at
  0x002FEC4B (76 bytes), push_back at 0x0005548F (26), unwind at 0x007791B7
  (10), and handler at 0x007791C1 (10). String, float and import checks pass.
- `eh_verify.py` reports one EH-bearing parent EXACT, zero baseline entries
  and zero missing objects. The renumbered unwind label resolves through its
  parent EH data; no ledger label is changed.
- `find_declared_unmatched.py`: all defined functions already matched.
- `header_adopt_lane.py accept --class AI` passes byte/adoption/link checks
  and retires exactly this source's AI queue row. Its link preview preserves
  census-linked bytes; this is not a new census or real-link measurement.
- `check_csv.py` and `git diff --check` pass.

Consolidation remains separate. The completed AI evidence planner reports
stale TU-map inputs and only hint-strength placement for this unit; the
push_back helper has a different suggested TU from its parent. No source or
row is moved. The broad merge dry run was interrupted before a final verdict,
and no accepted-donor or source-file reduction is claimed.

The outgoing batch also contains the earlier AIRingHeroTactic source move.
Immediately before publication, a case-insensitive search for the removed
Rva005AC98ACheck basename across active sources, tools, hooks, workflows,
registries and docs found only historical evidence, the provenance comment
and the measured link-status snapshot. Its existing consolidation audit
continues to describe the move; no active consumer update is needed.
