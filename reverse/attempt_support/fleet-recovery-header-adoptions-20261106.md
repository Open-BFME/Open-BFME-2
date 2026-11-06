# Stopped-fleet header adoptions recovered on current master

Date: 2026-11-06. Source base: `8bb483ac9115`; recovery owner `codex-recovery-20261106-root`.
Historical handoffs were committed separately before the stable provider check.
Source adoption and queue retirement are published separately to shorten each required gate window. The source commit leaves all five queue rows pending.

## Recovered scope

| Class | Consumer | Matched rows |
| --- | --- | ---: |
| FontLibrary | `Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/AptDisplayStringAllocation_ctor_Rva004D5A4D.cpp` | 1 |
| DataChunkInfo | `Code/GameEngine/Source/GameLogic/Map/StandingWaveAreasDataChunkParser.cpp` | 7 |
| WorldHeightMap | `Code/GameEngineDevice/Source/W3DDevice/GameClient/FlatHeightMapDoPartialUpdate.cpp` | 1 |
| WorldHeightMap | `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DSnowManagerRender.cpp` | 1 |
| RenderObjectDrawModuleInfo | `Code/GameEngine/Source/GameClient/System/FXParticleSystem/RenderObjectDrawModuleInfoXfer.cpp` | 1 |

FontLibrary recovers the source change from unpublished `aec478f1bd6f`. DataChunkInfo and WorldHeightMap recover chat02/seat1 and chat04/seat3 proposals. RenderObjectDraw recovers the adoption from unpublished `3f7132879388`, adapted to current master's already-repaired public `DoXfer(Xfer &)` identity. It does not restore the obsolete protected pointer signature. Unit-local defines select the canonical header's existing capitalized, reference-taking Snapshot mode.

All changes replace private views with existing headers. DataChunkInfo's version remains at +8. WorldHeightMap retains refcount +4 and origin offsets +0x120E0/+0x120E4. RenderObjectDraw's fifteen field bindings follow its constructor/destructor/transfer-backed canonical offset labels. The existing headers carry the target layout facts; no donor path or speculative original field name is asserted. No shared header, compiler flags, source path, code row, pin, alias, table or body is added or moved. Source-file count is unchanged.

## Verification of the recovered proposal

- `find_declared_unmatched.py SOURCE --fail` for all five consumers: all defined functions already matched, before and after changes.
- `./build.sh` on the five explicit sources: **11/11** matched; **1 data row**, **6 float literals**, **4 named imports**, zero skipped/unverified string references. Four StandingWave compiler-local funclets are verified through their parent EH data after compiler label renumbering.
- `link_check.py --prepare-current` on the five explicit sources, with the checkout held steady: **5 strict reusable providers**, ordinary gates again **11/11**, no extra source expansion or census/index/status update. The first attempt issued no witnesses because HEAD moved during separately committed historical handoffs; the stable rerun passed.
- `header_adopt_lane.py accept --class FontLibrary` on its explicit consumer: PASS, **1 row retired**.
- `header_adopt_lane.py accept --class DataChunkInfo` on its explicit consumer: PASS, **1 row retired**.
- `header_adopt_lane.py accept --class WorldHeightMap` on its two explicit consumers: PASS twice, **2 rows retired**.
- `header_adopt_lane.py accept --class RenderObjectDrawModuleInfo` on its explicit consumer: PASS, **1 row retired**.
- Acceptance includes the ordinary byte and census-preview preservation checks. All **5** proposed queue removals were performed by the owning tool, not by hand. Publication is split after repeated lost races: this commit carries the source changes while retaining the queue rows. The owning acceptance will retire them again in a separate debt-only publication.
- `check_csv.py`: 99,514 functions, 9,318 symbols, 2,272 data rows, OK. `git diff --check`: clean.

Compiler: pinned BFME1 VS2003 through the existing shared VM, Wine prefix `/home/bfme/.wine-pdb`, `BUILD_POOL=1`. Only one recovery worker ran; the stopped fleet did not resume. Logs and command/status/timing receipts remain under ignored `build/fleet-recovery/20261106-pass3/`.

