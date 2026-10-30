# WWLib vector allocation-header cleanup

Base: `e3570ba43c`. Sources:

- `Code/Libraries/Source/WWVegas/WWLib/simplevec_float_cleanup.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/simplevec_vector3_dtor.cpp`

Each source hand-declared the Microsoft array-delete operator to add its
nonthrowing specification. Both now include the toolchain `<new>` header before
`always.h` and select its existing `_OPERATOR_NEW_DEFINED_` guard. This avoids
redefining the placement array operators already supplied by `<new>`. An initial
trial including `<new>` after `always.h` failed with duplicate placement-operator
definitions; the final arrangement compiles without changing shared headers.
No source path, row, pin, class declaration, compiler flag or hatch is changed.

Verification:

- Frozen-file checks pass before and after the edits. Baseline and final
  supported builds pass all 12 matched rows (five float, seven Vector3), with
  no string, float or import references skipped. Final strict explicit-provider
  preparation also passes all 12 rows and records current receipts for both.
- Before/after object-fact comparisons preserve all ten external COMDATs per
  object: their names, relocation-aware digests and sizes, plus all strong,
  undefined and weak external sets. This is object-fingerprint equality, not
  additional retail coverage for unrowed definitions. Baseline snapshots are
  local ignored artifacts under `build/simplevec-msheaders-codexb5/`.
- The owning Microsoft-header auditor reports zero local Microsoft-name
  occurrences in both files. Its scoped `refresh_queue` removes exactly their
  two queue rows; other rows remain intact.
- Ordinary previews against `6fe1089c24` (2026-10-30 04:25) retain LINKS:
  float 175 -> 175 and Vector3 227 -> 227 authored bytes, 402 total. EH has
  zero applicable rows, no baseline use and no missing objects. The CSV check
  passes (99,012 function rows, 9,412 symbols, 2,237 data rows).
- The staged audit across all local outgoing commits is INCONCLUSIVE: its
  index predates base `8822408da0` and three changed sources lack current
  receipts, first `Common/FprintfAppendLine.cpp`. Earlier commits have already
  been handed to the runner publisher and are immutable. This pass does not
  certify their complete affected-consumer closure. See the scoped audit
  result below for the two current providers.
- The staged audit scoped to base `e3570ba43c` confirms current receipts for
  both edited providers, then exits 2, INCONCLUSIVE: the index is older and
  `Common/0CreateAHeroManager21FE49.cpp` lacks a current affected-consumer
  receipt. Full selection and loss checks remain pending. Neither audit is
  reported as a successful link-closure check.

No census, image-ownership or source-file gain is claimed. The measurable
cleanup is two retired Microsoft-header findings. Carry the providers and
related consumers into the next scheduled census.

Reference freshness remains overdue. Official BFME 1 master was fetched at
`a72edf759cf674820d6c10d40a50472f1cd8a226`; the clean repository pin remains
`337e4b48e8f295f74bdd1155ad2b6dd848b63c32`. Reference ownership is held by
`yasinschroeder-codex5`, so this pass makes no reference change or successful
freshness stamp and imports no donor body.
