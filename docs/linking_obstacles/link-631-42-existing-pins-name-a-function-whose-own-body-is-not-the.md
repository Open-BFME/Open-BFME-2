### LINK-631: 42 existing pins name a function whose own body is not the body at their address
Status: Open. Updated: 2026-11-08; inspected revision: c32d83389b (swarm Link lane).

Evidence / affected units: pin_admission refuses a real name stacked on an address that carries another
real name unless a fold proof holds, but only for a pin being added; pin_consistency judges only one name
pinned at several addresses. Older pins were never re-judged, and the resolver keeps lending them to every
caller of their name: LINK-629's 0x000365F0 (`list<FXNugget*>` copy constructor over `StringBase<char>`'s)
gave FXList's copy constructor 0x0052BD3A a false match. A read-only sweep replayed the admission proof
for all 2,716 pins that stack a real name on a named address (of 9,308 pins, 4,310 with real names):

| class (pin notes) | pins | proven fold | wrong body (own / callee) | name also elsewhere | proof stopped | no unit defines it |
|---|---:|---:|---:|---:|---:|---:|
| no fold reason | 1,323 | 373 | 26 / 27 | 19 | 56 | 822 |
| fold mentioned, no `fold-proof=` | 797 | 482 | 16 / 9 | 24 | 85 | 181 |
| `fold-proof=` recorded | 596 | 579 | 0 / 5 | 0 | 6 | 6 |

The 42 own-body cases (23 differ in size, 8 in bytes, 11 only in relocations; 8 are BFME 1 donor-sweep
pins) are listed in full, with every matched caller, in
[own-body-differs.tsv](../../reverse/attempt_support/pin-audit-20261107/own-body-differs.tsv). 22 of them
have matched rows referencing the name, 31 caller edges in all: each such caller is a possible false
match. Judged per case (column `judgement` in the TSV; no pin retracted):

