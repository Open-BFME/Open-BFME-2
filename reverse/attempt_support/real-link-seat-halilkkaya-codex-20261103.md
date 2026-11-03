# Real-link slice handoff: halilkkaya-codex, 2026-11-03

Initial base: `c1325ac0b6`. No push performed. Land in this order:

| Commit | Base | Resolved names in touched consumers |
| --- | --- | --- |
| 02ba74b593 | c1325ac0b6 | CDManager: 8 |
| 8e7d73b3a6 | 02ba74b593 | Dynamesh/shatter: 33 source/name references, 32 distinct names; 25 attributed only to this pair in the artifact |
| 81510a474f | 8e7d73b3a6 | Player: 2 |
| 007bf15b24 | 81510a474f | Apt Laser donor: 3 |
| 97f025c16c | 007bf15b24 | FieldParse tables: 3 |
| f637f07083 | 97f025c16c | Member-call ICF spelling: 1 |

These are local provider/reference repairs. The starting whole-image artifact
is successful workflow run `41678189681`, measurement `96cfeda7ba`: 678
unresolved names and two duplicates. No real-link, census, nightly, link_cycle
or smoke run was started. `exit_link --blockers` ingests errors.tsv; it does
not rerun the linker and was not used to generate an updated measurement.

All seven changed sources pass normal checks together: 42/42 function rows
and four data rows, including three newly recovered FieldParse tables.
Each implementation evidence file records the broader sibling byte checks,
true source-restored A/B tests and scoped DIR32. The combined scoped DIR32
checks 42 rows plus 18 witnesses, 78 symbols, with no new or whitelisted
conflict. check_csv passes 99,421 function rows, 9,350 symbol pins and 2,269
data rows. No pin, compiler flag, shared header, source path or hatch was added.

A combined true base/tip comparison restores all seven sources and the function
and data ledgers to c1325ac0b6, builds normally, compares 70 units, then restores
and normally builds the tip. This includes all 44 original artifact sources
and every previously checked sibling/provider unit:

- LINKS: 29 -> 33; no LINKS-to-blocked transition.
- Unresolved source/name references: 226 -> 176.
- Distinct unresolved names within this scope: 213 -> 170.
- New LINKS: CDManager, Player, dynamesh and shatter (54+112+113+133 authored
  bytes in the preview). This is not census credit.
- Apt stays U3 with its two old other blockers unchanged; Vslot AG stays U3.

`link_batch_audit --base c1325ac0b6 --tip f637f07083` exits 2, INCONCLUSIVE:
index `984a4cdc4d` (November 2 08:35) predates the base; seven changed source
objects lack current strict receipts, first Player.cpp. This does not establish
whole-consumer clearance. Carry these providers and affected consumers into
the next scheduled real-link/census. No repeated strict preparation or
whole-tree rebuild was attempted. Logs: `build/seat-link/final-ab/`,
`final-dir32.log`, `final-link-batch-audit.log`, and each repair subdirectory.

The initial full foreground incremental build succeeded. Every implementation
commit passed normal hooks without bypass. Six retained shadow findings in
Player.cpp are documented in its evidence; no identity debt was retired.

## Remaining prerequisites

- collect.cpp: trimming loses two native virtual leaves; its donor vtable
  context still emits them. Recover their identities before retiring it.
- twiddler.cpp: its donor owns external _ENUM_VALUE/vector helpers. The
  surface-owning native element contract disagrees with StringClass/int.
- Particle: the primary selector is rowed nonvirtual with an incompatible
  signature. Reconcile constructor/destructor/selector tables together.
- Apt: native fifteen-slot base hierarchy disagrees with DrawableModule/
  Snapshot views. Online screens need their full deleting/lifetime hierarchy.
- Icons: LINK-086 requires real ArmyHeroIcon owners, hidden-result signatures,
  full eight-slot tables and vtordisp reconciliation.
- ThingTemplate/ThingFactory were held through class:ThingTemplate and skipped.
- Deflect: the native 5B destructor tail jump becomes 11B with an ordinary
  derived vptr restore. Trial reverted; no novtable workaround retained.
- Vslot AG: bool/int return contract remains. RET4 at 47A69C is held by other
  seats. An early trial mistakenly continued after a claim refusal; the gate
  rejected the inlined callers and all helper/source/ledger changes were
  restored before the table-only commit. No held-helper change remains.
- STL element families, XferSave maps, GeneralAllocator and locale search-state
  contracts retain their existing obstacle-register prerequisites. No fresh
  missing body is claimed from a differently spelled existing owner alone.
- Clear, tree-key range and the two large thunk units already preview LINKS
  before this batch; their artifact discrepancies receive no repair credit.

The following table covers all 44 original sources. Artifact counts are from
that measurement. Current U/LINKS is the ordinary combined tip preview, which
can also have COMDAT/selection blockers. The accompanying TSV preserves every
original requested name, existing pin and representative ledger owners as
investigation hints; neither a pin nor a same-address owner proves identity.

