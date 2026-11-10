# 66 of 11,838 tests are red, and nothing was ever going to say so

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
| `test_recovery_experiments.py` | 22 | 22 failed, 5 passed | `StopIteration` |
| `test_header_dependents.py` | 14 | 14 failed, 58 passed | a dependents list gained `Code/B.cpp` |
| `test_nightly_measure.py` | 9 | 9 failed, 218 passed | `Refused: tracked path differs from approved commit: .githooks/post-checkout` |
| `test_publisher_service.py` | 6 | 6 failed, 4 passed | `assert 0 == 1` |
| `test_reloc_names.py` | 3 | 3 failed, 11 passed | no specimens left in the data (below) |
| `test_boot_smoke_profile.py` | 3 | 3 failed, 24 passed | `RedirectError not raised`; `pefile.PEFormatError: DOS Header magic not found` |
| `test_publisher.py` | 1 | — | |
| `test_link_rank_snapshot.py` | 1 | — | |
| `test_flag_input_coverage.py` | 1 | — | |
| `test_flag_delta_sources.py` | 1 | — | |
| `test_fix_eh_prolog_sizes.py` | 1 | — | |
| `test_doc_lint.py` | 1 | — | |
| `test_claims_gc.py` | 1 | — | |
| `test_build_lib_thin.py` | 1 | — | |
| `test_tu_structure.py` | 1 | passed alone | **mine, fixed at `7b1c3d1eb1a`** |
| | **66** | | |

The five clusters are five different lanes. `test_nightly_measure.py` and
`test_boot_smoke_profile.py` belong to jobs AGENTS.md says not to start without
a maintainer, so their failures want that owner rather than a passing seat.

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
