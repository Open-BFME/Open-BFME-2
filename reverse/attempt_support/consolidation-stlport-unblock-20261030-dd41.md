# STLport donor removal -> TU merge lane (dd-41, 2026-10-30)

Base: origin/master `e75ccb7c79` + the three STLport bundles still in the fleet inbox
(dd-35 `20261030T0211Z-dd31-rebased`, dd-35 `20261030T0218Z-stlport-lane`,
dd-33 `20261030T0215Z-stlport-headers`), applied on the sandbox branch `dd41`
(tip `ab66263d1e`). Every dry run below ran on that tree.

## How the candidates were picked

`reverse/functions.csv`/merge-map snapshot (2026-10-29 17:54Z) records 119 TUs with a
C2953 donor; 109 of those are an `_STL`/`StringBase` template (97 `_STL::allocator`,
53 `StringBase`, 18 `_STL::vector`, ...). For each of the 227 C2953 donor files the
tree was scanned for a surviving private copy (`namespace _STL`, `class/struct
StringBase`). On the bundle tree 28 of the 119 TUs have **no** C2953 donor left;
17 more have at least one cleared donor and at least one donor the snapshot already
accepted. Those 45 were dry-run in priority order (largest accepted count first,
smallest TU first within a class).

## Results (fresh `tu_skeleton.py --merge TU --dry-run --no-claim`)

### Accepted two or more donors

| TU | accepted | refused | verdict |
|---|---|---|---|
| `GameLogic/ScriptEngine/ScriptConditions.cpp` | 0 (63 donors, 254 approved rows) | {} | **BLOCKED** by the seed's own LinkGuard, see below |
| `GameClient/LivingWorld/InGameUI/StrategicInGameUI.cpp` | 6 | {} | **HELD** by `jonathan-merge-all` (`file:` on the TU and 5 donors) - skipped |
| `WWVegas/WW3D2/RenderAsset.cpp` | 3 | {} | **BLOCKED**: case-only collision, see below |
| `GameClient/GUI/InGame/Tactical/BannerUI.cpp` | 1 real donor (`Rva00216517Fire.cpp`) | {} | below the 2-donor bar; the other "accepted" entry is the TU file itself |

StrategicInGameUI accepted `Rva005E36EAMat.cpp`, `StrategicInGameUIBuildQueueUnitQueued.cpp`,
`Bfme/Rva005E8AAFCtor.cpp`, `Rva005E8D71Dtor.cpp`, `Rva005E9625Dtor.cpp`,
`Rva005E98A0Dtor.cpp` (refused {}, 15 mixed). Whoever holds the `jonathan-merge-all`
claim can land it as it stands; the three `Common/Bfme/Rva005E74CF.cpp`,
`Rva005E7529Dtor.cpp`, `Rva005E8D71Ctor.cpp` donors still fail C2953 `StringBase`
against the TU's seed even though they carry no private copy by the scan above -
the seed defines `StringBase` and the donors include the frozen shim header.

### Accepted nothing (blocked, not this lane)

`AnimationAsset.cpp` (rejected `HAnimPrototypeOwnerCtor.cpp` C2953 **`RefCountPtr`** -
not an `_STL` copy - and `Rva0014D078LoadAnim.cpp` StringClass view),
`RayEffect.cpp`, `RegionAwardDispute.cpp`, `LightPointSystem.cpp`, `BaseUpgrade.cpp`,
`MonitorConditionUpdate.cpp`, `TerrainResourceManager.cpp`, `RespawnUpdate.cpp`,
`W3DSnow.cpp` (4 cleared donors, all still rejected for other classes),
`GettingBuiltBehavior.cpp` (3 cleared donors), `W3DGameFont.cpp`, `SubtitleEntry.cpp`,
`LivingWorldEyeTower.cpp`, `W3DShadow.cpp`, `ThreatFinderUpdate.cpp`,
`AIUpgradeScienceBuilder.cpp`, `GeometryUpgrade.cpp`, `MoveToGroupOrder.cpp`,
`W3DAptComponentView3D.cpp`, `GiantBirdAIUpdate.cpp`, `VideoPlayer.cpp`,
`LoadScreen.cpp`, `HotKey.cpp`, `W3DDisplay.cpp`, `ElvenWoodSpecialPower.cpp`.

