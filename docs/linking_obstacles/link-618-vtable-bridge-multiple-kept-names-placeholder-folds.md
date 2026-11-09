### LINK-618: vtable bridge "multiple-kept-names": one retail class kept under two names
Status: Open (partly repaired). Updated: 2026-11-06; seats halilkkaya-lk36 (base `bd49217dc8`),
halilkkaya-lk37 (base `b616c8a1db`) and halilkkaya-lk38 (base `3d70a843d39`), real link `306f01e6f6`
(433 multiple-kept-names refusals in its `vtable_bridge_queue.tsv`), census index `47fd56b879`
(lk38: `d707d2f53b`).

**Problem.** The bridge (`tools/vtable_bridge.py`) refuses a retail table when the kept objects bind it
under more than one `??_7` name. Many of these are one class rowed twice: a constructor unit names it,
and a destructor-only unit (a `Rva...Dtor.cpp`, a `ModuleUpdateDtors.cpp` family or an `EmitVtableTag`
scaffold) names it again. Others are genuine ICF folds of distinct classes, such as `VectorClass<...>`
instantiations or the 24 names on Snapshot's table. A fold cannot clear those, and `rename.py` refuses
them.

**Method (reusable).**
1. Candidates: the refusal rows whose names are all simple classes, either one readable name plus
   placeholders or all placeholders. Dry-run `rename.py class --fold OLD --into NEW` in both directions.
   165 readable and 254 placeholder dry runs gave 41 and 93 plans.
2. Keep only folds that leave the `??_7NEW` copies identical. Compare every emitted copy of OLD's table,
   renamed, with every copy of NEW's (scratch `lk36_foldcmp.py` over `build/match`). Where the copies
   differ, the fold makes the first copy in link order win and the other unit loses under the census
   "first" rule, so that fold needs the views reconciled first.
3. After the fold, run link_check over every unit that names either spelling. A constructor unit
   usually emitted an implicit or inline destructor, or kept a present-unmatched donor body, that now
   duplicates the destructor row. Declare the destructor there and do not define it. The row then
   becomes the only definition, and the hatch it used (a present-unmatched marker or an alternatename
   to a wrong body) goes away.
4. Gates: `./build.sh` over every rewritten unit, find_declared_unmatched, an A/B of every emitted
   table (equal under the new name), scoped DIR32, `pin_consistency --check` and link_check
   before/after.

