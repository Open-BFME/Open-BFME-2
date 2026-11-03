# Seven prospective AIPathfind donor paths: bounded read-only audit

Scope: only the seven prospective absorbed paths below, all into `Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp`. This is a pre-application audit snapshot, not a certification of an applied merge or the complete outgoing Git range. Main owns source/header edits, normal merge, final gates and publication. No tracked source, Git index, claims, network or compiler/cache mutation was performed here. Tracked reads stopped after the report.

| Donor below Code/GameEngine/Source/GameLogic/ | Code row RVA / size |
|---|---|
| Object/Pathfinder_SetDebugPathPosition.cpp | 0x002E74B5 / 17B |
| AI/PathfinderRva002F95B7.cpp | 0x002F95B7 / 63B, 0x002EAE20 / 63B |
| AI/PathfinderRva002EB3D7.cpp | 0x002EB3D7 / 63B |
| AI/PathfinderRva002EB675.cpp | 0x002EB675 / 63B |
| AI/PathfinderWorldLineWalk.cpp | 0x002EED41 / 63B |
| AI/PathfinderRva002F6AE3.cpp | 0x002F6AE3 / 63B |
| AI/Rva002F6F90QueryCallback.cpp | 0x002F6F90 / 341B |

There are8 function rows in7 files (one donor has2), totalling736B. The seed snapshot has81 function rows plus2 matched data entries, explaining its83 normal-build units. Moving these8 functions while preserving the two data entries yields89 function rows plus2 data entries, or91 normal units. Do not misread the earlier83 normal-unit count as83 function rows. The committed TU-map snapshot places every one of the8 donor rows at AIPathfind.cpp, approved: seven S rows and the callback's C row. These are existing assignments; main's supported merge must enforce fresh-map/current-input approval rather than treating this snapshot as approval.

## Required supported updates

1. Apply the move only through `tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp`. Repoint all8 `reverse/functions.csv` source cells and all8 `reverse/tu_map.csv` source cells. There are no donor-owned `data_rows.csv` or `body_owners.csv` entries in this snapshot, and no matching fold-proof token or source mention in `reverse/symbols.csv`. Preserve every row's symbol, RVA, extent, notes and exact body.
2. Preserve the callback's real Microsoft-header debt. `reverse/ms_header_queue.tsv:554` currently owns `Rva002F6F90QueryCallback.cpp`, category conflicting/abi, recommended `<stdio.h>`, hand declaration, specific `fprintf:abi`. The merged TU must own the finding after `tu_skeleton.refresh_reports`; the old source key must vanish with its file, not with its debt. That function scans the merged source using `ms_header_audit.scan_text` and `refresh_queue`, with `removed=gone`, and updates the ignored occurrences report through its owning tool. Do not blanket replace fprintf or silently retire this ABI mismatch.
3. The seed's remaining `reverse/header_queue.tsv` Pathfinder key is preexisting and source-root-owned. This snapshot caught it before main's owning Pathfinder header acceptance completed; main has since reported successful owning acceptance. It is not donor-transfer debt. No header queue entry is keyed to any of these seven donors. Main should use the current accept result and the merge's queue transfer/refresh, not reintroduce the captured stale key.
4. No donor keys were found in code_identity_baseline.tsv, data_check_baseline.txt, gate_baseline.txt, hatch_baseline.tsv, flag_overrides.csv, unclaimed_sources_whitelist.txt, pin_consistency_baseline.csv, dx_migration_queue.tsv or module_registry_baseline.txt. The seed's12 hatch keys and2 data-ledger/pool owners remain seed-owned. Neither pool owner is retired by this move. There is no protected debt transfer to invent; preserve totals and use any exact trailer the supported merge prints.
5. `docs/doxygen/sources.cfg` has no reference to an old donor basename; the normal merge's existing doxygen repointer/ensure behavior remains the supported owner. No additional active tooling/configuration source list was found that needs a handwritten path update.

## Active path consumers and intentional old references

