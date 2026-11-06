### LINK-618: vtable bridge "multiple-kept-names": one retail class kept under two names
Status: Open (partly repaired). Updated: 2026-11-06; seat halilkkaya-lk36, base `bd49217dc8`, real link
`306f01e6f6` (433 multiple-kept-names refusals in its `vtable_bridge_queue.tsv`), census index `47fd56b879`.

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

**Lessons.**
- Run link_check over the current objects of every unit an earlier fold in the batch changed. A stale
  index object (the pre-fold donor destructor in DozerAIUpdateCtor.cpp) fakes a duplicate.
- Pick the fold direction that does not respell a hatch key. LoadScreen.cpp's present-unmatched key
  and a data pin `??_7Rva0053FADE@@6B@` made one direction refuse.
- rename.py refuses a fold while an earlier fold's edits are unstaged: its name_dependents guard reads
  the working tree. Commit each fold before starting the next.

**Blocked or refused (recorded in re_attempts.log where a fold was tried).**
- Rva0053FADE/Rva0053FB33 (0x008694DC): data pin respelling refused one direction. In the other, 9 of 14
  units stop linking: the copy-constructor units emit implicit `~Rva0053FADE` copies. Declare the base
  destructor in those derived views first.
- Rva005750CF/Rva00574C1B (0x0086E4A4): the MI secondary table `??_7..@@6BRva00575125Second@@@` differs
  between the views.
- Rva005D078BSecond/Rva005D0C31Second (0x0087528C): the constructor unit inlines the base's constructor
  and destructor.
- Rva007F4900CleanupDeleting/Rva00661350 (0x008E2BE8): the deleting destructor comes from the
  `BFME_VPTR_CLEANUP_DELETING_DTOR` macro, which also defines the destructor.
- Rva00148AB0 to Bucket (0x007D3564): NameKeyGenerator.cpp emits an inline `??0Bucket` (selectany), which
  would meet the row's strong definition.
- The readable folds whose copies differ need the placeholder unit rewritten on the real class view:
  - the AI states (AIFollowPathAsTeamState, AIAttackMoveToState, AIAttackFollowWaypointPathState);
  - ScriptActionsInterface and GameResultsInterface (the SubsystemInterface slot views differ:
    `BFME_SUBSYSTEM_SLOTS`);
  - TextOnFrameTransition, ProfilePreferences, ExperienceTrackerAutoResolve and DominateEnemySpecialPower;
  - the Die/Update/Create/SpecialPower MI scaffolds (DieModuleDerived.cpp, Rva0024A797Derived.cpp,
    Rva004B8CDEDerived.cpp, Rva00493DEFDerived.cpp). Their folds would only rename the scaffold's
    subobject tables.
- Eight AI-state placeholder pairs (0x008112C0 through 0x00811900, constructors in
  AIStateHashCtors0033F2FD.cpp): the destructor units derive from a `WindModuleInfo` stand-in for State.
  Moving them onto canonical State needs `~State`'s identity: `??1State@@UAE@XZ` has no row or pin, and
  0x0049B47C is a many-name fold.

**Next check.** Read the next published real link's `vtable_bridge_queue.tsv` for the 21 tables above.
Re-run the dry-run sweep after other seats' header adoptions, because each adoption turns DIFF
candidates into SAME ones.

Clearance: none claimed (no new real link measured). Census confirmation: none claimed.