**Completed (each is its own commit; the subjects are rename.py's).**
- Readable names: Rva0044D285 to LANPreferences (0x0083EF04), Rva004CDD39 to ActivateModuleSpecialPower
  (0x0085FC88), Rva004CE03D to UnleashSpecialPower (0x0085FDC0) and Rva00539926 to InGameSimpleHelp
  (0x00869268). The first three are on master as 13dd65c126f, 709009d677c and 1ec51a96a49.
  - LANPreferences drops a self-alias `/alternatename` and a pin.
  - InGameSimpleHelp drops an `/alternatename` that sent `~InGameSimpleHelp` to `??1Coord2D` (an empty
    body).
  - The two special powers drop present-unmatched donor destructors.
- Placeholder unifications, both names placeholders and nothing invented: 0x007C64B0, 0x007D4F10,
  0x0084D7C8, 0x0084DEF8, 0x0084DFF8, 0x007E174C, 0x00814EBC, 0x0083D478, 0x00864D80, 0x008694F8,
  0x0086A894, 0x0086E2C8, 0x00871AE0, 0x008743B8, 0x00875ED0, and 0x0086DB3C/0x0086DB40 (the chat
  screen's two tables).
- 21 refusal rows in total should leave the multiple-kept-names list at the next real link. A table
  whose single name remains then goes to the bridge's ordinary checks, so it may be bridged, or need no
  bridge where its first copy already matches. This is unmeasured until the next published real link.
- link_check was unchanged over every touched unit set, and no unit went from LINKS to not linking.
  Hatches removed: 3 `/alternatename`, 2 pins and 6 present-unmatched. `hatch_counters.py --update` can
  tighten the register in a Verifier-Change commit; this seat did not edit it.

**Completed by lk37 (2026-11-06; each its own commit).**
- `37cf9de066a` puts the eight AI-state destructor units on the canonical State
  (Include/Common/StateMachine.h): Rva0034149B, Rva0034159A, Rva00341796, Rva00341E70 (private
  `FXParticleSystem::WindModuleInfo` copies) and Rva00341F99, Rva00342157, Rva00342228, Rva00341E22 (the
  opaque `Rva0049B47C`). The base call now names `??1State@@UAE@XZ`, the same 0x0049B47C body, and each
  table grows from one slot to State's 17 (retail's length). 24 rows stay exact.
- Eight folds, destructor class into the constructor class (`AIStateHashCtors0033F2FD.cpp`):
  Rva0034149B into Rva0033F4DF (0x008112C0), Rva0034159A into Rva0033F540 (0x00811368), Rva00341796 into
  Rva0033F56B (0x008113B8), Rva00341E22 into Rva0033F701 (0x00811798), Rva00341E70 into Rva0033F724
  (0x008117F0), Rva00341F99 into Rva0033F74B (0x00811850), Rva00342157 into Rva0033F772 (0x008118B0) and
  Rva00342228 into Rva0033F79D (0x00811900). The constructor unit declares each destructor, so it no
  longer emits an implicit copy. Where the folded class already owns the xfer row (0x003414F6,
  0x00341E2D, 0x00342283), both views declare the protected `xfer` override: slot 3 moves from
  __purecall to retail's target. Every `??_7` copy of each class is identical.
- Rva0053FB33 into Rva0053FADE (0x008694DC): the direction that keeps the `??_7Rva0053FADE@@6B@` data
  pin. Rva0053FADECopy.cpp and Rva00540845Copy.cpp now declare `~Rva0053FADE` instead of defining it
  inline, so the row 0x0053FB33 is its one definition.
- GameResultsInterface (0x0083AD08): `06917bb207f` gives GameResultsQueueStartup_Unresolved.cpp the
  fourteen-slot SubsystemInterface (`BFME_SUBSYSTEM_SLOTS`) and Zero Hour's empty queue
  init/reset/update, so its GameResultsInterface and queue (0x0083AD70) tables grow from 9 slots to
  retail's 22, the queue methods in retail's slots 14-21. `72c2fc0e8da` folds Rva00419CD4 into
  GameResultsInterface. Retail's interface destructor and constructor are inline: the queue's
  destructor and constructor expand them, and 0x00419CD4/0x00419CDF/0x00419D18 are the out-of-line
  COMDAT copies the linker kept. So the destructor is inline in both units (identical COMDATs), and the
  queue unit's constructor, which cl emitted although it expands it, is `__declspec(dllimport)
  __forceinline`, leaving the row the one definition. Without that, link_check showed both units losing
  to a duplicate `??0GameResultsInterface`.
- 10 refusal rows should leave the multiple-kept-names list at the next real link (unmeasured). Each fold's
  link_check covered every unit naming either spelling plus the units the earlier folds changed (the
  census objects are stale for them): at most 22 units, all LINKS, LINKED unchanged against the census.
- Naming lead, applied by lk38 (below): each AI-state table's slot 2 is a 6-byte getter returning the
  class-name literal, and its onEnter/update rows already carry those names. 0x008112C0
  AIAttackSquadState, 0x00811368 AIDockState, 0x008113B8 AIHarvestState, 0x00811798 AIGoingIdleState,
  0x008117F0 AIGuardRetaliateState, 0x00811850 AITunnelNetworkGuardState, 0x008118B0 AIHuntState,
  0x00811900 AIAttackAreaState. `rename.py class` collides with those existing rows and `--fold` needs
  the readable name on the table.

**Completed by lk38 (2026-11-06; base `3d70a843d39`, one commit per class).**
- The eight placeholder classes are folded into their readable names: Rva0033F4DF into
  AIAttackSquadState, Rva0033F540 into AIDockState, Rva0033F56B into AIHarvestState, Rva0033F701 into
  AIGoingIdleState, Rva0033F724 into AIGuardRetaliateState, Rva0033F74B into AITunnelNetworkGuardState,
  Rva0033F772 into AIHuntState and Rva0033F79D into AIAttackAreaState. 32 rows (each class's constructor,
  destructor, deleting destructor and its placeholder-class slot bodies) now carry the real class.
- Evidence, re-read from retail for each table: slot 2 is `mov eax,imm32; ret` and the immediate is the
  class-name literal (0x00C11304 "AIAttackSquadState", 0x00C113AC "AIDockState", 0x00C113FC
  "AIHarvestState", 0x00C117DC "AIGoingIdleState", 0x00C11834 "AIGuardRetaliateState", 0x00C11894
  "AITunnelNetworkGuardState", 0x00C118F4 "AIHuntState", 0x00C11944 "AIAttackAreaState"). None of the
  names is in `canonical_classes.csv`.
- Method: a hand fold per docs/naming.md ("Renaming by hand"). rename.py has no route for it: `class`
  collides with the readable rows; `class --fold` refuses first on the stale data_ledger.csv name
  (`??_7Rva0034159A@@6B@` is still listed at 0x00811368) and then its virtual-slot route would refuse on
  the inherited State slots, which are ICF bodies shared with other classes (0x000B3FD0, 0x0047A699).
  The token is respelled in every source and row, each old (name, rva) is tombstoned with the getter
  evidence, re_attempts records each row `landed`, and name_basis.csv is untouched (the tier stays
  unverified, which is accurate for a hand rename).
- Verification per commit: `./build.sh` exact over the changed units; every `??_7` each changed object
  emits is identical to its pre-fold object under the new name, and the two `??_7NEW` copies
  (constructor unit and destructor unit) are identical, 17 slots; find_declared_unmatched clean; scoped
  DIR32 OK; pin_consistency --check OK; link_check over the 44 units that spell or touch either name or
  that the LINK-618 folds changed after census index d707d2f53b: 44 of 44 link, LINKED 34,030 -> 34,030
  bytes, for every commit.
- Rva000647D4Xfer.cpp calls the ICF body 0x00341E2D through a private base view. That body is rowed
  twice, as AIGoingIdleState::xfer and Locomotor::xfer, so the view now spells AIGoingIdleState with a
  note that it proves no AIGoingIdleState base. (P69, 2026-11-09, retracted the Locomotor::xfer row: that
  body is AIGoingIdleState::xfer alone now.)
- Follow-up, not done: several placeholder-class rows keep `int` signatures that cannot override State's
  virtuals (`?onExit@AIHarvestState@@UAEXH@Z`, `?update@AIGuardRetaliateState@@UAEHXZ`,
  `?onEnter@AIHuntState@@UAEHXZ`, `?onEnter@AIAttackAreaState@@UAEHXZ`, `?rva00342120@...`), and three
  slot units keep private State copies (Rva003418EAMethod.cpp and Rva00341E70VSlot.cpp derive from a
  `FXParticleSystem::WindModuleInfo` copy). Once those are respelled, the constructor and destructor views
  can declare the overrides. That makes slots 3-8 of each table name retail's bodies in place of
  `__purecall` or State's defaults. AIDockState can do this now: all four of its rows (xfer, onEnter,
  onExit, update) already have State's signatures. Slot 2 needs each 6-byte getter (rowed as a free
  `?Rva0033F565Get@@YAHXZ` in ConstIntGetters4.cpp) to become the class's `GetSnapshotName`.
- Sweep (method step 2) re-run over lk36's 134 dry-run plans with current objects: no new SAME candidate.
  The SAME ones are lk36's blocked Bucket, Rva005D078BSecond/Rva005D0C31Second and
  Rva007F4900CleanupDeleting/Rva00661350; the NO-NEW-COPY ones are the MI scaffold folds lk36 excluded.

**Lessons.**
- A placeholder's base "identity" can be settled by the ledger before any pin: look for a row at the
  fold address under the canonical name (`rg ",0x0049B47C," reverse/functions.csv`) before calling it
  unproven.
- The census index keeps each folded unit's pre-fold object. Run link_check over every unit an earlier
  commit of the batch changed, not only the units naming the current pair: the constructor unit showed
  `unresolved ??1Rva0033F4DF` against the stale destructor object until those units were included.
- Run link_check over the current objects of every unit an earlier fold in the batch changed. A stale
  index object (the pre-fold donor destructor in DozerAIUpdateCtor.cpp) fakes a duplicate.
- Pick the fold direction that does not respell a hatch key. LoadScreen.cpp's present-unmatched key
  and a data pin `??_7Rva0053FADE@@6B@` made one direction refuse.
- rename.py refuses a fold while an earlier fold's edits are unstaged: its name_dependents guard reads
  the working tree. Commit each fold before starting the next.

**Blocked or refused (recorded in re_attempts.log where a fold was tried).**
- Rva0053FADE/Rva0053FB33 (0x008694DC): repaired by lk37, below.
- Rva005750CF/Rva00574C1B (0x0086E4A4): the MI secondary table `??_7..@@6BRva00575125Second@@@` differs
  between the views.
- Rva005D078BSecond/Rva005D0C31Second (0x0087528C): the constructor unit inlines the base's constructor
  and destructor.
- Rva007F4900CleanupDeleting/Rva00661350 (0x008E2BE8): the deleting destructor comes from the
  `BFME_VPTR_CLEANUP_DELETING_DTOR` macro, which also defines the destructor.
- Rva00148AB0 to Bucket (0x007D3564): NameKeyGenerator.cpp emits an inline `??0Bucket` (selectany), which
  would meet the row's strong definition.
- The readable folds whose copies differ need the placeholder unit rewritten on the real class view:
  - the AI states (AIFollowPathAsTeamState, AIAttackMoveToState, AIAttackFollowWaypointPathState). lk37:
    their destructors (Rva00340D1F, Rva00345CAB, Rva00345F21) chain to `??1Rva0033FF2B` (0x0033FF2B),
    which is AIInternalMoveToState's destructor (it restores 0x00C10DE8, AIInternalMoveToState's table,
    itself a multiple-kept-names refusal). `rename.py class --fold Rva0033FF2B --into
    AIInternalMoveToState` refuses: AIInternalMoveToState is registered, so Rva0033FF2BDtor.cpp,
    Rva00340461Xfer.cpp and Rva00340BDCDtor.cpp must come `--prepared` on its header. Adopting that
    header needs LINK-513 first (GetSnapshotName 0x0033F2F7 and `_bfme_state_slot7` 0x0033F2D7 rowed
    under placeholders). `rename.py function --rva 0x0033F2F7 --to-class AIInternalMoveToState --new
    GetSnapshotName` refuses because the installer AIInternalMoveToStateOnExit_AIInternalMoveToState.cpp
    keeps a private view whose slot 2 is __purecall: that unit's header adoption has to come `--prepared`
    in the same to-class step. Order: LINK-513's two to-class moves with the installer adoption, then the
    Rva0033FF2B fold with the three prepared units, then the three readable folds with their
    destructor units on the canonical header;
  - ScriptActionsInterface (0x0081FD98; GameResultsInterface was repaired by lk37, above). Both copies
    need SubsystemInterface's fourteen slots plus four pure ones (retail has 18; ScriptActions' own table
    0x0081FE48 puts executeAction, the rowed closeWindows body and two more there). ScriptActions_ctor.cpp
    rows the interface's constructor 0x003BA89A, so it emits the table and an inline
    `~ScriptActionsInterface` COMDAT; ~ScriptActions 0x003BD582 expands that destructor. The destructor
    and deleting destructor rows 0x003BA6A9/0x003BA6B4 sit in GameEngineDeletingBaseDerived.cpp, which
    has no constructor that would emit an inline copy, so its definition stays strong and meets the
    COMDAT as a duplicate. Retail's copies come from the ScriptActions TU (all three sit at
    0x003BA6A9..0x003BA8AC beside ScriptActions::reset). tu_map gives 0x003BA6A9/0x003BA6B4 no TU and
    proposes ScriptActionsInterface.cpp for 0x003BA89A: approve those rows into the ScriptActions TU,
    then make the destructor inline there and fold;
  - TextOnFrameTransition, ProfilePreferences, ExperienceTrackerAutoResolve and DominateEnemySpecialPower;
  - the Die/Update/Create/SpecialPower MI scaffolds (DieModuleDerived.cpp, Rva0024A797Derived.cpp,
    Rva004B8CDEDerived.cpp, Rva00493DEFDerived.cpp). Their folds would only rename the scaffold's
    subobject tables.
- Eight AI-state placeholder pairs (0x008112C0 through 0x00811900): repaired by lk37, below. The
  premise was wrong: `??1State@@UAE@XZ` has been a matched row in StateCtor.cpp at 0x0049B47C since
  `0fe7b0f981e` (2026-10-07).

  2026-11-07 source recovery: that unchanged State destructor row now lives in
  Common/StateMachine.cpp after the supported StateCtor.cpp consolidation.
  All 23 merged rows, two EH graphs and the 903-byte combined link preview are
  retained. The historical row-existence evidence above still holds; the move
  claims no new placeholder-fold/table/image clearance (LINK-144).

**Next check.** Read the next published real link's `vtable_bridge_queue.tsv` for lk36's 21 tables and lk37's 10
(0x008112C0, 0x00811368, 0x008113B8, 0x00811798, 0x008117F0, 0x00811850, 0x008118B0, 0x00811900, 0x008694DC,
0x0083AD08).
Re-run the dry-run sweep after other seats' header adoptions, because each adoption turns DIFF
candidates into SAME ones.

Clearance: none claimed (no new real link measured). Census confirmation: none claimed.

2026-11-06 AIDockState lifecycle follow-up (base30b22402f4): the packed constructor and destructor now declare the existing canonical transfer/onEnter/onExit/update overrides. Both emitted17-slot tables resolve native slots3..6 to3415F5/341695/341723/341770. Normal40/40, three EXACT EH graphs, frozen and normal/private provider equality pass; preview retains3/3 LINKS and1639B. No executable body/row/header/flag/pin/alias change. The unused destructor-side State::onEnter copy remains identically provided by the packed constructor. Slot2 name getter33565 was held elsewhere and remains untouched/pure; this is not full-table or runtime clearance. Other states' recorded signature prerequisites remain. [Scoped proof and remaining getter prerequisite](../../reverse/attempt_support/aidock-native-lifecycle-table-20261106/README.md).

2026-11-06 Snapshot table 0x007BB554 (24 kept names), seat leosmare (base `0f70da5432`, census index `f07300675e`):
- Completed, one commit per unit: BoredUpdateModuleDataDtor.cpp, EvacuateDamageModuleDataDtor.cpp,
  W3DBuffDraw.cpp, System/TBuff.cpp (Rva006DABB0) and TransitionDamageFXModuleDataDestructorThunk.cpp now
  derive from canonical Snapshot (reference/shims/moduledata/Common/Snapshot.h) in place of a private
  one-slot `...Base`. Each emits `??_7Snapshot@@6B@` as retail's [0x00401750, __purecall x3] and no longer
  emits `??_7BoredUpdateModuleDataBase@@6B@`, `??_7EvacuateDamageModuleDataBase@@6B@`,
  `??_7W3DBuffDrawModuleDataBase@@6B@`, `??_7Rva006DABB0Base@@6B@` or `??_7TransitionDamageFXModuleDataBase@@6B@`.
  TransitionDamageFX's alias row `??1TransitionDamageFXModuleDataBase@@UAE@XZ` (0x0049B47C) is tombstoned in
  deleted_rows.csv: its funclets now call `??1Snapshot@@UAE@XZ`, Snapshot.cpp's row at that address.
  All rows exact, EH EXACT, link_check LINKS per unit; all 395 cached `??_7Snapshot@@6B@` copies agree.
- Caveat (target fact): those derived tables grow from one slot to four with __purecall in slots 1-3, where
  retail has ModuleData's bodies (0x000B3FD0, 0x00065212, 0x0047A69C) or, for 0x007CE310, 0x000B3FD0,
  0x000D1BA0, 0x000D211D. W3DBuffDrawModuleData (0x007CD270) is bridged in the queue either way;
  BoredUpdateModuleData and EvacuateDamageModuleData have no data row and their constructors install the
  retail table through a bound global, so the emitted copies are orphans. Short-to-wrong, not fixed.
- Still kept on 0x007BB554, with the prerequisite each needs:
  - `BfmeSnapshotBase` (GODupBase.cpp) and `Rva00426745SnapshotBase` (BfmeStringRecord00426A5B.cpp):
    multiple inheritance, so the swap renames the secondary-qualified table (`??_7GODupBase@@6BBfmeSnapshotBase@@@`,
    bound at 0x00807D2C and bridged). The data_ledger name must move with the source; rename.py
    `class --fold` refuses both as readable names.
  - `Base001F4C67` (Rva001F4C67Finish.cpp): the real base is Rva001F376E, whose views in
    ParticleBaseConstructor.cpp and RenderParticleConstructor.cpp also emit `??_7Rva001F4C67@@6B@`; a
    one-unit swap makes the copies differ (link_check: LINKED 187 -> 0). Put Rva001F376E on Snapshot in
    all three together.
  - `TerrainResourceModuleDataBase`: FamilyDeletingDtors_muse-eeab.cpp emits the same derived table, retail
    0x00849440 is 82 slots, and link_check refuses the four-slot copy when two units emit it
    ("selected ... not retail's"). Needs ModuleData's real slots, not __purecall.
  - `ShareExperienceBehaviorModuleDataBase`: the unit instantiates the module data, which Snapshot's pure
    slots make abstract (C2259). Same prerequisite.
  - `Rva000E59D3Base`: Rva000E59D3 is W3DFloorBuffer. Its table 0x007CE9E0 holds 0x000E4886
    (`?rva000E4886@Rva000E4886`), 0x000E5A25 (`?name@Rva000E5A25Named`) and 0x000E6186
    (`?DoXfer@W3DFloorBuffer`), all rowed in W3DFloorBuffer.cpp as non-virtual placeholders. Fold the class
    and make those Snapshot's three overrides, in W3DFloorBuffer.cpp and Rva000E59D3Dtor.cpp together.
  - Not examined this pass: `Rva003B4100` and `Rva0025EF18` (own 14B/11B destructors, so the Snapshot alias
    may be a ledger error), `SnapC8` (Rva0006D0D7Dtor.cpp), `ResourceGatheringManagerBase`,
    `Rva0022CE19SnapshotBase` (4 emitters, GameInfoSlotView.h), `W3DTreeDrawModuleDataBase` (the derived
    class adds a virtual, so slots shift), the FXParticleSystem infos, MemoryPoolObject, ModuleData and
    UpdateModuleData.
- Lesson: before swapping a base, list every object that emits the derived table (`rg -l -a -F` over
  build/match) and read retail's slots; link_check judges a table against retail only when two units emit it.

Clearance: none claimed (no new real link measured).
Publication audit for the preceding AIDockState lifecycle repair0f70da5432: link_batch_audit was INCONCLUSIVE against indexfaee62b0b2/base95c9bc54ac759acf01788b6da141d85d5bf63806, with two missing current receipts, first Rva0034159ADtor.cpp. The scoped40/40, EH and table checks above remain valid; a fresh census/current-consumer pass is still required. No runtime clearance claimed.

2026-11-07, seat halilkkaya-lk40 (base `4b2bb61eb1d`), measurement only: the published queue (real link
`1d41894d2a`, 401 multiple-kept-names) predates the P8/P9 bridge commits (`ee341cc5d99` bridges every used
vtable name at one proven retail address; `3d1a86c6c18` discovers current names from row relocations;
neither is an ancestor of `1d41894d2a`). A read-only `vtable_bridge.plan()` over the current kept objects
(full `./build.sh` green) gives multiple-kept-names 0: a table kept under several names now gets one full
copy per used name. The folds above therefore no longer gate bridging; they still matter for one class
identity per table and for the first kept copy being retail's (fewer bridges). The AIInternalMoveToState
chain was not started: its first step's address 0x0033F2F7 was held by another seat's `class:UpdateModule`
claim.

2026-11-08 root follow-up: the Rva0033F33D constructor/destructor pair now
uses the same canonical State base and xfer declaration. The constructor
removes its one-byte char and manual vptr write in favour of compiler
emission; the destructor retires its incompatible private WindModuleInfo
view. All three rows (33/75/28-byte extents) remain exact; eight-source
strict preparation passes 129 rows/four data rows, with four exact EH
graphs. Both emitted tables agree at 68 bytes/17 slots. Bounded replay
changes one strong-definition refusal to zero, retaining one bridge/17
slots; preview conserves LINKS/4,207 bytes at c885072a48. This is the same
State prerequisite as the earlier cohort, not full table recovery:
AIBackAwayAndCowerState's placeholder getter/class and lifecycle slots
2/4/5/6 still need reconciliation. The stale Wind queue key remains;
LINK-247 records that boundary. Next-image confirmation is pending.
[Native operands, preserved bodies and controls](../../reverse/attempt_support/back-away-state-table-20261108/README.md).

Published as 60858c3763 (first attempt, 27.9 seconds). Required checks pass;
the broader audit is INCONCLUSIVE because unchanged Rva00340BDCDtor.cpp
lacks a current receipt (index c885072a48/base bc96d415a7). Carry it into
the next census/image; the one bridge and four derived-slot prerequisites
remain, with no full-link/runtime claim.

2026-11-08 root identity/lifecycle follow-up: Rva0033F33D's four rows and
its constructor caller now spell AIBackAwayAndCowerState, the literal
returned by native table C10EE0's slot-2 getter 33F35E (VA C10F24). This
uses the documented canonical hand-rename route: the fold planner cannot
express the getter tie or inherited ICF slots. Old rows are tombstoned and
re_log records the evidence; name_basis is unchanged. Both lifecycle
views declare existing native slots 3/4/5/6, and the measured owned pointer
uses StateMachine plus normal global-scope deletion instead of a private
slot proxy. All 85 changed-source rows and five EH graphs pass; supporting
strict receipts cover 171 rows, and the eight-source preview conserves
LINKS/6,021 bytes at c885072a48. Both 17-slot tables remain identical;
the removed inherited default has an identical current provider. Slot 2,
shared-class consolidation, the Wind queue identity and next-image
confirmation remain open; no bridge/image/runtime clearance is claimed.
[Identity, native slots and preserved-body proof](../../reverse/attempt_support/back-away-class-lifecycle-20261108/README.md).

Published as bd717ca94a (first attempt, 56.0 seconds). Name-dependent
commit verification passes 666 rows/25 sources and 70 exact EH graphs;
post-rebase push verification passes 516 rows/14 sources and 19 exact EH
graphs. The broader audit remains INCONCLUSIVE: ten source objects lack
current receipts, first ConstIntGetters4.cpp (index c885072a48/base
8e5e79fd2f). Carry the larger closure into the next census/image; no full
link or bridge clearance is claimed.

2026-11-08 root getter follow-up: tools/rename.py --to-class moves native
33F35E into AIBackAwayAndCowerState::GetSnapshotName and declares the
protected override in both lifecycle views. All 45 changed-source rows
and 247 dependent rows pass; EH is exact. Both 17-slot copies agree,
with only slot 2 changed from purecall to the native literal getter.
Six strictly current cached objects conserve preview LINKS/4,918 bytes
at c885072a48. Fourteen source slots have positive name bindings; the
remaining State loadPostProcess/slot7/slot16 bodies already match C3 at
B3FD0, but their names lack rows. B3FD0/class:State are held by
Burachi-3D@Burak/85351563, so their ICF admission is deferred. An AI-source
alias also needs owner-source fold proof and shadow A1/TU review; inline
is not a general placement exemption. These are covered bodies, not a
regression. Shared-class/Wind-queue work and next-image confirmation
remain open; no full bridge or runtime clearance is claimed.
[Getter proof and held inherited-name dependency](../../reverse/attempt_support/back-away-getter-20261108/README.md).

Published as 11c1dad59b (attempt three, 34.6 seconds after two lost races).
Required checks and the post-publication native table/getter proof pass.
The broader audit remains INCONCLUSIVE: unchanged AICowerState_onEnter.cpp
lacks a current receipt (index c885072a48/base93e2f70268). The three held
inherited-name gaps persist; carry both dependencies into the next
census/image rather than reporting full link/bridge clearance.