`GameText.cpp` accepts one real donor (`Rva002E5791VectorDeletingDtor.cpp`, which is
dd-35's converted file) - below the two-donor bar and it would collide with dd-35's
queued bundle, so it was left alone.

`LANGameInfo.cpp` (dd-27) and `W3DFloorBuffer.cpp` (dd-21) were skipped as held.

`meshmdlio.cpp` (4 cleared donors, 116 approved rows) is the one TU left without a
verdict: its dry run does not finish in 420 s. Give it a real `--merge` run with a
long budget; the earlier attempt died on a `FileNotFoundError` because the seat's own
temp-file cleanup removed `.meshmdlio.*.tu_skeleton.cpp` while the run was live -
never delete `.*.tu_skeleton.cpp` files while a merge is running.

## Obstacle: ScriptConditions seed fails the LinkGuard

A real `--merge` of `GameLogic/ScriptEngine/ScriptConditions.cpp` (63 donors, 254
approved rows, run 03:50-04:03Z) ends `accepted: []`, `refused: {}`, `rc=2`:

    blocked: no verified merge of two or more donors; the seed itself fails under
    every merged flag set: link: .../ScriptConditions.cpp links at the census;
    the merged object would not: unresolved
    ?hasSpecialPower@Object@@QBE_NW4SpecialPowerType@@@Z

The snapshot's `n_accepted=11` for this TU is stale: under the merged flag sets the
TU's own object stops providing `Object::hasSpecialPower` for its callers. Nothing
was written; the claim was released. The `reconcile:` hint points at `tu_views.py`
for the donors' own views of `AI`, `AudioManager`, `BfmeFixedStorage0004543D`,
`BfmeObjectDlinkBase`, ... - that is the lane this TU needs before any merge.

## Obstacle: RenderAsset.cpp case-only collision

`--merge Code/Libraries/Source/WWVegas/WW3D2/RenderAsset.cpp` verifies (11/11 rows,
3 donors absorbed: `Rva00136794Ctor.cpp`, `Rva00136642HintInsert.cpp`,
`Rva001364ACCreateNode.cpp`), writes the TU, and then the pre-commit hook refuses:

    case-only path collision (breaks Windows/macOS checkout):
      Code/Libraries/Source/WWVegas/WW3D2/RenderAsset.cpp
      <-> Code/Libraries/Source/WWVegas/WW3D2/renderasset.cpp

`renderasset.cpp` already exists on master and owns one row of the *same* retail TU
(`?PostLoad@ModifiedRenderFactory@RenderAsset@@QAEXXZ` 0x00136F5B, evidence
"WB9B2CB0 renderasset.cpp:302"), while `reverse/tu_map.csv` approves
`RenderAsset.cpp` as the TU path. The merge attempt was reverted; nothing landed.

The fix is a naming/TU-map decision, not a merge: either move 0x00136F5B's row into
the approved TU and delete `renderasset.cpp`, or re-case the approved TU to
`renderasset.cpp`. Until then this 3-donor merge cannot land on Windows/macOS.

## Method notes for the next seat

* `tu_skeleton.py --merge` claims its own scope; in a sandbox without credentials run
  it with `--no-claim` and claim `file:` + each moved row's RVA on the PC first
  (the `--plan TU` "pull" rows are the upper bound; the dry run's `accepted` list is
  the real set).
* `claims.py claim` with 200+ keys takes ~20 minutes; run it detached.
* A `--merge --dry-run` on a 250-row TU does not finish in 900 s; go straight to the
  real merge (it verifies the same way and writes nothing on failure).