| Source | Artifact names | Current U / LINKS |
| --- | ---: | --- |
| `Code/Libraries/Source/WWVegas/WW3D2/collect.cpp` | 41 | 41 |
| `Code/Libraries/Source/WWVegas/WW3D2/dynamesh.cpp` | 21 | LINKS |
| `Code/GameEngine/Source/Common/Rva001F4B01Ctor.cpp` | 12 | 12 |
| `Code/Libraries/Source/WWVegas/WW3D2/shattersystem.cpp` | 12 | LINKS |
| `Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp` | 11 | 9 |
| `Code/Libraries/Source/WWVegas/WWSaveLoad/twiddler.cpp` | 10 | 10 |
| `Code/GameEngine/Source/Common/Rva005F422CDtor.cpp` | 9 | 9 |
| `Code/GameEngine/Source/Common/System/CDManager.cpp` | 8 | LINKS |
| `Code/GameEngine/Source/Common/Thing/ThingFactory.cpp` | 7 | 16 |
| `Code/GameEngine/Source/Common/Rva005BA1FDCtor.cpp` | 7 | 7 |
| `Code/GameEngine/Source/Common/VslotSmallBodiesAG_Rva00131CF2.cpp` | 7 | 3 |
| `Code/GameEngine/Source/Common/BfmeConv1292DeferredWalkers.cpp` | 6 | 6 |
| `Code/Libraries/Source/Apt/AptValue/AptValueNameEntry.cpp` | 6 | 3 |
| `Code/GameEngine/Source/Common/RTS/PlayerCtorBFME2.cpp` | 4 | 4 |
| `Code/GameEngine/Source/Common/Rva006DE1A0Finish.cpp` | 3 | 3 |
| `Code/GameEngine/Source/Common/RvaPayloadValueReturnsUnresolved.cpp` | 3 | 3 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva000C225D.cpp` | 3 | 3 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva001EBEAB.cpp` | 3 | 3 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva002BC47D.cpp` | 3 | 3 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva005205DA.cpp` | 3 | 3 |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_LocaleTranslateToSystem.c` | 3 | 3 |
| `Code/GameEngine/Source/Common/BfmeConv881O1.cpp` | 2 | 2 |
| `Code/GameEngine/Source/Common/BfmeConv901.cpp` | 2 | 2 |
| `Code/GameEngine/Source/Common/PAVectorEraseRangeFamily003AF.cpp` | 2 | 2 |
| `Code/GameEngine/Source/Common/R5VectorDtorEHFramedPolymorphic.cpp` | 2 | 2 |
| `Code/GameEngine/Source/Common/R5VectorDtorEHFramedPolymorphic_Rva005de870.cpp` | 2 | 2 |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_rva005de9c4_ctor.cpp` | 2 | 2 |
| `Code/GameEngine/Source/Common/RTS/Player.cpp` | 2 | LINKS |
| `Code/GameEngine/Source/Common/RTS/ProductionPrerequisite.cpp` | 2 | 4 |
| `Code/GameEngine/Source/Common/Rva00066A9ABody.cpp` | 2 | 2 |
| `Code/GameEngine/Source/Common/Rva003C2F40TreeCtor.cpp` | 2 | 2 |
| `Code/GameEngine/Source/Common/System/SaveGame/AerialPathfinder.cpp` | 2 | 3 |
| `Code/GameEngine/Source/Common/WeaponStore.cpp` | 2 | 2 |
| `Code/Libraries/Source/WWVegas/WWLib/Rva0020EE29Clear.cpp` | 2 | LINKS |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva001DE3E3.cpp` | 2 | 2 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva001DF2D3.cpp` | 2 | 2 |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_rva00587375_overflow.cpp` | 2 | 2 |
| `Code/GameEngine/Source/Common/FamilyDeletingDtors_muse-cd13.cpp` | 1 | 1 |
| `Code/GameEngine/Source/Common/Rva006C3CC0Cluster.cpp` | 1 | 1 |
| `Code/GameEngine/Source/Common/Rva007B6880Thunks.cpp` | 1 | LINKS |
| `Code/GameEngine/Source/Common/RvaCountNoteRunFamily.cpp` | 1 | LINKS |
| `Code/GameEngine/Source/Common/System/CrateCreationEntryList.cpp` | 1 | 1 |
| `Code/Libraries/Source/WWVegas/WWLib/StlportTreeKeyRangeVector.cpp` | 1 | LINKS |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW6Rva0016DEC0.cpp` | 1 | 1 |

## Shader-manager data graph

No source or data-row edit is retained. Native roots at VA DB43A4 and DB43AC
have 2 and 10 pointers (8 and 40 bytes), including zero sentinels. The old
catalog extent of 196B is not a size proof. Ten nested lists occupy
DB4348..DB43A4 (92B):

| Root | Child list VA | Object VAs before null |
| --- | --- | --- |
| shader | 00DB439C | 00DB5A34 |
| filter | 00DB4348 | 00DB5BD4 |
| filter | 00DB4364 | 00DB5B54, 00DB5B5C |
| filter | 00DB4350 | 00DEC1F0 |
| filter | 00DB4394 | 00DB5A64 |
| filter | 00DB4370 | 00DEC140, 00DEC174 |
| filter | 00DB437C | 00DEC0E0 |
| filter | 00DB4358 | 00DEC1CC, 00DEC1DC |
| filter | 00DB4384 | 00DEC080 |
| filter | 00DB438C | 00DEC018 |

Five initialized object homes (DB5A34, DB5A64, DB5B54, DB5B5C, DB5BD4) lack
matched data owners. Seven DE-region objects are unsigned scalar stand-ins
in Rva007B6880Thunks; DEC1F0 has a 28B data row in Rva007AC9B0FilterInits.
Recover actual objects, sizes, vtables and initialization/lifetime before
supplying the roots. Zero Hour has different master-list composition; its
names do not establish the thirteen BFME2 object identities. Both existing
code rows remain exact (371B), and find_declared_unmatched is clean. The three
investigation claims were released without source edits.

## Claims for the lead

Held until landing: file claims for all seven changed Code sources, plus
RVA claims 0023C7F5, 00874540, 00874630 and 00874704. Release scope claims
after pushing and use claims.py release --landed for landed bodies. Blocked
or abandoned collect, twiddler, Deflect, Matrix3D and shader-root investigation
claims are released. The unrelated RET4 owner 0047A69C remains held by others.