## Publication and measurement limits

The published census index is `d707d2f53b` (2026-11-06 11:04 UTC), older than this source base. Strict providers and owning acceptance preserve their bounded scopes; they do not establish current full consumer closure. The outgoing pre-push batch audit must judge the actual final range and its inconclusive cases must remain unverified. The previously missing current receipt for `0CreateAHeroManager21FE49.cpp` is not assumed repaired by this five-source batch.

The newest official real link inspected before publication is run **42233431149** at `6e5fe55db8`: **291 unresolved**, **0 duplicates**, **673 initializer bridges**, **1,775 vtable bridges**. It predates this recovery. Its diagnostic link is not the exit test. No new real link, image, menu, skirmish, save/load or retail-CRC result is claimed. Remaining family/header/merge prerequisites remain queued; no consolidation or export-count gain is claimed.

## Commit-gate shadow finding

The normal commit hook reverified **11/11** rows, **EXACT 1** EH graph, the data row, six float literals and four imports, and accepted all five queue removals. Its shadow identity detector reports the existing `?Set_Material@DX8Wrapper@@SAXPAVVertexMaterialClass@@@Z` definition as divergent. Read-only COFF/index comparison finds this source's **52-byte** provider has digest **c0b7cdf7e449** both in published index `d707d2f53b` and the recovered current object. Its declaration/body also precede the new WorldHeightMap include and are unchanged. This establishes provider preservation against that index; it does not repair the pre-existing retail identity finding. No identity baseline key was added or retired. The full outgoing consumer audit and index-age limitations remain.

## Publication rebase

Rebased onto `ffc7c6bdc9d` after concurrent master updates. Documentation conflicts preserve both contributors' histories. `git diff --quiet 5a1e6ff3247 HEAD -- <the five consumer paths>` exits 0: all five already-verified source files are byte-for-byte unchanged by the rebase. The historical Cylinder and particle-slave investigations are now explicitly marked superseded by current upstream repairs. Pre-push verification still judges the actual outgoing batch; no full consumer or runtime claim follows from this source-equality check.

## Completed combined-batch publication checks

The combined source/debt attempts passed the normal pre-push gates: 11/11 rows, 13-symbol DIR32 consistency, EXACT 1 EH graph, six float literals, four imports and converged data checks. Rebases reused five source receipts. Their audit remained INCONCLUSIVE/UNVERIFIED: index d707d2f53b predates each outgoing base (including 71fdc054f3a90042ea6bfa0a1b921548378c22e1), and 0CreateAHeroManager21FE49.cpp lacks a current affected-consumer receipt. These cases remain for the next authoritative census; no closure or runtime result is inferred. Repeated successful gates lost publication races, so source adoption and owning queue retirement are now published separately. No hook was bypassed or changed.

## Owning retirement after source publication

Source batch `2f02f6e984e` landed on master, including source commit `60c0dabc72c`. The four owning acceptance commands were then rerun against that published source with HEAD held steady: FontLibrary PASS/1 row, DataChunkInfo PASS/1 row, WorldHeightMap PASS twice/2 rows and RenderObjectDrawModuleInfo PASS/1 row. The tool alone removes these **5** queue rows; no source, header, symbol, ledger, baseline or compiler change accompanies this retirement.

The source publication's normal pre-push check passed 11/11 rows, one data row, six float literals, four imports, 13-symbol DIR32 consistency and EXACT 1 EH graph. Its actual outgoing base was `8ff67a87b55d231d1506a10f4daf9fa91367cd0e`; the link batch audit remained INCONCLUSIVE/UNVERIFIED on old index d707d2f53b and the missing current affected-consumer receipt for 0CreateAHeroManager21FE49.cpp. Carry that exact scope into the next authoritative census. This debt-only follow-up does not clear consumer closure or establish a real linked image/runtime result.

## Consumer-preservation audit, 2026-11-06

