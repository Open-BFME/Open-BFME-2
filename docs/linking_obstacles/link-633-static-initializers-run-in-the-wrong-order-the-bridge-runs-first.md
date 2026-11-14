### LINK-633: static initializers run in the wrong order: the bridge runs first, and object order is path order (P32)
Status: Open. Updated: 2026-11-14; inspected revision: 7477c3573a (swarm tool lane 2).

Evidence / affected units: P32. LivingWorldRegionEffects' field table gets empty names because
`initializeRegionEffectFields` (0x007AF9D6, Rva003EE746ColorProvider.cpp) runs before the nine string
initializers it reads (0x007AF8E3..0x007AF9BB, Rva003EE900Forward.cpp and Rva003EE980Forward.cpp);
retail runs the strings at .CRT$XCU slots 548-556 and the fill at 557. link.exe lays out .CRT$XCU in
input order, and exit_link orders its inputs by path (`expected_objects`).

Completed: `tools/exit_link.py --order {path,retail}` (default path; tests in
`tools/tests/test_exit_link_order.py`). Retail order keeps the census's own address order
(`link_census.link_order`, rule retail-truth-5) and moves only the objects that row a retail .CRT$XCU
entry, among the positions they already hold, into retail slot order; path breaks ties. (A merge that
placed initializer objects by slot and the rest by address stalled behind slot 0, security_cookie_init
at 0x00629CA8: retail keeps its initializer functions in their own region, RVA rising with slot for
1,161 of 1,165 slots, and 1,162 of 1,166 initializer objects hold only those.)

Two local diagnostic links of one tree (8a30049c6a, srv1, seed of 133 stubs), path against retail order:

| | path | retail |
|---|---:|---:|
| unresolved / duplicates | 0 / 0 | 0 / 0 |
| vtable bridge: tables refused | 270 | 231 |
| of them target-not-winning-provider | 41 | 2 |
| retail tables bridged | 3,517 | 3,556 |
| image_iso defects | 1,602 | 1,576 |
| vtable_short / vtable_slots_wrong | 6 / 32 | 2 / 10 |
| .CRT$XCU entries (bridge entries) | 1,668 (491) | 1,668 (491) |
| P32 fill slot / strings before the fill | 253 / no | 253 / no |

Retail order fixes 28 image_iso defects (short or wrong tables of Rva000E3B41, WaterRenderObjClass,
Rva006DD51, the two FESL owners, STLport basic_filebuf, ...) and adds 2: the
`ConcreteModuleTemplate<ModuleTag<7, LIFE_EVENT ...>>` table comes out short (FXParticleSystemFactories'
copy now wins: the P18 shape on LINK-584's FX vtable path), and IMEManager's table gets a wrong slot from
the vtable bridge. 14,909 named publics change provider object (118 vtables), including every LINK-133
mover family (`_floorf`, PendingSurfaceStruct, vector<Object*>, set<Rva001408C0Target*>,
W3DRadarResetSurface, vector<ICoord2D>, slist<int>). image_iso checks vtables and globals, not code
bytes, so whether each new code winner is retail's form is not measured.

**Object order does not fix P32.** The fill is not registered by its object: it is one of the 491
initializers the bridge (`retail_initializers.obj`, from `exit_link.initializer_table`) registers,
and the bridge goes first, before every object, in either order. The string initializers are
registered by their own objects under compiler-local names and run after the whole bridge.

Remaining / next check:
- P32 needs the bridge out of the way, by one of: (a) give 0x007AF9D6 its real static registration in
  its own TU (it then leaves the bridge; retail order places Rva003EE746ColorProvider.obj after the two
  string objects: 11,649 against 11,643/11,646, where path order puts it first at 4,384); or (b) emit
  the bridge as slot-ordered pieces interleaved with the objects, which only works under retail order.
  (a) is the source fix the exit test wants anyway (the bridge must reach 0).
- Before retail order becomes the default: compare each moved code COMDAT's bytes with retail (not
  only vtables), and look at the two new defects (FX LifeEvent tag table, IMEManager slot).

