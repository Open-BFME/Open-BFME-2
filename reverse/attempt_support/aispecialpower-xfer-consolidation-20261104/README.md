# AISpecialPowerUpdate save/load consolidation, 2026-11-04

Base: `b2e6d2bb8e`. The default picker claimed the approved Update TU and
five donors. The original-path planner retains Object/AISpecialPower as a
WorldBuilder hint only; the current in-memory map approves the provisional
Object/Update TU. No original retail path or new TU approval is asserted.

The supported class-view reconciliation found differing base clauses and
incompatible module-data views. Its unused BehaviorModuleBase change was
restored. The bounded repair instead makes the existing TU and xfer donor
share their AISpecialPowerUpdate declaration: existing getter/update/xfer
methods, bytes +0x20/+0x21, padding, and the existing +0x24 pointer spelling.
The xfer body uses its existing slot-1 transfer view through that pointer.
This retains the seed's names; no new semantic name or pointer-product identity
is inferred. No header, flags, pin, alias, data owner or ledger identity changes.

Declaration prerequisite checks:

- Normal build: 7/7 rows exact, one string and one float reference verified.
- find_declared_unmatched: both sources pass; EH parent EXACT.
- Both sources' complete external COMDAT digests, strong definitions and
  undefined/weak/common bindings are unchanged (declarations.json).
- Ordinary link preview: both LINKS, 410 -> 410 and 153 -> 153 authored bytes,
  census/index measured at a62ac1c10b, 2026-11-04 07:28 UTC. This is a preview,
  not a new census measurement.
- tu_skeleton --merge --dry-run accepts the TU and xfer donor (7 rows).
  Other donors still fail: ctor lacks the shared constructor declaration;
  dtor needs its pointee view reconciled; post-init needs module-data fields;
  map-load needs its secondary interface reconciled. Two mixed sources remain.

The affected pair has no data/identity debt key or header-queue row on the
removed donor. Existing seed data-ledger owners remain. Remaining header debt
belongs to the surviving TU and four other donors and is not retired here.

Applied composition (parent `a9a7828552`, outgoing base `537ac50eeb`):

- tu_skeleton merged the save/load donor into the approved Update TU, removing
  one Code source. Only its source cell changed in functions.csv and tu_map.csv;
  the map was not regenerated. All seven rows remain matched (563 authored bytes).
- Normal build: 7/7 exact, string/float checks pass, EH parent EXACT;
  find_declared_unmatched passes. Enforced converged data check: 11 addresses,
  no second names or unjudged rows. check_csv passes.
- The merged object's ten external COMDAT digests, six strong definitions,
  external dependencies and weak/common bindings equal the inputs' union
  (composition.json). The supported merge link guard passes. Current-object
  preview LINKS, 410 -> 563 bytes in the destination: this is the absorbed
  153-byte row, not a linking coverage gain.
- Audited all outgoing Code path changes from the base through the staged
  merge: this is the only removal; earlier outgoing sources retain their paths.
  Full tracked-tree search for the removed basename found only the merged TU's
  provenance comment, historical attempt receipts, and reverse/link_status.csv.
  Historical evidence and census-owned status remain unchanged. No active tool,
  workflow, include, build/config or source registry consumer needs a path fix.
  No directory moved. No alias was removed. Active data/identity/hatch/header
  registers have no removed-donor key; surviving owners and debt remain. The
  merge refreshed header reports with no queue changes.

The whole outgoing link audit returned INCONCLUSIVE (exit 2): its index at
`a62ac1c10b` predates the outgoing base; six earlier changed sources lack current
receipts: Common/GeometryInfo_getMaxHeightAbovePosition.cpp,
GameClient/GUI/AptSpellStore.cpp, and GameLogic/AI/SynchronizeGroupOrder.cpp,
SynchronizeGroupOrderDtor.cpp, SynchronizeGroupOrderSlot4.cpp,
SynchronizeGroupOrderXfer.cpp (all beneath Code/GameEngine/Source/).
Carry those providers and affected consumers, the removed save/load provider,
and the surviving Update TU into the next scheduled census. The pair's object
union and preview are verified; the broader batch is not proved clean by that
inconclusive audit. No census gain is claimed.
