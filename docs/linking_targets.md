# Linking target checklist

Recorded 2026-10-25 from the linking handoff. The census snapshot is
`ef9c691284`, **2026-10-25 18:23 UTC**, recorded in
[link_status.csv](../reverse/link_status.csv) and
[link_census_history.csv](../reverse/link_census_history.csv).
The initial 50 named units and their blocker categories were checked against the
committed status. Bytes and difficulty/attempt groupings preserve the handoff's
reported values; they describe leads rather than verified current failures.
The additional 35 two-blocker and 290 larger-blocker rows complete all **375**
census-blocked units, using reconciled game bytes in their tables.

Before selecting a target, read the [obstacle register](linking_obstacles.md),
resolve its current source after renames/consolidation, check claims and prior
attempts, and verify the blocker against current inputs. When working a row,
update its follow-up with the date, revision, result, evidence link and remaining
dependency. Record cleared scope and census confirmation separately; retain the
snapshot bytes and history. Add newly encountered causes to the obstacle register.

## One blocker: fresh candidates

The handoff found no earlier served-queue entry for these 16 units. Follow-up:
**Open / current-input verification pending** for each row.

| Unit | Matched bytes | Census blocker | Follow-up |
| --- | ---: | --- | --- |
| `urlBuilder.cpp` | 942 | COMDAT losers | Open |
| `stlport_narrow_stringbuf_overflow_setbuf.cpp` | 567 | COMDAT losers | Open |
| `stlport_pair_asciistring_twins.cpp` | 395 | Wrong selected | Open |
| `MeshModelReadVertexMaterials.cpp` | 271 | Wrong selected | Open |
| `stlport_narrow_string_erase_count.cpp` | 130 | Unresolved | Open |
| `ElementStrideWalks.cpp` | 90 | Unresolved | Open |
| `VectorRangeEraseRva003F6975.cpp` | 80 | Unresolved | Open |
| `Rva00541913CopyCtor.cpp` | 76 | Wrong selected | Open |
| `StlportNarrowAppendCStr.cpp` | 58 | COMDAT losers | Open |
| `GrantUpgradeCreate.cpp` | 42 | Unresolved | Open |
| `PartitionData_friendUpdateCellsTouched.cpp` | 37 | Wrong selected | Open |
| `StlSweepW5Rva0042830DAssignTwin.cpp` | 33 | Unresolved | Open |
| `StlportVectorClearRva00475F2A.cpp` | 30 | Unresolved | Open |
| `Weapon_getName_Thunk.cpp` | 26 | Wrong selected | Open |
| `Rva000FDCD7Get.cpp` | 26 | Unresolved | Open |
| `ConstIntGetters2Addr.cpp` | 6 | Addresses | Open |
| **Total: 16 units** | **2,809** | | |

## One blocker: previously worked

The handoff reports earlier solved, converted or landed work for these 16 units.
Follow-up: **Recheck the existing repair and its prerequisites** before retrying.

| Unit | Matched bytes | Census blocker | Follow-up |
| --- | ---: | --- | --- |
| `MeshLoadContextAddLegacyMaterial.cpp` | 2,828 | Wrong selected | Recheck repair |
| `stlport_float_format.cpp` | 2,620 | COMDAT losers | 2026-10-25: still blocked (2,619 current bytes); active append declaration hits VC7.1 C1001, alternate syntax rejected. Trials restored. [Evidence](../reverse/attempt_support/link-regression-clusters-20261025.md). |
| `MaterialCollectorDestructor.cpp` | 1,686 | Wrong selected | Recheck repair |
| `MaterialCollectorCollectMaterials.cpp` | 1,506 | Wrong selected | Recheck repair |
| `PositionStartSpots.cpp` | 994 | Wrong selected | See LINK-006 map-metadata subset |
| `SkirmishMapStartSpots.cpp` | 703 | Wrong selected | See LINK-006 map-metadata subset |
| `stlport_narrow_string_substring_ctor.cpp` | 363 | Unresolved | Recheck repair |
| `meshmdlio.cpp` | 352 | Wrong selected | 2026-10-25 at d7fa8a31bf3: paired current-provider preview clears all 352 bytes; 11/11 rows exact; three obsolete hatches retired. [Evidence](../reverse/attempt_support/meshmdlio-hatch-cleanup-20261025-bce2/readme.md), LINK-012; provider residuals and census confirmation remain open. |
| `GameInfoSetMapSize.cpp` | 343 | Wrong selected | See LINK-006 map-metadata subset |
| `stlport_narrow_string_substr.cpp` | 277 | Unresolved | Recheck repair |
| `Rva001ECF66Finish.cpp` | 96 | Unresolved | Recheck repair |
| `RtcStack.cpp` | 90 | Duplicates | Recheck repair |
| `w3d_dep.cpp` | 47 | Unresolved | Recheck repair |
| `Rva003BBAF0Ctor_Rva003FD199.cpp` | 44 | Unresolved | LINK-011: preview cleared; census pending |
| `SpecialPowerModule.cpp` | 36 | Unresolved | Recheck repair |
| `GapBodiesSeat10O1_Rva00525E00.cpp` | 22 | Wrong selected | Recheck repair |
| **Total: 16 units** | **12,007** | | |

## One blocker: harder obstacles

Each row retains the handoff's investigation lead alongside the census category.

