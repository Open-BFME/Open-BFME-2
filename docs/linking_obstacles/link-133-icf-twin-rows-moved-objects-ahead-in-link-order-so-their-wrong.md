### LINK-133: ICF-twin rows moved objects ahead in link order, so their wrong COMDAT copies became the kept copy

Update (2026-11-04, codex3): the horde TU merge guard rejected `Rva000796CBPairInit.cpp` because composition would break another unit's `allocator<const LocomotorTemplate *>::allocate` copy; that donor remains separate. Inspect the selected allocator and emitted destination copy before retrying. The parser-only merge passes the guard; [scope, index and verification evidence](../../reverse/attempt_support/horde-module-data-parser-consolidation-20261104-codex3.md).

Status: Placement cause cleared by census rule `retail-truth-5` (re-baseline at `840db2d676`); 56 newly exposed units open as source repairs (below). Updated: 2026-10-29.

2026-10-28 consumer recheck at `6d7a215d6b`, refreshed index `d92e7e6635`:
`WWLib/Rva0006C995Insert.cpp` still fails solely on the selected pointer-set
`insert` and `insert_unique` copies. The existing CollectKeys provider/context
prerequisite remains; no unchanged suppression trial was repeated.

Checkbox consumer cleanup (2026-10-28, base `7c93954985cd`, index `d92e7e6635`):
W3DCheckBox.cpp already previews LINKS with the current renderer repair.
Removing its unused renderer include preserves all three rows and 39 retained
COMDAT fingerprints, while removing two helpers and four unused dependencies.
The explicit path to the same DisplayString shim enables a strict reusable
receipt. Paired preview remains LINKS for 948 authored bytes; the renderer's
Add_Quad blocker remains. This is dependency cleanup, not a new linking gain.
The outgoing audit is INCONCLUSIVE (older index; missing current receipt for
Common/0CreateAHeroManager21FE49.cpp). Carry this removed-helper scope into
the next census; full consumer and runtime verification remain pending.
[Checks and evidence](../../reverse/attempt_support/checkbox-dependencies-20261028-codex.md).

Status: Open; Render2DSentenceDrawBFME2.cpp repair landed / awaiting census. Updated: 2026-10-28; inspected revision: `3868d198bf`; index 41c28839bf (census c8734bec0c).
Status: Duplicate of LINK-132 (same cause, filed in parallel); new results are tracked under LINK-132, and this entry keeps the whole-ledger simulation history. Updated: 2026-10-28; inspected revision: `1e9d0f5a75`; index 73061d9452.

Evidence / affected units: `link_census.link_order` places each object by the lowest RVA of any of its rows. The post-census ICF-twin row commits (760b73e4df, a0c3cb8b6a, 991302b1d0, 547b34bc57, 34fbfc03e0) gave several units a row at a low folded address (an 8-byte destructor fold such as 0x00001E13, 0x0006C94B or 0x0007FAB3), so those objects now link far earlier than at the census. Where such an object carries a non-retail COMDAT copy, that copy is now the first one in link order: link.exe keeps it, and `judge_selected` charges every unit touching the name. Ordinary `link_check` cannot see this (it keeps the census positions and only checks the units passed). A scratch whole-ledger simulation (all 21,940 current objects in current `link_order`, census `check_object`/`wrong_selected` rules, census `/MAP` exceptions remapped as `--current-ledger` does) finds 131 census-linked units, 279,690 B, failing only for this reason:

