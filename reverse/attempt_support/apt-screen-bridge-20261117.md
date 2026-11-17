# Native Apt screen bridge prerequisites

The 2026-11-17 default picker claims primary table RVA 0x0086DB40 in
BfmeAptScreenInGameChatCtor.cpp. Commit a35f8a9775a shares the constructor
and destructor's accessed native class layout. Normal builds pass six rows,
two EH parents and ten unchanged COMDAT copies. The current bridge is not
retired by that preparation; its pass test requires a published real link.

Retail's fourteen primary targets, in slot order, are 0056DC2A, 0056DA49,
0056D9C1, 0056D983, 00444680, 000910FB, 00313913, 0056DC46, 0031393A,
0008FF78, 0050B5C6, 0050B5C6, 000B3FD0 and 000B3FD0 (all RVAs).
Slots 1/2/3 have existing rowed providers under separate placeholder classes.
Their future transfer must use the supported rename/naming route and preserve
their callback signatures, rather than adding aliases or copying the bodies.

A scratch-only factory adoption of Rva0056D915View.h fails C2259: the native
class still needs its slot-7 override of GameWindow::fetchCreateInstance.
The existing six-byte provider Rva0056DC46Get already returns the actual
createAptScreenInGameChat function address; its source is ConstIntGetters4.cpp.
The factory allocates 0x2A4, matching the shared view's explicit extent check.
No factory source change was applied.

Claims for 0x0056DC46 and the folded slot targets 0x000910FB/0x00444680 were
refused because another worker holds them. Those targets were left untouched.
Resume those repairs only after acquiring their claims. The placeholder
scalar-deleting-destructor emitter in OpaqueScalarDeletingDtorsB12.cpp is
another view to reconcile; do not remove its row or fake constructor without
proving the proper owner emits the existing deleting destructor.

The source commit landed on its first push attempt in 77.4 seconds. Its broad
link audit was INCONCLUSIVE against the older 3d7c5d8f25 index and missing
current receipts, not proof of link cleanliness. No image or smoke was run.
