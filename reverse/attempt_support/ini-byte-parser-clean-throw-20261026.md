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

## Duplicate-declaration follow-up

After banking the integer-throw repair as `92fbda1679`, a separate homogeneous
cleanup removes three repeated `#define NULL 0` definitions and the second
`strlen`/`_mbscpy` prototypes left by composition. One NULL definition and the
original explicit `extern "C" ... __cdecl` declarations remain in scope.
No include, macro value, function body, name, layout or compiler flag changes.

The normal whole-file build again passes 53/53 rows, all literal/import checks,
seven EXACT TU EH graphs and the frozen-file check. The owning scoped
`ms_header_audit.refresh_queue` refresh changes only INI.cpp's row: 13 local
occurrences become eight (five function declarations and three macros), with
six `same` and two `abi` findings, zero failed classifications. Its conflicting
CRT classification remains; this retires five redundant occurrences, not the
entire header-queue item. Unrelated queue entries remain byte-for-byte intact.

Logs: `build/codex-cleanup-20261025/iteration20-dedup-{build,eh,frozen,ms}.log`.

## Publication and upstream reconciliation

Published as `5994f7c59a` at 2026-10-26 04:46 UTC. The normal push hook checks
33 upstream data-debt retirements, then passes 85 functions and 12 EXACT EH
graphs across INI.cpp, the updated upstream SpecialPower destructor and the
additional Eva.cpp dependency. The two explicitly changed units separately
pass 58/58 rows with strict reusable receipts. The shadow batch-link audit
again stops on Eva's known include-inventory prerequisite; no repeated
preparation is attempted without new evidence. Its saved index `763dc8759f`
also predates outgoing base `7d17532afb`.

The required post-push rebase onto `c330885439` preserves the upstream
VectorClass repair and the audio repair notes in two documentation conflicts.
Upstream now owns LINK-015; the local EH-label obstacle becomes LINK-016 and
the AIUpdate placement obstacle LINK-017, with their references reconciled.
No game source conflict was resolved. Upstream's reference pointer advances
to `ff391a5e90`, a descendant of the previously verified `f633d0e97a`; the
clean reference checkout is synchronized to that pinned revision.

The new normal full build at `69286bb3a5` passes all 98,252 function rows,
2,216 data rows, 214 STLport constructor folds, reference checks and the no-op
image, after compiling 53 changed units. This verifies the maintainer's pinned
`ff391a5e90` inputs. Official upstream was independently observed at the newer
`87ca288bdd`; no claim is made to have advanced or verified that revision.
The existing freshness stamp remains the historical successful `f633d0e97a`
check, rather than recording an unverified latest-upstream success.
Log: `build/codex-cleanup-20261025/iteration21-reference-full-build.log`.

Independent read-only rebase review confirms all 17 obstacle IDs and their
references are consistent, the upstream and local repair paragraphs survive,
INI.cpp equals published `5994f7c59a`, and all 53 other changed Code files are
upstream changes. No accidental source change was introduced by resolution.

## Standard boolean and null follow-up

Base `69286bb3a5`. A separate cleanup removes the remaining local NULL, FALSE
and TRUE macros. The existing `<cstddef>` supplies NULL; the two boolean
assignments in `INI::getNextQuotedAsciiString`, `0x0002E93F..0x0002EA4F`,
272 bytes, use C++ `false` and `true`. No include or compiler flag changes.

The normal whole-file build retains all 53 rows / 3,945 bytes, 54 strings plus
one empty reference, one float and nine imports. All seven TU EH graphs are
EXACT, including the normally renumbered labels, and the frozen-file check
passes. The owning scoped Microsoft-header refresh changes only INI.cpp's
queue row from eight local occurrences to five: five function declarations,
zero macros, three `same`, two `abi`, zero failed classifications. The CRT
conflict classification remains; this is a three-occurrence reduction, not
closure of the header-queue item or a linking gain. Independent read-only
review found no blocker in the source or scoped register update.

Logs: `build/codex-cleanup-20261025/iteration21-macros-{build,eh,frozen,ms}.log`.
