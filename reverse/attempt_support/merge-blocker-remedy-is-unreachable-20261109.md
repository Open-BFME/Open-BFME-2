# The pre-compile merge blocker tells you to split, and 1 of 24 can be split

> **Corrected after first publication (`a3623130cb1`).** The screen below had a
> wall of its own that was wrong: it treated a destination TU with no file in the
> tree as unusable. `--split` composes a new TU file (`docs/consolidation.md`,
> the split lane, step 5), so that is no obstacle. The mistake excluded five
> cases, and one of them carved and landed -- `GameModePreferences.cpp ->
> LanLobbyMenu.cpp`, 6 rows, 57/57 matched (`8eb38889d50`). The corrected
> figures run through this note: **24 pairs attempted, 1 carvable**, and the
> "destination unusable" bucket is 7 TUs / 118 donor files, not 12 / 149. Every
> other conclusion stands, and the dominant wall got stronger: it now has a case
> with an *approved* destination (`mesh.cpp`, by=S).

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
| 7 | 118 | destination is itself blocked |
| 5 | 31 | destination approved, no file in the tree -- **attemptable after all** |
| 2 | 20 | merge-shaped: nothing would remain, so `--merge` is the call |
| **80** | **1,513** | |

The fourth row is the correction noted at the top: first published as part of a
12-TU "unusable" bucket. A destination with no file is composed by the split, so
those five belong with the attemptable ones, giving **24 pairs over 21 TUs**.

The 47 are the largest group and they are **not a split lane**: AGENTS.md allows
a row to move only into the address's *approved* unit, and a `proposed`
destination is not approval. 28 of them (601 donor files) hang on exactly one
such row, headed by `Object.cpp` (208 donors, `?GetSnapshotName@ObjectRecoveryHelper@@MBEPBDXZ`,
`by=N`), `LivingWorldLogic.cpp` (83) and `Eva.cpp` (43). Those belong to
`next_work.py --tier tu-approval` / `--tier tu-evidence`, not here. The 125
not-approved blocking rows are `proposed` by N (72), C (22), U (16), K (8), S (1)
and blank (6).

## 23 of the 24 attemptable cases refuse, in six different ways

`--split FILE --for TU --dry-run` on every pair (some TUs have two or more
destinations, so 24 pairs over 21 TUs; `NetCommandMsg.cpp` and `vertmaterial.cpp`
were held by other seats and `AptCIH.cpp` is blocked without any foreign row,
which is a separate question). A dry run costs about three seconds and writes
nothing.

| pairs | wall |
| ---: | --- |
| 14 | `no definition spells its name` -- **the remedy cannot be performed** |
| 3 | the destination's private class views reject the carved body |
| 3 | the residual loses matched rows (flag region or shared helper) |
| 1 | the residual no longer compiles: the carved body's visibility is a codegen lever |
| 1 | the unit-key carry: a per-TU global both files define |
| 1 | the split link guard: the carve would duplicate two file-scope globals |
| 1 | merge-shaped after all (`every row is this TU's: use --merge`) |
| **1** | **carved, verified and landed** (`8eb38889d50`) |

Worth separating out: in the three view-wall cases, the unit-key case and the
link-guard case the carve itself is **sound** -- the report says `alone: N/N
carved rows match beside the TU under its flags`, `refused_rows: {}` -- and the
refusal comes from the destination or a register, not from the carve.

The one that landed is `GameModePreferences.cpp -> LanLobbyMenu.cpp`:
`LANPreferences::loadFromIniFile` (`by=S`) and `LANPreferences::LANPreferences`
(`by=Z`, Zero Hour's own definition site) with their four EH funclets riding
along, into a TU file the split composed. `./build.sh` on both files gave 57/57
matched. Note what made it work and nothing else did: the blocking rows are
**hand-written bodies in the wrong file**, with the two strongest anchors in the
map behind their destination. That is the shape of a real split.

The one new link-guard case, `INIWater.cpp -> WaterTransparencySetting.cpp`, is
worth reading for its message: the terminal line says `no verified merge of two
or more donors`, which is the generic text printed after the only donor was
rejected. The actual reason is in the report's `rejected` map -- "a link-clean
original would stop linking; new duplicates: `?theWaterSetBlockParse@@3UBlockParse@@A`"
-- so do not take a split's last line as its reason.

## The dominant wall: the blocker asks for something structurally impossible

For 14 of the 24 pairs the blocking row has no definition span in the file, so
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
| 0x00355C2F | `VisRasterizerClass::Enable_Two_Sided_Rendering` | mesh.cpp |
| 0x00035620 | `ScopedCriticalSection::Lock` | NameKeyGenerator.cpp |
| 0x00035640 | `ScopedCriticalSection::Unlock` | NameKeyGenerator.cpp |

The last three came from the five cases the first screen wrongly excluded, and
two of them answer an obvious objection -- that the real problem is only the
map's `proposed` confidence. **Their destinations are approved** (`visrasterizer.cpp`
by=S, `scopedcriticalsection.cpp` by=N), and they still cannot be carved. So the
wall is independent of approval.

