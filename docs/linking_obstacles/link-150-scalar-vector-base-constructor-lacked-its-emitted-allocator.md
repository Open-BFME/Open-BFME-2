### LINK-150: scalar-vector base constructor lacked its emitted allocator identity (2026-10-29)

Status: Repair landed / awaiting verification; inspected base `95bb9e1d6b`.
`StringScalarVectorCopyBFME2.cpp` already previews LINKS before this repair,
but its rowed copy constructor has one registered wrong/unknown binding to
the emitted vector-base constructor. The complete 28-byte allocator and
58-byte base constructor now have byte-and-callee-verified ICF rows against
their existing owners, with no source or pin change and no unique coverage
increase. All 7/7 scoped rows pass; the identity scan has zero wrong bindings.
After normal byte preparation of 198 missing provider objects (1,759 function
rows and 37 data rows), the owning tool retires the one identity key.
Ordinary preview retains LINKS against index `85f6b7f40c` (2026-10-29 15:08).
Full consumer and census confirmation remain pending; no census gain is
claimed. The eight outgoing providers have current strict receipts (42/42
function rows, four data rows), but the batch audit remains INCONCLUSIVE on
the older index and missing current CreateAHeroManager consumer receipt.
Carry this provider and its consumers into the next scheduled census.
The successful commit hook also exposes a separate shadow divergent
`_Vector_base<BfmeAsciiScalarValue8>` destructor: two 24-byte COMDAT variants
in this source and `StringContainerRecordCopyBFME2.cpp`, with no certified
retail owner. These unchanged providers need a separate reconciliation;
zero wrong call bindings does not clear this definition finding.
[Evidence and initial refused admission](../../reverse/attempt_support/scalar-vector-base-identity-20261029-codex4.md).
