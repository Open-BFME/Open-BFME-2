# ClickReactionBehavior composition prerequisite, 2026-11-04

Inspected base: `97b17f4a9e`. Scope: the approved ClickReactionBehavior TU,
its constructor donor, and ClickReactionBehaviorView.h. No source path moves.

## Changes and evidence

The TU formerly declared UpdateModule privately through PB_DeepBase/PB_Iface1/
PB_Iface2. Its constructor donor already includes the canonical UpdateModule.h.
Replace the private base hierarchy with that existing header. The existing
reaction/xfer view and constructor both put two four-byte fields at +0x24/+0x28;
use the existing m_clicks/m_cooldown vocabulary in the constructor's declaration
and initializer list. No new inferred identifier or function identity is added.
No alternate-name pragma, pin, ledger row, or protected-register key is removed.

Target facts: the rowed constructor clears +0x24/+0x28, and the matched xfer
uses those offsets. Existing source declarations provide the member vocabulary;
this reconciliation does not claim recovery of retail's member spellings.
The canonical base supplies the existing module-data/object offsets +4/+8.

## Verification

- `./build.sh .../ClickReactionBehavior.cpp`: 7/7 matched, including its EH
  handler and unwind row (the compiler label changes, the parent EH graph agrees).
- `./build.sh .../ClickReactionBehaviorCtorThunk.cpp`: 3/3 matched, including
  its EH handler and unwind row.
- `find_declared_unmatched.py` passes for both sources and the shared header.
- `eh_verify.py` for both units: EXACT 2/2 parent EH graphs.
- `data_check.py` for both units: zero findings, zero outside the baseline.
- `link_check.py` for each changed unit: LINKS, preserving census-linked
  scope 600/600 and 112/112 bytes respectively (census 2026-11-04 07:28,
  measured revision a62ac1c10b). These previews are not a new census.
- No ClickReaction entries exist in header_queue.tsv, ms_header_queue.tsv,
  code_identity_baseline.tsv or data_check_baseline.txt; no debt is retired.
- Only ClickReactionBehavior.cpp includes the edited view header. No active
  tooling reference to the view header or constructor source was found under
  tools/, .githooks/ or .github/. Relative include resolution stays in the same
  directory; no path consumer changes are needed.

## Remaining merge blocker

The supported planner (`name_lane.py consolidate --under
Code/GameEngine/Source/GameLogic/Object/Behavior/`) identifies the seed and donor
as whole-file candidates; other factory sources remain unresolved/mixed and are
not moved. `tu_skeleton.py` rebuilds its stale TU map in memory. Before the edits,
the merge fails with UpdateModule redefinition; canonical-base adoption advances
it to C2614 for m_f24/m_f28; aligning those fields advances it to the link guard:

```
accepted: []
rejected: ClickReactionBehaviorCtorThunk.cpp
  unresolved ?rva004596F9@ClickReactionBehaviorIface@@UAEXXZ
  unresolved ?slot0@ClickReactionBehavior@@UAEXXZ
  unresolved ?slot0@ClickReactionBehaviorIface@@UAEXXZ
```

The donor remains census-linked, so the merge tool correctly writes nothing.
`tu_views.py --dry-run` reports no private-class reconciliation plan because the
seed declarations live in an included header. The next task is to recover the
ClickReactionBehaviorIface/leaf virtual declarations against the native table
and existing owners, then rerun the supported merge and its link guard. Do not
add aliases for the three unresolved declarations or discard existing link-wide
aliases to make composition pass. Two mixed donor files also remain outside
this merge scope. No source-file or headline linking gain is claimed.
