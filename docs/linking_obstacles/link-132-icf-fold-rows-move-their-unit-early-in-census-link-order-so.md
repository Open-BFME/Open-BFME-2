### LINK-132: ICF fold rows move their unit early in census link order, so its non-retail copies are selected

**Living World callback consumer (2026-10-28, base `da546383b783`, index
`41c28839bf`):** `Rva002B8573Method.cpp` previews blocked solely on the
selected `vector<Object *>::push_back` copy, for 343 authored bytes. The
consumer already declares that specialization out of line, so this check
does not repair the selected provider. Recheck it after the AIBuilder
selection prerequisite is resolved and carry it into the next normal census;
no new census-linked coverage is claimed.

**Color-picker subset (2026-10-28, base `cea5d968c5`, index `41c28839bf`):**
W3DAptComponentColorPicker.cpp now keeps math.h's unused `floorf` local.
All 14 rows and both EH graphs remain exact; all 29 retained external COMDAT
fingerprints and external dependencies are unchanged. Ordinary preview goes
from blocked to LINKS for 1,660 authored bytes. The existing retail floor
owner still reports the global selected-copy blocker. Strict receipts cover
both sources (16/16 rows); scoped data checking retains an unchanged global
wrong-name finding. The outgoing batch audit is INCONCLUSIVE: older index
and missing current receipt for Common/0CreateAHeroManager21FE49.cpp.
Carry this scope and consumer into the next scheduled census; global selection
and census confirmation remain open.
[Verification and object receipt](../../reverse/attempt_support/color-picker-floor-link-20261028-codexb.md).