- **The pin names another function (2).** 0x000365F0 and 0x00036E70, the two LINK-629 pins (0x00036E70's own name is rowed and matched at 0x004EC395).
- **The wrong body is ours (29).** Our view of a record or class compiles a body retail never had: invented records (Bfme*/Rva*/Pod), TU-private views (`DynamicVectorClass` texture handles twice, `RefPtr`, LightSubPoint's alloc-proxy spelling), folds that must hold but compile apart (a pointer element against a 4-byte one), and two where the owner row is our placeholder for the same class (`BfmeObject476` is `PlayerTemplate`, per WorldBuilder: rename the owner, keep the pin). Three families are one mistake each:
  - **ProductionPrerequisite** (0x002CF99D `_Construct`, 0x004EE1A9 copy ctor, 0x00395928 `allocate`; 9 caller edges): our `PrereqUnitRec` view copies trivially (`_Construct` 18 B) where retail's record copy calls out (45 B; the fold owner is a string record), and `allocate` and the copy constructor differ by its size. The pins' fold claims look right; `PrereqUnitRec`'s layout is the fix, and the vector/uninitialized-copy rows that call through these pins are the ones to recheck.
  - **EvaMessageInfo** (0x003F6B24, 0x00101ECF, 0x00101F5C; EvaMessageVectorAssign.cpp): our record differs from retail's string record 0x00111ACF by its size.
  - **W3DAnimationInfo** (0x00469C61, 0x0047008E; BFME 1 donor-sweep pins): our view keeps Zero Hour's `AsciiString` member, while the body retail calls where the donor does copies a 16-byte plain record.
- **Cannot tell (11).** Real types on both sides and nothing here decides it: 0x003025A5, 0x000F0BF1, 0x00288978, 0x0033BE70 (a fold across `BitFlags<17>` and `BitFlags<11>` is unlikely, so the pin is suspect), 0x0016CC80, 0x00616730, 0x003A8D15 (FX ConcreteModuleTemplate, LINK-584's path), 0x001F0534, 0x004C3121, 0x00023850, 0x00211E58.

Worst by matched callers:

| pin | pinned name | address carries | differs in | matched callers | judgement |
|---|---|---|---|---|---|
| 0x002CF99D | `??$_Construct@UPrereqUnitRec@ProductionPrerequisite@@U12@…` | `??$_Construct@UBfmeStringRecord002CF5B1@@U1…` | size | 4 | ours |
| 0x0014F3C4 | `?setup@FreelistProxyHead@@QAEXPBXPAX@Z` | `??0?$_STLP_alloc_proxy@IUBfmeScriptSlotAddr…` | size | 3 | ours |
| 0x004EE1A9 | `??0PrereqUnitRec@ProductionPrerequisite@@QAE@ABU01@@Z` | `??0PerTurnStats@LivingWorldScoreKeeper@@QAE…` | size | 3 | ours |
| 0x003025A5 | `??0?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UCo…` | `??0?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAs…` | bytes | 2 | cannot tell |
| 0x00395928 | `?allocate@?$allocator@UPrereqUnitRec@ProductionPrerequisi…` | `?allocate@?$allocator@UBfmeE12@@@_STL@@QBEP…` | size | 2 | ours |
| 0x0002C552 | `?_M_create_node@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@…` | `?_M_create_node@?$_Rb_tree@VAsciiString@@V1…` | size | 1 | ours |
| 0x000365F0 | `??0?$list@PAVFXNugget@@V?$allocator@PAVFXNugget@@@_STL@@@…` | `??0?$StringBase@D@@AAE@ABV0@@Z` | size | 1 | pin |
| 0x0006F7BD | `??1Rva006F7BD@@UAE@XZ` | `??1RTS3DScene@@UAE@XZ` | relocations | 1 | ours |
| 0x000F0BF1 | `?Resize@?$VectorClass@VTCBClass@TCBSpline3DClass@@@@UAE_N…` | `?Resize@?$VectorClass@VVector3@@@@UAE_NHPBV…` | relocations | 1 | cannot tell |
| 0x00101ECF | `??$__uninitialized_copy@PBUEvaMessageInfo@@PAU1@@_STL@@YA…` | `??$__uninitialized_copy@PBUBfmeStringRecord…` | bytes | 1 | ours (likely) |
| 0x00101F5C | `??$_M_allocate_and_copy@PBUEvaMessageInfo@@@?$vector@UEva…` | `??$_M_allocate_and_copy@PBUBfmeStringRecord…` | size | 1 | ours (likely) |
| 0x00155490 | `?Resize@?$VectorClassWide@UTextureStatisticsStructWide@@@…` | `?Resize@VectorClassBfmeThingFT@@UAE_NHPBVBf…` | relocations | 1 | ours |

Both LINK-629 pins are in the list (0x000365F0 and 0x00036E70). The suspect family LINK-629 named,
`push_back` 0x0005548F, `insert` 0x005925E2 and `_M_create_node` 0x000B6447 for `FXNugget*`, is proven:
real folds. `insert` and `_M_create_node` already carry `fold-proof=`; only `push_back<FXNugget*>` lacks it.
Five pins with a recorded `fold-proof=` now fail on a callee (0x004DFCB0 vector<SpecialPowerTemplate
const*>::push_back, 0x002888D4, 0x0041F4E5 twice, 0x00388F63): their proofs' premises moved after
admission. 855 pins without `fold-proof=` are proven folds and only lack the note.

Completed: the sweep, and `pin_consistency.py --audit` (shadow, 69accdc3bc + review fixes 18b8469364,
awaiting review) which replays it on demand. No pin was edited.

Remaining / next check: fix our side first where the judgement says ours (the record layouts and private views; the ProductionPrerequisite record is the largest), then confirm each remaining case against its matched callers before retracting:
a byte-verified caller outranks the pin (pin_consistency --clear-cut's warning), and a different body
can also be our defining unit compiling the name unlike retail. The ProductionPrerequisite record
family (0x002CF99D, 0x004EE1A9, 0x00395928) looks like one misidentified record type. Retract or
respell through pin_admission / rename.py, rebuild each caller, and expect some callers to go red: those
were false matches. Re-run `pin_consistency.py --audit` after each batch.

#### 2026-11-08: the ProductionPrerequisite family, re-judged (swarm static-defects lane, seat3)

This is retail disassembly plus scratch compiles. No pin, row or ledger was changed.

**PrereqUnitRec's layout is already retail's.**
- Retail 0x002CF5B1 copies a 12-byte `{dword, dword, AsciiString}` record. It calls
  StringBase<char>'s copy at 0x004365F0, and `_Construct` 0x002CF99D calls 0x002CF5B1.
- Our unit compiles Zero Hour's `PrereqUnitRec {const ThingTemplate *unit; Int flags;
  AsciiString name;}`. Its copy constructor (35 B) is the same instruction sequence as
  0x002CF5B1.

**The string member's class is the defect, not its size.**
- ProductionPrerequisite.cpp compiles against Zero Hour's inline AsciiString
  (`/Ireference/shims/zh_ascii_outofline`). MSVC then emits `_Construct` without
  retail's EH frame: 18 B instead of 45.
- A minimal probe isolated the cause. The AsciiString header alone decides it:
  BFME 2's AsciiString gives 45 B under STLport 4.5.3 or 4.6, with an implicit or a
  user copy constructor. Zero Hour's gives 18 B in every case.
- In scratch, swapping the unit to `/Ireference/shims/bfme2_ascii_common
  /Ireference/shims/bfme2_ascii` makes the pinned `_Construct` 0x002CF99D compile to
  retail's 45-byte body.
- `allocate` (0x00395928) is a separate configuration difference. Ours calls
  dllimport `__new_alloc::allocate`; retail's 28-byte body calls 0x004307F0 with a
  0 hint. `bfmealloc` clashes with this unit's explicit instantiations (C2950), so
  that needs its own pass.

**0x004EE1A9 and three rows are vector<LivingWorldScoreKeeper::PerTurnStats>'s, not PrereqUnitRec's.**
- 0x004EE1A9 stores vtable 0x00C62A28, which is `??_7PerTurnStats@LivingWorldScoreKeeper@@6B@`,
  then copies three 16-bit fields. It is rowed as PerTurnStats's copy constructor,
  and the `??0PrereqUnitRec@...` pin stacked on it is wrong.
- These rows call 0x004EE1A9 and sit in LivingWorldScoreKeeper.cpp's approved
  tu_map range (0x004EE113..0x004EE233), next to the rowed
  `_Construct<PerTurnStats>` at 0x004EE1D0:
  - 0x004EE1E2 `__uninitialized_copy` and 0x004EE20B `__uninitialized_fill_n`, both
    rowed in ProductionPrerequisite.cpp under PrereqUnitRec names.
  - 0x004EE233 `_M_allocate_and_copy`, rowed in Rva004EE233AllocateCopy.cpp.
- They matched only because REL32 resolution lends them the wrong pin.
- Retail's real PrereqUnitRec helpers are 0x004F5097 and 0x004F50BD. Both are only
  pinned today. They call `_Construct` 0x002CF99D out of line, and the real overflow
  0x004F5165 and push_back 0x004F5243 call them.
- Under the BFME 2 AsciiString, 0x004EE1E2 and 0x004EE20B go red in
  ProductionPrerequisite.cpp; the other 4 of 6 rows stay exact. That is expected:
  they were false matches.

**Rehoming the three rows (scratch, LivingWorldScoreKeeper.cpp).** I declared
`PerTurnStats(const PerTurnStats &)` and explicitly instantiated the three helpers.
- 0x004EE233 `_M_allocate_and_copy<PerTurnStats*>` is exact once
  `allocator<PerTurnStats>::allocate` has a home at 0x00395928 (a fold pin
  through pin_admission).
- 0x004EE1E2 and 0x004EE20B still miss on one point: the unit calls
  `_Construct<PerTurnStats>` out of line, where retail inlines it. That looks like
  an inlining-flag difference for this region; it is untested.

**Order of work.**
1. Rehome 0x004EE1E2, 0x004EE20B and 0x004EE233 as PerTurnStats helpers in
   LivingWorldScoreKeeper.cpp. This needs the inlining question settled and a fold
   pin for `allocate<PerTurnStats>`.
2. Retract the `??0PrereqUnitRec` pin at 0x004EE1A9 (Link lane).
3. Move ProductionPrerequisite.cpp to the BFME 2 AsciiString. This depends on the
   shared AsciiString work (Merge lane 2's string_base.h) or the
   `bfme2_ascii_common` include pattern. The ProductionPrerequisite class scope
   intersects the ThingTemplate header seat's claim (StarkillerHDX@fleet, w14) through
   ProductionPrerequisiteIsSatisfied_ProductionPrerequisite_isSatisfied.cpp.
4. Row 0x004F5097 and 0x004F50BD under the PrereqUnitRec names in place of their pins.

#### 2026-11-08 (later): the vector<PerTurnStats> cluster, and why the rehome is one batch

**The inlining question is settled; no flag is involved.** LivingWorldScoreKeeper.cpp already compiles
at the region default (/O1 /arch:SSE /G7). Retail's PerTurnStats has three `short`
members (+4, +6, +8; V3PolyCopyCtors.cpp spells them `Short`) and an implicit copy constructor.

In scratch, I changed the unit's view from `char m_4[2]; char m_6[2]; int m_8;` to three
`short`s, with `xfer` reading them directly and no declared copy constructor. The results:
- All 78 of the unit's row addresses stay exact.
- The unit emits all five retail bodies byte-exact:
  - copy constructor 0x004EE1A9
  - `_Construct` 0x004EE1D0
  - `__uninitialized_copy` 0x004EE1E2
  - `__uninitialized_fill_n` 0x004EE20B
  - `_M_allocate_and_copy` 0x004EE233
- 0x004EE233 needs `allocator<PerTurnStats>::allocate` admitted as a fold pin at
  0x00395928, with `fold-proof=` this unit.
- A declared out-of-line copy constructor is what stops the inlining: it gives
  `_Construct` an EH frame. StlportConstructCopySiblings.cpp only reaches the
  18-byte body through a `throw()` specialization.
- 0x004EE1A9 and 0x004EE1D0 are in this unit's approved range too. Their rows
  (V3PolyCopyCtors.cpp, StlportConstructCopySiblings.cpp) move with the batch, so
  no second definition remains.

**Four more matched rows reach these bodies through the PrereqUnitRec names.** These are retail
direct calls; each object's relocation is named:

| row | unit | calls (as) |
|---|---|---|
| 0x004EE55E `Rva004EE55EVector::reserve` | StlVectorReserveProviderRepairs.cpp | 0x004EE233 (`_M_allocate_and_copy<PrereqUnitRec*>`) |
| 0x004EE6D0 `Rva004EE6D0::rva004EE6D0` (insert overflow; push_back 0x004EE9B1) | Rva004EE6D0Insert.cpp | 0x004EE1E2 and 0x004EE20B (PrereqUnitRec), 0x004EE1A9 (PerTurnStats) |
| 0x0051ED0A `Rva004EE501` copy constructor | AptTimeLine.cpp | 0x004EE1E2 (PrereqUnitRec) |
| 0x0051F7AD `vector<Rva0051F7ADRecord>::operator=` | AptTimeLine.cpp | 0x004EE233 and 0x004EE1E2 (PrereqUnitRec) |

These are vector<PerTurnStats>'s reserve, insert overflow and push_back, copy
constructor and `operator=`. AptTimeLinePlayer's `m_20`, spelled
`vector<Rva0051F7ADRecord>`, is a vector<PerTurnStats>: the time line's per-turn
score graph.

Retracting the three wrong rows on their own would turn these four callers red.
`_M_allocate_and_copy<PrereqUnitRec>` would resolve nowhere, and
`__uninitialized_copy<PrereqUnitRec>` would resolve only to retail's real 0x004F5097.
So the rehome is one batch, with the callers respelled to PerTurnStats:
1. LivingWorldScoreKeeper.cpp: the view fix, plus explicit instantiations of the three helpers.
2. Remove PerTurnStats from V3PolyCopyCtors.cpp and from StlportConstructCopySiblings.cpp's
   `throw()` specialization.
3. Admit the `allocate<PerTurnStats>` fold pin.
4. Retract 0x004EE1E2, 0x004EE20B and 0x004EE233 (deleted_rows.csv), and delete
   Rva004EE233AllocateCopy.cpp, the unit's only row.
5. Row the five bodies in LivingWorldScoreKeeper.cpp.
6. Respell the element of the four callers' views, in StlVectorReserveProviderRepairs.cpp,
   Rva004EE6D0Insert.cpp and AptTimeLine.cpp (136 rows; its explicit specializations at
   lines 599-600, 913-916, 966-977 and 1109 name these types).
7. Retract the `??0PrereqUnitRec` pin at 0x004EE1A9.

Only after that does `__uninitialized_copy/_fill_n<PrereqUnitRec>` resolve to retail's real
0x004F5097 and 0x004F50BD alone. Scratch scripts are on srv1 seat3:
`build/scratch_defects/perturn_v2.py` and `prereq46.py`.

**Claim conflict (steps 3 and 4 of the earlier order).** `class:ProductionPrerequisite` cannot be claimed.
The ThingTemplate header seat (StarkillerHDX@fleet, note "header seat w14") holds a footprint
that includes ProductionPrerequisiteIsSatisfied_ProductionPrerequisite_isSatisfied.cpp. Moving
ProductionPrerequisite.cpp to the BFME 2 AsciiString waits for that seat and for string_base.h.

#### 2026-11-08: the PerTurnStats batch, steps 1-3 landed and 4-7 blocked

**Landed, each verified on its own:**
1. LivingWorldScoreKeeper.cpp spells PerTurnStats as retail did: three `short`s and an
   implicit copy constructor. It instantiates `__uninitialized_copy`, `__uninitialized_fill_n`
   and `_M_allocate_and_copy` for PerTurnStats (80/80).
2. The rows for 0x004EE1A9 (copy constructor) and 0x004EE1D0 (`_Construct`) moved into
   LivingWorldScoreKeeper.cpp, their approved TU (`add_match --replace-existing`). The
   hand-written copy in V3PolyCopyCtors.cpp and the `throw()` `_Construct` specialization in
   StlportConstructCopySiblings.cpp are gone (110/110 across the three units).
3. `allocator<PerTurnStats>::allocate` is pinned to 0x00395928 through `pin_admission --add`,
   with `fold-proof=` LivingWorldScoreKeeper.cpp. Pin consistency is OK.

Checked after a census index refresh (index 2026-11-08 04:34 at a6dea28a09). Every
checked unit links, including the callers that steps 4-7 would respell.

| Unit | LINKED bytes |
|---|---|
| LivingWorldScoreKeeper.cpp | 3,425 -> 3,485 |
| V3PolyCopyCtors.cpp | 667 -> 628 |
| StlportConstructCopySiblings.cpp | 162 -> 144 |
| Rva004EE6D0Insert.cpp | 241, unchanged |
| Rva004EE233AllocateCopy.cpp | 45, unchanged |
| StlVectorReserveProviderRepairs.cpp | 954, unchanged |
| AptTimeLine.cpp (now also holds `operator=` 0x0051F7AD) | 10,032, unchanged |

No row name changed, so no caller's resolution changed.

**Stopped before step 4, the retractions.** The cause is the prerequisite recorded in
`reverse/attempt_support/perturnstats-readmission-callers-20261104.md`, and it still holds:
- Every respelled caller must name `LivingWorldScoreKeeper::PerTurnStats`.
- `class_gate.py` refuses a private `class LivingWorldScoreKeeper`, so the caller must
  include the canonical LivingWorldScoreKeeper.h instead.
- StlVectorReserveProviderRepairs.cpp defines its own `_STL::vector`/`allocator`, which
  clashes with the header's `<vector>`.
- AptTimeLine.cpp's `Rva004EE501` sits on the 12-byte `_Vector_base<PrereqUnitRec>`; the
  header's sits on `_Vector_base<int>`.

Retracting 0x004EE1E2, 0x004EE20B and 0x004EE233 before the callers move would turn
0x004EE55E, 0x004EE6D0, 0x0051ED0A and 0x0051F7AD red.

Next: reconcile `vector<LivingWorldScoreKeeper::PerTurnStats>` in LivingWorldScoreKeeper.h:
- the nested PerTurnStats goes in the header;
- the `Rva004EE501` views fold onto `vector<PerTurnStats>` at +0x28, and its rows are renamed.

Then steps 4-7 land as one commit: the retractions, the three rows in
LivingWorldScoreKeeper.cpp under the PerTurnStats names (it already emits them
byte-exact), the caller respellings, and retracting the `??0PrereqUnitRec` pin at 0x004EE1A9.

Clearance: pending.
Census confirmation: not claimed.