*Per-copy code comparison and plan (2026-11-08, swarm Link lane; read-only on the two images above).*
For each public (MAP "Publics by Value" only: file-local statics never bind another object's call) whose
supplying object differs between the two images and that a matched functions.csv row places in retail,
each image's bytes were compared with retail's at the row over its extent (DIR32 slots masked by the
image's own .reloc table; a rel32 after E8/E9/0F 8x equivalent when both targets resolve to the same
ledger function, through jmp thunks). A first pass that also read MAP statics counted 28 worse cases;
20 of them (GameWindowManagerScript's file-static parsers, the per-file C helpers `_ggetm`,
`_get_sockaddrin`, `_piFindActivePing`, `AddSubInternalFPF`, `rva00343FB0`, and `_floorf`) were that
artifact: their other copies are file-local in both images, as in retail.

| | moved publics (14,337) |
|---|---:|
| better (new copy matches retail, old did not) | 234 |
| worse (old matched, new does not) | 8 |
| both match | 3,222 |
| neither matches | 424 |
| no matched row (no retail address to compare) | 10,449 |

The 8 worse cases are all LINK-630's shape: an STL copy from another unit whose call binds to that
unit's own instantiation of the callee, which has no row (6 only a pin to retail's address, 2 neither),
where retail calls a body rowed under another instantiation's name (an ICF fold):

| caller (retail) | new winner | its callee | retail's callee row | callee body |
|---|---|---|---|---|
| `__unguarded_insertion_sort_aux<BfmeAssignRecord32>` 0x00173841 | stlport_bfmeassignrecord32_sort | `__unguarded_linear_insert<BfmeAssignRecord32>` (pin) | `Rva0017351CInsert` 0x0017351C | identical |
| `sort<int*, fnptr>` 0x002C571E | stlport_funptr_value_sort | `__final_insertion_sort<int*>` (pin) | `__final_insertion_sort<void**>` 0x002C55EB | differs at +29 (its own call) |
| `vector<Rva001DEF38Element>::~vector` 0x001DEEF9 | StlportVectorDtorDeferred | `_Destroy<Rva001DEF38Element>` (pin) | `__destroy_aux<Rva00414BDBElement>` 0x001DEEE0 | identical |
| `ModuleInfo::~ModuleInfo` 0x0033CF2F | ThingTemplate | `vector<ModuleInfo::Nugget>::~vector` (no pin) | `vector<BfmeStringRecord002CF4C6>::~vector` 0x0033CD02 | differs at +27 |
| `_Rb_tree<pair<AsciiString,AsciiString>,...>::_M_insert` 0x002072AF | ScriptEngineRva0020881A | `operator< <AsciiString,AsciiString>` (pin) | `??M` pair 0x00206BCF | identical |
| `..._Rb_tree::insert_unique` 0x0020796D | ScriptEngineRva0020881A | same | same | identical |
| `vector<PolygonTrigger*>::_M_insert_overflow` 0x002DFCF6 | CastleBehaviorRegisterOwnedObject | `allocator<PolygonTrigger*>::allocate` (no pin) | `allocator<int>::allocate` 0x00068E15 | identical |
| `vector<ObjectID>::erase` 0x0025BF5D | VectorObjectIDFillInsert | `__copy_ptrs<ObjectID>` (pin) | `__copy_ptrs<Rva005334A4Element>` 0x0025BF40 | differs at +20 |