Status: Open; needs a census link-order rule decision (maintainer).
Update (2026-10-29, halilkkaya-lk6): the rule decision landed as retail-truth-5
(0d26afd6d2, `code_places` skips rows whose address another object's row claims),
after the 2026-10-28 15:58 census (d92e7e6635, still retail-truth-4). Re-ranking that
census index under the new rule turns 10 names' kept copy non-wrong (125 units,
271,771 B blocked only by them) and 35 names wrong (50 linked units, 43,547 B upper
bound); the second set is LINK-135. Census confirmation awaits the first retail-truth-5
census.
Census confirmation (2026-10-29, swift-wt2): the retail-truth-5 re-baseline 93614acd90
(census of `840db2d676`) records the `vector<Object *>` family linked: AIBuilder.cpp,
GameEngineInit.cpp, AITactic.cpp, AIStructureCreepTactic.cpp, AISPecialPowerTargetAoE.cpp,
GenericObjectCreationNuggetReallyCreate.cpp/PositionCreate.cpp, SquadGetAllObjectsAndRemoveDead.cpp,
SiegeDeployHordeInitiate.cpp, SplitHordeSpecialPower_doSpecialPower.cpp,
ScriptActions_doTeamPartialUseCommandButton.cpp, AIRva005D8B0BCheck.cpp, AIRoamingDefenseTacticRoam.cpp,
AITeamBuilder_checkIdleTeams.cpp, GameLogicDestructor.cpp and StlportVectorPushBackSiblings.cpp
(16 of 18). HordeContainIface11CSlots.cpp (23,871 B) no longer shows the vector selections in
`rt5_lc.py` order; it waits only on `Pathfinder::RemoveObjectFromPathfindMap` and
`RemoveObjectGoalFromPathfindMap`, rowed in AIPathfind.cpp, whose merge (48bda983ba) postdates the
census index. HordeContainRva00475F61.cpp is the LINK-135 provider loss. No AIBuilder source change
was needed; plain `link_check` still shows the old blockers until the next index.
Preview (2026-10-29, halilkkaya-lk7, tree `0e1f80a20e`): link_check judges selection by census
index position, so it still shows these holders' copies as kept. With the index permuted into
retail-truth-5 order over the current ledger (`rt5_lc.py`, evidence directory of LINK-135), the
`vector<Object *>`, `floorf`/`??_EPendingSurfaceStruct` and `set<Rva001408C0Target>` consumers LINK:
HordeContainIface11CSlots.cpp (23,871 B), GameEngineInit.cpp (9,424 B), AIStructureCreepTactic.cpp,
AITactic.cpp, GenericObjectCreationNuggetReallyCreate.cpp, AIBuilder.cpp, AISPecialPowerTargetAoE.cpp,
HordeContainRva00475F61.cpp, render2dsentence.cpp, W3DVideoStateAllocate.cpp, CastleBehaviorRva00398E9A.cpp
and the TerrainResourceManager units; so do the holders Rva00622290CollectKeys.cpp (3,183 B)
and Render2DSentenceDrawBFME2.cpp (2,448 B), which census-order link_check still shows losing one
COMDAT each. Preview only; no census gain claimed.
Updated: 2026-10-28; inspected revision: `4506f9bc93`, index at `c8734bec0c`.
Evidence / affected units: `link_census.link_order` (and `allowed_symbols.link_order`,
`link_check`, `tu_skeleton`) places an object by the lowest RVA of any matched row,
including `fold-proof=` / gen-alias rows that only name another unit's folded body.
Retail placed that address from one object only, so a fold row is no evidence of
where its own unit sat. The ICF-fold row batches (760b73e4df, 991302b1d0,
a0c3cb8b6a and peers, after the 2026-10-27 14:34 census) moved /O2 library units to
the front, and their FPO copies now beat the retail /O1 copies. Between the 14:34
and 09:35 censuses the no-wrong-selected figure rose (7,612,844 -> 7,654,261 B),
but LINKED fell to 7,384,253 B: 270,008 B now fail only by wrong_selected.
Holders that sit early only because of a fold row (blocked consumers, sole bytes,
overlapping; fold RVA -> unit's lowest own row):
`Render2DSentenceDrawBFME2.cpp` `_floorf` 60 units / 180,956 B plus
`??_EPendingSurfaceStruct` 22,632 B (0x1E13 -> 0x1540B0); `AIBuilder.cpp`
vector<Object*> dtor/push_back/_M_insert_overflow about 50 KB (0x7FAB3 -> 0x4EC0C1);
`Rva00622290CollectKeys.cpp` set<Rva001408C0Target> insert/insert_unique 15,160 B
(0x6C94B -> 0x620B30); `BfmeFVFDescriptorVertexDeclaration.cpp` vector<ICoord2D>
growth 3,123 B (0x142D70 -> 0x181460); `window_video_manager.cpp` 2,340 B;
`RTS3DSceneVisibilityCheck.cpp` 995 B; `ThingTemplate.cpp` 882 B; `WOLBuddyOverlay.cpp`
874 B; and seven smaller ones. Their sum is 378,108 B before overlap.
Completed: FVF trial only. A declaration-only `vector<ICoord2D>::_M_insert_overflow`
specialization, and the same as `extern template`, both make the inlined `push_back`
materialize and zero its `__false_type` tag (`push ecx` ... `mov byte [esp+0x17],0`).
That fails 0x181880 and 0x1818C0, so both trials were reverted. Per-unit suppression
fails wherever the unit inlines the caller. AIBuilder trials (27 blocked units
checked together with link_check, all still blocked; every trial reverted). Dropping
the import-inlined `~_Vector_base<Object*>` with /EHs keeps 29/29 rows, but the copies
are still not retail's EH-framed shape. A declaration-only `~vector<Object*>`,
`push_back` or `_M_insert_overflow` specialization breaks `checkForNewUpgrades`
(0x004ECA01): its inlined dtor and register choice change. Retail's `push_back`
(0x001F211B, zeroed tag) is the shape this TU only produces when the growth body is
out of view. The retail AIBuilder TU's own copy was therefore discarded, so retail
linked a unit with that copy earlier than AIBuilder. CastleBehavior (0x398E9A) and
TerrainResourceManager (0x35A005) have the same cause (CollectKeys and Render2DSentence
holders).
Current-index check (2026-10-28, index `41c28839bf`):
`WW3D2/render2dsentence.cpp` previews blocked for 1,249 authored bytes solely
on `??_EPendingSurfaceStruct@Render2DSentenceClass@@QAEPAXI@Z` selecting a
non-retail body. The earlier cached index `14dc3d2467` previewed this unit as
LINKS; the refreshed result is a provider-selection obstacle, not evidence of
a source byte regression. No repair or census gain is claimed.
Remaining / next check: a census rule that ignores `fold-proof=` and gen-alias rows
when ordering objects (they claim no placement), recorded through
`census_rebaseline.py` with a Verifier-Change trailer, applied the same way in
`allowed_symbols.link_order`, `link_check` and `tu_skeleton`. Before that, measure it
with `link_check` positions recomputed under the rule. Alternatively move each fold
row into the unit retail ICF kept, which only TU evidence can approve.
Simulation (2026-10-28, revision `739f3c6957`, index `54b83e4f69`): the
`Render2DSentenceDrawBFME2.cpp` 0x1E13 fold row puts it at link index 27, so its /O2
`??4W3DRadarResetSurface@@QAEAAV0@ABV0@@Z` (`edx`) beats retail's /O1 body at 0x00072381
(`ecx`); that is the sole blocker of byte-exact `W3DVideoStateAllocate.cpp`. The /O2
emitters inline the operator in retail and MSVC 7.1 /O2 always emits the COMDAT, so no
source spelling repairs it. Ignoring `fold-proof=` rows when ordering turns 11 names
retail-first and 3 non-retail-first: up to 126 unlinked units (270,718 B) are blocked
only by `wrong_selected` on gained names, and up to 14 linked units (31,695 B) touch a
lost name (`??1Rva004A9DF3Element@@QAE@XZ`, `Pathfinder::rva002F83F5`,
`basic_string<char>::append(const char *)`; re-judge them in the census after a rule
change). Ignoring all shared-RVA rows is net negative (10 gains, 37 losses).
[Simulation script and output](../../reverse/attempt_support/fold-row-link-order-20261028/README.md);
its `re_attempts.log` verdict cites this entry under its pre-rebase number LINK-131.
Completed (halilkkaya-lk5, 2026-10-28, base `fd7b44f483`, ordinary `link_check` against
index `41c28839bf`, which already holds the moved order). Five movers were repaired
per unit, all rows exact:
- `RTS3DSceneVisibilityCheck.cpp` (cause 547b34bc57) drops `/Oy-`. Retail's
  `slist<int>(const allocator &)` at 0x00071233 is the 18-byte frameless body this
  TU emits just ahead of Visibility_Check, and /Oy- had made it a 21-byte ebp-framed
  copy. 4/4 rows; the unit and stlport_slist_int_ctor.cpp go 0 -> 995 B.
  Refresh (2026-10-28, base `d14dea8af7`, index `d92e7e6635`): current
  cached object previews LINKS for 977 authored bytes. The unreferenced
  RefRenderObjListIterator constructor diagnostic is not a blocker. This
  confirms the scoped preview only; census confirmation remains pending.
- `BfmeFVFDescriptorVertexDeclaration.cpp` (760b73e4df): its import-inline
  `__uninitialized_copy<ICoord2D *>` constructs with placement new. A call inside a
  dllimport `__forceinline` body is never inlined, so `_Construct` stayed out of line
  and `_M_insert_overflow` came out at 266 B. It is now byte-identical to MapUtil's
  retail 259 B (0x00181770). 6/6 rows; 0 -> 1,820 B.
- `OpaqueScalarDeletingDtorsB13.cpp` (a0c3cb8b6a) defines `~BaseA() {}` inline, as
  OpaqueScalarDeletingDtorsB11.cpp does, so `??_GBaseA` is retail's 29 B. 29/29 rows;
  0 -> 768 B.
- `ChatWindowsLan.cpp` (991302b1d0) declares `Rva002EE9B7()` only, as
  CastleBehaviorCtor.cpp does. Its call was already out of line, and the provider is
  HordeContainCtor.cpp's retail copy. 13/13 rows; 0 -> 882 B.
- `Rva00622290CollectKeys.cpp` (991302b1d0) declares `set<Rva001408C0Target *>::insert`
  and `insert_unique` only. The trial above failed because retail inlines `set::insert`
  at two sites (collectKeys and LoadAsset's key loop): those sites now use
  `insertKeyInline`, `set::insert`'s verbatim STLport body. A bare `insert_unique` call
  there swaps LoadAsset's eax/ecx. 14/14 rows; 12 of the 15 consumers go 0 -> 4,887 B.
  assetmanager_impl.cpp (4,037 B) and AssetManagerImplRefresh.cpp (3,267 B) are left
  with only `??0Q1ReceiverTreeStorage@@...`. BfmeResourceEnumerator.cpp's
  /alternatename provides it, but that unit was merged after the index, so the census
  must confirm both. CollectKeys itself stays blocked by its own signed `find<int>` copy
  (retail 0x00759410 compares unsigned), the less<unsigned> map-family prerequisite in
  `re_attempts.log` (0x0055401D, 0x00622290).
- `window_video_manager.cpp` was already repaired upstream by fe7faa1c69; both of its
  units preview LINKS (2,340 B).
  Rechecked 2026-10-28 against index `d92e7e6635`: the current
  `window_video_manager.cpp` alone previews LINKS for 2,206 authored bytes.
  Its two non-retail-looking node cleanup copies are unreferenced diagnostics,
  not blockers in this preview. Census confirmation remains pending.

2026-10-28 follow-up at `71781d61e0`, index `d92e7e6635`: the published index
still predates the CollectKeys provider repair. With the current CollectKeys
object included in the preview, `AssetManagerImplRefresh.cpp` reports LINKS
for 3,267 authored bytes; its scoped build verifies all eight rows. CollectKeys
itself remains blocked on its separate signed `find<int>` copy. The refresh
consumer's selection and the tree-storage provider still need confirmation in
the next census; this paired preview is not a census gain.

For every name whose first definer was one of these objects, the kept copy becomes
proven retail's or the next definer's retail copy, so no consumer can lose. Of the
seven census-linked consumers of those names, five LINK. CastleBehaviorCtor.cpp and
EmotionTrackerUpdateCtor.cpp fail only on `?update@UpdateModuleInterface@@UAEXXZ`,
whose provider the index forgot (a merge after the index), not on these names.
Reusable pattern: before declaring a COMDAT only, try to make the unit's copy equal
retail's (a flag the retail neighbour proves, or a helper the import-inline body could
not inline). When declaring it only, give every site retail inlined the verbatim body
under another name, so only the out-of-line calls bind to the declaration.
Clearance: pending.
Census confirmation: not claimed.

#### Identity fold rows that move a unit (halilkkaya-cid4, 2026-10-28)

The identity batch "row 12 STL helper folds as ICF twins in 8 units" adds fold rows
below five units' lowest rows: `stlport_map_int_ptr_tree_copy3.cpp` and `...copy4.cpp`
(0x004FFEAF/0x004FFF54 -> 0x00382B7F), `StlportReserveRva0047B35E.cpp` (0x0047B35E ->
0x000B413D), `AnimateWindowManager.cpp` and `ShellMenuScheme_Rva0020066C.cpp`
(0x00200667 -> 0x0014F3C4). Before landing each, every external COMDAT (code and
data) the unit defines was compared with its first definer among the objects the unit
jumps over, by section bytes plus relocation target names: 0 differ (17, 21, 1, 544
and 544 shared copies identical), so no kept copy changes and no consumer can select a
different body. All five preview LINKS before and after (index `41c28839bf`). Use the
same comparison before admitting any fold row that lowers its unit's position. If the
census rule above stops counting fold rows, these units return to their old places
with no selection change. Census confirmation: not claimed.

#### AssetList consumer refresh (2026-10-28)

At `9974966c04`, a refreshed preview against index `41c28839bf` replaces
stale provider definitions with current objects. AssetListOperatorInsert.cpp
changes from the ordinary cached preview's two set selected-copy blockers to
LINKS for 532 authored bytes. Rva00622290CollectKeys.cpp remains blocked by an
unresolved integer tree copy constructor and an unproven `find<int>` COMDAT.
This is a bounded preview, not a census result; carry both units into the next
normal census. No source change or new census-linked coverage is claimed.

#### AssetRegistry worker consumer refresh (2026-10-28)

At `03498faf5f`, index `41c28839bf`, the picker still serves
`assetmanager/Rva0061FFA0.cpp` for the same two set-insertion selected-copy
blockers. Its ordinary cached preview reproduces both. The supported
`link_check.py --refresh` replaces 1,904 objects rebuilt since the census,
and the unit previews LINKS for 1,365 authored bytes without a source edit.
The normal build verifies all eight function rows, its data row and ten
named imports; its worker EH graph is EXACT. The frozen-file check passes.
This verifies this consumer against refreshed providers, not the whole
set-insertion family. Carry it into the next normal census; no new measured
linked coverage or source recovery is claimed.

#### Horizontal slider consumer subset (2026-10-28)

At `e0be65e163`, index `41c28839bf`, W3DHorizontalSlider.cpp's unused
W3DGadget include pulled in the selected PendingSurfaceStruct destructor.
The direct GameWindow include preserves all seven rows, one EXACT EH graph
and all 54 retained external COMDAT fingerprints, while dropping two unused
renderer/compiler helpers. Ordinary preview changes from blocked to LINKS
for 2,675 authored bytes. This clears only the slider consumer in preview;
LINK-132's global selection issue and census confirmation remain pending.
[Evidence and object comparison](../../reverse/attempt_support/horizontal-slider-link-20261028-codex.md).
The batch audit is INCONCLUSIVE: the index predates the outgoing base and
Common/0CreateAHeroManager21FE49.cpp lacks a current consumer receipt.
Carry the removed-helper scope into the next normal census; full external
consumer selection remains unverified.

#### Other W3D gadget consumers (2026-10-29)

At `5fc9728c94`, index `d92e7e6635` (census 2026-10-28 15:58), W3DListBox,
W3DRadioButton, W3DCheckBox, W3DProgressBar and W3DVerticalSlider failed only
on the selected non-retail `??_EPendingSurfaceStruct@Render2DSentenceClass@@QAEPAXI@Z`,
pulled in the same way through the unused W3DGadget include. The slider recipe
(GameClient/Gadget.h + GameClient/GameWindow.h, local WIN_DRAW_LINE_WIDTH)
keeps every row exact (5/5, 3/3, 3/3, 3/3, 16/16). Preview with the five units
and W3DComboBox.cpp: the five change from blocked to LINKS (6,988 authored B).
**Correction (same day):** the index's first (wrong) `??_E` definer is object 27,
Render2DSentenceDrawBFME2.obj, whose copy e8931880e6 (2026-10-28 12:08) already
removed; index d92e7e6635 measures 10:52, before it. With the current
Render2DSentenceDrawBFME2.cpp passed to link_check, the next definer is
W3DComboBox.obj (object 44, retail digest), and all six gadget units, the
*unchanged* five plus W3DPushButtonImageDispatch_Thunk.cpp, preview LINKS
(7,113 B, checked at 5122fde56d), as does W3DComboBox.cpp (1,209 B). So the
include changes (41f25b959e, 1a6d0ce22b; also applied to the thunk) are only an
unused-dependency cleanup, byte-neutral; the preview gain belongs to e8931880e6, not
to them. Remaining definers of the wrong digest after it: objects 1998
(Render2DSentenceBuildThaiBFME2), 3716 (render2dsentence), 4131
(Render2DSentenceGlyphSurfaceBFME2) and later, all after the retail W3DComboBox copy.
Clearance: preview only; census confirmation awaiting the next census.
#### Vertical slider consumer subset (2026-10-28)

At `66ae34555a`, index `d92e7e6635` (2026-10-28 15:58),
W3DVerticalSlider.cpp repeats the unused W3DGadget renderer dependency above.
Including GameWindow directly and retaining the border-width constant removes
only the PendingSurfaceStruct destructor and vector-construction iterator.
All 16 rows and 33 retained external COMDAT fingerprints are unchanged;
strict receipt, frozen-file, EH and data checks pass. Ordinary preview changes
from blocked to LINKS for 844 authored bytes. This clears only this consumer
in preview; global LINK-132/LINK-133 selection and census confirmation remain
pending. [Evidence](../../reverse/attempt_support/vertical-slider-link-20261028-codexb4.md).
The outgoing audit is INCONCLUSIVE: its index predates the base and affected
consumer Common/AIHarvestPrepareSiteState.cpp lacks a current receipt. Carry
the removed-helper scope and affected consumers into the next census; complete
consumer selection remains unverified.

#### Pathfinder footprint consumer subset (2026-10-28)

At `72a0f2d577`, index `41c28839bf`, PathfinderClassifyObjectFootprint.cpp
exposed an unused math-header `_floorf` copy. Giving the inline wrapper local
linkage preserves the full 3,381-byte classifier, all 19 retained external
COMDAT fingerprints and all external dependencies. Ordinary preview changes
from blocked to LINKS for 3,378 authored bytes. The earlier missing
ClassifyWall provider has landed; the global selected-copy issue in
LINK-132/LINK-133 and census confirmation remain open.

[Verification and object comparison](../../reverse/attempt_support/pathfinder-footprint-floor-link-20261028-codex.md).
The outgoing batch audit is INCONCLUSIVE because the index predates the base
and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a current
receipt. Carry this removed-copy scope into the next normal census; full
external consumer selection and new census-linked bytes remain unclaimed.

#### Scorch update consumer subset (2026-10-28)

At index `41c28839bf`, BaseHeightMapRenderObjClass_updateScorches.cpp failed
only on the selected `_floorf`. Its object published math.h's inline `floorf`
(via wwmath.h) but referenced it only from `.debug$F`; the body calls
`__imp__floor` directly. The same local declaration ahead of `<math.h>`
removes the public copy. `./build.sh`: 4/4 rows, 14 float literals, 4 named
imports; EH graph EXACT. Ordinary preview: blocked to LINKS, 1,493 authored
bytes. Preview only; carry into the next normal census.

#### Streak renderer consumer subset (2026-10-28)

Scoped repair at `771fab033f`, preview index `41c28839bf`:
StreakRendererRenderStreak.cpp keeps math.h's unused inline `floorf` local.
All four rows and the EH graph remain exact; all 80 retained external
COMDAT fingerprints and dependency bindings are unchanged. The renderer's
ordinary preview changes from blocked to LINKS for 14,007 authored bytes.
Strict receipts cover it and the existing retail floor owner (6/6 rows).
The owner retains its global selected-copy blocker. The outgoing audit is
INCONCLUSIVE because its index predates the base and affected consumer
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Carry this
scope into the next normal census; global clearance and census confirmation
remain pending. [Evidence](../../reverse/attempt_support/streak-renderer-floor-link-20261028-codex.md).
