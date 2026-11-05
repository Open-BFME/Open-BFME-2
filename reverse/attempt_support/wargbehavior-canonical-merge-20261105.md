# WargBehavior canonical views and consolidation prerequisite

Inspected revision: a40a338ad9. Worker: yasinschroeder-codex2.

Target facts: retail constructor 0x00460804 (35 bytes) calls BehaviorModule
0x00253330, stores VA 0x00C426E8 at +0 and VA 0x00BEE9C0 at +0x0C.
The prior source substituted two TU-local integer addresses for these tables.
The primary table has 12 entries; slots 0..4 target RVAs 0x0025335A,
0x0058B03E, 0x00460827, 0x004CE56D, 0x0046082D. Slots 5..8 target
0x000B3FD0, slot 9 targets 0x0050B238, slots 10..11 target 0x000D43D0.
The 47-entry secondary table is BehaviorModuleInterface's inherited table.
No external donor path or name is inferred from these placements.

Changes: both WargBehavior views now derive from the existing canonical
BehaviorModule and declare the constructor and virtual const name-key getter.
The compiler supplies both vptr stores; the dummy integers and opaque base
are removed. No new pin, alias, vtable data row, or other hatch is admitted.
The header adoption dry run refused the old explicit m_vtable field; after
manual reconciliation, header_adopt_lane.py accept --class BehaviorModule
passed and retired the constructor's sole header_queue.tsv row.

Verification before merge:

- ./build.sh WargBehaviorCtor.cpp: 1/1 exact, 35 bytes.
- ./build.sh WargBehavior.cpp: 3/3 exact, including both EH rows; the compiler
  renumbers $L310, which the parent EH graph verifier resolves to $L1631.
- find_declared_unmatched.py on each source: all defined functions matched.
- tu_views.py --dry-run: original conflict was a missing vs present base clause.
- tu_skeleton.py --merge WargBehavior.cpp --dry-run: both files accepted,
  no rejected donor; 4 rows, 127 bytes. ConstIntGetters4.cpp stays mixed.
- link_check.py uses the fetched 2026-11-05 15:19 index at f44cbcf5b0;
  constructor preview preserves LINKS, 35 -> 35 bytes.

Remaining limitation (LINK-572): the compiler's primary WargBehavior table
still has __purecall in Snapshot slots 1, 2, 3, unlike retail's concrete
entries. The original dummy table was also unusable at runtime. Body byte
matching and a LINKS preview do not verify these slots or runtime behavior.
Recover their real overrides and the folded destructor identity before
claiming the primary table correct. The secondary table now has real inherited
getters and the correct 47-slot shape. No census or runtime progress claimed.

Planner: name_lane.py consolidate --under
Code/GameEngine/Source/GameLogic/Object/Behavior/ catalogued the input paths,
private views, quoted-include and internal-linkage review requirements, and
path-keyed data_ledger.csv ownership. Its donor-path leads were unresolved;
merge admission instead uses the current TU mapper's approved provisional TU.

## Applied merge and publication audit

Reconciliation commit: 284435195a (runner-rebased SHA). tu_skeleton --merge
accepted the seed and WargBehaviorCtor.cpp, removed the constructor donor,
and repointed its single function row, its TU-map source column, and both
path-keyed data-ledger entries. The map was not regenerated or admitted here.
Four matched rows remain in the approved provisional TU; one source file is
removed. The 0x00460827 getter remains in mixed ConstIntGetters4.cpp, and the
0x0024B443 factory remains in its displaced source; neither was moved.

Final verification:

- ./build.sh WargBehavior.cpp: 4/4 exact, 127 ledger bytes including EH.
  Parent-verified unwind label now resolves $L310 to $L1810.
- find_declared_unmatched.py: all defined functions already matched.
- check_csv.py: OK, 99,475 function rows, 9,320 symbols, 2,268 data rows.
- link_check.py: merged TU and WargBehaviorFriendNew.cpp both LINKS against
  the fetched f44cbcf5b0 index; merger's link_guard also preserved both old
  census-linked sources. The TU's preview 77 -> 112 accounts for the moved
  constructor, not new linked coverage. Factory stays 56 -> 56.
- data_check.py: zero findings; --converged: zero second names/unjudged rows.
- code_identity_gate.py --staged: 4 rows, zero new findings (shadow mode).
- tu_ownership.py --staged: success.
- Fresh Behavior-scoped consolidation report regenerated after final edits.

Audit scope: origin/master..284435195a plus this staged merge; WargBehaviorCtor.cpp
is the only source-path removal across the pending batch. Searched tools/,
.githooks/, .github/, Code/, reverse/, docs/, and root build/config files for
the donor path and basename. No active tooling, include, config, doxygen,
header-queue, ms-header, identity-baseline, data-baseline, hatch-baseline or
body-owner reference remains. There are no debt keys to retire in this merge;
the prior header queue retirement used its owning accept tool. The merger
transfers both protected data-ledger path references without changing totals.
Its cached _s_vtable/_s_secondary0C names predate canonical adoption; this path
transfer does not claim those historical symbol facts are freshly measured.

Intentional old paths: the TU's generated provenance comment; historical
reverse/link_status.csv census measurement; prior attempt handoff and
reverse/re_attempts.log records; dummy-vptr-ctors-20261105.tsv investigation
snapshot. These are evidence, not active build path consumers. No provider was
removed without a replacement: the constructor's exact definition now resides
in the approved destination. The link preview verifies the factory consumer.
No matching coverage, census headline, image ownership or runtime gain claimed.
