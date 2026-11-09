### LINK-109: placeholder deleting destructors still emit nonretail complete destructors

Status: Blocked on class and row identity reconciliation. Updated: 2026-10-27; inspected revision: 40d8eced18722ddcee26c59ddc4f3fb8d157d887.
Evidence / affected units: Code/Libraries/Source/WWVegas/WWLib/Rva00170C0Siblings.cpp retains L10/S10 in current-provider ordinary preview against index 5ce093a71a (2026-10-26 19:02, retail-truth-4). Each blocker is its empty Rva<target>Dtor complete-destructor definition. The native deleting rows call existing nonempty matched bodies under different names. This is related to the complete-destructor prerequisite in LINK-012, not evidence of ten missing native matches.
Completed: inspected every deleting row's native call and its current callee row. All 12 deleting rows remain exact; declaration, EH and shadow data checks pass. No destructor source trial or ledger change is retained. The existing names at the call targets are owner facts, not proof that the placeholder class has that identity.

| Native deleting row | Complete-destructor target | Existing row owner and home |
| --- | --- | --- |
| 0x00122110 | 0x00120FB0 | VectorClass<FontCharsBuffer*>::~VectorClass, WW3D2/render2dsentence.cpp; the earlier naming attempt separately records conflicting ResolutionDesc vtable neighbors. |
| 0x00156840 | 0x00155330 | DynamicVectorClass<Rva00155940Element*>::~DynamicVectorClass, WW3D2/FontCharsClassConstructorBFME.cpp (2026-11-09: hlod.cpp's VectorClass<ModelNodeClass> placement retracted; retail stores table 0x007D3B98 there and inlines ModelNodeClass's destructor). |
| 0x00157110 | 0x00156750 | VectorClass<MixFileFactoryClass::AddInfoStruct>::~VectorClass, WWLib/mixfile.cpp. |
| 0x00157E60 | 0x00157C20 | VectorClass<Render2DSentenceClass::PendingSurfaceStruct>::~VectorClass, WW3D2/render2dsentence.cpp. |
| 0x00188320 | 0x001880D0 | Rva001880D0StringCleanupForward::cleanup, WWLib/wwstring_free_string.cpp; the five-byte body jumps to StringClass::Free_String at 0x00610A40. |
| 0x00616490 | 0x006162B0 | GenericNode::~GenericNode, WW3D2/layer.cpp; its named deleting destructor is separately rowed at 0x006162E0, so the call target alone does not establish a rename. |
| 0x00626D90 | 0x00625800 | BfmeThingZU::bfmeUnhookZU, Common/BfmeOneHundredSixtyTwo.cpp. |
| 0x00663410 | 0x0066C730 | Rva00800290Buffer::reset, GameNetwork/Y2FeslBufferAndChain.cpp. |
| 0x0073AAC0 | 0x0073A900 | BfmeThingCDE::bfmeDtorCDE, Common/BfmeThingCDEDestructor.cpp. |
| 0x007581C0 | 0x0075A080 | Rva009A4620CollisionData::~Rva009A4620CollisionData, Common/System/Rva009A4620Destructor.cpp. |

Remaining / next check: reconcile each actual class, base/member lifetime and deleting-row identity with these existing owners through the naming lane, preserving the two distinct GenericNode deleting extents and the conflicting first vector evidence. Removing the empty definitions alone would also stop the compiler from emitting the rowed deleting destructors. Renaming or moving those rows, changing pins, or adding new bodies is outside this worker's scope. No admissible new fold pin or missing native match was established.
Current-input follow-up (2026-10-27, `0f2cabf5a8`): all 12 rows (360 bytes)
still pass the normal build; ordinary preview against `bf3dd31211` retains the
same ten COMDAT/selected conflicts. The supported identity retirement refuses
without changing the register: the current scan additionally finds the
0x00188320 deleting row's `??1Rva001880D0Dtor@@UAE@XZ` binding to native
0x001880D0, already owned by the string cleanup forwarder above. Resolve that
class/operation identity before attempting to retire the source's obsolete
keys; do not add the finding to the shrink-only register. No source trial,
new match or linking gain in this follow-up.
Clearance: none for this unit; current-provider preview still reports L10/S10.
Census confirmation: pending; no census gain claimed.

Follow-up (2026-11-09): the real link at `a7a3c4d962` (after the 0x00155330
retraction `36efc6df39`) still refused `??_7?$VectorClass@PAVRva00155940Element@@@@6B@`
(0x007D3B98) and `??_7?$VectorClass@VModelNodeClass@HLodClass@@@@6B@` (0x007D6720)
as ambiguous-table-name: no object binding remained, but the committed
`reverse/data_ledger.csv` row 0x007D3B98 still listed the ModelNodeClass table as an
alias. A local `tools/data_ledger.py --out` run drops that alias (refs 6 -> 5); only
that row was applied. Clearance: pending the next real link's vtable_bridge_queue.
