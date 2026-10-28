# FireWeaponUpdate bounded composition, 2026-10-28

Inspected base: `c217a70481`. Provider index: `41c28839bf`, 2026-10-28
11:08. This is source-file recovery, not a linking or image-ownership gain.

## Scope and placement

`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/`
and the merge tool's fresh in-memory TU map approve FireWeaponUpdate.cpp.
The planner has Z/S placement anchors, not an original retail `__FILE__` string;
this does not establish an external donor path as BFME 2 source.
`tu_skeleton.py --merge` accepted the existing TU, BehaviorDtor, Ctor and PoolKey:
16 rows, three fewer source files. It repointed 12 function/TU-map source cells
and both cached-key data owners. The committed map was not regenerated.

## Verification and bindings

- Before: all seven clean-file candidates verify 24/24 rows. The four accepted
  files preview LINKS for 1,504 authored bytes in total; all seven for 1,808.
- After: `./build.sh` and `link_check.py --prepare-current` verify 16/16 rows,
  one string, and strict reusable receipts. Ordinary preview remains LINKS
  for 1,504 bytes. The merge guard preserves its census-linked donor scope.
- Frozen-file, CSV, staged TU ownership, class, code-identity, MS-header,
  ordinary and converged data checks pass. Three parent EH graphs are EXACT.
- The union of originals and the merged object each defines 59 external
  COMDAT names. 58 raw-byte/relocation fingerprints are unchanged; no external
  names are added or removed. Destructor, helper and update references become
  definitions within the same TU. No new external dependency is introduced.
- The primary compiler table `??_7FireWeaponUpdate@@6BObjectModule@@@`
  changes from 8 bytes (`b4fc4fc09cec`) to 16 (`5067786404e0`). Existing
  offset-0 objectModuleAnchor and offset-4 deleting-destructor relocations
  are retained. Offset 8 adds getModuleNameKey and offset 12 adds xfer, using
  the destination view's existing virtual declarations and matched bodies.
  Constructor +45 and destructor +22 retain their DIR32 reference to this name.
  Both secondary table fingerprints are unchanged. This synthetic primary
  view is not a recovered complete retail table: data_ledger's native table
  at RVA 0x0084C198 is 352 bytes. Full native table/layout recovery and runtime
  dispatch remain open; byte masking and the ordinary preview do not prove them.
- Both OilSpillUpdate constructor/destructor consumers were prepared through
  `link_check.py --prepare-current` and passed ordinary byte gates. The staged
  batch audit remains INCONCLUSIVE: the index predates the base, and an affected
  broader consumer, Common/0CreateAHeroManager21FE49.cpp, lacks a current receipt.
  Full selected-provider/consumer closure is unverified. Carry this moved scope
  and the primary-table change into the next normal census. No census or smoke
  run was started.

## Debt and path audit

The four accepted paths have no code/data baseline or header/MS-header queue
keys to retire or transfer. The cached key and its guard retain names/addresses;
only their owning source changes. The existing Coord3D class allowance stays,
and hatch totals do not change. Active function, TU and data ownership paths
resolve to the destination; no active fold-proof reference targets a deleted file.

Audited the complete staged path batch against base c217a70481 using all three
deleted basenames across tools, hooks, workflows, Code, reference/shims, docs,
reverse and root build configuration. No active tooling/include consumer needs
an update. Remaining old names are provenance comments, historical attempt and
deleted-row evidence, a historical functions.csv explanation, and the last
published link_status.csv snapshot. These are intentionally retained; the
snapshot is owned by measurement. No new ledger source is untracked.

## Remaining composition prerequisites

Rva0048B9D0Replace.cpp needs WeaponSlotType declaration ordering and an evidenced
rva0048B9D0 member declaration in the union view. ModuleDataCtor's fake allocator
and _List_base views conflict with the real STLport headers. ModuleDataDtor's
m_list spelling differs from the seed's m_nuggets. Reconcile each donor in its
own verified change before retrying the supported merger. Five mixed sources
remain separate (GapBodiesGE22, ModuleNameGetters, INI_Rva0048BCBBParseFireWeaponNugget,
ModuleDataBuildFieldParse and string_base_clear); any split is a separate lane.

Local receipts: build/fireweapon-consolidation-codex/{before-build,after-build,
strict,consumer-strict,before-link,after-link,batch-audit}.log, comparison.json,
merge.log and final-path-audit.txt. These scratch files are not required as
tracked compiler inputs.
