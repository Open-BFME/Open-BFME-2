### LINK-618: vtable bridge "multiple-kept-names": one retail class kept under two names
Status: Open (partly repaired). Updated: 2026-11-06; seats halilkkaya-lk36 (base `bd49217dc8`) and
halilkkaya-lk37 (base `b616c8a1db`), real link `306f01e6f6` (433 multiple-kept-names refusals in its
`vtable_bridge_queue.tsv`), census index `47fd56b879`.

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
- 9 refusal rows should leave the multiple-kept-names list at the next real link (unmeasured). Each fold's
  link_check covered every unit naming either spelling plus the units the earlier folds changed (the
  census objects are stale for them): at most 22 units, all LINKS, LINKED unchanged against the census.
- Naming lead, not applied: each AI-state table's slot 2 is a 6-byte getter returning the class-name
  literal, and its onEnter/update rows already carry those names. 0x008112C0 AIAttackSquadState,
  0x00811368 AIDockState, 0x008113B8 AIHarvestState, 0x00811798 AIGoingIdleState, 0x008117F0
  AIGuardRetaliateState, 0x00811850 AITunnelNetworkGuardState, 0x008118B0 AIHuntState, 0x00811900
  AIAttackAreaState. `rename.py class` collides with those existing rows and `--fold` needs the readable
  name on the table, so merging the placeholder classes into them needs a naming-lane decision.
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
  - ScriptActionsInterface and GameResultsInterface (the SubsystemInterface slot views differ:
    `BFME_SUBSYSTEM_SLOTS`);
  - TextOnFrameTransition, ProfilePreferences, ExperienceTrackerAutoResolve and DominateEnemySpecialPower;
  - the Die/Update/Create/SpecialPower MI scaffolds (DieModuleDerived.cpp, Rva0024A797Derived.cpp,
    Rva004B8CDEDerived.cpp, Rva00493DEFDerived.cpp). Their folds would only rename the scaffold's
    subobject tables.
- Eight AI-state placeholder pairs (0x008112C0 through 0x00811900): repaired by lk37, below. The
  premise was wrong: `??1State@@UAE@XZ` has been a matched row in StateCtor.cpp at 0x0049B47C since
  `0fe7b0f981e` (2026-10-07).

**Next check.** Read the next published real link's `vtable_bridge_queue.tsv` for the 21 tables above.
Re-run the dry-run sweep after other seats' header adoptions, because each adoption turns DIFF
candidates into SAME ones.

Clearance: none claimed (no new real link measured). Census confirmation: none claimed.
