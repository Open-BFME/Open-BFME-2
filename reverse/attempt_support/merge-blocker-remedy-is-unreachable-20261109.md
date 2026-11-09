# The pre-compile merge blocker tells you to split, and 0 of 19 can be split

Measured at `592396ae2c7`, 2026-11-09. This finishes the question
`merge-queue-hides-81-tus-behind-one-row-20261109.md` opened at `1650aa94c47`
and corrects that note's framing: it treated the whole hidden population as a
split lane. Two thirds of it is not split work at all, and of the part that is,
nothing can be carved.

## The blocker

`tu_skeleton.merge()` (`tools/tu_skeleton.py:2465`) refuses before any donor is
weighed:

```python
if tu in mixed or ((ROOT / tu).exists() and tu not in don):
    report["blocked"] = "TU path exists and holds rows of another TU (split it first)"
    return report
```

Because it returns before ranking, such a TU appears in no `--queue`, no
`--merge-all` ordering and no `decisions.json`. The refusal names one remedy:
split the file first.

## The population is stable, so nobody is clearing it

Re-measured with the tool's own predicates (`donors()`, `tu_path()`; a
hand-rolled version of this test over-reported by 38% last time and is not used):

| | `1650aa94c47` | `592396ae2c7` (178 commits later) |
| --- | ---: | ---: |
| TUs the map names, file on disk | 1,313 | 1,313 |
| blocked before any compile | 138 | 139 |
| of those, holding 2+ donors | 81 | 80 |
| donor files behind them | 1,586 | 1,513 |

The one TU that left the list is `HordeContain.cpp`, cleared by the split landed
at `f8c4581efaf`; `HordeSiegeEngineContain.cpp` (27 donors) entered it. The
population is otherwise unchanged across 178 commits, so no other lane is
touching it.

## Two thirds of it was never split work

Screening all 80 against the three walls that stopped four attempts on
2026-11-09, before paying for any compile:

| TUs | donor files | verdict |
| ---: | ---: | --- |
| 47 | 1,013 | the blocking row's destination is only `proposed` |
| 19 | 331 | attemptable |
| 12 | 149 | destination is itself blocked, or has no file in the tree |
| 2 | 20 | merge-shaped: nothing would remain, so `--merge` is the call |
| **80** | **1,513** | |

The 47 are the largest group and they are **not a split lane**: AGENTS.md allows
a row to move only into the address's *approved* unit, and a `proposed`
destination is not approval. 28 of them (601 donor files) hang on exactly one
such row, headed by `Object.cpp` (208 donors, `?GetSnapshotName@ObjectRecoveryHelper@@MBEPBDXZ`,
`by=N`), `LivingWorldLogic.cpp` (83) and `Eva.cpp` (43). Those belong to
`next_work.py --tier tu-approval` / `--tier tu-evidence`, not here. The 125
not-approved blocking rows are `proposed` by N (72), C (22), U (16), K (8), S (1)
and blank (6).

## All 19 attemptable cases refuse, in five different ways

`--split FILE --for TU --dry-run` on every pair (two TUs have two destinations
each, so 19 pairs over 16 TUs; `NetCommandMsg.cpp` and `vertmaterial.cpp` were
held by other seats and `AptCIH.cpp` is blocked without any foreign row, which is
a separate question). A dry run costs about three seconds and writes nothing.

| pairs | wall |
| ---: | --- |
| 11 | `no definition spells its name` -- **the remedy cannot be performed** |
| 3 | the destination's private class views reject the carved body |
| 2 | the residual loses matched rows (flag region or shared helper) |
| 1 | the residual no longer compiles: the carved body's visibility is a codegen lever |
| 1 | the unit-key carry: a per-TU global both files define |
| 1 | merge-shaped after all (`every row is this TU's: use --merge`) |

Nothing carved. Worth separating out: in the three view-wall cases and the
unit-key case the carve itself is **sound** -- the report says `alone: N/N carved
rows match beside the TU under its flags`, `refused_rows: {}` -- and the refusal
comes from the destination or a register, not from the carve.

## The dominant wall: the blocker asks for something structurally impossible

For 11 of the 19 pairs the blocking row has no definition span in the file, so
`identify()` has nothing to carve and **no split can ever move it**. The row is a
compiler-emitted COMDAT: retail's linker kept one copy of a body many objects
emit, inside the contribution of the object it took it from, and the map's
contiguity then reads that object's neighbourhood as another TU. Most of these
addresses are ICF folds carrying many ledger rows (0x002888D4 has 13 across as
many files, 0x0031B031 has 4, 0x002174A4 has 6).

Two sub-mechanisms, separated by reading each file:

**Forced in by an explicit instantiation (6 rows).** The file carries a
`template X<Y>::m(...);` line and no body. That line has no body span, so the
carve sees nothing to move.

| rva | row | file | instantiation lines |
| --- | --- | --- | ---: |
| 0x0031B031 | `__copy<ScienceType*>` | ThingTemplate.cpp | 1 |
| 0x002174A4 | `AptRef<AptCommandMap>::operator=` | AptPlayer.cpp | 1 |
| 0x001FF5AC | `_Construct<pair<const unsigned,bool>>` | FileSystem.cpp | 1 |
| 0x00469142 | `pair<const unsigned,bool>::pair` | FileSystem.cpp | 1 |
| 0x001894F0 | `DynamicVectorClass<TextureClass*>::ctor` | matinfo.cpp | 3 |
| 0x001814D0 | `__uninitialized_fill_n<AngleFXInfo*>` | StructureToppleUpdate.cpp | 1 |

**Merely used (5 rows).** No mention of the member at all; the body is emitted
from a header because the file uses the type. `dx8caps.cpp` names `StringClass`
nine times and defines none of its members; `Armor.cpp` does not contain the
string `_M_find`.

