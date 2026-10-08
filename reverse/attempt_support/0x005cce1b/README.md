# Checklist update dependency repair

The served synthetic unwind parent in `Code/gen_small/uw_gen_008.cpp` was
false at 0x005CCEB6: retail's full eight bytes forward `this+4` to 0x005CCE1B.
The entire generated 359-line unit was read and preserved. The correct native
home, StrategicInGameUIChecklist.cpp, was inspected in full (118 lines).

Native `0x005CCE1B..0x005CCEB6`, 155 bytes, and independent named WB
`0x015B4B80` prove StrategicInGameUI::Checklist::Impl::Update. It obtains UI
through the factory's slot1 when unbound, binds every stored item's UI counted
reference, selects an item when the UI query is zero, then updates every item
through slot7. The paired sentinel nodes hold reference/implementation at
0x08/0x0C. Existing AddItem pins supply CreateNewItem and binding operations;
RefCountClass::Release_Ref and the selection helper already have matched rows.

The prior attempt was blocked by an existing shared provider's return ABI.
Native call at 0x005CCE7D reaches the five-byte folded slot4 vcall thunk
0x005CB26A and tests EAX. Its C++ view previously returned void. Correcting
that view and slot to return int leaves the full provider bytes exact and
allows the 155-byte clean update to match every instruction except its
temporarily unresolved corrected helper name in the isolated pre-repair trial.
The owner is renamed rather than adding another pin or duplicate method.
Existing void callback bindings discard the returned register and retain the
same byte ABI; their existing link targets are updated to the corrected owner.

The provider's whole 27-line unit and the binding consumer's whole 863-line
unit were read. Normal provider/consumer gates and name-dependent checks are
required before committing. No new escape hatch is needed.

Local evidence: build/checklist-update-wb.txt, build/checklist-update-diff.txt,
build/checklist-slot4-diff.txt. The latter verifies all five provider bytes.
