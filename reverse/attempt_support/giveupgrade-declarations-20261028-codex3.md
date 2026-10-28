# GiveUpgradeUpdate composition prerequisites, 2026-10-28

Inspected base `2eb6108a74`; ordinary-preview index `d92e7e6635`.
The scoped GameLogic consolidation planner was reviewed. It provides no
original-path proof for this name: the rows are unresolved in that planner.
The supported TU tool rebuilds the stale map in memory and approves this
grouping (29 rows, ten whole-file donors, four mixed sources). No map,
source path, ledger row, pin, baseline or class layout is changed here.

The existing SpecialAbilityUpdate view in GiveUpgradeUpdate.cpp now also
declares its already-rowed initiateIntentToDoSpecialPower and protected
onExit methods, with the existing exit wrapper as a friend. Neither method
is called virtually in these fragments. These are declaration prerequisites
for Rva0049C51AForward.cpp and Rva0049C5D9Exit.cpp, whose qualified base
calls previously could not compile against the destination view.

## Verification and boundary

- Baseline build: 10/10 rows across the three sources; edited destination:
  8/8 rows exact, all defined functions matched, both EH graphs EXACT.
- Saved before/after object facts preserve every external COMDAT digest,
  strong definition, undefined external and weak binding in all three units.
- Scoped data checking: zero findings. No affected code/data identity,
  hatch or header/MS-header queue key is added, removed or transferred.
- Ordinary same-index preview: all three sources LINKS (462, 57 and 27
  authored bytes). The destination already linked before the edit; the
  difference from its older census byte count is earlier landed work.
  No new census-linked coverage is claimed.
- Strict prepare-current verifies all ten rows and accepts three reusable
  provider receipts. An initial preparation overlapped the dry-run temporary
  source writes and correctly refused changing inputs; the sequential retry
  passed after the dry run ended.

The supported dry merge gets both helpers through compilation/byte checking
but refuses them at the link guard: a file without a census object would
place the composed unit earlier than the guard can judge. No merge was
applied. The remaining constructor, transfer, module-data constructor, slot
and object-provider fragments still need class/declaration/include/layout
reconciliation; four mixed files remain separate. A fresh normal census/index
covering the current destination is the next prerequisite for these two
helpers. Do not bypass the guard or repeat unchanged dry runs.

The staged-tree batch audit is INCONCLUSIVE: index d92e7e6635 predates the
base and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a
current receipt. Carry that consumer and this declaration/composition scope
into the next scheduled census; ordinary scoped previews and unchanged object
facts do not establish full consumer coverage.
