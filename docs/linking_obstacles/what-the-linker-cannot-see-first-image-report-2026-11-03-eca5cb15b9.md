### What the linker cannot see: first image report (2026-11-03, `eca5cb15b9`)

`tools/image_report.py` over 18,545 kept objects. Each of these links and then fails at run time.

- **Initializers: 146 of retail's 1,166 are registered.** 966 retail entries are plain function rows,
  54 are rows already named `??__E`, and nothing registers them, so those globals are never built.
  27 registrations are not in retail's table and 113 could not be identified. Next step: register
  them in retail's order. A table generated at exit-link time from retail's list needs no source
  change and can count down as real statics replace it; `??__E` rows should recover first.
- **Vtables: 1,876 have a copy shorter than retail's** (1,165 agree, 55 longer, 346 undefined). A
  private view declares only the slots it calls, so `??_7Xfer@@6B@` has copies of 1 and 39 words, and
  COMDAT selection may keep either. A virtual call past the end of a kept copy jumps into whatever
  follows. Next step: confirm which copy the link keeps; the header lanes already remove these views.
- **FieldParse: the 4 wrong tables are cleared.** `ThingTemplate::s_objectFieldParseTable` was BFME 1's
  (115 entries, 66 shared with retail's 191). `ThingTemplateFieldTable.cpp` now holds retail's: every
  offset, raw user word and parser pointer equal retail's. Its other 8 name lists have no data rows, so
  they are compared by content only. Merge the file back when `ThingTemplate.cpp` adopts canonical INI.
  Cleared in `ModuleFactory.cpp`, which took three tables from Zero Hour headers: `UnitCrateCollide`
  (3 entries), `SalvageCrateCollide` (10, retail's fields were absent) and `TransitionDamageFX` (121;
  each mask spans 0x154 bytes, and it adds subobject lists at +0xFD4). Every token offset and user
  word now equals retail's; confirm pointers on the next image report.
- **Globals:** 3,194 agree, 18 differ, 34 are zero where retail is not, and no object defines 481 that
  retail gives a value. No strong data is defined twice; 24 addresses have several defined names.
