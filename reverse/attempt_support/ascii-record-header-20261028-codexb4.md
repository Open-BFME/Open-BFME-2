# AsciiString record header prerequisite

Inspected base: `fa53c16f5f`; BFME 1 freshness receipt is dated 2026-10-26.
The default picker claimed `class:AsciiString` and selected
`Code/Libraries/Source/WWVegas/WWLib/stlport_vector_stringrecord_allocate_copy.cpp`.
Prior attempts and current ledger ownership were checked before the trial.

## Target facts and trial

The original source passes the frozen-file check. Replacing its private
AsciiString declaration with the canonical BFME 2 header, with that header's
include directory first, passes three of five rows. Two fail:

- `fill<BfmeStringRecord00063BE4*>`, RVA 0x000AD806, 35 bytes: retail copies
  nine dwords with `rep movsd`; the trial calls record assignment instead.
- `__copy_backward<BfmeStringRecord00063BE4*>`, RVA 0x000AD897, 50 bytes:
  retail likewise copies nine dwords; the trial calls record assignment.

The private AsciiString has implicit trivial assignment. The canonical header
gives it real string assignment, making the containing record assignment
nontrivial. Separately, the established copy constructor at 0x00063BE4 in
StringRecordCopyBFME2.cpp copies seven words, calls the string-copy worker for
the field at +0x1C, then copies two tail bytes. This is evidence for an owning
string in that constructor, not evidence that the raw-copy helpers belong to
the same application type. Their ledger placement notes cite masked whole-body
search, not original type evidence.

The trial was fully reverted. A normal build then verifies the original unit
and the separately inspected AI attack-path unit together: 6/6 function rows,
one string reference and five float references pass. No header, source, pin,
ledger owner, queue entry or debt baseline changed. The attempt log's first
record uses 36 as the fill extent; the actual ledger extent is 35 bytes.

Next: recover the assignment helpers' actual element identity from their
native callers before retrying header adoption. Do not add a raw-memory
assignment to an owning string record merely to preserve these two rows.
No header debt or linking gain is claimed.

## Separate Microsoft-header queue lead

The Microsoft-header picker subsequently claimed
AIUpdateInterface_computeAttackPath_ComputeAttackPath.cpp for a local
`fprintf(void *, const char *, ...)` declaration. Its callee is already rowed
as `_fprintf`, RVA 0x002CEC42, in FprintfAppendLine.cpp. The ledger identifies
an application format-and-append helper whose object has a vector at +4,
not CRT FILE I/O. No stdio conversion was attempted: its true application
identity must be recovered before substituting a standard-library declaration.
The source remains unchanged and its normal byte build passes.
