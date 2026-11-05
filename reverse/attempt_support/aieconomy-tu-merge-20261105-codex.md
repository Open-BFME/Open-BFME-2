# AIEconomyBuilder consolidation, 2026-11-05

Destination: `Code/GameEngine/Source/GameLogic/SkirmishAI/AIEconomyBuilder/AIEconomyBuilder.cpp`.
`tu_skeleton.py` rebuilt its stale TU map in memory: 42 approved rows,
four clean donors and five mixed files. The destination remains a provisional
approved map assignment; this pass supplies no new original-path evidence.

## Prerequisite and result

The earlier attempt at this TU is recorded in `reverse/re_attempts.log` under
`tu-merge:Code/GameEngine/Source/GameLogic/SkirmishAI/AIEconomyBuilder/AIEconomyBuilder.cpp`.
The farm-library transfer donor needed the shared class's method declaration.
It now includes `AIEconomyBuilderFarmLibrary.h`, and the seed no longer hides
the STLport `push_back` body behind a declaration-only specialization.
Compiler trials isolated that declaration as the extra stack-home cause in
the composed transfer body. The separate prerequisite commit is `2ed19a4c81`.
Its header gate verified 971/971 rows in all eight dependent sources.

`tu_skeleton.py --merge` accepted the initialization and farm-library-transfer
donors, removing these two source files:

- `Code/GameEngine/Source/Common/Rva004EA420Init.cpp`
- `Code/GameEngine/Source/GameLogic/SkirmishAI/AIEconomyBuilder/AIEconomyBuilderDoXferFarmLibrary.cpp`

The tool moved all six donor ledger rows, including their EH companions,
into the destination. Only six source cells changed in the committed TU map;
the map was not regenerated. The combined unit retains 23 matched rows.

## Verification and batch audit

- `./build.sh` on the destination: 23/23 exact, three float literals verified.
- `find_declared_unmatched.py`: all definitions already matched.
- `eh_verify.py`: four EH-bearing rows EXACT; no missing objects or debt.
- `tu_ownership.py --staged`: passed. `check_csv.py` and staged whitespace
  checks passed; function/data/symbol row totals remain unchanged.
- The merge's census link guard passed with the donors removed. A fresh
  `link_check.py` predicts LINKS for all 1,529 bytes of the destination against
  the fetched 2026-11-05 05:17 census index at `c95fcfcfcd`. The unit's old
  1,145-byte census total excludes the donors: this is consolidation, with no
  new census or real-link coverage claim.
- Narrow register searches found no identity, data or Microsoft-header debt
  keyed to either absorbed donor. The merge refreshed header/MS-header queues;
  surviving class-adoption rows remain. The existing farm-list storage owner
  stays `Common/Rva007B6880Thunks.cpp` in `data_ledger.csv`.
- The tool carried the initialization donor's hatch into the destination with
  `hatch_counters.py --update`. Deduplicating the global declaration reduces
  `g_Va00E04490` occurrences from four to three. No alias pragma was removed.

Audited range: prerequisite `e5e17e246f..2ed19a4c81` plus this staged merge;
origin was fetched through `94439f5ce1` immediately before the audit.
Reviewed the complete staged path list and searched both old basenames across
tracked tooling, hooks, workflows, sources, build/config files, registers and
documentation (including narrow searches in the attempt log). No active tool,
include or path-derived consumer requires either deleted filename. Remaining
old-path mentions are provenance comments in the destination, historical
attempt evidence/logs and the recorded `reverse/link_status.csv` snapshot.
Those remain intentionally; the active function/TU/hatch registers name the
current owner. No stale object receipt was used for the destination checks.

## Remaining prerequisites

The update donor still requires the shared class's `update` declaration and
the previously recorded secondary-base/vtable reconciliation. The farm-search
donor still conflicts with STLport's `_STL::less`, and retains its existing
class-layout/EH prerequisites. Both remain separate and byte-matched. The five
mixed donors were untouched; no split was attempted inside this merge.
