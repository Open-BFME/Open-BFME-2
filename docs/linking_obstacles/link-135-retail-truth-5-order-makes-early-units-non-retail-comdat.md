### LINK-135: retail-truth-5 order makes early units' non-retail COMDAT copies the kept ones

Status: Open; per-provider repairs landing / awaiting census. Updated: 2026-10-29;
inspected revision: `b740e71229` (FX redo: `6d854aae1c`); index `d92e7e6635` (census 2026-10-28 15:58, retail-truth-4).
Evidence / affected units: retail-truth-5 (0d26afd6d2) places objects by their own
unshared rows. Re-ranking the census index by `code_places` over the census commit's
own `functions.csv` (the retail-truth-4 rule on that ledger reproduces the index order
exactly) turns 10 names' kept copy from wrong to non-wrong (125 census-unlinked units,
271,771 B blocked only by them: the expected LINK-132/LINK-133 recovery) and 35 names
the other way (50 census-linked units, 43,547 B upper bound). A retail-copy holder that
sat early only through an ICF row moves back to its own code, and the next definer,
early through its own unshared COMDAT row, holds a non-retail copy. Providers that
become first: CreateAHeroDataCopy.cpp (`vector<AsciiString>` copy ctor, 26 users /
18,926 B), FXParticleSystemModules.cpp (25 FXParticleSystem module factory names,
8,121 B), GameWindowManager_registerTabList.cpp (3,042 B),
stlport_deque_e12_new_elements.cpp (3,003 B), FontLibraryInit.cpp (2,559 B),
HordeContainRva00475F61.cpp (2,426 B), StlportVectorCopyCtorFamily.cpp (2,266 B),
AIUpdate.cpp (1,915 B), Rva0052CD81Finish.cpp (682 B), ArmorHashtableRtsCtor.cpp (607 B).
[Simulation script, output and table](../../reverse/attempt_support/rt5-order-losses-20261029/README.md).
Completed:
- `CreateAHeroDataCopy.cpp` (halilkkaya-lk6): its copy constructor at 0x00409D4D calls
  `vector<AsciiString>`'s copy constructor (REL32); a declaration-only specialization
  stops the unit emitting its /EHs copy (digest 851ff550b937; retail 82e371045a40 at
  0x000BC07E, owned by stlport_vector_asciistring_copy_backward.cpp). 9/9 rows exact
  (funclet labels renumber, parent EH data verified); `link_check` LINKS 404 -> 404 B.
  Seven other names the copy pulled in leave the object; each keeps the same first
  copy in retail-truth-5 order, and the copy constructor's first copy turns retail.
  Follow-up at `b98e313906` (codexb4, index `840db2d676`): the default picker
  served TransitionDamageFX.cpp's old selected-copy finding. Paired current
  previews with CreateAHeroDataCopy.cpp and the rowed vector-copy provider
  report all three LINKS (404, 167 and 1,134 authored bytes). No additional
  source repair is needed in that consumer; carry the provider repair into
  the next census. The saved-index-only target preview retains the old blocker.
