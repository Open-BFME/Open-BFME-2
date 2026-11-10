# 576 of the 927 false-reject records are already closed; the tooling lane is 351

Measured at `598687dc8dd`, 2026-11-09, over `reverse/re_attempts.log`.

AGENTS.md gives a tooling seat one instruction for this lane: `rg "false-reject"
reverse/re_attempts.log`, reproduce, fix the check. The log is append-only and
carries no date, so 927 records read as one undifferentiated pile and the seat
cannot tell which of them a later commit already answered. This note prices the
pile.

## The question that sorts it

An earlier attempt of mine sorted by *"has the check's own file changed since the
record was written"*. That has no signal: it flags 584 of 601 mappable records,
because these tools change daily. I did not publish it.

The question that does sort it is about the ledger, not the tool: **does the
name the record was trying to land now own that address?** Whatever repaired it
-- a tool fix, a different worker, a rule change -- the work is done.

One refinement matters. A compiler label's ordinal is assigned by the build, so
a record wanting `$L6014` is satisfied by a `$L6755` row at that address; only
an address still held by a generated placeholder (`uw_*`, `ji_*`, `?rva*`,
`dup_*`, a `Code/gen_small/` source) or held by nothing is open. Without that
refinement the count is 501 closed rather than 576, which is the measure being
wrong, not the backlog being smaller.

## Result

| | records |
| --- | ---: |
| **CLOSED** -- the wanted identity owns the address | **576** (62%) |
| OPEN -- a different real name owns it (needs a read) | 144 |
| OPEN -- still a placeholder | 138 |
| OPEN -- no row at the address | 69 |
| | **927** |

Per check, the not-closed remainder:

| not closed | check |
| ---: | --- |
| 110 | add_match |
| 27 | rename.py |
| 12 | link_census |
| 11 | hatch_counters |
| 11 | header_adopt_lane |
| 10 | check_csv |
| 10 | name_lane |
| 8 | vtable_bridge |
| 7 | classification |
| 7 | tu_skeleton |

`link_debt.addresses` (14), `tail` (12), `funclet` (9) and `flag_defaults` (6)
are fully closed; `link_check` has 18 of 19 closed and `pin_admission` 26 of 29.

## What that bought immediately

Reading the 110 open `add_match` records by what currently holds their address
put 99 of them on `uw_*` generated-unwind rows, and 97 of those on one shape:
a row `gen_small.py sweep-funclets` minted into the parent's real TU, which
`add_match --replace-rva` refused because `generated_unwind_scaffold` keyed on
`gen_uw.py`'s harness path and file header. Fixed at `1d70dd1552f`; 1,264 rows
were in that state.

That is the point of the measure. The cluster was invisible while the backlog
looked like 927 equal items.

## What this does not claim

- **Not that the 351 are all real false rejects.** 144 are "a different real
  name owns it", which needs a human read: the record may have been wrong, or
  the address may have been re-identified since. They are a reading queue, not
  a work queue.
- **Not that a CLOSED record proves the check was ever wrong.** It proves only
  that the address no longer wants the name, which is what makes it not worth a
  seat's time. Some were closed by the author finding a different route.
- **Not a verdict on the 23 records whose check token this does not map**
  (`name`, `pre`, `ms`, `tail` and friends are often the first word of a
  multi-word description, not a tool). That is my parsing, not the records'.
- **No dates.** Dating the log is possible but cheap only approximately: the
  file is append-only, so sampling commits and reading `git show <sha>:<path> |
  wc -l` gives a monotone line-to-date map in seconds where `git blame` exceeds
  ten minutes (30,988 commits touch the log). I measured that and did not need
  it here -- the ledger answers better than a date does.

## Method

For every 5-field record containing `false-reject`, take its symbol and RVA,
look up every `reverse/functions.csv` row at that RVA, and compare. Placeholder
detection is by name prefix (`rva`/`bfmeRva`/`ji_`/`uw_`/`dup_`/`d_` followed by
hex) or a `Code/gen_asm/`, `Code/gen_small/` source. Symbols annotated by their
author, e.g. `_$E2(LivingWorldEyeTower)`, are read bare. The run is a few
seconds; it loads the whole ledger once, which is why it belongs in a seat's
scratchpad rather than in `tools/`.

## A finding alongside it: no hook runs pytest

`rg -n "pytest" .githooks/*` finds nothing, and the verification alarm watches
the gate and real-link workflows. So a broken test can sit indefinitely -- and
a documented command can ship broken for eight days with its own test red the
whole time, which is cause 3 below. Cases found while verifying the above:

