# AnimationSound module-data composition, 2026-10-30

Seat: yasinschroeder-codexb. Inspected base: `de459f73ab`.
Approved destination:
`Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`.

## Routing and declaration prerequisite

The default picker claimed the destination and eight whole-file donors. The
scoped `name_lane.py consolidate` packet was reviewed, including original-path
leads, alternatives, and blockers. Its BFME1 Behavior path is donor evidence,
not permission to change the current Update destination. The supported merger
rebuilds the stale committed TU map in memory: 49 rows are approved for this
TU; seven mixed files remain untouched. No map assignments are regenerated.

The initial supported probe rejects all eight donors. The module-data fragment
has only a constructor-facing class, whereas the seed has only its static
parser declaration. Reconcile these existing declarations and the tree view
before composition. The module-data object remains 0x18 bytes: virtual base
storage occupies +0..7, the existing 12-byte seed tree occupies +8..0x13, and
the float remains at +0x14. The donor's old separate +0x10 word becomes the
last four bytes of the tree. Field identities beyond the seed's existing view
are structural inferences, not recovered donor layout facts.

Both sources now share the tree declaration and the module-data declaration;
the seed learns the existing tree destructor and module-data base/constructor/
destructor declarations, and the donor learns the existing tree methods and
static parser declaration. No body, symbol binding, pin or escape hatch is
added. The tree initializer declaration loses `throw()` to agree with its
matched provider in Common/AnimationSoundTreeFree.cpp (0x004CA13D).

The intermediate composed object demonstrated the reason: its module-data
constructor was 34 bytes with no EH prologue, versus the retail/standalone
63-byte constructor with EH data. Seeing the tree constructor's body together
with its `throw()` initializer declaration lets the compiler omit cleanup.
The standalone objects remain identical in their link facts when that
unsupported no-throw guarantee is removed. This is declaration reconciliation,
not permission to change the provider or claim a donor source identity.

`./build.sh` verifies 21/21 rows across the two sources, ten string literals
plus one empty-string reference, one floating literal and one named import.
Both sources pass the frozen-file check. `eh_verify.py` reports all three EH
graphs EXACT. Before/after object comparisons preserve each source's external
COMDAT bytes and symbolic relocation fingerprints, external definitions,
unresolved names, weak aliases and full reference roots/edges: seed 45 COMDATs,
45 definitions, 44 unresolved names and two weak aliases; donor seven COMDATs,
seven definitions, eight unresolved names and two weak aliases.

The first strict receipt attempt overlapped a merge trial's temporary sources
and was rejected because its preparation inputs moved; no witness was accepted.
The subsequent check succeeds after those trials finish: both explicit providers
are byte-verified with strict reusable receipts; census/index/status are unchanged.

The ordinary preview against census index `12b9e7a7c0` (2026-10-30 10:11)
preserves LINKS for both sources: 1,958 seed bytes plus 73 constructor/EH
bytes, 2,031 authored bytes total. These are predictions, not new census figures.

## Supported composition and verification

The prerequisite was handed to the runner as `50c85187a0` and is now
`e63a29b45b` after its publication transport rebased the pending bundle. The
scoped naming packet was regenerated after declaration changes and its
freshness check passed before applying the supported merge.

`tu_skeleton.py --merge` accepts the seed and the module-data constructor
fragment, removes one net source file, and repoints exactly two function-ledger
source cells and two TU-map source cells. The merger's score is 19; normal
verification covers all 21 rows including EH rows. Seven whole-file donors
still fail for the manager/client declarations, entry layouts, declaration
ordering and duplicate STL nodes. All seven mixed sources remain separate.
The census-linked-input guard accepts the actual composed object.

The final `./build.sh` verifies 21/21 rows and the same strings, float and
import references. All three EH graphs are EXACT, the frozen-file check passes,
and strict preparation accepts the final source with a reusable receipt.
Comparing the original two-object union with the composed object preserves
all 52 external COMDAT byte-and-symbolic-relocation fingerprints, 52 external
definitions, 46 unresolved names, four weak aliases and the complete relocation
reference roots/edges (60 roots, 43 edge owners). There is no lost provider or
changed symbolic binding in these object facts.

## Registers and tooling audit

The constructor donor has no code/data identity, header-adoption,
Microsoft-header or flag-override debt entries. Its existing base-destructor
alternatename moves to the destination through the supported merger and
`hatch_counters.py --update`; no hatch is added. The global refresh also drops
one pre-existing stale present-unmatched key for
`Common/RTS/Rva0073DFD0Finish.cpp`: the element was already respelled in
`7ed98efdf8`, and the registered old marker is absent. This is housekeeping
found by the owner tool, not source recovery credited to this merge.

The merger transfers header-queue ownership and refreshes the scoped
Microsoft-header report; repeating the scoped refresh yields no changes.
Staged TU ownership, Microsoft-header and hatch checks pass. Data identity
reports zero findings; converged enforcement checks eleven addresses with no
second names or unjudged rows. `check_csv.py` passes.

The tooling audit includes the complete pending publication bundle relative
to origin/master, not only this move: INIMultiplayerSettings.cpp,
BezierProjectileBehaviorPoolKey.cpp, StlSweepR3Rva001FDEBC.cpp and this
module-data fragment. Combined full-path/basename searches cover tools, hooks,
workflows, Code, shim headers, root build/configuration files, documentation
and reverse registers. No active consumer needs an update. Remaining mentions
are source-origin banners and historical caller comments, attempt evidence,
re-attempt/deleted-row records, completed obstacle history and the published
link-status snapshot. Active source-ledger and TU-map cells name current files.
No directories or discovery patterns change.

The merged ordinary preview LINKS for 2,031 authored bytes against index
`12b9e7a7c0`, equal to the original input sum. The apparent 73-byte seed gain
is moved ownership; no new census LINKED gain is claimed.

The whole pending bundle audit uses staged tree
`29d4fc128c57edc041753683b64742a3e6595341` against origin/master
`3412e13e5f`. It first reports two stale source receipts. Refreshing all six
explicit changed sources succeeds: 198/198 rows, one data row, 139 strings plus
five empty-string references, 95 floating literals and 25 named imports. The
repeated audit is INCONCLUSIVE: its index predates the outgoing base, and
affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a current receipt.
This is incomplete consumer-selection evidence, not a clean outgoing audit.
Carry the composed unit, removed provider and affected consumers into the next
scheduled census. No direct census, nightly or smoke runner was started.
