### LINK-679: `AIPathfind.cpp` insert_unique copy without the retail begin() layout

Status: Repair landed / awaiting census. Updated: 2026-11-15; inspected revision: `bb93a2a56e`.
Evidence / affected units: census 2026-11-15 08:36 (`331df3e3ff`) holds
`Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp` (6,253 authored bytes) out on one name,
`?insert_unique@?$_Rb_tree@IU?$pair@$$CBII@_STL@@U?$_Select1st@...@2@URva002F3759Compare@@...@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@...@_STL@@_N@2@ABU?$pair@$$CBII@2@@Z`
(no ledger row: the comparator is address-derived). Two objects emit it. `pathfinder.cpp`, first in
link order, is built with `/D_BFME_RETAIL_TREE_INSERT_LAYOUT` and emits the 134-byte body
(digest 4ce30247ddaf); `AIPathfind.cpp` was built without it and emitted the vendored 4.5.3
`_M_insert(__x, __y, __v)` begin() branch, 132 bytes (b70d5ea34e06), so its copy lost under the
`first` rule. Retail's `insert_unique(value)` of this tree is the rowed 134-byte body at
0x002F0E5E (`Rva002F1DDCTree::rva002F0E5E`, reached from the hinted insert at 0x002F1DDC): the
134-byte copy equals it outside its two relocation fields.
Completed: `/D_BFME_RETAIL_TREE_INSERT_LAYOUT` added to the unit's `// cl:` line (the opt-in the
vendored `_tree.c` already offers; same repair as `FontLibraryInit.cpp` under LINK-135).
`./build.sh` of the unit: 97/97 functions exact, data rows, string/float/import refs OK. Exactly
one COMDAT digest of the object changes (this name, now 4ce30247ddaf); no other copy, strong
definition or undefined reference changes. Preview against index `bb93a2a56e` (census
2026-11-15 08:36): `AIPathfind.cpp` LINKS 0 -> 6,253 bytes, `pathfinder.cpp` keeps 50,353.
Remaining / next check: none for this name. The family is still rowed under three address-derived
models (`Rva002F1DDCTree`, `map<int, Rva002F3093Record>`, `Rva002F0DD6Less`) beside the
`Rva002F3759Compare` instantiation; unifying them is naming work, not a link blocker.
Clearance: preview only, scope `AIPathfind.cpp` and `pathfinder.cpp`.
Census confirmation: awaiting.

**2026-11-15 same cause, `ThingTemplate.cpp` (base `2c5fc2bb9e`, seat halilkkaya-link):**
`Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp` (672 authored bytes) was out on
`insert_unique(value)` of `_Rb_tree<AsciiString, pair<const AsciiString, const FXList *>, ...>`,
pinned at 0x0033D28A: its copy (143 bytes, c90cdcd8dd6e) was the kept one and not retail's, the same
begin() branch. With `/D_BFME_RETAIL_TREE_INSERT_LAYOUT` on its `// cl:` line the copy is 151 bytes
(24d5cfc19cd2) and equals retail at 0x0033D28A outside its four relocation fields. 19/19 functions
exact. The unit's other `insert_unique` instantiation (the `SparseMatchFinder` armor map, no retail
address, this unit its only copy) changes with it; nothing else does. Preview against index
`bb93a2a56e`: LINKS 0 -> 672; no other census object touches a changed name. Census confirmation:
awaiting. Not this cause: `ConnectionManager.cpp`'s `map<unsigned short, AsciiString>` names. Its
pinned `_Construct` target 0x006204B0 is a two-dword pair copy with no AsciiString constructor
call, so the pin or the element type is wrong and the unit needs its tree identity read first.
