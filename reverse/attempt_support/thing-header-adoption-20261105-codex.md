# Thing header adoption, 2026-11-05

The outgoing change retires five header-queue keys through
`header_adopt_lane.py accept --class Thing`. AptMyHeroRefreshCamera replaces its
private Thing definition with the canonical include; four existing indirect
consumers gain direct includes. The canonical header stays unchanged.

Initial base: `4de236a7f1`. Scope: the header picker's first 25 Thing consumers,
held under `class:Thing` by `yasinschroeder-codex`. Seven keys passed initial
acceptance. During publication, upstream independently landed the same
PlayerBattlePlanBonuses and Rva005AB125Tactic adoptions. Rebase onto
`67fd5410bc` retains both upstream changes and their obstacle history; those
two retirements are not credited to this commit.

The constructor-backed canonical Thing places cached position at +0x38.
AptMyHeroRefreshCamera reads its m_cachedPos fields. A TU-local scalar inline
X accessor preserves the retail expression scheduling; direct X/Y/Z member
arguments failed byte matching and were replaced before acceptance. This pass
infers no donor name or layout from equivalent bytes.

## Outgoing adopted scope

| Source (under Code/GameEngine/Source/GameClient/) | Matched rows |
| --- | ---: |
| GUI/ControlBar/ControlBarCommandProcessing.cpp | 8 |
| GUI/GUICallbacks/Apt/AptMyHeroRefreshCamera.cpp | 5 |
| InGameUIIdleWorker.cpp | 9 |
| InGameUIPlaceBuildAvailable.cpp | 1 |
| InGameUIUpdateLocalPhantomStructureDisplay.cpp | 3 |

All 26 rows in these five sources pass byte verification. The combined
seven-file check also covers the upstream battle-plan (7 rows) and tactic
(5 rows): all 38 rows, one data row, 14 string literals, seven compiler float
literals and nine funclet rows checked past compiler-label renumbering pass.
All seven sources pass find_declared_unmatched after the initial edits.
All seven owning accepts pass structural, byte and combined link-preservation
prediction checks against the local census index (2026-11-05 05:17 at
`c95fcfcfcd`), confirmed current by `link_check.py --fetch-index`.

The [initial build](thing-header-adoption-20261105-codex/build.log) and
[initial seven-file acceptance](thing-header-adoption-20261105-codex/accept.log)
record the pre-rebase verdicts. The
[post-rebase build](thing-header-adoption-20261105-codex/build-after-rebase.log)
and [post-rebase acceptance](thing-header-adoption-20261105-codex/accept-after-rebase.log)
pass again, retaining upstream's explanatory comment in the battle-plan prefix.
These checks establish no new census coverage or runtime result.

The other eighteen automatic trials were restored; their queue keys and source
files remain unchanged. The four AI scanner failures remain the previously
recorded STLport guarded-include false rejects. Other consumers still need
individual layout, declaration or codegen reconciliation; their failed trial
bodies were not left in Code/. No source paths, pins or aliases change.
