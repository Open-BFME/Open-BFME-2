# AISkirmishPlayer consolidation prerequisites and thunk recovery

Date: 2026-11-05. Seat: codexb4. Inspected base: `0f4112977e`;
destructor declaration prerequisite: `8578d8fd3e`.

The default picker claimed the main AISkirmishPlayer TU, its constructor donor
and Common destructor donor. The consolidation planner was regenerated for
`Code/GameEngine/Source/GameLogic/AI/`. `tu_skeleton.py` rebuilt current TU
assignments in memory: 41 approved rows, including the mixed ConstIntGetters4
source that must remain outside this merge. No map regeneration is committed.
The prior 2026-11-04 attempt already identified incompatible lifetime views;
this is an existing cleanup obstacle, not lost coverage.

## Kept changes

The main TU declares its virtual destructor and clearTeamsInQueue, with an
AIPlayer virtual destructor in slot zero. AIPlayer's destructor must be public,
as in the canonical AIPlayerClass.h and the existing destructor donor: a
protected declaration emits `??1AIPlayer@@MAE@XZ`, whereas the rowed public
provider is `??1AIPlayer@@UAE@XZ`. This access correction is included with the
following recovery.

At RVA 0x004EF45A the ledger already owned a five-byte generated thunk targeting
0x004F3DB1. The main TU's inline selectTeamToReinforce still carried a stale
present-unmatched marker saying its base was unrowed. Current AIPlayerTeamBuild
owns that 985-byte base method. The forwarding method is now out of line and
`add_match.py --replace-rva 0x004EF45A` replaces the scaffold row with its real
AISkirmishPlayer member. The approved TU map assigns this address to this TU.
There is exactly one ledger owner at this address. The generated source remains
untouched. `hatch_counters.py --update` removes just this present-unmatched key
(2,268 to 2,267). No gate, header, data or identity debt is retired.

## Verification and unsuccessful merge

Before edits, the three original sources passed all 40 existing rows. Final
main-TU verification passes 36/36 rows, all literal-reference checks and all six
EH graphs. The frozen-file check reports all definitions matched. CSV integrity
passes with the same 99,458 function rows. Ordinary link_check against the
2026-11-05 05:17 index at `c95fcfcfcd` checks current dependencies and reports
LINKS, 3,658 to 3,663 own bytes. The five bytes moved from an existing owner;
this is no new census coverage or runtime claim.

The destructor-only composition first failed on the protected base-destructor
relocation. With public access, the tool advances past byte verification of
the combined 38 rows, then its link guard rejects the formerly census-linked
Common donor: unresolved `?doTeamBuilding@AIPlayer@@MAEXXZ`,
`?isSkirmishAI@AIPlayer@@UAE_NXZ` and `?slot01@AIPlayer@@MAEXXZ`.
Defining the derived destructor emits its vtable and exposes the main TU's
incomplete base-slot declarations. No failed composition is kept in Code/.

The constructor composition still fails at `PlayerList::Player` after view
deduplication. Diagnostic composition additionally exposes incompatible
AISkirmishPlayer field spellings (the same names occur at different offsets).
The supported canonical AIPlayer adoption probe refuses with C1083 while
computing the header layout; it is not applied and its queue row remains.
Next work is canonical AIPlayer/Snapshot slot/provider reconciliation, then
Player include order and offset-based constructor-view reconciliation. Rerun
the merge only after those prerequisites change. This pass removes no source
file and does not claim the TU is consolidated.

## Pending-batch path audit

The outgoing batch also contains the earlier PhysicsBehaviorCtor.cpp and
PhysicsBehaviorPoolKey.cpp move into PhysicsUpdate.cpp. Combined basename and
path searches across tools, hooks, workflows and Code found no active removed
path consumer. Surviving Physics references are origin comments; generated
thunk references in exit_link.py and its test must remain because that TU still
exists. The stale main-TU skeleton comment for 0x004EF45A is removed. Searches
of data/header/MS-header/identity/gate registers found no removed Physics path
or old thunk symbol requiring transfer. The earlier Physics audit remains in
`physics-consolidation-20261105-codexb4/readme.md`. No alias is removed.

Local raw logs: `build/aiskirmish-final-build.txt`,
`build/aiskirmish-final-link.txt`, `build/aiskirmish-final-eh.txt`,
`build/aiskirmish-public-dtor-merge.txt`,
`build/aiskirmish-ctor-diagnostic.txt` and
`build/aiskirmish-outgoing-path-audit.txt`. The normal outgoing hook audits
provider and consumer bindings; inconclusive scope must be carried into the
next scheduled census, not described as verified linking coverage.