- `FXParticleSystemModules.cpp` (halilkkaya-lk6): **reverted 2026-10-29** (with the `??_G`
  repair below): the explicit copy-constructor instantiations reordered the unit's
  `ModuleTag<...>::s_key`/`s_name` template statics, so 16 of them resolved to two retail
  bases (full-gate DIR32 consistency red; rows stayed 227/227). Redo the factory/clone
  suppression without moving any template static's emission (check `DIR32 consistency`
  over the unit's rows). Original repair, for the redo: its /O1 /GX- vtables instantiated
  22 `ConcreteModuleClass::createTemplate()` and 3 `ConcreteModuleTemplate::clone()`
  bodies (GPU_DRAW, RENDEROBJECT_DRAW, LIFE_EVENT) whose retail copies, with
  `__EH_prolog`, are rows of the /EHsc FXParticleSystemFactories.cpp. Declaring those
  specializations (`FX_FACTORY_ELSEWHERE`, `FX_CLONE_ELSEWHERE`) stops the copies;
  the three copy constructors the clones used are this unit's rows and are now
  instantiated explicitly, as TERRAIN_COLLISION's already was. 227/227 rows exact;
  `link_check` LINKS for Modules, Factories and FXParticleSystem.cpp (13,604 B, unchanged).
  All 25 lost names' first copy turns retail; the 36 other names leaving the object
  (STREAK/QUAD/BUTTERFLY template ctor, vtables, v1, dtors) keep their first copy.
  **Redone DIR32-clean 2026-10-29 (halilkkaya-lk7)**, with the `??_G` repair below. Cause
  of the break: the ledger binds this unit's dynamic initializers by MSVC 7.1's counter
  names (`object-symbol=_$E274` ...), and the counter follows the point where each
  `ConcreteModuleClass<TAG>` is instantiated. Declaring a member specialization
  instantiates the class, so the three named-tag `createTemplate` declarations placed
  with their wrappers moved RENDEROBJECT_UPDATE/LIFE_EVENT/TERRAIN_COLLISION's
  `s_instance` and `s_key`/`s_name` initializers ahead of RENDEROBJECT_DRAW, GPU_DRAW
  and the three class-wrapper tags (`_$E170..192`, `_$E266..296` permuted). Fix: each
  factory declaration sits right before its class's explicit instantiation (the named
  tags' beside `template class ConcreteModuleClass<...NamedTag>`). Verified: all 174
  `_$E` initializers and 121 `_$S` table entries map to the same targets as master's
  object; 227/227 rows exact; scoped `verify_dir32_consistency` over all 307
  FXParticleSystem sources (1,677 rows) OK (1,179 symbols); 0 of the 25 names left in the
  object, each one's rt5 first copy retail; `link_check` 13,604 -> 13,604 B (three FX units).
- `GameWindowManager_registerTabList.cpp` (halilkkaya-lk6): its retail-digest
  `list<GameWindow *>::erase(first, last)` calls the single-node `erase` out of line
  (REL32); a declaration-only specialization drops the unit's /EHs copy (641dc4771d86)
  so GameWindowManagerScript.cpp's retail one (9c5cf8aa042e) is first. 4/4 rows exact;
  `erase(first, last)` keeps digest 45b9ab4d4135. The unit itself still does not link
  (unchanged: its `registerTabList` COMDAT names the `list` assignment row 0x0046F0C2
  where retail calls 0x002C54EE; see the 2026-10-26 split-name recheck).
  Follow-up (2026-10-29, base 38dbdee4d7): declaring the single-node insert
  specialization suppresses this unit's conflicting copy in favor of the rowed
  0x005925E2 provider in GameWindowManagerScript.cpp. All four rows remain exact;
  preview against census index 85f6b7f40c removes the insert COMDAT finding but
  still reports the assignment-driven registerTabList mismatch (0 linked bytes).
  Resolve the 0x0046F0C2 family identity before claiming link clearance; consumer
  selection and census confirmation remain pending.
  Recheck at `a92f873f7e` (2026-10-30): current preview against `12b9e7a7c0`
  still reports the same registerTabList COMDAT/selected-body findings and
  0 -> 0 bytes. Current rows retain the native-target conflict above. No new
  trial or source change; claims released and the identity prerequisite stays
  open. [Checks](../../reverse/attempt_support/fprintf-crt-header-20261030-codexb4.md).
- `AIUpdate.cpp` (halilkkaya-lk6): every use of the locomotor tree's node
  `allocator::allocate` is inlined (the out-of-line /G7 copy, 31a17b736d02, had only its
  own FPO reference); an import-inline (`__declspec(dllimport) __forceinline`)
  specialization with the bfmealloc body keeps the inlining and drops the copy, so
  ThingTemplateConstructor.cpp's retail copy (010668febc82) is first. 9/9 rows exact;
  no other COMDAT digest of the object changes; the unit's own pre-existing blockers
  are unchanged and ThingTemplateConstructor.cpp LINKS (1,881 B).