| Unit | Matched bytes | Census blocker | Follow-up / prerequisite |
| --- | ---: | --- | --- |
| `Rva0056616BCopyDeferred.cpp` | 481 | Wrong selected | 2026-10-25: current 333 B parent still blocked by selected vector<BfmePod32> copy. [Evidence](../reverse/attempt_support/link-regression-clusters-20261025.md). |
| `stlport_narrow_ostringstream_dtor.cpp` | 429 | COMDAT losers | STL conflicts; compiler C1001 |
| `vector_class_vector3_ctor.cpp` | 218 | Wrong selected | LINK-015: preview links 194 B (2026-10-26); census pending |
| `Rva001F9524Concat.cpp` | 185 | COMDAT losers | Symbol identity debt |
| `stlport_narrow_string_copy.cpp` | 152 | Unresolved | Missing callee address |
| `DebugDestructorThunk.cpp` | 113 | COMDAT losers | Vtable slot-count mismatch |
| `stlport_pod28_vector_resize_value.cpp` | 73 | Wrong selected | Extra emitted COMDAT |
| `DebugStatisticsTextureShutdown.cpp` | 10 | Unresolved | Destructor inlining |
| **Total: 8 units** | **1,661** | | |

## Two blockers: largest identified candidates

| Unit | Matched bytes | Census blockers | Follow-up / prerequisite |
| --- | ---: | --- | --- |
| `PointGroupClassRva0017A890.cpp` | 12,000 | COMDAT + wrong selected | LINK-015: preview links 11,964 B (2026-10-26); census pending |
| `pointgr.cpp` | 10,695 | COMDAT + wrong selected | LINK-015: preview links 10,565 B (2026-10-26); census pending |
| `MmxIDct.asm` | 7,686 | Two address issues | Recheck LINK-007 storage repairs |
| `DX8SkinClearVisibleList.cpp` | 1,630 | COMDAT + wrong selected | LINK-015: preview links 1,613 B (2026-10-26); census pending |
| `StlportVectorDtorDeferred.cpp` | 461 | Two unresolved | Current-provider verification pending |
| `Rva00066A9ABody.cpp` | 371 | Two unresolved | Two global providers |
| `Rva007B7280Siblings.cpp` | 354 | COMDAT + wrong selected | LINK-015: blocked; its own inlined `??_G` loses while no copy is proven |
| `LargeGroupAudioKeyMapBfmeAddKey.cpp` | 324 | Two unresolved | Global records and vector resize |
| `FXListStoreCtor.cpp` | 280 | COMDAT + wrong selected | Current-provider verification pending |
| `PolygonTriggerCtor.cpp` | 186 | Unresolved + COMDAT | LINK-011 preview cleared 157 authored bytes; reconcile scope |
| **Total: 10 units** | **33,987** | | |

Point-group ownership evidence:
[VertexLoc handoff](../reverse/attempt_support/vertexloc-ownership-20261024/readme.md).
LINK-011 records 157 authored bytes for PolygonTriggerCtor; this checklist retains
the handoff's 186 matched bytes. Compare the measured scopes when updating it.

## Remaining two-blocker units: all 35 units

These complete the 45 two-blocker units: the initial shortlist contains ten,
and this table contains the other 35. All 40 one-blocker units appear in the
initial shortlist. Snapshot: `ef9c691284`, 2026-10-25 18:23 UTC.

The reconciled game-byte contribution is **4,492 bytes**. Two generated unwind
units contribute **2,885 bytes (64.2%)**; the other 33 contribute **1,607 bytes**.
Two rows contribute zero after the headline's provenance/padding and coverage
filters. These use the same unique-byte attribution as the complete headline
reconciliation below. Recheck current sources and providers before working a row.
Blocker key: **U** unresolved, **C** COMDAT losers, **S** wrong selected providers.
Follow-up starts at **Open / current-input verification pending**, with the
existing LINK-011 preview clearances retained for its two rows.

