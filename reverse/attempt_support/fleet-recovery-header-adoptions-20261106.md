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
