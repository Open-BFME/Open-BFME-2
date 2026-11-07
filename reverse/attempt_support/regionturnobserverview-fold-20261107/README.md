# Folding Rva0020E346 into RegionTurnObserverView: refused on a third table name (2026-11-07)

The previous note found that three LivingWorld contracts record their base at offset 4 as
the placeholder `Rva0020E346`, and that naming it would give all three a real base. This
pursued that and reached a precise blocker. Nothing was changed: the attempt was a
`--dry-run`, no source, ledger, contract or header was touched, and no claim was taken.

## First, a correction: the two table addresses were never in conflict

The previous note flagged, as unreconciled, that a landed row wrote the build-plot
secondary table as `C63528` while the contract recorded `0x863528`. They differ by
`0x400000` - the PE image base - and both forms are real. The data ledger settles it in one
row, carrying the address and the alias together:

```
0x00862A20,8,.rdata,vtable,??_7RegionTurnObserverView@@6B@,...,_vtbl_00C62A20,1,4
```

The source is explicit too: `RvaSmallVtableCtors.cpp` comments the constructor as
"vtable **VA** 0x00c62a20". Notes use virtual addresses, the ledger and contracts use RVAs.
There was no discrepancy to reconcile, and the earlier note should be read with that
correction.

## The identity holds, from three directions

- The data ledger names table `0x00862A20` `??_7RegionTurnObserverView@@6B@`.
- `Rva0020E346`'s single row - a 9-byte constructor at `0x0020E346` - stores that table,
  and its own note says "owner unrecovered so address-derived".
- `Rva003FA62B`'s contract already records `bases: ["RegionTurnObserverView"]` with vslots
  `{0: BeginTurn(int,int), 1: EndTurn(int,int)}`, decided by retail-vtable.

And the fold would add rather than duplicate: `RegionTurnObserverView` has rows for
BeginTurn, OnTurnEnding and a non-virtual destructor (`??1RegionTurnObserverView@@QAE@XZ`),
but **no constructor row at all**. The 9 bytes would supply the one it lacks.

## What refused it, and why that is right

`rename.py class --fold Rva0020E346 --into RegionTurnObserverView --dry-run`:

```
rename: refused: retail vftable 0x00C62A20 is also named for Rva003FA62BBase,
Rva005D0643B3 (data_ledger.csv): a third name for the table
```

That is the documented rule working as intended - retail folds identical vftables, so a
table carrying three names may be an ICF fold of distinct classes, and folding blindly
would merge unrelated ones.

## Why the blocker is removable, and the next step

The two extra names are not classes. Neither `Rva003FA62BBase` nor `Rva005D0643B3` has a
single row in `reverse/functions.csv`, and neither has a contract. They exist only in the
alias list of that one data-ledger row. `Rva003FA62BBase` is plainly the old placeholder
spelling of the base subobject in `Rva003FA62B`, whose contract has already resolved that
base to RegionTurnObserverView.

So this is one class with two stale aliases, not three classes sharing a folded table. The
step that unblocks the fold is retiring those two aliases from the table's row through the
supported data-ledger path - not by hand - after which the table has one name and the fold
becomes admissible. That would give RegionTurnObserverView its missing constructor and
three LivingWorld contracts a named base.

One thing for whoever does it: the placeholder declares `virtual ~Rva0020E346()` while the
canonical header gives RegionTurnObserverView two virtual callbacks and a *non-virtual*
destructor, and its own comment says native `C62A20` is "exactly two three-byte RET8
callbacks, without a virtual destructor". The shapes differ, so the fold's destructor
handling matters here; `--access` exists for respelling that family, and the byte gate is
the judge.

## Tracing the unblock to its real owner

The two extra names are not an editable field. `reverse/data_ledger.csv` is a protected
path with a dedicated tool, and that tool only *derives* it - `data_ledger.py` takes
`--check` and `--out` and nothing else, producing "one row per retail global the matched
code reaches". The alias list is computed, so the stale aliases are a symptom of what the
code spells, not a line to retire.

And the code no longer spells them: **neither `Rva003FA62BBase` nor `Rva005D0643B3` appears
anywhere under `Code/`.** They have no rows in `reverse/functions.csv` and no contracts
either. The committed ledger is simply behind the sources, which its own check confirms:

```
data_ledger: 17101 matched source(s) have no object; build first
data_ledger: reverse/data_ledger.csv is stale; run python3 tools/data_ledger.py
```

So the fold's blocker clears by regenerating the derived ledger - but **not from here, and
not now.** The same check says the derivation is missing objects for 17,101 matched
sources, so regenerating in this worktree would compute the ledger from incomplete data and
publish a worse file than the stale one. That needs a tree with the objects built, and the
file is protected, so it belongs to whoever runs the full build rather than to a lane seat.

The chain, end to end, for whoever picks it up: regenerate the data ledger from a fully
built tree; the two stale aliases drop because nothing spells them; table `0x00862A20` is
then named only `??_7RegionTurnObserverView@@6B@`; `rename.py class --fold Rva0020E346
--into RegionTurnObserverView` becomes admissible; RegionTurnObserverView gains the
constructor it lacks; and LivingWorldArmy, LivingWorldBuilding and LivingWorldBuildPlot get
a named base instead of a placeholder. Every step after the regeneration is a supported
tool call with the byte gate as judge.