The combined old-basename search was run once over the repository, including hidden .githooks/.github and Code/tools/docs/root configuration, excluding build, reference and internal checkout state. Its complete55-line result is `path-references.txt`. No active tool, source/header include, hook, workflow or build-configuration reference to a deleted donor path appeared. None of the donors is source-included by another unit in that result. Eight seed tu-skeleton comments currently say 'not merged yet'; the supported merge should consume/update those placeholders as it absorbs the bodies.

The remaining references are deliberately historical/derived:

- `reverse/link_status.csv` has all7 donors marked yes with zero recorded unresolved/conflicts. This is the prior census's per-source result, not fresh postmerge evidence. Leave measured history to its owning census; do not manually transfer or manufacture a headline result.
- `reverse/class_contracts/Pathfinder.json` lists the SetDebug donor among witness sources for offsets76/80/84. These are historical view witnesses, not a compile input/source registry; preserve the evidence rather than editing its provenance into a false original location.
- `reverse/name_basis.csv:1589` records the mechanical old file rename. `reverse/name_votes.csv` and `reverse/name_agreed.csv` retain old callback naming proposals (including later blocked statuses). They are historical naming records, not a licence to apply the stale ThingTemplate proposal or a source list to rekey by hand.
- `reverse/re_attempts.log:28994`, `reverse/attempt_support/pathfinder-fixed-storage-20261103/merge-dry-summary.json`, and `reverse/attempt_support/sideways-worldtocell-link-20261015/*` are banked outcome/provenance records. Preserve old paths there. No external BFME donor path is asserted as BFME2's original source.

Generic discovery remains coherent: tools/build.py uses current ledger ownership plus recursive Code/*.cpp discovery and source-relative object names; tools/link_check.py source preparation also inspects current owned paths and recursive Code/*.cpp; ms_header_audit recursively scans current source roots. tools/subsystem_link.py intentionally selects the user-provided directory's *.cpp; this move removes one member from Object and adds its body to the existing AI TU, so ad hoc directory-only subsets follow that documented selection rather than retaining an old object path. No donor-specific invocation/configuration was found. Both source directories remain, and the destination is an existing AI .cpp, so these globs still reach the consolidated unit. Old donor object/cache receipts must not be credited as the new TU's checks.

## Provider/consumer implications and remaining final proof

Read-only existing cached objects expose exactly8 donor code definitions plus7 string-literal COMDAT definitions in the callback; no donor supplies a vtable, deleting helper, EH metadata or a unique mutable data provider. The SetDebug body has no undefined dependency. The five wrapper files call existing `Rva002E7875WorldToCell` and their exact typed `Pathfinder::iterateCellsAlongLine` overloads, with6 wrappers in total because F95B7 also contains EAE20. The callback calls canonical `Pathfinder::CheckForAdjust` and references g_00E03745, `_theLogicRandomLogFile`, `_fprintf` and __fltused. Full symbol names and object hashes are in `cached-donor-providers.json`; these are existing cached facts, not a new compile receipt.

A safe composition must retain those exact function symbols and typed overload bindings; no new pin or alias is needed for a source move. Canonical source/header adoption should prevent duplicate private Pathfinder/PathfindLayer definitions. The callback's opaque-template/object layout and hand stdio declaration remain existing representation/debt; this audit does not rename/recover them or erase their queue finding. String COMDAT coalescing must retain exact bytes and symbolic users.

Main still needs normal91-unit verification, existing2 data checks, owning EH checks, fresh ordinary code/data/relocation provider-union comparison, include/case/ledger/ownership checks and the normal affected-consumer/link guards after the supported merge. The old census says these donors linked; therefore a passed body comparison alone is insufficient if composition removes/changes a provider. The current index in the cached snapshot is dated2026-11-02 commit984a4cdc4d / census357ce2a88f; it is explicitly not a fresh selected-provider or full-image result. No whole-image safety claim is made here. Main must audit the complete outgoing path-move range immediately before publication and extend this report if more paths/consumers are added.

Evidence snapshots: register-snapshot.json (narrow rows/register matches and source hashes), path-references.txt (combined path search), cached-donor-providers.json (read-only cached definitions/undefined bindings), patterns.txt. Extraction scripts are build/aipathfind-readonly-audit-20261103/seven-path-audit.py and this scratch directory's providers.py.