| Mover (census → current position; fold row) | Copies now kept | Units / census bytes |
| --- | --- | ---: |
| `WW3D2/Render2DSentenceDrawBFME2.cpp` (4072 → 27; `??1RendererDataStruct@Render2DSentenceClass@@QAE@XZ` 0x00001E13) | `_floorf` (its /G7 `sub esp,8`/`add esp,8` form, 20 B; retail is the 18 B `push ecx`/`pop ecx` form), `??_EPendingSurfaceStruct@Render2DSentenceClass@@QAEPAXI@Z`, `??4W3DRadarResetSurface@@QAEAAV0@ABV0@@Z` (both /G7-scheduled), `Add_Quad` (unknown) | 81 / 202,107 (pathfinder.cpp 50,353, seglinerenderer.cpp 18,478, StreakRendererRenderStreak.cpp 14,007, gridcull.cpp 11,117, ...) |
| `SkirmishAI/AIBuilder.cpp` (17176 → 1975; `??1RvaVector@@QAE@XZ` 0x0007FAB3) | `vector<Object *>` destructor, `push_back`, `_M_insert_overflow` | 28 / 55,572 (HordeContainIface11CSlots.cpp 23,871, GameEngineInit.cpp 9,424, ...) |
| `assetmanager/Rva00622290CollectKeys.cpp` (20924 → 1509; `??1AssetSetGroup@@QAE@XZ` 0x0006C94B) | `set<Rva001408C0Target *>::insert`, `insert_unique`; its own `find<int>` | 15 / 15,338 |
| `GUI/window_video_manager.cpp` (11910 → 3933; hashtable `find` 0x00148B27) | WindowVideo hashtable destructor | 2 / 2,250 |
| `WW3D2/BfmeFVFDescriptorVertexDeclaration.cpp` (4465 → 3879; `vector<ICoord2D>` dtor 0x00142D70) | `vector<ICoord2D>::_M_insert_overflow` | 1 / 1,806 |
| `RTS3DSceneVisibilityCheck.cpp` (1603 → 1576; `slist<int>` dtor 0x0006FB50) | `slist<int>` constructor | 2 / 986 |
| `GUI/ChatWindowsLan.cpp` (20005 → 1618; `??1NativeSelectionSet` 0x00073116) | `??0Rva002EE9B7@@QAE@XZ` (unknown) | 1 / 877 |
| `OpaqueScalarDeletingDtorsB13.cpp` (18901 → 1851; 0x0007FAB3) | `??_GBaseA@@UAEPAXI@Z` (unknown) | 1 / 754 |

In every case the next definer in current link order holds the retail-proven copy, so removing (or correcting) the mover's copy is enough. Five more tiny units (atlbasemodule.cpp `___ImageBase`, four `__imp_` node-allocator users, 440 B) fail the same way in the ordinary preview too: model artifacts, not regressions.

