# Two siblings-file base/derived lifetime contracts (root20, 2026-11-14)

Default next_work --claim served Rva00170C0Siblings.cpp and its two bridged
tables. Whole-file baseline passes 13/13; source and ledger remain unchanged.
Native bytes and current object/source fingerprints are in the adjacent JSON.
No queue retirement, current-image gain or new runtime result is claimed.

## Debug command family: 0x007BE7EC

Target facts: the table starts with 382F0,3B810,3B810; errors.txt begins after
those three words. Its current data row/ledger extent is only four bytes.
The unique base scalar destructor is 382F0 (31B), already emitted/rowed in
InlineDtorDeletingDtorsC03.cpp. Native 6C5930 is the 7B cleanup restoring this
base table. The served placeholder also owns scalar 118640 (30B), which calls
that cleanup. That scalar appears in two different native derived tables:
WW3D command 7CFBF0 and ProfileCmdInterface 8E7CB0. It is not the base scalar.

Thus a whole-family Rva006C5930Dtor -> DebugCmdInterface fold is unsound.
Current base views disagree at one/two/three slots; DebugCmdInterface is not
registered, while ProfileCmdInterface is registered at profile/internal_cmd.h.
Reconcile the base and both derived lifetimes, retain the distinct scalar
contracts, establish compiler-proven derived ICF sharing, then reconcile the
base extent through its owning data workflow. Declaration-only cleanup caused
past authoritative unresolved names; deleting the placeholder table binding
would merely hide debt.

Prior evidence is reverse/attempt_support/profile-command-table-008e7cb0.md:
constructor/initializer codegen and both fold refusals remain relevant. No new
class identity is inferred from the shared 7B body alone.

## Scene iterator family: 0x007D3338

Target facts: native base table has 140C00 then four purecalls; derived table
7D33BC is 141C10,140E70,140E80,140E90,141590. The 24B constructor141BF0 installs
7D33BC, list at+4 and current node at+8. Create_Iterator141CD0 allocates12B.
The 30B scalar141C10 calls7B cleanup141C30, which restores base7D3338.

Source/inference: a normal SimpleSceneIterator : SceneIterator, with inline
empty base teardown and declared noinline derived destructor, explains the
retained base restore and scalar CALL. The current creator incorrectly uses
novtable on SimpleSceneIterator, so its native derived table is bound under
the base SceneIterator name in data_ledger. Legacy scene.cpp/Is_Done views also
carry unobserved Scene/OnlyVis tail fields and another present-unmatched ctor;
copying those tails contradicts the proven12B allocation.

The owning prepared fold Rva00141C30Dtor -> SimpleSceneIterator needs three
concrete prerequisites: shared registered12B derived declaration; registered
base special-member owner for7D3338 (native constructor has no E8 base call);
and correct own-table compiler emission plus owning ledger regeneration for
7D33BC. Otherwise the existing 4B placeholder/12B target layout check and
inlined_base_restores proof correctly remain closed. Keep the true base-dtor
ICF row at141C30; it does not make SimpleSceneIterator own the base table.
The old scene-tu-approval-20261104-codexb4.md records the separate earlier
base-name admission issue. Do not hand-rename ledger bindings or add pins.

## Remaining whole-file context

The other deleting rows retain the prior LINK-109 class/callee prerequisites;
all13 current rows pass. Neither served table has a standalone safe spelling
fix. This session performed native byte/ownership and source/lifetime analysis,
no speculative source mutation or new compiler experiment. Read-only independent
reviews corroborated both contracts. Scratch baseline: build/root-siblings/.
