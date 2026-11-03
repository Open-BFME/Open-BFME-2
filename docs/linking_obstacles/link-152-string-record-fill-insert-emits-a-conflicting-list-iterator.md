### LINK-152: string-record fill-insert emits a conflicting list iterator comparison (2026-10-30)

`stlport_vector_stringrecord_5de651_fill_insert.cpp` byte-matches its three
rows but emits a non-retail `??9_List_iterator_base@_STL@@QBE_NABU01@@Z`
COMDAT, which blocks its ordinary link preview. Apply the TU-local node
comparison already used by its separate `StlSweepW5Rva005DE4BA.cpp` overflow
provider. The repaired object loses only that external definition; all 67
retained external COMDAT fingerprints and the undefined external set stay
identical. The replacement comparison is a 12-byte TU-local function.

Scoped repair verified: normal build passes 3/3 rows; paired strict preparation
passes 4/4. Against index `6fe1089c24` (2026-10-30 04:25), paired preview
predicts LINKS, 0 -> 270 authored bytes for the edited source and 178 -> 178
for its unchanged overflow provider. The source-only consumer audit is
INCONCLUSIVE: the index predates the source base and an affected consumer,
`Common/0CreateAHeroManager21FE49.cpp`, lacks a current strict receipt.
Full consumer selection and census confirmation remain open. The index lists
a retail comparison provider in `stlport_list_int.cpp` and three other wrong
copies; those copies remain separate work. No census gain is claimed.
The outgoing staged-tree batch audit also remains INCONCLUSIVE: the index
predates merge base `198e16293c`, and three earlier source objects lack current
strict receipts, first `GameClient/GUI/GUICallbacks/Apt/AptPlayerStatusDtor.cpp`.
Carry those providers and affected consumers into the next scheduled census.
[Target facts, rejected trial and verification scope](../../reverse/attempt_support/fill-insert-list-compare-20261030-codexb4.md).

Follow-up (2026-10-30): the three other wrong copies are repaired with the
same TU-local `_STL::operator!=` for `_List_iterator`:
`GameClient/MessageStream/SelectionXlatTranslateGameMessage.cpp`,
`GameLogic/Object/Contain/HordeContainRva00475F61.cpp` and
`GameLogic/AI/AIPlayerQueueSupplyTruck.cpp`. Retail inlines the node compare
(`areAllSelected` at `0042FA0D`: `cmp esi,[ebx]`). In the old objects, only
`.debug$F` referenced the out-of-line copy. Normal builds pass 6/6 and 13/13
rows, and the funclet pins verify past renumbering. Each object loses only the
`??9` definition (COMDATs 652 -> 651, 724 -> 723, 66 -> 65). No other COMDAT
is added or changed, and the undefined externals are identical. Preview
against index `6fe1089c24`: 3 of 3 link cleanly, LINKED 0 -> 7,362 bytes
(Selection alone 0 -> 4,150). The retail provider `stlport_list_int.cpp` still
does not link itself (0 of 1; codegen-like `distance`/`size`/`resize` copies).
Recheck (2026-10-30, halilkkaya-lk8, index 12b9e7a7c0 with current objects):
`stlport_list_int.cpp` now previews LINKS (67 B) too; with the four wrong
`??9` copies gone, its census blocker was only the wrong selection. All four
repaired units and the provider still need census confirmation.
Census confirmation remains open, and no census gain is claimed.