- Blocked (re_attempts.log, 2026-10-29): `stlport_deque_e12_new_elements.cpp`
  (`copy<const_iterator, iterator>`), `FontLibraryInit.cpp` (`insert_unique`; since
  repaired, below) and
  `StlportVectorCopyCtorFamily.cpp` (`__uninitialized_copy<const vector<BfmeE8> *, ...>`):
  a declaration-only specialization keeps the call but changes the calling row (the
  caller must then materialise an empty tag argument, as in LINK-132's FVF trial, or
  set up the hidden return slot differently).
- `HordeContainRva00475F61.cpp` (halilkkaya-lk6): its /O1 /G7 build emitted
  `less<int>::operator()` (475d42af7839) although every use is inlined; the same
  import-inline specialization drops it, so stlport_list_int.cpp's retail 0x00626F90
  copy is first. 6/6 rows exact, no other COMDAT digest changes; the unit's own
  pre-existing blockers are unchanged and stlport_list_int.cpp LINKS.
- `ArmorHashtableRtsCtor.cpp` (halilkkaya-lk6): nothing in the object references the
  `hashtable<NameKeyType, ArmorTemplate>` destructor it emitted (a945b7b54bce); a
  declaration-only specialization drops it with its `clear` and node helpers, so
  Armor.cpp's retail copies (destructor 536bacaa8f30, `clear` e5f4c01a0c16) are first.
  3/3 rows exact, no other COMDAT digest changes; both units LINK (607 B, unchanged).
- `Rva0052CD81Finish.cpp` (halilkkaya-lk6): its copy constructor (0x0052CD81) calls
  `_Vector_base<SaveMapPreview>(n, alloc)` out of line; a declaration-only
  specialization drops the unit's /O1 copy (0aad7a9d42b3) so
  Rva0054103EVectorInsertOverflow.cpp's retail one (c9402de9d640) is first. 1/1 row
  exact, no other COMDAT digest changes; the unit's pre-existing blockers are unchanged,
  Rva0054103EVectorInsertOverflow.cpp and SaveMapPreviewCopy.cpp LINK.
