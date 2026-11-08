### LINK-631: 42 existing pins name a function whose own body is not the body at their address
Status: Open. Updated: 2026-11-07; inspected revision: c32d83389b (swarm Link lane).

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

Clearance: pending.
Census confirmation: not claimed.
