# AssistedTargetingUpdate constructor table review

**Result: 63/63 native slots exact.** No unresolved slots or wrong profile was
found in the current normal constructor object.

| Compiler table | Retail VA | Exact slots |
|---|---|---|
| AssistedTargetingUpdate / ObjectModule | 0x00C4AF64 | 13/13 |
| AssistedTargetingUpdate / BehaviorModuleInterface | 0x00BEFF90 | 47/47 |
| AssistedTargetingUpdate update interface | 0x00C4B1E0 | 3/3 |

Inspected normal object:
`build/match/^code_^game^engine_^source_^game^logic_^object_^update_^assisted^targeting^update^ctor.obj`

SHA256: `080d5653e7a935c027a5f4bbc4fd54ead4ee3d4880f655ebb34b7245de99b6d7`.
Ctor source SHA256:
`a4d9d7b51930d7d1e7c5d737648d18c2a172ec8c551e07a7341629f6c4cd023f`.
The normal cache receipt matches the current source and all six dependencies.

Method: read the current object once, inspect every COFF slot relocation, and
read retail through `eh_verify.Image` (RVA-indexed, base 0x400000). Require
complete 52/188/12-byte table extents and exactly one DIR32 relocation per
slot. Resolve seven external entries through narrowly selected current matched
ledger rows. Prove the other 56 entries through the object's own compiled
function bodies: full extent and all non-relocation bytes must match, and each
relocation must resolve to the exact native callee. The deleting destructor's
two relocations resolve to AssistedTargetingUpdate::~AssistedTargetingUpdate
at RVA 0x486E18 and operator delete at 0x2FD60. The transfer body's two resolve
to Xfer::Version1 at 0x53EE and UpdateModule::xfer at 0x44DF9F.

Canonical inherited empty/getter implementations therefore have body evidence,
not guessed address aliases. No pin fallback, prospective binding, injected
symbol map or private-probe substitution was needed. Exact per-slot details,
selected ledger rows and hashes are in
`table-slots.json`; the read-only inspection script
is `build/assisted-table-slot-review-20261106.py`.

Scope: this proves the three tables emitted by this object. Selection of other
copies in the final real image and ordinary byte/EH/link gates remain the
parent's publication checks. No compiler, claims, network, Code/ edits or
ledger edits were performed by this review.