Summary (2026-10-29): 7 of the 10 providers repaired, covering 32 of the 35 lost
names; the three left (deque `copy`, FontLibraryInit `insert_unique`, BfmeE8
`__uninitialized_copy`) touch 9 census-linked units, 7,828 B upper bound.
Second loss class (2026-10-29, halilkkaya-lk6): the same re-ranking also changes
`keep_rule`'s verdict on units' own copies (with the census's referenced-name set; on
the census order the computation reproduces the census's multi-copy losers exactly).
Nine census-linked units (18,739 B) newly lose a copy: AIPlayerTeamBuild.cpp (9,120 B;
`list<TeamPrototype *>` `clear`/`_M_create_node`, first copy becomes Player.cpp's),
FXParticleSystemModules.cpp (3,856 B; two named-wrapper `??_G`), ThingTemplateConstructor.cpp
and Rva0033DDA1Dtor.cpp (2,651 B; `??_7ThingTemplate`, first becomes ThingTemplate.cpp's),
ProcessAnimateWindow.cpp and Rva00468E98Rotate.cpp (1,988 B; `cos`/`sin`),
LivingWorldLogicDtorRva002B964F.cpp (717 B; three `LivingWorldLogic` vtables, first becomes
LivingWorldLogicCtorBfme.cpp's), W3DDisplayCtorRva00049DEA.cpp (302 B; `vector<int>`
destructor) and ArmorHashtableRtsCtor.cpp (105 B; `_M_initialize_buckets`).
[rt5_losers.py and output](../../reverse/attempt_support/rt5-order-losses-20261029/rt5_losers.txt).
- `FXParticleSystemModules.cpp` (halilkkaya-lk6), **reverted 2026-10-29** with the factory
  repair above (it was built on it): the RENDEROBJECT_UPDATE and LIFE_EVENT
  named wrappers' `??_G` inlined the 5-byte wrapper destructor and called the module
  template's destructor directly (unproven f8e666291096 / 2b715f6d1187); retail's
  (Factories rows 0x003AA1EA, 0x003AB92A) call the wrapper destructor. Declaring both
  wrapper destructors `__declspec(noinline)` (RENDEROBJECT_UPDATE's keeps its inline
  definition: it is this unit's 0x003A9397 row) gives both `??_G` retail's digests
  (38f68adc5995, 28e3c4687c29). 227/227 rows exact; no rt5 loser left in the unit;
  link_check unchanged (13,604 B over the three FX units). Redone with the factory repair
  (halilkkaya-lk7, 2026-10-29): both `??_G` carry retail's digests again and rt5_check
  finds no loser or wrong-selected name in the unit.
- `Player.cpp` (halilkkaya-lk6): the donor unit (11 rows, placed at 0x000B6464 by its
  `getAcademyStats` row) emitted `list<TeamPrototype *>` `clear` and `_M_create_node`
  from unmatched code; declaration-only specializations (beside its existing
  TeamPrototype `deallocate` one) drop them, so AIPlayerTeamBuild.cpp's copies are
  first and it keeps linking (9,120 B). 11/11 rows exact; only the unmatched
  `Player::xfer` COMDAT (sole definer) changes digest; every dropped name keeps a
  definer; AIPlayerTeamBuild.cpp has no rt5 loser left.
  **Follow-up 2026-10-30 (science providers):** Player now declares the
  existing const ScienceType allocator and vector push_back. Exact-name
  providers in FXShaderParameterBinderInit/PlayerAddScience retain native
  28-byte allocation and the 49-byte 2E01C6 push_back owner. Only Player's
  divergent 26/58-byte definitions disappear; all eleven Player rows and
  every retained raw body/relocation stay unchanged. All eight provider
  rows verify in fresh private objects. The three-unit preview conserves
  the two providers' LINKS; Player retains independent blockers, with no
  headline gain claimed. This completes the small final batch of the Player
  provider pass. Evidence: `reverse/attempt_support/player-science-providers-20261030/`.
  The const PBW allocate-and-copy still lacks an exact native definition
  (31B9EB's owner has another element type; ScienceVectorReserve uses PAW).
  hasUpgradeComplete's QAE pin names a const QBE placeholder owner at 2AB87D;
  reconcile name/signature/layout before removing that donor body. Pins
  alone cannot supply either missing definition. Broader consumer verification
  remains qualified by the older index and missing current receipts.
- `cos`/`sin` (halilkkaya-lk6): retail's `float cos(float)`/`sin(float)` copies sit at
  0x0002FBC0/0x0002FBB0 as ICF-twin rows of AptMathCallbacksBFME2.cpp, which therefore
  no longer places that unit early. HordeContainIface11CSlots.cpp, Rva00468E98Rotate.cpp
  and ProcessAnimateWindow.cpp emit unproven copies (1d05f2cde23b / 6f922c457873) that
  then come first and lose; every use is inlined (only their FPO records refer to them).
  A `static` declaration ahead of math.h (the LINK-132 `floorf` pattern) keeps them
  local, so BfmeCalcBWF.cpp's retail copies come first. 183/183 rows exact, no other
  COMDAT digest changes, no rt5 loser left. HordeContainIface11CSlots.cpp (23,871 B) is
  one of the units retail-truth-5 frees (`vector<Object *>` selection) and would
  otherwise lose `cos` instead (found by running rt5_losers.py over census-unlinked units:
  7 units, 25,594 B); ProcessAnimateWindow.cpp and Rva00468E98Rotate.cpp keep linking (1,988 B).
- `W3DDisplayCtorRva00049DEA.cpp` (halilkkaya-lk6): its private `vector` view's implicit
  `~vector<int>` (unproven a8b8bf46d7cc), called only by the unwind funclet, would be
  first from 0x00049DEA and lose; declaring the destructor in the view keeps the call
  and drops the copy (69 other definers; first becomes a retail copy). 5/5 rows exact
  (funclet labels renumber, parent EH data verified); link_check LINKS 302 B.
- `ArmorHashtableRtsCtor.cpp` (halilkkaya-lk6): its rowed constructor calls
  `_M_initialize_buckets` out of line; a declaration-only specialization drops the
  unit's unproven copy (ef03b9ac339d), which would be first and lose against Armor.cpp's
  retail row 0x00148DDF. 3/3 rows exact, no other digest changes; LINKS (105 B).
- `SquadCtor.cpp` (halilkkaya-lk6): one of the units retail-truth-5 frees; its unproven
  `vector<ObjectID>`/`_Vector_base<ObjectID>` destructors (called only by the implicit
  `~Squad`) would be first and lose. Declaration-only, like its Object* ones; 1/1 row
  exact; only `~Squad` (sole definer, no row) changes digest; no rt5 blocker left.
Freed-unit check (2026-10-29): of the 123 existing units retail-truth-5 frees, 49 already
LINK in the ordinary preview; rt5_check on current objects finds no loser or
wrong-selected name in 122 (SquadCtor.cpp repaired above). Two show an unresolved name
only because the providers were renamed after the census: W3DProjectedShadowDecalHelpers.cpp
(`BoundedShortGrid::load`, BoundedShortGridLoad.cpp) and W3DTankDrawDoDrawModule.cpp
(`W3DTankDraw::updateTreadPositions`); previewed with those providers both LINK (11,109 B).
- `FontLibraryInit.cpp` (halilkkaya-lk6): its `insert_unique` copy differed from retail's
  only in the begin()-insert branch layout; building it with
  `/D_BFME_RETAIL_TREE_INSERT_LAYOUT` (the vendored _tree.c opt-in 344 units use) gives
  retail's digest ff7306be33ea. 24/24 rows exact; no other COMDAT digest changes; the
  five units touching the name (2,559 B) keep linking under retail-truth-5.
  Recheck (2026-10-29, codexb4): the default picker still served
  `stlport_rb_tree_create_nodes.cpp` for this already-repaired name. Current
  strict receipts preserve all 45 rows across that provider and
  `FontLibraryInit.cpp`; ordinary preview reports LINKS for 1,001 and 989
  authored bytes respectively against index `840db2d676`. No further source
  change or census gain is needed for this served item.
- `StlportVectorCopyCtorFamily.cpp` (halilkkaya-lk6): its `__uninitialized_copy<const
  vector<BfmeE8> *, vector<BfmeE8> *>` carried STLport's /EHsc try/catch rollback; an
  explicit noinline loop specialization, the one the file already gives four other
  element types, compiles to retail's 38-byte loop (067a12a09458). 7/7 rows exact (the
  calling row still sees a definition, so its tag argument is unchanged); no other
  digest changes; both units LINK (2,266 B). Remaining LINK-135 loss: the deque
  `copy<const_iterator, iterator>` (3,003 B). Cause, found 2026-10-29: the bfmealloc
  shim's `_algobase.h` makes `__copy_aux` `__forceinline` with the tag by value, so this
  unit inlines it; retail's copy calls the stock `__copy_aux(..., const __false_type &)`
  out of line (o1 sibling). A noinline specialization is refused (C2912: only the shim's
  by-value overloads exist). Next: the stock header for this unit, or a shim scoped so
  `copy`'s `__copy_aux` keeps the stock form, verified against all eight rows.
- `stlport_deque_e12_new_elements.cpp` (halilkkaya-lk7, 2026-10-29): repaired with the
  stock header. The unit now includes the pristine STLport `_algobase.h` ahead of the
  bfmealloc shim (`/I reference/open-bfme-1/inputs/vendor/stlport/stl`, as its sibling
  stlport_deque_e12_o1.cpp already does) and drops its shim-era declaration-only
  `copy<iterator, iterator>` and `copy_backward` specializations, which also changed how
  its two-iterator `erase` called them. `copy<const_iterator, iterator>` is retail's
  63-byte wrapper (6b0d474ec455, was a17c11b019eb), `erase(first, last)` retail's
  (62c3531b3092, was 33add262babe) and `erase(pos)` the sibling's digest; every other new
  COMDAT is retail's (two stock `__copy_trivial*` copies are proven wrong but retail copies
  sort first, as for the sibling). 8/8 rows exact; scoped DIR32 over the ten deque<BfmeE12>
  sources OK; retail-truth-5-ordered link_check (index permuted by the current ledger's
  `link_rank`) LINKS both units, 3,003 B (was 0); census-order link_check unchanged
  (10 deque sources, 6,331 B). With the FX redo above, all 35 first-class names are repaired.
Not repaired: `??_7ThingTemplate` (ThingTemplate.cpp's donor view lists other slots;
2,651 B) and the three `LivingWorldLogic` vtables (the dtor unit's view is a purecall
stub; 717 B): both need the class views reconciled (header lane), not a copy
suppression.
`??_7ThingTemplate` trial (halilkkaya-lk7, 2026-10-29; re_attempts.log 0x0033DDA1): retail's
vtable at RVA 0x00810C4C has one slot (0x0073E90B, the deleting destructor 0x0033E90B; the
string "PlayerUpgrade" follows), so the one-slot view of ThingTemplateConstructor.cpp and
Rva0033DDA1Dtor.cpp is retail's and ThingTemplate.cpp's two-slot copy (protected `??_E` and
private `getObjectMemoryPool` from Common/ThingTemplate.h's memory-pool glue) is not.
ThingTemplate.cpp emits that vtable only through its Zero Hour `~ThingTemplate` copy
(present-unmatched, empty body). Deleting the copy drops the vtable, but also three of the
unit's rows that only the destructor instantiates (0x002CF51B `~Nugget`, 0x0033CA81
`~vector<ProductionPrerequisite>`, the WeaponTemplateSet map `_Rb_tree` destructor):
20/23, reverted. Next: move the 0x0033DDA1 destructor row into ThingTemplate.cpp (its
addresses sit among that unit's rows) with the class's destructor public and no virtual
`getObjectMemoryPool`, or keep those three rows alive without the Zero Hour copy. MapUtil.cpp, AIUpdate.cpp, ThingFactory.cpp, Player.cpp and SquadCtor.cpp
also gain rt5 losers but are blocked by other causes anyway.
Residual units (halilkkaya-lk7, 2026-10-29): census-unlinked units that the
retail-truth-5 preview (`rt5_lc.py` in the evidence directory) still shows blocked by one
or two names, repaired where the cause is local:
- `FireWeaponWhenDeadBehavior.cpp` (209 B): its `??_7FireWeaponWhenDeadBehavior@@6BObjectModule@@@`
  (5 slots, ending with `getModuleNameKey`, 0x00482E51) differed from the first copy,
  Rva00589079Derived.cpp's 4-slot view (both orders keep that one first). Retail's vtable
  0x008497B4 has `getModuleNameKey` as slot 4 (13 slots in all), so the donor view now
  declares it too; only that vtable's digest changes (cc9059c20428 -> 236251dce123, equal
  to the unit's). 8/8 donor rows; scoped DIR32 over the donor and the seven
  FireWeaponWhenDead sources OK; link_check (census and rt5 order) 2,236 -> 2,445 B.
Verification (halilkkaya-lk7, 2026-10-29, tree `0e1f80a20e`): re-ranking the census index by
retail-truth-5 over the current ledger (`rt5_now`-style simulation: objects gone from the ledger
keep their census-ledger place) lists 58 census-linked units that would newly fail on census
copies. The retail-truth-5-ordered link_check (`rt5_lc.py`) over those 58 plus the 13 repaired
providers' current objects: 53 of 61 link (77,016 B). Of the eight that do not, four are
providers the census already counts unlinked (registerTabList, AIUpdate, Rva0052CD81Finish,
Player.cpp: 0 -> 0); three are the class-view cases above (ThingTemplateConstructor.cpp,
Rva0033DDA1Dtor.cpp, LivingWorldLogicDtorRva002B964F.cpp: 3,368 B); and
Rva005E3AE1Dtor.cpp (22 B) only because its retail `??_GRva005E3AE1` provider is now the merged
SBServer.cpp, which the census index lacks (its object holds retail digest 9b3295d907e3 and
sorts first, 0x005E3AE1 < 0x005F4AA3). No other loss is open.
`??_7ThingTemplate` header step (halilkkaya-cls2, 2026-10-29, `79031854ef`):
`Code/GameEngine/Include/Common/ThingTemplate.h` now spells the native 0x640-byte layout
with the one-slot vftable (base `Common/Overridable.h`: only a virtual destructor, no pool
glue); five units adopt it, rows exact, `link_check` unchanged. Not registered yet in
`reverse/canonical_classes.csv`. ThingTemplate.cpp still compiles the Zero Hour shim class
(`reference/shims/bfme_moduleinfo_decl/Common/ThingTemplate.h`, two slots) and stays the
two-slot provider. `reverse/tu_map.csv` approves the constructor 0x0033E1B8 (Z), the
destructor 0x0033DDA1 (Z) and `??_G` 0x0033E90B (N) for ThingTemplate.cpp, so retail's TU
held the real destructor. Remaining: ThingTemplate.cpp adopts Common/ThingTemplate.h (its
ModuleInfo, ArmorTemplateSet/WeaponTemplateSet and SparseMatchFinder rows need those
member types declared beside it, replacing the opaque members) and absorbs
Rva0033DDA1Dtor.cpp and ThingTemplateConstructor.cpp; the retail destructor then
instantiates the three rows in place of the Zero Hour copy and the unit emits the one-slot
vftable.
Remaining / next check: repair the other providers above the same way (each one's
rows, `link_check`, and its first copy in the script's order), then carry the scope
into the next census, the first under retail-truth-5.
Clearance: none. Census confirmation: awaiting the first retail-truth-5 census.
Current-object sweep (b1, 2026-10-29, tree `edd7232ac5`, census index `840db2d676`): `link_check
--paths-from` over the 232 existing census-unlinked units with their current objects links 55
(78,486 B); single-unit checks against the stale index under-report (ArmorHashtableRtsCtor.cpp
and Rva003F9FE6CopyCtor.cpp LINK once CreateAHeroDataCopy.cpp's current object is included).
Two residuals checked, not repaired:
- `GiantBirdAIUpdateCtor_GiantBirdAIUpdate.cpp` (518 B): unresolved `?aiDoCommand@AICommandInterface@@UAEXXZ`
  from its view's slot. Retail's ctor stores 0x00C17A6C at +0x20; slot 0 is 0x0036BC79, rowed
  `?aiDoCommand@Rva00368344@@UAEXPBUAICommandParms@@@Z`, and no other table holds that address, so
  `Rva00368344` is GiantBirdAIUpdate (structural inference). `rename.py class` refuses the merge
  (GiantBirdAIUpdate exists); needs a code-identity route (re_attempts.log 0x0036B717).
- `Rva007B7280Siblings.cpp`, `Rva007B73C0.cpp`: their `??_G?$VectorClass@VVector3@@` inlines `Clear`
  (/O2), retail's 0x000F1CF7 calls it; the teardowns themselves need Clear inline, so the same TU
  cannot emit retail's copy without a hatch. Likely retail's own pointgr.obj copy lost too.
