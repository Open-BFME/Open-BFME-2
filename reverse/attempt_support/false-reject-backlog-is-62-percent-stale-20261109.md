# 576 of the 927 false-reject records are already closed; the tooling lane is 351

> **Corrected 2026-11-11: the open lane is 330, not 439.** The triage was
> counting retracted records, counting retractions as records, and asking a
> question that misses work landed under a different name. The three corrections
> are in the 11-10/11-11 sections at the end; the numbers in the body above them
> are the uncorrected ones, kept so the method is legible.

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

## The open `add_match` records are one cluster, and its obstacle is gone

Re-measured at `4bb4bbac83f`: 933 records, 502 closed. Of the 159 `add_match`
records still open, **144 are a `$L<n>` compiler-local label** whose evidence
says some other TU already owns that number -- phrased as `one-name-one-address`
(79), `local-name` (30), `global-local-name` (11), `local-label` (6),
`compiler-local-label-collision` (4) and so on.

That obstacle does not exist any more. `ledger_io.same_function_name` scopes a
label to its source when both rows satisfy `ledger_io.local_funclet`, and
`test_local_funclet_names.py` already pins the admission end to end. Checked
against the live ledger: for **140 of the 144**, every existing row holding that
name is itself a proven label, so a correctly-noted row in its own TU collides
with nothing. The other 4 have no row with that name at all.

So these records are stale in their *reason* while still open in their *work*:
the address is still a placeholder, but nothing in the tooling refuses it. They
belong to the decomp lane -- each needs a parent source and the byte gate -- not
to a tooling seat.

**Why 144 of them exist is a tooling defect, and that is fixed.** The refusal
said only:

    $L356 is already in the ledger at 0x0079A030 (…)
    one name = one address; use --replace-existing only when deliberately
    repointing that claim

For a compiler label that advice is actively wrong: `--replace-existing` would
repoint the *other* TU's claim. Nothing told the worker that the label scopes
per-TU, or which of `local_funclet`'s five conditions their notes missed, so
they read a verdict on identity where the truth was a verdict on notes and
recorded a false reject. `add_match.local_label_hint` now names the missing
condition instead, on both the single and batch paths. Submitting any of the 144
without scoping notes produces the explanation in all 144 cases.

`check_csv` has the same cluster: **13 of its 17 open records are `$L` labels**,
and it already routes its duplicate-name check through the same
`ledger_io.same_function_name`, so all 13 have fully scoped peers too. Its
message said `One is wrong.`, which for a compiler label is false -- both can be
right. Fixed at `e0d4d5ee95c`, where `local_label_hint` moved to `ledger_io`
beside the rule it explains and both tools now use it.

### Two rows are latent blockers

Of 10,546 `$L` rows in the ledger, 1,898 names are used more than once and
**exactly 2 rows fail `local_funclet`**:

| row | why it is unscoped |
| --- | --- |
| `$L4914` @ `0x007AB398`, `Code/Libraries/Source/WWVegas/WWLib/stlport_target_list_73eee0.cpp` | notes carry `object-symbol=$L5079` |
| `$L3985` @ `0x0075D58E`, `Code/GameEngine/Source/Common/System/GeometryRecord.cpp` | notes are **empty**: no `gen-funclet`, no `parent=` |

Each currently holds its name alone, so neither blocks anything today. But an
unscoped row is global: the first worker who needs that label number in another
TU is refused, and before `e0d4d5ee95c` would have been told one of the two rows
must be wrong. Giving them notes means asserting a parent I have not proven, so
they are reported rather than edited -- `$L3985` in particular is a matched
compiler-label row carrying no parentage evidence at all.

## `hatch_counters`: nine of eleven are one shape, and three are already closed

The open `hatch_counters` records are a consumer rebound from a wrong or
undefined spelling to the address's ledger owner. The file's count falls --
9→2 and 7→2 for the LANAPI pair, 12→6 for ColdGlobalDwordGetters -- but the
register keys `address_global` per **name**, so the owner's key rises and the
commit is refused.

Rule 10 exists to trade exactly that, and spends only a spelling
`reverse/data_ledger.csv` records in its `names` column at that address. That
column is empty for **33,157 of 34,425 rows**, so `ledger_respellings()` finds
just **6 owners** image-wide. Checked one by one:

| record | token | rule 10 supply |
| --- | --- | --- |
| `g_Va00E03314` | `g_Va00A03314` | **mapped** -- obstacle gone |
| `g_Va00E04450/E04904/E046B4` | `g_Va00A04450` … | **mapped** -- obstacle gone |
| LANAPI pair | `g_Va00A03354` | moot: `0x00A03354` is now `?s_instance@AptLanLobby@@0PAV1@A`, a real name, so there is no `address_global` key left to grow |
| token parsers | `g_Va00DC85C4Names` | none: `names` empty |
| AsciiString fix | `g_Va00E063D4` | none: `names` empty |
| rule 10 / C linkage | `g_Rva0112A210Fold` | none: `names` empty |

So three are stale and the rest need one ledger edit each, not a tool change.
The records instead propose widening `ADDR_GLOBAL` to bare `g_<hex>` or raising
the baseline; both raise an enforced total and neither is the route. One record
blames `_ledger_ident` for keeping a C name's leading underscore -- it strips
it, and `_g_Rva0112A210Fold` resolves to an owner, so that diagnosis is wrong
and the empty `names` column is the blocker there too.

`address_global_route()` (`77726e29b1d`) now says this at the refusal, on both
the `--update` path and the commit hook's. It admits nothing: `--report` is
identical and `--staged` stays silent on a clean tree. The remaining work is a
ledger edit per address, in its own commit, since the grant is read from `HEAD`.

## `tu_skeleton`: four are a stale index, and `link_census` is a different lane

Four of the seven open `tu_skeleton` records are one phantom: a unit a later
split or merge **deleted** is still in the census index, so the rows that moved
into the absorbing TU read as duplicates of it, and a unit added since is
missing as a provider ("no longer defines"). Each names an index commit older
than the split it tripped over. Against the live tree:

| record | index it used | now |
| --- | --- | --- |
| `TerrainLogic.cpp` duplicate `?rva00282B26@…` | `12902e9e1b` | one row in TerrainLogic; `Rva00282B26.cpp` gone; **LINKS cleanly** |
| `ParticleSys.cpp`, three duplicates | `12902e9e1b` | one row each in ParticleSys; `Rva001F6492Chain.cpp` gone |
| `BoneFXDamage.cpp` lacks providers | `112a456a2c` | all three providers in the ledger |
| `PartitionManager` "no longer defines" | `3c963aae8f` | — |

The files were never wrong. `index_staleness()` (`c01385f21b7`) now reports how
many sources moved since the index commit, on stderr so a landing script's
verdict parsing is untouched; against `12902e9e1b` it reports 1,052. Two of the
four records' shas are not in this clone at all, and an index commit a checkout
lacks is deliberately left unjudged.

**`link_census`'s 12 are not this.** Eleven are COMDAT selection — `keep_rule`,
`comdat-loser`, `comdat_losers` — where several TUs emit a copy of the same
function and retail kept a different one, so the local copy "differs from the
first copy in link order". They turn on which TU retail compiled a copy from
and why MSVC 7.1 emitted an out-of-line body there (the `??1Rva006D07E0Key`
cluster alone holds out seven Apt units, four of them with no other blocker).
That is linker semantics against retail evidence, and the rule decides what
counts as LINKED, so it is not a tooling-seat message fix and is left to the
link lane. The twelfth is the hard-coded-image-address heuristic firing on
`0x7F7FFF`, a pixel colour constant, which is its own small question.

## `name_lane` and `vtable_bridge`: 12 of 13 are fixed already

Neither lane needed a tool change. What they needed was someone to check.

