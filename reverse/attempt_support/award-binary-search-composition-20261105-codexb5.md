# Award binary-search composition prerequisite

2026-11-05, codexb5; inspected revision `2fab882c26` (upstream base
`ee03ec37a6`). Scope: `Common/AwardSystemManager.cpp` and
`WWVegas/WWLib/stlport_binary_search_int.cpp` under their existing Code paths.
The current in-memory TU map approves the helper for AwardSystemManager;
this is not new evidence for an original retail source path.

The supported merge's initial dry run rejected the integer binary-search
donor with duplicate `_STL::less` and `binary_search` templates. The donor
now includes STLport's algorithm header, declares the existing lower-bound
specialization, and defines the binary-search specialization using the shared
`less<int>` type. It explicitly zeroes the one-byte comparator. `/Oi` retains
retail's `xor eax,eax; lea edi,[ebp-4]; stosb` initialization instead of an
out-of-line memset call. AwardSystemManager now carries `/Oi` too.

Both prerequisites were committed and handed to `/opt/runner/publish`
separately, before attempting a source move (commit subjects: "Use shared STL
comparator in award binary search" and "Align award TU intrinsic code
generation for composition"). No pin, alias, class layout, shared header,
ledger identity or protected-register entry changed.

## Verification

- Normal donor build: 1/1 exact, 56 bytes at RVA `0x0040AD75`.
- Normal destination build: 69/69 exact, 12 data rows, five emitted STLport
  constructor folds, 13 literals and two empty-string references verify.
- Both declared-unmatched checks pass. Destination EH: ten graphs EXACT.
- Final serial `link_check.py --prepare-current` for both units: 70/70 rows
  pass, with strict reusable provider receipts; census/index/status unchanged.
- Final converged data check: two sources, eleven converged addresses, zero
  second names and zero unjudged rows.
- Final ordinary link preview: both LINKS, destination 3,143 -> 3,143 bytes,
  donor 56 -> 56 bytes. Index/census: `c95fcfcfcd`, 2026-11-05 05:17.
  These are bounded predictions, not new census or real-link results.

The merger's isolated `compose`/`Verifier.matched` path was used to diagnose
the remaining byte rejection without changing source ownership. With the
destination's old flags, only binary-search missed; with `/Oi`, all 70 rows
matched. Comparing `_comdat_sections` raw bodies and relocation offsets,
kinds and symbol names against the two separately built objects gives 166
destination copies + one donor copy = 167 composition copies: none added,
removed or changed. This is composition evidence, not an applied merge.
The existing shadow identity finding for `Rva0040B6D4`'s AwardTrigger vector
base constructor has identical bytes and relocation identities with and
without `/Oi`; it was not repaired or added to a register.

An overlapping normal build and strict-provider preparation invalidated the
destination object receipt. A cached normal retry did not repair it. Its
object and dependency sidecar were removed together, then a serial normal
build with the optional object store disabled rebuilt it. Converged data
verification and the normal commit hook subsequently passed. Final strict
preparation and data checking were also run serially.

## Merge boundary and handoff

The final supported `tu_skeleton.py --merge` stopped before compiling or
editing: another worker holds `0x0007FAB3` and `0x0014F3C4`. Its report has
`accepted: []`; the source and ledger remain unchanged by that attempt.
The tool released the scope it acquired; no source-file reduction is claimed.
Retry the supported merge when those claims are available. The isolated
two-file result does not establish which other donors the full search accepts.

The earlier full dry run, before aligning the destination's intrinsic flag,
also rejected StringBase, allocator and uninitialized-copy declarations,
parser FieldParse aggregate initialization, and several vector/introsort
byte shapes. The parser's previously recorded Rva0040AF1D layout prerequisite
remains separate; no private-view reconciliation was attempted here.

The final outgoing batch audit (`origin/master..2fab882c26`, including the
previously published AIGateUpdate move) is INCONCLUSIVE. Its index predates
the outgoing base; after refreshing both edited units, the remaining missing
current receipt is `Object/Update/AIGateUpdate.cpp`. Carry that unit and the
since-index selection check into the next census. No proven loss was reported,
and this is not a clean full-batch linking verdict. The earlier AIGateUpdate
path-compatibility audit remains in its own merge handoff; this pass moves no
paths. The donor has no gate, identity, data, header or hatch register keys to
retire. Destination's existing FieldParse, INIException and NameKeyGenerator
header queue entries remain untouched.
