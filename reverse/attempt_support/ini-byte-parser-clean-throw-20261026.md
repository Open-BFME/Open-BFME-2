# INI byte parser: native integer exception

Base `091dbc15da`, 2026-10-26. Claimed scope: INI.cpp and
`INI::parseBitString8`, `0x0002F1DC..0x0002F21A`, 62 bytes.

The merged file still expressed the range error as an explicit
`_CxxThrowException` call with a zero-filled throw-info anchor. Retail first
parses an unsigned value through `parseBitString32`, tests bits 8..31, and
stores the low byte only on success. Its error arm reuses `[ebp-4]` for the
integer value 1 and throws through the native integer throw info at
RVA `0x008FE2C8`.

The body now uses the file's existing `throw ERROR_BUG` idiom, where
`ErrorCode` is `int` and `ERROR_BUG` is 1. The explicit runtime declaration,
manual call, `__assume(0)` and unused zero-filled anchor are removed. The
compiler emits the exception metadata. No flag, boundary, name, pin, alias,
shared header or ledger row changes. The stale 56-byte source comment is
corrected to the verified 62-byte extent.

Verification:

- The normal whole-file build passes all 53 rows / 3,945 bytes, including
  every byte of this 62-byte body, 54 strings plus one empty reference, one
  float and nine imports. Five EH labels are resolved after normal compiler
  renumbering; no pin or ledger-label edit is needed.
- The INI/Get comparison cohort retains 178 references: 149 owner, 19 alias,
  eight EH and two fold bindings, zero wrong bindings.
- All eight EH graphs in that cohort are EXACT; data checking finds no
  findings, and the frozen-file check passes.
- The owning scoped Microsoft-header scan retains the same 13 local
  occurrences and no failed classification. No MS-header debt retirement
  is claimed for removing the compiler-runtime declaration.
- Independent read-only review confirms the compiler and retail metadata
  describe `int` (`.H`), size four, simple-type flag one, with no copy or
  destructor entries. No source or register blocker was found.
- Ordinary preview against `763dc8759f` retains the same seven duplicate and
  five selected findings from the retired INI donors and old ownership map.
  It adds no unresolved reference; its result remains unclean and is not
  counted as a linking gain.

The data catalogue still lists the old `_parseBitString8ThrowInfoAnchor`
spelling at the native `__TI1H` address, alongside two other callers' anchor
spellings. This historical `names` entry is not an active emitted symbol or
a new ownership claim; it is left intact rather than hand-edited.

Logs: `build/codex-cleanup-20261025/iteration20-bit8-{build,identity,eh,data,frozen,ms,link}.log`.
Matching coverage is unchanged. The earlier publication's complete batch-link
verdict remains blocked on Eva.cpp's strict include inventory and the older
comparison index; this source cleanup does not clear those prerequisites.