**`name_lane`, 9 of 10 stale.** Four records are a proposal refused for a name
another *class* in the same file uses (`Rva006F7600::get` against
`Rva006F7540::get`, `ArmyDetailsPanelImpl::IsSelected` against
`Rva005E3B1A::IsSelected`, and a `clear` against another placeholder's scope).
`Lane.problem()` now replaces its caller's file-wide word set with the
scope-aware `collision_words()` for every `member` and `function` proposal, and
the submit path's `taken` set is keyed `(scope, name)`. Both landed in
`f37cb996139` on **2026-10-30**, a week after the records
(`codex8-20261023-225509-*`). Checked on the mechanism, not just the date: with
two classes in one text, the other class's `get` is absent from the proposing
class's collision set while a same-class `m_n` still blocks.

Three more are superseded by the fourth, which records its own repair -- direct
`typedef struct`/`class` aliases are recognised (`record_typedef_names`), so the
`ListboxData` header check went false→true. And `Lane.named_rvas()` now withholds
an RVA only through `rename.wb_lead_names()`, whose docstring states the rule the
record asked for ("most rows pair a body and name nothing"), since `b6a20d351df`.

The one that stands: `rename.py --evidence agree:<id>` used directly does not
check that the record's source still matches its votes' fingerprints, though
`apply` does (`fresh_voters`). That is `rename.py`'s, and `data_rows.py
--admit-agreed` skips it by design, so it needs that lane's judgement.

**`vtable_bridge`, 3 of 8 stale, and a handoff that cost me the detour.** The
weak `??_E` cluster was proposed in
`reverse/attempt_support/vtable-bridge-weak-deleting-dtor-20261108/`, headed
"proposed tooling fix, **not landed**" because the tool was claimed. The seat
holding it landed the fix the same day (`b9aeebea15a`), in a stronger form than
the patch: `slot_matches()` resolves a weak slot through `weak_resolutions()` and
*also* requires that copy's own weak record to name the same default. All three
regression tests the handoff specified exist, plus a fourth; 112 pass. I read
the heading as current and claimed the tool before reading the history. The
heading is now corrected, which is the whole fix.

Left for the link lane: the twin/alignment records (`align1` vs `align16`), the
vbtable positive-slot selector (its checker was held), the RTTI-prefixed
one-slot `_com_error` table, and the wide `basic_ifstream` slot 0, which looks
like the same weak-`??_E` mechanism from the real link's side but was not
re-measured here.

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

**11 other test files carried the same unguarded `_load`**, all now guarded:
`test_gen_tinst`, `test_gen_uw_shapes`, `test_gen_uw_transaction`,
`test_inventory`, `test_land_supersede`, `test_ledger_guards`, `test_pin_audit`,
`test_pin_consistency`, `test_red_rows`, `test_wb_queue_hooks`,
`test_zh_packet_metadata`.

An earlier revision of this note put that at 19, counting by `rg "if name in
sys.modules"`. Six files -- `test_dump_predicate`, `test_merge_cluster`,
`test_ledger_terminators`, `test_readability_metric`, `test_scan_population`,
`test_tu_structure` -- were already guarded in the other idiom (`if name not in
sys.modules:` around the load, returning `sys.modules[name]`), and
`test_gen_getters` loads `gen_small.py` under the distinct name
`gen_small_getter_test`, so it never touches the shared entry. Both forms are
safe; only the count was wrong.

Three of the eleven clobbered `build`, which 25 test files import normally --
the same exposure that caused the 8. The three `_load` calls that happen inside
a test rather than at import were checked before guarding: `bfme1_sweep`,
`zh_sweep` and `permute` all do `import wb_context` and resolve its attributes
at call time, so the `leads` fixture's monkeypatch still reaches them without a
fresh module, and `test_ledger_terminators:259` only asserts identity.

I did not run the whole 321-file suite; the 31-file subset above is every test
importing `add_match`, `gen_uw` or `ledger_io`. After the three fixes it is
**4 failed, 1757 passed, 4 skipped**, down from 15 failed.

## 2026-11-10: the triage question has a blind spot, and the age gap is real

Two corrections to the method above, both found while clearing the
`vtable_bridge` cluster.

### It only ever asked `functions.csv`

"Does the name the record wanted now own that address?" is read against
`reverse/functions.csv` alone. A false reject whose subject is a **data** row --
a vtable, a virtual-base table, a static, a string -- is rowed in
`reverse/data_ledger.csv` or `reverse/data_rows.csv`, so the question can never
resolve and the record is scored open whatever the truth.

Re-asking it against both data ledgers closes **17** of the 403 that read as
open, and finds 50 more sitting at a real data address under a different name
(a rename to judge, not a refusal to reproduce). It closed 27 of 439 before the
void correction below retired the rest. By check:

| check | closed by the data ledger |
| --- | ---: |
| `data_rows` (+ `data_rows.py`, `.verify_row`) | 10 |
| `vtable_bridge` (+ `.is_table_row`) | 9 |
| `link_debt.staged` | 2 |
| `data`, `data_check`, `rename.py`, `as`, `clearance` | 6 |

Both scripts are now in the repo, which they were not before -- this note's
whole method lived in one seat's scratchpad. Run them in order from anywhere:

    python3 reverse/attempt_support/fr_open.py     # writes fr_open.json beside itself
    python3 reverse/attempt_support/fr_data.py     # re-asks the open ones of the data ledgers

The two `.json` files they write are working output, not evidence; delete them
when done.

### It counted retractions as records, and retracted records as open

`void` is re_log's retraction: it deletes every EARLIER row at exactly its
(symbol, rva), so a false reject a later void answered is no longer a record of
anything. The triage never consulted it, and got this wrong twice:

- **45 standing records were already retracted** -- 15 by the vtable_bridge and
  pin_admission clearance below, and **30 by other workers**, going back far
  enough that nobody has re-measured since.
- **15 `void` rows were counted as false rejects themselves**, because the
  retraction prose names one ("Retract duplicate append; consolidate to one
  false-reject finding below").

The direction matters and is easy to get backwards: a void only retracts what
precedes it. 47 records sit at a boundary that holds an EARLIER void, and all 47
still stand -- several are the consolidated finding the void was clearing room
for, appended on the very next line.

Corrected, the pile is **926 records, 881 standing, 403 open** -- not 941 and
439. Of those 403, 17 more close against the data ledgers above.

### It asked only whether the WANTED name owns the address

The question sorts by the record's own spelling, so it misses every case where
the work landed under a different one -- and that is the common case. A
placeholder gets renamed (`?rva004071D7@...` -> `??0BfmeHeroElement005C39DE@...`,
`?d_0030bea2@@YAXXZ` -> `?slot1@Rva0030C1FCOwner@@...`), a `$L` label is
renumbered, an alias is adopted. The record's name never owns anything again.

re_log already tracks the standing verdict per (symbol, rva), and a resolution
there -- `converted`, `solved`, `mapped`, `landed` -- answers the record whatever
name did it. Asking it retires **301 more**, of which 223 the ledger question
agreed were closed anyway and **78 it did not see**:

- 63 are a placeholder renamed, `matched` in the ledger at that address;
- 15 are `tool:`/`ms-headers:` pseudo-symbols at 0x0 -- records about a tool
  rather than an address, each already marked `solved` by whoever fixed it.

Order is respected, so this does not over-close: `standing_status` returns the
LATEST verdict, so a resolution followed by a fresh false reject still reads as
blocked.

**Corrected totals: 931 records, 886 standing after voids, 585 after
resolutions, 330 open.** Against 941/439 before. `check_csv` alone goes from 17
open to 6.

### `$L` records are usually right about the body and wrong about the number

Seven of the open `check_csv` records are one shape: a TU-local label collision
where the address is now matched by a correctly-scoped label from *exactly the
parent the record names*, under a different number.

| record | wanted | the ledger has | parent |
| --- | --- | --- | --- |
| 50380 | `$L2598` @ 0x7A9D4F | `$L2597` | `?objectMemberLookup@AptSound@@…` |
| 50381 | `$L2599` @ 0x7A9D40 | `$L2598` | same |
| 50991 | `$L7227` @ 0x7776B1 | `$L7259` | `??1AptPalantir@@UAE@XZ` |
| 53241, 53244 | `$L1697` @ 0x77F22A | `$L1729` | ArmyPlacer `PlaceObjects`, guard-bit-0 |
| 53242, 53245 | `$L1698` @ 0x77F237 | `$L1730` | same, guard-bit-1 |

Label numbering is per-TU and shifts with everything the compiler emitted
before, so a worker's guess at the number is the fragile part; the parent and
the body are what identify the funclet. All five boundaries are recorded
`mapped`, not `void`: two of them carry an earlier `landed` row (L53238,
L53239) that a void would delete along with the deferral. **Check what else
sits at a boundary before voting it.**

### A record is stale the moment the fix lands, and nobody goes back

The whole `vtable_bridge` cluster -- 9 of its 11 records -- names a defect that
was repaired **after the record was written**, by someone who never knew the
record existed:

| records | named blocker | repaired at |
| --- | --- | --- |
| 101661, 101711, 101712, 102083 | `is_table_row` reads `??_8` base offsets as function slots | `0e11bbf733d` 11-08 |
| 101706, 101707, 101710 | a weak `??_E` slot must resolve to its rowed `??_G` default | `b9aeebea15a` 11-08 |
| 101617, 102301, 101643, 101645 | the LINK-619 `/O1`-vs-`/O2` alignment wall, "deferred until the position-observation proof lands" | `88c4a34da58` **11-10, that morning** |

All nine are retracted with `void` at `f067741fcf9`. Two stay open: 101567 (the
real link emits `??_E` for wide `basic_ifstream` where a local build emits only
`??_G`) and 102511 (RTTI-prefixed LARGEST selection for `_com_error`).

Note the shape of the evidence. Three of the four `??_8` records say so
themselves -- "34 vbtable-only rows share selector error" -- and the ledger holds
exactly 34, every one of which `is_table_row` now excludes. **That check needed
no build to replay**: it reads `data_ledger.csv` and nothing else. The same is
true of `pin_admission.is_placeholder`, whose 6 records all name the `b_`/`j_`
gap-thunk family that `SELF_ADDRESS_THUNK_RE` now covers; all six addresses
return `True` in the spelling `gen_small.thunk_symbol` actually mints.

So the cheap first move on any record is not "reproduce the refusal" but **call
the named predicate**. A large share of these checks are pure over a committed
CSV, and the fleet's own `./build.sh` is the expensive part of reproducing.

One trap while doing that: the three `?j_` records above are written with
UPPERCASE hex (`?j_000066EB@@YAXXZ`). `SELF_ADDRESS_THUNK_RE` is lowercase-only,
which looks like a case-sensitivity bug and is not -- `thunk_symbol` formats
`{rva:08x}`, and all 264 such names in the ledgers are lowercase. The uppercase
is the record's own transcription. Widening the pattern would admit placeholder
spellings the generator never mints, which weakens the predicate; don't.

## What the remaining open lane actually is

After the three corrections above the pile is **324 open**. Splitting it by the
state of the ledger at each record's address changes what the lane looks like:

| state at the record's RVA | records |
| --- | ---: |
| matched, but every name there is still a placeholder | **190** |
| matched under a real name | 77 |
| no ledger row at the address | 57 |

The 190 are the lane's real shape and they are **not "the check is broken and
nothing can land"** -- the body landed and byte-verified. What is unresolved is
the *name*. 145 of them are `add_match`, where a worker proposed a real name and
was refused. So the question for each is narrow: is a check still refusing this
rename, or did the worker simply stop? Only the first is a tooling record.

The 77 matched under a real name are the best remaining hunting ground, since
the naming work visibly completed after the record was written: 19 `rename.py`,
8 `header_adopt_lane`, 4 `classification`, 3 each `pin_admission` and
`rename.run_batch`. Those are the ones to read next.

The 57 with no row are mostly `tool:` pseudo-symbols at 0x0 -- records about a
tool, where the only evidence is the tool's own code.

**A caution that cost real time.** "The address is matched" is not closure: a
row can be `matched` and still carry a placeholder name (`Rva0012345`,
`uw_0076fa6b`). 267 of the 324 are matched under *some* name, which looks like a
backlog that has almost entirely evaporated; filtering to a real name leaves 77.
Do not take the first number.

## How to date a record without `git blame`

Every "is this stale?" question needs the record's age against its fix, and
`git blame -L <n>,<n> -- reverse/re_attempts.log` on a 100k-line append-only log
is slow enough to time out. It is also the wrong question. The cheap form asks
whether the record was already in the file when the fix landed:

    git grep -c '<distinctive text from the record>' <fix-sha>^ -- reverse/re_attempts.log

A non-zero count means the record predates the fix, which is all "stale" means.
It returns in about a second. `git log -S` over the log is worse than blame --
never run it unscoped.

To find the fix itself, `git log -S'<a line of the rule>' -- tools/<file>.py` is
fast, because it is scoped to one small file.

## A boundary is only safe to close when EVERY row on it is answered

Three records reported closed on 2026-11-11 were deliberately left standing:
the `tu-merge` file-level boundaries for TerrainLogic.cpp (98570),
ParticleSys.cpp (98571) and Player.cpp (102310). Each carries a LATER `blocked`
row that is a different, live finding. 100096 is explicit about it:

> The 98571 link-guard false reject **has cleared** … what remains is LINK-155's
> view wall: C2011 FXParticleSystem::ParticleSystemInfo … redefinitions

So the false reject is genuinely answered and the boundary is not. `void`
deletes every earlier row there and a resolution supersedes every row there, so
either verdict would bury the live wall. File-level `tu-merge:<path>` symbols
accumulate rows this way and are the main place this bites; an address boundary
usually holds one record.

The counterpart trap is the reverse: 87825/92513, 87826/92514, 87828/92515 and
94614/98203 are PAIRS at one boundary, both rows answered by the same fix, and
there voting the boundary is right. Read the neighbours either way.

`fr_open.py` now does that lookup for you. Every open record in `fr_open.json`
carries `boundary_rows` (every other row at its exact (symbol, rva), with line
and status), a `boundary_safe_to_vote` flag, and a `boundary_warning` naming the
later lines when there are any. **72 of the 317 open records -- 23% -- carry a
later row**, so this is not a rare corner. It is a prompt to read, not a
verdict: a later row answered by the same fix is fine to vote through, which is
how the four pairs above were closed.
