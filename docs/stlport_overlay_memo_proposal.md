# Verify the STLport overlay once per process (proposal, not scheduled)

Status: proposal for the owner to route. It touches `tools/stlport_overlay.py`,
which every `build.compiler_command` reaches, so it needs the same care as a
`tools/build.py` change (the build cache trap, `docs/matching.md`).

## What it costs today

- `compiler_environment` calls `stlport_overlay.materialize()` for every source
  marked `// stlport46` (521 sources on 2026-11-07), on every `compiler_command`
  call, compile or not.
- Each call:
  - re-hashes all 531 files of `vendor/stlport-4.6` against `SHA256SUMS`
    (`verify_tree`);
  - re-walks the tree;
  - re-reads and re-applies every BFME patch under a file lock;
  - and compares every generated header with what is on disk.
- On srv1 that is 0.19–0.21 s per call.
- In a single-core currency check over 17,961 objects (`exit_link.stale_objects`,
  py-spy, 2026-11-07), `materialize` took 210 of 330 seconds.
  `compile_is_current` builds the command for each object, so every check of a
  `// stlport46` object pays it.
- The same cost is in every caller of `compiler_command`: the full gate's and
  the census's stale checks, the hooks' scoped currency checks and
  `link_batch_audit`.

## Proposal

- **Once per process:** memoise `materialize()` within a process on an exact
  digest of its inputs. Verify the tree and apply the patches on the first call
  and return the same destination after that.
- **Re-verify at a run's end:** add `stlport_overlay.recheck()`, the full
  `verify_tree` plus the generated-file comparison. Call it where a run already
  re-checks its inputs at the end, in the same places as
  `_inventory_cache_still_current`:
  - `build.compile_rows` after its compile phase;
  - `stale_sources` after the stale check;
  - `exit_link` and `link_census` in their final "inputs moved during the run"
    checks.
  A change found there fails the run, exactly as a moved input does now.
- **No stat-keyed shortcut:** a same-size, same-mtime edit would pass it. The
  memo is per process and the end-of-run check is exact.

## Why it is safe for the cache

- `materialize()`'s result enters the command only through the destination path
  (a digest of `SHA256SUMS` and the patches). The generated headers enter each
  object's dependency hashes. Neither changes, so `_cmd_fingerprint`, object
  bytes, receipts and the object store's keys are untouched. Nothing recompiles
  and no receipt goes stale at rollout.
- What changes is when a tampered vendor tree is detected: at the end of the
  run instead of at each command. The dependency hashes of every header actually
  included still catch a changed header for currency, as they do today.

## Expected effect and checks

- About 200 of 330 single-core seconds off a full currency check, and
  proportionally off every scoped check of `// stlport46` units. With a
  `BUILD_POOL` of 8 the parallel checks lose the same fraction.
- Tests:
  - a second `materialize()` in one process does no tree I/O;
  - `recheck()` fails after a vendor file or patch is changed mid-process;
  - a fresh process re-verifies;
  - `tools/tests/test_gate_exploits.py` keeps every verdict.
- Measure: a stale check's wall and CPU time before and after on the same tree,
  with identical answers.
