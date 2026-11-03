### LINK-035: `StlSweepR3` vector-destructor units instantiated the whole `vector<RecordN>`
Status: Open (6 of 7 repaired). Updated: 2026-10-26; inspected revision: 018ace6021; index d1f046749a.
Evidence / affected units: `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva<rva>.cpp` units holding one
63 B STLport `vector<RvaNRecord>` destructor (or `_M_clear`) row. Each wrote `template class
_STL::vector<RvaNRecord>;`, which emits every member: the record's ctor/copy/assign/dtor and `_Construct`
were unresolved, and its own `_Destroy<RvaNRecord *>` copy was not retail's body (the name is only pinned).
Retail's destructor calls an out-of-line two-argument range destroy.
Completed (each in its own commit, `./build.sh` exact, partners still link):
- 0x004F7D7F (61b147288f), 0x005F9813 (1a419a0c1d), 0x00577EB2 (02b625c1f2), 0x005E2857 (1f0a322ceb):
  callee 0x005F97BC, rowed `_Destroy<TreeHintRef00217D4C *>` (StlportVectorEraseRangeFamily.cpp).
- 0x0022DCDA (79e9273e2d): callee 0x0022D941, rowed `?Rva0022D941Destroy@@YAXPAURva0022CD2A@@0@Z`.
- Recipe: instantiate only `~vector`, as an explicit specialization whose body calls the rowed callee
  through `reinterpret_cast` (as `BattlePromptConstructorLifetimes.cpp` does), followed by
  `template _STL::vector<RvaNRecord>::~vector();` so cl 7.1 emits the otherwise unreferenced specialization.
  This also drops the three `#pragma optimize` lines per unit; `hatch_counters.py --update` has not
  been run to tighten the register. A forced-inline forwarding `_Destroy` specialization was tried
  first: it loads both bounds into registers before the EH state store, so the bytes differ.
- link_check: 0 -> 324 B over the five units.
- 0x00214B22 (c9700d27ca): retail 0x00214B09 is called with two pushed arguments by 0x00214B22 and
  0x004043AE (capstone over game.dat), so its row was respelled from 3-argument `__destroy_aux` to
  `??$_Destroy@PAVRva00214ADC@@@_STL@@YAXPAVRva00214ADC@@0@Z` (explicit instantiation in
  `stlport_vector_rva00214adc_destroy.cpp`, still exact; the one consumer spelling, the erase forwarder in
  `StlportVectorEraseRangeDeferred.cpp`, respelled with it). Then the recipe: link_check 0 -> 73 B; the
  provider, `StlportVectorEraseRangeDeferred.cpp` and the two 0x00214ADC units still link.
Remaining / next check:
- `StlSweepR3Rva000B0298.cpp` (`_M_clear`, 30 B, callee 0x000AFF52): 0x000AFF52 is likewise a
  two-argument `_Destroy` rowed as `__destroy_aux<Rva00111B25Record *>` (StlSweepW5Rva000AFF52.cpp), and
  respells the same way. But 0x000B0298 itself carries TWO matched rows: this unit's `_M_clear` and
  `?rva000B0298@Rva000B0298@@QAEXXZ` (`Code/GameEngine/Source/GameClient/Rva000B0298Clear.cpp`, a
  frameless twin over `EvaMessageInfo` calling `_Destroy<EvaMessageInfo *>`). The pin
  `?_M_clear@?$vector@UEvaMessageInfo@@...` at 0x000B0298 and the EH twin 0x000B0254
  `~vector<EvaMessageInfo>` suggest the real identity is `vector<EvaMessageInfo>::_M_clear`. Resolve
  the over-claim first (keep one row; retire the other through `deleted_rows.csv`), then link the
  survivor; do not just apply the recipe to the duplicate row.
- The `_Destroy<RvaNRecord *>` pins in `reverse/symbols.csv` for the six repaired units (incl.
  `_Destroy<Rva00214B22Record *>` at 0x00214B09) look unreferenced now; check every object before dropping them through the register's path.
Clearance: the five units preview LINKS against index 47e030bafc with current objects; 0x00214B22 previews
LINKS against index d1f046749a with current objects. Census confirmation: all six repaired units
(0x004F7D7F, 0x005F9813, 0x00577EB2, 0x005E2857, 0x0022DCDA, 0x00214B22) are linked in the census at
`73061d9452` (2026-10-27 14:34); `StlSweepR3Rva000B0298.cpp` was retired as a LINK-060 duplicate
(78f462d97d). Checked 2026-10-28 by seat halilkkaya-lk3.

**Assigned `_M_clear` recheck (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`):** `StlSweepR3Rva000B0298.cpp` remains U5/L1/S1 with current providers. Its 30-byte row still calls 0x000AFF52, whose 25-byte owner remains spelled `__destroy_aux<Rva00111B25Record*>`; the second 0x000B0298 row in Rva000B0298Clear.cpp remains present. Both provider and duplicate owner preview LINKS. No source edit or repeat of the failed forced-inline forwarding recipe was made. Raw native evidence and paired previews are in `build/c136-r3sweep/`; `build/link-report.md` maps the receipts. Resolve the duplicate row and destroy signature together before the next repair; clearance and census confirmation remain pending.
