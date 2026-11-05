# CivilianSpawnUpdate consolidation and AI header debt (2026-11-05)

Inspected source: `fcae9526ac63eff19e2bdc5df2b250800474faa9`.
Worker: `yasinschroeder-codex3`; model: `gpt-6.1-sol`; approximately 12 minutes.

## Scope and original evidence

The default picker claimed the approved target
`Code/GameEngine/Source/GameLogic/Object/Update/CivilianSpawnUpdate.cpp`
and its `CivilianSpawnUpdateCtorThunk.cpp` and
`CivilianSpawnUpdateModuleDataDtor.cpp` donors in the same directory.
The current planner report was regenerated with
`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/`.
It identifies differing compiler settings, private class declarations, include
contexts, two existing constructor aliases and the seed's owned parse table.
The committed TU map is stale; `tu_skeleton.py` rebuilt it in memory, reported
22 approved rows, and left the 55-row mixed `Rva0024A797Derived.cpp` untouched.
No map, source paths, rows, names, pins or hatches changed in this pass.

Original guarded dry run accepts neither donor. The constructor composition
reports undeclared `m_int08` and integer-to-enum initialization errors; the
module-data destructor composition fails bytes. `tu_views.py --dry-run`
reports enum/unsigned spellings for the update's +0x20 frame field and a
module-data `declspec` conflict: the destructor alone specifies `novtable`.
These are composition prerequisites, not lost matched rows.

## Canonical-base experiment (restored)

Replace the seed's private 12-byte ModuleData declaration with the registered
`Include/Common/ModuleData.h`; declare its unsigned `m_int08` at the beginning
of CivilianSpawnUpdateModuleData instead. This keeps spawn delay at +0x08,
followed by the existing filter +0x0C, limit +0x10 and vector +0x14. The seed's
constructor and parse table supply these target offsets; no donor evidence is
being promoted to a target layout claim.

Normal build passes **14/14 function rows and the one data row**, including
renumbered parent-EH funclet resolution, three strings and two float literals.
Owning `header_adopt_lane.py accept --class ModuleData` refuses the source
because link_check predicts a loss. The ordinary current-object preview says:

```text
CivilianSpawnUpdate.cpp: does not link  LINKED 970 -> 0 bytes
  comdat ??0ModuleData@@QAE@XZ (first: differs from the first copy in link order (no retail address))
```

The index is the 2026-11-05 05:17 census at `c95fcfcfcd`.
The failed header acceptance removes no queue key. A separate constructor
trial reconciles the frame enum casts, delay field spelling and known virtual
overrides; its three rows still match, but this does not clear the base COMDAT
or destructor prerequisites. The guarded merge still accepts no donors.
The view tool itself conservatively restores the virtual-union rewrite because
it replaces the object's `__purecall` dependency with the real name-key/update
symbols. Neither this tool refusal nor the byte-passing header trial is a
reason to bypass the link guard. All trial sources were restored byte-for-byte.

Next work must reconcile the base constructor's actual selected provider and
its consumers before attempting canonical ModuleData adoption, then verify the
constructor composition and native destructor/vtable/EH contract together.
The destructor's novtable mismatch remains an independent byte prerequisite.
No shared header or checker was changed to force this local trial.

## Landable debt cleanup and controls

The restored seed already explicitly includes the canonical AIUpdate header
and contains neither private AICommandInterface nor AIUpdateInterface.
Each owning acceptance passes independently:

```sh
python3 tools/header_adopt_lane.py accept --class AICommandInterface Code/GameEngine/Source/GameLogic/Object/Update/CivilianSpawnUpdate.cpp
python3 tools/header_adopt_lane.py accept --class AIUpdateInterface Code/GameEngine/Source/GameLogic/Object/Update/CivilianSpawnUpdate.cpp
```

Each command prints PASS and retires exactly one header-queue row. Only these
two rows leave the register; ModuleData debt remains, as do the two constructor
aliases. No alias is removed or moved, and no debt is claimed retired by prose.

After restoring the source controls, normal builds pass **21/21 function rows**
(seed 14, constructor 3, destructor 4) and the seed's one data row.
`find_declared_unmatched.py` reports all definitions matched across all three.
Ordinary current-object preview reports **3/3 LINKS**, preserving
970 + 111 + 73 = **1,154 bytes** against the cited census. This is a preview,
not a new census or a headline linking gain. Source-file reduction is zero;
header debt decreases by two. `check_csv.py` passes. There are no source moves
requiring a tooling-path compatibility audit, nor any data/identity transfers.