`mesh.cpp` shows the mechanism being used on purpose. It holds
`_bfmeVisTwoSidedInlineAnchor`, carrying an `absent-from-retail` marker, whose
entire body is two calls:

```cpp
v->Enable_Two_Sided_Rendering(b);
idb->Enable_Two_Sided_Rendering(b);
```

That helper exists to make the compiler emit those inline bodies into this
object, which is how the tree reproduces retail's COMDAT placement. The row is in
`mesh.cpp` by construction; the approved TU, `visrasterizer.cpp`, is where the
*source* is written. "Split it first" asks for a body to be moved out of a file
that never contained one. `NameKeyGenerator.cpp` is the ordinary version of the
same thing: it names `ScopedCriticalSection` twice, both times as a local RAII
object, and the inline `Lock`/`Unlock` are emitted because of that.

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
  the refusal's stated remedy is unreachable for 14 of 24, so the TUs are
  deadlocked rather than queued.
- **Not a false reject**, for any of the 14. A false reject needs work shown to
  be correct, and a merge that never compiles cannot be shown correct. They are
  recorded as `blocked` with the per-row mechanism.
- **Not that `emission_held` should be widened.** That would change which rows a
  merge may absorb; two of the fourteen sit inside a documented decision against
  it, and the remaining question (is contiguity valid evidence for a COMDAT many
  objects emit?) is upstream in `tu_map`, where it would move approvals.
- **Not that the 17 CARVABLE TUs will merge once approved.** `identify()` finding
  one definition span is what the carve needs to *start*; the `ArmyDefinition.cpp`
  case here carved both rows cleanly and was still refused because the residual
  lost matched rows. CARVABLE means attemptable, not landable.
- **Not a measurement of any other tool revision.** Every figure here is
  `592396ae2c7`. The last note had to retract a conclusion because a tool changed
  under it hours later.

## What to do instead

The 47 `proposed`-destination TUs (1,013 donor files) are the biggest prize and
are **TU-approval work**, served by `next_work.py --tier tu-approval` and
`--tier tu-evidence`. But approval is only worth paying for where the blocking
row has a body a carve could move. Running the carve's own `identify()` over
every one of those 125 blocking rows splits the group cleanly:

| TUs | donor files | after approval |
| ---: | ---: | --- |
| 17 | 615 | **CARVABLE** -- a definition in the file spells the row, so approval buys an attemptable split |
| 25 | 324 | **NO BODY** -- the same wall as above; no approval can help |
| 5 | 74 | mixed: some rows carvable, some not |

So the merge-unblocking value of the tu-approval lane concentrates in **17 TUs
holding 615 donor files**, led by `Object.cpp` (208 donors, one row,
`?GetSnapshotName@ObjectRecoveryHelper@@MBEPBDXZ`), `AIStates.cpp` (109),
`LivingWorldLogic.cpp` (83), `ConnectionManager.cpp` (42) and
`PersistentStorageThread.cpp` (32). Approving a row in the 25 NO BODY TUs is
still worth doing for TU-APPROVED, but it will not move a merge.

Every one of the 29 destination TUs behind those 17 has **no file in the tree**,
so each needs its own anchor before `by=N` can be promoted. Of the banked
evidence: `siegeenginecontain.cpp` has 4 WorldBuilder leads,
`livingworldregionmanager.cpp` has 18, and three destinations appear in the
2026-11-04 missed-`__FILE__`-xref scan. All of that is donor or target facts that
approve nothing on their own.

Two smaller notes:

- Of the walls that are not structural, the one closest to landing is
  `DozerAIUpdate.cpp` (15 donors): everything passes except rule 2 above.
- Do not spend further dry runs on the 14. They are recorded in
  `reverse/re_attempts.log` with the reason, and the reason will not change until
  a predicate does.

## Method

- `tu_skeleton.donors()`/`tu_path()` for the population, never a reimplementation.
- `reverse/tu_map.csv` is stale; every figure uses the map `tu_skeleton` rebuilds
  in memory, as `--queue` warns. A count taken from the committed CSV is wrong.
- Confidence read per blocking RVA from the rebuilt map, because "approved"
  is what AGENTS.md requires for a move and 125 of the blocking rows are not.
- 24 dry runs, logs kept per pair; each wall then read back against the source
  file, which is what caught the two sub-mechanisms, the `ArrowStormUpdate`
  codegen lever and `mesh.cpp`'s inline anchor.
- Two hypotheses were tested and dropped: that these rows were missing a
  `homeless()` classification (`homeless()` returns False for any row that has a
  TU, by design), and that `unit_key_carry` had an oversight (it has a test and a
  decision label).
- One of my own screen's walls was wrong and cost the better part of the lane's
  only landing. Treating a destination with no file in the tree as unusable
  seemed obviously safe and was never checked against the split lane's own
  documentation, which says in step 5 that it composes a new TU file. The habit
  that keeps catching errors here is the same one each time: **run the lane's own
  predicate instead of a plausible stand-in** -- `donors()` not a hand-rolled
  mixed test, `identify()` not `spells_definition`, and the documented behaviour
  of `--split` not an assumption about it.