Completed: `Render2DSentenceDrawBFME2.cpp` (2026-10-28, claude2): `extern "C" { static float __cdecl floorf(float); }` ahead of the first include (it must precede math.h's inline definition, else C2375) stops the unit publishing `_floorf`; `W3DRadarResetSurface::operator=` is import-inline like its constructor (every use inlines; the object has no `__imp_` reference); declaration-only `VectorClass<PendingSurfaceStruct>::Clear`/`Resize` specializations stop the unused virtuals' `delete[]` from emitting `??_EPendingSurfaceStruct` (only `.debug$F` referenced it). All 12 rows still byte-match; the two Unwind rows' `object-symbol=` hints follow the renumbered labels. Preview with the census index 41c28839bf: of the 125 census units failing only by wrong_selected, plus this unit, 80 link (199,977 B), among them pathfinder.cpp, seglinerenderer.cpp, gridcull.cpp; the rest fail on the AIBuilder/CollectKeys/slist copies below. The unit itself still does not link: its visible `Add_Quad` copy references `_g_BfmeRender2DZ`, a second name `/alternatename`-bound to `?g_Va00DEC49C@@3MA` (Rva00118B50State.cpp), so its relocations are unproven, and as first copy in link order it now loses (2,448 B). Using the owner `g_Va00DEC49C` links it (preview: LINKS) but adds two address_global occurrences the register does not grant; it needs the global's real name, or an admitted rewrite, then the alias can go.

Trial: `Rva00622290CollectKeys.cpp` with decl-only `insert`/`insert_unique` specializations changes LoadAsset's frame and collectKeys' binding (6/14 fail); a decl-only `find<int>` member-template specialization crashes cl (C1001). Reverted and logged (re_attempts, 0x00622290). Trial: `RTS3DSceneVisibilityCheck.cpp` slist<int> allocator constructor: an import-inline specialization inlines `_Slist_base` where retail calls the 18-byte row 0x00071233; a decl-only specialization calls it but grows Visibility_Check's frame (0x60 to 0x64) and moves the allocator temporary. Reverted and logged (re_attempts, 0x00071245).

Consumer recheck (2026-10-28, base `49397dc664`, index `41c28839bf`): the default-picked `W3DMouse_releaseD3DCursorTextures.cpp` needs no local repair when previewed with the existing Render2DSentenceDrawBFME2.cpp changes: it reports LINKS for 121 authored bytes. The provider still fails on its unproven Add_Quad copy. This confirms only that consumer's preview; LINK-132/LINK-133 and census confirmation remain open. [Session handoff](../../reverse/attempt_support/xfer-header-blockers-20261028-codex.md).

Remaining / next check:
- `Render2DSentenceDrawBFME2.cpp`: `_floorf`, `operator=` and `??_EPendingSurfaceStruct` repaired (above); carry the 80 previewed units into the next census. Its own link waits on the `g_Va00DEC49C`/`_g_BfmeRender2DZ` naming.
- `AIBuilder.cpp` (claimed by another seat): its `vector<Object *>` copies must equal retail or not be emitted; the next definer (GenericObjectCreationNuggetReallyCreate.cpp, 2709) is retail.
  - 2026-10-28, base `7e5426520a`, index `41c28839bf`: the current
    `GameLogicDestructor.cpp` preview also fails on the selected
    `vector<Object *>` destructor. Its 30-row unit remains blocked by this
    same provider selection; the previously documented AIBuilder suppression
    trials were not repeated. Recheck this consumer after the provider or an
    approved link-order rebaseline changes. Census confirmation is pending.
  - 2026-10-28 (claude-opus-5-5, index 41c28839bf): both AIBuilder-side routes fail for the destructor. Retail's
    `~vector<Object *>` is the 5-byte `jmp 0x001F1609` (0x001F22A3); AIBuilder emits its out-of-line copy only for
    `checkForNewUpgrades`' unwind funclets, while retail inlines the destructor (with the base cleanup) in that body.
    (1) A declaration-only `~vector` specialization stops the copy but makes the body call it (FAIL 1/29).
    (2) An explicit `~vector` defined under `#pragma inline_depth(0)` still calls the base cleanup through
    `__imp_` (the unit's import-inline `~_Vector_base`) and changes `checkForNewUpgrades`' register allocation
    (`edi`/`esi` swap from 0x004ECACF; FAIL 1/29). Both reverted. Retail discarded AIBuilder's own copy too, so this
    unit cannot supply the kept copy: it needs the `link_order` rule question below, or a fold row that does not
    move AIBuilder ahead of GenericObjectCreationNuggetReallyCreate.cpp. Served unit
    `GenericObjectCreationNuggetPositionCreate.cpp` (535 B, wrong_selected only) waits on this.
  - 2026-10-28 (claude-opus-5-5, index 41c28839bf): `WWLib/StlportVectorPushBackSiblings.cpp` (388 B, the
    retail `vector<Object *>::push_back` owner 0x001F211B) is blocked only by `push_back` and
    `_M_insert_overflow` selection: AIBuilder.obj (place 1996) holds the first, wrong copy of both. Same
    prerequisite; no trial repeated.
- Rule question for maintainers: 675 objects are positioned by an ICF-alias row (an address another object's row also claims), many already at the census. If `link_order` ignored such alias rows, objects would sit where their own code is; that is a census rule change (`tools/census_rebaseline.py`), not a seat edit. Until then, a commit that adds a low-address fold row to a unit should first check the unit's other COMDAT copies against the units it overtakes.

Clearance: none. Census confirmation: the next census should show these losses unless the movers are repaired first.

#### Decision and census confirmation (2026-10-29, retail-truth-5)

Maintainer decision: `link_order` ignores ICF-alias rows, recorded as the census
rule change `retail-truth-5` through `tools/census_rebaseline.py`. Definition
(`link_census.code_places`, shared by `link_check.link_rank`, tu_skeleton's merge
guard and `allowed_symbols`/`dup_defs`): an object is placed by the lowest
retail RVA of its rows whose address no other object's row also claims; an
object all of whose rows are shared keeps its lowest row. This entry's
shared-address definition is used, not `fold-proof=` alone: 1,136 `fold-proof=`
rows move 476 objects, while 2,313 shared rows carry no marker (AIBuilder's
0x0007FAB3 row among them). 954 of 21,607 objects move in the ledger at
`0d26afd6d2`.

Tools: `0d26afd6d2` (rule, `retail-truth-4` kept as PREVIOUS_RULES, measured by
its own `link_census.py` in a separate process), `51627be276` (that process's
pool pickling fix). Re-baseline row `93614acd90`: one census of `840db2d676` on srv1, both
rules on the same 21,503 objects (digest `1ace094a05f389db`), the previous rules
by `64db12ad35:tools/link_census.py`:

| Rules | Files linked | LINKED | Authored |
| --- | ---: | ---: | ---: |
| retail-truth-4 | 21,282 | 7,604,932 | 7,144,051 |
| retail-truth-5 | 21,253 | 7,586,952 | 7,126,071 |

At this commit retail-truth-4 already recovered most of the 2026-10-28 loss
(7,384,253 at `54b83e4f69`): those units were repaired at source before the
re-baseline (above), not by the rule. The rule itself links 27 more units
(36,835 census bytes in the index) and 56 fewer (56,898); the row's LINKED
net is −17,980 B. Proven-wrong
selected names rise from 159 to 191.

Gained (the movers this entry names, and their consumers): `Common/GameEngineInit.cpp`, `GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/TargetlessTactics/AIStructureCreepTactic.cpp`, `assetmanager/Rva00622290CollectKeys.cpp`, `GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/AITactic.cpp`, `GameLogic/Object/GenericObjectCreationNuggetReallyCreate.cpp`, `WWVegas/WW3D2/Render2DSentenceDrawBFME2.cpp`, `GameLogic/SkirmishAI/AIBuilder.cpp`, `GameLogic/SkirmishAI/AISpecialPowers/AISPecialPowerTargetAoE.cpp`, `GameLogic/SkirmishAI/AIStatCollector/AIStatCollector.cpp`, `GameLogic/Object/SpecialPower/ManTheWallsSpecialPower.cpp`, `GameLogic/Object/Update/ProductionUpdate.cpp`, `GameLogic/System/GameLogicDestructor.cpp`, `GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/TargetlessTactics/AIRoamingDefenseTacticRoam.cpp`, `GameLogic/Object/GenericObjectCreationNuggetPositionCreate.cpp`, `GameLogic/Object/SpecialPower/SiegeDeployHordeInitiate.cpp`, `GameLogic/SkirmishAI/AITeamBuilder/AITeamBuilder_checkIdleTeams.cpp`, `WWVegas/WWLib/StlportVectorPushBackSiblings.cpp`, `GameLogic/System/LivingWorld/Rva002B8573Method.cpp`, `GameLogic/ScriptEngine/ScriptActions_doTeamPartialUseCommandButton.cpp`, `GameLogic/Object/GenericObjectCreationNuggetWaypointPick.cpp`, `GameLogic/SkirmishAI/AISpecialPowers/AIRva005D8B0BCheck.cpp`, `GameLogic/AI/SquadGetAllObjectsAndRemoveDead.cpp`, `WWVegas/WWLib/StlportVectorObjectPtrInsertOverflow.cpp`, `GameLogic/Object/SpecialPower/SplitHordeSpecialPower_doSpecialPower.cpp`, `GameLogic/Object/GenericObjectCreationNuggetRequirements_Create.cpp`, `Common/RTS/GameLogic_QueueForNotifyPathfindCellChanged.cpp`, `GameLogic/Object/Rva004E00BA.cpp`.

Newly exposed (source-repair leads, not regressions): units retail-truth-4
linked only because an object that a shared row placed early happened to hold
retail's copy. At its own code it now follows a definer whose copy is not
retail's. Example: `??0?$vector@VAsciiString@@…@ABV01@@Z` (28 units): BfmeObject476Copy.cpp
was placed by the shared `hashtable::_M_next_size` fold at 0x0005571B and now sits at
0x001FD293, so CreateAHeroDataCopy.cpp (0x00069F75) is the first definer and its copy
is wrong. The repair is the same as for this entry's movers: make the first
definer's copy retail's or stop it emitting the copy. Charged names are the
census index's for the retail-truth-5 row (first name shown; … = more):

**2026-10-29 `vector<AsciiString>` copy ctor cleared (ordinary preview, census
index `840db2d676`, inspected `5325e2b3bd`):** 9554d91a12 made
CreateAHeroDataCopy.cpp call the rowed retail copy constructor (0x000BC07E), so
the first definer no longer emits a wrong copy. `link_check.py` on
CreateAHeroDataCopy.cpp plus the 24 table units below that still exist under
their names (BfmeObject476Copy … Rva00403927Assign): 25 of 25 link,
0 -> 17,728 B. Census confirmation: awaiting. The other rows of this table are
untouched by this note.

| Unit | Census bytes | Charged COMDAT |
| --- | ---: | --- |
| `GameLogic/AI/AIPlayerTeamBuild.cpp` | 9,120 | comdat_losers 2: `?_M_create_node@?$list@PAVTeamPrototype@@V?$allocator@PAVTeamPrototype@@@_STL@@@_STL@@IAEPAU?$_List_node@PAVTeamPrototype@@@2@ABQAVTeamPrototype@@@Z` … |
| `GameClient/FXParticleSystemFactories.cpp` | 4,099 | wrong_selected 25: `?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?GPU_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?GPU_DRAW_MODULE_NAME@2@3QBDBVGpuDrawModule@2@VGpuDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVGpuDrawModuleTemplate@2@XZ` … |
| `GameClient/FXParticleSystemModules.cpp` | 3,856 | wrong_selected 25: `?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?GPU_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?GPU_DRAW_MODULE_NAME@2@3QBDBVGpuDrawModule@2@VGpuDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVGpuDrawModuleTemplate@2@XZ` …; comdat_losers 2: `??_G?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAXI@Z` … |
| `GameClient/GUI/GameWindowManagerScript.cpp` | 2,865 | wrong_selected 1: `?erase@?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@QAE?AU?$_List_iterator@PAVGameWindow@@U?$_Nonconst_traits@PAVGameWindow@@@_STL@@@2@U32@@Z` |
| `Common/BfmeObject476Copy.cpp` | 2,519 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `GameLogic/System/ObjectFilter.cpp` | 2,376 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `GameClient/GUI/GUICallbacks/Apt/AptMessengerOnlineResponse.cpp` | 2,359 | wrong_selected 1: `??R?$less@H@_STL@@QBE_NABH0@Z` |
| `Common/Thing/ThingTemplateConstructor.cpp` | 1,881 | wrong_selected 1: `?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@_STL@@@_STL@@QBEPAU?$_Rb_tree_node@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@2@IPBX@Z`; comdat_losers 1: `??_7ThingTemplate@@6B@` |
| `GameClient/GUI/ProcessAnimateWindow.cpp` | 1,869 | comdat_losers 2: `?cos@@YAMM@Z` … |
| `GameLogic/Map/SidesList_sidesInfo.cpp` | 1,714 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `GameLogic/Map/SidesListCastleBuildLists.cpp` | 1,596 | wrong_selected 1: `??$__uninitialized_copy@PBV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@PAV12@@_STL@@YAPAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@0@PBV10@0PAV10@ABU__false_type@0@@Z` |
| `WWVegas/WWLib/stlport_deque_e12_o1.cpp` | 1,526 | wrong_selected 2: `??$copy@U?$_Deque_iterator@UBfmeE12@@U?$_Const_traits@UBfmeE12@@@_STL@@@_STL@@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@2@@_STL@@YA?AU?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@0@U?$_Deque_iterator@UBfmeE12@@U?$_Const_traits@UBfmeE12@@@_STL@@@0@0U10@@Z` … |
| `WWVegas/WWLib/stlport_deque_e12_new_elements.cpp` | 1,477 | wrong_selected 2: `??$copy@U?$_Deque_iterator@UBfmeE12@@U?$_Const_traits@UBfmeE12@@@_STL@@@_STL@@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@2@@_STL@@YA?AU?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@0@U?$_Deque_iterator@UBfmeE12@@U?$_Const_traits@UBfmeE12@@@_STL@@@0@0U10@@Z` … |
| `GameLogic/Object/Damage/TransitionDamageFX.cpp` | 1,134 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `GameLogic/Object/SpecialPower/OCLSpecialPowerAtLocation.cpp` | 1,094 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `GameLogic/Object/Upgrade/ReplaceSelfUpgradeImplementation.cpp` | 1,093 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `Common/StringVectorRecordCopyBFME2.cpp` | 1,044 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `Common/StringContainerRecordCopyBFME2.cpp` | 1,004 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `WWVegas/WWLib/stlport_rb_tree_create_nodes.cpp` | 1,001 | wrong_selected 1: `?insert_unique@?$_Rb_tree@HU?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBHUBfmePod52@@@2@@Z` |
| `GameClient/GUI/FontLibraryInit.cpp` | 989 | wrong_selected 1: `?insert_unique@?$_Rb_tree@HU?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBHUBfmePod52@@@2@@Z` |
| `WWVegas/WWLib/OwnedRecord840Copy.cpp` | 984 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `GameLogic/Object/Upgrade/ReplaceSelfUpgradeRva004B7110.cpp` | 963 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `Common/RTS/ScienceStoreFindScienceInfo.cpp` | 878 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `Common/Thing/Rva0033DDA1Dtor.cpp` | 770 | comdat_losers 1: `??_7ThingTemplate@@6B@` |
| `Common/System/Upgrade.cpp` | 754 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `GameLogic/System/LivingWorld/LivingWorldLogicDtorRva002B964F.cpp` | 717 | comdat_losers 3: `??_7LivingWorldLogic@@6BLivingWorldBuildingObserver@@@` … |
| `WWVegas/WWLib/StlportVectorCopyCtorFamily.cpp` | 670 | wrong_selected 1: `??$__uninitialized_copy@PBV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@PAV12@@_STL@@YAPAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@0@PBV10@0PAV10@ABU__false_type@0@@Z` |
| `W3DDevice/GameClient/Drawable/Draw/W3DScriptedModelDrawConditionInfoCopy.cpp` | 613 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `GameLogic/Object/Armor.cpp` | 502 | wrong_selected 1: `??1?$hashtable@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@_STL@@QAE@XZ` |
| `WWVegas/WWLib/Rva0054103EVectorInsertOverflow.cpp` | 473 | wrong_selected 1: `??0?$_Vector_base@VSaveMapPreview@@V?$allocator@VSaveMapPreview@@@_STL@@@_STL@@QAE@IABV?$allocator@VSaveMapPreview@@@1@@Z` |
| `WWVegas/WWLib/OwnedRecord900Copy.cpp` | 421 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `Common/System/SaveGame/CreateAHeroDataCopy.cpp` | 404 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `WWVegas/WWLib/stlport_rb_tree_pod_insert_g7.cpp` | 383 | wrong_selected 1: `?insert_unique@?$_Rb_tree@HU?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBHUBfmePod52@@@2@@Z` |
| `GameLogic/Object/Update/RousingSpeechUpdateTrigger.cpp` | 355 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `GameLogic/Object/SpecialPower/Rva003F9FE6CopyCtor.cpp` | 348 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `Common/System/Rva0056616BCopyDeferred.cpp` | 333 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `W3DDevice/GameClient/W3DDisplayCtorRva00049DEA.cpp` | 302 | comdat_losers 1: `??1?$vector@HV?$allocator@H@_STL@@@_STL@@QAE@XZ` |
| `Common/SpawnArmyCopyCtor.cpp` | 295 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `WWVegas/WWLib/Rva004045B4.cpp` | 221 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `Common/System/SaveGame/SaveMapPreviewCopy.cpp` | 209 | wrong_selected 1: `??0?$_Vector_base@VSaveMapPreview@@V?$allocator@VSaveMapPreview@@@_STL@@@_STL@@QAE@IABV?$allocator@VSaveMapPreview@@@1@@Z` |
| `GameLogic/Object/SpecialPower/PlayerUpgradeSpecialPowerDoSpecialPower.cpp` | 197 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `WWVegas/WWLib/Rva00136794Ctor.cpp` | 180 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `WWVegas/WWLib/stlport_vector_asciistring_copy_backward.cpp` | 167 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `Common/VectorDeletingDtorsV06.cpp` | 166 | wrong_selected 1: `?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLifeEventModuleTemplate@2@XZ` |
| `Common/Rva00468E98Rotate.cpp` | 119 | comdat_losers 2: `?cos@@YAMM@Z` … |
| `Common/RTS/Rva002AF581Ctor.cpp` | 110 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `Common/Rva001ED03CCopy.cpp` | 109 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `GameLogic/Object/ArmorHashtableRtsCtor.cpp` | 105 | wrong_selected 1: `??1?$hashtable@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@_STL@@QAE@XZ`; comdat_losers 2: `?_M_initialize_buckets@?$hashtable@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@_STL@@AAEXI@Z` … |
| `WWVegas/WWLib/stlport_map_int_pod52_tree_dtor.cpp` | 100 | wrong_selected 1: `?insert_unique@?$_Rb_tree@HU?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBHUBfmePod52@@@2@@Z` |
| `WWVegas/WWLib/stlport_map_int_pod52_o1.cpp` | 86 | wrong_selected 1: `?insert_unique@?$_Rb_tree@HU?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBHUBfmePod52@@@2@@Z` |
| `WWVegas/WWLib/stlport_list_gamewindow_assign_dispatch.cpp` | 79 | wrong_selected 1: `?erase@?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@QAE?AU?$_List_iterator@PAVGameWindow@@U?$_Nonconst_traits@PAVGameWindow@@@_STL@@@2@U32@@Z` |
| `WWVegas/WWLib/stlport_list_gamewindow_copy.cpp` | 76 | wrong_selected 1: `?erase@?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@QAE?AU?$_List_iterator@PAVGameWindow@@U?$_Nonconst_traits@PAVGameWindow@@@_STL@@@2@U32@@Z` |
| `WWVegas/WWLib/Rva00403927Assign.cpp` | 70 | wrong_selected 1: `??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z` |
| `WWVegas/WWLib/stlport_list_int.cpp` | 67 | wrong_selected 1: `??R?$less@H@_STL@@QBE_NABH0@Z` |
| `WWVegas/WWLib/stlport_rb_tree_locomotor_create_node.cpp` | 34 | wrong_selected 1: `?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@_STL@@@_STL@@QBEPAU?$_Rb_tree_node@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@2@IPBX@Z` |
| `WWVegas/WWLib/stlport_list_gamewindow_assign_004243BE.cpp` | 22 | wrong_selected 1: `?erase@?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@QAE?AU?$_List_iterator@PAVGameWindow@@U?$_Nonconst_traits@PAVGameWindow@@@_STL@@@2@U32@@Z` |

Clearance: the placement cause is cleared by `retail-truth-5` (census row
`93614acd90` for `840db2d676`, srv1; index published); the 56 units above remain open as source repairs.

#### Pathfinder consumer subset (2026-10-28)

Scoped repair verified against base `7c27ac5b25` and preview index
`41c28839bf`: ClassifyBridgeCells, PathfinderNewMap.cpp and
PathfinderBridgeUpdateRva0052ED74.cpp give math.h's unused inline `floorf`
internal linkage. Each object stops exposing `_floorf`; all 41 retained
external COMDAT byte-and-relocation digests and the external dependencies
remain unchanged. No provider, row, pin, shared header or source path moves.
[Scoped evidence and object receipts](../../reverse/attempt_support/pathfinder-inline-floor-link-20261028-codexb4.md).

Normal builds pass six function rows and two data rows; NewMap's EH graph is
EXACT. Strict receipts cover all three sources and the existing retail
`_floorf` owner (eight rows). The same-index ordinary preview changes the
three consumers from blocked to LINKS, totaling 4,349 authored bytes. These
are preview results, not measured linked-byte gains. The separate retail
owner still reports the selected-copy blocker; LINK-133 remains open globally.

The outgoing batch audit is INCONCLUSIVE: the index predates the base and
affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a current
receipt. Carry the removed-helper scope and affected consumers into the next
normal census; full selected-consumer coverage and census confirmation remain
pending.

TerrainLogicIterateTreesNearAPoint.cpp (2026-10-28, claude; census index at
`c8734bec0c`): the same internal-linkage `floorf` declaration ahead of
`<math.h>` stops the object exposing `_floorf`, its only selected-copy
blocker. All 3 rows still byte-match. The Unwind funclet's `object-symbol=`
hint follows the renumbered label (`$L1216` to `$L1219`). Ordinary preview:
does not link to LINKS, 938 B. Census confirmation pending.

`_floorf` consumer batch (2026-10-28, claude; census index at `c8734bec0c`):
35 more units whose only link blocker was the selected `_floorf` copy take the
same internal-linkage declaration ahead of their first include
(Bfme/Rva004E65CFLeaf.cpp plus 34 picked from the not-linked,
wrong_selected-only units that include math.h). Every row still byte-matches
(353 function rows across the 35 sources). Rva004E65CFLeaf's three Unwind
hints follow their renumbered labels; in the other 34, 118 SEH funclet rows
verify past renumbered `$L` labels through their parents' EH data and keep
their ledger labels. Ordinary preview: all 35 change from does not link to
LINKS, 59,705 B in total. Not touched: the retail `_floorf` owner
(TerrainLogicAmbientColorRva0027DA6A.cpp, which must keep publishing it),
gridcull.cpp (held by another worker; its header says retail links the CRT
floorf), and nine candidates other workers held (Rva002F5925InfoRva002F5925, UnitHelpSource,
InGameCommandButtonHelpRender, InGameNotificationBoxUpdateNotice,
GameSubTitles, PathfinderProcessPathfindQueue,
PathfinderRva002F4491CellCallback, PathfinderRva002F83F5Neighbors,
Rva002ECE6AInfoCtor). Census confirmation pending.

_floorf consumer follow-up (2026-10-28, claude; census index at `c8734bec0c`):
four units the batch above skipped because they call `floor`/`floorf` take the
same declaration: seglinerenderer.cpp, StreakRendererRenderStreak.cpp,
Pathfinder/pathfinder.cpp and W3DTankDrawDoDrawModule.cpp. Their objects reference
`_floorf` only from `.debug$F` (each call inlines to `__imp__floor`), so the
static declaration changes no code. All 144 function rows still byte-match, and the
four SEH funclet rows verify past renumbered `$L` labels. Ordinary preview:
seglinerenderer (18,478 B), StreakRendererRenderStreak (14,007 B) and pathfinder
(50,353 B) go from does not link to LINKS, 82,838 B in total. W3DTankDrawDoDrawModule
(771 B) now shows only `?updateTreadPositions@W3DTankDraw@@IAEXM@Z` unresolved:
7a9f82a892 renamed that provider row (W3DTankTruckDrawUpdateTreadPositions.cpp, which
links) after the census, so the next census should resolve it.
W3DBridgeGetModelVerticesFixed.cpp is also `_floorf`-only but another worker's merge
into W3DBridgeBuffer.cpp held it. Census confirmation pending.

Correction to both `_floorf` consumer paragraphs above (2026-10-28, claude): census
`c8734bec0c` predates e8931880e6 (Render2DSentenceDrawBFME2 stops publishing `_floorf`
and `??_EPendingSurfaceStruct`), and `link_check` keeps every unit it is not given at its
census definitions. With Render2DSentenceDrawBFME2.cpp in the same preview, untouched
consumers link too (W3DBridgeGetModelVerticesFixed.cpp, Render2DSentenceBuildThaiBFME2.cpp,
W3DListBox.cpp: 6,341 B). So the 59,705 B and 82,838 B previews above belong to
e8931880e6's carry-over (claude2's 80 units). The 40 local declarations only stop each
object publishing a non-retail /G7 copy, which keeps those units linking whatever the
link order. Do not count them as new linked bytes. Do not extend the batch
to the remaining `_floorf` or PendingSurfaceStruct consumers. Confirm them at the next census.

2026-11-04: W3DShroud's erase-donor composition now preserves the existing 0x005530A8 provider instead of emitting a non-retail /G7 COMDAT; scoped merge guard and 2,030-byte link preview pass, with no census gain claimed. [Audit and remaining interpolation prerequisite](../../reverse/attempt_support/shroud-erase-consolidation-20261104.md).


Recovery publication (2026-11-06): historical fleet investigation at the inspected revision below; not a fresh reproduction or closure verdict. Original claims are released.



**2026-11-06 FadeInTextRender composition (chat 07 seat 2, base `f15737ff46b`):**
The supported merge dry-run rejects its only movable draw donor: the census-linked
`rva00596908Rva00596908Farm.cpp` would fail on selected
`??_GRva0059675ABase@@UAEPAXI@Z` in the composed object. No move applied and no
source or ledger change. The destructor file separately has an unapproved row.
This is a selected-COMDAT composition prerequisite; the exact cause still needs
provider/copy/flags inspection, not a proven placement regression or false reject.
[Tracked trial and remaining audits](../../reverse/attempt_support/fade-consolidation-20261106-c07-seat2.md).
