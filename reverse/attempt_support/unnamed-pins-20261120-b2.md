# Pins on rowed addresses that nothing names (b2, 2026-11-20)

Not acted on. 241 `reverse/symbols.csv` pins look unused; none was removed, because the proof
needs every object current and the full `./build.sh` meant to refresh them was stopped at 60
minutes without output. Table: `unnamed-pins-20261120-b2.tsv`.

## What was measured (at `e84000acc2`)

| Step | Pins left |
|---|---|
| Pin address is a row's start address and the pin's name is not that row's name | 9,199 total; 7,032 + 694 + 377 second names by an earlier, looser count |
| Named by no object in `build/match` (external symbol index, undefined or defined), no row, no `/alternatename` text | 1,984 |
| Has a class component, and no source under `Code/` spells that class | 392 |
| Nor any source under `reference/shims`, `reference/open-bfme-1/game`, `vendor` | 250 |
| Name appears in no other `reverse/*.csv`, `*.tsv`, `*.txt` | 241 |

Of the 241, 222 carry a helper-style class name (`Rva…`, `Bfme…`, `Gen…`, an address token) and
19 a meaningful one (`LevelGrantSpecialPowerBase`, `SidesInfoStringVector`, …). The 19 sit on
rows with address-derived names and are naming evidence: keep them.

## Why it is not proven yet

- The object index came from `build/match` as it stood; an object older than its source would
  hide a reference. A finished full build removes that doubt.
- A literal source search cannot see token-pasted class names. `Code/` has such macros
  (`S4Mem##ADDR`, `Rva##RVA##Object`, `NAME##Sub`, `OWNER##Node`). A coarse wildcard match on
  every paste pattern flags 217 of the 222; the precise test (each pasted fragment must itself
  appear as a standalone word in source) was not run.
- `docs/naming.md` retires a callee pin only when no object the real link takes names it,
  reading symbol tables, weak externals, `/alternatename` and `/INCLUDE`. The index here read
  externals only; a raw fixed-string pass over the objects (`rg -a -F -f names build/match`)
  covers the rest.

## How to finish

1. Run a full `./build.sh` to completion, then index every object's externals.
2. Recompute the 1,984 with the raw fixed-string pass; drop any name found in an object, a
   source, a directive or another ledger.
3. Keep pins whose own name is meaningful while the row's is address-derived.
4. Delete the rest from `reverse/symbols.csv`; run `tools/check_csv.py`,
   `tools/pin_consistency.py --check`, `tools/hatch_counters.py --update`; commit with a
   `Verifier-Change:` trailer for the baseline.

With fresh objects the class-in-source test is unnecessary, so the candidate set is the 1,984,
less the meaningful names, not only the 241.

The same session removed 60 pins the safe way (each together with its `/alternatename` and its
last call site), commits `0c9b6fc1f6..e84000acc2`.
