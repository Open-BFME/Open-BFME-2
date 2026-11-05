# ShareExperience module-data constructor consolidation

Base: 99312fe867, 2026-11-05. Owner: yasinschroeder-codex.
The separately committed declaration reconciliation lets the supported
`tu_skeleton.py --merge` absorb ShareExperienceBehaviorModuleDataCtor.cpp
into the approved ShareExperienceBehavior.cpp TU. One source file is removed.
All four donor rows move: constructor 0x0047FE90 (76 bytes), base destructor
0x0049B47C (7), cleanup 0x0078B925 (8) and EH handler 0x0078B92D (10).
TU-map edits only repoint three existing source columns; assignments are
not regenerated. The base destructor is an ICF companion, not a new TU claim.

Verification:

- Ordinary final-TU build passes 19/19 rows, two strings and four floats;
  declared-unmatched passes; eh_verify reports all four graphs EXACT.
- Comparing link_census.read_facts for the two original objects against the
  combined object preserves all 50 distinct COMDAT digest/retail verdict
  records, every strong definition and every weak alias. No alias or pin is
  removed. The supported merge's link guard accepts the composition.
- Final ordinary preview reports LINKS, 933 authored bytes (the old TU's 840
  plus the donor's 93). This is a move, not a linking or census gain.
- Data checking reports zero findings; staged TU ownership reports none;
  ledger integrity preserves 99,455 function rows, 9,322 symbol rows and
  2,268 data rows. Diff whitespace checks pass.
- The absorbed donor has no code/data identity, gate, hatch, header-queue,
  Microsoft-header or converged-data debt keys. No debt is retired. The
  merger carries path-keyed records and refreshes header queues. An explicit
  Microsoft-header refresh of both paths changes no queue rows. The existing
  Debug header item remains: its acceptance check refuses the unchanged
  private Debug view/no canonical include; this merge does not adopt Debug.
- Strict reusable receipt preparation verifies all four changed surviving
  sources of the pending batch: 146/146 function rows, three data rows and
  nine string references. The module-data factory consumer also passes its
  one row with a strict reusable receipt.

The outgoing link_batch_audit remains INCONCLUSIVE: census c95fcfcfcd
(2026-11-05 05:17) predates outgoing base 73cb536e062, and affected unchanged
consumer Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp lacks a
current receipt. Carry both pending moved TUs and provider/consumer scope
into the next scheduled census; full batch linking remains unverified.
No nightly, real-link, smoke or census run was started.

The tooling compatibility audit covers origin/master (73cb536e062) through
99312fe867 plus this staged merge. Its two removed paths are this module-data
constructor and Code/Libraries/Source/WWVegas/WWLib/Rva001EC349Dtor.cpp (already
merged into LinearCampaignManager.cpp). Searches across tools, hooks,
workflows, source/includes, build/configuration, reverse registries and docs
find no active hard-coded consumers needing updates. Function and TU-map
source columns are repointed by the merge tool. Remaining mentions are TU
provenance comments, historical link_status.csv, obstacle/attempt evidence
and an old OpaqueRefCounted proposal patch. Those historical facts stay.
Both units retain their existing compiler regions/include resolution;
no directories move and no source inclusion needs updating.

The behavior constructor remains rejected by the merge guard: its small
ShareExperienceBehaviorInterface view conflicts with the TU's twelve-slot
Rva00480093Iface20 contract, producing unresolved slot00/slot01/slot02 and
further slots in the combined vtable. Its three link-wide aliases stay in
place. Two mixed files remain outside this merge. Next: reconcile the
behavior constructor's secondary-interface contract in a separate verified
change; census confirmation of this moved scope remains pending.
