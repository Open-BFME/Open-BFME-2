# Palantir compiler guard ownership cleanup

Inspected base `71d01c340b`, 2026-10-29, seat codex4.

The default picker claimed AptPalantirCallbacks.cpp for its historical
objectives-static wrong-name key. All 37 rows already match. The first
supported retirement refused on the current `$S2` guard at RVA `0x009FF04C`:
the committed index still chose `g_Va00DFF04C` in GlobalFlagClearers_DFEExx.cpp.
The other nine historical keys are already fixed in source.

Target and history facts:

- `reverse/deleted_rows.csv` records replacement of the external guard
  clearers at `0x007774DD` and `0x007774EA` by the parent's compiler-emitted
  rollback funclets. The parent's exact EH graph binds both.
- Commit `578521da6c` moved all four static-string atexit cleanups into the
  callback unit, and explicitly left data retirement blocked on this guard.
- A current source search finds only the unused extern in
  GlobalFlagClearers_DFxx.cpp and the extern/definition in
  GlobalFlagClearers_DFEExx.cpp. No data ownership row, pin, converged global
  or active tooling refers to that external name.

Remove those obsolete declarations/definition. Generate the index with
`python3 tools/data_ledger.py --out build/codex4-palantir-data-ledger-20261029.csv`
and copy only its complete row for `0x009FF04C`. The generated row names the
existing compiler guard under HandleOverSpellStoreButton, owned by the callback
unit with one definition and four matched relocation sites. The full generation
reports 198 matched sources without objects; none belongs to this scoped
repair. Unrelated generated rows are excluded. This is compiler identity,
not a claim that retail used this source identifier.

Verification:

- Normal build of all three source paths: 38/38 function rows, two data rows
  and 11 literals pass. The callback's C++ bodies are unchanged.
- `find_declared_unmatched.py`: all definitions matched for all three sources.
- Enforced `data_check.py`: zero findings across the three sources.
- Enforced converged data check: 11 addresses, zero second names or unjudged rows.
- `eh_verify.py`: 11 EXACT graphs, none baselined or missing.
- `repair_queue.py retire data` passes and removes all ten callback keys
  from its register; no baseline lines are removed by hand.
- `hatch_counters.py --update` removes the obsolete name's two register keys,
  lowering address_global occurrences from 4,138 to 4,135.
- Ordinary preview against index `85f6b7f40c` (2026-10-29 15:08) preserves
  LINKS for AptPalantirCallbacks.cpp (1,639 authored bytes) and
  GlobalFlagClearers_DFxx.cpp (13 bytes).

No path moves, function ownership changes, new names, census gain or image
ownership measurement. Full consumer/census confirmation remains pending.
