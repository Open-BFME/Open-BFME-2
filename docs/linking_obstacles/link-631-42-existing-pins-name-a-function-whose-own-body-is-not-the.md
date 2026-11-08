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
match. The worst:

| pin | pinned name | address carries | differs in | matched callers |
|---|---|---|---|---|
| 0x002CF99D | `??$_Construct@UPrereqUnitRec@ProductionPrerequisite@@U12@@_…` | `??$_Construct@UBfmeStringRecord002CF5B1@@U1…` | size | 4 (??$__uninitialized_copy@PAUPrereqUnitRe…) |
| 0x0014F3C4 | `?setup@FreelistProxyHead@@QAEXPBXPAX@Z` | `??0?$_STLP_alloc_proxy@IUBfmeScriptSlotAddr…` | size | 3 (??0?$_List_base@PAVObject@@V?$Rva001EB9…) |
| 0x004EE1A9 | `??0PrereqUnitRec@ProductionPrerequisite@@QAE@ABU01@@Z` | `??0PerTurnStats@LivingWorldScoreKeeper@@QAE…` | size | 3 (??$__uninitialized_copy@PAUPrereqUnitRe…) |
| 0x003025A5 | `??0?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UCoor…` | `??0?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAs…` | bytes | 2 (??0?$map@VAsciiString@@UCoord3D@@U?$les…) |
| 0x00395928 | `?allocate@?$allocator@UPrereqUnitRec@ProductionPrerequisite…` | `?allocate@?$allocator@UBfmeE12@@@_STL@@QBEP…` | size | 2 (??$_M_allocate_and_copy@PAUPrereqUnitRe…) |
| 0x0002C552 | `?_M_create_node@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VA…` | `?_M_create_node@?$_Rb_tree@VAsciiString@@V1…` | size | 1 (?_M_insert@?$_Rb_tree@VAsciiString@@V1@…) |
| 0x000365F0 | `??0?$list@PAVFXNugget@@V?$allocator@PAVFXNugget@@@_STL@@@_S…` | `??0?$StringBase@D@@AAE@ABV0@@Z` | size | 1 (??0FXList@@QAE@ABV0@@Z) |
| 0x0006F7BD | `??1Rva006F7BD@@UAE@XZ` | `??1RTS3DScene@@UAE@XZ` | relocations | 1 (??_GRva006F7BD@@UAEPAXI@Z) |
| 0x000F0BF1 | `?Resize@?$VectorClass@VTCBClass@TCBSpline3DClass@@@@UAE_NHP…` | `?Resize@?$VectorClass@VVector3@@@@UAE_NHPBV…` | relocations | 1 (?Resize@?$DynamicVectorClass@VTCBClass@…) |
| 0x00101ECF | `??$__uninitialized_copy@PBUEvaMessageInfo@@PAU1@@_STL@@YAPA…` | `??$__uninitialized_copy@PBUBfmeStringRecord…` | bytes | 1 (??4?$vector@UEvaMessageInfo@@V?$allocat…) |
| 0x00101F5C | `??$_M_allocate_and_copy@PBUEvaMessageInfo@@@?$vector@UEvaMe…` | `??$_M_allocate_and_copy@PBUBfmeStringRecord…` | size | 1 (??4?$vector@UEvaMessageInfo@@V?$allocat…) |
| 0x00155490 | `?Resize@?$VectorClassWide@UTextureStatisticsStructWide@@@@U…` | `?Resize@VectorClassBfmeThingFT@@UAE_NHPBVBf…` | relocations | 1 (?Resize@?$DynamicVectorClassWide@UTextu…) |
| 0x0016CC80 | `??$_Construct@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@U1…` | `??$_Construct@USegInfo@W3DRopeDraw@@U12@@_S…` | size | 1 (?_M_create_node@?$_Rb_tree@VAsciiString…) |
| 0x001EBA87 | `??$_M_allocate_and_copy@PAUBfmeAssignRecord172@@@?$vector@U…` | `??$_M_allocate_and_copy@PBUBfmePod172@@@?$v…` | size | 1 (?reserve@?$vector@UBfmeAssignRecord172@…) |
| 0x001FE06A | `??1PlayerTemplate@@UAE@XZ` | `??1BfmeObject476@@UAE@XZ` | relocations | 1 (??_GPlayerTemplate@@UAEPAXI@Z) |
| 0x00288978 | `??0?$_List_base@UcrateCreationEntry@@V?$allocator@UcrateCre…` | `??0?$_List_base@UBfmePod264@@V?$allocator@U…` | size | 1 (??$_S_sort@UcrateCreationEntry@@V?$allo…) |

Both LINK-629 pins are in the list (0x000365F0 and 0x00036E70). The suspect family LINK-629 named,
`push_back` 0x0005548F, `insert` 0x005925E2 and `_M_create_node` 0x000B6447 for `FXNugget*`, is proven:
real folds. `insert` and `_M_create_node` already carry `fold-proof=`; only `push_back<FXNugget*>` lacks it.
Five pins with a recorded `fold-proof=` now fail on a callee (0x004DFCB0 vector<SpecialPowerTemplate
const*>::push_back, 0x002888D4, 0x0041F4E5 twice, 0x00388F63): their proofs' premises moved after
admission. 855 pins without `fold-proof=` are proven folds and only lack the note.

Completed: the sweep, and `pin_consistency.py --audit` (shadow, 69accdc3bc + review fixes 18b8469364,
awaiting review) which replays it on demand. No pin was edited.

Remaining / next check: for each own-body case, confirm against the matched callers before retracting:
a byte-verified caller outranks the pin (pin_consistency --clear-cut's warning), and a different body
can also be our defining unit compiling the name unlike retail. The ProductionPrerequisite record
family (0x002CF99D, 0x004EE1A9, 0x00395928) looks like one misidentified record type. Retract or
respell through pin_admission / rename.py, rebuild each caller, and expect some callers to go red: those
were false matches. Re-run `pin_consistency.py --audit` after each batch.

Clearance: pending.
Census confirmation: not claimed.
