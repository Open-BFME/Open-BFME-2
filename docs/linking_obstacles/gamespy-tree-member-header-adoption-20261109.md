### GameSpy tree member header adoption

Status: consumer repaired; destructor provider blocked. Inspected2978028b46.

Rva00386374Dtor.cpp now includes the canonical12B Rva0038404A member header;
obsolete padding is removed while native member receivers+34/+40 and the next
map+4C remain. Normal25/25, one exact EH graph, frozen checks and LINKS386->386
pass; the owning acceptance tool retires its one queue row.

RvaTreeDtorFamily.cpp remains unchanged. A TU-local void*& cleanup guard with
the canonical pointer layout preserves218 code rows but changes one byte in
the unwind action at77FA57 (78/79 EH graphs exact). The banked partial is not
an adoption; its provider queue row remains. Recover the member lifetime while
preserving that unwind graph before retrying. The related provider patterns in
LINK-249 and LINK-614 remain prerequisites too. GameSpyStagingRoom's consumer
view is still queued; no shared header or image closure is claimed.

[Evidence and banked attempt](../../reverse/attempt_support/gamespy-tree-member-header-20261109.md).

Same-file follow-up after1e0712eda9: the remaining GameSpyStagingRoom consumer
view now uses its canonical1020-byte header. Four bytes of padding after its
member at5E4 preserve the next receiver1608. Normal25/25, one EXACT EH graph,
frozen checks and LINKS386->386 pass; owning acceptance retires its one queue
row, leaving this consumer file with no header-debt rows. The provider's
holder-lifetime repair remains open. Broad tree-package audit: INCONCLUSIVE
for unchanged AIRingHeroTactic.cpp's missing current receipt; actual next
census/image confirmation remains pending.

Provider follow-up: a shared4B RvaTreeFamilyHolder is now the actual first
member of canonical Rva0038404A, with its original inline destructor defined
in the provider. This preserves sizeof12 and offsets0/4/8; six clear-provider
expressions now read its pointer explicitly. The second holder declaration
in StlportPod248ElementDtor.cpp is reconciled too. The full18-source header
closure passes855 bodies,32 data rows and140 exact EH graphs; all18 sources
preview LINKS34306->34306. The previous action77FA57 is exact. Owning
acceptance retires the final Rva0038404A header row. Its local header/lifetime
obstacle is cleared within this scope; normal census/image confirmation and
the distinct LINK-249/LINK-614 provider classes remain open.
