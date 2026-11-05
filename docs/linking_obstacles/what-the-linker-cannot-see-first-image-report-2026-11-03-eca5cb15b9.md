### What the linker cannot see: first image report (2026-11-03, `eca5cb15b9`)

`tools/image_report.py` over 18,545 kept objects. Each of these links and then fails at run time.

- **Initializers: 146 of retail's 1,166 are registered.** 966 retail entries are plain function rows,
  54 are rows already named `??__E`, and nothing registers them, so those globals are never built.
  27 registrations are not in retail's table and 113 could not be identified. Next step: register
  them in retail's order. A table generated at exit-link time from retail's list needs no source
  change and can count down as real statics replace it; `??__E` rows should recover first.
  Corrected 2026-11-04 (`212c0525c0`): those 54 rows, and the 60 "unreachable" entries, were already
  registered. The report credited every object's `_$E1` to one ledger row. On `993e6014c8`: 228
  registered, 938 bridged, 116 registered twice. Method and remaining families: LINK-236
  (`link-236-static-initializers-the-exit-link-bridges.md`).
- **Vtables: the link keeps a short copy of 1,734 (measured 2026-11-03 at `083582aacd`'s objects).** A
  private view declares only the slots it calls, so `??_7Snapshot@@6B@` has copies of 1, 2, 3, 4 and 8
  words where retail has 4. 9,804 of 9,808 copies are SELECT_ANY, so the first object in link order wins,
  and here that is a 1-word copy. Another 72 keep a long copy; 1,205 are right, 70 of them with shorter
  copies present. Assumes link order is `_object_sources` order, and retail's length is its run of code
  pointers within the ledger's extent. A virtual call past the end of a kept copy jumps into the data
  that follows, so an image will crash here. The header lanes remove these views, which fixes the
  source. If they are not done when the link reaches 0, build a table like `retail_initializers.obj`: a
  SELECT_ANY copy first in the link, with retail's slots by ledger name, counted, for each vtable whose
  slots all resolve.
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


**2026-11-05, generated vtable bridge (pending link measurement).** The Link lane
implements the P1 bridge in `tools/vtable_bridge.py`, called by `exit_link.py`.
It emits only existing select-any names, refuses strong/common/absolute providers
and ambiguous or unkept targets, and records every refusal in a separate list.
Matching first copies need no bridge, allowing the counters to retire as source
headers are repaired. Positive slot pointers are ledger-bounded; this does not
recover class layouts or synthesize RTTI prefixes.

Direct VC7.1 tests found that a select-any copy can beat another select-any copy,
including a vtable from a compiled C++ class. A non-COMDAT strong definition instead
causes LNK2005 in either order, so detecting it before generation is mandatory.
A losing select-any copy's unresolved reference still appears in linker errors.
No source edit or source-recovery credit is claimed by this bridge. G1 requires its
table and slot counters to reach zero. Final paired-link evidence will be recorded
here before the Link lane requests review.
