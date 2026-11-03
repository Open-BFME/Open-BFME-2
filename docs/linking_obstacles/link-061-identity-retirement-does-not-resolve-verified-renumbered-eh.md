### LINK-061: identity retirement does not resolve verified renumbered EH labels

**Status: Verifier prerequisite cleared; DX8 descriptor reconciliation remains.
Updated: 2026-10-27; inspected revision: `b8ac4b22c1`.**

- **Evidence / scope:** [the DX8 retirement refusal](../../reverse/attempt_support/dx8-identity-funclet-refusal-20261026.md)
  records 13 identity keys in dx8wrapper.cpp. Normal verification passes 228
  functions, 13 data rows and 21 EXACT EH graphs, including 72 renumbered funclets.
- **Completed:** no source or register edit. Retirement correctly refuses four
  stale providers and separately rejects old funclet labels already resolved by
  the byte gate. The latter is recorded as a false reject, not a debt repair.
- **Remaining / next check:** reconcile the retirement tool with verified parent
  EH resolution in a separate tooling change, refresh providers, then repair and
  judge the descriptor/vector bindings. Do not hand-change pins or labels.
- **Additional consumer (2026-10-26, `9e1ca7f93f`):**
  [window video's current check](../../reverse/attempt_support/window-video-debt-cleanup-20261026.md)
  reproduces the same literal-label refusal for four funclets whose parents
  pass all seven EH graphs. Five other retirement findings are not classified
  as false rejects. No identity key is removed; the separate 15-marker hatch
  cleanup preserves every matched byte.
- **Additional consumer (2026-10-26, `42e205255d`):**
  [audio key insertion](../../reverse/attempt_support/audio-identity-funclet-refusal-20261026.md)
  passes all five rows and two EXACT EH graphs. Retirement still demands
  `$L4992`, while the verified parent places `$L5053` at 0x00773EC5. The
  relocation scanner repeats the literal lookup, so skipping the first refusal
  would conceal the cleanup call. Missing/stale providers remain independent
  prerequisites; seven real-COFF regression cases reproduce the verifier defect.
- **Verifier repair (2026-10-26):**
  [strict shared EH resolution](../../reverse/attempt_support/identity-eh-retirement-verifier-20261026.md)
  preserves the logical row key while scanning the physical label's references;
  unproved labels refuse retirement and ordinary/full scans. After normal
  provider refresh, audio's two outgoing identity keys have a clean verdict;
  its complete 992-row scan checks 1,117 references with zero findings. This
  clears the audio verifier prerequisite, not the other source-specific repairs.
- **DX8 follow-up (2026-10-27):**
  [the destructor fold receipts](../../reverse/attempt_support/dx8wrapper-destructor-folds-20261027.md)
  clear the funclet-label prerequisite for this source too. Normal verification
  passes 230 functions and 13 data rows; refreshing 22 provider sources passes
  404 functions and three data rows and permits a complete retirement verdict.
  Tool-admitted fold receipts replace the two existing derived-vector destructor
  pin annotations without increasing pins. Retirement removes five identity keys;
  eight keys for the duplicate descriptor constructor/destructor views remain.
  Reconcile those views with naming evidence, rather than adding alias pins.
  The paired current thread-lock provider preview is 2/2 LINKS (28,658 and
  247 authored bytes); it confirms LINK-106, not a new census result.
- **Clearance / census confirmation:** none claimed.
