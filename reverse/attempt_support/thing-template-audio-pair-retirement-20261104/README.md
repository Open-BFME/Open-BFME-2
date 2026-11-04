# ThingTemplate.cpp: retire the AudioEventRTS pair duplicate at 0x002A12E1 (2026-11-04, claudeb)

Base `a1ad5f0db7`; link index `5a13f2cd61` (census 2026-11-04 05:53).

## Target facts

- Retail 0x002A12E1 (53 B) destroys the pair's +4 member through 0x004EC395, the
  ICF-folded `_List_base<int>` destructor, then releases the AsciiString key. It
  is the list-valued pair `pair<const AsciiString, TreeHintOpaque002A484A>`,
  already rowed (gen-alias) in `stlport_rb_tree_subscript_002a6a2d.cpp`.
  `reverse/tu_map.csv` approves the address for InGameUI.cpp, not ThingTemplate.cpp.
- Retail's object table parses `MaxSimultaneousOfType` with `INI::parseUnsignedShort`
  (`ThingTemplateFieldTable.cpp:184`). Retail's UnitSpecificSounds parser and its
  map callback are rowed in `ThingTemplateSoundMapParse.cpp` (0x0033DC9C, 0x0033DBE5).

## Change

1. ThingTemplate.cpp: drop the Zero Hour `parseMaxSimultaneous` (INI::scanInt plus the
   "DeterminedBySuperweaponRestriction" keyword), `parsePerUnitSounds` and
   `parseArbitrarySoundsIntoMap` (AudioEventRTS ctor/copy/dtor/setEventName), both
   `present-unmatched` markers (hatch present_unmatched -2) and the reskin table's
   reference to parseMaxSimultaneous (now INI::parseUnsignedShort, as retail).
2. Ledger: retire the duplicate `??1?$pair@VAsciiString@@VAudioEventRTS@@@_STL@@QAE@XZ`
   row (0x002A12E1) and its EH children `$L74359` (0x00774EAF) and `__ehhandler$`
   (0x00774EB7) via `reverse/deleted_rows.csv`. Re-row both EH children under the
   surviving owner in stlport_rb_tree_subscript_002a6a2d.cpp (`$L5650`, `__ehhandler$`),
   with eh_verify EXACT.
3. Old-name consumers migrated to the owner type (structural; the call bytes are
   unchanged): DestroyInstances.cpp (`_Destroy` 0x002A1D94 re-rowed under the new
   template name; the explicit pair specialization only declares the dtor, so this TU
   no longer defines it or its private `??1AudioEventRTS@@QAE@XZ`),
   RvaTreeValueEraseFamily.cpp (`??_G` 0x002A14B9 re-rowed; erase 0x002A4281 calls the
   owner), Rva002A408BErase.cpp. `reverse/stlport_trial.csv` names follow.

A first variant that gave DestroyInstances a full list-valued view emitted its own
EH-less pair destructor, which link order selected over retail's EH copy (four units
0 bytes). That is why the dtor is declared and not defined there.

## Verification

- `./build.sh` on all five sources: 151/151 matched; eh_verify 6/6 EXACT;
  find_declared_unmatched clean on each; check_csv OK.
- Index touches: `??1AudioEventRTS@@QAE@XZ` was defined and touched only by
  DestroyInstances.obj; no other object depends on any removed definition.
- link_check (current objects, index 5a13f2cd61):
  - stlport_rb_tree_subscript_002a6a2d.cpp LINKS 164 -> 174
  - DestroyInstances.cpp LINKS 541
  - RvaTreeValueEraseFamily.cpp LINKS 2,341
  - Rva002A408BErase.cpp LINKS 59
  - ThingTemplate.cpp still 0: unresolved 6 -> 1 (`Player::getProductionCostChangePercent`,
    kept for linked Player.cpp's canAffordBuild); the pair-dtor loser is gone. The FXList
    insert_unique and weapon findBestInfoSlow COMDAT identities remain.
