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
the gate and real-link workflows. So a broken test can sit indefinitely. Two
cases, both found while verifying the above:

- Three `test_gen_uw_shapes.py` tests had failed since 2026-10-17 on a BFME 1
  constant asserted against BFME 2's image (fixed at `22f4d5b0e60`).
- **15 tests fail only in a combined run** and pass when their own file runs
  alone. Identical at `a8381105532` and after my commits, so they are
  pre-existing and nothing here caused them:

  | file | tests |
  | --- | ---: |
  | `test_add_match_import_scaffold.py` | 8 |
  | `test_reloc_names.py` | 3 |
  | `test_stlport_overlay.py` | 2 |
  | `test_dump_predicate.py` | 1 |
  | `test_claims.py` | 1 |

  `test_add_match_import_scaffold.py` passes 84/84 alone. This is the same
  class of bug as `tool:test_exit_link` (fixed at `cd973bd3e4c`): test files
  sharing process state. `test_dump_predicate.py`'s one offence is real and in
  another lane -- `tools/ms_header_audit.py:3243` decides dumpness by
  `path.startswith("Code/gen_asm/")`.

I did not run the whole 321-file suite; the 31-file subset above is every test
importing `add_match`, `gen_uw` or `ledger_io`.
