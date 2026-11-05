# DemoTrapUpdate creation callback consolidation

Base: `008153cd55` (the separately verified declaration prerequisite).
The supported merge absorbs Common/DemoTrapUpdate_onObjectCreated.cpp into
GameLogic/Object/Update/DemoTrapUpdate.cpp, removing one source file and
preserving all 12 code rows. Only the callback's source cell changes in the
function ledger and TU map; TU approval/evidence is unchanged.

The original dry run rejected duplicate Thing/Object definitions. The
prerequisite uses the seed's canonical UpdateModule hierarchy, existing local
Object prefix and existing module-data prefix. The callback still reads module
data at +4 and Object at +8, selects data+0x28/+0x30 using data+0x3C, and calls
the same two Object methods. No function, global or member name is newly
claimed as recovered.

## Verification

- Before composition, normal build: 12/12 rows exact across both sources.
  Ordinary link prediction: both LINKS, 44 + 686 = 730 authored bytes.
- After composition, normal build and strict reusable-receipt preparation:
  12/12 exact, two string references verified, declaration checks clean.
  Both EH graphs are EXACT; renumbered unwind labels retain parent placement.
  Ordinary prediction: merged TU LINKS, 730 authored bytes, against census
  `c95fcfcfcd` (2026-11-05 05:17). This preserves the combined coverage;
  the displayed per-file 686 -> 730 is movement, not new census coverage.
- Shadow code identity: 12 rows, zero new findings. Shadow data: zero findings.
  TU ownership shadow check and CSV integrity pass (99,456 function rows).
- `header_adopt_lane.py accept --class UpdateModule` passes for the final TU
  and retires exactly its one stale header-queue row. No manual retirement.
  The merge's scoped Microsoft-header refresh changes no queue row. Neither
  donor nor destination has data/identity/flag/hatch debt to transfer. Data
  owners and weak aliases are unchanged.
- Compared the census seed/donor COMDAT union with the final object: all 68
  retained definitions have identical byte/relocation fingerprints, none are
  added or changed. The one removed array-construction helper
  `??_H@YGXPAXIHP6EPAX0@Z@Z` has 1,801 other equal-digest census providers.

## Complete pending path audit

Audited origin/master `96e9022227` through the staged merge tree, including
the pending AutoHealBehaviorPoolKey.cpp and ProductionQueueHordeContainXfer.cpp
absorptions. Searched the three old basenames/paths across tools, hooks,
workflows, source/header includes, root configuration, docs, reverse registers
and reference shims. No active include, build list or tool consumer needs an
update. The merge repoints the callback's ledger/TU-map source and four
name-basis source cells. Doxygen has no callback entry. Remaining mentions are
source provenance comments, historical naming votes/agreements, deleted-row
explanations, attempts and the last census status; those remain history.
The consolidation planner was regenerated after source changes and its
currency check passes. Whitespace checks pass.

The complete three-destination batch audit is INCONCLUSIVE: its census index
predates the outgoing base, and affected consumer
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. This is the
existing LINK-004 prerequisite, unchanged by this merge; carry the full
provider/consumer scope into the next scheduled census. No full-batch
clearance, real game link or new census gain is claimed.

Remaining source recovery: the destructor and field parser remain in mixed
Rva0024A797Derived.cpp and ModuleDataBuildFieldParse.cpp. Reconcile/split those
through the supported tools before another merge; this pass does not move
their rows or resolve their other owners.
