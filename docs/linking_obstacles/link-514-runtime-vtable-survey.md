### LINK-514: kept `??_7` copies differ from retail's vftables (runtime vtable survey)
Status: Open (partly repaired). Updated: 2026-11-05; inspected revision: e5e17e246f (census index c95fcfcfcd).
Evidence / scope: [survey, method and reproduction](../../reverse/attempt_support/runtime-vtable-survey-20261105.md); [ranked table](../../reverse/attempt_support/runtime-vtable-survey-20261105.tsv); every `??_7` the census link order keeps (6,416 tables).

**Problem.** A byte-exact unit can still emit a vftable unlike retail's: a placeholder or Zero Hour-shaped
private view gives a short table, a wrong slot, or `__purecall` where retail has a body. link.exe keeps
the first COMDAT copy in link order without a word, and the census judges vftables only where a matched
`data_rows.csv` row or a pin gives the symbol an address (127 of 6,421 index names have a verdict). So
"links" does not mean "runs": calls through those slots crash or misbehave at runtime.

**Method (reusable).**
- Take each `??_7`'s first definer in `link_census.objects(ledger())` order.
- Locate retail's table from the matched rows' DIR32 vptr stores (`name_globals.load_index()`), not
  from ledger labels.
- Bound its extent by every retail `C7 /0` immediate, ledger row and code-proven table start.
- Resolve each slot's relocation the way `RetailTruth` does.

**Results (6,416 tables).**
- 1,330 equal retail.
- 3,442 can crash (any `__purecall` slot, or shorter than retail):
  - T1, boot/menu/save-load paths: 852;
  - T2, skirmish classes: 707;
  - the rest are placeholder classes.
- 136 have a wrong slot.
- 750 are unproven; 748 have no retail address.
- In referenced tables: 3,241 `__purecall` slots where retail has a body, 908 wrong slots, and
  40,230 retail slots the kept copy lacks.
- Only 10 tables have a better copy that link order discards, so the class views, not link
  order, are the cause.

**Top risks.**
- `W3DDisplay` (1/101 slots, kept from W3DDisplayDtor.cpp).
- `AudioManager`'s SubsystemInterface table (14/105).
- `InGameUI` (7/120).
- `XferSave` (1/39) and `XferMD5CRC` (2/39), on the save/load and game-logic CRC path.
- The AIUpdate family's ObjectModule tables (12-16/154).
- About 25 `*ModuleData` tables (4/31, Snapshot slots 1-3 pure).
- `HordeContain`'s interface table (151 of 155 slots pure).
- Every `BehaviorModuleInterface` table of CallHelpOnDamage, ObjectSMCHelper and four other
  classes (47/47 pure).
- The ActiveBody/RespawnBody/OathbreakerBody `BodyModuleInterface` tables (43/43 pure).
- The Apt menu screens (1/14-23 slots).

lk28's 56 slot-1 `loadPostProcess` tables (`behaviormodule-snapshot-slots-20261105-lk28.md`) are a
subset: 372 kept tables have `__purecall` at slot 1.

**Completed (2026-11-05, seat halilkkaya-rt-o1, base e5e17e246f).** 267 slots in 149 kept tables now
equal retail. Each fix declares, in the kept unit's class view, an override that retail's slot word
already names through a matched row of the table's own class. The row is bound by its exact mangled
name; no new names or rows were added.
- da28ffb0a68: DynamicPortalBehaviour slot 1.
- d9e8d212bbd: slots 1/3/4 (`loadPostProcess`/`xfer`/`getModuleNameKey`), 64 tables. This covers
  the five Body tables, AIUpdateInterface, Siege/Transport/GiantBird and the Upgrades.
- 35d01b993d7: any rowed virtual slot of a single-copy table, 79 tables / 156 slots.
- a8a794b1de6: 25 multi-copy classes, edited in every defining unit at once (27 tables / 41 slots).

Totals:
- Referenced `__purecall` slots 3,241 -> 3,098.
- Wrong slots 908 -> 784.
- Equal slots 23,714 -> 23,981.
- T1 tables 852 -> 813.

Every batch:
- byte-matched;
- was accepted only where each changed table gained `eq` slots and nothing else moved (survey A/B);
- kept link_check unchanged over the edited units and every other definer of a changed table.

Lesson: a ctor/dtor pair holds two copies of one table. Changing one copy charges the other under
the census "first" rule (13 siblings, 4,082 B, in the first trial), so both copies change together.

Rejected and left for header work:
- Declarations that append a slot because the view's base lacks it: the Apt screens, group
  orders, mice, GameSpyInfo, TaintManager, SpecialPowerModule's multi-copy group, StateMachine,
  Weapon, the siege-engine contains, ObjectSMCHelper and others. They need the family's canonical
  base header first.
- Slots whose retail body is rowed under a non-virtual name (`?name@C@@QBEPBDXZ`, the BFME2
  GetSnapshotName getters, 108 slots), or under another class's or a placeholder's name. Both need
  naming-lane renames before a declaration can bind them.
- Short tables (40,230 missing slots), which need full class views.

**Remaining / next check.** A table moves to retail only through its class family's own view:
adopt the canonical class header (`header_adopt_lane.py`), or declare the family's override where
its body is already rowed. A placeholder table kept from a destructor-only unit needs the same view
as the class's constructor unit. Re-run the survey script on the affected units before and after
each change: every changed table must move toward retail slot by slot, with `link_check` showing no
LINKS→not-linking.

Clearance: none claimed; measurement only, no census rule changed.
Census confirmation: none claimed.
