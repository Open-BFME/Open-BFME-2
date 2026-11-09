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