Five are identity only (the callee body the new winner links is byte-identical to retail's); three are
unproven (their callee differs at a further call, probably the same shape one level down). Rebinding any
of them to retail's row means calling the row's spelling from the donor unit: the code-identity respell
route (crash-prevention's, approved, not landed). Left until it lands.

The two new image_iso defects:
- FX LifeEvent `ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT ...>>` (0x0081C2E4, retail 4 slots): in path
  order the vtable bridge supplies it; in retail order the bridge refuses it (target-not-winning-provider:
  slot 0, the deleting destructor 0x003ABF34, is won by FXParticleSystemFactories' own copy), and
  Factories' 2-slot table wins. The fix is LINK-584's vtable half (Factories' flattened class shape).
- IMEManager slot 30: both images point at the same `serviceIMEMessage` copy, which byte-matches retail in
  both; most likely image_iso's next-symbol extent moving with the order (to confirm).

Plan: (1) the code-identity respell route for the 8 (or fold proofs where the body is identical);
(2) LINK-584's vtable half for the LifeEvent table; (3) re-link both orders: retail order becomes the
default only with zero worse cases; (4) then give 0x007AF9D6 its real static registration in its own TU
(one bridge entry fewer), which places it after the strings under retail order (P32).

Backlog, not started: the 424 publics that match retail in neither order (both images' copies differ
from retail's body). They do not depend on the order. List: build/copy_compare.json on the Link lane's
srv1 seat ("neither matches"); regenerate with the same comparison before working them.

*Update 2026-11-08 (swarm Link lane), re-measured at f97f4dcbee on the same terms.* The FX LifeEvent
table is fixed (LINK-584): FXParticleSystemFactories, FXParticleSystemModules and VectorDeletingDtorsV06
now adopt the canonical `LifeEventModuleInfo` header, so all three copies carry retail's four slots
(deleting destructor, LoadPostProcess, GetSnapshotName, DoXfer). The bridge still refuses the table under
retail order (slot 0's deleting destructor is won by Factories' copy), but the winning table now has
retail's shape, and image_iso no longer reports it.

| | path | retail |
|---|---:|---:|
| unresolved / duplicates | 0 / 0 | 0 / 0 |
| vtable bridge: tables refused | 270 | 231 |
| retail tables bridged | 3,516 | 3,556 |
| image_iso defects | 1,600 | 1,575 (26 fixed, 1 new) |

Per-copy (14,336 moved publics): better 234, worse 8, both match 3,222, neither 424, no retail row
10,448. The worse cases are the 8 STL copies above, unchanged, so retail order is not yet the default.
- The 5 whose callee body is byte-identical to retail's can alternatively be settled with fold proofs
  through `pin_admission.py --add ... fold-proof=<source>` instead of the respell route; the other 3 wait
  on the respell route (crash-prevention's, approved, not landed).
- To confirm later: IMEManager slot 30, the one new image_iso defect, is most likely image_iso's
  next-symbol extent moving with the order (same `serviceIMEMessage` copy in both images, byte-matching
  retail in both).

0x007AF9D6's real registration is blocked on retail's source form (re_attempts.log): written into
`s_parseTable`'s initializer list, MSVC 7.1 keeps each entry's constant parse pointer in static data and
initializes only the `str()` parts at runtime, while retail's data has 0 there and 0x007AF9D6 stores the
parse pointers itself. Candidates: FieldParse constructors for those entries, or a static initializer
object whose constructor fills the table. The row would also need a respell to the compiler's initializer
name. So `initializers_bridged` is unchanged and P32 stays open; it needs that registration and retail
order together.

*Update 2026-11-14 (swarm tool lane 2): real links of 7477c3573a in both orders.* One boat sandbox, one compile
(store audit clean), then `exit_link.py --link --order path` and `--order retail` on the same objects at the
same checkout path, and image_iso at 7477c3573a on each image. Both are real, authoritative, with no stubs.

| | path | retail |
|---|---:|---:|
| unresolved / duplicates | 0 / 0 | 0 / 0 |
| COMDAT copies kept from a non-owner unit (image_iso kept_copies) | 242 in 132 units | 5 in 5 units |
| of them in header-queue units | 148 (69 units) | 1 |
| of them STLport | 194 | 4 |
| image_iso vtable_slot / vtable_short | 20 / 1 | 13 / 2 |
| image_iso defects | 1,316 | 1,310 |

Each kept body was compared with retail at its row, instruction by instruction, with absolute addresses in
either image's range and rel32 targets masked:
- Of the 242 path-order non-owner copies, 238 differ from retail under path order and match it under retail
  order. 4 differ under both: `money_get::do_get`, the `hashtable<pair<const int, Rva003A37FAElement>>`
  constructor, and two `vector::_M_insert_overflow`.
- Retail order keeps 2 copies that are worse (they match retail under path order and differ under retail
  order). Each is a non-owner unit whose lowest own code RVA places it ahead of the owner:
  - `_List_base<Object*>` constructor: HordeDispatchSpecialPower.cpp beats the owner AIGroup.cpp.
  - `??_GRva0058AD7A@@UAEPAXI@Z`: Rva0058AD7ACtor.cpp beats the owner Rva0058AD7ABase.cpp. This is also the
    one new vtable defect (`??_7Rva0058AD7A@@6B@` short, with a wrong slot).
  Whole-object order cannot put every owner first. These need the non-owner unit's private view replaced
  (header adoption) or its identity.

Limits: this covers image_iso's kept-copy table, not every moved public. The 8 worse cases of the
2026-11-08 comparison over all moved publics were not re-checked at 7477c3573a. The comparison is static
only: retail order also changes .CRT$XCU order, and no game has run on either image. Evidence on srv1:
`~/bfme2-ops/swarm/sweeps/toollane2/linkorder/` (report.md, the driver, both images).

Clearance: pending.
Census confirmation: not claimed.

**2026-11-08 the 8 worse copies against the code-identity route (swarm Link lane).** The route has landed (through
`6494b4b9d0`). Its own checks (`identity_head`, `placeholder_types`, `identity_shape_problem`), run read-only on each
callee row spelled as the winning copy calls it, refuse 7 of the 8. It covers operators, special members and template
members with placeholder-typed names; several of these rows are free template functions (which it treats as
hand-written names) or have no placeholder type. It also judges a row by its own wrong calls, while here the wrong call
is in another unit's copy.

| case | winning copy calls | retail's row | route | decision |
|---|---|---|---|---|
| `__unguarded_insertion_sort_aux<BfmeAssignRecord32>` | `__unguarded_linear_insert<BfmeAssignRecord32>` | `Rva0017351CInsert` 0x0017351C (identical body) | refused, hand-written name | plain rename, normal naming evidence, after the FX work |
| `_Rb_tree<pair<AsciiString,AsciiString>,...>::_M_insert`, `insert_unique` (2 cases) | `??$?MVAsciiString@@V0@@_STL@@YA_NABU?$pair@VAsciiString@@V1@@0@0@Z` | `??M@YA_NABU?$pair@VAsciiString@@V1@@_STL@@0@Z` 0x00206BCF (identical body) | refused, no placeholder type | plain rename with its own evidence, after the FX work |
| `vector<Rva001DEF38Element>::~vector` | `_Destroy<Rva001DEF38Element>` | `__destroy_aux<Rva00414BDBElement>` 0x001DEEE0 (identical body) | refused | open: a different function name, so a rename is not justified |
| `vector<PolygonTrigger*>::_M_insert_overflow` | `allocator<PolygonTrigger*>::allocate` (QBE) | 0x00068E15, a fold of many rows (identical body) | refused for every row there | open: fold proof only |
| `sort<int*, fnptr>` | `__final_insertion_sort<int*>` | `<void**>` 0x002C55EB | refused | open, body differs at +29 |
| `vector<ObjectID>::erase` | `__copy_ptrs<ObjectID>` | `__copy_ptrs<Rva005334A4Element>` 0x0025BF40 | refused | open, body differs at +20 |
| `ModuleInfo::~ModuleInfo` | `vector<ModuleInfo::Nugget>::~vector` | `vector<BfmeStringRecord002CF4C6>::~vector` 0x0033CD02 | name shape passes; wrong-binding check not run | not pursued: class-wide (17 rows, 18 units) with a vote per row. Body differs at +27 |

After the 3 renames, 5 remain. **Separate question, whatever the link order:** the 3 whose bodies differ (+29, +20,
+27) are copies that really are not retail's byte for byte at the first level compared; the difference is at a further
call, probably the same shape one level down, but that is unproven. Worth settling on its own.

Retail order stays non-default until the worse count is zero, and it is not a priority against the real link.
A separate false reject is recorded in `re_attempts.log`: `identity_shape_problem` reports `allocate` as a changed
`_STL`-scoped name when only the template argument changes.

*Scaffolding fix for P32 (2026-11-09, swarm crash triage; coordinator-approved, Codex-reviewed).* `exit_link`'s
`INITIALIZERS_AFTER_OBJECTS` moves one bridge entry, 0x007AF9D6, into `retail_initializers_after_objects.obj`, input after
every object and before the libraries. Every other entry stays in `retail_initializers.obj`, first, in its order;
`initializers_bridged` still counts them all. The link refuses a listed address outside the bridge, and one whose extent
a retail initializer can reach a reader of through direct edges (`static_init_readers`). On retail that finds no reader, across
the table's whole extent 0x00DC14C8..0x00DC15C0; the search cannot see virtual calls, pointers held in data or computed
addresses, so it is evidence, not proof.

**This is not recovered order.** The entry still runs from a generated table, later than retail's slot 557. The true fix is
still one retail TU with the strings, the table and its compiler-emitted initializer, which is blocked twice: no approved unit
for these addresses, and the compiler keeps the entries' parse pointers static (3340a03cf5), so retail's source form is unknown.
Follow-up: option (b) above, the bridge split by retail slot under `--order retail`, for any other entry of this shape.
Verification on the first image after landing is owed: see P32's packet. Clearance: pending.

**2026-11-12 order trial at `08725f0841` (swarm Link lane; coordinator-approved, P142).** Tool lane 2 traced P142 to the
order: the real link and every test image (`real-link.yml --link`, `diagnostic-link.yml` and srv1's `local_link.py
--diagnostic`) take the default, path order, while the census and `tu_skeleton`'s LinkGuard follow retail's address order.
One boat sandbox compiled the tree once and linked it twice from the same objects and the same stub seed (the newest local
image's): `--order path` as the control, then `--order retail`. The path image equals srv1's local image `cfe7fac489`
except for timestamps, a per-compile anonymous-namespace hash and two 8-byte deleting-destructor thunks laid out in the
other order. Neither difference comes from the order.

| | path | retail |
|---|---:|---:|
| unresolved / duplicates | 0 / 0 | 0 / 0 |
| vtable bridge: tables refused | 34 | 28 |
| image_iso defects | 1,360 | 1,353 (7 vtable slots fixed, 0 new) |
| rowed kept copies that differ from retail (`kept_copies`) | 245 | 7 |
| `.CRT$XCU` entries / changing index / changing relative order | 1,633 | 1,633 / 1,161 / 877 |
| boot (game queue, harness at master) | crash at 0x0263CA71 (retail 0x0070A8F1), the known r18 stop | crash in start-up: `_$E1+0x2c` calls 0x1000 |
| skirmish | same stop as boot | same start-up crash |

Names whose kept copy moves (15,508), by `image_iso`'s own judgement against retail's rows: 240 toward retail's copy,
2 away, 3,936 match either way, 0 match in neither order, 11,330 have no code row. The 8 worse cases of 2026-11-08 are
gone.

**Retail order fails the pass rule, and it is not switched.**
- Away 1, `_List_base<Object*, allocator<Object*>>::_List_base` (retail 0x004EC36C, row AIGroup.cpp). Retail order keeps
  HordeDispatchSpecialPower.cpp's explicit specialization, which gives the generic name retail's pooled body at 0x001EB984
  (`mov ecx, g_freelistPool00DB8FEC; call pop`). Retail names that body `_List_base<Object*,
  Rva001EB984PoolAllocator<Object*>>` (rowed in WWLib). Pin line 953 of `reverse/symbols.csv` puts the generic name at
  0x001EB984 as well, one name at two addresses (LINK-658's shape). Fix: the unit uses the pool-allocator list type, and
  that pin retires. This is not a fold proof: the bodies differ.
- Away 2, `_List_base<upgradePair, allocator<upgradePair>>::_List_base` (retail 0x002049AD). EvaCtor.cpp declares a
  private 8-byte `struct upgradePair {int a; int b;}`, so its copy allocates a 0x10-byte node where retail's allocates 0x18
  (a 16-byte element; ModuleFactory.cpp's copy is retail's). ScriptEngine_ctor.cpp has a third view, `int opaque[5]`. Fix:
  one real 16-byte `upgradePair` for all three units. No rename and no fold proof applies.
- Start-up crash, new under retail order. The initializer of `Rva007ACBC0Ww3dCmdGroup.obj` (moved from index 1,492 to 775)
  calls virtual slot 0x84 on `theDebug` (DebugPreStaticInit.cpp), which is still null when it runs. No initializer reaches
  `Debug::PreStaticInit` by direct calls within three levels in either image, so its creator is reached indirectly. Next:
  trace the path image's boot to the write of `theDebug`, then compare that initializer's retail slot with the command
  group's (slot 557's shape, P32). The 470 bridged initializers run first in both orders.

Not affected: the census and LinkGuard keep modelling retail order, so until the switch `tu_skeleton` has to judge a
merge's kept copies in path order as well (P142, tool lane 2). Evidence: `~/bfme2-ops/swarm/sweeps/link-633-order/`
(`out/summary.json`, `moved.tsv`, `crt_*.tsv`, `defects_diff.txt`, `away_callees.txt`, `prestaticinit.txt`); the images
are in the Link lane's `build/boat-run/link-20261112t020507/`. Clearance: pending.

**2026-11-12 fixes for the trial's findings (swarm Link lane).**
- Away 2 (EvaCtor): fixed in this push. EvaCtor.cpp declares the list base constructor without defining it, and Eva's
  queue element takes retail's 16-byte shape {int id; Coord3D position}. Retail folds every 16-byte list base
  constructor into 0x002049AD, and ScriptEngine's pair list and AutoDepositUpdate's upgradePair share it. Follow-up,
  not done: ScriptEngine_ctor.cpp's 20-byte `int opaque[5]` view of the same element.
- Away 1 (the pooled `list<Object*>`) is wider than a retype. Retail calls the pooled body 0x001EB984 from 16 sites; three
  units reach it through the generic name (stlport_list_objectptr_insert.cpp at 0x0047031F through pin 953,
  MoveToFormationGroupOrder.cpp at 0x00547CD2, and possibly HordeContainRva00475F61.cpp at 0x004761EF), and
  HordeDispatchSpecialPower.cpp and stlport_list_objectptr_insert.cpp define the generic name with the pooled bytes. The
  existing users of `Rva001EB984PoolAllocator` (about 17) each keep a private one-word `_List_base` view and cast to the
  generic list for every operation. The fix is one canonical pool-list allocator on `g_freelistPool00DB8FEC`, adopted by
  all of them; pin 953 retires at the end. Handed to the header lane as a class project.
- The start-up crash: `theDebug` is created by initializer #1 (`rva0003A210`) in both orders, so it is never null. In
  the retail-order boot it points at freed memory reused for the environment block. The extra initializer is Zero
  Hour's static `Debug Debug::Instance` in debug_debug.cpp (index 1,630 in path order, 607 in retail order, before the
  command group at 775), whose constructor reaches the debug allocator's GlobalFree. Retail BFME 2 constructs Debug
  only from Debug::PreStaticInit (0x00038634), and none of its 1,166 initializers constructs one. Removing the instance
  needs the 13 Zero Hour `present-unmatched` bodies that use it converted or retired first: the Link lane's debug-port
  cleanup.
- Retail order stays non-default until both are done and a re-trial passes the rule above.