- Three `test_gen_uw_shapes.py` tests had failed since 2026-10-17 on a BFME 1
  constant asserted against BFME 2's image (fixed at `22f4d5b0e60`).
- **15 tests failed** in a 31-file run, identical at `a8381105532` and after
  the commits above, so none of them was caused here.

  An earlier revision of this note said all 15 "fail only in a combined run and
  pass when their own file runs alone". That was wrong, and wrong in the
  direction that makes them look harmless: only the 8 are order-dependent. I
  had verified `test_add_match_import_scaffold.py` alone and generalised from
  the one file I checked. Run alone, each file gives:

  | file | tests | alone | cause |
  | --- | ---: | --- | --- |
  | `test_add_match_import_scaffold.py` | 8 | **passes 84/84** | another file's import |
  | `test_reloc_names.py` | 3 | **also fails** | no specimens left in the data |
  | `test_stlport_overlay.py` | 2 | **also fails** | assertion in the wrong path form |
  | `test_dump_predicate.py` | 1 | **also fails** | a real offence, another lane |
  | `test_claims.py` | 1 | **also fails** | `claims.py` CLI bug |

  So 7 of the 15 were plain broken tests, which is worse than order
  dependence, not better. Three separate causes, now each diagnosed:

  **1. The 8 are the `tool:test_exit_link` bug again** (fixed at
  `cd973bd3e4c`). `test_reloc_names.py`'s `_load()` overwrote
  `sys.modules["build"]` with a second copy of the module. Tools resolve some
  imports at call time -- `add_match.replacement_scaffold` does `import build`
  inside the function -- so it read the fresh copy's real `game.dat` while the
  fixture had patched `build.EXE` on the first copy;
  `pe_imports.generated_import_scaffold` then found no import slot and the
  admission refused a row it should take. It bites at COLLECTION, before any
  test in the poisoning file runs, which is why the two files pass together in
  a 3-file run but not a 31-file one, and why the file's position in the list
  does not matter. Fixed by the same guard.

  **2. `test_stlport_overlay.py` compared a POSIX path against a Wine
  `INCLUDE`.** `build.compiler_command` writes every entry through
  `build.wine_path` off Windows (`Z:\home\...`), so the tool was right and the
  test was stale. Its negative branch had also gone vacuous: the plain
  spelling is absent from a Wine `INCLUDE` whether the overlay is on or off,
  so the three unselected cases asserted nothing.

  **3. `claims.py claim --dry-run KEY...` exited 2** -- the form
  `tools/claims.py`'s own usage text and `docs/claims.md:16` both print. With
  `action` then `rvas` (`nargs="*"`), argparse binds the whole positional group
  inside the first run of plain words, so `claim` fills `action`, `rvas` takes
  the empty rest, and every key after the flag is "unrecognized". Only
  keys-then-flags worked. It shipped broken at `5e914a66b49` (2026-11-01) with
  its own test red from that day, and the same applies to `--note`.

  Left for their owners: `test_dump_predicate.py`'s single offence
  (`tools/ms_header_audit.py:3243` decides dumpness by
  `path.startswith("Code/gen_asm/")`), and `test_reloc_names.py`'s 3, which
  are one state and not a tool bug -- `reverse/reloc_names.csv` now holds **0
  rows**, the only dup-claimed anonymous thunked body (`0x00355257`) is pinned
  in `symbols.csv`, and no pinned-but-unclaimed `FUN_` row is left. These
  tests mine the live data for a specimen and the project has named its way
  out of all of them. Whether to skip when drained or synthesize fixtures is a
  call for that lane: the file's own convention is to raise on a missing
  specimen, so the red is arguably the authors' intended signal with nowhere
  to go.

**19 other test files carry the same unguarded `_load`** and are one import
away from repeating cause 1: `test_gen_getters`, `test_gen_uw_shapes`,
`test_gen_tinst`, `test_inventory`, `test_dump_predicate`, `test_merge_cluster`,
`test_ledger_terminators`, `test_ledger_guards`, `test_red_rows`,
`test_gen_uw_transaction`, `test_scan_population`, `test_land_supersede`,
`test_pin_consistency`, `test_pin_audit`, `test_wb_queue_hooks`,
`test_readability_metric`, `test_tu_structure`, `test_zh_packet_metadata` and
`test_reloc_names` itself (now guarded). Each is a two-line fix, but whether
any of them wants a fresh copy deliberately needs reading, so they are not
swept here.

I did not run the whole 321-file suite; the 31-file subset above is every test
importing `add_match`, `gen_uw` or `ledger_io`. After the three fixes it is
**4 failed, 1757 passed, 4 skipped**, down from 15 failed.
