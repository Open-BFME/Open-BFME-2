# DelayedWeaponSetUpgradeUpdate composition prerequisite (2026-10-30)

Base: `d41945e85ec30033bcfa16059a985fad478ca744`.
Scope: `Code/GameEngine/Source/GameLogic/Object/Update/DelayedWeaponSetUpgradeUpdate.cpp`
and its `DelayedWeaponSetUpgradeUpdatePoolKey.cpp` donor.

The default picker claimed both files for consolidation. The supported naming
planner (`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/`)
reported private-view, pragma-context and path-keyed-register prerequisites.
Those packets provide investigation evidence only. `tu_skeleton.py --plan`
rebuilt the stale TU map in memory and approved eight rows for the destination:
four existing rows, the pool-key method and its two compiler EH rows, and the
six-byte name getter still in the mixed `Common/ModuleNameGetters3.cpp`.
That mixed source has 116 other rows and remains outside this whole-file merge.
No regenerated TU map is committed.

The first supported merge dry run rejected the pool-key donor: the seed class
lacked `getModuleNameKey`. `tu_views.py --dry-run` separately exposed the donor's
baseless class versus the seed's UpdateModule/interface bases. The seed's
private Module flattened both canonical Module's +4 ModuleData and ObjectModule's
+8 Object pointer into two storage words. Adopt the registered Module and
ObjectModule headers, derive BehaviorModule from ObjectModule, and declare the
existing pool-key method as the slot-4 override. The headers' retail base-chain
and slot evidence is documented in the shared obstacle register. This does not
establish canonical BehaviorModule or UpdateModule interfaces; their existing
placeholder slots and aliases remain. No name is newly inferred from a donor.

## Prerequisite verification

- Before editing, `find_declared_unmatched.py` passes both files, and the ordinary
  build passes all seven rows and the pool-name string. The baseline preview
  retains LINKS for 133 seed bytes and 78 donor bytes against the 2026-10-29
  15:08 index at `85f6b7f40c`.
- The changed seed passes all four rows, totaling 133 bytes. The owning
  `header_adopt_lane.py accept --class Module` passes its byte and per-unit
  link guards and retires exactly one row from `reverse/header_queue.tsv`.
  An initial acceptance refused the transitive Module include; the source now
  includes both registered headers directly.
- Both providers pass `link_check.py --prepare-current`: seven rows, the string
  reference, and strict reusable compiler receipts. Frozen-file checks pass.
- Before/after `link_census.object_facts` comparison preserves all three strong
  definitions and the weak alias. Ten COMDATs become fifteen: the old four-byte
  Module primary table becomes the canonical forty-byte ObjectModule primary
  table, and five inline providers appear (Module onObjectCreated,
  onDrawableBoundToObject, preloadAssets, onDelete; ObjectModule onCapture).
  The constructor/destructor relocation-aware fingerprints change with the
  primary-table symbol; ordinary byte verification still passes. Undefined names
  gain the separately rowed getModuleNameKey and __purecall. No unchanged-facts
  or complete consumer-closure claim is made.

- The post-edit ordinary preview retains both LINKS verdicts and 211 authored
  bytes (133 + 78). The staged-tree batch audit exits 2, INCONCLUSIVE: its index
  predates the outgoing base and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. The new providers and their affected consumers need confirmation in
  the next scheduled census; this is not a complete consumer verdict.

This prerequisite retires one header-debt entry. No source path changes and no
census linking or image-ownership gain is claimed. The subsequent supported
merge must independently preserve all seven rows and the local-static EH graph.

## Applied whole-file composition

Prerequisite commit: `e009465d802cdfb1fd378b47e3a841d2867bbded`.
The refreshed supported planner passes `--check`; its first concurrent refresh
hit a temporary dry-run source that disappeared, so the successful refresh was
run after that dry run finished. The second merge dry run and applying
`tu_skeleton.py --merge` both accept the seed and pool-key donor, with no rejected
donors and a passing guard for both census-linked units. The applying tool claims
the moved scope, composes all seven rows, deletes the donor, and repoints three
function sources and two static-data sources. Only the three corresponding
`source` cells change in tu_map.csv; this is not a regenerated map.

Verification and debt ownership:

- The ordinary build and strict current preparation pass all seven function
  rows, the pool-name string, and the compiler funclet. The compiler label
  changes from $L310 to $L591; the exact parent EH graph still places the label
  at native 0x0078C2F3. `eh_verify.py` reports one EXACT graph, no baseline use
  and no missing object. No standalone funclet body or guessed parent is added.
- Comparing the post-header seed plus original donor to the composed object
  preserves all 17 external COMDAT names, sizes and relocation-aware digests,
  all four strong definitions and the weak alias. Of 16 unioned undefined
  names, only getModuleNameKey disappears, now resolved within the object.
  The comparison excludes local symbols; their target data references are
  checked by data_check and the byte/EH gates.
- Both static data entries (0x00A038DC key and 0x00A038E0 guard) transfer with
  unchanged names, extents and ownership status. `data_check.py` reports zero
  findings; its enforced converged pass reports no second names or unjudged
  rows. `check_csv.py` passes 99,011 functions, 9,415 symbols and 2,235 data rows.
- Neither source has code-identity, data-check or MS-header queue debt to
  transfer. The seed's Module header queue row was already retired through
  acceptance in the prerequisite. Its three existing aliases stay unchanged.
  The merger's global hatch refresh also dropped an unrelated stale BodyModule
  marker key; that incidental change was restored from HEAD, so this merge
  changes no hatch baseline.

Tooling compatibility audit, once across the outgoing source-path changes:

- Reviewed `origin/master..` the staged tree after composition, based on
  `e009465d802c` (origin reference `e75ccb7c7980`). The only path removal in the
  batch is the pool-key donor. The earlier FXParticleSystem cleanup has no path
  moves. Searched the old basename and path across tools, hooks, workflows,
  source/includes, root build/configuration files, ledgers, registries and docs.
- No active include, tool, build configuration, doxygen input, protected debt
  key or fold-proof path refers to the removed donor. All active function,
  TU-source and data-source cells now identify the existing tracked seed.
- Retained old-path mentions are historical: source composition comments,
  deleted_rows.csv's prior standalone-funclet retirement explanation, earlier
  attempt-support reports, and this handoff. The old link_status.csv row is a
  census snapshot, left for the scheduled census rather than rewritten here.
  The static's identifier contains PoolKey as a name, not a source path.
- Frozen-file checks pass after composition. No shared header or generic tool
  changes are required. Generic discovery follows current files and ledger
  owners; no old-directory special case was found. The pre-merge planner
  snapshot is evidence of the selected inputs, not a reusable post-merge plan.

The final ordinary preview reports LINKS 133 -> 211 for the destination,
whose authored bytes now include the former donor's 78 census bytes. This
preserves the combined pre-merge 211; it is not a census gain. The batch audit
against origin/master and the staged tree again exits 2, INCONCLUSIVE on the
older `85f6b7f40c` index and missing current CreateAHeroManager consumer receipt.
Full consumer confirmation remains pending; carry this composed provider and
affected consumers into the next scheduled census. Do not rewrite census
history or claim ownership improvement from this preview.

Result: one fewer source file, three more rows in their approved TU, and the
prerequisite's one retired header queue row. The mixed six-byte name getter and
the canonical BehaviorModule/UpdateModule interface prerequisites remain open.
