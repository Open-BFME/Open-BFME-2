# Tooling compatibility audit: Team.cpp merge, 2026-11-08

Run once over the complete outgoing batch before pushing, per AGENTS.md
("Publication") and `docs/consolidation.md` ("Tooling compatibility audit before
pushing").

## Audited range

`origin/master..HEAD` at the time of the audit, one path change:

    M  Code/GameEngine/Source/Common/RTS/Team.cpp
    D  Code/GameEngine/Source/Common/RTS/Team_countObjects.cpp
    M  reverse/functions.csv
    M  reverse/ms_header_queue.tsv
    M  reverse/name_basis.csv
    M  reverse/tu_map.csv

One absorbed donor, no renames, no directory moves. The merge engine repointed
`rename.PATH_COLUMNS` (`functions.csv`, `tu_map.csv`, `header_queue.tsv`,
`data_rows.csv`, `body_owners.csv` where applicable), plus `name_basis.csv`,
`ms_header_queue.tsv` and `hatch_baseline.tsv`, and printed its
`Verifier-Change:` trailer for the carried hatch key.

## Remaining references to the absorbed path, classified

A tree-wide search for `Team_countObjects` outside `build/` returns these, and
**none requires a change**:

| where | classification |
| --- | --- |
| `Code/GameEngine/Source/Common/RTS/Team.cpp:3776` | the merge's own provenance comment, `// ---- from .../Team_countObjects.cpp`. Intended. |
| `reverse/name_basis.csv:153` | a basis record whose *origin* column is the pre-merge path and whose destination column the merge repointed to `Team.cpp`. Historical by design. |
| `reverse/class_contracts/ThingTemplate.json:1475` | the contract's list of units that contributed a view. Historical evidence of where a view came from. |
| `reverse/attempt_support/team-consolidation-20261028-bce2/merge-report.json` | a banked merge report from 2026-10-28. Historical evidence. |
| `reverse/link_status.csv:1794` | **generated**, see below. |
| `reference/open-bfme-1/**` (8 hits) | the BFME 1 submodule, whose paths are `game/GameEngine/...` and unrelated to this tree. Never committed from here. |

`docs/consolidation.md` step 4 is explicit that original path strings and
historical evidence are preserved and remaining mentions classified rather than
replaced, which is what the first four rows above are.

## link_status.csv is generated, and is stale until the next census

`reverse/link_status.csv` carries a row keyed by the absorbed donor and is
**not** in `rename.PATH_COLUMNS`, so the merge did not repoint it. It does not
need repointing: it is written by `tools/link_census.py` (and read by
`progress.py`, `class_views.py`, `cycle_diff.py`, `data_back_rank.py`,
`census_rebaseline.py`), so it is a census artifact that regenerates with
correct paths on the next census run.

I did not refresh it. Running the census (`link_cycle.py`,
`nightly_measure.py`) needs a maintainer's OK under AGENTS.md, and the audit
checklist's "refresh affected generated reports through their owning tools"
cannot be satisfied here without that. The staleness is one row naming a file
that no longer exists, in a report whose own `LINK PROBLEMS` figure counts
losing COMDATs and wrongly selected providers -- the absorbed donor contributed
none (`yes,0,0,0,0,0`), so no figure moves.

Worth noting for whoever extends the lane: if source-path moves become frequent,
`link_status.csv` is an active registry that the merge engine does not repoint,
and `docs/consolidation.md` step 3 invites extending shared repointing support
when another active registry needs it. One stale row per merge is cheap; a
consolidation wave would leave many.

## Other checks

- `./build.sh Code/GameEngine/Source/Common/RTS/Team.cpp`: 166/166 matched, 1
  data row byte-verified, 5 string literals verified, EH EXACT 15.
- `tools/find_declared_unmatched.py` on the TU: clean (167 matched rows, all
  defined functions already matched).
- The merge's own `link_guard` judged the composition against the census before
  writing, and `link_batch_audit` runs once in the pre-push hook for the batch.
- No baseline line added; the hatch key moved as a transfer with the printed
  trailer.
