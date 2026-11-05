### LINK-083: `StlSweepR3` units instantiate a whole algorithm or container over an opaque record whose retail callees are rowed under another type

**Status: Repair landed / awaiting census (8 units, 1 duplicate retired); family Open. Updated: 2026-10-26; inspected revision: 1b06fe6829; index 5ce093a71a.**

- **Evidence / scope:** a `StlSweepR3Rva<rva>.cpp` unit holds one STLport row over an address-named
  record (`Rva<rva>Record`) and writes `template class` / `template void` instantiations to emit it.
  That emits every member and helper over the opaque record: the record's ctor/dtor/operator=/
  operator</operator==/hash are unresolved, and the emitted helpers (pinned in `symbols.csv` to
  retail addresses) are not retail's bodies. Retail's callees are already rowed, but under another
  type (the record's real element, or a placeholder method), so the names never line up.
- **Repair recipe:** define only the row as an explicit specialization (STLport 4.5.3's body)
  that calls the rowed callees by their own types (`reinterpret_cast` / pointer casts, as in
  LINK-035), then `template X::member();` where cl 7.1 would not emit it otherwise. Drop the pins
  for helpers the unit no longer emits and the `max<unsigned>` `#pragma optimize` block.
- **Completed (agent K9):**
  - 4ca752a55e `StlSweepR3Rva00218FC2.cpp` (`sort`, 67 B): calls 0x00218E09
    `__introsort_loop<Rva00218E09Record*, ..., less<>>` and 0x0021889A `Rva0021889AFinalSort`, both
    rowed in `GameFont.cpp`; 2 pins dropped. link_check with GameFont.cpp and MixFileCreatorParse.cpp:
    0 -> 67 B, partners link.
  - d5855a74e9 `StlSweepR3Rva00058A86.cpp` and `StlSweepR3Rva0002CCC3.cpp` (hash-set dtors, 57 + 67 B):
    call 0x00057FC1 (`clear` of the pair-keyed table over `Rva00057FC1Record`) and 0x002234FE
    (`clear` of `hash_map<AsciiString, AsciiString, rts::hash>`, INIMacroTable.cpp); 2 pins dropped.
    0 -> 124 B, and `AudioManagerAdjustPriorityAndVolume.cpp` (calls the 0x00058A86 dtor) 0 -> 43 B.
  - f29627cb3f `StlSweepR3Rva002BFA86.cpp` (`erase(const_iterator)`, 80 B): calls 0x00223149
    `Rva000427195::bucketIndex` and 0x002BF75A `Rva002BF75A::rva002BF75A`; 2 pins dropped; 0 -> 80 B.
    The same commit removes the unused `max<unsigned>` pragma blocks from 00058A86 and 0002CCC3.
  - Each `./build.sh` exact; RvaPairCopyCallFamily.cpp, PlayerXferStringMaps.cpp,
    Rva002BF75AFree.cpp, StlSweepR3Rva0002CD71.cpp, StlSweepR3Rva00057FC1.cpp, INIMacroTable.cpp
    still link. Preview total 0 -> 314 B; `hatch_counters.py --update` not run (9 pragma lines down).
  - 6edfe79e8d `StlSweepR3Rva003F318C.cpp` (`vector::operator=`, 206 B, LivingWorldRegionConnection
    elements): calls 0x003F2CD6 `vector<BfmeStringRecord000B9534>::_M_allocate_and_copy<LivingWorldRegionConnection*>`
    (protected: reached through a derived view), 0x00565A24 `ConnectionVec::Rva00565A24_ScrapStorage`,
    0x003F325A `Rva003F325ACopy`, 0x003F0CA1 `Rva003F0CA1_DestroyRange`, 0x003F29D2 `Rva003F29D2_CopyRange`
    (the two copy rows through tag-taking casts: retail pushes a fourth tag argument); 6 pins dropped.
    0 -> 206 B. Calling a declared-only explicit specialization of the real `<vector>` member template
    `_M_allocate_and_copy` ICEs cl 7.1 (C1001, P2 main.c:148) from any context (derived view, template
    view, own member, pointer-to-member), so the unit spells a minimal `_STL::vector` shape instead of
    including `<vector>` (Rva00569F0CAssign.cpp precedent); same bytes.
  - 827dd7e8a1 `StlSweepR3Rva00332613.cpp` and bf8a1b680e `StlSweepR3Rva00337D21.cpp` (`__introsort_loop`,
    135 B each): call 0x00331716 `__median<int, less<int>>` / 0x00335CFD `Rva00335CFMedian` (comparator
    as a fourth argument through a cast), the pivot copy ctors 0x00331962 `BfmeStringRecord00331962` /
    0x003371B1 `Rva003371B1`, 0x00331D10 / 0x00337655 `__unguarded_partition<S4SortElem12/20*>` (cast so
    the by-value pivot parameter is the copy ctor's record) and 0x0033254D `Rva0033254DPartial` /
    0x00337C55 `partial_sort<Rva003371B1*, Rva00337C55Less>`. The pivot record needs a destructor in
    scope (inline, or declared when rowed: 0x003372B7 `??1Rva003371B1`) or the `mov [ebp+0Ch],esp` EH
    spill of the argument slot disappears. Each drops a copy-ctor `/alternatename`, a `max<unsigned>`
    `#pragma optimize` block and 5 pins; 0 -> 135 B each. The five callees were already rowed, so no
    renames were needed.
  - Each `./build.sh` exact; provider units (Rva003F3F27.cpp, Rva003F2CD6.cpp,
    LivingWorldRegionConnectionHelpers.cpp, Rva003F325ACopy.cpp, stlport_int_algorithm_bodies.cpp,
    StringRecordCopyBFME2.cpp, stlport_introsort_loop_s4sortelem12_002e1b60.cpp, Rva0033254DPartial.cpp,
    stlport_sort_s4sortelem20.cpp, Rva00335CFMedian.cpp, Rva003371B1Copy.cpp, Rva003371B1Dtor.cpp,
    stlport_unguarded_partition_s4sortelem20.cpp, stlport_partial_sort_rva00337c55.cpp) still link.
    Preview total for the family now 0 -> 790 B.
  - 33a4c45d14 `StlSweepR3Rva00212A16.cpp` (`hashtable::_M_insert`, 68 B): calls 0x00212858
    `Rva000427195::rva00212858` (resize), 0x00223149 `Rva000427195::bucketIndex` and 0x00212354
    `Rva000427195::rva00212354` (new node), the same three calls as the rowed twin Rva000A7A63Insert.cpp;
    3 pins and the `max<unsigned>` pragma block dropped. 0 -> 68 B; Rva00212858Resize.cpp,
    PlayerXferStringMaps.cpp, Rva00212354NewNode.cpp, Rva00212A5AInsert.cpp, Rva000A7A63Insert.cpp and the
    caller LivingWorldManagerSoundTable.cpp still link. Family preview total 0 -> 858 B.
  - 1b06fe6829 `StlSweepR3Rva000B0298.cpp` retired as a LINK-060 duplicate: 0x000B0298 is rowed and
    links as `?rva000B0298@Rva000B0298@@QAEXXZ` (Rva000B0298Clear.cpp, called by
    VectorOverflowRva000B059B.cpp); the sweep `_M_clear` row was uncalled. Row in deleted_rows.csv; +0 B.
- **Remaining, same shape (inspected 2026-10-26, no edit):** `StlSweepR3Rva0051F7AD.cpp` (operator=
  over 12-byte `ProductionPrerequisite::PrereqUnitRec`; callees 0x004EE233, 0x004EE540, 0x0051EC31,
  0x0052C37A, 0x004EE1E2 all rowed; draft follows the 003F318C shape) and `StlSweepR3Rva003F40EF.cpp`
  are file-claimed by another seat (StarkillerHDX, link seat w6). `StlSweepR3Rva00627B10.cpp`
  (`__make_heap`) likewise claimed. `StlSweepR3Rva00551B02.cpp`, `StlSweepR3Rva005838DC.cpp`,
  `StlSweepR3Rva005AFEDB.cpp`, `StlSweepR3Rva001DE3E3.cpp` and `StlSweepR3Rva001FDEBC.cpp` were edited by
  other seats today (f664738191, 7e3d3a672f) and were left alone. Every other R3 unit links in preview
  (a 2026-10-26 link_check sweep of all 139; StlSweepR3Rva00214B22.cpp needs its partner
  stlport_vector_rva00214adc_destroy.cpp).
- **Same shape outside R3 (attempted 2026-10-26, agent K9, no edit landed):** `StlSweepW5Rva001506BF.cpp`
  (`vector::_M_fill_insert`, 222 B) and its twins `StlSweepW5Rva0015079D.cpp` / `StlSweepW5Rva0015087B.cpp`
  instantiate over an 8-byte element whose callees are rowed under Rva0014F480 / Rva0014F4A1 /
  Rva0014F4C2. An explicit specialization over a stub vector reaches 212/222 B; it needs a non-POD
  `__false_type` (cl zero-fills an empty POD tag temporary passed to an opaque callee) and a pre-copy
  `_M_finish` local, and 10 bytes of frame-slot colouring remain. Draft and variants:
  `reverse/attempt_support/stlsweep-w5-1506bf-fill-insert-20261026.md`.
  `StlSweepW4Rva000C225D.cpp` (260 B, BfmeStringRecord000B94D2 callees) reaches 254/260 B with the
  same draft: only the `_M_finish - __n` spill slot (`__x` home instead of retail's `__n` home) and
  the two `__uninitialized_copy` tags just below it differ. The W4/W5 `_M_fill_insert` units 001524F9,
  0017422D, 00215949, 003F53DA, 005205DA and 0039C415 have the same shape and probably hit the same
  wall; solve the spill-slot choice once before drafting them.
- **Related leads not done:** `Rva008312E0StringReplace.cpp` / `Rva008314E0StringReplace.cpp`
  (/Od /Ob1) emit `erase`/`replaceBase` COMDATs that retail calls out of line at 0x00012150
  (`basic_string<char>::erase`) and 0x0002A610 / 0x0002A730 (`BfmeStrV24::bfmeReplaceV24`, last
  parameter spelled `int` where the caller passes a tag reference). Calling those rows by type means
  stubbing `basic_string<char>` in a unit that stubs its own STL; frame-slot effects under /Ob1 untested.
- **Census confirmation:** the K9 repairs (00218FC2, 00058A86, 0002CCC3, 002BFA86, 003F318C,
  00332613, 00337D21, 00212A16) are linked in the census at `73061d9452` (2026-10-27 14:34);
  0051F7AD (below) was still unlinked there and previews LINKS. Checked 2026-10-28.

**Assigned R3 emission cleanup (2026-10-27, inspected `97c23353111e60304b56434c02d20bee3465d83f`, ordinary-preview index `5ce093a71a`, retail-truth-4):** `StlSweepR3Rva003F40EF.cpp` now instantiates only its rowed `swap` instead of uninitialized-copy, fill, sort and heap algorithms. Both existing rows remain exact, including the 75-byte parent and its 10-byte EH handler; EH is EXACT. Its unrelated `_Construct` and comparison unresolveds disappear, changing U5 to U3. The remaining native callees are the already rowed ArmySummary copy at 0x0040E96D (384 B), assignment at 0x0040EAED (399 B) and destructor at 0x0040E499 (155 B), so the row and consumer names need a coordinated naming-lane repair. `StlSweepR3Rva00627B10.cpp` now instantiates only its rowed comparator `make_heap`, retaining its 28-byte row and U4/L1/S1. Its native callee 0x006279B0 is already rowed as `push_heap<S4SortElem24 *, S4Cmp009F4BF0>` (93 B); the opaque record/algorithm family is still unresolved. Both units and `StlSweepR3Rva0051F7AD.cpp` drop their unused unsigned-max optimization blocks, removing nine pragma occurrences. The vector-assignment unit retains its original early `_algobase.h` include: removing that include changes the 206-byte row, whereas removing only the unused optimization block preserves it. Its U3/L2/S2 and native 0x004EE233, 0x004EE540, 0x0051EC31, 0x0052C37A and 0x004EE1E2 provider prerequisites remain. No row, pin or cross-instantiation cast changed. The 153-unit current-provider comparison adds no blocker and preserves every previously linking unit. Only the two unrelated swap blocker names are cleared in ordinary-preview scope; census confirmation pending. No assigned unit is fully cleared.


**Vector-assignment provider repair (2026-10-27, inspected `ad2bb03703`,
ordinary-preview index `bf3dd31211`):**
[The native-provider proof](../../reverse/attempt_support/vector-51f7ad-provider-link-20261027-codexb4.md)
clears `StlSweepR3Rva0051F7AD.cpp` in the nine-source ordinary-preview scope:
U3/L2/S2 becomes LINKS, 0 -> 206 authored bytes. Its explicit C++ specialization
calls the existing owners at 0x004EE233, 0x004EE540, 0x0051EC31, 0x0052C37A
and 0x004EE1E2 without recovering a new element name. All 41 cohort rows and
two EH graphs remain exact; all seven previously clean units stay clean.
The target has six owner bindings and no wrong-binding findings, and has a
strict reusable byte-verification receipt. Six obsolete pins and their hatch
occurrences are retired. The ProductionPrerequisite TU keeps its separate
blockers and identity debt; its rowed copy worker is not a whole-unit clearance.
The element remains opaque: the earlier PrereqUnitRec identification is not
proved by shared callees. Remaining: reconcile that identity and downstream
provider contracts; confirm strict recursive closure and the next census.
No census-linked-byte or image-ownership gain is claimed.

**Real element names for two R3 rows (2026-10-27, seat halilkkaya-lk3,
inspected `d16a31e4dc`, index `73061d9452`, retail-truth-4):**
- `StlSweepR3Rva003F40EF.cpp` is `_STL::swap<ArmySummary>`. Target facts: the
  75-byte body builds a 0x68 temporary through 0x0040E96D, assigns twice
  through 0x0040EAED and destroys the temporary through 0x0040E499; those rows
  are `ArmySummary`'s copy constructor, `operator=` and virtual destructor.
  The unit now declares only those three members (no ZH or placeholder
  record) and instantiates the real STLport `swap`; the row and its
  `__ehhandler$` row are respelled `??$swap@VArmySummary@@@_STL@@...`, and the
  one consumer (`LivingWorldBattle::BattlePlayer::SwapArmies`, 0x003F427D)
  calls it under that name. The three `Rva003F40EFRecord` pins are dropped.
  `./build.sh` 18/18 rows exact across both sources (EH labels verified past
  renumbering); link_check: the unit 0 -> 85 B, LivingWorldBattle.cpp,
  ArmySummaryCopyBFME2.cpp and ArmySummary.cpp still LINKS. The 0x00783FBC
  unwind funclet stays in `uw_gen_001.cpp` (LINK-095 lane).
- `StlSweepR3Rva00627B10.cpp` is `push_heap<S4SortElem24 *, S4Cmp009F4BF0>`,
  not `make_heap`. Target facts: 0x00627B10 pushes first, last, the
  comparator and two zero tags to 0x006279B0, which has no loop: it copies
  `last[-1]` and calls `__push_heap` 0x00627330 once with hole
  `(last - first) - 1` and top 0, which is STLport 4.5.3's
  `__push_heap_aux(first, last, comp, Distance *, Tp *)`, not `__make_heap`.
  0x006279B0 had been rowed as the three-argument `push_heap` (same bytes:
  the callee ignores the tags). Both rows are respelled with their real
  STLport names (`__push_heap_aux<S4SortElem24 *, S4Cmp009F4BF0, int,
  S4SortElem24>` in `stlport_push_heap_s4sortelem24.cpp`; `push_heap` in the
  sweep unit, which declares the helper so the call stays out of line as in
  retail). The `__make_heap<Rva00627B10Record *>` pin is dropped. Neither
  address has a direct caller; the partition manager's query 0x00628040
  inlines its own `__push_heap_aux` and still LINKS. `./build.sh` 2/2 exact;
  link_check: the unit 0 -> 28 B; stlport_push_heap_s4sortelem24.cpp,
  stlport_heap_s4sortelem24.cpp, stlport_pop_heap_s4sortelem24.cpp and
  partitionmanager_impl.cpp still LINKS.
- Remaining R3 units in this family: `00551B02`, `005838DC` and `005AFEDB`
  stay blocked on TU approval (LINK-078); the 0x001DE3E3/0x001FDEBC hashtable
  assignments are second claims of linked rows (LINK-060).
- Census confirmation: awaiting the next census.

2026-11-04: 0x00627B10 now belongs to `Code/Libraries/Source/partitionmanager/PartitionManagerImpl.cpp`; byte/link preview and consolidation audit: [partition STL merge](../../reverse/attempt_support/partition-stl-merge-20261104-codexb5.md).
- 2026-11-04: 0051F7AD now uses STLport vector without losing its 206-byte match or preview link; AptTimeLine merge dry run accepts it. [Prerequisite evidence](../../reverse/attempt_support/apt-timeline-vector-reconcile-20261104.md); no census gain claimed.

- 2026-11-04: 0051F7AD is merged into its approved AptTimeLine.cpp TU (one source removed; 136/136 functions exact; destination and assignment consumer preview LINKS). Broader audit remains inconclusive on the stale 0CreateAHeroManager21FE49.cpp receipt and older index; carry to census. [Merge audit](../../reverse/attempt_support/apt-timeline-vector-reconcile-20261104.md).

- 2026-11-05: AttributeModifierStore range-destroy specialization removes the STL donor's C2908 merge blocker with identical object facts; next reconcile the vector class/destructor C2910 conflict. [Prerequisite checks and remaining blockers](../../reverse/attempt_support/attribute-range-destroy-specialization-20261105-codexb5.md).
