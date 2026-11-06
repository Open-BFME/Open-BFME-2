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


**2026-11-05, generated vtable bridge; paired native measurements completed 2026-11-06 UTC.** The Link lane
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
table and slot counters to reach zero.

Measured at `1622f06c577e91584f9af06a9412af91170ddf29`, rebased on the
writable-initializer correction `473dfd265a`. Evidence remains on srv1 in the
Link worktree under `build/vtable-p1/comparison.json`, with the input hashes,
native logs, MAPs, receipts, object snapshots and both `linked_report/` results.
Four VC7.1 links ran serially at nice priority, using `/FIXED:NO /OPT:NOREF
/OPT:NOICF` and no `/FORCE`. The baseline response differs only by removal of
`retail_vtables.obj`; all common input hashes and the original scoreboard stayed
unchanged. Neither strict link produced an image: both have exactly the same
377 unresolved names and zero duplicates. The paired image measurements therefore
use diagnostic images with the identical 377-name stub set, not runnable real
images or G1 passes.

The planner generated **2,241 tables / 25,542 positive slots**, retained 163
provably matching first copies, and refused 1,038 tables: 453 multiple kept names,
397 without a kept definition, 134 with strong definitions, 27 with omitted
targets, 19 with ambiguous target names, four ambiguous table names and four
unrowed targets. The complete refusal evidence is `with/exit_link/vtable_bridge_queue.tsv`;
the picker and `reverse/exit_link_blockers.tsv` are unchanged.

| Image check | Without bridge | With bridge |
| --- | ---: | ---: |
| Short winning tables | 1,304 | 40 |
| Wrong compared slots | 1,622 | 48 |
| Equal compared slots | 6,072 | 24,873 |
| Unanalyzed slots | 21,820 | 4,593 |
| Image bytes | 12,988,416 | 13,078,528 |

Only these vtable-related report counts changed. The 40 remaining short tables
are 27 omitted-target, five ambiguous-target-name, four unrowed-target and four
strong-definition refusals. Of the remaining 48 wrong compared slots, 23 belong
to generated tables, 12 to ambiguous-target refusals and 13 to omitted-target
refusals. A pointer to the ledger-selected external name is not proof that the
winning code body or its dependencies agree with retail: seven of those 23
generated-slot defects select a different object than the ledger owner, while
16 select the owner's object. These remain visible defects, not bridge credit;
`remaining-vtable-defects.json` records the selected names and MAP providers.
For example, `VectorClass<StringClass>`'s deleting destructor wins from
`INIStatsRecordTextures.cpp` rather than the ledger's `dx8wrapper.cpp`.
No game-source repair or checker relaxation is included.

Both diagnostic images pass `real_image.py check` with no problems: non-retail
base `0x10000000`, relocations retained, receipt/MAP/image agreement and exactly
one named slot for each required harness API. All 674 bridged initializers occur
as the complete ordered block within `___xc_a..___xc_z` in both images, with no
`.CRT` LNK4078. All 2,241 generated vtables win from `retail_vtables.obj` and
all 25,542 actual pointer values equal their resolved target MAP addresses.
Generated vtable sections use native C++ vtable attributes `0x40301040`;
initializer sections use native writable `0xC0300040`. This verifies placement,
not runtime execution or class recovery. No game was started. Both image reports
exit 1 because defects remain.

The bridged diagnostic is `with/diagnostic_link/exit.exe`, SHA-256
`74d455c6a31e9e4ab1b205bc3c9dd5036c6e983ccb3d55d075c04ac781f7a9ff`.
Its MAP SHA-256 is
`cc941c59c002cb003c858046e080925c4336b5d4301534391861654c4bd9de9b`.
The snapshot/manifest/receipt total is 149,486,825 bytes, versus 148,324,277 for
the control; nothing was dropped. Both images have `.text` virtual size
10,078,228 bytes; `.rdata` grows from 2,126,614 to 2,186,822 bytes.

Direct native fixture evidence is `native/results.json` and
`native/cpp_results.json`. A generated SELECT_ANY copy **can beat a real C++
SELECT_ANY definition**, even one with the right size; the compiled fixture
demonstrates the selected first virtual method changing. The generator avoids
provably matching first copies, but this is not a universal semantic guarantee.
Strong non-COMDAT definitions are refused: the fixture gives LNK2005/LNK1169
in either order. A reference in a losing SELECT_ANY copy still reports missing
with or without the bridge. These observations are toolchain facts, not an
assumption that strong definitions automatically win.

**2026-11-06, review corrections.** Slot generation now requires the first
external provider in response order, across kept objects and archives, to be
the ledger owner's object. Other copies refuse as
`target-not-winning-provider`, with both providers recorded. The displaced
source slots retain their names and every ledger RVA in JSON and queue evidence;
a linked slot comparing equal no longer erases that source-identity lead.

`exit_link.py --blockers` now publishes `reverse/vtable_bridge_queue.tsv`
from the matching unstubbed real-link result. The fleet link tier serves real
blockers, then refusals, then bridge retirement, with one claim per source file
and zero byte credit. Unknown or vanished owners remain visible in a
`file:reverse/data_ledger.csv` ownership-investigation item. No Code owner is
invented. Diagnostic or mismatched results cannot publish this work; old
artifacts without bridge metadata leave the last queue intact.

Validation: 627 tests passed and the existing empty-fixture test skipped; one
unrelated header-acceptance fixture fails because it lacks `reverse/symbols.csv`,
also reproduced from origin/master's test. Four picker integration tests passed,
including the fallthrough priority when higher-priority work is claimed.

At the maintainer's request, the queued local build and measurement were
cancelled before taking the compiler lock. No new native counts or image are
claimed for these corrections. The committed queue starts with its schema and
an explicit pending-publication comment; the next hourly measured real-link
artifact populates it and its diagnostic measures the new image defects.
The earlier paired measurements above remain historical evidence at their
named commit, not measurements of the corrected eligibility rule.
