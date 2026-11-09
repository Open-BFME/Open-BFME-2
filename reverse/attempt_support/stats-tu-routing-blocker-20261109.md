# Statistics TU routing prerequisite (2026-11-09)

After the two statistics sources adopted ModuleInfo's shared header, the
supported consolidation planner and a fresh in-memory TU plan were inspected.
No Code, ledger or source-path change was made by this investigation.

`name_lane.py consolidate --under Code/GameEngine/Source/Common/` wrote
`build/consolidation/stats-20261109/`. Its suggested
`Thing/ThingFactoryIniStatsHelper.cpp` grouping is a hint, not an approved
destination. The committed map was stale; the following supported commands
rebuilt their routing from current inputs instead of trusting it:

```
python3 tools/tu_skeleton.py --plan Code/GameEngine/Source/Common/INIStatsRecord.cpp
python3 tools/tu_skeleton.py --split Code/GameEngine/Source/Common/Rva0050CBA2StatsDump.cpp
python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/Common/INIStatsRecord.cpp --dry-run
```

The split overview finds 22 diagnostic-fragment rows with no approved TU and
one approved for INIStatsRecord.cpp: destructor 0x0050C688, 21 bytes. The full
INIStatsRecord plan has 11 approved rows: six already in its TU, that destructor,
three rows in a separate STLport vector provider containing 64 other rows, and
one matched funclet placeholder. The diagnostic fragment likewise contains
22 other rows. Neither mixed file is a whole-file donor.

The merge dry run reports `accepted: []`, `rejected: {}` and `blocked: fewer
than two donors`. This is a routing/mixed-file prerequisite, not a failed
compiled composition. The normal INIStatsRecord object does not define its
destructor; the diagnostic fragment supplies the 21-byte COMDAT (digest
483da72537d6). Row-only rehoming would therefore lose the provider.

Before a merge: establish approved routing for the 22 diagnostic rows; prepare
any necessary split/emission reconciliation in a separate verified change using
the supported tools; handle the mixed vector provider separately. Do not force
the planner's guessed path, split a mixed file inside a merge, or commit a
regenerated map from this lane. Once a valid batch exists, repeat the required
debt/header/provider checks and audit active path consumers before pushing.

The files have differing CRT declarations in their source text, but no compiler
composition was reached: these are observations, not demonstrated merge
failures. The two header-adoption changes remain independently verified.
Scratch receipts are `stats-tu-plan.log`, `stats-split-overview.log` and
`stats-tu-dry.log` under `build/thingtemplate-header-cohort-20261109/`.
