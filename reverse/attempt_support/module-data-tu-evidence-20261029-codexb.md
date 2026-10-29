# Module-data COMDAT run: placement remains unresolved

Inspected `30d8077f52cd1399b66ffc93448d520ef199e30d`, 2026-10-29.
The default picker claimed six code rows, 0x0025780C through 0x0025792A.
No game source, row, map or register was changed. This is a blocked placement
investigation, not source recovery or linking progress.

## Current target evidence

A map rebuilt in memory with `tu_map.build(tu_map.Layout(Path.cwd(), None))`
leaves every selected row's `tu` empty and confidence `displaced`:

| RVA | Bytes | Current owner / role |
| --- | ---: | --- |
| 0x0025780C | 52 | SubObjectsUpgradeModuleDataFriendNew.cpp, factory |
| 0x00257840 | 28 | SpawnedModelConditionCreateModuleData.cpp, constructor |
| 0x0025785C | 102 | RandomSoundSelectorClientBehaviorModuleDataCtor.cpp |
| 0x002578C2 | 28 | FamilyDeletingDtors_muse-2335.cpp, deleting destructor |
| 0x002578DE | 76 | RandomSoundSelectorClientBehaviorModuleDataDtor.cpp |
| 0x0025792A | 84 | RandomSoundSelectorClientBehaviorModuleDataFriendNew.cpp |

Their evidence contains only class-derived N hints. There is no matching
entry for these addresses in `wb_name_leads.csv` or `string_xrefs.tsv`.
`tu_evidence.py --write build/tu-evidence-25780c.csv` emits 775 evidence rows,
none for the six bodies or the constructor's three EH rows (0x00772097,
0x0077209F, 0x007720AA). Thus neither promoted E/P nor proposal-only R/V/I
supplies a placement anchor.

The adjacent constructors at 0x00257768 and 0x0025797E remain approved by C
for Common/Thing/ModuleFactory.cpp in that same rebuild. This does not approve
the intervening displaced rows: `tu_map.build` deliberately requires
`not r["disp"]` for C propagation. Removing real names to expose C would
discard evidence, not establish their translation unit.

The supported Upgrade consolidation survey reports the factory as unresolved,
with no placement evidence or alternatives. Its input/output freshness check
passes; its committed-map input is itself stale, so the in-memory rebuild
above is the placement verdict. No regenerated map was committed.

## Donor evidence and its limits

Zero Hour's `GameEngine/Include/GameLogic/Module/SubObjectsUpgrade.h:69`
defines the module-data constructor inline. At line 80 the module class uses
`MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA`; Common/Module.h:159-174
defines the factory inline in the macro. This explains why a same-class
out-of-line definition is not available as a Z anchor for the factory.
It is donor structure, not proof of BFME 2's emitter or class spelling.

The retail path inventory does contain
GameClient/Drawable/Behavior/RandomSoundSelectorClientBehavior.cpp at string
RVA 0x0085E7C8. None of these four RandomSound bodies references that path.
The existing GameLogic/Object/Behavior and Common N hints are not that path,
but changing source directories would still require approval and would not
prove that these displaced COMDATs came from the behavior TU.

## Checks and next prerequisite

- `check_csv.py` passes (98,944 function, 9,420 symbol and 2,235 data rows).
- `name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Upgrade/`
  and `--check build/consolidation` complete successfully.
- `find_declared_unmatched.py` over all six claimed sources reports all
  defined functions matched (the deleting-destructor file also reports its
  ordinary two-unclaimed-definition informational note).
- The current map rebuild and all-signal evidence pass above are read-only.
  No compilation is necessary for this source-unchanged investigation.

Retry when an independently checkable BFME 2 path/placement anchor reaches
this run, or an approved verifier-rule change can resolve displaced inline
COMDATs. The nearby C approvals, class names, macro donor and path inventory
alone do not meet today's pass test. All six bodies remain matched and all
scope claims are released after handoff.
