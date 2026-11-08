# Bulk adoption probing is not a lane: 10 passes from 445 units

Measured 2026-11-08 by running `header_adopt_lane.py adopt` (no `--apply`, so
nothing was written) over every live queue row of the chosen classes.

## The rate

| units probed | passed | rate | cohort |
| ---: | ---: | ---: | --- |
| 17 | 2 | 12% | `UpgradeMux` |
| 85 | 2 | 2.4% | the 195-row "contract has the field" re-run, 28 classes |
| 108 | 1 | 0.9% | `Drawable` |
| 82 | 0 | 0% | `Thing` |
| 81 | 1 | 1.2% | `AICommandInterface` |
| 72 | 4 | 5.6% | `Vector3` |
| **445** | **10** | **2.2%** | total |

Yesterday's sample of twelve declaration-only candidates gave one pass and I
recorded "about one in twelve" from it. Over 445 units the real rate is **one in
forty-five**, and twelve was far too small a sample to say anything. The earlier
figure should not be quoted.

## What that means for picking work

The header queue's live rows are not a bulk lane. `Thing` is the clean
demonstration: 82 units, 19 TUs of merge reach, the third-ranked blocker by
breadth -- and zero adoptions. Ranking by rows and reach
(`header-work-ranked-by-merges-20261108.md`) picks the classes where adoption
would be *worth* the most, which is not the same as where it will *work*, and
nothing measured so far predicts the latter.

Three things do move the needle, in descending order of measured size:

1. **The include walker**, 7.1% of all units probed, refused before any layout
   question (`header-lane-include-machinery-20261108.md`). Three toolchain
   headers account for all of it.
2. **Contract-to-header work** on the 195 group: the contract names the field,
   its offset and its size, and the compiled header does not spell it
   (`header-missing-field-rows-anatomised-20261108.md`).
3. **Probing**, at 2.2%.

A seat with a compile budget should spend it on (1) and (2) before (3).

## Probing makes the worktree transiently dirty

Worth knowing before running a sweep in a checkout you also commit from.
`try_units` writes each candidate's swapped text to the **real** source path,
compiles it, and restores the original in a `finally`. So while a cohort is in
flight the tree shows its units as modified with real diffs, and anything
needing a clean tree fails -- `push.py` stopped with
`cannot rebase: You have unstaged changes` listing 34 files mid-cohort. It is
transient and it restores, but:

- Do not commit or push while a probe sweep runs; wait for the cohort.
- A probe sweep in a shared checkout looks exactly like another worker's
  uncommitted work. Nothing should "clean up" those files.
- `--merge-all` cherry-picks onto the invoking checkout's branch, so a sweep
  running beside it can make a pick fail. The pick is retried next pass, so
  this costs time rather than correctness.

## Landed from this, and handed off

`AssistedTargetingUpdate.cpp` adopted `AIUpdate.h` for `AICommandInterface`,
byte-verified 16/16, row retired.

The other five passes are **not mine to apply**: `class:Drawable` and
`class:Vector3` were claimed by another seat between the probe and the apply,
and AGENTS.md says to choose other work. They are verified passes as of this
commit, so whoever holds those classes can apply them directly:

| class | unit |
| --- | --- |
| `Drawable` | `Code/GameEngine/Source/Common/System/BuildAssistantWallLocations.cpp` |
| `Vector3` | `Code/GameEngine/Source/GameLogic/Map/TerrainLogicBridges.cpp` |
| `Vector3` | `Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/DefaultProductionExitUpdateXfer.cpp` |
| `Vector3` | `Code/Libraries/Source/WWVegas/WW3D2/fxshadernamespacesas.cpp` |
| `Vector3` | `Code/Libraries/Source/WWVegas/WWLib/sharebuf_vector3_copy_ctor.cpp` |

Headers: `Drawable` -> `Code/GameEngine/Include/GameClient/Drawable.h`,
`Vector3` -> `Code/Libraries/Source/WWVegas/WWMath/Vector3Data.h`.

## Not probed

The sweep was stopped after four of its fourteen cohorts, because a running
sweep blocks landing and the measured rate did not justify holding four more
classes' worth of pushes. Unprobed, with live row counts:
`ModelConditionFlags` 52, `ContainModuleInterface` 51, `BehaviorModule` 48,
`ModuleData` 44, `Matrix3D` 53, `DamageInfo` 32, `Overridable` 28,
`BehaviorModuleInterface` 26, `UpdateModuleInterface` 25, `LocomotorSet` 13.
At 2.2% those 372 units are worth about eight adoptions.
