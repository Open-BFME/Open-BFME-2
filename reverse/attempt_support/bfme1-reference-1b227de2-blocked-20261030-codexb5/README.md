# BFME 1 freshness attempt blocked by the shared compiler lock

The ignored freshness receipt was over 72 hours old, so this session fetched
official `Open-BFME/Open-BFME-1` master once, without recursion. The clean,
committed reference remains `efb2b2a27078c6e96538a8c587438b72b675d6df`;
its earlier full verification is recorded by BFME 2 commit `c07ab1f491a`.
The fetched snapshot is `1b227de2b4fba1e79a69a9e16d3b6e5c4fbb831e`.
Neither the checkout nor the gitlink was advanced, and the ignored freshness
receipt was not rewritten. Future freshness checks therefore remain required.

## Exact blocker

The ordinary old-input `BUILD_POOL=16 ./build.sh` ran at BFME 2
`cf3cb470f7aa46c241e5daefdb746bc4e1fb9c9d`, with Code and ledgers unchanged.
It found 6,688 of 20,550 units stale and restored 3,713 from the validated
object store. It then waited more than twenty minutes for the shared
full-build compiler lock, with 2,975 units still to compile. The original
process was polled throughout; no duplicate full gate was launched. It was
terminated while still in `locks_lock_inode_wait` (exit 143). The log and
stop receipt are included. This is an incomplete environmental check, not a
passing full gate or an observed reference regression. No new-input gate ran.

The selected STLport migration was verified in a separate prepared worktree,
leaving this baseline's source and ledger unchanged until it was stopped.

## Completed input and donor audit

`inputs.json` records all 49 changed upstream paths: eleven game source
files and no headers or build-setting changes. The resolved `game/` and
`inputs/reference/` directories exist, and the latter tree is identical.
The initial 20,428 existing-source dependency receipts record 1,507 BFME 1
paths, with no intersection with the changed paths. This initial scan does
not prove final cache currency; that requires the pending full gate.
Changed donor basenames are mentioned only in comments, with no changed
include/import consumer found.

The ordinary stale sweep cache was archived out of its active lookup path;
`discarded-cache.json` records its hashes. `affected_donors.py` performed a
scoped refresh from non-decoder upstream ledger metadata and the two retail
images, without reading donor source text. Its detailed results and summary
record the donor revision and image hashes: 50 selected rows, 28 eligible
native bodies, 21 without an exact placement and seven without a usable
needle. No donor compile trial is reused by this attempt. This is no global
sweep/control-floor result, source transfer or identity claim.

## Resume

When the shared compiler is available, repeat the old/new full verification
at one unchanged current BFME 2 revision, refresh any inputs changed since
this snapshot, and publish the verified pointer. Only then write a successful
freshness receipt. Retain the current verified pointer until that completes.
No nightly, link cycle or game smoke run was started.
