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
