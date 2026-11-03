### StrategicInGameUI army-unit cluster: no reachable TU signal (2026-10-29)

Status: investigated to a dead end; the nine file claims are released. The
picker's TU-evidence item for the StrategicInGameUI Army Unit cluster (45 bare
code rows across `StrategicInGameUIArmyUnitIcon.cpp`,
`...ArmyUnitIconLifetime.cpp`, `...ArmyUnitSwapperDialog.cpp`,
`...ArmyUnitSwapperValidation.cpp`, `GUI/StrategicUiArmyHandler.cpp`,
`Common/Rva005F45AFPermuted.cpp`, `Rva005F54DADtor.cpp`,
`Rva005F4DC4Create_Rva005F4EE8.cpp`, `Rva005F4AD7Dtor.cpp`; parents
0x005F4254..0x005F566A and EH funclets 0x007A51BE..0x007A53BB) found nothing
that can anchor them:

- F: `reverse/string_xrefs.tsv` has no path string for any of the nine files.
  The game image carries no InGameUI path at all (its own roots are
  `C:\projects\bfme2patch103\bfme2\`); the WorldBuilder build pushed these
  paths, the game build did not.
- Z/S: the Zero Hour tree defines no `StrategicInGameUI::ArmyHeroIcon`,
  `::ArmyUnitIcon` or `::ArmyUnitSwapperDialog` (Living World UI is BFME
  2-only).
- W: `reverse/wb_name_leads.csv` pairs a dozen RVAs in the range to the real
  WB paths (scores 1..3), but the route is corroboration-only. Every row
  whose notes cite a lead is Wself; the two leads that are not (0x005F4B8F
  `SendSwapArmyMembersMessage`, 0x005F53E6 `Impl::Impl`) carry no naming hint
  for W to agree with (a free function and a placeholder class), and nested
  names (`ArmyUnitIcon@StrategicInGameUI`) never demangle under tu_map's
  METHOD pattern, so N is empty even where the current source is already the
  WB-named file. W cannot fire on this cluster without a tu_map design
  change, which is not a seat decision.
- C: the nearest approved code row below the cluster is 0x005EEDE6
  (StickyBombUpdate.cpp), 0x546E bytes below 0x005F4254 -- past GAP. Above,
  the approved root StrategicInGameUI.cpp run starts at 0x005F56B0 (itself a
  provisional merge whose WB lead names
  `StrategicInGameUICancelArmyMemberMoveButton.cpp`; a naming-lane question
  on its own).
- E/P (promoted): `tu_evidence.py --write` places 0 evidence rows in
  0x005F4000..0x005F5950. V passes its gate but is unpromoted and reaches
  none of these rows either.
- Provisional: needs two hinted rows in one candidate TU. Only
  `StrategicInGameUI::CanMoveArmyMembers` (0x005F50E9,
  N=`GUI/StrategicInGameUI.cpp`) and `::CanSwapArmyMembers` (0x005F516D,
  N=`LivingWorld/InGameUI/StrategicInGameUI.cpp`) hold hints, one per
  candidate, both displaced -- and their WB leads name
  `StrategicInGameUIArmyUnitSwapperDialog.cpp` for both bodies, so either
  StrategicInGameUI.cpp would be the wrong home anyway.

Unlocking the cluster needs evidence none of the signals can carry today:
game-side `__FILE__` strings (none exist), a nested-class N rule that pairs
whole WB files (a tu_map design change), or promoted V/I/R rows reaching the
range (they do not). Renaming the placeholder rows to the WB real names is
worthwhile in the naming lane but creates no placement hint.
