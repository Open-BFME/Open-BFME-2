### LINK-138: nested vector ctor 0x002BC339 uses a placeholder element (2026-10-29, seat yasinschroeder-claudeb2)

Status: open; no source change retained. `Rva0019D850NestedVectorRelease_Rva002bc339.cpp`
(C=2, S=2) spells the element as the POD `Rva002BC339Value {int[3]}`, but
retail's unwind (0x2BBB57) destroys the 20-byte non-trivial
`Rva002BB6BE20Rec`. In scratch, the Rec element under `/O1 /EHs
/D_STLP_NO_EXCEPTIONS` (4.5.3 + bfmealloc or 4.6) with a noinline
`uninitialized_fill_n` specialization reproduces 0x2BC339 exactly up to
relocations. The TU's own count `_Vector_base<vector<Rec>>` copy is 61 B
against retail's 60 B ICF fold 0x5C8C37, which has a non-/O1 shape. A
decl-only base-ctor specialization changes the caller's frame, so that path
fails too. Prerequisites: a provider or fold binding for 0x5C8C37 under the
Rec spelling, owners for the extra Rec COMDATs, and a row rename off the Value
spelling. Doing these inside the LivingWorldLogic.cpp merge (approved TU) is
preferred. Handoff: `reverse/attempt_support/002bc339-nested-vector-link-20261029.md`.
