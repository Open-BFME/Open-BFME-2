# Particle terrain-info table provider

Status: source provider repaired; complete class/interface and real-image confirmation pending.

Rva005646BC.cpp's subobject constructor formerly stored the address of a
one-byte char placeholder, g_00C1D3B0, for native four-slot table 0x0081D3B0.
It now references the existing compiler table of Rva003AE315, installed by
the matched copy constructor in V3PolyDeferredCopyCtors.cpp. The old name has
no outside index referrer and no matched or converged data owner. No ledger
alias, pin or queue is changed.

All three code rows, both other data rows and the parent EH graph pass;
private LinkGuard is clean, ordinary preview conserves 169 authored bytes,
and strict source preparation passes. A bounded cached-object bridge replay
removes the strong-definition refusal (1->0) while retaining the same one
four-slot bridge. Full-image/current-provider selection is not established.

Next: the class provider still has one of four native slots. Reconcile its
Snapshot lifetime, native getter 0x003AE336 (literal
"ParticleTerrainCollisionModuleInfo") and xfer 0x00564522 without inventing
a namespace from the literal. The containing object's two one-byte table
owners at 0x0081D390/0x0081D3A0 remain separate registered-row work. Await a
new real-link queue for the removed char-provider refusal and an actual
image before runtime conclusions.

[Target facts, consumer scope and bounded replay](../../reverse/attempt_support/terrain-particle-info-table-provider-20261108/README.md).
