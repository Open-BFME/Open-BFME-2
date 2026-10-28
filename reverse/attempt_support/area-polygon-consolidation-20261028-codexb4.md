# AreaPolygon reserve consolidation, 2026-10-28

Seat: yasinschroeder-codexb4. Inspected prerequisite: `460c91f9d2`.
Destination: `Code/GameEngine/Source/Common/AreaPolygonBase.cpp`.
Absorbed source: `Code/GameEngine/Source/Common/AreaPolygonBase_reserve.cpp`.

## Routing and composition

The default picker claimed the destination and eleven clean donors. The
Common-scoped name_lane consolidation report was regenerated after the
prerequisite and its snapshot check passed immediately before the supported
merge. Its AreaPolygon.cpp original-path lead is corroboration, not authority
to change the current approved destination. The TU planner rebuilt stale
assignments in memory: 39 approved rows, twelve clean inputs including the
seed, and five mixed files. The committed map changes only the reserve row's
source cell; no assignments are regenerated.

The first trial rejected every donor. Prerequisite `460c91f9d2` declares the
existing reserve method in the seed and aligns the donor's vector member
spelling with m_points. Layout and linker identities are preserved. Its
fifteen rows byte-verify, and the two objects retain identical external
definitions, undefined symbols, weak externals and COMDAT digests.

The next supported dry run and applied merge accept the seed and reserve
donor. tools/tu_skeleton.py removes one source file and repoints reserve
0x0030B96B (21 bytes), retaining all fifteen destination rows. It carries the
donor's declaration-only vector::reserve specialization into the seed so the
call still reaches the rowed 0x0030B876 provider rather than emitting a local
EH variant. No pin, generated source or class header is edited.

Ten clean donors and five mixed files remain outside this composition:

- Finish, scale, transform and deletePoint require the BfmePod8 declaration
  before their specializations and compatible AreaPolygonBase declarations.
- UpdateBounds requires the rva0030B3D1 declaration and a reconciled bounds
  view. Operator assignment needs its explicit class declaration.
- Swap defines a private vector template conflicting with the included one.
- setPoint and parse need method declarations and reconciled member views.
  parse also has a different BfmeE12 view and EH flags; verify those separately.
- PointQuery is refused by the link guard: composition would break another
  unit's copy of `??0Rva0030D111Point@@QAE@ABU0@@Z`. This matches the earlier
  consolidation-shard1-20261027 handoff. Preserve the separate donor until
  that provider/consumer identity is reconciled.

## Verification and registers

Before composition, explicit strict preparation verified the seed, reserve,
setPoint and parse: 19/19 rows and no string, float or import references.
After composition, ./build.sh and strict preparation verify 15/15 destination
rows with no string, float or import references. Frozen-file and CSV checks
pass. EH verification finds no row with EH data in this destination. TU
ownership and Microsoft-header staged checks pass. Code identity reports
15 rows and no new finding. Data identity reports none; converged enforcement
checks eleven addresses with no second name or unjudged row.

Saved original objects versus the merged object preserve the same union of
44 external definitions, thirteen external undefined symbols after removing
internally supplied definitions, zero weak externals and 44 COMDAT triples
(name, byte-and-symbolic-relocation digest, size). Thus the composition changes
neither selected copy content nor provider/dependency identities.

Neither source has a key in code_identity_baseline.tsv,
data_check_baseline.txt, header_queue.tsv, ms_header_queue.tsv or
hatch_baseline.tsv. The merger refreshes header queues; a scoped refresh
afterward returns no changes. No debt is transferred or retired, and the
hatch register has no diff. The only ledger changes are the single source
cell in functions.csv and the matching source cell in tu_map.csv. The new
ledger owner is tracked.

## Full pending-batch compatibility audit

Fetched origin/master is `d727ca6b5b`; the local pending stack forks at
`1cd9e93025`. The complete pending path-move batch absorbs five files:
AnimationSoundTree.cpp, Rva0014CE67Ctor.cpp, Thing/Rva001D9A00Finish.cpp,
U4GlobalGuardedNotifies_Rva004ca223.cpp and AreaPolygonBase_reserve.cpp,
all under Common. The first four have their earlier tracked composition
audits. Destinations remain the existing AnimationSoundClientBehavior,
AnimationAsset, INIAudioEventInfo and AreaPolygonBase TUs. No directory moves.

One combined full-path/basename search across the working source, tools,
hooks, workflows, build/configuration files, registries and documentation
finds no active consumer needing repair. Remaining old paths describe source
origin comments, census status, logs, tracked handoffs, naming provenance or
votes, and TU-map naming evidence. These historical references are preserved;
active ledger source cells resolve to current owners. The search also covered
AptOnlineHome.cpp, which appears as a deletion only in the direct comparison
against newer upstream: it is not a deletion in this pending stack. Nothing
in that upstream-only area is edited. Planner reports become stale after this
merge and must be regenerated before selecting further consolidation.

## Link evidence and limits

Index: `d92e7e6635`, 2026-10-28 15:58. The supported merger's link guard
protects all twelve census-linked clean inputs and accepts the reserve
composition. Ordinary preview reports the destination LINKS, with authored
attribution 673 -> 694 bytes. The 21 bytes move existing coverage; no census
link gain is claimed. The PolygonTrigger writer's existing provider/census
obstacle is not resolved by moving reserve.

The outgoing audit against fetched origin/master and the staged composition
is INCONCLUSIVE: the provider index predates the base, and 26 source objects
lack current receipts (first: Common/INI/INIAudioEventInfo.cpp). Full outgoing
consumer selection remains unverified. Carry this provider and affected
consumer cohort into the next scheduled census. No nightly, smoke, ownership
measurement or direct link-cycle run was started.