The missing receipt is resolved at checkout `da93446935f9`: `python3 tools/link_check.py --prepare-current Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` exits **0**, verifies **24/24** rows, three strings, one float and sixteen compiler-renumbered funclets, and issues **1 strict reusable provider**. The old object had an obsolete source hash and lacked an include-search inventory. No source repair or receipt exception was needed. This is a local cache repair, not a repository-wide cure for every historical audit mentioning this file.

The published source batch is audited against its actual base `8ff67a87b55d231d1506a10f4daf9fa91367cd0e` and tip `2f02f6e984e9bce072abddb082b18bdbb19fa76a`, using two clean worktrees created with `worktree_setup.py`. Among `link_census.CENSUS_INPUTS` and `TOOL_FILES`, `git diff --name-only BASE TIP -- <those paths>` lists exactly the five consumers above: **0 header, ledger, pin, tool, reference or source-path changes**. Both snapshots use the committed reference and ordinary compiler commands.

`python3 tools/link_check.py --prepare-current <the five explicit sources>` verifies each snapshot separately: both pass **11/11** matched rows, one data row, six float literals and four named imports; their ordinary gate reuses **5/5** objects and accepts five strict reusable providers. `link_census.object_current(..., allow_fresh=False)` checks all **10/10** objects against their own snapshot's strict receipts. Object MD5s also equal their receipt's recorded object digest; no cache entry, inventory or index was relabeled or hand-authored.

`class_cleanup.runtime_graph` and `same_runtime` compare all non-debug COFF sections, including linker directives, byte hashes, relocation kinds/targets, external providers, COMDAT selection/association and weak defaults. All **5/5 complete graphs are exactly equal**, without even section renumbering: **40 sections**, **99 relocations**, **31 external definitions**. A supplementary comparison also preserves COFF machine/flags and all **46 undefined/common/absolute external records** (including unused symbols); there are **0 weak defaults** on either side. Object file hashes differ, so raw object identity was not assumed. The JSON retains both full runtime graphs and source/object/receipt hashes.

The latest fetched published index is `f07300675e` (2026-11-06 15:57), still older than this base. `link_batch_audit.affected_sources(index, names) - providers` finds **4,464 other consumer units** for the **31 provider names**. Its largest fan-outs are the unchanged AsciiString destructor (2,380) and array-constructor helper (1,907). Complete runtime-object equality plus unchanged other compiler/identity inputs proves this batch leaves *every consumer binding unchanged*, including users absent from that older index. It requires no assumption that all those consumers currently link or match retail. This closes this batch's consumer-preservation handoff by direct before/after proof; it does not relabel the original census-based gate result as PASS.

Checks of the comparison itself: `python3 -m pytest tools/tests/test_class_cleanup.py -q` passes **21 tests**, including byte, relocation, weak-default, COMDAT-policy and provider-loss rejection. Mutating a section byte hash and removing a provider in each real after graph is rejected **10/10** times. These are audit negative controls, not the game's retail CRC control. No verifier or hook was edited.

[Machine-readable comparison and complete runtime graphs](fleet-recovery-consumer-audit-20261106.json). Reproduction: create clean worktrees at the exact base/tip; run the five-source `--prepare-current` command in each; require strict `object_current(..., allow_fresh=False)` and receipt/object digest agreement; call `class_cleanup.runtime_graph(build.obj_path(ROOT / source))` in each tree and `same_runtime(before, after)` for every pair. Also compare every COFF storage-class-2 record with section <= 0 (name, section, value, type, storage), and COFF machine/flags. The captured JSON permits rechecking graph equality and negative mutations without a compiler. Local command logs, snapshot capture script, receipts and objects are retained under `build/consumer-audit-20261106/`.

Still unmeasured: a fresh full census / ordinary census-based audit at this historical base, actual no-FORCE real-link result, retail correctness of pre-existing Set_Material, boot/menu/skirmish/save-load and retail game-logic CRCs. The old baseline remains stale; no full consumer rebuild, new image or runtime success is claimed. Unrelated family/header/TU prerequisites and historical obstacle entries remain open.