| rva | row | file |
| --- | --- | --- |
| 0x00129C80 | `StringClass::operator+=` | dx8caps.cpp |
| 0x0036CC7A | `FileClass::Get_File_Handle` | W3DFileSystem.cpp |
| 0x002CF51B | `ModuleInfo::Nugget::~Nugget` | ThingTemplate.cpp |
| 0x0002BAF8 | `SaveDate::SaveDate` | GameState.cpp |
| 0x002888D4 | `hashtable<...ArmorTemplate>::_M_find` | Armor.cpp |

### Why `emission_held` does not already cover them

`emission_held` exists for exactly this class of row and its docstring states the
right principle -- "no source spells it, and any TU instantiating the template
emits the same bytes... it makes no file mixed, names no donor, blocks no merge
or split". It does not reach these rows because the merge blocker and the carve
rest on **two different predicates**:

- the carve uses `identify()`, strict: candidate definition spans whose head
  spells the row's name;
- `emission_held`'s last gate uses `spells_definition()`, deliberately biased to
  True -- `if owner is None: return True`, documented as "no proof of absence".

So for a non-template name (`StringClass::operator+=`, `FileClass::Get_File_Handle`,
`SaveDate::SaveDate`, `~Nugget`) `instance_owner()` returns None and
`spells_definition` can never return False, whatever `identify()` found. For a
template name it counts the explicit instantiation line as a real home, which is
defensible on its own terms -- the line does assert "emit it here" -- but leaves
the carve with nothing to move.

Measured per gate, for all 11: `spells_definition` is True for every one, and it
is the only gate that rejects five of them.

## Two deliberate rules, with their cost measured

Neither of these is reported as a defect. Both are recorded choices, and what
follows is only what they cost in this lane.

**1. `emission_held` excludes compiler-generated special members** on purpose:
"review of `bfb856bfbf`: a hand-written copy ctor can match the implicit one's
bytes exactly". That covers `SaveDate::SaveDate` and `~Nugget` above, so two of
the eleven are inside an explicit prior decision.

**2. The unit-key carry resolves keys by symbol name**, and
`tools/tests/test_tu_skeleton_split.py:1062` pins the behaviour with the comment
"Sol R1 S1: the residual is one more definer, never a tie-breaker". This is what
refuses `DozerAIUpdate.cpp -> WorkerAIUpdate.cpp`, the only pair whose carve,
link guard and both donors all passed:

- the register already holds a separate key per unit: `_DRAWABLE_FRAMES_PER_FLASH`
  at `0x00A038F4` -> DozerAIUpdate.cpp and at `0x00A03CAC` -> WorkerAIUpdate.cpp;
- the moved body, `WorkerAIUpdate::privateRepair`, does not reference the global;
- the residual still defines its own copy, so neither key needs to move.

The global comes from the shim `bfme2_drawable_flash` and the register keys it to
**259 sources**, so under this rule no carve between any two of those 259 files
can land. It is the widest shared key by two orders of magnitude (the next is
`_SPAWN_UPDATE_RATE`, 6 sources); 19 key names in all are held by more than one
source. Whether that cost is worth paying is a maintainer's call, not a seat's,
and the rule was not touched.

## What this does not claim

- **Not that the 80 merges would succeed.** The blocker returns before compiling,
  so nothing here shows what these TUs would do if they reached a verdict. They
  would still face the view wall, byte mismatches and the link guard, which
  stopped 132 of 134 donors in the last measured sample. The claim is only that
  the refusal's stated remedy is unreachable for 11 of 19, so the TUs are
  deadlocked rather than queued.
- **Not a false reject**, for any of the 11. A false reject needs work shown to
  be correct, and a merge that never compiles cannot be shown correct. They are
  recorded as `blocked` with the per-row mechanism.
- **Not that `emission_held` should be widened.** That would change which rows a
  merge may absorb; two of the eleven sit inside a documented decision against
  it, and the remaining question (is contiguity valid evidence for a COMDAT many
  objects emit?) is upstream in `tu_map`, where it would move approvals.
- **Not a measurement of any other tool revision.** Every figure here is
  `592396ae2c7`. The last note had to retract a conclusion because a tool changed
  under it hours later.

## What to do instead

- The 47 `proposed`-destination TUs (1,013 donor files) are the biggest prize and
  are **TU-approval work**, served by `next_work.py --tier tu-approval` and
  `--tier tu-evidence`. 28 of them need exactly one row approved. 84 of the 125
  blocking rows already carry a real name, which is what Z and S need.
- Of the four walls that are not structural, the one closest to landing is
  `DozerAIUpdate.cpp` (15 donors): everything passes except rule 2 above.
- Do not spend further dry runs on the 11. They are recorded in
  `reverse/re_attempts.log` with the reason, and the reason will not change until
  a predicate does.

## Method

- `tu_skeleton.donors()`/`tu_path()` for the population, never a reimplementation.
- `reverse/tu_map.csv` is stale; every figure uses the map `tu_skeleton` rebuilds
  in memory, as `--queue` warns. A count taken from the committed CSV is wrong.
- Confidence read per blocking RVA from the rebuilt map, because "approved"
  is what AGENTS.md requires for a move and 125 of the blocking rows are not.
- 19 dry runs, logs kept per pair; each wall then read back against the source
  file, which is what caught the two sub-mechanisms and the `ArrowStormUpdate`
  codegen lever.
- Two hypotheses were tested and dropped: that these rows were missing a
  `homeless()` classification (`homeless()` returns False for any row that has a
  TU, by design), and that `unit_key_carry` had an oversight (it has a test and a
  decision label).
