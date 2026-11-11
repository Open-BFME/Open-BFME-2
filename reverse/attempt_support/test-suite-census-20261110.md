# 66 of 11,838 tests are red, and nothing was ever going to say so

> **22 remain.** Of the 66 measured, 44 are fixed: `test_tu_structure.py`'s 1
> (`7b1c3d1eb1a`, which the run caught and which was already fixed when this was
> written), `test_header_dependents.py`'s 14 (`ee2d7795743`) and
> `test_recovery_experiments.py`'s 22 (`60dc4dca8fe`), and three singletons
> (`41a969507d6`, `c02cdfcaa65`). An earlier revision said
> "52 remain", which double-counted the one already fixed. The table records
> which and why.
>
> Both large clusters were **one line of fixture each**, and neither tool was
> wrong. That is now 31 of the 37 traced to a fixture that misdescribed its
> tool, against one real tool bug all day (`claims.py`'s argument order).

Measured at `7b1c3d1eb1a`, 2026-11-10: `python3 -m pytest tools/tests/` over all
322 files, 20 minutes, **66 failed, 11,772 passed, 176 skipped**.

## Nothing runs this suite

`grep -rln pytest .githooks/ .github/workflows/` finds **nothing**. Not a hook,
not a workflow. The verification alarm watches the gate and real-link
workflows, which do not run pytest either. So a test can break and stay broken
indefinitely, and the ones below have.

That is the whole explanation for this note. Every failure examined so far has
been a stale test rather than a broken tool: the tools are guarded by the byte
gate and the commit hooks, which do run, so tool regressions get caught --
nobody was checking whether the *tests* still described the tools.

Earlier today eight failures were repaired this way (`claims.py`'s documented
`claim --dry-run` argument order was the one real tool bug among them;
`4bb44369a15`, `cfef858142e`, `5e548edd49d`, `c2ae255b3eb`, `3e462179eba`,
`7b1c3d1eb1a`), and two were parked with their reason (`0425a500500`).

## Where the 66 are

Every cluster below **also fails when its own file runs alone**, so none of it
is cross-file order dependence. First cause shown is the first distinct error
in a standalone run, as a starting point and not a diagnosis.

| file | failed | alone | first cause seen |
| --- | ---: | --- | --- |
| `test_recovery_experiments.py` | 22 | ~~22 failed, 5 passed~~ | **fixed at `60dc4dca8fe`**: the fixture replaces `subprocess.run` wholesale for the compiler and finds the output by scanning argv for `-Fo`, so `build.wine_path`'s own `winepath -w` call landed in it and `next()` raised `StopIteration`. Stubbing `wine_path` also drops the file from 2.25s to 0.42s and removes its Wine dependency |
| `test_header_dependents.py` | 14 | ~~14 failed, 58 passed~~ | **fixed at `ee2d7795743`**: the fixture wrote receipt dep keys with `\`, which `ROOT / dep` cannot resolve on POSIX, so every unit with a dep looked uncompiled and the vendored bound collapsed to "every unit" |
| `test_nightly_measure.py` | 9 | 9 failed, 218 passed | `Refused: tracked path differs from approved commit: .githooks/post-checkout` |
| `test_publisher_service.py` | 6 | 6 failed, 4 passed | `assert 0 == 1` |
| `test_reloc_names.py` | 3 | 3 failed, 11 passed | no specimens left in the data (below) |
| `test_boot_smoke_profile.py` | 3 | 3 failed, 24 passed | `RedirectError not raised`; `pefile.PEFormatError: DOS Header magic not found` |
| `test_publisher.py` | 1 | ~~fails alone~~ | **fixed at `6b15e593a45`**: the fixture's `pre-receive` ruleset was written 0644, and git silently ignores a non-executable hook, so the push it expects refused went through |
| `test_link_rank_snapshot.py` | 1 | ~~fails alone~~ | **fixed at `95b9398847b`**: it asserted a scoped-naming handoff that AGENTS.md gates off until the game reaches the menu (`name_scoped.RELATED_WORK_HANDOFF = False`); now asserts its absence, with a sibling covering it enabled |
| `test_flag_input_coverage.py` | 1 | ~~fails alone~~ | **fixed at `95b9398847b`**: `ledger_cache` memoises on the blob id in the real checkout's git dir, shared by every worktree and kept between runs, so once that blob was cached the deleted git object could never be reached |
| `test_flag_delta_sources.py` | 1 | ~~fails alone~~ | **fixed at `c02cdfcaa65`**: the hook gained `classify_full_scope`, so a selection covering every provider becomes one ordinary full build; the empty selector list means "build everything" and the test read it as nothing verified |
| `test_fix_eh_prolog_sizes.py` | 1 | ~~fails alone~~ | **fixed at `6b15e593a45`**: the inventory gained `FUN_0061ed9c` 234 bytes inside the byte-verified 388-byte body at `0x0021ECB2`; an overlap is now excused only where a matched ledger row holds that exact extent |
| `test_doc_lint.py` | 1 | fails alone | **not a test bug — real content debt** (below) |
| `test_claims_gc.py` | 1 | ~~fails alone~~ | **fixed at `41a969507d6`**: `renew()` now sends one batched push before the per-token retry loop, so 3 pushes carry 1 backoff, not 2 |
| `test_build_lib_thin.py` | 1 | ~~fails alone~~ | **fixed at `41a969507d6`**: `@__security_check_cookie@4` was recovered from `msvcrt.lib` to real C++, so its source is no longer an archive |
| `test_tu_structure.py` | 1 | passed alone | **mine, fixed at `7b1c3d1eb1a`** |
| | **66** | | |

The five clusters are five different lanes. `test_nightly_measure.py` and
`test_boot_smoke_profile.py` belong to jobs AGENTS.md says not to start without
a maintainer, so their failures want that owner rather than a passing seat.

## `test_doc_lint.py` is not a test bug either: the docs have drifted

`test_repository_guide_is_clean` lints the real tree and `tools/doc_lint.py`
reports **20 errors and 8 warnings**. The lint works; the documentation has
drifted behind the fleet's renaming and merging, in three groups:

- **10 `[sources]`** -- `docs/doxygen/sources.cfg` lists one file that no longer
  exists (`GameLogicRandomSeed_get.cpp`) and nine that are placeholder-named and
  so undocumented (`BfmeThingRE.cpp`, `BfmeItemKA.cpp`, `BfmeB1137.cpp` …).
- **6 `[ref]`** -- a `\file` naming a path absent from `sources.cfg`
  (`WW3D2/Register_Aggregate_Prototype.cpp`, `GameSpy/md5c.c`, …).
- **12 `[name]`** -- documented names in no ledger, `Code/` or shim: 3 errors
  (`MeasureIcmpPing`, ×3 sites) and 9 warnings that may be Zero Hour names.
- 1 `[address]` -- `w2_wwlib_md5_sha1.dox:17` names `0x00606220` where the
  function should be named.

Left for the guide's owner rather than bulk-edited here: each one is a content
decision (was the file renamed, merged away, or should it be documented?), and
guessing would put wrong prose in the manual to make a test green.

## The one that is not a test bug

`test_reloc_names.py`'s 3 are a data state. `reverse/reloc_names.csv` holds **0
rows**, the only dup-claimed anonymous thunked body (`0x00355257`) is pinned in
`symbols.csv`, and no pinned-but-unclaimed `FUN_` row is left, so all three
specimen helpers come up empty. The file's convention is to raise on a missing
specimen, so the red is arguably the authors' intended signal. Whether to skip
when drained or synthesize fixtures is that lane's call; it is recorded in
`false-reject-backlog-is-62-percent-stale-20261109.md`.

## What this does not claim

- **Not that 65 tools are broken.** On today's evidence the opposite is likely:
  of the ten failures diagnosed so far, nine were the test drifting from a tool
  that still works, and several had stopped checking anything (an assertion
  comparing a POSIX path to a Wine `INCLUDE` passed vacuously whenever the
  overlay was off; a fixture whose includes all resolved "missing" never scanned
  the header conflicts it existed to show).
- **Not that running it in a hook is the fix.** Twenty minutes per commit is not
  a hook, and twenty minutes per push would stall the landing window every
  worker shares. A workflow is the obvious home, but adding one spends the
  project's CI and starts reporting to maintainers, so it is their call, not a
  seat's. Recorded here so it can be made deliberately.
- **No per-test diagnosis.** Each line is a starting point. The two caveats that
  cost real time today: a test can fail because its fixture is unfaithful rather
  than because the tool moved, and a pinned SHA can be unreachable because
  `tools/push.py` rebases before pushing (see `tools/tests/fixtures/README.md`).

## Method

`python3 -m pytest -q -p no:cacheprovider tools/tests/` once, then each failing
file alone. No `-x`, no `-k`, no plugins (none are installed, and there is no
`conftest.py` or pytest config in the repo, so collection order is the argument
order and the full run is alphabetical).
