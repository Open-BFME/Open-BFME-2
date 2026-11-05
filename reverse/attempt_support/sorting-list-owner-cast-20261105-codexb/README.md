# Sorting list owner casts, 2026-11-05

Inspected revision: `b8a4a09885e1163173864fe10aeeee995ecc0235`.
Scope: `Code/Libraries/Source/WWVegas/WW3D2/sortingrenderer.cpp`, claimed as a file.
This tests a narrower alternative to the full list-sharing trial in
[the October 29 handoff](../sorting-renderer-shared-state-20261029-round2.md).

The data queue's two registered findings are `_sorted_list` at RVA 0x009B6200
and `_clean_list` at RVA 0x009B620C. The data ledger's current names are
`?g_00DB6200@@3PAXA` and `?g_00DB620C@@3PAXA`. Both are defined as four-byte
`void *` objects in `Rva007B6880Thunks.cpp`; their matched setters are at
0x007B7090 and 0x007B70A0. Those pointer definitions are vptr anchors, not
proof of complete list storage. The existing DLListClass header supplies a
virtual destructor plus head and tail, a 12-byte native view.

## Rejected trial

Replace the two private static list objects with casts of the addresses of
those existing pointer owners. No second external list symbol was introduced.
The first build retains 10/11 bodies and all five data rows; only
`SortingRendererClass::Deinit` (0x00130A20, 151 bytes) fails. Each inlined
`Remove_Head` gains an additional null check. Retail starts its first loop
`56 57 33 ff a1 04 62 db 00 3b c7 8b f0 74 31`; the trial starts
`56 57 33 ff a1 04 62 db 00 8b f0 3b f7 74 33 3b c7 74 1d`.

Binding local list references inside Deinit produces the same failure.
[trial.patch](trial.patch) preserves this second form as an unapplied attempt.
Neither form belongs in Code. They were both reverted.

Even a matching cast would not establish complete backing storage: the two
current owners define only the vptr word. The next attempt must reconcile full
list storage and the private-list visibility contract together (or establish
approved TU composition), rather than treating a clean symbol name as storage
closure. No baseline key was retired, and no link or ownership gain is claimed.

## Restored-source checks

- `./build.sh Code/Libraries/Source/WWVegas/WW3D2/sortingrenderer.cpp`: 11/11
  function bodies and 5/5 data rows pass. String, float and import checks pass.
- `find_declared_unmatched.py` reports all defined functions already matched.
- `data_check.py` remains in shadow with the original two findings and zero
  findings outside the baseline.

Time: 18 minutes. Model: gpt-6.1-sol.
