# EmotionTrackerUpdate consolidation, 2026-10-29

Base: `6825bf755c`. The default claimed picker selected the existing
`Code/GameEngine/Source/GameLogic/Object/Update/EmotionTrackerUpdate.cpp` TU
and ten donor files. The supported consolidation planner was run under
`Code/GameEngine/Source/` to include the Common satellites. Its current
assignment is provisional; donor path agreement is not proof of an original
BFME 2 source path or complete class layout. The merger rebuilds stale TU
assignments in memory rather than regenerating the committed map.

## Declaration prerequisites

The seed lacks declarations for the already matched nugget deactivation and
name-key getter. Declare those methods and use the seed's existing
EmotionNugget view in Rva004B0E9CClear.cpp. The clear helper still accesses the
same opaque entry field at +0x4c through its existing local view; this does not
recover an EmotionEntry layout or rename the helper. No canonical class is
copied and no pin or hatch is added.

Both revised sources pass `./build.sh`: 15/15 rows, including the six seed
funclets whose assembler labels were renumbered. Saved pre-edit objects and
current verified objects have identical COMDAT byte/relocation fingerprints,
strong definitions, undefined externals and weak aliases, compared through
`link_census.object_facts` with identity verdicts excluded. Both sources pass
`find_declared_unmatched.py`. Baseline strict preparation also passed the
separate name-key source's three rows and one string literal. Initial link
previews against index `85f6b7f40c` (2026-10-29 15:08) report all three units
LINKS: 933 + 32 + 79 authored bytes. This is preview evidence, not a census
change. The constructor and broader derived-interface reconciliation remain
outside this bounded declaration change.

## Applied merge

After the prerequisite commit was handed to the runner, publication rebased
the batch onto `e584f58929`. The supported planner was refreshed, and
`tu_skeleton.py --merge` absorbed Rva004B0E9CClear.cpp and
EmotionTrackerUpdatePoolKey.cpp into the existing EmotionTrackerUpdate TU.
Four function-row source columns move: 0x004B0E9C (32 bytes), 0x004B1393 (69),
0x0078E887 (13), and 0x0078E894 (10). The destination owns 18 matched rows;
source files decrease by two. The merger transfers both function-static data
owners at 0x00A03D8C and 0x00A03D90 without changing their names. The committed
TU map changes source columns only, not assignments or approval evidence.

`./build.sh` and strict `link_check.py --prepare-current` pass 18/18 rows and
the name-key string literal. EH verification is EXACT 2/2 and the frozen-file
check is clean. `tu_ownership.py --staged` passes. Code identity reports no new
finding across 18 rows; staged data identity reports zero findings. Converged
data verification checks all 11 addresses with no second names or unjudged
rows. `check_csv.py` passes with 99,005 function rows after the upstream rebase.

The verified final object retains exactly the union of the three saved
pre-edit objects: 28 COMDAT byte/relocation fingerprints, nine strong
definitions, 24 undefined externals, and no weak aliases. Undefined references
are compared after removing definitions supplied by the combined inputs.
The merger preserves the seed's compiler definitions and include paths. Its
queue refresh leaves no moved-source entries in the header or MS-header
queues; the separate constructor's Thing queue and destructor's hatch stay
with their unchanged owners. There are no protected identity/debt keys on the
absorbed sources. No debt, baseline, pin or hatch count is retired or added.
The final preview against the same census index reports LINKS, retaining
1,044 authored bytes (the three originals' 933 + 32 + 79). This is a file
consolidation, not an increase in the census's linked-byte headline.

## Complete pending path-batch audit

The batch based on `e584f58929` also contains the earlier AptSaveLoad callback
absorption recorded in aptsaveload-consolidation-20261029-codex.md. Its one
deleted callback plus this merge's two deleted satellites are all pending
source-path changes. Combined searches of active tools, hooks, workflows,
source/header includes, root build/configuration files, documentation and
reverse registers find no active hard-coded consumer requiring a change.
Current ledger source columns resolve to the merged owners. Remaining old
paths are provenance comments, historical handoffs/attempts/deleted-row
narrative, append-only naming records, and the last census's link_status.csv.
Preserve those records; the census publisher owns link-status refreshes.

The outgoing batch audit first found four stale receipts after the rebase:
AptSaveLoad, AIStateMachineUpdate, EmotionTrackerUpdateCtor and
ScriptEngine_setSides. Explicit strict preparation refreshes all four:
30/30 rows, 12 string literals and one import reference verified. The repeat
audit is still INCONCLUSIVE because index `85f6b7f40c` predates the outgoing
base and the affected Common/0CreateAHeroManager21FE49.cpp consumer lacks a
current receipt. This is the existing shared obstacle, not proof of a clean
consumer closure. Carry that consumer and the merged provider scope into the
next scheduled census; no nightly, census or smoke run was started here.

## Remaining prerequisites

Eight donors remain outside this merge after supported compile rejection:

- ForceEmotion, Rva004B0EBC, loadPostProcess and xfer need their method/member
  declarations reconciled with the composed EmotionTrackerUpdate view.
- Rva004B0FEBCheck needs the composed Object/player and nested-filter views.
- Rva004B15E6Clear carries a private STL allocator definition conflicting with
  the seed's STLport declarations.
- ModuleDataParseAddEmotion needs its static method/member declarations in
  the composed module-data view.
- The constructor still needs its Thing header adoption and compatible base
  and derived-interface declarations.

Six mixed sources remain untouched: ModuleNameGetters, the two destructors,
EmotionTrackerUpdate_update, ModuleDataBuildFieldParse and Rva004B0FEBCtor.
Their other rows preclude absorbing them in this merge. Reconcile rejected
views in separately verified changes; do not split mixed files inside a merge.
