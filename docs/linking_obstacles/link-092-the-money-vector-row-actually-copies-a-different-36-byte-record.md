### LINK-092: the Money vector row actually copies a different 36-byte record
Status: Open. Updated: 2026-10-26; inspected revision: 2a45addda1806342ac5c52757f63be902dcd428e.
Evidence / affected units: `MoneyVectorPushBack.cpp` reaches 0x00063BE4 and 0x006BF5E0. Their current owners are BfmeStringRecord00063BE4's copy constructor in `StringRecordCopyBFME2.cpp` and BfmeVecBE's overflow in `Rva006BF5E0Overflow.cpp`. The native call offsets, complete owner extents and current names are in `build/link-worker-w6/row-reference-witnesses.log`; `paired-before.log` and `paired-after.log` include both current providers.
Completed: diagnosis only; no source edit. The record copy is seven dwords, an AsciiString and two bytes, as its retail-proven owner records. It is not the engine's small Money value. Including the canonical Money header would therefore replace this false view with a different native type and break the row.
Remaining / next check: reconcile the vector row and its consumers onto the existing 36-byte record family through the naming lane, preserving the real Money users separately. The three unresolved Money virtuals come only from the wrong whole-vector instantiation; they do not establish missing native Money methods. No new match or independently proven fold pin was established.

2026-11-01 correction (Cortys): the false Money row was retracted in its own
normal commit, then the native 59-byte method was readmitted under the existing
neutral BfmeVecBE/36-byte record views, at the same source path. Its raw body is
identical and its two relocations now name the actual copy and overflow owners.
The compiler chooses storage for a default-initialized empty trait; no storage
reuse hack or alias is added. A complete owned call-chain review supports the
copy's no-C++-throw contract. The retraction checks passed 4,633 rows across
182 potentially affected units and 633 EXACT EH graphs. Current scoped preview
predicts LINKS 0 -> 59, with both providers retained. The per-source identity
retirement verdict passed, but publication's outgoing-range guard refuses the
removal because the old symbol name disappeared. The register key is retained
and the false-reject evidence is banked; no identity-debt retirement is claimed.
Census confirmation remains pending.

The Snapshot queue row remains: its acceptance command requires the header,
which the corrected record-only source does not use. FXParticleSystem.cpp is unchanged
and retains its existing base-view prerequisite and 5,650-byte prediction.
Evidence: `reverse/attempt_support/record-vector-identity-20261101/`.

Separate pin follow-up: the old Money-copy and vector-overflow address bindings
are removed after an 18,650-object audit found no observed undefined consumer.
The sole constructor-name hit is a current, unrelated 27-byte Money COMDAT;
its real definition is preserved. The owning counter update retires two pin
hatches. Conservative dependency checks cover 29 units. The repaired cohort's
3,456-byte prediction is retained; the menu unit stays nonlinking with its
existing prerequisites. The refused identity-key retirement and Snapshot queue
entry remain open. Full receipt currency is not claimed for every unhit object.

Post-publication follow-up: once 0a5c6b4a4d is upstream, the ordinary owning
identity retirement command can remove the retained Money-copy key against
the already-published new symbol. No function row or source changes in this
follow-up. The range guard's earlier refusal is a publication-order prerequisite;
the earlier false-reject label is voided, and no checker change is needed.
The Snapshot header queue row remains pending its supported retirement path.
