# BFME 1 reference freshness, 2026-10-30

BFME 2 base: `4bf903241756abcd19dd7a73cf78fc87ca1b6904`. The local freshness
receipt was overdue, so official `Open-BFME/Open-BFME-1` master was fetched
once, without recursion. The clean old checkout and committed gitlink were
`1d5131d3f193cdf01a99da66ccd6828639585650`; the fetched snapshot is
`aeb018303c11f20f1780600a3add79c3c34b36a3`.

## Inputs and donor evidence

The nine upstream path changes include four game source files and no headers
or build inputs. `inputs/reference`, `inputs/toolchains` and `inputs/vendor`
retain identical tree IDs; the resolved directories exist. No layout repair
is needed. The dependency intersection audit inspected 21,621 local receipts
and 1,499 distinct BFME 1 paths, finding no reference to a changed path.
This intersection audit does not substitute for the full gate's cache checks.

The scoped donor refresh reads the new revision's narrowly filtered ledger
metadata and both retail images; it does not read decoder sources or import
a donor body. Of 38 selected ledger rows, 27 qualify as native bodies:
18 have no exact placement, five have multiple placements, and four rows
have unique placements (three distinct target RVAs). Placement establishes
byte evidence, not target identity or source-transfer approval. No global
sweep/control-floor result or new coverage is claimed. The active
`build/bfme1_sweep` cache was empty, and no old donor compile trial is reused.
Historical attempt evidence remains historical.

## Verification

Both original full-gate processes exited zero with every check green:
99,015/99,015 function rows across 20,248 source files; 31,537 string literals
and 2,247 empty-string references; 9,116 float literals; 6,425 named imports;
18,875 DIR32 symbols; pin consistency, module registry and source claims;
2,238 data rows; and the no-op patch. There are no old-input failures or
new-input regressions. Full outputs are old-full.txt and new-full.txt.

The old gate restored 5,619 stale objects from the validated object store and
compiled the remaining stale sources. The new gate found all 20,247 TUs
current in the dependency cache. The identical code/ledger inputs and unchanged
header/toolchain trees allow this reuse; both runs still perform every byte
and reference check. No cache check or verifier was bypassed.

The ignored freshness stamp is written only after these successful results.
This is reference maintenance; no census, image-ownership or source-coverage
gain is claimed. No link-cycle, nightly or smoke runner was started.

Commands at the fixed BFME 2 base:

    BUILD_POOL=12 ./build.sh
    git -C reference/open-bfme-1 checkout --detach aeb018303c11f20f1780600a3add79c3c34b36a3
    git add reference/open-bfme-1
    PYTHONUNBUFFERED=1 BUILD_POOL=12 ./build.sh

Staging the clean gitlink makes the build guard verify the intended prospective
pin. The first new-input invocation refused before compiling because the
changed gitlink was not yet staged; staging fixed that input mismatch without
changing the verifier.

The companion CRT-header work stays in a separate worktree during this
comparison, so both full gates use identical BFME 2 source and ledger inputs.
