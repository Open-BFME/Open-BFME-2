# ObjectCreationList native handle-vector correction

Inspected BFME 2 base: `7497c3becc`. BFME 1 reference: verified
`1d5131d3f193cdf01a99da66ccd6828639585650`; model GPT-6.

## Target facts

The native vector clear at `005F8653` (30 bytes) calls the stride-eight
range destructor `005F85C8`, whose complete element destructor is the
existing `Rva005F8447` owner (61 bytes). Its two counted handles release
through the established native lifetime operation. The growth operation
`005F8752` (178 bytes) calls allocator `00523D6C`, copy `004F6A88`, construct
`004F6A52`, fill `004F6AAE`, then clear `005F8653`. Append `005F8855`
(55 bytes) calls the same construct and growth operations.

`004F6A52` invokes the existing two-handle copy constructor at `0044BD00`.
The actual native copy/fill helpers retain their fourth, unused tag argument
in callers; replacing those calls with three-argument inline adapters changes
the parent's instruction stream and is rejected by the private trial.

These operations contradict the former Zero Hour
`DeliverPayloadNugget::Payload` view: one AsciiString and one integer. Its
destructor pin even named `00495C43`, the independently owned pooled-index
record destructor, rather than the native two-handle lifetime. No original
element or enclosing application name is recovered by this correction.

## Source and ledger correction

Remove the Zero Hour-only DeliverPayloadNugget implementation and obsolete
donor callback table. Retail's separate, existing five-callback table contains
no DeliverPayload entry and remains in place. Retain all other matched bodies.
Explicit ordinary vector instantiations use the existing `Rva005F8447` view;
construction calls the existing `Rva004F6A52Assign`, and destruction calls the
existing `Rva005F85C8Destroy`. The native copy/fill operations use the stock
STLport template bodies, preserving their actual call contracts.

The three disproven real-name rows are withdrawn with tombstones in a separate
reviewable commit, as `add_match.py` requires for non-scaffolds. Readmit their
three native replacements through ordinary `add_match.py` before publication.
Do not publish the temporary 263-byte withdrawal alone. There is no source-path
move, approved-TU claim, duplicate range or invented canonical naming basis.

Remove six old Payload pins. The three newly emitted helper names are admitted
only through `pin_admission.py --add`, with whole-body fold proofs in this
source: allocator 28 bytes, copy 38 bytes, fill 37 bytes. Complete bytes and
resolved relocations reproduce their existing retail owners; no masked or
unresolved call is used as proof. Pin consistency passes. Net pins decrease
by three. The pre-existing native-holder append pin remains unchanged.

## Verification boundary

The private reconstruction reproduces all three replacement bodies exactly,
including every resolved call, and all 23 retained rows. Its in-memory preview
against index `12b9e7a7c0` clears the original eight blockers. This preliminary
preview is not a normal current-object receipt or a census result.

Normal strict preparation of the applied withdrawal passes all 23 retained rows,
two string literals, two compiler float literals and the named import. Parent EH
graphs independently recover renumbered compiler labels; no label alias is added.
The final readmission, provider cohort and outgoing audit are recorded below
after their ordinary checks complete. Debt is retired only through its owning
register tool. Full consumer selection, census and runtime results remain
unproven until separately measured; no nightly, link cycle or smoke is started.

The normal withdrawal preview has no remaining blocker and retains 1,164
authored bytes. All four retained EH graphs are EXACT and frozen-definition
preflight passes. The removed-provider audit compares the 117 removed external
code definitions with every indexed definer and consumer: none loses its sole
provider while retaining an external indexed consumer. This is an index-bounded
negative check, not proof that all current image consumers have receipts.
