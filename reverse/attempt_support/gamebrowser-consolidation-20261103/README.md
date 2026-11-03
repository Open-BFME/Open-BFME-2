# Gamebrowser consolidation audit (2026-11-03)

Move: `Code/GameEngine/Source/Common/Rva007F63D0Set.cpp` into
`Code/Libraries/Source/Fesl/gamebrowser/gamebrowser.cpp` through
`tu_skeleton.py --merge`. One source file removed; one row repointed at
0x00662B60, with all 39 resulting rows preserved.

The planner surveyed Fesl/gamebrowser before execution; it supplied no original
path/name proof. The skeleton rebuilt current TU assignments in memory and
approved this donor; the committed TU map changes only its source cell.
Mixed and refused donors were left alone. No identifier is renamed here.

Verification: frozen-file checks before/after; `./build.sh` passed 39/39 rows
both before (two sources) and after (one TU), with 31 string references checked;
`check_csv.py` passed. The merge's LinkGuard accepted both census-linked inputs
against the 2026-11-03 20:03 index (8661f15284), including outside consumers and
COMDAT selection. `link_check.py` reports LINKS for the resulting 4,302-byte
TU; this is a preview, not a new census or real-link measurement.

`objects.json` compares independently verified pre-merge objects with the
rebuilt TU. The exact union is preserved: 39 strong definitions, 59 COMDAT
(name, digest, size) tuples, 57 undefined symbols, one weak route, COMMON data,
and all nine distinct linker directive tokens. All six alternatename pragmas
remain. No provider, alias route or COMDAT digest was removed or added.

Audit scope: local base 678d949f99 through the two preceding evidence/tooling
commits plus this staged merge; origin was fetched immediately before audit.
The only source path removed in this batch is the donor above. Searches of
active tools, hooks, workflows, source/includes, build/configuration files,
ledgers, registers and docs found no active consumer requiring a path fix.
Remaining old-path mentions are the census snapshot `reverse/link_status.csv`,
this evidence, the earlier false-reject evidence/log and TU provenance comments;
they are intentionally historical. Core ledger paths were repointed by the tool.

Neither source has code/data identity debt, gate baseline or header-queue keys.
The tool refreshed header and MS-header queues with no changes. Flag override
keys were carried with totals kept (16 rows / 14 default losses); the owning
flag proposal tool confirms the regional default still loses 14 of the current
39 rows, so the empty override remains required. Hatch totals are unchanged.
No linking obstacle entry mentions this unit, symbol or RVA; no new obstacle
was encountered.