| Census source | Game bytes | Blockers | Follow-up |
| --- | ---: | --- | --- |
| `Code/gen_small/uw_gen_002.cpp` | 1,647 | 2 (U=2) | Open |
| `Code/gen_small/uw_gen_008.cpp` | 1,238 | 2 (U=2) | Open |
| `Code/GameEngine/Source/GameClient/System/FXParticleSystem/T1Base005F3750Ctor.cpp` | 184 | 2 (U=1, C=1) | Open |
| `Code/GameEngine/Source/Common/MultiplayerSettingsCtor.cpp` | 159 | 2 (U=2) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/HRawLoadW3D_Unresolved.cpp` | 149 | 2 (C=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/Rva00056da2Finish.cpp` | 136 | 2 (C=1, S=1) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerScreenBWFilterInit.cpp` | 101 | 2 (U=2) | Open |
| `Code/GameEngine/Source/GameClient/GUI/GameWindowManager_registerTabList.cpp` | 73 | 2 (C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/Rva003ADEFBCopy.cpp` | 67 | 2 (U=2) | Open |
| `Code/GameEngine/Source/Common/EmotionSystem.cpp` | 59 | 2 (U=2) | LINK-011: preview cleared; census pending |
| `Code/Libraries/Source/WWVegas/WW3D2/Rva007B73C0.cpp` | 59 | 2 (C=1, S=1) | LINK-015: blocked; its own inlined `??_G` loses while no copy is proven |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva00054EBE.cpp` | 47 | 2 (C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva000E0225.cpp` | 47 | 2 (C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/Bfme/Rva00739C70Cleanup.cpp` | 43 | 2 (U=2) | Open |
| `Code/GameEngine/Source/Common/SpecialPowerStore.cpp` | 37 | 2 (U=2) | LINK-011: preview cleared; census pending |
| `Code/GameEngine/Source/Common/PoolDeleteDeletingDtors01.cpp` | 35 | 2 (C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/Rva006F84C0DeletingDtor.cpp` | 35 | 2 (C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/BfmeConv901.cpp` | 33 | 2 (U=2) | Open |
| `Code/GameEngine/Source/Common/PlayerAITypeSetCtor.cpp` | 33 | 2 (U=2) | Open |
| `Code/GameEngine/Source/Common/S2DualVptrDerivedCtors.cpp` | 32 | 2 (U=2) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DPropDraw.cpp` | 32 | 2 (C=2) | Open |
| `Code/GameEngine/Source/Common/FamilyDeletingDtors_muse-cd13.cpp` | 28 | 2 (U=1, C=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva004F6FE1.cpp` | 27 | 2 (C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva005FE3C1.cpp` | 27 | 2 (C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/StaticInit/Rva00C6E31EInitializers.cpp` | 25 | 2 (U=2) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Rva005003C7EqualRange.cpp` | 24 | 2 (C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/BfmeThreeHundredThirtyFour.cpp` | 22 | 2 (U=2) | Open |
| `Code/GameEngine/Source/Common/System/XferBlockWriter_rva009D86E0_Rva0060CB97.cpp` | 21 | 2 (U=2) | Open |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarScheme_trolBarScheme_QAEXPAVControlBarSchemeAnimation_Z.cpp` | 18 | 2 (U=2) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate.cpp` | 17 | 2 (C=2) | Open |
| `Code/GameEngine/Source/Common/System/BitFlagsClear.cpp` | 14 | 2 (C=1, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Die/DieModule.cpp` | 13 | 2 (U=2) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/Rva001296F0Destroy.cpp` | 10 | 2 (U=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00502645.cpp` | 0 | 2 (U=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva004FCD6D.cpp` | 0 | 2 (C=1, S=1) | Open |
| **Total: 35 units** | **4,492** | | |

## Three or more blockers: all 290 units

Snapshot: `ef9c691284`, 2026-10-25 18:23 UTC. These are historical census
leads; follow-up starts at **Open / current-input verification pending**.
Paths retain the census spelling. Resolve current ownership after consolidation
before claiming a target, and update the follow-up with dated repair evidence.

**Game bytes** attribute unique, nonpadding bytes from the headline's game-code
partition. Credit the initial 50 and the other 35 one/two-blocker units first,
then these units in descending standalone byte contribution, breaking ties by
source path. Assign each remaining byte to its first unit in that order. This
reconciles overlapping owners and totals **95,078 bytes** across **290 units**.
A zero means no additional headline game bytes after provenance filtering,
clean-provider coverage and overlap attribution; the census blockers remain listed.
The initial shortlist above preserves the handoff's separate reported byte values.

Blocker key: **U** unresolved, **D** duplicate definitions, **C** COMDAT losers,
**A** address issues, **S** wrong selected providers. Counts come from the
snapshot's `reverse/link_status.csv`; byte attribution uses its measured ledger
through `tools/progress.py`'s provenance and retail-byte functions.

| Census source | Game bytes | Blockers | Follow-up |
| --- | ---: | --- | --- |
| `Code/gen_small/uw_gen_010.cpp` | 6,639 | 88 (U=88) | Open |
| `Code/gen_small/uw_gen_011.cpp` | 5,320 | 457 (U=457) | Open |
| `Code/gen_small/uw_gen_000.cpp` | 3,419 | 95 (U=95) | Open |
| `Code/gen_small/uw_gen_001.cpp` | 3,406 | 184 (U=184) | Open |
| `Code/gen_small/uw_gen_013.cpp` | 3,205 | 184 (U=184) | Open |
| `Code/gen_small/uw_gen_009.cpp` | 2,533 | 113 (U=113) | Open |
| `Code/GameEngine/Source/GameNetwork/ConnectionManager.cpp` | 2,520 | 49 (U=42, C=4, S=3) | Open |
| `Code/gen_small/uw_gen_014.cpp` | 2,489 | 271 (U=263, A=8) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlportVectorEraseRangeDeferred.cpp` | 2,464 | 3 (U=3) | Open |
| `Code/gen_small/uw_gen_006.cpp` | 2,448 | 103 (U=103) | Open |
| `Code/gen_small/uw_gen_012.cpp` | 2,227 | 100 (U=100) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/ww3d.cpp` | 1,750 | 20 (U=16, C=2, S=2) | Open |
| `Code/gen_small/uw_gen_004.cpp` | 1,644 | 6 (U=6) | Open |
| `Code/GameEngine/Source/GameLogic/Object/ObjectCreationList.cpp` | 1,499 | 8 (U=2, C=4, S=2) | Open |
| `Code/GameEngine/Source/GameClient/System/FXParticleSystem/ParticleModuleInfoCopyCtors.cpp` | 1,455 | 28 (U=28) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/texture.cpp` | 1,429 | 21 (U=21) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/W3DModelDrawModuleData.cpp` | 1,361 | 11 (U=10, C=1) | Open |
| `Code/Libraries/Source/STLport/Rva008312E0StringReplace.cpp` | 1,351 | 4 (C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.cpp` | 1,299 | 6 (U=2, C=2, S=2) | Open |
| `Code/gen_small/uw_gen_005.cpp` | 1,251 | 72 (U=72) | Open |
| `Code/GameEngine/Source/GameClient/MapUtil.cpp` | 1,182 | 24 (U=12, C=7, S=5) | Open |
| `Code/GameEngine/Source/GameClient/MapMetaDataCopyDeferred.cpp` | 941 | 7 (C=3, S=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/Rva0020EE29Clear.cpp` | 938 | 24 (U=23, C=1) | Open |
| `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogicCtorBfme.cpp` | 913 | 9 (U=6, C=3) | Open |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlay.cpp` | 899 | 17 (U=12, C=2, S=3) | Open |
| `Code/GameEngine/Source/Common/UserPreferencesDeferredIgnores.cpp` | 897 | 5 (C=3, S=2) | Open |
| `Code/GameEngine/Source/Common/RTS/PlayerCtorBFME2.cpp` | 841 | 6 (U=4, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp` | 800 | 22 (U=10, C=8, S=4) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate.cpp` | 749 | 14 (U=12, C=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/mixfile.cpp` | 748 | 9 (U=7, C=1, S=1) | Open |
| `Code/gen_small/uw_gen_003.cpp` | 703 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/Rva00170C0Siblings.cpp` | 692 | 48 (U=8, C=20, S=20) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar.cpp` | 647 | 8 (U=8) | Open |
| `Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldManagerCtor.cpp` | 585 | 5 (U=5) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_pod_malloc_deferred_copies.cpp` | 583 | 13 (C=6, S=7) | Open |
| `Code/GameEngine/Source/GameClient/FXList.cpp` | 581 | 9 (U=3, C=4, S=2) | Open |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp` | 572 | 9 (U=5, C=3, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate.cpp` | 564 | 13 (U=12, S=1) | Open |
| `Code/GameEngine/Source/GameClient/GUI/AptPlayerTooltipMap.cpp` | 550 | 4 (U=1, C=2, S=1) | Open |
| `Code/GameEngine/Source/GameClient/EvaMessageVectorAssign.cpp` | 538 | 6 (U=2, C=2, S=2) | Open |
| `Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread_Unresolved.cpp` | 517 | 9 (U=5, C=2, S=2) | Open |
| `Code/GameEngine/Source/GameClient/System/FXParticleSystem/ParticleModuleTemplateClones.cpp` | 501 | 6 (U=6) | Open |
| `Code/Libraries/Source/STLport/Rva008314E0StringReplace.cpp` | 499 | 4 (C=2, S=2) | Open |
| `Code/GameEngine/Source/Common/Rva005F422CDtor.cpp` | 495 | 9 (U=9) | Open |
| `Code/GameEngine/Source/Common/V3PolyDeferredCopyCtors.cpp` | 491 | 13 (U=12, C=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0039C415.cpp` | 457 | 11 (C=5, S=6) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/mesh.cpp` | 454 | 6 (U=3, C=2, S=1) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva001041BDASlot1.cpp` | 438 | 7 (U=6, C=1) | Open |
| `Code/GameEngine/Source/Common/RTS/ProductionPrerequisite.cpp` | 429 | 11 (U=2, C=6, S=3) | Open |
| `Code/GameEngine/Source/Common/Rva0026E836Derived.cpp` | 428 | 5 (U=3, A=2) | Open |
| `Code/GameEngine/Source/Common/System/CrateCreationEntryList.cpp` | 417 | 5 (U=1, C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_asciistring_record_deferred.cpp` | 413 | 12 (C=6, S=6) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdateCtor.cpp` | 409 | 9 (U=9) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva005205DA.cpp` | 402 | 5 (U=3, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva002BC47D.cpp` | 398 | 5 (U=3, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_pod_hash_bodies.cpp` | 391 | 14 (C=7, S=7) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/RailroadGuideAIUpdate.cpp` | 361 | 29 (U=22, C=6, S=1) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp` | 352 | 26 (U=14, C=7, S=5) | Open |
| `Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/Rva005E39F3Ctor.cpp` | 345 | 7 (U=7) | Open |
| `Code/Libraries/Source/WWVegas/WWMath/tcbspline.cpp` | 340 | 17 (U=15, C=1, S=1) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DGameClient.cpp` | 337 | 14 (U=10, C=2, S=2) | Open |
| `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildingCtor.cpp` | 327 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/decalmsh.cpp` | 326 | 6 (U=6) | Open |
| `Code/GameEngine/Source/Common/Rva004E0D67Dtor.cpp` | 325 | 4 (U=4) | Open |
| `Code/GameEngine/Source/Common/RvaMorphInitFamily.cpp` | 309 | 5 (U=5) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva001EBEAB.cpp` | 307 | 5 (U=3, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/BfmeConv1292DeferredWalkers.cpp` | 298 | 6 (U=6) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp` | 290 | 4 (U=3, C=1) | Open |
| `Code/GameEngine/Source/Common/VslotSmallBodiesAG_Rva00131CF2.cpp` | 286 | 10 (U=10) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Contain/OpenContain.cpp` | 283 | 13 (U=11, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva001DF2D3.cpp` | 281 | 4 (U=2, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva00215949.cpp` | 274 | 5 (U=3, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva001524F9.cpp` | 273 | 5 (U=3, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/RvaCloneDeferredValueReturns.cpp` | 272 | 10 (U=4, C=6) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva0017422D.cpp` | 269 | 5 (U=3, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_pod_noexc_deferred_copies.cpp` | 269 | 8 (C=4, S=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva000C225D.cpp` | 264 | 5 (U=3, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva003F53DA.cpp` | 263 | 5 (U=3, C=1, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp` | 261 | 11 (U=9, C=2) | Open |
| `Code/GameEngine/Source/Common/Rva007AEA2CArrayInits.cpp` | 249 | 10 (U=10) | Open |
| `Code/GameEngine/Source/Common/Rva006CBF40Deferred.cpp` | 245 | 14 (C=7, S=7) | Open |
| `Code/GameEngine/Source/GameLogic/AI/StateMachineDefineState.cpp` | 233 | 4 (C=2, S=2) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp` | 231 | 28 (U=17, C=6, S=5) | 2026-10-26 at 766153ce00: current eight rows/241 B and one EH graph pass; ordinary preview retains 17 U, 6 C, 5 S and 0 linked bytes. TU approval remains 0 rows/1 mixed seed; see [routing handoff](../reverse/attempt_support/aiupdate-tu-approval-20261026/readme.md), LINK-016. |
| `Code/Libraries/Source/WWVegas/WWLib/Rva00240230VectorInsertOverflow_Rva00541d10.cpp` | 231 | 8 (U=2, C=3, S=3) | Open |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleDtor_Unresolved.cpp` | 230 | 3 (C=3) | 2026-10-25: aa31e9bac4 and paired current-provider checks clear 222 B and 14 public consumers (1,212 B); LINK-014. Census pending. |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva00584405.cpp` | 225 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva001506BF.cpp` | 222 | 8 (C=4, S=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0015079D.cpp` | 222 | 8 (C=4, S=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0015087B.cpp` | 222 | 8 (C=4, S=4) | Open |
| `Code/gen_small/gthunks_000_admitted.cpp` | 220 | 69 (U=69) | Open |
| `Code/GameEngine/Source/GameClient/RegionDetailsStructuresIconCtor.cpp` | 217 | 4 (U=4) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdate.cpp` | 217 | 9 (U=7, C=2) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Weapon.cpp` | 214 | 22 (U=18, C=2, S=2) | Open |
| `Code/GameEngine/Source/Common/System/SaveGame/SaveMapPreviewCopy.cpp` | 209 | 5 (U=1, C=2, S=2) | Open |
| `Code/GameEngine/Source/Common/Rva0037BCC4DeferredCtorCRC.cpp` | 208 | 3 (U=2, C=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdateCtor.cpp` | 208 | 4 (U=1, C=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva003F318C.cpp` | 206 | 5 (U=3, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva0051F7AD.cpp` | 206 | 7 (U=3, C=2, S=2) | Open |
| `Code/GameEngine/Source/GameNetwork/native_network_BFMENetwork_Ctor.cpp` | 205 | 9 (U=7, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/RvaPayloadValueReturnsUnresolved.cpp` | 204 | 7 (U=3, C=4) | Open |
| `Code/GameEngine/Source/GameClient/GUI/Rva005776A7Ctor.cpp` | 203 | 8 (U=5, C=2, S=1) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp` | 198 | 20 (U=12, C=5, S=3) | Open |
| `Code/GameEngine/Source/GameLogic/LargeGroupAudio/LargeGroupAudioKeyList.cpp` | 191 | 3 (U=1, C=1, S=1) | Open |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarRva004C1B60_Rva00405DBC.cpp` | 189 | 5 (U=5) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_rva00587375_overflow.cpp` | 189 | 8 (U=2, C=4, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWSaveLoad/twiddler.cpp` | 187 | 11 (U=10, C=1) | Open |
| `Code/GameEngine/Source/Common/Rva00787C20HashOwnerDestructor.cpp` | 186 | 8 (U=4, C=2, S=2) | Open |
| `Code/GameEngine/Source/Common/Thing/ProductionPrerequisiteRecVectorInsertOverflow.cpp` | 183 | 3 (C=1, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva00501B33.cpp` | 183 | 5 (U=3, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/Rva00566695Assign.cpp` | 179 | 3 (C=2, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWMath/vehiclecurve.cpp` | 178 | 4 (U=3, C=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Damage/EvacuateDamageCtorModuleFactoryBody.cpp` | 177 | 5 (U=1, C=2, S=2) | Open |
| `Code/GameEngine/Source/GameLogic/System/GlobalWeatherSystemCtorDeferred.cpp` | 173 | 4 (U=4) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDrawCtor.cpp` | 164 | 3 (U=1, C=2) | Open |
| `Code/GameEngine/Source/Common/System/CDManager.cpp` | 154 | 9 (U=7, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp` | 152 | 27 (U=23, C=2, S=2) | Open |
| `Code/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp` | 151 | 17 (U=16, S=1) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DAnimationInfoVectorInsert.cpp` | 149 | 4 (C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva004F8C16.cpp` | 149 | 10 (U=4, C=3, S=3) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogic.cpp` | 145 | 6 (U=6) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_pod8_resize_byvalue.cpp` | 143 | 6 (C=3, S=3) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehavior.cpp` | 142 | 7 (U=7) | Open |
| `Code/GameEngine/Source/GameLogic/LivingWorld/SplineCameraParseINIBlock.cpp` | 140 | 5 (U=4, C=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00218E09.cpp` | 140 | 7 (U=3, C=2, S=2) | Open |
| `Code/GameEngine/Source/Common/Rva0019D850NestedVectorRelease_Rva002bc339.cpp` | 137 | 4 (C=2, S=2) | Open |
| `Code/GameEngine/Source/Common/Rva002D22CAInit.cpp` | 135 | 7 (U=7) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00332613.cpp` | 135 | 7 (U=3, C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00337D21.cpp` | 135 | 7 (U=3, C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/shattersystem.cpp` | 133 | 8 (U=3, C=2, S=3) | Open |
| `Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/ArmyHeroIconCtor.cpp` | 130 | 10 (U=10) | Open |
| `Code/GameEngine/Source/GameLogic/Object/PartitionManager.cpp` | 129 | 15 (U=12, C=1, S=2) | Open |
| `Code/GameEngine/Source/Common/BfmeConv881O1.cpp` | 127 | 4 (U=2, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/DamageFX.cpp` | 126 | 7 (U=4, C=2, S=1) | Open |
| `Code/GameEngine/Source/Common/Rva006C3CC0Cluster.cpp` | 125 | 3 (U=1, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/Rva006DE1A0Finish.cpp` | 125 | 3 (U=3) | Open |
| `Code/GameEngine/Source/Common/BfmeConv1950.cpp` | 118 | 4 (U=4) | Open |
| `Code/GameEngine/Source/Common/Thing/ThingFactory.cpp` | 85 | 13 (U=6, C=6, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/FlammableUpdate.cpp` | 117 | 6 (U=4, C=1, S=1) | Open |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp` | 116 | 61 (U=49, C=6, S=6) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/dynamesh.cpp` | 113 | 28 (U=17, C=8, S=3) | Open |
| `Code/GameEngine/Source/Common/PAVectorEraseRangeFamily003AF.cpp` | 112 | 4 (U=2, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/Rva00196D90MemberConstructor_Rva0032bde7.cpp` | 112 | 6 (C=3, S=3) | Open |
| `Code/GameEngine/Source/Common/R5VectorDtorEHFramedPolymorphic_Rva005de870.cpp` | 111 | 7 (U=2, C=2, S=3) | Open |
| `Code/GameEngine/Source/Common/Rva005BA1FDCtor.cpp` | 108 | 7 (U=7) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/HeightMap.cpp` | 107 | 30 (U=28, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/RTS/Rva000D3FA0Destructor.cpp` | 103 | 4 (C=2, S=2) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankTruckDraw.cpp` | 103 | 16 (U=12, C=3, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/JetAIUpdate.cpp` | 101 | 53 (U=47, C=3, S=3) | Open |
| `Code/GameEngine/Source/Common/Rva00415704Ctor.cpp` | 100 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_introsort_loop_s4sortelem20.cpp` | 98 | 3 (U=3) | Open |
| `Code/GameEngine/Source/Common/System/SaveGame/Rva0052CD81Finish.cpp` | 96 | 4 (C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_istream.cpp` | 90 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva003F40EF.cpp` | 85 | 5 (U=5) | Open |
| `Code/GameEngine/Source/Common/ConstIntGettersAddr.cpp` | 84 | 1042 (A=1042) | Open |
| `Code/GameEngine/Source/Common/BfmeConv1879.cpp` | 82 | 5 (U=5) | Open |
| `Code/GameEngine/Source/Common/RTS/PlayerRelationMapCtor.cpp` | 81 | 3 (C=2, S=1) | Open |
| `Code/GameEngine/Source/Common/Rva001F4B01Ctor.cpp` | 80 | 13 (U=12, C=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva002BFA86.cpp` | 80 | 4 (U=2, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/collect.cpp` | 79 | 20 (U=14, C=5, S=1) | Open |
| `Code/GameEngine/Source/Common/System/SaveGame/AerialPathfinder.cpp` | 75 | 3 (U=2, C=1) | Open |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanGameOptionsMenu.cpp` | 75 | 28 (U=27, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00214B22.cpp` | 73 | 7 (U=5, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva005E2857.cpp` | 73 | 7 (U=5, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva003609F7.cpp` | 73 | 4 (C=2, S=2) | Open |
| `Code/GameEngine/Source/Common/S4StlSortHelpers.cpp` | 71 | 21 (U=13, C=5, S=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00212A16.cpp` | 68 | 9 (U=3, C=3, S=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva0002CCC3.cpp` | 67 | 4 (U=2, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00218FC2.cpp` | 67 | 4 (U=4) | Open |
| `Code/GameEngine/Source/Common/RTS/ScoreKeeperPerFrameStatsDefaultResizeDeferred.cpp` | 66 | 4 (U=3, C=1) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva0008EF3FProductCtor_Unresolved.cpp` | 66 | 50 (U=50) | Open |
| `Code/GameEngine/Source/Common/Rva005CEB57Ctor.cpp` | 62 | 3 (U=1, C=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva002F0B8A.cpp` | 61 | 4 (C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva002F0BB5.cpp` | 61 | 4 (C=2, S=2) | Open |
| `Code/GameEngine/Source/Common/MoneyVectorPushBack.cpp` | 59 | 8 (U=3, C=3, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlContainerRva0073E4C0.cpp` | 59 | 5 (U=3, C=1, S=1) | Open |
| `Code/GameEngine/Source/GameClient/SelectionInfo.cpp` | 58 | 4 (U=2, C=2) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/ringobj.cpp` | 57 | 8 (U=7, C=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00058A86.cpp` | 57 | 4 (U=2, C=1, S=1) | Open |
| `Code/GameEngine/Source/GameClient/InGameUI.cpp` | 55 | 9 (U=5, C=3, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Create/LockWeaponCreate.cpp` | 55 | 4 (U=2, C=2) | Open |
| `Code/GameEngine/Source/Common/RTS/Player.cpp` | 52 | 33 (U=24, C=6, S=3) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/sphereobj.cpp` | 51 | 12 (U=7, C=5) | Open |
| `Code/GameEngine/Source/Common/Rva003C2F40TreeCtor.cpp` | 50 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WWMath/curve.cpp` | 48 | 5 (U=3, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/WeaponStore.cpp` | 47 | 3 (U=2, C=1) | Open |
| `Code/GameEngine/Source/Common/Thing/ProductionPrerequisiteAssign.cpp` | 45 | 4 (C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva005FE3DC.cpp` | 45 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_unguarded_insertion_sort_s4sortelem20.cpp` | 45 | 3 (U=2, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_numpunct_virtuals.cpp` | 44 | 4 (U=4) | Open |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/OCLSpecialPower.cpp` | 40 | 3 (U=2, C=1) | 2026-10-25: current-provider preview still has protected SpecialPower dtor, findPositionAround and FindPositionOptions blockers; LINK-014. |
| `Code/Libraries/Source/WWVegas/WW3D2/decalsys.cpp` | 39 | 8 (U=8) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/ParkingPlaceBehavior.cpp` | 38 | 15 (U=8, C=6, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdate.cpp` | 37 | 10 (U=8, C=2) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/StickyBombUpdate.cpp` | 36 | 15 (U=13, C=1, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/FlightDeckBehavior.cpp` | 35 | 14 (U=8, C=5, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva002CEFAA.cpp` | 35 | 3 (U=3) | Open |
| `Code/gen_small/thunks_000_admitted.cpp` | 35 | 7 (U=7) | Open |
| `Code/GameEngine/Source/Common/BfmeConv890.cpp` | 34 | 5 (U=5) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Locomotor.cpp` | 34 | 8 (U=4, C=2, S=2) | Open |
| `Code/GameEngine/Source/Common/Audio/AudioManagerAdjustPriorityAndVolume.cpp` | 33 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00423EB0.cpp` | 33 | 4 (C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00555D32.cpp` | 33 | 4 (C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00555D53.cpp` | 33 | 4 (C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/wwfont.cpp` | 33 | 4 (U=4) | Open |
| `Code/GameEngine/Source/GameClient/GUI/Rva0057621ACtor.cpp` | 32 | 15 (U=11, C=3, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/LaserUpdate.cpp` | 32 | 8 (U=6, C=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00162860.cpp` | 32 | 3 (U=1, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/BfmeConv821.cpp` | 31 | 6 (U=6) | Open |
| `Code/GameEngine/Source/Common/BfmeConv907.cpp` | 31 | 8 (U=8) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_rva005de9c4_ctor.cpp` | 31 | 6 (U=1, C=2, S=3) | Open |
| `Code/gen_small/uw_gen_007.cpp` | 31 | 4 (U=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00013490.cpp` | 30 | 4 (U=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva004157BB.cpp` | 29 | 4 (U=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva00464431.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva00540053.cpp` | 29 | 4 (U=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00053E34.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0007EA02.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva000B6569.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva000B67BC.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva001DD339.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva001DD356.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00215641.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva002CF594.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0030B378.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0038151E.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva003F447F.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00428421.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00469C85.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva005FE089.cpp` | 29 | 3 (U=1, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB03Deferred.cpp` | 28 | 3 (U=2, C=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehavior.cpp` | 28 | 4 (U=2, C=1, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/WeaponSet.cpp` | 28 | 7 (U=4, C=1, S=2) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp` | 28 | 30 (U=30) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00406B1D.cpp` | 28 | 4 (U=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00406CB7.cpp` | 28 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva0042D4EB.cpp` | 28 | 4 (U=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva0044BE1D.cpp` | 28 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00482A4D.cpp` | 28 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00551B02.cpp` | 28 | 4 (U=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva005838DC.cpp` | 28 | 4 (U=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva005AFEDB.cpp` | 28 | 4 (U=4) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva005CE7CE.cpp` | 28 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva005DA663.cpp` | 28 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva005E96DC.cpp` | 28 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00627B10.cpp` | 28 | 6 (U=4, C=1, S=1) | Open |
| `Code/GameEngine/Source/Common/R5VectorDtorEHFramedPolymorphic.cpp` | 27 | 15 (U=4, C=5, S=6) | Open |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/OptionsMenu.cpp` | 27 | 8 (U=8) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva0033A7DC.cpp` | 27 | 5 (U=5) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva0056DDF5.cpp` | 27 | 5 (U=5) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_valarray_int.cpp` | 27 | 4 (U=1, C=2, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva004DA329.cpp` | 25 | 5 (U=3, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva005F35ED.cpp` | 25 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWMath/lookuptable.cpp` | 24 | 4 (U=2, C=2) | Open |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp` | 23 | 12 (U=11, C=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/HelicopterSlowDeathUpdate.cpp` | 22 | 13 (U=12, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/PhysicsUpdate.cpp` | 21 | 19 (U=13, C=5, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW6Rva0016DEC0.cpp` | 21 | 3 (U=1, C=1, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdate.cpp` | 16 | 14 (U=13, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DeliverPayloadAIUpdate.cpp` | 14 | 25 (U=17, C=4, S=4) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/AnimationSteeringUpdate.cpp` | 14 | 6 (U=4, C=2) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/HordeUpdate.cpp` | 14 | 5 (U=5) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/DumbProjectileBehavior.cpp` | 13 | 22 (U=12, C=6, S=4) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/EMPUpdate.cpp` | 13 | 6 (U=6) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/HackInternetAIUpdate.cpp` | 10 | 23 (U=21, C=1, S=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/SpectreGunshipUpdate.cpp` | 10 | 20 (U=16, C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/texproject.cpp` | 10 | 12 (U=11, C=1) | Open |
| `Code/GameEngine/Source/GameLogic/Object/Update/MobMemberSlavedUpdate.cpp` | 8 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WW3D2/light.cpp` | 6 | 3 (U=3) | Open |
| `Code/GameEngine/Source/Common/BfmeConv892_Rva004C121B.cpp` | 0 | 4 (U=2, C=1, S=1) | Open |
| `Code/GameEngine/Source/GameClient/GUI/Rva00576DF1Ctor.cpp` | 0 | 11 (U=8, C=2, S=1) | Open |
| `Code/GameEngineDevice/Source/MilesAudioDevice/Rva0006047CSeq.cpp` | 0 | 5 (U=5) | Open |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DVideoBuffer.cpp` | 0 | 7 (U=5, C=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva000AF1C2.cpp` | 0 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva000B0298.cpp` | 0 | 7 (U=5, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva001DE3E3.cpp` | 0 | 7 (U=3, C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva001FDEBC.cpp` | 0 | 7 (U=3, C=2, S=2) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva0022DCDA.cpp` | 0 | 7 (U=5, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva0046AA69.cpp` | 0 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva004F715B.cpp` | 0 | 5 (U=3, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva004F7D7F.cpp` | 0 | 7 (U=5, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva005243FA.cpp` | 0 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva0052BBD7.cpp` | 0 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00569450.cpp` | 0 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00577EB2.cpp` | 0 | 7 (U=5, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00587752.cpp` | 0 | 3 (U=3) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva005AE78A.cpp` | 0 | 3 (U=1, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva005B09D8.cpp` | 0 | 6 (U=4, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva005F9813.cpp` | 0 | 7 (U=5, C=1, S=1) | Open |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0020F0B8.cpp` | 0 | 5 (U=5) | Open |
| `Code/gen_small/fam_003_Rva0028688a.cpp` | 0 | 7 (U=5, C=1, S=1) | Open |
| **Total: 290 units** | **95,078** | | |

## Broader workstreams

These scopes can overlap the targets above. Their verification and remaining
prerequisites are maintained in the [obstacle register](linking_obstacles.md).

| Workstream | Reported bytes | Latest recorded scope/status |
| --- | ---: | --- |
| LINK-001: WeightInfo graphics units | 45,204 | 30 units cleared in ordinary preview; census pending |
| LINK-007: VP6 storage | 17,413 | Landed; fixed-comparison closed-strict gain |
| LINK-007: filter adjacency | 2,369 | Landed; fixed-comparison closed-strict gain |
| LINK-007: scaler coefficients | 1,739 | Landed; fixed-comparison closed-strict gain |
| LINK-009: split-identity destructors | 661 | Trial proven; identity merge or admission decision pending |
| LINK-011: four units | 297 | Ordinary preview cleared; census pending |

The INI repair [0c7ebc35a7](https://github.com/Open-BFME/Open-BFME-2/commit/0c7ebc35a7)
is tracked under LINK-004: 2,989 authored bytes cleared in a bounded ownership
diagnostic, with census confirmation pending. It sits outside the 50-unit list.

A newer-census lead, `Rva00598E85Ctor.cpp` (177 bytes), was checked on
2026-10-26 at `d7fa8a31bf`: current INI and lower-bound provider objects clear
its sole selected-copy blocker in the ordinary preview. This confirms the
existing INI repair; no new source or census gain is claimed. See the
[AI consumer evidence](../reverse/attempt_support/ai-constructor-current-provider-20261026.md)
and LINK-004. It is outside the historical snapshot totals below.

## Snapshot totals

| Category | Units | Reported matched bytes |
| --- | ---: | ---: |
| Fresh one-blocker candidates | 16 | 2,809 |
| Previously worked one-blocker candidates | 16 | 12,007 |
| Harder one-blocker candidates | 8 | 1,661 |
| Listed two-blocker candidates | 10 | 33,987 |
| **Initial shortlist** | **50** | **50,464** |

The committed census contains **85 units with one or two blockers** (40 with
one, 45 with two). The handoff reports **55,142 matched bytes** for that wider
set. Its remaining 35 units are listed above with **4,492 reconciled game
bytes**; the handoff's reported-byte subtraction was 4,678.
The three largest listed targets total **30,381 bytes**, about **60.2%** of the
listed bytes. Size ranks investigation opportunities; current evidence and
shared-provider dependencies determine the next repair.


### Complete headline reconciliation

This uses the census's unique, nonpadding game bytes rather than the initial
handoff's reported matched-byte values.

| Scope | Units | Unlinked game bytes |
| --- | ---: | ---: |
| Initial shortlist | 50 | 50,028 |
| Remaining two-blocker table above | 35 | 4,492 |
| Three-or-more-blocker table above | 290 | 95,078 |
| Coverage remainder outside represented rows | - | 14 |
| **Census total** | **375** | **149,612** |
