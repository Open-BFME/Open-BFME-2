### LINK-633: static initializers run in the wrong order: the bridge runs first, and object order is path order (P32)
Status: Open. Updated: 2026-11-08; inspected revision: 8a30049c6a (swarm Link lane).

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

Clearance: pending.
Census confirmation: not claimed.
