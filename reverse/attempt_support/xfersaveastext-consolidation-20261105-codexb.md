# XferSaveAsText consolidation, 2026-11-05

Result: two fragments become one approved TU, reducing the source-file count
by one while retaining 48 matched rows and 7,013 authored bytes in link preview.
The prerequisite reconciliation is commit c588410866: both fragments use the
same Xfer-derived view and real STLport templates instead of private template
definitions. The link-wide `_bfmeAppend` alias remains present.

## Scope and evidence

- Destination: `Code/GameEngine/Source/Common/System/XferSaveAsText.cpp`.
- Absorbed: `Code/GameEngine/Source/Common/System/BfmeRva00C7B388Xfer.cpp`.
- Planner: `name_lane.py consolidate --under Code/GameEngine/Source/Common/System/`.
  Its WorldBuilder `Code/Libraries/Source/xfer/xfer_debug.cpp` hint is donor
  evidence, not a claim about BFME 2's original source path. The merge uses the
  current TU map rebuilt in memory by `tu_skeleton.py`, which approves 48 rows
  at the destination. No regenerated map is committed.
- `tu_skeleton.py --merge` accepted both fragments and rejected none. Its link
  guard compared the census-linked cohort together, including selected COMDATs,
  changed provider/consumer contracts and outside consumers. No loss was found.
- `./build.sh` at the final path: 48/48 exact, 82 literals, three empty-string
  references and two imports verified. Seven renumbered funclet labels were
  verified against their parents' EH data.
- `find_declared_unmatched.py`: all defined functions already matched.
- `link_check.py` at the final path: LINKS, 7,013 authored bytes. The separate
  fragments previewed 4,566 + 2,447 bytes before the merge. This preserves their
  total; it is not a new census-linked-byte claim. Index: 2026-11-05 15:52,
  commit 112a456a2c.
- `check_csv.py` and `git diff --cached --check`: pass.

## Batch audit

Audited the sole source-path change against origin/master at c588410866.
Combined basename/path searches covered tools, hooks, workflows, Code, docs and
build.sh. No active consumer needs changing. Remaining old-path mentions are
source provenance comments, historical attempt evidence, and the recorded
`reverse/link_status.csv` census result; those retain their historical meaning.

The merge tool repointed exactly 36 rows in each of functions.csv and the
committed tu_map.csv. A comparison of their removed/added records confirms only
the source column changed: identities, extents, approval and evidence remain
unchanged. The existing `_bfmeAppend` alternatename and its hatch key moved
together with the defining Print body; its count stays one. No provider or
alias was discarded as dead.

Neither fragment owns code-identity, data-check or canonical-header queue debt.
`tu_skeleton.py` refreshed the header reports through their owning tools:
Microsoft-header findings are attached to the destination, including the
existing `_vsnprintf` ABI issue. No debt retirement is claimed. The three-row
mixed STLport donor remains untouched and is not part of this merge.

Existing LINK-004 Xfer header-adoption history remains valid; this consolidation
introduces no new link obstacle and changes none of its remaining prerequisites.
